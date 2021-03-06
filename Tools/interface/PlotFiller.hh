#ifndef PLOTFILLER_HH
#define PLOTFILLER_HH

// Title:     PlotFiller.hh
// Author:    Travis Lamb
// Started:   22nd of June, 2012

// Uses Plot and PhysicsProcess to return a plot for a given process and yield.

// Our libraries
#include "CUAnalysis/Tools/interface/Plots.hh"
#include "CUAnalysis/SpecialTools/interface/EventNtuple.hh"
#include "CUAnalysis/SpecialTools/interface/Table.hh"
#include "CUAnalysis/SpecialTools/interface/ProgressBar.hh"

//ROOT libraries
#include "TBenchmark.h"

//C++ libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

// PlotFiller is a modular solution to extracting plots from root files.
// It allows the user to customize how he/she wants to produce the plots.
// The user can set various functions to change how the class calculates cut, weights, etc.
class PlotFiller{

public:

  typedef std::map<DEFS::LeptonCat, std::map<std::string,  Plot * > >  MapOfPlots;

   // NOTE That the user must provide the fill function at construction (because it is a required function).
   PlotFiller(MapOfPlots &plots_,
              std::vector<PhysicsProcess*> &procs_,
              Table &cutFlow_,
              void (*userFillFunc_) (MapOfPlots&, TString, EventNtuple*, double) );
   ~PlotFiller();
   
   // Simple functions to change the functionality of the code.
   void setWeightFunction(double (*userWeightFunc_) (EventNtuple*, const PhysicsProcess*));
   void setCutFunction(bool (*userCutFunc_) (EventNtuple*, const PhysicsProcess*, Table&));
   void setProcessFunction(void (*userProcessFunc_) (EventNtuple*, const PhysicsProcess*));
   void setInitializeEventFunction(void (*userInitEventFunc_) (EventNtuple*, const PhysicsProcess*));
   void setLimitBranches(DEFS::Ana::Type lb);
   
   // Debug functions
   void setMaximumEventsDEBUG(unsigned int maxEvts);
   
   // Runs the events and produces the output.
   void run();
   
private:
   // NOTE That the plots and processes are references.
   MapOfPlots &plots;
   std::vector<PhysicsProcess*> &processes;
   Table &cutFlow;
   unsigned int numberOfEvents;
   unsigned int debugNumberOfEvents;
   bool debug;
   DEFS::Ana::Type limitBranches;
   TBenchmark* sample_benchmark;
   TBenchmark* event_benchmark;
   TBenchmark* func_benchmark;

   // These are the custom functions.
   // Fills the plots
   void (*userFillFunc) (MapOfPlots &, TString, EventNtuple*, double);
   // Returns a double that will multiply the weight
   double (*userWeightFunc) (EventNtuple*, const PhysicsProcess*);
   // Returns true if the event passes the cut
   bool (*userCutFunc) (EventNtuple*, const PhysicsProcess*, Table&);
   // This function is called once for each process before the events are run
   void (*userProcessFunc) (EventNtuple*, const PhysicsProcess*);
   // This function is called once for each event before any cuts are made
   void (*userInitEventFunc) (EventNtuple*, const PhysicsProcess*);
   
   // These default functions allow the user to only have to create functions for weights etc that he/she wants to add.
   static bool defaultCutFunc(EventNtuple*, const PhysicsProcess*, Table&)
   {
      return true;
   }
   static double defaultWeightFunc(EventNtuple*, const PhysicsProcess*)
   {
      return 1.0;
   }
   static void defaultProcessFunc (EventNtuple*, const PhysicsProcess*)
   {
      return;
   }
   static void defaultInitEventFunc (EventNtuple*, const PhysicsProcess*)
   {
      return;
   }
};

#endif
