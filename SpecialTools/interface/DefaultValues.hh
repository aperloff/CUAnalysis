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

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

class DefaultValues{

public:

   // Returns the path to the config files
   // basically returns $CMSSW_BASE+"/src/CUAnalysis/Config/Official/"
   static std::string getConfigPath();
  
   static std::string getBDTLocation(DEFS::JetBin jetBin, DEFS::TagCat tagcat, DEFS::University univ, bool filenameOnly = false);

   static std::string getWeightForCategory(DEFS::TagCat tagcat,  
                                           DEFS::PhysicsProcessType, int );

   // Return a table with normalization of process for the given tag category
   static Table getNormTable(DEFS::LeptonCat evtcat, DEFS::TagCat tagcat);

   // Return a table with location of files for the given tag category
   static Table getFileLocationTable(DEFS::TagCat tagcat);

   // Return a vector of PhysicsProcess's for the requested processName's
   // Each PhysicsProces has norm obtained from getNormTable, and 
   // ntuples chained from files in getFileLocationTable
   // Calls the getSingleProcess recursively
   static std::vector < PhysicsProcess * > getProcesses(std::vector<DEFS::PhysicsProcessType> processName,
                                                        DEFS::JetBin jetBin, 
                                                        DEFS::TagCat tagcat,
                                                        bool for_plots,
                                                        DEFS::NtupleType ntuple_type);

   
   // Return a single PhysicsProces with norm obtained from normTable, and 
   // ntuples chained from files in fileTable
   static PhysicsProcess * getSingleProcess(DEFS::PhysicsProcessType process,
                                            DEFS::JetBin jetBin,
                                            std::map<DEFS::LeptonCat,Table> normTable,
                                            Table fileTable,
                                            bool for_plots,
                                            DEFS::NtupleType ntuple_type);



  
   //GIVE THE OFFICIAL LIST OF PROCESSES FOR THE GIVEN ANALYSIS
   // DON'T MESS WITH THIS METHOD, CREATE ANOTHER ONE FOR TEST PURPOSES
   static std::vector < PhysicsProcess * > getProcessesHEM(DEFS::JetBin,
                                                           DEFS::TagCat,
                                                           bool include_data,
                                                           bool forPlots,
                                                           DEFS::NtupleType ntuple_type);

   static std::vector < PhysicsProcess * > getProcessesRA2b(DEFS::JetBin,
                                                            DEFS::TagCat,
                                                            bool include_data,
                                                            bool include_systematics,
                                                            bool forPlots,
                                                            DEFS::NtupleType ntuple_type,
                                                            DEFS::LeptonCat lepton = DEFS::both);

   // Returns the luminosity for a given dataset
   static double getLuminosity(TString channelName);
   
   // Returns the cross section for the given process
   static pair<double,double> getCrossSectionAndError(TString channelName);
   
   // Returns the branching ratio for the given process
   static double getBranchingRatio(TString channelName);
   
   // Returns the number of Monte Carlo events for the given process
   static double getNumMCEvts(TString channelName);

   // Returns the scale factor for the given process
   static double getScaleFactor(TString channelName);
   static double getScaleFactor(TString channelName, DEFS::LeptonCat leptonCat);

   // Returns the maximum tEventProb for a given ME found in that MEs matching 
   // MC sample (i.e. the WW ME in the WW MC sample).
   //This is not a unique identifier. It will mix up STopT and STopS in STopT_T/STopT_Tbar and STopS_T/STopS_Tbar respectively.
   //Takes the highest value.
   static pair<double,double> getMaxEventProbAndError(int probStatIndex, Table* inputTable = 0);
   //Not unique. Will mix up WLg and WLgSub. Takes the highest value.
   static pair<double,double> getMaxEventProbAndError(DEFS::PhysicsProcessType ppType, string meType, Table* inputTable = 0);
   //Alias for the previous member function so it can be used in CINT
   static pair<double,double> getMaxEventProbAndError(string ppType, string meType, Table* inputTable = 0);
   //Not unique. Will mix up WLg/WLgSub from WJets, STopT from STopT_T and STopT_Tbar, and STopS from STopS_T and STopS_Tbar.
   //Takes the highest value.
   static pair<double,double> getMaxEventProbAndError(string meType, Table* inputTable = 0);

   // Returns the median BDT value for a given jet bin and lepton category
   static pair<double,double> getMedianPurity(DEFS::JetBin jetBin, DEFS::LeptonCat leptonCat, string BDTType, Table* inputTable = 0);

   // Sets two vectors with the variables and spectators for a given MVA training
   static void getMVAVar(TString filename, vector<TString>& MVAV, vector<TString>& MVAS);

   // Returns the index of the location of b within a, or -1 if b is not found in a
   static int vfind(vector<string> a, string b);
   static int vfind(vector<TString> a, TString b);
   static vector<int> vfind_many(vector<string> find_in, vector<string> to_find, bool debug = false);

   // templated version of my_equal so it could work with both char and wchar_t
   template<typename charT>
   struct my_equal {
       my_equal( const std::locale& loc ) : loc_(loc) {}
       bool operator()(charT ch1, charT ch2) {
           return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
       }
   private:
       const std::locale& loc_;
   };
   
   // find substring (case insensitive)
   template<typename T>
   static int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
   {
       typename T::const_iterator it = std::search( str1.begin(), str1.end(), 
           str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
       if ( it != str1.end() ) return it - str1.begin();
       else return -1; // not found
   }

   // Remove a substring p from a given string s
   template<typename T>
   void removeSubstrs(std::basic_string<T>& s, const std::basic_string<T>& p);

   // Destroy all open canvases
   static void DestroyCanvases();

   // Returns an object from any ROOT file in CUAnalysis/ConfigFiles/Official/
   static TObject* getConfigTObject(TString histoFile, TString hname, TString newName);
   static TH1* getConfigTH1(TString histoFile, TString hname, TString newName);
   static TH2* getConfigTH2(TString histoFile, TString hname, TString newName);

   // Returns a rebinned TH2 object
   // There is still a problem with rebinning the underflow and overflow bins
   // Everything else works though
   TH2* Rebin2D(TH2* old, Int_t nxgroup, Int_t nygroup, const char*newname, const Double_t *xbins, const Double_t *ybins, TString Options = "");

   // Tests the Rebin2D function
   void Rebin2DTest(TString Options = "");

   //prints a TBenchmark summary with variable precision and a list of timers
   static void printSummary(TBenchmark* bench, int precision, Float_t &rt, Float_t &ct, vector<string> timers);

};
 
#endif
