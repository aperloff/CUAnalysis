//Our libraries
#include "CUAnalysis/SpecialTools/interface/EventNtuple.hh"
#include "CUAnalysis/SpecialTools/interface/Table.hh"
#include "CUAnalysis/SpecialTools/interface/TableRow.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellVal.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellText.hh"
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/SpecialTools/interface/Defs.hh"
#include "CUAnalysis/SpecialTools/interface/DefaultValues.hh"
#include "CUAnalysis/SpecialTools/interface/VectorUtilities.hh"
#include "CUAnalysis/Tools/interface/mymath.hh"
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

namespace UserFunctions
{
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
    bool verbose; // adds or takes away cout statements when running
    bool doBenchmarks = false;
    TBenchmark* func_benchmark  = new TBenchmark();
    TBenchmark* once_benchmark  = new TBenchmark();

    ////////////////////////////////////////////////////////////////////////////////
    //  User Functions
    ////////////////////////////////////////////////////////////////////////////////

    // Is run once for each process before events are cut (initialize)
    void initEventFunc(EventNtuple *ntuple, const PhysicsProcess* proc);

    // this function fills all of the plots for a given process
    void fillPlots(PlotFiller::MapOfPlots &plots, TString processName, EventNtuple *ntuple, double weight = 1.0);

    // returns a boolean if the event passes the specified cuts
    bool eventPassCuts(EventNtuple *ntuple, const PhysicsProcess* proc, Table &cutFlow);                              

    // returns a double
    double weightFunc(EventNtuple *ntuple, const PhysicsProcess *proc);

    // Is run once for each process before events (initializes PU Reweighting
    void processFunc(EventNtuple *ntuple, const PhysicsProcess *proc);

    // concat any two streamable objects into a string
    template <class T, class U>
    std::string concatString(const T& obj1, const U& obj2);

    /// increments the specified tables
    inline void incrementCounter(int nCut, string pName, Table &t1) {
        (*(t1(DEFS::getCutLevelString((DEFS::CutLevel)nCut),pName)))++;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Implement User Functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void UserFunctions::fillPlots(PlotFiller::MapOfPlots &  plots, TString processName, EventNtuple * ntuple, double weight) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Start("fillPlots");

    // Global distributions
    plots[leptonCat]["MET"]->Fill(ntuple->MET,weight);
    plots[leptonCat]["MHT"]->Fill(ntuple->MHT,weight);
    plots[leptonCat]["HT"]->Fill(ntuple->HT,weight);
    plots[leptonCat]["NJets"]->Fill(ntuple->NJets,weight);
    plots[leptonCat]["NBTags"]->Fill(ntuple->BTagsDeepCSV,weight);

    // Distributions for leptons (inclusive)
    for(unsigned int ielectron=0; ielectron<ntuple->Electrons->size(); ielectron++) {
        if(ntuple->Electrons_passIso->at(ielectron)) {
            plots[leptonCat]["ElectronPt"]->Fill(ntuple->Electrons->at(ielectron).Pt(),weight);
            plots[leptonCat]["ElectronEta"]->Fill(ntuple->Electrons->at(ielectron).Eta(),weight);
            plots[leptonCat]["ElectronPhi"]->Fill(ntuple->Electrons->at(ielectron).Phi(),weight);
            plots[leptonCat]["ElectronEtaPhi"]->Fill(ntuple->Electrons->at(ielectron).Eta(),ntuple->Electrons->at(ielectron).Phi(),weight);
        }
    }
    for(unsigned int imuon=0; imuon<ntuple->Muons->size(); imuon++) {
        if(ntuple->Muons_passIso->at(imuon)) {
            plots[leptonCat]["MuonPt"]->Fill(ntuple->Muons->at(imuon).Pt(),weight);
            plots[leptonCat]["MuonEta"]->Fill(ntuple->Muons->at(imuon).Eta(),weight);
            plots[leptonCat]["MuonPhi"]->Fill(ntuple->Muons->at(imuon).Phi(),weight);
        }
    }

    // Distributions for the first 10 jets
    for (int ijet=0; ijet<ntuple->NJets && ijet<10; ijet++) {
        string name = UserFunctions::concatString("Jet",ijet)+"Pt";
        plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Pt(),weight);
        name = UserFunctions::concatString("Jet",ijet)+"Eta";
        plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Eta(),weight);
        name = UserFunctions::concatString("Jet",ijet)+"Phi";
        plots[leptonCat][name]->Fill(ntuple->Jets->at(ijet).Phi(),weight);
    }
    // DeltaPhi for the first 4 jets
    for (unsigned int ijet=0; ijet<4; ijet++) {
        string name = UserFunctions::concatString("Jet",ijet)+"DeltaPhi";
        if(ijet==0)      plots[leptonCat][name]->Fill(ntuple->DeltaPhi1,weight);
        else if(ijet==1) plots[leptonCat][name]->Fill(ntuple->DeltaPhi2,weight);
        else if(ijet==2) plots[leptonCat][name]->Fill(ntuple->DeltaPhi3,weight);
        else if(ijet==3) plots[leptonCat][name]->Fill(ntuple->DeltaPhi4,weight);
    }

    if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis) {
        // NJets in HEM region
        int nJetCounter = 0;
        for(auto jet : *(ntuple->Jets)) {
            //HEM 15/16 problem at -3<eta<-1.4 and 270<phi<310 (-1.5707963268<phi<-0.872664626)
            if(jet.Eta()<-1.4 && jet.Eta()>-3 && jet.Phi()>-1.5707963268 && jet.Phi()<-0.872664626 && jet.Pt()>=30. && abs(jet.Eta())<=2.4)
                nJetCounter++;
        }
        plots[leptonCat]["NJets_HEMRegion"]->Fill(nJetCounter,weight);
        if(nJetCounter>=1)
            plots[leptonCat]["MET_HEMRegion"]->Fill(ntuple->MET,weight);
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
} //fillPlots

//______________________________________________________________________________
// Return true if the event pass the cuts imposed to the given lepton category
bool UserFunctions::eventPassCuts(EventNtuple * ntuple, const PhysicsProcess* proc, Table& cutFlow) {  

    // Event Filters
    // An AND condition of event filters
    if(!ntuple->HBHEIsoNoiseFilter || !ntuple->HBHENoiseFilter || !ntuple->JetID ||
       !ntuple->BadChargedCandidateFilter || !ntuple->EcalDeadCellTriggerPrimitiveFilter)
        return false;
    if(ntuple->PFCaloMETRatio >= 5)
        return false;
    for(unsigned int ijet=0; ijet<ntuple->Jets->size(); ijet++) {
        if(ntuple->Jets->at(ijet).Pt()>200 && ntuple->Jets_muonEnergyFraction->at(ijet)>0.5 &&
            abs(mymath::deltaPhi(ntuple->Jets->at(ijet).Phi(),ntuple->METPhi)) > TMath::Pi()-0.4 )
            return false;
    }
    // Missing filters:
    //ntuple->eeBadScFilter
    //ntuple->globalSuperTightHalo2016Filter
    incrementCounter(1,proc->name,cutFlow);

    // An OR condition of several triggers
    vector<string> triggers_to_check = {"HLT_PFMET100_PFMHT100_IDTight_v","HLT_PFMET110_PFMHT110_IDTight_v",
                                        "HLT_PFMET120_PFMHT120_IDTight_v","HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v",
                                        "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v"};
   
    vector<int> trigger_indices = utilities::vfind_many(*(ntuple->TriggerNames),triggers_to_check);
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
    incrementCounter(2,proc->name,cutFlow);

    // Count the number of electrons/muons Aditee style
    // Uncomment this block of code and the correct NLeptons line
    // if(ntuple->Electrons->size()>1 || ntuple->Muons->size()>1)
    //    return false;
    // int nelectrons=0;
    // for(unsigned int ielectron=0; ielectron<ntuple->Electrons->size(); ielectron++) {
    //    if(ntuple->Electrons->at(ielectron).Pt()>20. && abs(ntuple->Electrons->at(ielectron).Eta())<2.1 &&
    //       ntuple->Electrons_MTW->at(ielectron) < 100. && ntuple->Electrons_passIso->at(ielectron)) {
    //       nelectrons++;
    //    }
    // }
    // int nmuons=0;
    // for(unsigned int imuon=0; imuon<ntuple->Muons->size(); imuon++) {
    //    if(ntuple->Muons->at(imuon).Pt()>20. && abs(ntuple->Muons->at(imuon).Eta())<2.1 &&
    //       ntuple->Muons_MTW->at(imuon) < 100. && ntuple->Muons_passIso->at(imuon)) {
    //       nmuons++;
    //    }
    // }

    // Count the number of electrons/muons with the base cuts and iso cuts (to prove that is what Aditee is missing)
    // Uncommenting the block below and the other NLeptons definition is successful in recovering my numbers using the
    //  NElectrons and NMuons branches
    // int nelectrons=0;
    // for(unsigned int ielectron=0; ielectron<ntuple->Electrons->size(); ielectron++) {
    //    if(ntuple->Electrons->at(ielectron).Pt()>10. && abs(ntuple->Electrons->at(ielectron).Eta())<2.5 &&
    //       ntuple->Electrons_passIso->at(ielectron)) {
    //       nelectrons++;
    //    }
    // }
    // int nmuons=0;
    // for(unsigned int imuon=0; imuon<ntuple->Muons->size(); imuon++) {
    //    if(ntuple->Muons->at(imuon).Pt()>10. && abs(ntuple->Muons->at(imuon).Eta())<2.4 &&
    //       ntuple->Muons_passIso->at(imuon)) {
    //       nmuons++;
    //    }
    // }

    // Check the number of leptons
    int NLeptons = ntuple->NElectrons+ntuple->NMuons;
    //int NLeptons = nelectrons+nmuons;
    if ((UserFunctions::leptonBin == DEFS::leptons0) && ((NLeptons)!=0))
        return false;
    else if ((UserFunctions::leptonBin == DEFS::lepton1) && (NLeptons>1 || NLeptons==0))
        return false;
    incrementCounter(3,proc->name,cutFlow);

    if (controlRegion == DEFS::all)
        return true;

    return true;  
} //eventPassCuts

double UserFunctions::weightFunc(EventNtuple* ntuple, const PhysicsProcess* proc) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Start("weightFunc");

    TString auxName = proc->name;
    auxName.ToUpper();
   
    double weight = 1.0;
    //double weight = ntuple->Weight;
    //weight *= ntuple->puWeight;
    //if(auxName.Contains("DATA")) weight = 1.0;

    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Stop("weightFunc");

    return weight;
} //weightFunc

void UserFunctions::initEventFunc(EventNtuple* ntuple, const PhysicsProcess* proc) {
    if(UserFunctions::doBenchmarks) {
        UserFunctions::func_benchmark->Reset();
        UserFunctions::func_benchmark->Start("initEventFunc");
    }

    TString auxName = proc->name;
    auxName.ToUpper();

    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Stop("initEventFunc");
} //initEventFunc

//This is run once per process before looping over events
void UserFunctions::processFunc(EventNtuple* ntuple, const PhysicsProcess* proc) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Start("processFunc");

    TString auxName = proc->name;
    auxName.ToUpper();

    if(UserFunctions::doBenchmarks)
        UserFunctions::func_benchmark->Stop("processFunc");
} //processFunc

template <class T, class U>
std::string UserFunctions::concatString(const T& obj1, const U& obj2) {
    std::ostringstream output;
    output << obj1 << obj2;
    return output.str();
} //concatString

////////////////////////////////////////////////////////////////////////////////
//  Local Functions
////////////////////////////////////////////////////////////////////////////////

///  fills the histograms and controls the output canvas and file for the rest of the program
void doPlotter(PlotFiller::MapOfPlots& plots, vector<PhysicsProcess*> procs, Table& cutFlow, int maxEvents);

/// get the formatted canvases
vector<TCanvas*> getCanvases(PlotFiller::MapOfPlots & plots, vector<PhysicsProcess*> procs);

/// write the canvases to a ROOT file and to <formats>
void writeCanvasesToFiles(TFile &ofile, string outputDirectory, vector<TCanvas*> canvases, string suffix, vector<string> formats);

/// write the histograms to a ROOT file
void writeHistogramsToFile(TFile &ofile, PlotFiller::MapOfPlots & plots);

/// returns a map containing all of the plots that will be made for each process and their specific attributes
PlotFiller::MapOfPlots getPlots(DEFS::LeptonCat leptonCat, bool normToData, float luminosity);

/// duplicate a set of plots, defined by the plots_to_logify vector, and reset their logxy values 
void logify(PlotFiller::MapOfPlots &plots, std::vector<std::string> plots_to_logify, pair<bool,bool> logxy);

/// Make a table of the plot names from the MapOfPlots (optional: print the table to the command line)
Table makePlotTable(PlotFiller::MapOfPlots& plots);

/// Make a table of cuts for each of the processes
Table getInitializedCutTable(const vector<PhysicsProcess*> &procs);

/// prints a list of PhysicsProcesses
void printProcesses(vector <PhysicsProcess*> procs);

////////////////////////////////////////////////////////////////////////////////
//  main
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
int main(int argc,char**argv) {
 
    // evaluate command-line / configuration file options
    CommandLine cl;
    if (!cl.parse(argc,argv)) return 0;

    string           alternateDataFile    = cl.getValue<string>    ("alternateDataFile",          "");
    string           anaCat               = cl.getValue<string>    ("ana",             "HEMAnalysis");
    UserFunctions::analysisCat            = DEFS::Ana::getAnaType  (anaCat);
    int              batchNumber          = cl.getValue<int>       ("batchNumber",                -1);
    string           cutRegion            = cl.getValue<string>    ("cutRegion",               "all");
    UserFunctions::controlRegion          = DEFS::getControlRegion (cutRegion);
    bool             debug                = cl.getValue<bool>      ("debug",                   false);
    UserFunctions::doBenchmarks           = cl.getValue<bool>      ("doBenchmarks",            false);
    UserFunctions::doPUreweight           = cl.getValue<bool>      ("doPUrewt",                 true);
    vector<string>   formats              = cl.getVector<string>   ("formats",         ".png:::.eps");
    bool             help                 = cl.getValue<bool>      ("help",                    false);
    bool             include_data         = cl.getValue<bool>      ("include_data",             true);
    bool             include_systematics  = cl.getValue<bool>      ("include_systematics",     false);
    string           inputFilename        = cl.getValue<string>    ("inputFilename",              "");
    string           inputDirectoryName   = cl.getValue<string>    ("inputDirectoryName", "canvases");
    bool             isCombinedFile       = cl.getValue<bool>      ("isCombinedFile",          false);
    string           jBin                 = cl.getValue<string>    ("jBin",                  "jets2");      
    UserFunctions::jetBin                 = DEFS::getJetBin        (jBin);
    string           lepCat               = cl.getValue<string>    ("lep",                    "both");
    UserFunctions::leptonCat              = DEFS::getLeptonCat     (lepCat);
    string           lepBin               = cl.getValue<string>    ("lepBin",             "leptons0");
    UserFunctions::leptonBin              = DEFS::getLeptonBin     (lepBin);
    UserFunctions::limitBranches          = cl.getValue<int>       ("limitBranches",               0);
    float            luminosity           = cl.getValue<float>     ("luminosity",            34558.0); //pb-1
    int              maxEvts              = cl.getValue<int>       ("maxEvents",                   0);
    bool             normToData           = cl.getValue<bool>      ("normToData",              false);
    string           ntype                = cl.getValue<string>    ("ntype",           "EventNtuple");
    UserFunctions::ntupleType             = DEFS::getNtupleType    (ntype);
    string           outputDirectory      = cl.getValue<string>    ("outputDirectory",           ".");
    string           outputFilename       = cl.getValue<string>    ("outputFilename",  "output.root");
    UserFunctions::pileupSystematic       = cl.getValue<TString>   ("pileupSystematic",    "nominal");
    UserFunctions::signalTitle            = cl.getValue<TString>   ("signalTitle",      "H(125)->WW");
    string           suffix               = cl.getValue<string>    ("suffix",                     "");
    string           tcat                 = cl.getValue<string>    ("tcat",                 "pretag");
    UserFunctions::tagCat                 = DEFS::getTagCat(tcat);
    UserFunctions::verbose                = cl.getValue<bool>      ("verbose",                 false);

    if (help) {cl.print(); return 0;}
    if (!cl.check()) return -1;
    cl.print();

    // Check that the leptcat actually exists
    if (UserFunctions::leptonCat == DEFS::none) {
        cout<<"plotter_x called with unknown lepton category "<<lepCat<<endl;
        return -2;
    }

    // if is a combined file, don't need to get the systematic processes
    if(isCombinedFile) include_systematics = false;

    // Tell ROOT to not print useless INFO
    gErrorIgnoreLevel = kWarning;

    TBenchmark* m_benchmark = new TBenchmark();
    m_benchmark->Reset();
    m_benchmark->Start("plotter_x");
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Reset();
   
    // The vector holding all processes.
    vector <PhysicsProcess*> procs;
    if(debug) {
        vector<DEFS::PhysicsProcess::Type> p;
        p.push_back(DEFS::PhysicsProcess::Data_JetHT);
        procs = DefaultValues::getProcesses(p, UserFunctions::jetBin, UserFunctions::tagCat, true, UserFunctions::ntupleType);
        printProcesses(procs);
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

    // Set up the cut flow table before modifying the processes
    // That way every table will have all of the same columns regardless of whether or not that process was run
    // Makes merging the tables much easier
    Table cutFlow = getInitializedCutTable(procs);

    // Set up the batching by process (for now)
    if(batchNumber>=0) {
        if(batchNumber==0)
            procs.erase(procs.begin()+1,procs.end());
        else {
            procs.erase(procs.begin()+batchNumber+1,procs.end());
            procs.erase(procs.begin(),procs.begin()+batchNumber);
        }

        if(procs.size()!=1) {
            cout << "ERROR::plotter_x tried removing processes for batch mode, but ended up with more than one process" << endl;
            return -3;
        }
        else {
            cout << "INFO::plotter_x running in batch mode. Removeing all processes except " << procs.at(0)->name << endl;
        }

        outputFilename.insert(outputFilename.find(".root"),UserFunctions::concatString("_",batchNumber));
    }


    // Report Scale Factors
    // unsigned int maxNameLength = 0;
    // for(auto p : procs) {
    //     if(p->name.size()>maxNameLength)
    //        maxNameLength = p->name.size(); 
    // }

    // The vector containing all plots to be made
    PlotFiller::MapOfPlots plots = getPlots(UserFunctions::leptonCat,normToData,luminosity);

    // Make a table of the plots to be run
    Table plotTable = makePlotTable(plots);

    // Print the plot table    
    plotTable.printTable(cout);

    // Only do this if filling/selecting will occur
    // If reading in histograms from file and then formatting we don't need to fill the plots from the trees
    TFile *ifile = nullptr, *ifile_data = nullptr;
    TDirectoryFile *data_dir = nullptr;
    if(inputFilename.empty()) {
        // Fill all the plots 
        doPlotter(plots, procs, cutFlow, maxEvts);

        // Print the cut flot table
        cutFlow.printTable(cout);
    }
    else {
        // Open the input file
        ifile = TFile::Open(inputFilename.c_str(),"READ");
        TDirectoryFile* idir = (TDirectoryFile*)ifile->GetDirectory(inputDirectoryName.c_str());

        // Open the input file for data if necessary
        if(!alternateDataFile.empty()) {
            ifile_data = TFile::Open(alternateDataFile.c_str(),"READ");
            data_dir = (TDirectoryFile*)ifile_data->GetDirectory("");
        }

        for (PlotFiller::MapOfPlots::iterator p = plots.begin() ; p != plots.end() ; p++) {
            for (map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end(); p2++) {
                bool uniformBinWidth = true;
                double binWidth = p2->second->templateHisto->GetXaxis()->GetBinWidth(1);
                for(int ibin=1; ibin<=p2->second->templateHisto->GetXaxis()->GetNbins(); ibin++) {
                    if(binWidth!=p2->second->templateHisto->GetXaxis()->GetBinWidth(ibin))
                        uniformBinWidth = false;
                }

                double original_bin_width = p2->second->templateHisto->GetXaxis()->GetBinWidth(1);
                if(isCombinedFile)
                    p2->second->loadHistogramsFromCombinedFile(idir, UserFunctions::leptonCat);
                else
                    p2->second->loadHistogramsFromFile(idir, procs, UserFunctions::leptonCat, isCombinedFile ? true : false, data_dir);
                p2->second->setScaled(true);
                double bin_width_ratio = p2->second->templateHisto->GetXaxis()->GetBinWidth(1)/original_bin_width;

                if(uniformBinWidth) {
                    dynamic_cast<FormattedPlot*>(p2->second)->range.first *= bin_width_ratio;
                    dynamic_cast<FormattedPlot*>(p2->second)->range.second *= bin_width_ratio;
                }
                else {
                    //dynamic_cast<FormattedPlot*>(p2->second)->range.first = p2->second->templateHisto->GetXaxis()->GetXmin();
                    //dynamic_cast<FormattedPlot*>(p2->second)->range.second = p2->second->templateHisto->GetXaxis()->GetXmax();
                }

                if(debug) {
                    p2->second->printList();
                }
            }
        }

        // Try to get the cut flow table
        cutFlow = *((Table*)ifile->Get("cutFlow"));
    }

    // Write output to file. The processs are passed to obtain the canvases
    if(outputDirectory.compare(outputDirectory.size()-1,1,"/")!=0) outputDirectory+="/";
    if(!gSystem->OpenDirectory(outputDirectory.c_str())) gSystem->mkdir(outputDirectory.c_str());

    // Make/open the output file
    TFile ofile((outputDirectory+outputFilename).c_str(),"RECREATE");
    ofile.mkdir("canvases");
    ofile.mkdir("histograms");

    if(batchNumber<0) {
        // Make a copy of a subset of plots and set the y-axis to a logarithmic scale (if not in batch mode)
        vector<string> plots_to_logify = {"HT","MHT","MET","NJets","NBTags","NJets_HEMRegion"};
        logify(plots,plots_to_logify,make_pair(false,true));

        // Get the formatted canvases (if not in batch mode)
        vector<TCanvas*> canvases = getCanvases(plots, procs);

        // Write the formatted canvases to the output ROOT file (if not in batch mode)
        writeCanvasesToFiles(ofile, outputDirectory, canvases, suffix, formats);
    }

    // Write the histograms to the output ROOT file
    writeHistogramsToFile(ofile, plots);

    // Close the output file
    ofile.cd();
    cutFlow.Write();
    ofile.Close();
    if(!inputFilename.empty()) ifile->Close();
    if(!alternateDataFile.empty()) ifile_data->Close();

    if(UserFunctions::doBenchmarks) {
        cout << endl << "plotter_x::once_benchmark" << endl;
        float rt = 0, ct = 0;
        vector<string> timers = {"getPlotsForLeptonCat","getPlots","doPlotterSetup","writePlotsToFile"};
        DefaultValues::printSummary(UserFunctions::once_benchmark, 8, rt, ct, timers);
    }

    m_benchmark->Stop("plotter_x");
    cout << "plotter_x" << endl << "\tCPU time = " << m_benchmark->GetCpuTime("plotter_x") << " s" << endl
         << "\tReal time = " << m_benchmark->GetRealTime("plotter_x") << " s" << endl;
    delete m_benchmark;

    return 0;
} //main


////////////////////////////////////////////////////////////////////////////////
//  Implement Local Functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
void doPlotter(PlotFiller::MapOfPlots& plots, vector<PhysicsProcess*> procs, Table& cutFlow, int maxEvents) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("doPlotterSetup");

    PlotFiller pFill(plots, procs, cutFlow, &UserFunctions::fillPlots);
    pFill.setCutFunction(&UserFunctions::eventPassCuts);
    pFill.setWeightFunction(&UserFunctions::weightFunc);
    pFill.setProcessFunction(&UserFunctions::processFunc);
    pFill.setInitializeEventFunction(&UserFunctions::initEventFunc);
    pFill.setLimitBranches(UserFunctions::limitBranches);
    if (maxEvents>0)
        pFill.setMaximumEventsDEBUG(maxEvents);

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("doPlotterSetup");

    pFill.run();
} //doPlotter

//______________________________________________________________________________
vector<TCanvas*> getCanvases(PlotFiller::MapOfPlots & plots, vector<PhysicsProcess*> procs) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("getCanvases");

    vector<TCanvas*> canvases;
    for ( PlotFiller::MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
        for ( map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end() ; p2++) {
            vector<TCanvas*> to_merge;
            if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis)
                to_merge = ((FormattedPlot*) p2->second)->getCanvasTDR(procs);
            else
                to_merge = ((FormattedPlot*) p2->second)->getStackedCanvasTDR(procs);
            canvases.insert(canvases.end(),to_merge.begin(), to_merge.end());
        }
    }

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Stop("getCanvases");

    return canvases;
} //getCanvases

//______________________________________________________________________________
void writeCanvasesToFiles(TFile &ofile, string outputDirectory, vector<TCanvas*> canvases, string suffix, vector<string> formats) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("writeCanvasesToFile");

    // Get the canvas and write them to a TFile file and as <formats>
    cout << "Writing canvas(es) to ROOT file " << ofile.GetName() << endl;
    ofile.cd("canvases");
    for(auto can : canvases) {
        string canName = outputDirectory+"/"+can->GetName();
        canName += "_"+DEFS::getLeptonCatString(UserFunctions::leptonCat);
        cout << "\tSaving canvas " << canName << " ... ";
        can->Write();
        for (auto format : formats)
            can->SaveAs((canName+format).c_str());
        cout << "DONE" << endl << flush;
    }

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Stop("writeCanvasesToFile");
}//writeCanvasesToFile

//______________________________________________________________________________
void writeHistogramsToFile(TFile &ofile, PlotFiller::MapOfPlots & plots) {
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("writeHistogramsToFile");

    // Get the Histos and write them to file
    cout << "Writing histogram(s) to ROOT file " << ofile.GetName() << endl;
    for(PlotFiller::MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
        for(map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end() ; p2++) {
            ((FormattedPlot*) p2->second)->saveHistogramsToFile(ofile,"histograms");
        } //for histos inside plot
    } //for plots

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Stop("writeHistogramsToFile");
} //writeHistogramsToFile

//______________________________________________________________________________
PlotFiller::MapOfPlots getPlotsForCat(DEFS::LeptonCat leptonCat, bool normToData, float luminosity){
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("getPlotsForLeptonCat");

    PlotFiller::MapOfPlots plots;

    FormattedPlot* a = new FormattedPlot;

    //Goes in the label and tells us whether we are looking at electrons or muons
    string lepStr = "_"+DEFS::getLeptonCatString(leptonCat);

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
     
    string name = "";
    string title = "";

    //
    // Event quantities
    //
    title = "MET";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 1000),
                          {"E_{T}^{miss} [GeV]","Number of Events / 50 GeV"},
                          make_pair(0.,1000.));   
    plots[leptonCat][string(title)] = a;

    title = "MHT";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 1000),
                          {"H_{T}^{miss} [GeV]","Number of Events / 50 GeV"},
                          make_pair(0.,1000.));   
    plots[leptonCat][string(title)] = a;

    title = "HT";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 80, 0, 4000),
                          {"H_{T} [GeV]","Number of Events / 50 GeV"},
                          make_pair(0.,4000.));   
    plots[leptonCat][string(title)] = a;

    title = "NJets";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 20),
                          {"N_{jets}","Number of Events"},
                          make_pair(0.,20.));   
    plots[leptonCat][string(title)] = a;

    if(UserFunctions::analysisCat == DEFS::Ana::HEMAnalysis) {
        title = "NJets_HEMRegion";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 20),
                              {"N_{jets}","Number of Events"},
                              make_pair(0.,20.));   
        plots[leptonCat][string(title)] = a;

        title = "MET_HEMRegion";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 1000),
                              {"E_{T}^{miss} [GeV]","Number of Events / 50 GeV"},
                              make_pair(0.,1000.));   
        plots[leptonCat][string(title)] = a;
    }

    title = "NBTags";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 20, 0, 20),
                          {"N_{btags}","Number of Events"},
                          make_pair(0.,20.));   
    plots[leptonCat][string(title)] = a;

    //
    // Lepton quantities
    //
    title = "ElectronPt";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, 0, 1000),
                          {"p_{T}^{e}","Number of Events / 10 GeV"},
                          make_pair(0.,1000.));   
    plots[leptonCat][string(title)] = a;

    title = "ElectronEta";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, -5, 5),
                          {"#eta^{e}","Number of Events / 0.05"},
                          make_pair(-5.,5.));   
    plots[leptonCat][string(title)] = a;

    title = "ElectronPhi";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 61, -TMath::Pi(), TMath::Pi()),
                          {"#phi^{e}","Number of Events / 0.103"},
                          make_pair(-TMath::Pi(),TMath::Pi()));   
    plots[leptonCat][string(title)] = a;

    title = "ElectronEtaPhi";
    name = title+lepStr;
    a = new FormattedPlot(new TH2D(name.c_str(), title.c_str(), 100, -5, 5, 61, -TMath::Pi(), TMath::Pi()),
                          {"#eta^{e}","#phi^{e}","Ratio"}, make_pair(-5,5));   
    plots[leptonCat][string(title)] = a;

    title = "MuonPt";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, 0, 1000),
                          {"p_{T}^{#mu}","Number of Events / 10 GeV"},
                          make_pair(0.,1000.));   
    plots[leptonCat][string(title)] = a;

    title = "MuonEta";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, -5, 5),
                          {"#eta^{#mu}","Number of Events / 0.05"},
                          make_pair(-5.,5.));   
    plots[leptonCat][string(title)] = a;

    title = "MuonPhi";
    name = title+lepStr;
    a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 61, -TMath::Pi(), TMath::Pi()),
                          {"#phi^{#mu}","Number of Events / 0.103"},
                          make_pair(-TMath::Pi(),TMath::Pi()));   
    plots[leptonCat][string(title)] = a;

    //
    // Jet quantities
    //
    for (unsigned int ijet=0; ijet<10; ijet++) {
        title = UserFunctions::concatString("Jet",ijet)+"Pt";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, 0, 1000),
                              {UserFunctions::concatString("p_{T}^{jet",ijet)+"}","Number of Events / 10 GeV"},
                              make_pair(0.,1000.));   
        plots[leptonCat][string(title)] = a;

        title = UserFunctions::concatString("Jet",ijet)+"Eta";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 100, -5, 5),
                              {UserFunctions::concatString("#eta^{jet",ijet)+"}","Number of Events / 0.05"},
                              make_pair(-5.,5.));   
        plots[leptonCat][string(title)] = a;

        title = UserFunctions::concatString("Jet",ijet)+"Phi";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 61, -TMath::Pi(), TMath::Pi()),
                              {UserFunctions::concatString("#phi^{jet",ijet)+"}","Number of Events / 0.103"},
                              make_pair(-TMath::Pi(),TMath::Pi()));   
        plots[leptonCat][string(title)] = a;
    }

    for (unsigned int ijet=0; ijet<4; ijet++) {
        title = UserFunctions::concatString("Jet",ijet)+"DeltaPhi";
        name = title+lepStr;
        a = new FormattedPlot(new TH1D(name.c_str(), title.c_str(), 31, 0, TMath::Pi()),
                              {UserFunctions::concatString("#Delta#phi(jet",ijet)+",MHT)","Number of Events / 0.101"},
                              make_pair(0,TMath::Pi()));   
        plots[leptonCat][string(title)] = a;
    }

    for(auto iplot=plots[leptonCat].begin(); iplot!=plots[leptonCat].end(); iplot++) {
        dynamic_cast<FormattedPlot*>(iplot->second)->normToData = normToData;
        dynamic_cast<FormattedPlot*>(iplot->second)->stacked = false;
        dynamic_cast<FormattedPlot*>(iplot->second)->leptonCat = leptonCat;
        dynamic_cast<FormattedPlot*>(iplot->second)->jetBin = UserFunctions::jetBin;
        dynamic_cast<FormattedPlot*>(iplot->second)->tagCat = UserFunctions::tagCat;
        dynamic_cast<FormattedPlot*>(iplot->second)->controlRegion = UserFunctions::controlRegion;
        dynamic_cast<FormattedPlot*>(iplot->second)->overlaySignalName = signalName;
        dynamic_cast<FormattedPlot*>(iplot->second)->overlaySignalFactor = signalFactor;
        dynamic_cast<FormattedPlot*>(iplot->second)->luminosity = luminosity;
    }

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Stop("getPlotsForLeptonCat");

    // return all the plots to be made
    return plots;
} //getPlotsForLeptonCat


//______________________________________________________________________________
PlotFiller::MapOfPlots getPlots(DEFS::LeptonCat leptonCat, bool normToData, float luminosity){
    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Start("getPlots");

    //All plots
    PlotFiller::MapOfPlots plots;

    //Add plots based on category
    PlotFiller::MapOfPlots plots_cat = getPlotsForCat(leptonCat, normToData, luminosity);
    plots.insert(plots_cat.begin(),plots_cat.end());

    if(UserFunctions::doBenchmarks)
        UserFunctions::once_benchmark->Stop("getPlots");

    return plots;
}

//______________________________________________________________________________
void logify(PlotFiller::MapOfPlots &plots, std::vector<std::string> plots_to_logify, pair<bool,bool> logxy) {
    PlotFiller::MapOfPlots plots_to_append;
    string newTitle;
    string newName;
    FormattedPlot* aa;
    for(auto iplot=plots[UserFunctions::leptonCat].begin(); iplot!=plots[UserFunctions::leptonCat].end(); iplot++) {
        if(utilities::vfind(plots_to_logify,iplot->first)!=-1) {
            newTitle = iplot->first + ((logxy.first)?"_logx":"") + ((logxy.second)?"_logy":"");
            newName = newTitle + "_" + DEFS::getLeptonCatString(UserFunctions::leptonCat);
            aa = new FormattedPlot(*dynamic_cast<FormattedPlot*>(iplot->second));
            aa->templateHisto->SetNameTitle(newName.c_str(),newTitle.c_str());
            aa->logxy = logxy;
            plots_to_append[UserFunctions::leptonCat][newTitle] = aa;
        }
    }
    plots[UserFunctions::leptonCat].insert(plots_to_append[UserFunctions::leptonCat].begin(), plots_to_append[UserFunctions::leptonCat].end());
}

//______________________________________________________________________________
Table makePlotTable(PlotFiller::MapOfPlots& plots) {
    Table table("List of Plots");
    TableRow* tableRow;
    TableCellText* tableCellText;
    stringstream out;

    for ( PlotFiller::MapOfPlots::iterator p = plots.begin(); p != plots.end() ; p++) {
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

//______________________________________________________________________________
Table getInitializedCutTable(const vector<PhysicsProcess*> &procs) {
    vector<string> cuts;
    for (unsigned int c = 0; c<DEFS::nCutLevel; c++) {
        cuts.push_back(DEFS::getCutLevelString((DEFS::CutLevel)c));
    }
    vector<string> pnames;
    for(auto p : procs) {
        pnames.push_back(p->name);
    }
    return Table("cutFlow",cuts,pnames,"TableCellInt");
}

//______________________________________________________________________________
void printProcesses(vector <PhysicsProcess*> procs) {
   cout << "LIST OF PROCESSES:" << endl;
   for(auto p : procs) {
    cout << "\t" << p->name << endl;
   }
   cout << endl << endl << endl;
}
