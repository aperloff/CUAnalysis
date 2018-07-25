// Name: PhysicsProcess.hh
// Author: Travis Lamb

// This class will eventually replace an older Physics class. It is a base class that simply holds data members.

#ifndef PHYSICSPROCESS_DEF
#define PHYSICSPROCESS_DEF

//ROOT libraries
#include "TFile.h"
#include "TString.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TObjArray.h"

//STD libraries
#include <iostream>
#include <utility>
#include <sstream>

//CMSSW libraries
#include "../XrdVersion.hh"
#if __has_include("../XrdCl/XrdClFileSystem.hh")
#include "../XrdCl/XrdClFileSystem.hh"
#define has_xrdcl 1
#else
#define has_xrdcl 0
#endif

//This package
#include "CUAnalysis/SpecialTools/interface/Defs.hh"

using namespace std;

typedef map<DEFS::LeptonCat,double> PhysParMap;
typedef map<DEFS::LeptonCat,unsigned int> PhysParMapUI;

class PhysicsProcess
{
public:
   PhysicsProcess(){;}
   PhysicsProcess(std::string procName,
                  std::string groupingName,
                  std::string fileNameTEMP,
                  std::string treeName = "PS/EvtTree",
                  bool debug = false);

   double getScaleFactor(DEFS::LeptonCat lepCat) {
     return sigma[lepCat]*intLum[lepCat]*scaleFactor[lepCat] * branching_ratio[lepCat] / initial_events[lepCat];
   }
   void setPhysicsParameters(PhysParMap cross_section, PhysParMap lum, PhysParMap br, PhysParMapUI in_ev, PhysParMap sf);

   // The main function that checks if two given strings match. The first string may contain wildcard characters.
   bool match(const char *first, const char * second);

   // Retreive the list of files in the chain and possibly print them to the screen
   vector<string> getListOfFiles(bool print = false, string appendChar = "");

   // The given name of the process
   TString  name;
   inline TString getName() const {return name;}
   // The group with which you will merge it in canvases (Diboson, Single Top, etc)
   TString groupName;
   // The file path of the process
   string fileName;
   // The pointer to the file's TChain
   TChain* chain;
   // The production cross section
   PhysParMap sigma;
   // The branching ratio
   PhysParMap branching_ratio;
   // The integrated luminosity to which to normalize
   PhysParMap  intLum;
   // The initial number of events in the MC sample
   PhysParMapUI initial_events;
   // A scale factor which can be applied to any process for any purpose (i.e. QCD/WJets scaling)
   PhysParMap scaleFactor;
};

class PlotterPhysicsProcess: public PhysicsProcess
{
public:
   PlotterPhysicsProcess(std::string procName,
                         std::string groupingName,
                         std::string fileNameTEMP,
                         int col,
                         std::string treeName = "PS/EvtTree");
   
   // the color used to draw this process
   int color;

};

#endif
