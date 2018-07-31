
// Title:     PlotFiller.cc
// Author:    Travis Lamb
// Started:   22nd of June, 2012
// Last Edit: 22nd of June, 2012

// Uses Plot and PhysicsProcess to return a plot for a given process and yield.

// Our libraries
#include "CUAnalysis/Tools/interface/PlotFiller.hh"

using namespace std;

//#####################################################################
//#####################################################################
//#####################################################################

PlotFiller::PlotFiller(MapOfPlots &plots_,
                       vector<PhysicsProcess*> &procs_,
                       Table &cutFlow_,
                       void (*userFillFunc_) (MapOfPlots &, TString, EventNtuple*, double)):
   plots(plots_),
   processes(procs_),
   cutFlow(cutFlow_),
   userFillFunc(userFillFunc_)
{
   userWeightFunc = &defaultWeightFunc;
   userCutFunc = &defaultCutFunc;
   userProcessFunc = &defaultProcessFunc;
   userInitEventFunc = &defaultInitEventFunc;
   
   numberOfEvents = 0;
   
   debug = false;

   sample_benchmark = new TBenchmark();
   sample_benchmark->Reset();
   event_benchmark = new TBenchmark();
   event_benchmark->Reset();
   func_benchmark = new TBenchmark();
   func_benchmark->Reset();
}

PlotFiller::~PlotFiller() {
   delete sample_benchmark;
   delete event_benchmark;
   delete func_benchmark;
}

void PlotFiller::setWeightFunction(double (*userWeightFunc_) (EventNtuple*, const PhysicsProcess*)) {
   userWeightFunc = userWeightFunc_;
}

void PlotFiller::setCutFunction(bool (*userCutFunc_) (EventNtuple*, const PhysicsProcess*, Table&)) {
   userCutFunc = userCutFunc_;
}

void PlotFiller::setProcessFunction(void (*userProcessFunc_) (EventNtuple*, const PhysicsProcess*)) {
   userProcessFunc = userProcessFunc_;
}

void PlotFiller::setInitializeEventFunction(void (*userInitEventFunc_) (EventNtuple*, const PhysicsProcess*)) {
   userInitEventFunc = userInitEventFunc_;
}

void PlotFiller::setMaximumEventsDEBUG(unsigned int maxEvts) {
   debugNumberOfEvents = maxEvts;
   debug = true;
}

void PlotFiller::setLimitBranches(int lb) {
   limitBranches = lb;
}

void PlotFiller::run() {
   cout << "PlotFiller::run Begin filling plots" << endl;
   for(unsigned int i = 0; i < processes.size(); i++) {
      cout << "\n\e[1mDoing PhysicsProcess \e[4m" << processes[i]->name << "\e[24m\e[21m" << endl;
      //cout << "\tFrom file " << processes[i]->fileName << endl;
      processes[i]->getListOfFiles(true,"\t");
      // Tell all plots to prepare for filling 
      for (MapOfPlots::iterator p = plots.begin() ; p != plots.end() ; p++) {
         TString suffix = "_"+processes[i]->name + "_" + DEFS::getLeptonCatString(p->first);
         for (map<string,  Plot * >::iterator p2 = p->second.begin(); p2 != p->second.end(); p2++)
            p2->second->prepareToFillProcess(suffix, processes[i]->groupName);
      }//for 
      
      // Create the eventNtuple
      EventNtuple * ntuple = 0;
      TChain * c = processes[i]->chain;
      // Try to speed up processing
      //c->SetCacheSize(10000000);
      //c->AddBranchToCache("*");
      
      if(limitBranches > 0 ) {
         cout << "\tPlotFiller::run Normally we'd be turning off some branches here. Not today!" << endl;
      }

      // Check some test branch
      if (c->GetBranch("RunNum")) {
         ntuple = new EventNtuple(c, (DefaultValues::ci_find_substr(processes[i]->name,string("data"))!=-1) ? false : true);
         //c->SetBranchAddress("EvtTree",&ntuple);
      }
      else {
	      cout << "\tPlotFiller::run TreeMaker2/PreSelection/RunNum branch not found." << endl
	           << "\tSetting EventNtuple pointer to 0x0." << endl;
      }

      // The counter for how many events pass the cuts in each process
      unsigned int numProcEvts = 0;
      double sumW = 0;
   
      // Define the weight variable and set the default as 1.0
      double weight = 1.0;

      // Loop over events in the process
      if(debug && debugNumberOfEvents < c->GetEntries()) {
         numberOfEvents = debugNumberOfEvents;
      }
      else {
         numberOfEvents = c->GetEntries();
      }
      *(cutFlow(DEFS::getCutLevelString((DEFS::CutLevel)0),processes[i]->name)) = Value(numberOfEvents,0.0);
      cout << "\tProcessing " << numberOfEvents << " events (out of " << c->GetEntries() << ")." << endl;
      
      // This runs once for each process before the events are run.
      userProcessFunc(ntuple, processes[i]);

      for (unsigned int ev = 0 ; ev < numberOfEvents ; ev++) {
         //if debug, time the event
         if(debug && numberOfEvents<100) {
            event_benchmark->Start("event");
            func_benchmark->Start("GetEntry");
         }

         // Report every now and then
         if(ev==0) sample_benchmark->Start("sample");
         if(ev==numberOfEvents-1) sample_benchmark->Stop("sample");
         ProgressBar::loadbar(ev+1,numberOfEvents,50,"PlotFiller Progress:",
                              (ev==numberOfEvents-1) ? make_pair((float)sample_benchmark->GetCpuTime("sample"),
                                                                 (float)sample_benchmark->GetRealTime("sample"))
                                                     : make_pair(float(0.0),float(0.0)));
         if(ev==numberOfEvents-1) sample_benchmark->Reset();
         
         // Get the given entry
         c->GetEntry(ev);

         if(debug && numberOfEvents<100)
            func_benchmark->Stop("GetEntry");

         // Runs before any cuts are made
         userInitEventFunc(ntuple, processes[i]);
         
         // Cut events here
         if(!userCutFunc(ntuple, processes[i], cutFlow))
            continue;
         
         // reset the weight for each event, so the default will be 1.0
         weight = 1.0;
         weight *= userWeightFunc(ntuple, processes[i]);
         
         // Fill plots
         //cout << "Entry = " << ev << endl; 
         userFillFunc(plots, processes[i]->name, ntuple, weight);
         
         // Keep track of the total number of events & weights passing the cuts 
         sumW += weight;
         numProcEvts++;

         if(debug && numberOfEvents<100) {
            event_benchmark->Stop("event");
            float rt = 0, ct = 0;
            cout << endl << "PlotFiller::event_benchmark" << endl;
            vector<string> timers(1,"event");
            DefaultValues::printSummary(event_benchmark, 8, rt, ct, timers);
            event_benchmark->Reset();

            cout << endl << "PlotFiller::func_benchmark" << endl;
            vector<string> timers2(1,"GetEntry");
            DefaultValues::printSummary(func_benchmark, 8, rt, ct, timers2);
            func_benchmark->Reset();
         }
      }
      
      cout << endl << "Number of " << processes[i]->name << " events passing the cuts: " << numProcEvts << " (weighted: " << sumW << ")" << endl;
   }
   cout << "\nPlotFiller::run DONE" << endl;
}
