#ifndef DEFS_DEF
#define DEFS_DEF

//ROOT libraries
#include "TROOT.h"
#include "TSystem.h"
#include "TAttMarker.h"
#include "TString.h"

//C++ libraries
#include <iostream>
#include <string>
#include <map>
#include <vector>

// This namespace holds the definitions of all physics processes 
// author: Ricardo Eusebi, Feb 12, 2009
// modified: Osipenkov, Ilya

namespace DEFS{

  // ---------------------------------------------------------------
  //            ALL ABOUT THE ANALYSIS WE WANT TO DO 
  // ---------------------------------------------------------------  
  namespace Ana {
    enum Type{
      RA2bAnalysis,
      HEMAnalysis,
      UNKNOWN
    };
  
    // A routine that returns the string given the type 
    std::string getTypeString(Type);
 
     // A routine that returns the type given a string
    Type getAnaType(std::string str);

  }// Ana namespace
  
  // ---------------------------------------------------------------
  //            ALL ABOUT THE PHYSICSPROCESS TYPES
  // ---------------------------------------------------------------
  namespace PhysicsProcess {
    enum Type {Data_EGamma, Data_JetHT, Data_MET, Data_SingleMuon,
               Data_HEMiss_EGamma, Data_HEMiss_JetHT, Data_HEMiss_MET, Data_HEMiss_SingleMuon,
               RelVal_QCD_FlatPt_15_3000HS, RelVal_QCD_Pt_600_800, RelVal_QCD_Pt_80_120, RelVal_SMS_T1tttt_mGl1500_mLSP100, RelVal_TTbar,
               RelValHEMiss_QCD_FlatPt_15_3000HS, RelValHEMiss_QCD_Pt_600_800, RelValHEMiss_QCD_Pt_80_120, RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100, RelValHEMiss_TTbar,
               UNKNOWN};

    // A routine that returns the type given a string 
    Type getProcessType(std::string str);///
    
    // A routine that returns the type given a string 
    std::string getTypeString(Type );

    // A routine that returns the title for a given process type
    std::string getTypeTitle(Type type);

    // A routine that returns the Color_t for a given process type
    Color_t getProcessColor(Type type);

    // A routine the returns the Marker_t for a given process type
    Marker_t getProcessMarker(Type type);
    
  }// PhysicsProcess namespace
  typedef DEFS::PhysicsProcess::Type PhysicsProcessType ;

  // ---------------------------------------------------------------
  //            ALL ABOUT THE DIFFERENT EVENT CATEGORIES
  // ---------------------------------------------------------------
  // Under no condition set the value of the category, otherwise nLeptonCat 
  // will not be working on some classes like PhysicsProcessForOpt
  // In addition, make sure that all the categories that data/MC has are here
  enum LeptonCat {none, muon, electron, both};
  static const unsigned int nLeptonCat = 4;

  // A routine that returns the string given the LeptonCat 
  std::string getLeptonCatString(LeptonCat );

  // for historical reasons
  std::string getEventCatString(LeptonCat a);

  // A routine that returns the LeptonCat given the string
  LeptonCat getLeptonCat(std::string type);

  enum LeptonBin {leptons0, lepton1, leptons2};
  static const unsigned int nLeptonBins = 3;

  // A routine that returns the string given the LeptonCat 
  std::string getLeptonBinString(LeptonBin);

  // A routine that returns the LeptonCat given the string
  LeptonBin getLeptonBin(std::string str);

  // A routine that returns a leptonBin given an integer number of leptons
  LeptonBin getLeptonBin(int nLeptons, LeptonBin inclusive_bin = leptons2);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE JET TYPES
  // ---------------------------------------------------------------
  enum JetBin {jets0, jet1, jets2, jets3, jets4, jets5, jets6, jets7, jets8, jets9};
  
  // for historical reasons
  static const unsigned int NJETS = 9;

  // A routine that returns a string given the type
  std::string getJetBinString(JetBin type);

  // A routine that returns a label given the type
  std::string getJetBinLabel(JetBin type);

  // A routine that returns a JetBin given
  JetBin getJetBin(std::string str);

  // A routine that returns a jetBin given an integer number of jets
  JetBin getJetBin(int nJets, JetBin inclusive_bin = jets9);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE TAGGING CATEGORIES
  // ---------------------------------------------------------------

  // The tagging categories per event
  // TSV = tight SecVtx
  // JP5 = JP < 5%
  enum TagCat {

    pretag,   // The pretag category
    eq0tag,   // Exactly zero SVX tags, i.e. the untag category.
    eq1tag,   // Exactly one SVX tag 
    eq2tag,   // Exactly two SVX tags 
    ge0tag,   // Greater equal than 0 SVX tags 
    ge1tag,   // Greater equal than 1 SVX tag 
    ge2tag,   // Greater equal than 2 SVX tags 

    // For the tagging with JP in descendant exclusive orthogonal category
    TSVTSV,   // for some reason this is not exactly equal to eq2TSV
    TSVJP5,   // one jet with a tight SVX tag and the other one with a loose JP tag which is not a tight SVX
    TSVNOJP5, // one jet with a tight SVX tag and the other one without a loose JP or tight SVX tag.
    JP5NOTSV // one jet with a Loose SVT tag and neither jet is a tight SVX tag.
   

    // For the tagging with Loose in descendant exclusive orthogonal category
    // TSVTSV  //  for some reason this is not exaclty equal to eq2TSV
    ///TSVLSV,    // one jet with a tight SVX tag and the other one with a loose SecVTx tag which is not a tight SVX
    //TSVNOLSV,  // one jet with a tight SVX tag and the other one without a loose SVX tag.   
    //LSVNOTSV   // one jet with a Loose SVT tag and neither jet is a tight SVX tag.

    // In principle we can have four choices, each with 4 exclusive categories in which in a 
    // given column a given line is always orthogonal to all lines above:
    //       | CHOICE A    | CHOICE B  |  CHOICE C | CHOICE D
    // cat 0 | TSVTSV      | TSVTSV    | TSVTSV    | TSVTSV   
    // cat 1 | TSVJP5      | TSVLSV    | TSVJP5    | TSVLSV   
    // cat 2 | TSVNOJP5    | TSVNOLSV  | TSVNOJP5  | TSVNOLSV 
    // cat 3 | JP5NOTSV    | LSVNOTSV  | LSVNOTSV  | JP5NOTSV    
    
  };

  // A routine that returns a string given the type
  std::string getTagCatString(TagCat type);

  // A routine that returns a label given the type
  std::string getTagCatLabel(TagCat type);

  // A routine that returns a jetBin given a string
  TagCat getTagCat(std::string str);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE CUT LEVELS
  // ---------------------------------------------------------------

  enum CutLevel {NtupleLevel, cut0, cut1, cut2, cut3, cut4, cut5, cut6, cut7, cut8, cut9};
  static const unsigned int nCutLevel = 4;

  // A routine that returns a string given the type
  std::string getCutLevelString(CutLevel type);

  // A routine that returns a CutLevel given a string
  CutLevel getCutLevel(std::string str);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE CONTROL REGIONS
  // ---------------------------------------------------------------

  enum ControlRegion {all, signal, control0, control1, control2, control3, control4, control5, control6, control7, control8, control9, None};
  static const unsigned int nControlRegion = 13;

  //A routine that returns a string given the type
  std::string getControlRegionString(ControlRegion type);

  // A routine that returns a CutLevel given a string
  ControlRegion getControlRegion(std::string str);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE NTUPLE TYPES
  // ---------------------------------------------------------------
   enum NtupleType {EventNtuple, Other};
   static const unsigned int nNtupleType = 2;
   
   // A routine that returns a string given the type
   std::string getNtupleTypeString(NtupleType type);
   
   // A routine that returns a NtupleType given a string
   NtupleType getNtupleType(std::string str);
   
   std::string getTreeName(NtupleType type, JetBin nJets = jets2);

  // ---------------------------------------------------------------
  //            ALL ABOUT THE UNIVERSITY
  // ---------------------------------------------------------------
   enum University {CUBoulder, Combined, OtherUniversity};
   static const unsigned int nUniversity = 3;

   // A routine that returns a string given the University
   std::string getUniversityString(University univ);

   // A routine that returns a University given a string
   University getUniversity(std::string str);

  // ---------------------------------------------------------------
  //            ALL ABOUT PDG ID Codes
  // ---------------------------------------------------------------
   enum PdgId {
     /// Special wildcard particle name
     ANY = 10000, 
     /// @name Charged leptons
     ELECTRON = 11, POSITRON = -ELECTRON, EMINUS = ELECTRON, EPLUS = POSITRON, MUON = 13, ANTIMUON = -MUON, TAU = 15, ANTITAU = -TAU,
     /// @name Neutrinos
     NU_E = 12, NU_EBAR = -NU_E, NU_MU = 14, NU_MUBAR = -NU_MU, NU_TAU = 16, NU_TAUBAR = -NU_TAU, 
     /// @name Bosons
     PHOTON = 22, GAMMA = PHOTON, GLUON = 21, WPLUSBOSON = 24, WMINUSBOSON = -WPLUSBOSON, WPLUS = WPLUSBOSON, WMINUS = WMINUSBOSON, Z0BOSON = 23, ZBOSON = Z0BOSON, Z0 = Z0BOSON, HIGGSBOSON = 25, HIGGS = HIGGSBOSON, 
     /// @name Quarks
     DQUARK = 1, UQUARK = 2, SQUARK = 3, CQUARK = 4, BQUARK = 5, TQUARK = 6, ANTIDQUARK = -DQUARK, ANTIUQUARK = -UQUARK, ANTISQUARK = -SQUARK, ANTICQUARK = -CQUARK, ANTIBQUARK = -BQUARK, ANTITQUARK = -TQUARK, d = DQUARK, u = UQUARK, s = SQUARK, c = CQUARK, b = BQUARK, t = TQUARK, dbar = -d, ubar = -u, sbar = -s, cbar = -c, bbar = -b, tbar = -t, 
     /// @name Nucleons
     PROTON = 2212, ANTIPROTON = -PROTON, PBAR = ANTIPROTON, NEUTRON = 2112, ANTINEUTRON = -NEUTRON, 
     /// @name Light mesons
     PI0 = 111, PIPLUS = 211, PIMINUS = -PIPLUS, K0L = 130, K0S = 310, KPLUS = 321, KMINUS = -KPLUS, ETA = 221, ETAPRIME = 331, PHI = 333, OMEGA = 223, 
     /// @name Charmonia
     ETAC = 441, JPSI = 443, PSI2S = 100443, 
     /// @name Charm mesons
     D0 = 421, DPLUS = 411, DMINUS = -DPLUS, DSPLUS = 431, DSMINUS = -DSPLUS, 
     /// @name Bottomonia
     ETAB = 551, UPSILON1S = 553, UPSILON2S = 100553, UPSILON3S = 200553, UPSILON4S = 300553, 
     /// @name b mesons
     B0 = 511, BPLUS = 521, BMINUS = -BPLUS, B0S = 531, BCPLUS = 541, BCMINUS = -BCPLUS, 
     /// @name Baryons
     LAMBDA = 3122, SIGMA0 = 3212, SIGMAPLUS = 3222, SIGMAMINUS = 3112, LAMBDACPLUS = 4122, LAMBDACMINUS = 4122, LAMBDAB = 5122, XI0 = 3322, XIMINUS = 3312, XIPLUS = -XIMINUS, OMEGAMINUS = 3334, OMEGAPLUS = -OMEGAMINUS, 
     /// @name Exotic/weird stuff
     REGGEON = 110, POMERON = 990, ODDERON = 9990, GRAVITON = 39, NEUTRALINO1 = 1000022, GRAVITINO = 1000039, GLUINO = 1000021
     /// @todo Add axion, black hole remnant, etc. on demand
   };
   static const unsigned int nPdgId = 105;

   /// Return a PdgId as a named string
   std::string toParticleName(PdgId p);

   /// Return a name as a PdgId
   PdgId toParticleId(const std::string pname);

   /// Return a PdgId from an int
   PdgId getParticleIdFromInt(int p);

}

#endif

