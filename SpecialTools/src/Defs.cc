#include "CUAnalysis/SpecialTools/interface/Defs.hh"

namespace DEFS {

  using std::cout;
  using std::endl;
  using std::string;
  using std::map;
  using std::vector;
  
  namespace Ana{

    //---------------------------------------------------------------------------
    // A routine that returns the type given a string 
    string getTypeString(Type type){
      
      //the returning string
      if      (type == RA2bAnalysis)        return "RA2/b Analysis";
      else if (type == HEMAnalysis)         return "HEM 15/16 Analysis";
      else if (type == DataComparison)      return "DataComparison";
      else if (type == PhotonFragmentation) return "PhotonFragmentation";
      else if (type == UNKNOWN)             return "UNKNOWN Analysis";

      cout<<"ERROR DEFS::getProcessTypeString AnalysisType "<<type<<" is unknown"<<endl;   
      
      return "";
      
    }//getAnalysisTypeString

    Type getAnaType(std::string str) {
       if     (str == "RA2bAnalysis")        return DEFS::Ana::RA2bAnalysis;
       else if(str == "HEMAnalysis")         return DEFS::Ana::HEMAnalysis;
       else if(str == "DataComparison")      return DEFS::Ana::DataComparison;
       else if(str == "PhotonFragmentation") return DEFS::Ana::PhotonFragmentation;
       else if(str == "UNKNOWN")             return DEFS::Ana::UNKNOWN;

       cout<<" ERROR  DEFS::getAnaType str ="<<str<<" not found"<<endl;

       return  DEFS::Ana::UNKNOWN;
    }//getAnaType
    
  }// namespace

  namespace PhysicsProcess {

    //---------------------------------------------------------------------------
    DEFS::PhysicsProcessType getProcessType(std::string str){

      if     (str == "Data_EGamma")                               return DEFS::PhysicsProcess::Data_EGamma;
      else if(str == "Data_JetHT")                                return DEFS::PhysicsProcess::Data_JetHT;
      else if(str == "Data_MET")                                  return DEFS::PhysicsProcess::Data_MET;
      else if(str == "Data_SingleMuon")                           return DEFS::PhysicsProcess::Data_SingleMuon;
      else if(str == "Data_HEMiss_EGamma")                        return DEFS::PhysicsProcess::Data_HEMiss_EGamma;
      else if(str == "Data_HEMiss_JetHT")                         return DEFS::PhysicsProcess::Data_HEMiss_JetHT;
      else if(str == "Data_HEMiss_MET")                           return DEFS::PhysicsProcess::Data_HEMiss_MET;
      else if(str == "Data_HEMiss_SingleMuon")                    return DEFS::PhysicsProcess::Data_HEMiss_SingleMuon;
      else if(str == "RelVal_QCD_FlatPt_15_3000HS")               return DEFS::PhysicsProcess::RelVal_QCD_FlatPt_15_3000HS;
      else if(str == "RelVal_QCD_Pt_600_800")                     return DEFS::PhysicsProcess::RelVal_QCD_Pt_600_800;
      else if(str == "RelVal_QCD_Pt_80_120")                      return DEFS::PhysicsProcess::RelVal_QCD_Pt_80_120;
      else if(str == "RelVal_SMS_T1tttt_mGl1500_mLSP100")         return DEFS::PhysicsProcess::RelVal_SMS_T1tttt_mGl1500_mLSP100;
      else if(str == "RelVal_TTbar")                              return DEFS::PhysicsProcess::RelVal_TTbar;
      else if(str == "RelValHEMiss_QCD_FlatPt_15_3000HS")         return DEFS::PhysicsProcess::RelValHEMiss_QCD_FlatPt_15_3000HS;
      else if(str == "RelValHEMiss_QCD_Pt_600_800")               return DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_600_800;
      else if(str == "RelValHEMiss_QCD_Pt_80_120")                return DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_80_120;
      else if(str == "RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100")   return DEFS::PhysicsProcess::RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100;
      else if(str == "RelValHEMiss_TTbar")                        return DEFS::PhysicsProcess::RelValHEMiss_TTbar;
      else if(str == "GJets_HT-100to200")                         return DEFS::PhysicsProcess::GJets_HT_100to200;
      else if(str == "GJets_HT-200to400")                         return DEFS::PhysicsProcess::GJets_HT_200to400;
      else if(str == "GJets_HT-400to600")                         return DEFS::PhysicsProcess::GJets_HT_400to600;
      else if(str == "GJets_HT-600toInf")                         return DEFS::PhysicsProcess::GJets_HT_600toInf;
      else if(str == "QCD_HT-200to300")                           return DEFS::PhysicsProcess::QCD_HT_200to300;
      else if(str == "QCD_HT-300to500")                           return DEFS::PhysicsProcess::QCD_HT_300to500;
      else if(str == "QCD_HT-500to700")                           return DEFS::PhysicsProcess::QCD_HT_500to700;
      else if(str == "QCD_HT-700to1000")                          return DEFS::PhysicsProcess::QCD_HT_700to1000;
      else if(str == "QCD_HT-1000to1500")                         return DEFS::PhysicsProcess::QCD_HT_1000to1500;
      else if(str == "QCD_HT-1500to2000")                         return DEFS::PhysicsProcess::QCD_HT_1500to2000;
      else if(str == "QCD_HT-2000toInf")                          return DEFS::PhysicsProcess::QCD_HT_2000toInf;
      else if(str == "GJets_DR-0p4_HT-100to200")                  return DEFS::PhysicsProcess::GJets_DR_0p4_HT_100to200;
      else if(str == "GJets_DR-0p4_HT-200to400")                  return DEFS::PhysicsProcess::GJets_DR_0p4_HT_200to400;
      else if(str == "GJets_DR-0p4_HT-400to600")                  return DEFS::PhysicsProcess::GJets_DR_0p4_HT_400to600;
      else if(str == "GJets_DR-0p4_HT-600toInf")                  return DEFS::PhysicsProcess::GJets_DR_0p4_HT_600toInf;

      else if(str == "UNKNOWN")              return  DEFS::PhysicsProcess::UNKNOWN;
 
      cout<<" ERROR  DEFS::getProcessType str ="<<str<<" not found"<<endl;
  
      return  DEFS::PhysicsProcess::UNKNOWN;

    }//getProcessType

    //---------------------------------------------------------------------------
    string getTypeString(Type type){

      if      (type == Data_EGamma)                               return string("Data_EGamma");
      else if (type == Data_JetHT)                                return string("Data_JetHT");
      else if (type == Data_MET)                                  return string("Data_MET");
      else if (type == Data_SingleMuon)                           return string("Data_SingleMuon");
      else if (type == Data_HEMiss_EGamma)                        return string("Data_HEMiss_EGamma");
      else if (type == Data_HEMiss_JetHT)                         return string("Data_HEMiss_JetHT");
      else if (type == Data_HEMiss_MET)                           return string("Data_HEMiss_MET");
      else if (type == Data_HEMiss_SingleMuon)                    return string("Data_HEMiss_SingleMuon");
      else if (type == RelVal_QCD_FlatPt_15_3000HS)               return string("RelVal_QCD_FlatPt_15_3000HS");
      else if (type == RelVal_QCD_Pt_600_800)                     return string("RelVal_QCD_Pt_600_800");
      else if (type == RelVal_QCD_Pt_80_120)                      return string("RelVal_QCD_Pt_80_120");
      else if (type == RelVal_SMS_T1tttt_mGl1500_mLSP100)         return string("RelVal_SMS_T1tttt_mGl1500_mLSP100");
      else if (type == RelVal_TTbar)                              return string("RelVal_TTbar");
      else if (type == RelValHEMiss_QCD_FlatPt_15_3000HS)         return string("RelValHEMiss_QCD_FlatPt_15_3000HS");
      else if (type == RelValHEMiss_QCD_Pt_600_800)               return string("RelValHEMiss_QCD_Pt_600_800");
      else if (type == RelValHEMiss_QCD_Pt_80_120)                return string("RelValHEMiss_QCD_Pt_80_120");
      else if (type == RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100)   return string("RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100");
      else if (type == RelValHEMiss_TTbar)                        return string("RelValHEMiss_TTbar");
      else if (type == GJets_HT_100to200)                         return string("GJets_HT-100to200");
      else if (type == GJets_HT_200to400)                         return string("GJets_HT-200to400");
      else if (type == GJets_HT_400to600)                         return string("GJets_HT-400to600");
      else if (type == GJets_HT_600toInf)                         return string("GJets_HT-600toInf");
      else if (type == QCD_HT_200to300)                           return string("QCD_HT-200to300");
      else if (type == QCD_HT_300to500)                           return string("QCD_HT-300to500");
      else if (type == QCD_HT_500to700)                           return string("QCD_HT-500to700");
      else if (type == QCD_HT_700to1000)                          return string("QCD_HT-700to1000");
      else if (type == QCD_HT_1000to1500)                         return string("QCD_HT-1000to1500");
      else if (type == QCD_HT_1500to2000)                         return string("QCD_HT-1500to2000");
      else if (type == QCD_HT_2000toInf)                          return string("QCD_HT-2000toInf");
      else if (type == GJets_DR_0p4_HT_100to200)                  return string("GJets_DR-0p4_HT-100to200");
      else if (type == GJets_DR_0p4_HT_200to400)                  return string("GJets_DR-0p4_HT-200to400");
      else if (type == GJets_DR_0p4_HT_400to600)                  return string("GJets_DR-0p4_HT-400to600");
      else if (type == GJets_DR_0p4_HT_600toInf)                  return string("GJets_DR-0p4_HT-600toInf");

      else if (type == UNKNOWN)              return string("UNKNOWN");

      else cout<<" ERROR  DEFS::getProcessTypeString type ="<<type<<" not found"<<endl;

      return "ERROR in DEFS::getProcessTypeString ";

    }//getTypeString
     
    //---------------------------------------------------------------------------
    // A routine that returns the title for a given process type
    std::string getTypeTitle(Type type) {

       if (type == Data_EGamma)
          return string("EGamma Data");
       else if (type == Data_JetHT)
          return string("JetHT Data");
       else if (type == Data_MET)
          return string("MET Data");
       else if (type == Data_SingleMuon)
          return string("SingleMuon Data");
       else if (type == Data_HEMiss_EGamma)
          return string("EGamma Data (HEM)");
       else if(type == Data_HEMiss_JetHT)
          return string("JetHT Data (HEM)");
       else if (type == Data_HEMiss_MET)
          return string("MET Data (HEM)");
       else if (type == Data_HEMiss_SingleMuon)
          return string("SingleMuon Data (HEM)");
       else if (type == RelVal_QCD_FlatPt_15_3000HS || type == RelVal_QCD_Pt_600_800 || type == RelVal_QCD_Pt_80_120)
          return string("QCD");
       else if (type == RelVal_SMS_T1tttt_mGl1500_mLSP100)
          return string("SMS-T1tttt");
       else if (type == RelVal_TTbar)
          return string("t#bar{t}");
       else if (type == RelValHEMiss_QCD_FlatPt_15_3000HS || type == RelValHEMiss_QCD_Pt_600_800 || type == RelValHEMiss_QCD_Pt_80_120)
          return string("QCD_HEM");
       else if (type == RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100)
          return string("SMS-T1tttt (HEM)");
       else if (type == RelValHEMiss_TTbar)
          return string("t#bar{t} (HEM)");
       else if (type == GJets_HT_100to200 ||type == GJets_HT_200to400 ||type == GJets_HT_400to600 ||type == GJets_HT_600toInf)
          return string("GJets");
       else if (type == QCD_HT_200to300 || type == QCD_HT_300to500 || type == QCD_HT_500to700 || type == QCD_HT_700to1000 || type == QCD_HT_1000to1500 || type == QCD_HT_1500to2000 || type == QCD_HT_2000toInf)
          return string("QCD");
       else if (type == GJets_DR_0p4_HT_100to200 || type == GJets_DR_0p4_HT_200to400 || type == GJets_DR_0p4_HT_400to600 || type == GJets_DR_0p4_HT_600toInf)
          return string("GJets_DR-0p4");
       else
          return getTypeString(type);
    }//getTypeTitle

    //---------------------------------------------------------------------------
    // A  routine that returns the Color_t for a given process type
    Color_t getProcessColor(Type type){

       if      (type == Data_EGamma) return kGray;
       else if (type == Data_JetHT) return kGray+1;
       else if (type == Data_MET) return kBlack;
       else if (type == Data_SingleMuon) return kGray+2;
       else if (type == Data_HEMiss_EGamma) return kRed-7;
       else if (type == Data_HEMiss_JetHT) return kRed+2;
       else if (type == Data_HEMiss_MET) return kRed;
       else if (type == Data_HEMiss_SingleMuon) return kRed+3;
       else if (type == RelVal_QCD_FlatPt_15_3000HS || type == RelVal_QCD_Pt_600_800 || type == RelVal_QCD_Pt_80_120 || 
                type == RelValHEMiss_QCD_FlatPt_15_3000HS || type == RelValHEMiss_QCD_Pt_600_800 || type == RelValHEMiss_QCD_Pt_80_120) return kRed-6;
       else if (type == RelVal_SMS_T1tttt_mGl1500_mLSP100 || type == RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100) return kMagenta-3;
       else if (type == RelVal_TTbar || type == RelValHEMiss_TTbar) return kRed-3;
       else if (type == GJets_HT_100to200 ||type == GJets_HT_200to400 ||type == GJets_HT_400to600 ||type == GJets_HT_600toInf) return kBlack;
       else if (type == QCD_HT_200to300 || type == QCD_HT_300to500 || type == QCD_HT_500to700 || type == QCD_HT_700to1000 ||
                type == QCD_HT_1000to1500 || type == QCD_HT_1500to2000 || type == QCD_HT_2000toInf) return kBlack;
       else if (type == GJets_DR_0p4_HT_100to200 || type == GJets_DR_0p4_HT_200to400 || type == GJets_DR_0p4_HT_400to600 || type == GJets_DR_0p4_HT_600toInf) return kBlack;
       else{
          cout << "WARNING Plotter::GetProcessColor() Unknown process name=|"<<getTypeString(type)
               <<"|. Returning process color as kBlack." << endl;
       }
       
       return kBlack;
       
    }//getProcessColor

    //---------------------------------------------------------------------------
    // A routine that returns the Marker_t for a given process type
    Color_t getProcessMarker(Type type){

       if      (type == Data_EGamma) return kFullSquare;
       else if (type == Data_JetHT) return kFullTriangleUp;
       else if (type == Data_MET) return kFullCircle;
       else if (type == Data_SingleMuon) return kFullTriangleDown;
       else if (type == Data_HEMiss_EGamma) return kOpenSquare;
       else if (type == Data_HEMiss_JetHT) return kOpenTriangleUp;
       else if (type == Data_HEMiss_MET) return kOpenCircle;
       else if (type == Data_HEMiss_SingleMuon) return kOpenTriangleDown;
       else if (type == RelVal_QCD_FlatPt_15_3000HS || type == RelVal_QCD_Pt_600_800 || type == RelVal_QCD_Pt_80_120) return kFullTriangleDown;
       else if (type == RelValHEMiss_QCD_FlatPt_15_3000HS || type == RelValHEMiss_QCD_Pt_600_800 || type == RelValHEMiss_QCD_Pt_80_120) return kOpenTriangleDown;
       else if (type == RelVal_SMS_T1tttt_mGl1500_mLSP100) return kFullCircle;
       else if (type == RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100) return kOpenCircle;
       else if (type == RelVal_TTbar) return kFullTriangleUp;
       else if (type == RelValHEMiss_TTbar) return kOpenTriangleUp;
       else if (type == GJets_HT_100to200 ||type == GJets_HT_200to400 ||type == GJets_HT_400to600 ||type == GJets_HT_600toInf) return kFullCircle;
       else if (type == QCD_HT_200to300 || type == QCD_HT_300to500 || type == QCD_HT_500to700 || type == QCD_HT_700to1000 ||
                type == QCD_HT_1000to1500 || type == QCD_HT_1500to2000 || type == QCD_HT_2000toInf) return kFullCircle;
       else if (type == GJets_DR_0p4_HT_100to200 || type == GJets_DR_0p4_HT_200to400 || type == GJets_DR_0p4_HT_400to600 || type == GJets_DR_0p4_HT_600toInf) return kFullCircle;
       else{
          cout << "WARNING Plotter::GetProcessColor() Unknown process name=|"<<getTypeString(type)
               <<"|. Returning process marker as kFullCircle." << endl;
       }
       
       return kFullCircle;
       
    }//getProcessMarker

  } //namespace   
   
  //---------------------------------------------------------------------------
  // A routine that returns the string given the Lepton Category
  string getLeptonCatString(LeptonCat type){
    if (type == electron)  return "electron";
    else if (type == muon) return "muon";
    else if (type == both) return "both";
    else if (type == none) return "none";

    cout<<"ERROR in DEFS::getLeptonCatString type="<<type<<" not defined"<<endl;

    return "";

  }//getLeptonCatString

  //---------------------------------------------------------------------------
  // for historical reasons
  std::string getEventCatString(LeptonCat a){
    return  getLeptonCatString(a);
  }


  // A routine that returns the string given the Lepton Category
  LeptonCat getLeptonCat(string type){
    TString s = type;
    s.ToUpper();

    if (s.Contains("NONE"))          return none;
    else if (s.Contains("MUON"))     return muon;
    else if (s.Contains("ELECTRON")) return electron;
    else if (s.Contains("BOTH"))     return both;
    else cout<<"ERROR in DEFS::getLeptonCatString type="<<type<<" not defined!. Returning none."<<endl;

    return none;

  }//getLeptonCat

  //---------------------------------------------------------------------------
  // A routine that returns the string given the Lepton Category
  string getLeptonBinString(LeptonBin type){
    if (type == leptons0)      return "leptons0";
    else if (type == lepton1)  return "lepton1";
    else if (type == leptons2) return "leptons2";

    cout<<"ERROR in DEFS::getLeptonBinString type="<<type<<" not defined"<<endl;

    return "";

  }//getLeptonCatString

  //---------------------------------------------------------------------------
  // A routine that returns the string given the Lepton Category
  LeptonBin getLeptonBin(string str){

    if (str == "leptons0")      return leptons0;
    else if (str == "lepton1")  return lepton1;
    else if (str == "leptons2") return leptons2;

    else cout<<"ERROR in DEFS::getLeptonBin str="<<str<<" not found!. Returning leptons0."<<endl;

    return leptons0;

  }//getLeptonCat

  //---------------------------------------------------------------------------
  LeptonBin getLeptonBin(int nLeptons, LeptonBin inclusive_bin) {

    if(nLeptons >= int(inclusive_bin)) return inclusive_bin;

    if (nLeptons == 0)      return leptons0;
    else if (nLeptons == 1) return lepton1;
    else if (nLeptons == 2) return leptons2;

    else cout<<" ERROR  DEFS::geLeptonBin jet(s)"<<nLeptons<<" not found"<<endl;
    return leptons0;

  }//getLeptonBin

  //---------------------------------------------------------------------------
  string getJetBinString(JetBin jBin){

    //the returning string
    if (jBin == jets0)      return string("jets0");
    else if (jBin == jet1)  return string("jet1");
    else if (jBin == jets2) return string("jets2");
    else if (jBin == jets3) return string("jets3");
    else if (jBin == jets4) return string("jets4");
    else if (jBin == jets5) return string("jets5");
    else if (jBin == jets6) return string("jets6");
    else if (jBin == jets7) return string("jets7");
    else if (jBin == jets8) return string("jets8");
    else if (jBin == jets9) return string("jets9");
    else cout<<" ERROR  DEFS::geJetBinString jBin ="<<jBin<<" not found"<<endl;

    return "ERROR in DEFS::getJetBinString ";

  }//getJetBinString


  //---------------------------------------------------------------------------
  string getJetBinLabel(JetBin jBin){

    //the returning string
    if (jBin == jets0)      return string("0 jets");
    else if (jBin == jet1)  return string("1 jet");
    else if (jBin == jets2) return string("2 jets");
    else if (jBin == jets3) return string("3 jets");
    else if (jBin == jets4) return string("4 jets");
    else if (jBin == jets5) return string("5 jets");
    else if (jBin == jets6) return string("6 jets");
    else if (jBin == jets7) return string("7 jets");
    else if (jBin == jets8) return string("8 jets");
    else if (jBin == jets9) return string("#geq 9 jets");
    else cout<<" ERROR  DEFS::geJetBinString jBin ="<<jBin<<" not found"<<endl;

    return "ERROR in DEFS::getJetBinString ";

  }//getJetBinLabel


  //---------------------------------------------------------------------------
  JetBin getJetBin(std::string str){

    if (str == "jets0")      return jets0;
    else if (str == "jet1")  return jet1;
    else if (str == "jets2") return jets2;
    else if (str == "jets3") return jets3;
    else if (str == "jets4") return jets4;
    else if (str == "jets5") return jets5;
    else if (str == "jets6") return jets6;
    else if (str == "jets7") return jets7;
    else if (str == "jets8") return jets8;
    else if (str == "jets9") return jets9;

    cout<<" ERROR  DEFS::getJetBin str ="<<str<<" not found"<<endl;
    return  jets0;

  }//getJetBin

  //---------------------------------------------------------------------------
  JetBin getJetBin(int nJets, JetBin inclusive_bin){

    if(nJets >= int(inclusive_bin)) return inclusive_bin;

    if (nJets == 0)      return jets0;
    else if (nJets == 1) return jet1;
    else if (nJets == 2) return jets2;
    else if (nJets == 3) return jets3;
    else if (nJets == 4) return jets4;
    else if (nJets == 5) return jets5;
    else if (nJets == 6) return jets6;
    else if (nJets == 7) return jets7;
    else if (nJets == 8) return jets8;
    else if (nJets == 9) return jets9;

    else cout<<" ERROR  DEFS::geJetBin jet(s)"<<nJets<<" not found"<<endl;
    return jets0;

  }//getJetBin

  //---------------------------------------------------------------------------
  // A routine that returns a string given the type
  string getTagCatString(TagCat type){

    if (type == pretag)  return "pretag";
    if (type == eq0tag)  return "eq0tag";
    if (type == eq1tag)  return "eq1tag";
    if (type == eq2tag)  return "eq2tag";
    if (type == ge0tag)  return "ge0tag";
    if (type == ge1tag)  return "ge1tag";
    if (type == ge2tag)  return "ge2tag";

    cout <<"ERROR  PhysicsProcess::getTagCatString cannot find the given type"<<endl;
    return "ERROR";

  }

  //---------------------------------------------------------------------------
  // A routine that returns a label given the type
  string getTagCatLabel(TagCat type){

    if (type == pretag)  return "pretag";
    if (type == eq0tag)  return "0 b-tags";
    if (type == eq1tag)  return "1 b-tag";
    if (type == eq2tag)  return "2 b-tags";
    if (type == ge0tag)  return "#geqslant0 b-tags";
    if (type == ge1tag)  return "#geqslant1 b-tags";
    if (type == ge2tag)  return "#geqslant2 b-tags";

    cout <<"ERROR  PhysicsProcess::getTagCatString cannot find the given type"<<endl;
    return "ERROR";

  }
  
  // A routine that returns a jetBin given a string
  DEFS::TagCat getTagCat(std::string str){
    
    if (str == "pretag")  return pretag;
    if (str == "eq0tag")  return eq0tag;
    if (str == "eq1tag")  return eq1tag;
    if (str == "eq2tag")  return eq2tag;
    if (str == "ge0tag")  return ge0tag;
    if (str == "ge1tag")  return ge1tag;
    if (str == "ge2tag")  return ge2tag;

    cout<<"ERROR  PhysicsProcess::getTagCat cannot find the given string"<<endl;
    return pretag;
    
  }

  //---------------------------------------------------------------------------
  string getCutLevelString(CutLevel type) {
     
    if      (type == NtupleLevel) return "NtupleLevel";
    else if (type == cut0)        return "c0:Filters";
    else if (type == cut1)        return "c1:Triggers";
    else if (type == cut2)        return "c2:NLeptons";
    else if (type == cut3)        return "c3:";
    else if (type == cut4)        return "c4:";
    else if (type == cut5)        return "c5:";
    else if (type == cut6)        return "c6:";
    else if (type == cut7)        return "c7:";
    else if (type == cut8)        return "c8:";
    else if (type == cut9)        return "c9:";

    cout <<"ERROR  DEFS::getCutLevelString cannot find the given type"<<endl;
    return "ERROR";

   }

   DEFS::CutLevel getCutLevel(std::string str) {

    if      (str == "NtupleLevel") return NtupleLevel;
    else if (str == "c0:Filters")  return cut0;
    else if (str == "c1:Triggers") return cut1;
    else if (str == "c2:NLeptons") return cut2;
    else if (str == "c3:")         return cut3;
    else if (str == "c4:")         return cut4;
    else if (str == "c5:")         return cut5;
    else if (str == "c6:")         return cut6;
    else if (str == "c7:")         return cut7;
    else if (str == "c8:")         return cut8;
    else if (str == "c9:")         return cut9;

    cout<<"ERROR  DEFS::getCutLevel cannot find the given string"<<endl;
    return NtupleLevel;

   }

   //---------------------------------------------------------------------------
   // A routine that returns a string given the type
   std::string getNtupleTypeString(NtupleType type){
      
      if      (type == EventNtuple) return "EventNtuple";
      else if (type == Other)       return "Other";

      cout<<"ERROR DEFS::getNtupleTypeString cannot find the given type"<<endl;
      return "ERROR";

   }

   // A routine that returns a NtupleType given a string
   DEFS::NtupleType getNtupleType(std::string str){
      
      if      (str == "EventNtuple") return EventNtuple;
      else if (str == "Other")       return Other;

      cout<<"ERROR  DEFS::getNtupleType cannot find the given string"<<endl;
      return Other;

   }

  // A routine that returns the treename for a given NtupleType
  std::string getTreeName(NtupleType type, JetBin nJets){
     
     if      (type == EventNtuple) return "TreeMaker2/PreSelection";
     else if (type == Other)       return "Other";
     
     cout<<"ERROR DEFS::getTreeName cannot find the given type"<<endl;
     return "ERROR";
     
  }

   //---------------------------------------------------------------------------
   // A routine that returns a string given the University
   std::string getUniversityString(University univ) {
      if      (univ == CUBoulder)       return "CUBoulder";
      else if (univ == Combined)        return "Combined";
      else if (univ == OtherUniversity) return "OtherUniversity";

      cout<<"ERROR DEFS::getUniversityString cannot find the given university"<<endl;
      return "ERROR";

   }

   // A routine that returns a University given a string
   DEFS::University getUniversity(std::string str) {

      if      (str == "CUBoulder")       return CUBoulder;
      else if (str == "Combined")        return Combined;
      else if (str == "OtherUniversity") return OtherUniversity;

      cout<<"ERROR  DEFS::getUniversity cannot find the given string"<<endl;
      return OtherUniversity;

   }

   //---------------------------------------------------------------------------
   /// Print a PdgId as a named string
   std::string toParticleName(PdgId p) {
      if (p == ELECTRON)         return "ELECTRON";
      else if (p == POSITRON)    return "POSITRON";
      else if (p == MUON)        return "MUON";
      else if (p == ANTIMUON)    return "ANTIMUON";
      else if (p == TAU)         return "TAU";
      else if (p == ANTITAU)     return "ANTITAU";
      else if (p == NU_E)        return "NU_E";
      else if (p == NU_EBAR)     return "NU_EBAR";
      else if (p == NU_MU)       return "NU_MU";
      else if (p == NU_MUBAR)    return "NU_MUBAR";
      else if (p == NU_TAU)      return "NU_TAU";
      else if (p == NU_TAUBAR)   return "NU_TAUBAR";

      else if (p == d)           return "d";
      else if (p == u)           return "u";
      else if (p == s)           return "s";
      else if (p == c)           return "c";
      else if (p == b)           return "b";
      else if (p == t)           return "t";
      else if (p == dbar)        return "dbar";
      else if (p == ubar)        return "ubar";
      else if (p == sbar)        return "sbar";
      else if (p == cbar)        return "cbar";
      else if (p == bbar)        return "bbar";
      else if (p == tbar)        return "tbar";

      else if (p == DQUARK)      return "DQUARK";
      else if (p == UQUARK)      return "UQUARK";
      else if (p == SQUARK)      return "SQUARK";
      else if (p == CQUARK)      return "CQUARK";
      else if (p == BQUARK)      return "BQUARK";
      else if (p == TQUARK)      return "TQUARK";
      else if (p == ANTIDQUARK)  return "ANTIDQUARK";
      else if (p == ANTIUQUARK)  return "ANTIUQUARK";
      else if (p == ANTISQUARK)  return "ANTISQUARK";
      else if (p == ANTICQUARK)  return "ANTICQUARK";
      else if (p == ANTIBQUARK)  return "ANTIBQUARK";
      else if (p == ANTITQUARK)  return "ANTITQUARK";

      else if (p == PROTON)      return "PROTON";
      else if (p == ANTIPROTON)  return "ANTIPROTON";
      else if (p == NEUTRON)     return "NEUTRON";
      else if (p == ANTINEUTRON) return "ANTINEUTRON";
      else if (p == PIPLUS)      return "PIPLUS";
      else if (p == PIMINUS)     return "PIMINUS";

      else if (p == PHOTON)      return "PHOTON";
      else if (p == WPLUSBOSON)  return "WPLUSBOSON";
      else if (p == WMINUSBOSON) return "WMINUSBOSON";
      else if (p == ZBOSON)      return "ZBOSON";
      else if (p == GLUON)       return "GLUON";
      else if (p == HIGGS)       return "HIGGS";
      else if (p == ANY)         return "*";

      cout << "ERROR DEFS::toParticleName cannot find the given PdgId" << endl;
      return "*";
   }



   /// Print a PdgId as a named string
   DEFS::PdgId toParticleId(const std::string& pname) {
      if (pname == "ELECTRON")         return ELECTRON;
      else if (pname == "POSITRON")    return POSITRON;
      else if (pname == "MUON")        return MUON;
      else if (pname == "ANTIMUON")    return ANTIMUON;     
      else if (pname == "TAU")         return TAU;
      else if (pname == "ANTITAU")     return ANTITAU;
      else if (pname == "NU_E")        return NU_E;
      else if (pname == "NU_EBAR")     return NU_EBAR;
      else if (pname == "NU_MU")       return NU_MU;
      else if (pname == "NU_MUBAR")    return NU_MUBAR;
      else if (pname == "NU_TAU")      return NU_TAU;
      else if (pname == "NU_TAUBAR")   return NU_TAUBAR;

      else if (pname == "d")           return d;
      else if (pname == "u")           return u;
      else if (pname == "s")           return s;
      else if (pname == "c")           return c;
      else if (pname == "b")           return b;
      else if (pname == "t")           return t;
      else if (pname == "dbar")        return dbar;
      else if (pname == "ubar")        return ubar;
      else if (pname == "sbar")        return sbar;
      else if (pname == "cbar")        return cbar;
      else if (pname == "bbar")        return bbar;
      else if (pname == "tbar")        return tbar;

      else if (pname == "DQUARK")      return DQUARK;
      else if (pname == "UQUARK")      return UQUARK;
      else if (pname == "SQUARK")      return SQUARK;
      else if (pname == "CQUARK")      return CQUARK;
      else if (pname == "BQUARK")      return BQUARK;
      else if (pname == "TQUARK")      return TQUARK;
      else if (pname == "ANTIDQUARK")  return ANTIDQUARK;
      else if (pname == "ANTIUQUARK")  return ANTIUQUARK;
      else if (pname == "ANTISQUARK")  return ANTISQUARK;
      else if (pname == "ANTICQUARK")  return ANTICQUARK;
      else if (pname == "ANTIBQUARK")  return ANTIBQUARK;
      else if (pname == "ANTITQUARK")  return ANTITQUARK;

      else if (pname == "PROTON")      return PROTON;
      else if (pname == "ANTIPROTON")  return ANTIPROTON;
      else if (pname == "NEUTRON")     return NEUTRON;
      else if (pname == "ANTINEUTRON") return ANTINEUTRON;
      else if (pname == "PIPLUS")      return PIPLUS;
      else if (pname == "PIMINUS")     return PIMINUS;

      else if (pname == "PHOTON")      return PHOTON;
      else if (pname == "WPLUSBOSON")  return WPLUSBOSON;
      else if (pname == "WMINUSBOSON") return WMINUSBOSON;
      else if (pname == "ZBOSON")      return ZBOSON;
      else if (pname == "GLUON")       return GLUON;
      else if (pname == "HIGGS")       return HIGGS;
      else if (pname == "*")           return ANY;

    cout << "ERROR DEFS::toParticleId cannot find the given string" << endl;
    return ANY;

   }

   /// Return a PdgId from an int
   DEFS::PdgId getParticleIdFromInt(int p) {
      if (p == 11)         return ELECTRON;
      else if (p == -11)   return POSITRON;
      else if (p == 13)    return MUON;
      else if (p == -13)   return ANTIMUON;     
      else if (p == 15)    return TAU;
      else if (p == -15)   return ANTITAU;
      else if (p == 12)    return NU_E;
      else if (p == -12)   return NU_EBAR;
      else if (p == 14)    return NU_MU;
      else if (p == -14)   return NU_MUBAR;
      else if (p == 16)    return NU_TAU;
      else if (p == -16)   return NU_TAUBAR;

      else if (p == 1)     return d;
      else if (p == 2)     return u;
      else if (p == 3)     return s;
      else if (p == 4)     return c;
      else if (p == 5)     return b;
      else if (p == 6)     return t;
      else if (p == -1)    return dbar;
      else if (p == -2)    return ubar;
      else if (p == -3)    return sbar;
      else if (p == -4)    return cbar;
      else if (p == -5)    return bbar;
      else if (p == -6)    return tbar;

      else if (p == 1)     return DQUARK;
      else if (p == 2)     return UQUARK;
      else if (p == 3)     return SQUARK;
      else if (p == 4)     return CQUARK;
      else if (p == 5)     return BQUARK;
      else if (p == 6)     return TQUARK;
      else if (p == -1)    return ANTIDQUARK;
      else if (p == -2)    return ANTIUQUARK;
      else if (p == -3)    return ANTISQUARK;
      else if (p == -4)    return ANTICQUARK;
      else if (p == -5)    return ANTIBQUARK;
      else if (p == -6)    return ANTITQUARK;

      else if (p == 2212)  return PROTON;
      else if (p == -2212) return ANTIPROTON;
      else if (p == 2112)  return NEUTRON;
      else if (p == -2112) return ANTINEUTRON;
      else if (p == 211)   return PIPLUS;
      else if (p == -211)  return PIMINUS;

      else if (p == 22)    return PHOTON;
      else if (p == -22)   return PHOTON;
      else if (p == 24)    return WPLUSBOSON;
      else if (p == -24)   return WMINUSBOSON;
      else if (p == 23)    return ZBOSON;
      else if (p == -23)   return ZBOSON;
      else if (p == 21)    return GLUON;
      else if (p == -21)   return GLUON;
      else if (p == 25)    return HIGGS;
      else if (p == -25)   return HIGGS;
      else if (p == 10000) return ANY;

      cout << "ERROR DEFS::getParticleIdFromInt cannot find the given PdgId" << endl;
      return ANY;
   }

}// end of namespace DEFS
