#ifndef DefaultValues_HH
#define DefaultValues_HH

//ROOT libraries
#include "TROOT.h"
#include "TSystem.h"
#include "TError.h"
#include "TMath.h"
#include "TBenchmark.h"
#include "TList.h"
#include "TString.h"
#include "TObject.h"
#include "TH1.h"
#include "TH2.h"

//C++ libraries
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <assert.h>
#include <sstream>

//Our libraries
#include "CUAnalysis/SpecialTools/interface/Defs.hh"
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/SpecialTools/interface/Table.hh"
#include "CUAnalysis/SpecialTools/interface/TableRow.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellVal.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellInt.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellText.hh"
#include "CUAnalysis/SpecialTools/interface/PhysicsProcess.hh"
#include "CUAnalysis/SpecialTools/interface/FileLocationTable.hh"

namespace DefaultValues {
    // Returns the path to the config files
    // basically returns $CMSSW_BASE+"/src/CUAnalysis/Config/Official/"
    std::string getConfigPath(DEFS::Ana::Type analysis);

    // Return a table with location of files for the given tag category
    Table getFileLocationTable(DEFS::TagCat tagcat, DEFS::Ana::Type analysis);

    // Return a vector of PhysicsProcess's for the requested processName's
    // Each PhysicsProces has norm obtained from getNormTable, and 
    // ntuples chained from files in getFileLocationTable
    // Calls the getSingleProcess recursively
    std::vector < PhysicsProcess * > getProcesses(std::vector<DEFS::PhysicsProcessType> processName,
                                                  DEFS::JetBin jetBin, 
                                                  DEFS::TagCat tagcat,
                                                  bool for_plots,
                                                  DEFS::NtupleType ntuple_type,
                                                  DEFS::Ana::Type analysis);

   
    // Return a single PhysicsProces with norm obtained from normTable, and 
    // ntuples chained from files in fileTable
    PhysicsProcess * getSingleProcess(DEFS::PhysicsProcessType process,
                                      DEFS::JetBin jetBin,
                                      Table fileTable,
                                      bool for_plots,
                                      DEFS::NtupleType ntuple_type);



  
    //GIVE THE OFFICIAL LIST OF PROCESSES FOR THE GIVEN ANALYSIS
    // DON'T MESS WITH THIS METHOD, CREATE ANOTHER ONE FOR TEST PURPOSES
    std::vector < PhysicsProcess * > getProcessesHEM(DEFS::JetBin,
                                                     DEFS::TagCat,
                                                     bool includeData,
                                                     bool forPlots,
                                                     DEFS::NtupleType ntupleType);

    std::vector < PhysicsProcess * > getProcessesDataComparison(DEFS::JetBin,
                                                                DEFS::TagCat,
                                                                bool includeData,
                                                                bool forPlots,
                                                                DEFS::NtupleType ntupleType);

    std::vector < PhysicsProcess * > getProcessesRA2b(DEFS::JetBin,
                                                      DEFS::TagCat,
                                                      bool includeData,
                                                      bool includeSystematics,
                                                      bool forPlots,
                                                      DEFS::NtupleType ntupleType);

    std::vector < PhysicsProcess * > getProcessesGenMET(DEFS::JetBin,
                                                        DEFS::TagCat,
                                                        bool includeData,
                                                        bool includeSystematics,
                                                        bool forPlots,
                                                        DEFS::NtupleType ntupleType);

    std::vector < PhysicsProcess * > getProcessesPhotonFragmentation(DEFS::JetBin,
                                                                     DEFS::TagCat,
                                                                     bool includeData,
                                                                     bool includeSystematics,
                                                                     bool forPlots,
                                                                     DEFS::NtupleType ntupleType);

    // Returns the luminosity for a given dataset
    double getLuminosity(TString channelName);

    // Returns the cross section for the given process
    std::pair<double,double> getCrossSectionAndError(DEFS::Ana::Type analysis, TString channelName);

    // Destroy all open canvases
    void DestroyCanvases();

    // Returns an object from any ROOT file in CUAnalysis/ConfigFiles/Official/
    template<class T>
    T getConfigObject(std::string filename, std::string objectName, std::string newName, DEFS::Ana::Type analysis);

    // Returns a rebinned TH2 object
    // There is still a problem with rebinning the underflow and overflow bins
    // Everything else works though
    TH2* Rebin2D(TH2* old, Int_t nxgroup, Int_t nygroup, const char*newname, const Double_t *xbins, const Double_t *ybins, TString Options = "");

    // Tests the Rebin2D function
    void Rebin2DTest(TString Options = "");

    //prints a TBenchmark summary with variable precision and a list of timers
    void printSummary(TBenchmark* bench, int precision, Float_t &rt, Float_t &ct, std::vector<std::string> timers);

};
 
#endif
