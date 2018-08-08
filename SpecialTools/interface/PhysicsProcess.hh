// Name: PhysicsProcess.hh
// Author: Travis Lamb

// This class will eventually replace an older Physics class. It is a base class that simply holds data members.

#ifndef PHYSICSPROCESS_DEF
#define PHYSICSPROCESS_DEF

//ROOT libraries
#include "TEnv.h"
#include "TFile.h"
#include "TString.h"
#include "TTreeCache.h"
#include "TTree.h"
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
#include "CUAnalysis/SpecialTools/interface/StringUtilities.hh"

class PhysicsProcess
{
public:
   PhysicsProcess(){;}
   PhysicsProcess(std::string procName,
                  std::string groupingName,
                  std::string fileNameTEMP,
                  std::string treeName = "PS/EvtTree",
                  bool debug = false);

   // Retreive the list of files in the chain and possibly print them to the screen
   std::vector<std::string> getListOfFiles(bool print = false, std::string appendChar = "");

   // The given name of the process
   std::string  name;
   inline std::string getName() const {return name;}
   // The group with which you will merge it in canvases (Diboson, Single Top, etc)
   TString groupName;
   // The file path of the process
   std::string fileName;
   // The pointer to the file's TChain
   TChain* chain;
};

class PlotterPhysicsProcess: public PhysicsProcess
{
public:
   PlotterPhysicsProcess(std::string procName,
                         std::string groupingName,
                         std::string fileNameTEMP,
                         std::string treeName = "PS/EvtTree",
                         int color_ = kBlack,
                         int marker_ = kFullCircle);
   
   // the color used to draw this process
   int color;
   // the marker used to represent this process
   int marker;
};

#endif
