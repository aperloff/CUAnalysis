//Our libraries
#include "CUAnalysis/SpecialTools/interface/EventNtuple.hh"
#include "CUAnalysis/SpecialTools/interface/Table.hh"
#include "CUAnalysis/SpecialTools/interface/TableRow.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellVal.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellText.hh"
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/SpecialTools/interface/Defs.hh"
#include "CUAnalysis/SpecialTools/interface/DefaultValues.hh"
#include "CUAnalysis/Tools/interface/mymath.hh"
#include "CUAnalysis/Tools/interface/Plots.hh"
#include "CUAnalysis/Tools/interface/PlotFiller.hh"
#include "CUAnalysis/Tools/interface/PUreweight.hh"
#include "CUAnalysis/Tools/interface/CommandLine.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

// ROOT libraries
#include "TROOT.h"
#include "TSystem.h"
#include "TEnv.h"
#include "TBenchmark.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF2.h"
#include "TH2D.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TError.h"

// C++ libraries
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stdlib.h>

using namespace std;
using DEFS::LeptonCat;

typedef PlotFiller::MapOfPlots MapOfPlots;

namespace UserFunctions
{
   TString outDir;
   TString signalTitle;
   DEFS::Ana::Type analysisCat;
   DEFS::LeptonCat leptonCat;
   DEFS::LeptonBin leptonBin;
   DEFS::JetBin jetBin;
   DEFS::TagCat tagCat;
   DEFS::ControlRegion controlRegion;
   DEFS::NtupleType ntupleType;
   int limitBranches = 0;
   PUreweight* puweight;
   bool doPUreweight;
   TString pileupSystematic;
   vector<string> formats;
   bool verbose; // adds or takes away cout statements when running
   bool doBenchmarks = false;
   TBenchmark* func_benchmark  = new TBenchmark();
   TBenchmark* once_benchmark  = new TBenchmark();

   ////////////////////////////////////////////////////////////////////////////////
   //  User Functions
   ////////////////////////////////////////////////////////////////////////////////

   // Is run once for each process before events are cut (initialize)
   void initEventFunc(EventNtuple* ntuple, const PhysicsProcess* proc);
   // this function fills all of the plots for a given process
   void fillPlots(MapOfPlots &  plots, TString processName, EventNtuple * ntuple, double weight = 1.0);
   // returns a boolean if the event passes the specified cuts
   bool eventPassCuts(EventNtuple * ntuple, const PhysicsProcess*);
                                  
   // returns a double
   double weightFunc(EventNtuple* ntuple, const PhysicsProcess* proc);
   // Is run once for each process before events (initializes PU Reweighting
   void processFunc(EventNtuple* ntuple, const PhysicsProcess* proc);
   // concat any two streamable objects into a string
   template <class T, class U>
   std::string concatString(const T& obj1, const U& obj2);
}

////////////////////////////////////////////////////////////////////////////////
//  Implement User Functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void UserFunctions::fillPlots(MapOfPlots &  plots, TString processName, EventNtuple * ntuple, double weight) {
   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Start("fillPlots");

   // Global distributions
   plots[leptonCat]["MET"]->Fill(ntuple->MET);
   plots[leptonCat]["MHT"]->Fill(ntuple->MHT);
   plots[leptonCat]["HT"]->Fill(ntuple->HT);
   plots[leptonCat]["NJets"]->Fill(ntuple->NJets);
   plots[leptonCat]["NBTags"]->Fill(ntuple->BTagsDeepCSV);

   // Distributions for leptons (inclusive)
   for(unsigned int ielectron=0; ielectron<ntuple->Electrons->size(); ielectron++) {
      if(ntuple->Electrons_passIso->at(ielectron)) {
         plots[leptonCat]["ElectronPt"]->Fill(ntuple->Electrons->at(ielectron).Pt());
         plots[leptonCat]["ElectronEta"]->Fill(ntuple->Electrons->at(ielectron).Eta());
         plots[leptonCat]["ElectronPhi"]->Fill(ntuple->Electrons->at(ielectron).Phi());
      }
   }
   for(unsigned int imuon=0; imuon<ntuple->Muons->size(); imuon++) {
      if(ntuple->Muons_passIso->at(imuon)) {
         plots[leptonCat]["MuonPt"]->Fill(ntuple->Muons->at(imuon).Pt());
         plots[leptonCat]["MuonEta"]->Fill(ntuple->Muons->at(imuon).Eta());
         plots[leptonCat]["MuonPhi"]->Fill(ntuple->Muons->at(imuon).Phi());
      }
   }

   // Distributions for the first 10 jets
   for (int ijet=0; ijet<ntuple->NJets && ijet<10; ijet++) {
      string name = UserFunctions::concatString("Jet",ijet)+"Pt";
      plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Pt());
      name = UserFunctions::concatString("Jet",ijet)+"Eta";
      plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Eta());
      name = UserFunctions::concatString("Jet",ijet)+"Phi";
      plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Phi());
   }

   if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis) {
      // NJets in HEM region
      int nJetCounter = 0;
      for(auto jet : *(ntuple->Jets)) {
         //HEM 15/16 problem at -3<eta<-1.4 and 280<phi<320 (-1.3962634<phi<-0.698131701)
         if(jet.Eta()<-1.4 && jet.Eta()>-3 && jet.Phi()>-1.3962634 && jet.Phi()<-0.698131701 && jet.Pt()>=30. && abs(jet.Eta())<=2.4)
            nJetCounter++;
      }
      plots[leptonCat]["NJets_HEMRegion"]->Fill(nJetCounter);
   }

   if(UserFunctions::doBenchmarks) {
      UserFunctions::func_benchmark->Stop("fillPlots");
      float rt = 0, ct = 0;
      cout << endl << "PlotFiller::func_benchmark" << endl;
      vector<string> timers; 
      timers.push_back("weightFunc");
      timers.push_back("initEventFunc");
      timers.push_back("processFunc");
      timers.push_back("fillPlots");
      DefaultValues::printSummary(func_benchmark, 8, rt, ct, timers);
      func_benchmark->Reset();
   }
}//fillPlots

//______________________________________________________________________________
// Return true if the event pass the cuts imposed to the given lepton category
bool UserFunctions::eventPassCuts(EventNtuple * ntuple, const PhysicsProcess* proc) {  

   // An OR condition of several triggers
   vector<string> triggers_to_check = {"HLT_PFMET100_PFMHT100_IDTight_v","HLT_PFMET110_PFMHT110_IDTight_v",
                                       "HLT_PFMET120_PFMHT120_IDTight_v","HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v",
                                       "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v"};
   
   vector<int> trigger_indices = DefaultValues::vfind_many(*(ntuple->TriggerNames),triggers_to_check);
   //loop over trigger names
   bool goodTrigger = false;
   for(unsigned h = 0; h < trigger_indices.size(); h++){
      unsigned index = trigger_indices[h];
      //check:
      //1) if the decision was true (the line fired)
      //2) if the line was not prescaled (currently ignored)
      if(ntuple->TriggerPass->at(index)==1) {
         goodTrigger = true;
         break;
      }
   }
   //skip event if finished searching and no HLT lines found
   if(goodTrigger == false)
      return false;

   // Check the number of leptons
   if ((UserFunctions::leptonBin == DEFS::leptons0) && ((ntuple->NElectrons+ntuple->NMuons)!=0))
      return false;
   else if ((UserFunctions::leptonBin == DEFS::lepton1) && ((ntuple->NElectrons+ntuple->NMuons)>1 || (ntuple->NElectrons+ntuple->NMuons)==0))
      return false;

   if (controlRegion == DEFS::all)
      return true;

   return true;  

}// eventPassCuts

double UserFunctions::weightFunc(EventNtuple* ntuple, const PhysicsProcess* proc)
{
   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Start("weightFunc");

   TString auxName = proc->name;
   auxName.ToUpper();
   
   double weight = 1.0;
   
   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Stop("weightFunc");

   return weight;

} // weightFunc

void UserFunctions::initEventFunc(EventNtuple* ntuple, const PhysicsProcess* proc)
{
   if(UserFunctions::doBenchmarks) {
      UserFunctions::func_benchmark->Reset();
      UserFunctions::func_benchmark->Start("initEventFunc");
   }

   TString auxName = proc->name;
   auxName.ToUpper();

   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Stop("initEventFunc");
} // initEventFunc

//This is run once per process before looping over events
void UserFunctions::processFunc(EventNtuple* ntuple, const PhysicsProcess* proc)
{
   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Start("processFunc");

   TString auxName = proc->name;
   auxName.ToUpper();

   if(UserFunctions::doBenchmarks)
      UserFunctions::func_benchmark->Stop("processFunc");

} // processFunc

template <class T, class U>
std::string UserFunctions::concatString(const T& obj1, const U& obj2)
{
   std::ostringstream output;
   output << obj1 << obj2;
   return output.str();
}//concatString

////////////////////////////////////////////////////////////////////////////////
//  Local Functions
////////////////////////////////////////////////////////////////////////////////

///  fills the histograms and controls the output canvas and file for the rest of the program
void doPlotter(MapOfPlots & plots, vector<PhysicsProcess*> procs, bool doPUrewt, int maxEvts, bool verbose);

/// get the formatted canvases
vector<TCanvas*> getCanvases(MapOfPlots & plots, vector<PhysicsProcess*> procs);

/// write the Canvases and plots to output files 
void writePlotsToFile(TString histoFileName, TString canvasFileName,
                      MapOfPlots & plots, vector<TCanvas*> canvases);

/// returns a map containing all of the plots that will be made for each process and their specific attributes
PlotFiller::MapOfPlots getPlots(DEFS::LeptonCat leptonCat, bool norm_data);

/// Make a table of the plot names from the MapOfPlots (optional: print the table to the command line)
Table makePlotTable(MapOfPlots& plots);

////////////////////////////////////////////////////////////////////////////////
//  main
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
int main(int argc,char**argv) {
 
   // evaluate command-line / configuration file options
   CommandLine cl;
   if (!cl.parse(argc,argv)) return 0;

   string           anaCat               = cl.getValue<string>    ("ana",            "HEMAnalysis");
   UserFunctions::analysisCat            = DEFS::Ana::getAnaType  (anaCat);
   string           lepCat               = cl.getValue<string>    ("lep",                   "both");
   UserFunctions::leptonCat              = DEFS::getLeptonCat     (lepCat);
   string           lepBin               = cl.getValue<string>    ("lepBin",            "leptons0");
   UserFunctions::leptonBin              = DEFS::getLeptonBin     (lepBin);
   string           ntype                = cl.getValue<string>    ("ntype",          "EventNtuple");
   UserFunctions::ntupleType             = DEFS::getNtupleType    (ntype);
   string           jBin                 = cl.getValue<string>    ("jBin",                 "jets2");      
   UserFunctions::jetBin                 = DEFS::getJetBin        (jBin);
   string           cutRegion            = cl.getValue<string>    ("cutRegion",              "all");
   UserFunctions::controlRegion          = DEFS::getControlRegion (cutRegion);
   string           tcat                 = cl.getValue<string>    ("tcat",                "pretag");
   UserFunctions::tagCat                 = DEFS::getTagCat(tcat);
   UserFunctions::doPUreweight           = cl.getValue<bool>      ("doPUrewt",                true);
   UserFunctions::pileupSystematic       = cl.getValue<TString>   ("pileupSystematic",   "nominal");
   UserFunctions::outDir                 = cl.getValue<string>    ("outDir",                   ".");
   UserFunctions::formats                = cl.getVector<string>   ("formats",        ".png:::.eps");
   UserFunctions::verbose                = cl.getValue<bool>      ("verbose",                false);
   bool             include_data         = cl.getValue<bool>      ("include_data",            true);
   bool             include_systematics  = cl.getValue<bool>      ("include_systematics",    false);
   bool             norm_data            = cl.getValue<bool>      ("norm_data",              false);
   int              maxEvts              = cl.getValue<int>       ("maxEvents",                  0);
   UserFunctions::limitBranches          = cl.getValue<int>       ("limitBranches",              0);
   bool             debug                = cl.getValue<bool>      ("debug",                  false);
   UserFunctions::doBenchmarks           = cl.getValue<bool>      ("doBenchmarks",           false);
   UserFunctions::signalTitle            = cl.getValue<TString>   ("signalTitle",     "H(125)->WW");
   bool             help                 = cl.getValue<bool>      ("help",                   false);

   if (help) {cl.print(); return 0;}
   if (!cl.check()) return -1;
   cl.print();

   // Trying to speed up the code
   gEnv->SetValue("TFile.AsyncPrefetching", 1);

   // Check that the leptcat actually exists
   if (UserFunctions::leptonCat == DEFS::none) {
      cout<<"plotter_x called with unknown lepton category "<<lepCat<<endl;
      return -2;
   }

   // Check that the leptcat is not both as we are not ready for it. 
   // Problems if combining:
   // - we have to figure out how to include two lums.
   // - we have to figure out how to cut on one category but not the other.
   //if (UserFunctions::leptonCat == DEFS::both) {
   //   cout<<"plotter_x called with lepton category both. WE HAVE NOT FIXED THIS TO WORK YET."<<lepCat<<endl;
   //   return 1;
   //}

   // Tell ROOT to not print useless INFO
   gErrorIgnoreLevel = kWarning;

   TBenchmark* m_benchmark = new TBenchmark();
   m_benchmark->Reset();
   m_benchmark->Start("plotter_x");
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Reset();


   // The vector containing all plots to be made
   MapOfPlots plots = getPlots(UserFunctions::leptonCat,norm_data);

   // Make a table of the plots to be run
   Table plotTable = makePlotTable(plots);
   
   // The vector holding all processes.
   vector <PhysicsProcess*> procs;
   if(debug) {
      vector<DEFS::PhysicsProcess::Type> p;
      p.push_back(DEFS::PhysicsProcess::Data_JetHT);
      procs = DefaultValues::getProcesses(p, UserFunctions::jetBin, UserFunctions::tagCat, true, UserFunctions::ntupleType);
   }
   else if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis) {
      procs = DefaultValues::getProcessesHEM(UserFunctions::jetBin, UserFunctions::tagCat,
                                             include_data, true, UserFunctions::ntupleType);
   }
   else if(UserFunctions::analysisCat == DEFS::Ana::RA2bAnalysis) {
      procs = DefaultValues::getProcessesRA2b(UserFunctions::jetBin, UserFunctions::tagCat,
                                              include_data, include_systematics,true,
                                              UserFunctions::ntupleType, UserFunctions::leptonCat);
   }
   else {
      cout << "ERROR::plotter_x Unknown analysis type. The program cannot continue." << endl;
      return -3;
   }

   // Report Scale Factors
   int maxNameLength = 0;
   for(auto p : procs) {
      if(p->name.Length()>maxNameLength)
         maxNameLength = p->name.Length(); 
   }

   cout << endl << "Process " << setw(maxNameLength) << "<name>" << " will be scaled by " << setw(15) << "<cross section>" << " * " << setw(12) << "<luminosity>"
        << " * " << setw(14) << "<scale factor>" << " * " << setw(17) << "<branching ratio>" << " / " << setw(15) << "<events in PAT>" << " = " << setw(13) << "<final value>" << endl; 
   for (unsigned p = 0; p< procs.size(); p++) {
     cout<<"Process "<<setw(maxNameLength)<<procs[p]->name<<" will be scaled by "<<setw(15)<<procs[p]->sigma[UserFunctions::leptonCat]<<" * "
         <<setw(12)<<procs[p]->intLum[UserFunctions::leptonCat]<<" * "<<setw(14)<<procs[p]->scaleFactor[UserFunctions::leptonCat]
         <<" * "<<setw(17)<<procs[p]->branching_ratio[UserFunctions::leptonCat]<<" / "<<setw(15)<<procs[p]->initial_events[UserFunctions::leptonCat]
         <<" = "<<setw(13)<<procs[p]->getScaleFactor(UserFunctions::leptonCat)<<endl;
   }

   // Print the plot table
   // I like doing this here for the aesthetics of the printouts
   plotTable.printTable(cout);

   // Fill all the plots 
   doPlotter(plots, procs, UserFunctions::doPUreweight, maxEvts, UserFunctions::verbose);

   // Write output to file. The processs are passed to obtain the canvases
   if(!UserFunctions::outDir.EndsWith("/")) UserFunctions::outDir+="/";
   if(!gSystem->OpenDirectory(UserFunctions::outDir)) gSystem->mkdir(UserFunctions::outDir);
   vector<TCanvas*> canvases = getCanvases(plots, procs);
   TString histoFileName = UserFunctions::outDir + "histos.root";
   TString canvasFileName = UserFunctions::outDir + "canvases.root";
   writePlotsToFile(histoFileName, canvasFileName, plots, canvases);

   if(UserFunctions::doBenchmarks) {
      cout << endl << "plotter_x::once_benchmark" << endl;
      float rt = 0, ct = 0;
      vector<string> timers;
      timers.push_back("getPlotsForLeptonCat");
      timers.push_back("getPlots");
      timers.push_back("doPlotterSetup");
      timers.push_back("writePlotsToFile");
      DefaultValues::printSummary(UserFunctions::once_benchmark, 8, rt, ct, timers);
   }

   m_benchmark->Stop("plotter_x");
   cout << "plotter_x" << endl << "\tCPU time = " << m_benchmark->GetCpuTime("plotter_x") << " s" << endl
        << "\tReal time = " << m_benchmark->GetRealTime("plotter_x") << " s" << endl;
   delete m_benchmark;

   return 0;

}//plotter()


////////////////////////////////////////////////////////////////////////////////
//  Implement Local Functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
vector<TCanvas*> getCanvases(MapOfPlots & plots, vector<PhysicsProcess*> procs) {
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("getCanvases");

   vector<TCanvas*> canvases;
   for ( MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
      for ( map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end() ; p2++){
         if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis)
            canvases.push_back(((FormattedPlot*) p2->second)->getCanvasTDR(procs));
         else
            canvases.push_back(((FormattedPlot*) p2->second)->getStackedCanvasTDR(procs));
      }
   }

   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Stop("getCanvases");

   return canvases;
}

//______________________________________________________________________________
void writePlotsToFile(TString histoFileName, TString canvasFileName, 
                      MapOfPlots & plots, vector<TCanvas*> canvases){
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("writePlotsToFile");

   //Get the canvas and write them to file and as <formats>
   cout<<"Writing canvas(es) to rootfile "<<canvasFileName<<endl;
   TFile * canOutFile = new TFile(canvasFileName,"RECREATE");
   for(auto can : canvases) {
      TString canName = UserFunctions::outDir+"/"+can->GetName();
      canName += "_"+DEFS::getLeptonCatString(UserFunctions::leptonCat);
      cout << "\tSaving canvas " << canName << " ... ";
      can->Write();
      for (auto format : UserFunctions::formats)
         can->SaveAs(canName+format);
      cout << "DONE" << endl << flush;
   }
   canOutFile->Close();

   //Get the Histos and write them to file
   //NOTE: this needs to be done AFTER the writing of the canvases as the
   //      scaling of the histos is done at that stage. 
   cout<<"Writing histo(s) to rootfile "<<histoFileName<<endl;
   bool firstH = true;
   for(MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
      for(map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end() ; p2++) {
         if(firstH) {
            ((FormattedPlot*) p2->second)->saveHistogramsToFile(histoFileName,"RECREATE");
            firstH = false;
         }
         else {
            ((FormattedPlot*) p2->second)->saveHistogramsToFile(histoFileName,"UPDATE");
         }
      }// for histos inside plot
   }// for plots  

   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Stop("writePlotsToFile");
}//writePlotsToFile

//______________________________________________________________________________
void doPlotter(MapOfPlots & plots, vector<PhysicsProcess*> procs, bool doPUrewt,
               int maxEvts, bool verbose) {
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("doPlotterSetup");

   PlotFiller pFill(plots, procs, &UserFunctions::fillPlots);
   pFill.setCutFunction(&UserFunctions::eventPassCuts);
   pFill.setWeightFunction(&UserFunctions::weightFunc);
   pFill.setProcessFunction(&UserFunctions::processFunc);
   pFill.setInitializeEventFunction(&UserFunctions::initEventFunc);
   pFill.setLimitBranches(UserFunctions::limitBranches);
   if (maxEvts>0)
      pFill.setMaximumEventsDEBUG(maxEvts);

   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("doPlotterSetup");

   pFill.run();

}//plotter(.., .., etc)

//______________________________________________________________________________
MapOfPlots getPlotsForCat(DEFS::LeptonCat leptonCat, bool norm_data){
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("getPlotsForLeptonCat");

   MapOfPlots plots;

   FormattedPlot* a = new FormattedPlot;

   //Goes in the label and tells us whether we are looking at electrons or muons
   TString lepStr = "_"+DEFS::getLeptonCatString(leptonCat);

   // The overlay of a scaled signal. For signalName pick the groupingName 
   // of one of the processes. Or just "" if you don't want a signal overlayed.
   //TString signalName = "ggH+WH+qqH(125)";
   TString signalName = UserFunctions::signalTitle;
   double signalFactor = 1.0;
   if(leptonCat == DEFS::electron) signalFactor = 1.0;
   else if(leptonCat == DEFS::muon) signalFactor = 1.0;
   else signalFactor = 1.0;

   //Double_t leptonptbinslow[9] = {20,25,30,35,40,50,70,100,1000};
   //Double_t leptonptbinshigh[10] = {20,50,55,60,65,70,80,100,120,1000};
   //Double_t jetptbinslow[9] = {20,25,30,35,40,50,70,100,1000};   
   //Double_t jetptbinshigh[10] = {20,50,80,100,110,120,130,140,160,1000};
   //Double_t Mjjbinslow[11] = {20,40,50,60,70,80,90,100,200,300,1000};
   //Double_t Mjjbinshigh[11] = {20,100,110,120,130,150,180,200,250,350,1000};
   //Double_t Mtbinshigh[11] = {0,20,40,60,70,80,100,120,140,200,1000};
   //Double_t METbinshigh[10] = {0,40,50,60,70,80,100,120,200,1000};
   //Double_t DRlepjet1low[10] = {0.3,0.5,0.9,1.3,1.5,1.7,2.0,2.5,3.0,5.0};
   //Double_t DRlepjet1high[11] = {0.3,2.0,2.25,2.5,2.75,3.0,3.25,3.5,4.0,4.5,5.0};
   Double_t etabins[83] = {
     -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, 
     -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, 
     -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, 
     -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, 
     -0.435, -0.348, -0.261, -0.174, -0.087, 
     +0.000, 
     +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
     +0.879, +0.957, +1.044, +1.131, +1.218, +1.305, +1.392, +1.479, +1.566, 
     +1.653, +1.740, +1.830, +1.930, +2.043, +2.172, +2.322, +2.500, +2.650, 
     +2.853, +2.964, +3.139, +3.314, +3.489, +3.664, +3.839, +4.013, +4.191, 
     +4.363, +4.538, +4.716, +4.889, +5.191};
   
   Double_t absetabins[42] = {0.000, 
     +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
     +0.879, +0.957, +1.044, +1.131, +1.218, +1.305, +1.392, +1.479, +1.566, 
     +1.653, +1.740, +1.830, +1.930, +2.043, +2.172, +2.322, +2.500, +2.650, 
     +2.853, +2.964, +3.139, +3.314, +3.489, +3.664, +3.839, +4.013, +4.191, 
     +4.363, +4.538, +4.716, +4.889, +5.191};
     
   //goes in the label and tells us what cuts we are applying
   string cut = "_MET > 35, elPt > 30";
   TString cuts = TString(cut);
   TString name = "";
   TString title = "";

   name = "MET";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 20, 0, 1000),
                         {"E_{T}^{miss} [GeV]","Number of Events / 50 GeV"},
                         make_pair(0.,1000.));   
   plots[leptonCat][string(name)] = a;

   name = "MHT";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 20, 0, 1000),
                         {"H_{T}^{miss} [GeV]","Number of Events / 50 GeV"},
                         make_pair(0.,1000.));   
   plots[leptonCat][string(name)] = a;

   name = "HT";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 80, 0, 4000),
                         {"H_{T} [GeV]","Number of Events / 50 GeV"},
                         make_pair(0.,4000.));   
   plots[leptonCat][string(name)] = a;

   name = "NJets";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 20, 0, 20),
                         {"N_{jets}","Number of Events"},
                         make_pair(0.,20.));   
   plots[leptonCat][string(name)] = a;

   if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis) {
      name = "NJets_HEMRegion";
      a = new FormattedPlot(new TH1D(name + lepStr, name, 20, 0, 20),
                            {"N_{jets}","Number of Events"},
                            make_pair(0.,20.));   
      plots[leptonCat][string(name)] = a;
   }

   name = "NBTags";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 20, 0, 20),
                         {"N_{btags}","Number of Events"},
                         make_pair(0.,20.));   
   plots[leptonCat][string(name)] = a;

   name = "ElectronPt";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 100, 0, 1000),
                         {"p_{T}^{e}","Number of Events / 10 GeV"},
                         make_pair(0.,1000.));   
   plots[leptonCat][string(name)] = a;

   name = "ElectronEta";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 100, -5, 5),
                         {"#eta^{e}","Number of Events / 0.05"},
                         make_pair(-5.,5.));   
   plots[leptonCat][string(name)] = a;

   name = "ElectronPhi";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 61, -TMath::Pi(), TMath::Pi()),
                         {"#phi^{e}","Number of Events / 0.103"},
                         make_pair(-TMath::Pi(),TMath::Pi()));   
   plots[leptonCat][string(name)] = a;

   name = "MuonPt";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 100, 0, 1000),
                         {"p_{T}^{#mu}","Number of Events / 10 GeV"},
                         make_pair(0.,1000.));   
   plots[leptonCat][string(name)] = a;

   name = "MuonEta";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 100, -5, 5),
                         {"#eta^{#mu}","Number of Events / 0.05"},
                         make_pair(-5.,5.));   
   plots[leptonCat][string(name)] = a;

   name = "MuonPhi";
   a = new FormattedPlot(new TH1D(name + lepStr, name, 61, -TMath::Pi(), TMath::Pi()),
                         {"#phi^{#mu}","Number of Events / 0.103"},
                         make_pair(-TMath::Pi(),TMath::Pi()));   
   plots[leptonCat][string(name)] = a;

   for (unsigned int ijet=0; ijet<10; ijet++) {
      name = UserFunctions::concatString("Jet",ijet)+"Pt";
      a = new FormattedPlot(new TH1D(name + lepStr, name, 100, 0, 1000),
                            {UserFunctions::concatString("p_{T}^{jet",ijet)+"}","Number of Events / 10 GeV"},
                            make_pair(0.,1000.));   
      plots[leptonCat][string(name)] = a;

      name = UserFunctions::concatString("Jet",ijet)+"Eta";
      a = new FormattedPlot(new TH1D(name + lepStr, name, 100, -5, 5),
                            {UserFunctions::concatString("#eta^{jet",ijet)+"}","Number of Events / 0.05"},
                            make_pair(-5.,5.));   
      plots[leptonCat][string(name)] = a;

      name = UserFunctions::concatString("Jet",ijet)+"Phi";
      a = new FormattedPlot(new TH1D(name + lepStr, name, 61, -TMath::Pi(), TMath::Pi()),
                            {UserFunctions::concatString("#phi^{jet",ijet)+"}","Number of Events / 0.103"},
                            make_pair(-TMath::Pi(),TMath::Pi()));   
      plots[leptonCat][string(name)] = a;
   }

   for(auto iplot=plots[leptonCat].begin(); iplot!=plots[leptonCat].end(); iplot++) {
      dynamic_cast<FormattedPlot*>(iplot->second)->normToData = norm_data;
      dynamic_cast<FormattedPlot*>(iplot->second)->stacked = false;
      dynamic_cast<FormattedPlot*>(iplot->second)->leptonCat = leptonCat;
      dynamic_cast<FormattedPlot*>(iplot->second)->jetBin = UserFunctions::jetBin;
      dynamic_cast<FormattedPlot*>(iplot->second)->tagCat = UserFunctions::tagCat;
      dynamic_cast<FormattedPlot*>(iplot->second)->controlRegion = UserFunctions::controlRegion;
      dynamic_cast<FormattedPlot*>(iplot->second)->overlaySignalName = signalName;
      dynamic_cast<FormattedPlot*>(iplot->second)->overlaySignalFactor = signalFactor;
   }

   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Stop("getPlotsForLeptonCat");

   // return all the plots to be made
   return plots;

}//getPlotsForLeptonCat


//______________________________________________________________________________
MapOfPlots getPlots(DEFS::LeptonCat leptonCat, bool norm_data){
   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Start("getPlots");

   //All plots
   MapOfPlots plots;

   //Add plots based on category
   MapOfPlots plots_cat = getPlotsForCat(leptonCat, norm_data);
   plots.insert(plots_cat.begin(),plots_cat.end());

   if(UserFunctions::doBenchmarks)
      UserFunctions::once_benchmark->Stop("getPlots");

   return plots;
}

//______________________________________________________________________________
Table makePlotTable(MapOfPlots& plots) {
   Table table("List of Plots");
   TableRow* tableRow;
   TableCellText* tableCellText;
   stringstream out;

   for ( MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
      int counter = 0;
      for ( map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end() ; p2++, counter++){
         out << counter;
         tableRow = new TableRow(out.str());
         out.str("");
         tableCellText = new TableCellText("Plot Name");
         tableCellText->text = p2->first;
         tableRow->addCellEntries(tableCellText);
         table.addRow(*tableRow);
         delete tableRow;
      }
   }

   return table;
}
