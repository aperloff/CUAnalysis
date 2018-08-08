#include "CUAnalysis/SpecialTools/interface/DefaultValues.hh"

// ----------------------------------------------------------------------------
// This method returns the full basepath of config files.
// Basically returns $CMSSW_BASE+"/src/CUAnalysis/Config/Run2ProductionV15/"
std::string DefaultValues::getConfigPath(){

  std::string basePath;
  char const* tmp = getenv("CMSSW_BASE");
  
  if(tmp != NULL)
    basePath = std::string(tmp);
  else {
    std::cout << "ERROR DefaultValues::getConfigPath() cannot find the top of the local CMSSW release" << std::endl;
    assert(tmp!=NULL);
  }
  
  return basePath + "/src/CUAnalysis/ConfigFiles/Run2ProductionV15a/";

}// getConfigPath

// ----------------------------------------------------------------------------
std::string DefaultValues::getBDTLocation(DEFS::JetBin jetBin, DEFS::TagCat tagcat, DEFS::University univ, bool filenameOnly) {
  // The location of the table with the file locations
  std::string fileLocationFile = getConfigPath()+"FileLocation_BDT.txt";

  // Create the table and parse the contents of the file
  FileLocationTable table("FileLocationTable_BDT");  
  if(!table.parseFromFile(fileLocationFile,"TableCellText","Normal"))
    std::cout<<"ERROR  DefaultValues::getBDTLocation() cannot parse config file "<<fileLocationFile<<std::endl;

  // make sure you add the basepath to the table
  if(!filenameOnly)
    table.addBasePath();

  // find the file location for that process
  std::string row = std::string(Form("%s_%s",DEFS::getJetBinString(jetBin).c_str(),DEFS::getTagCatString(tagcat).c_str()));
  TableCellText * cellFile = (TableCellText *) table.getCellRowColumn(row,"FilePath_"+DEFS::getUniversityString(univ));

  if(!filenameOnly)
    return getConfigPath()+cellFile->text;
  else
    return cellFile->text;

}

// ----------------------------------------------------------------------------
// This method returns the table with the event expectation for the evt/tag category
Table DefaultValues::getNormTable(DEFS::LeptonCat evtcat, DEFS::TagCat tagcat){

  Table table("NormTable");
  std::string eventEstimatesFile = getConfigPath()+"EventEstimates_";

  // add the tag name and the ".txt" at the end
  eventEstimatesFile += DEFS::getEventCatString(evtcat)+"_";
  eventEstimatesFile += DEFS::getTagCatString(tagcat);
  eventEstimatesFile += ".txt";

  if(!table.parseFromFile(eventEstimatesFile))
    std::cout<<"ERROR  DefaultValues::getNormTable() cannot parse config file "
	<<eventEstimatesFile<<std::endl;

  return table;
  
}//getNormTable

// ----------------------------------------------------------------------------
// This method returns the appropriate table of file location for each jet bin
// and tag category
Table DefaultValues::getFileLocationTable(DEFS::TagCat tagcat){ 

  // The location of the table with the file locations
  std::string fileLocationFile = getConfigPath()+"FileLocation.txt";
  
  // add the tag name and the ".txt" at the end
  //fileLocationFile += DEFS::getTagCatString(tagcat);
  //fileLocationFile += ".txt";

  // Create the table and parse the contents of the file
  FileLocationTable table("FileLocationTable");  
  if(!table.parseFromFile(fileLocationFile,"TableCellText","Normal"))
    std::cout<<"ERROR  DefaultValues::getFileLocationTable() cannot parse config file "
	<<fileLocationFile<<std::endl;


  // make sure you add the basepath to the table
  table.addBasePath();

  return table;
  
}//getFileLocationTable



// ----------------------------------------------------------------------------
std::vector < PhysicsProcess * > DefaultValues::getProcesses(std::vector<DEFS::PhysicsProcessType> processName,
                                                        DEFS::JetBin jetBin, 
                                                        DEFS::TagCat tagcat,
                                                        bool forPlots,
                                                        DEFS::NtupleType ntupleType){

  // The returning vector of processes
  std::vector<PhysicsProcess*>  proc;

  // get the table with the expected number of 
  std::map<DEFS::LeptonCat, Table> normTable;
  //normTable[DEFS::muon    ] = getNormTable(DEFS::muon    ,tagcat);
  //normTable[DEFS::electron] = getNormTable(DEFS::electron,tagcat);

  // get the table with the files location
  Table fileTable = getFileLocationTable(tagcat);

  // Loop over all the process names
  for (unsigned int prn = 0; prn < processName.size(); prn++){

    PhysicsProcess * pr = getSingleProcess(processName[prn], jetBin, normTable, fileTable, forPlots, ntupleType);
    if (pr == 0) {
      std::cout<<"ERROR DefaultValues::getProcesses could not add process"<<std::endl;
      continue;
    }

    proc.push_back(pr);
    
  }//for

  return proc;

}// getProcesses


// ----------------------------------------------------------------------------
// Return a PhysicsProcess object for process "process" from the given inputs.
// For some reson it does not compile when I use the signature
// (..., const Table & normTable, const Table & fileTable, ...) 
PhysicsProcess * DefaultValues::getSingleProcess(DEFS::PhysicsProcessType process,
                                                 DEFS::JetBin jetBin,
                                                 std::map<DEFS::LeptonCat, Table> normTable,
                                                 Table fileTable,
                                                 bool forPlots,
                                                 DEFS::NtupleType ntupleType){

   // get the process name
   std::string prName = DEFS::PhysicsProcess::getTypeString(process);
   
   // get the name of the jetBin
   std::string jetBinName = DEFS::getJetBinString(jetBin);
   
   // find the file location for that process
   TableCellText * cellFile = (TableCellText *) fileTable.getCellRowColumn(prName,"FilePath_"+DEFS::getNtupleTypeString(ntupleType));

   // make sure we found the cell
   if (cellFile == 0){
      std::cout<<"ERROR DefaultValues::getSingleProcess Table "<<fileTable.getTableOrigin()
          <<" does not have row "<<prName
          <<" for column FilePath_" << DEFS::getNtupleTypeString(ntupleType) <<std::endl;
      std::cout<<" SKIPPING PROCESS "<<prName<<std::endl;
      return 0;
   }

   // Create the PhysicsProcess
   PhysicsProcess *  proc;
   if(forPlots)
      proc =  new PlotterPhysicsProcess(prName, getTypeTitle(process), cellFile->text, DEFS::getTreeName(ntupleType,jetBin), getProcessColor(process), getProcessMarker(process));
   else
      proc =  new PhysicsProcess(prName, getTypeTitle(process), cellFile->text, DEFS::getTreeName(ntupleType,jetBin));

   // and return it.
   return proc;
   
}//getSingleProcess


// ----------------------------------------------------------------------------
std::string  DefaultValues::getWeightForCategory(DEFS::TagCat tagcat, DEFS::PhysicsProcessType type, int iDet){

  // The returning weights, for the moment just "1"
  return "1";

  /*
    std::string wei ;
  // Set the detector type
  if (iDet ==  TopLepType::TCEM)
    wei += "(h.det==1)";
  else if (iDet ==  TopLepType::TPHX)
    wei += "(h.det==2)";
  else if (iDet ==  TopLepType::TCMUP)
    wei += "(h.det==3)";
  else if (iDet ==  TopLepType::TCMX)
    wei += "(h.det==4)";
  else if (iDet == 5)
    wei += "(h.det>=5)";
  else 
    wei += "(h.det>0)";

  // Set the QCD veto. For PHX add a h.met>25 cut
  wei += "*((h.det==2)*(h.met>25)+(h.det != 2))";


  // For data require 
  if (type == DEFS::Data ){
    if (tagcat == DEFS::pretag )    
      wei += "*1";
    else if (tagcat == DEFS::eq0tag)
      wei += "*(h.ntag==0)";
    else if (tagcat == DEFS::eq1tag)
      wei += "*(h.ntag==1)";
    else if (tagcat == DEFS::eq2tag)
      wei += "*(h.ntag==2)";      
    else
      std::cout<<"ERROR DefaultValues::getWeightForCategory (data) called with tagcat="<<tagcat<<std::endl;     
  }
  // For MC require 
  else {

    // I have to apply this for the 1 and the 2 tags. Do I need it for the 0 tag ??
    if (type != DEFS::WLight && type != DEFS::NonW)
      if (tagcat != DEFS::pretag &&
	  tagcat != DEFS::eq0tag )
	wei += "*(h.ntag>0)";

    // Pretag
    //if (tag==-1) 
    //wei += "*h.wgt*(h.tagProb0*h.passQCD + h.tagProb1*h.passQCD + h.tagProb2*( (h.det==2)*h.passQCD+(h.det!=2) ) )";

    //switch on ntags
    if (tagcat == DEFS::pretag )      // pretag sample 
      wei += "*(h.wgt*h.passQCD)";
    else if (tagcat == DEFS::eq0tag )      // untag sample 
      wei += "*(h.tagProb0*h.wgt*h.passQCD)";
    else if (tagcat == DEFS::eq1tag) // single tag sample
      wei += "*(h.tagProb1*h.wgt*h.passQCD)";
    else if (tagcat == DEFS::eq2tag) // double tags sample
      wei += "*(h.tagProb2*h.wgt*( (h.det==2)*h.passQCD+(h.det!=2) ))";      
    else
      std::cout<<"ERROR DefaultValues::getWeightForCategory (MC) called with tagcat="<<tagcat<<std::endl;     

  }

  // For MC only, use triggerTO for tight, but getMet2JetTurnOn_v2 for loose leptons
  if (type != DEFS::Data)
    wei += "*(((h.det<5) * h.triggerTO)+ (h.det>=5) * 0.982 /(1.0 + exp(-(h.corrVtxMet-42.78)/3.681)))";


  return wei;
  */

}//getWeightForCategory

// ----------------------------------------------------------------------------
std::vector < PhysicsProcess * > DefaultValues::getProcessesHEM(DEFS::JetBin jetBin,
                                                           DEFS::TagCat tagcat, 
                                                           bool include_data,
                                                           bool forPlots,
                                                           DEFS::NtupleType ntupleType){

  std::vector<DEFS::PhysicsProcess::Type> procs;

  if (include_data) {
    procs.push_back(DEFS::PhysicsProcess::Data_MET);
    procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_MET);
    procs.push_back(DEFS::PhysicsProcess::Data_JetHT);
    procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_JetHT);
    //procs.push_back(DEFS::PhysicsProcess::Data_EGamma);
    //procs.push_back(DEFS::PhysicsProcess::Data_SingleMuon);
    //procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_EGamma);
    //procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_SingleMuon);
  }
  else {
    procs.push_back(DEFS::PhysicsProcess::RelVal_TTbar);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_TTbar);
    procs.push_back(DEFS::PhysicsProcess::RelVal_SMS_T1tttt_mGl1500_mLSP100);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100);
    procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_FlatPt_15_3000HS);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_FlatPt_15_3000HS);
    //procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_Pt_80_120);
    //procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_80_120);
    //procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_Pt_600_800);
    //procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_600_800);
  }

   return getProcesses(procs, jetBin, tagcat, forPlots, ntupleType);

}//getProcessesHEM

// ----------------------------------------------------------------------------
std::vector < PhysicsProcess * > DefaultValues::getProcessesRA2b(DEFS::JetBin jetBin,
                                                            DEFS::TagCat tagcat, 
                                                            bool include_data,
                                                            bool include_systematics,
                                                            bool forPlots,
                                                            DEFS::NtupleType ntupleType,
                                                            DEFS::LeptonCat leptonCat){

  std::vector<DEFS::PhysicsProcess::Type> procs;

  if (include_data) {
    //procs.push_back(DEFS::PhysicsProcess::Data_EGamma);
    //procs.push_back(DEFS::PhysicsProcess::Data_JetHT);
    procs.push_back(DEFS::PhysicsProcess::Data_MET);
    //procs.push_back(DEFS::PhysicsProcess::Data_SingleMuon);
    //procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_EGamma);
    //procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_JetHT);
    procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_MET);
    //procs.push_back(DEFS::PhysicsProcess::Data_HEMiss_SingleMuon);
  }
  else {
    //procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_Pt_600_800);
    //procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_Pt_80_120);
    procs.push_back(DEFS::PhysicsProcess::RelVal_QCD_FlatPt_15_3000HS);
    procs.push_back(DEFS::PhysicsProcess::RelVal_SMS_T1tttt_mGl1500_mLSP100);
    procs.push_back(DEFS::PhysicsProcess::RelVal_TTbar);
    //procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_600_800);
    //procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_Pt_80_120);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_QCD_FlatPt_15_3000HS);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_SMS_T1tttt_mGl1500_mLSP100);
    procs.push_back(DEFS::PhysicsProcess::RelValHEMiss_TTbar);
  }

   return getProcesses(procs, jetBin, tagcat, forPlots, ntupleType);

}//getProcessesRA2b

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getCrossSectionAndError(TString channelName) {
  Table table;
  double xsec;
  double error;

  table.parseFromFile(getConfigPath()+"CrossSections_13TeV.txt","TableCellVal");
  TableCell * cell = table.getCellRowColumn(std::string(channelName),"CrossSection");
  if(cell){
    xsec = ((TableCellVal*)cell)->val.value;
    error = ((TableCellVal*)cell)->val.error;
    if (xsec==0)
      std::cout << "WARNING::getCrossSection::The cross section for " << channelName << " is 0.0 +/- 0.0" << std::endl;
    return std::make_pair(xsec,error);
  } else{
    std::cout << "WARNING::getCrossSection::channelName " << channelName 
	 << " not recognized. Returning -1 for the cross section." << std::endl 
	 << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
	 << "Please check channel names." << std::endl;
    return std::make_pair(-1.0,-1.0);
  }
}//getCrossSection

// ----------------------------------------------------------------------------
double DefaultValues::getBranchingRatio(TString channelName) {
  Table table;
  double br;

  table.parseFromFile(getConfigPath()+"BranchingRatios_13TeV.txt","TableCellMixed");
  TableCell * cell = table.getCellRowColumn(std::string(channelName),"BranchingRatio");
  if(cell){
    br = ((TableCellVal*)cell)->val.value;
    if (br==0)
      std::cout << "WARNING::getBranchingRatio::The branching ratio for " << channelName << " is 0.0 +/- 0.0" << std::endl;
    return br;
  } else{
    std::cout << "WARNING::getBranchingRatio::channelName " << channelName 
	 << " not recognized. Returning -1 for the branching ratio." << std::endl 
	 << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
	 << "Please check channel names." << std::endl;
    return -1.;
  }
}//getBranchingRatio

// ----------------------------------------------------------------------------
double DefaultValues::getNumMCEvts(TString channelName)
{
  Table table;
  double value;

  table.parseFromFile(getConfigPath()+"EventsFromMC.txt",
		      "TableCellVal");
  TableCell * cell =table.getCellRowColumn(std::string(channelName),"Events_PATtuple");
  if(cell){
    value = ((TableCellVal*)cell)->val.value;
    if (value==0)
      std::cout << "WARNING::getNumMCEvts::There are 0 events in the " << channelName << " MC." << std::endl;
    return value;
  } else{
    std::cout << "WARNING::getNumMCEvts::channelName " << channelName 
	 << " not recognized. Returning -1 event from MC." << std::endl 
	 << "Please check channel names." << std::endl;
    return -1.;
  }
}//getNumMCEvts

// ----------------------------------------------------------------------------
double DefaultValues::getScaleFactor(TString channelName)
{
  Table table;
  double sf;

  table.parseFromFile(getConfigPath()+std::string("ScaleFactors_13TeV.txt"),"TableCellVal");
  TableCell * cell = table.getCellRowColumn(std::string(channelName),"ScaleFactor");
  if(cell){
    sf = ((TableCellVal*)cell)->val.value;
    if (sf==0)
       std::cout << "WARNING::getScaleFactor::The scale factor for " << channelName << " is 0.0 +/- 0.0" << std::endl
            << "This means the process will be killed" << std::endl;
    return sf;
  } else{
    std::cout << "WARNING::getScaleFactor::channelName " << channelName 
	 << " not recognized. Returning -1 for the scale factor." << std::endl 
	 << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
	 << "Please check channel names." << std::endl;
    return -1.;
  }
}//getScaleFactor

// ----------------------------------------------------------------------------
double DefaultValues::getScaleFactor(TString channelName, DEFS::LeptonCat leptonCat) {
  Table table;
  std::multimap<DEFS::LeptonCat,double> sf;
  std::vector<TableRow> tableRows;

  table.parseFromFile(getConfigPath()+std::string("ScaleFactors_13TeV.txt"),"TableCellMixed");
  tableRows = table.getRows();

  for(unsigned int irow=0; irow<tableRows.size(); irow++) {
    if(DEFS::PhysicsProcess::getProcessType(std::string(channelName))!=DEFS::PhysicsProcessType::UNKNOWN)
      assert(tableRows[irow]["ScaleFactor"]);
    if(leptonCat!=DEFS::LeptonCat::none)
      assert(tableRows[irow]["LeptonCat"]);

    if(TString(tableRows[irow].GetName()).CompareTo(channelName)==0 &&
       leptonCat!=DEFS::LeptonCat::none &&
       (DEFS::getLeptonCat(((TableCellText*)tableRows[irow]["LeptonCat"])->text) == leptonCat || 
       DEFS::getLeptonCat(((TableCellText*)tableRows[irow]["LeptonCat"])->text) == DEFS::getLeptonCat("both"))) {
      sf.insert(std::pair<DEFS::LeptonCat,double>(DEFS::getLeptonCat(((TableCellText*)tableRows[irow]["LeptonCat"])->text),((TableCellVal*)tableRows[irow]["ScaleFactor"])->val.value));
    }
    else if(TString(tableRows[irow].GetName()).CompareTo(channelName)==0 &&
       leptonCat==DEFS::LeptonCat::none) {
      sf.insert(std::pair<DEFS::LeptonCat,double>(DEFS::getLeptonCat(((TableCellText*)tableRows[irow]["LeptonCat"])->text),((TableCellVal*)tableRows[irow]["ScaleFactor"])->val.value));
    }
  }

  if(sf.size()==0) {
    std::cout << "WARNING::getScaleFactor::channelName " << channelName << " and LeptonCat " << DEFS::getLeptonCatString(leptonCat)
         << " not recognized. Returning -1 for the scale factor." << std::endl 
         << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
         << "Please check channel names." << std::endl;
    return -1.;
  }
  else if(sf.size()==1 && sf.find(leptonCat)->second==0.0) {
    if(sf.find(DEFS::both)!=sf.end() && sf.find(DEFS::both)->second!=0.0) {
      return sf.find(DEFS::both)->second;
    }
    std::cout << "WARNING::getScaleFactor::The scale factor for " << channelName << " is 0.0 +/- 0.0" << std::endl
         << "This means the process will be killed" << std::endl;
    return sf.find(leptonCat)->second;
  }
  else if(sf.size()>1) {
    if(sf.count(leptonCat)>1) {
      std::cout << "WARNING::getScaleFactor::channelName " << channelName << " and LeptonCat " << DEFS::getLeptonCatString(leptonCat)
           << " returned more than one (" << sf.count(leptonCat) << ") scale factor that matched all of the criteria. Returning -1 for the scale factor." << std::endl 
           << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
           << "Please check channel names." << std::endl;
      return -1.;
    }
    else if(sf.find(DEFS::both)!=sf.end() && sf.find(leptonCat)!=sf.end()) {
      return sf.find(leptonCat)->second;
    }
    else {
      std::cout << "WARNING::getScaleFactor::channelName " << channelName << " and LeptonCat " << DEFS::getLeptonCatString(leptonCat)
           << " returned more than one (" << sf.size() << ") scale factor that matched all of the criteria. Returning -1 for the scale factor." << std::endl 
           << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
           << "Please check channel names." << std::endl;
      return -1.;
    }
  }
  else {
    return sf.find(leptonCat)->second;
  }
}//getScaleFactor

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getMaxEventProbAndError(int probStatIndex, Table* inputTable) {
  Table* table;
  if(!inputTable) {
    table = new Table();
    table->parseFromFile(getConfigPath()+"MaxMeanMedianEventProbs.txt","TableCellMixed");
  }
  else {
    table = inputTable;
  }
  std::vector<double> eventProb;
  std::vector<double> error;
  std::vector<TableRow> tableRows;
  int maxIndex=0;
  std::stringstream ss;
  ss << probStatIndex;
  std::string rowName = ss.str();

  tableRows = table->getRows();
  for(unsigned int irow=0; irow< tableRows.size(); irow++) {
    if(std::string(tableRows[irow].GetName()).compare(rowName)==0) {
      assert(table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"));
      eventProb.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.value);
      error.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.error);
    }
  }

  if(eventProb.size()==0 || error.size()==0) {
    std::cout << "WARNING::getMaxEventProbAndError::No row with name [probStatIndex] " << rowName << " found. " 
         << "Returning -1 for the maximum tEventProb." << std::endl 
         << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
         << "Please check channel names." << std::endl;
    return std::make_pair(-1.0,-1.0);
  }

  for(unsigned int i=0; i<eventProb.size(); i++) {
    if(eventProb[maxIndex] < eventProb[i])
      maxIndex = i;
  }

  if(!inputTable) {
    delete table;
  }

  return std::make_pair(eventProb[maxIndex],error[maxIndex]);

  /*
  TableCell * cell = table.getCellRowColumn(rowName,"MaxEventProb");
  if(cell){
    eventProb = ((TableCellVal*)cell)->val.value;
    error = ((TableCellVal*)cell)->val.error;
    if (eventProb==0)
      std::cout << "WARNING::getMaxEventProbAndError::The maximum tEventProb for " << rowName << " is 0.0 +/- 0.0" << std::endl;
    return std::make_pair(eventProb,error);
  } else{
    std::cout << "WARNING::getMaxEventProbAndError::rowName " << rowName 
   << " not recognized. Returning -1 for the maximum tEventProb." << std::endl 
   << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
   << "Please check channel names." << std::endl;
    return std::make_pair(-1.0,-1.0);
  }
  */
}//getMaxEventProbAndError

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getMaxEventProbAndError(DEFS::PhysicsProcessType ppType,
                                                           std::string meType, Table* inputTable) {

  Table* table;
  if(!inputTable) {
    table = new Table();
    table->parseFromFile(getConfigPath()+"MaxMeanMedianEventProbs.txt","TableCellMixed");
  }
  else {
    table = inputTable;
  }
  std::vector<double> eventProb;
  std::vector<double> error;
  std::vector<TableRow> tableRows;
  int maxIndex=0;

  tableRows = table->getRows();
  for(unsigned int irow=0; irow< tableRows.size(); irow++) {
    assert(table->getCellRowColumn(tableRows[irow].GetName(),"MatrixElementType"));
    if(ppType!=DEFS::PhysicsProcessType::UNKNOWN)
      assert(table->getCellRowColumn(tableRows[irow].GetName(),"PhysicsProcessType"));
    if(((TableCellText*)table->getCellRowColumn(tableRows[irow].GetName(),"MatrixElementType"))->text.compare(meType)==0 &&
       ppType!=DEFS::PhysicsProcessType::UNKNOWN &&
       ((TableCellText*)table->getCellRowColumn(tableRows[irow].GetName(),"PhysicsProcessType"))->text.compare(DEFS::PhysicsProcess::getTypeString(ppType))==0) {
      assert(table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"));
      eventProb.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.value);
      error.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.error);
    }
    else if(((TableCellText*)table->getCellRowColumn(tableRows[irow].GetName(),"MatrixElementType"))->text.compare(meType)==0 &&
       ppType==DEFS::PhysicsProcessType::UNKNOWN) {
      assert(table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"));
      eventProb.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.value);
      error.push_back(((TableCellVal*)table->getCellRowColumn(tableRows[irow].GetName(),"MaxEventProb"))->val.error);
    }
  }

  if(eventProb.size()==0 || error.size()==0) {
    std::cout << "WARNING::getMaxEventProbAndError::No ppType and meType matches found. " 
         << "Returning -1 for the maximum tEventProb." << std::endl 
         << "The events will have the same scale as the MC sample, but on a negative scale." << std::endl 
         << "Please check channel names." << std::endl;
    return std::make_pair(-1.0,-1.0);
  }

  for(unsigned int i=0; i<eventProb.size(); i++) {
    if(eventProb[maxIndex] < eventProb[i])
      maxIndex = i;
  }

  if(!inputTable) {
    delete table;
  }

  return std::make_pair(eventProb[maxIndex],error[maxIndex]);

}//getMaxEventProbAndError

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getMaxEventProbAndError(std::string ppType, std::string meType, Table* inputTable) {
  return getMaxEventProbAndError(DEFS::PhysicsProcess::getProcessType(ppType),meType,inputTable);
}//getMaxEventProbAndError

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getMaxEventProbAndError(std::string meType, Table* inputTable) {

  return getMaxEventProbAndError(DEFS::PhysicsProcessType::UNKNOWN,meType,inputTable);
}//getMaxEventProbAndError

// ----------------------------------------------------------------------------
std::pair<double,double> DefaultValues::getMedianPurity(DEFS::JetBin jetBin, DEFS::LeptonCat leptonCat,
                                                   std::string BDTType, Table* inputTable) {
  Table* table;
  if(!inputTable) {
    table = new Table();
    table->parseFromFile(getConfigPath()+"MedianPurity.txt","TableCellMixed");
  }
  else {
    table = inputTable;
  }
  std::vector<double> BDT;
  std::vector<double> error;
  std::vector<TableRow> tableRows;

  tableRows = table->getRows();
  for(unsigned int irow=0; irow<tableRows.size(); irow++) {
    if(std::string(tableRows[irow].GetName()).compare(DEFS::getJetBinString(jetBin))!=0) continue;
    assert(tableRows[irow]["LeptonCat"]);
    assert(tableRows[irow]["BDTType"]);
    if(std::string(tableRows[irow].GetName()).compare(DEFS::getJetBinString(jetBin))==0 &&
       ((TableCellText*)tableRows[irow]["LeptonCat"])->text.compare(DEFS::getLeptonCatString(leptonCat))==0 &&
       ((TableCellText*)tableRows[irow]["BDTType"])->text.compare(BDTType)==0) {
      assert(tableRows[irow]["Median"]);
      Value val = ((TableCellVal*)tableRows[irow]["Median"])->val;
      BDT.push_back(val.value);
      error.push_back(val.error);
    }
  }

  std::string thisBin = "(JetBin,LeptonCat,BDTType)=("+DEFS::getJetBinString(jetBin)+","+DEFS::getLeptonCatString(leptonCat)+","+BDTType+")";

  if(BDT.size()==0 || error.size()==0) {
    std::cout << "WARNING::getMedianPurity::No " << thisBin << " matches found. " 
         << "Returning -1 for the median purity cut." << std::endl;
    return std::make_pair(-1.0,-1.0);
  }

  if(BDT.size()>1 || error.size()>1) {
    std::cout << "WARNING::getMedianPurity::Multiple combinations of " << thisBin << " categories found. "
         << "Returning the last match found in the configuration file." << std::endl;
  }

  if(!inputTable) {
    delete table;
  }

  return std::make_pair(BDT.back(),error.back());
}//getMedianPurity

// ----------------------------------------------------------------------------
void DefaultValues::getMVAVar(TString filename, std::vector<TString>& MVAV, std::vector<TString>& MVAS)
{
  Table table;
  table.parseFromFile(getConfigPath()+"BDTVariableList.txt", "TableCellMixed");

  int nvar = ((TableCellInt*)table.getCellRowColumn(std::string(filename),"NVar"))->val;
  int nspec = ((TableCellInt*)table.getCellRowColumn(std::string(filename),"NSpec"))->val;

  for(int v = 0; v<nvar; v++) {
    MVAV.push_back(((TableCellText*)table.getCellRowColumn(std::string(filename),Form("%i",v)))->text);
  }
  for(int s = nvar; s<nvar+nspec; s++) {
    MVAS.push_back(((TableCellText*)table.getCellRowColumn(std::string(filename),Form("%i",s)))->text);
  }

  return;
}//getMVAVar

// ----------------------------------------------------------------------------
void DefaultValues::DestroyCanvases() {
   TList* loc = (TList*)gROOT->GetListOfCanvases();
   TListIter itc(loc);
   TObject *o(0);
   while ((o = itc())) delete o;
}

// ----------------------------------------------------------------------------
TObject* DefaultValues::getConfigTObject(TString objectFile, TString oname, TString newName) {
 
   TString basePath = getConfigPath() + objectFile;

   TObject * hnew;
   TString currentDir = gDirectory->GetPathStatic();

   // open the file
   TFile * ifile = TFile::Open(basePath);
   if (!ifile->IsOpen()) {
      std::cout << "\tERROR DefaultValues::getConfigHisto file "+basePath
           << " could not be opened." << std::endl;
      return 0;
   }
   
   // get the histogram from the inside
   TObject * htemp = ifile->Get(oname);

   if(htemp==0) {
      std::cout << "ERROR DefaultValues::getConfigTObject the object " << oname << " was not found in file " << basePath << std::endl;
      assert(htemp!=0);
   }
   
   gDirectory->cd(currentDir);

   // clone it, assigne it to QCDWeightFunc and close the file
   hnew = htemp->Clone(newName);
   ifile->Close();

   return hnew;

}

// ----------------------------------------------------------------------------
TH1* DefaultValues::getConfigTH1(TString histoFile, TString hname, TString newName) {

   TH1* h = (TH1*) getConfigTObject(histoFile, hname, newName);

   if(h==0) {
      std::cout << "ERROR DefaultValues::getConfigTH1 the object found in file " << histoFile << "cannot be cast to a TH1*" << std::endl;
      assert(h!=0);
   }

   return h;

}

// ----------------------------------------------------------------------------
TH2* DefaultValues::getConfigTH2(TString histoFile, TString hname, TString newName) {

   TH2* h = (TH2*) getConfigTObject(histoFile, hname, newName);

   if(h==0) {
      std::cout << "ERROR DefaultValues::getConfigTH2 the object found in file " << histoFile << "cannot be cast to a TH2*" << std::endl;
      assert(h!=0);
   }

   return h;

}

// ----------------------------------------------------------------------------
TH2* DefaultValues::Rebin2D(TH2* old, Int_t nxgroup, Int_t nygroup, const char*newname, const Double_t *xbins, const Double_t *ybins, TString Options) {

  Options.ToUpper();
  bool verbose = false;
  if(Options.Contains("VERBOSE")) {
    verbose = true;
  }

   Int_t nxbins   = old->GetXaxis()->GetNbins();
   Double_t xmin  = old->GetXaxis()->GetXmin();
   Double_t xmax  = old->GetXaxis()->GetXmax();
   Int_t nybins   = old->GetYaxis()->GetNbins();
   Double_t ymin  = old->GetYaxis()->GetXmin();
   Double_t ymax  = old->GetYaxis()->GetXmax();
   if ((nxgroup <= 0) || (nxgroup > nxbins)) {
      Error("Rebin", "Illegal value of nxgroup=%d",nxgroup);
      return 0;
   }
   if ((nygroup <= 0) || (nygroup > nybins)) {
      Error("Rebin", "Illegal value of nygroup=%d",nygroup);
      return 0;
   }

   if (!newname && (xbins || ybins)) {
      Error("Rebin","if xbins or ybins are specified, newname must be given");
      return 0;
   }

   Int_t newbinsx = nxbins/nxgroup;
   Int_t newbinsy = nybins/nygroup;
   if (!xbins) {
      Int_t nbg = nxbins/nxgroup;
      if (nbg*nxgroup != nxbins) {
         Warning("Rebin", "nxgroup=%d is not an exact divider of nxbins=%d.",nxgroup,nxbins);
      }
   }
   else {
   // in the case that xbins is given (rebinning in variable bins), ngroup is
   // the new number of bins and number of grouped bins is not constant.
   // when looping for setting the contents for the new histogram we
   // need to loop on all bins of original histogram.  Then set ngroup=nbins
      newbinsx = nxgroup;
      nxgroup = nxbins;
   }
   if (!ybins) {
      Int_t nbg = nybins/nygroup;
      if (nbg*nygroup != nybins) {
         Warning("Rebin", "nygroup=%d is not an exact divider of nybins=%d.",nygroup,nybins);
      }
   }
   else {
   // in the case that xbins is given (rebinning in variable bins), ngroup is
   // the new number of bins and number of grouped bins is not constant.
   // when looping for setting the contents for the new histogram we
   // need to loop on all bins of original histogram.  Then set ngroup=nbins
      newbinsy = nygroup;
      nygroup = nybins;
   }

   // Save old bin contents into a new array
   Double_t entries = old->GetEntries();
   Double_t* oldBins = new Double_t[(nxbins+2)*(nybins+2)];
   Int_t i, j, binx, biny;
   for (binx=0;binx<nxbins+2;binx++) {
     for (biny=0;biny<nybins+2;biny++) { 
         oldBins[binx*(nybins+2)+biny] = old->GetBinContent(binx,biny);
     }
   }
   Double_t* oldErrors = 0;
   if (old->GetSumw2N() != 0) {
      oldErrors = new Double_t[(nxbins+2)*(nybins+2)];
      for (binx=0;binx<nxbins+2;binx++) {
          for (biny=0;biny<nybins+2;biny++) {
            oldErrors[binx*(nybins+2)+biny] = old->GetBinError(binx,biny);
          }
      }
   }

   // create a clone of the old histogram if newname is specified
   TH2 *hnew = old;
   if ((newname && strlen(newname) > 0) || xbins || ybins) {
      hnew = (TH2*)old->Clone(newname);
   }

   //reset kCanRebin bit to avoid a rebinning in SetBinContent
   //hnew->TestBit(old->kCanRebin);
   //hnew->SetBit(old->kCanRebin,0);

   // save original statistics
   const Int_t kNstat2D = 7;
   Double_t stat[kNstat2D];
   old->GetStats(stat);
   bool resetStat = false;

   // change axis specs and rebuild bin contents array::RebinAx
   if(!xbins && (newbinsx*nxgroup != nxbins)) {
      xmax = old->GetXaxis()->GetBinUpEdge(newbinsx*nxgroup);
      resetStat = true; //stats must be reset because top bins will be moved to overflow bin
   }
   if(!ybins && (newbinsy*nygroup != nybins)) {
      ymax = old->GetYaxis()->GetBinUpEdge(newbinsy*nygroup);
      resetStat = true; //stats must be reset because top bins will be moved to overflow bin
   }
   // save the TAttAxis members (reset by SetBins)
   Int_t    xnDivisions  = old->GetXaxis()->GetNdivisions();
   Color_t  xaxisColor   = old->GetXaxis()->GetAxisColor();
   Color_t  xlabelColor  = old->GetXaxis()->GetLabelColor();
   Style_t  xlabelFont   = old->GetXaxis()->GetLabelFont();
   Float_t  xlabelOffset = old->GetXaxis()->GetLabelOffset();
   Float_t  xlabelSize   = old->GetXaxis()->GetLabelSize();
   Float_t  xtickLength  = old->GetXaxis()->GetTickLength();
   Float_t  xtitleOffset = old->GetXaxis()->GetTitleOffset();
   Float_t  xtitleSize   = old->GetXaxis()->GetTitleSize();
   Color_t  xtitleColor  = old->GetXaxis()->GetTitleColor();
   Style_t  xtitleFont   = old->GetXaxis()->GetTitleFont();
   Int_t    ynDivisions  = old->GetYaxis()->GetNdivisions();
   Color_t  yaxisColor   = old->GetYaxis()->GetAxisColor();
   Color_t  ylabelColor  = old->GetYaxis()->GetLabelColor();
   Style_t  ylabelFont   = old->GetYaxis()->GetLabelFont();
   Float_t  ylabelOffset = old->GetYaxis()->GetLabelOffset();
   Float_t  ylabelSize   = old->GetYaxis()->GetLabelSize();
   Float_t  ytickLength  = old->GetYaxis()->GetTickLength();
   Float_t  ytitleOffset = old->GetYaxis()->GetTitleOffset();
   Float_t  ytitleSize   = old->GetYaxis()->GetTitleSize();
   Color_t  ytitleColor  = old->GetYaxis()->GetTitleColor();
   Style_t  ytitleFont   = old->GetYaxis()->GetTitleFont();

   if(!xbins && !ybins) { //&& (old->GetXaxis()->GetXbins()->GetSize() > 0) && (old->GetYaxis()->GetXbins()->GetSize() > 0)){ // variable bin sizes
      if (verbose) std::cout << "Case 1" << std::endl;
      Double_t *binsx = new Double_t[newbinsx+1];
      Double_t *binsy = new Double_t[newbinsy+1];
      for(i = 0; i <= newbinsx; ++i) {
        binsx[i] = old->GetXaxis()->GetBinLowEdge(1+i*nxgroup);
      }
      for(i = 0; i <= newbinsy; ++i) {
        binsy[i] = old->GetYaxis()->GetBinLowEdge(1+i*nygroup);
      }
      hnew->SetBins(newbinsx,binsx,newbinsy,binsy); //this also changes errors array (if any)
      delete [] binsx;
      delete [] binsy;
   } else if (!xbins && ybins) { //&& (old->GetXaxis()->GetXbins()->GetSize() > 0)) {
      if (verbose) std::cout << "Case 2" << std::endl;
      Double_t *binsx = new Double_t[newbinsx+1];
      for(i = 0; i <= newbinsx; ++i) {
        binsx[i] = old->GetXaxis()->GetBinLowEdge(1+i*nxgroup);
      }
      hnew->SetBins(newbinsx,binsx,newbinsy,ybins); //this also changes errors array (if any)
      delete [] binsx;
   } else if (!ybins && xbins) {//&& (old->GetYaxis()->GetXbins()->GetSize() > 0)) {
      if (verbose) std::cout << "Case 3" << std::endl;
      Double_t *binsy = new Double_t[newbinsy+1];
      for(i = 0; i <= newbinsy; ++i) {
        binsy[i] = old->GetYaxis()->GetBinLowEdge(1+i*nygroup);
      }
      hnew->SetBins(newbinsx,xbins,newbinsy,binsy); //this also changes errors array (if any)
      delete [] binsy;
   } else if (xbins && ybins) {
      if (verbose) std::cout << "Case 4" << std::endl;
      hnew->SetBins(newbinsx,xbins,newbinsy,ybins);
   } else {
      if (verbose) std::cout << "Case 5" << std::endl;
      hnew->SetBins(newbinsx,xmin,xmax,newbinsy,ymin,ymax);
   }

   // Restore axis attributes
   old->GetXaxis()->SetNdivisions(xnDivisions);
   old->GetXaxis()->SetAxisColor(xaxisColor);
   old->GetXaxis()->SetLabelColor(xlabelColor);
   old->GetXaxis()->SetLabelFont(xlabelFont);
   old->GetXaxis()->SetLabelOffset(xlabelOffset);
   old->GetXaxis()->SetLabelSize(xlabelSize);
   old->GetXaxis()->SetTickLength(xtickLength);
   old->GetXaxis()->SetTitleOffset(xtitleOffset);
   old->GetXaxis()->SetTitleSize(xtitleSize);
   old->GetXaxis()->SetTitleColor(xtitleColor);
   old->GetXaxis()->SetTitleFont(xtitleFont);
   old->GetYaxis()->SetNdivisions(ynDivisions);
   old->GetYaxis()->SetAxisColor(yaxisColor);
   old->GetYaxis()->SetLabelColor(ylabelColor);
   old->GetYaxis()->SetLabelFont(ylabelFont);
   old->GetYaxis()->SetLabelOffset(ylabelOffset);
   old->GetYaxis()->SetLabelSize(ylabelSize);
   old->GetYaxis()->SetTickLength(ytickLength);
   old->GetYaxis()->SetTitleOffset(ytitleOffset);
   old->GetYaxis()->SetTitleSize(ytitleSize);
   old->GetYaxis()->SetTitleColor(ytitleColor);
   old->GetYaxis()->SetTitleFont(ytitleFont);

   // copy merged bin contents (ignore under/overflows)
   // Start merging only once the new lowest edge is reached
   if (nxgroup != 1 || nygroup != 1) {
     Int_t startbinx = 1;
     Int_t startbiny = 1;
     const Double_t newxmin = hnew->GetXaxis()->GetBinLowEdge(1);
     const Double_t newymin = hnew->GetYaxis()->GetBinLowEdge(1);
     while( old->GetXaxis()->GetBinCenter(startbinx) < newxmin && startbinx <= nxbins ) {
      startbinx++;
    }
    while( old->GetYaxis()->GetBinCenter(startbiny) < newymin && startbiny <= nybins ) {
      startbiny++;
    }
    Int_t oldbinx = startbinx;
    Int_t oldbiny = startbiny;
    if(verbose) {
      std::cout << "startbinx = " << oldbinx << std::endl;
      std::cout << "startbiny = " << oldbiny << std::endl;
    }

    Double_t binContent, binError;

    for (binx = 1;binx<=newbinsx;binx++) {
      oldbiny = startbiny;
      Int_t ixmax = nxgroup;
      Double_t xbinmax = hnew->GetXaxis()->GetBinUpEdge(binx);
      for (biny = 1;biny<=newbinsy;biny++) {
        binContent = 0;
        binError   = 0;
        Int_t iymax = nygroup;
        Double_t ybinmax = hnew->GetYaxis()->GetBinUpEdge(biny);
        for (i=0;i<nxgroup;i++) {
          if (verbose) std::cout << "i = " << i << std::endl;
          if( ((hnew == old) && (oldbinx+i > nxbins)) || ((hnew != old) && (old->GetXaxis()->GetBinCenter(oldbinx+i) > xbinmax))) {
            ixmax = i;
            if(verbose) {
              std::cout << "WARNING::Before X Break!!!!" << std::endl;
              //std::cout << "old->GetXaxis()->GetBinCenter(oldbinx+i) > xbinmax\t" << (old->GetXaxis()->GetBinCenter(oldbinx+i) > xbinmax) << std::endl;
              //std::cout << "old->GetXaxis()->GetBinCenter(oldbinx+i) = " << old->GetXaxis()->GetBinCenter(oldbinx+i) << std::endl;
              //std::cout << "xbinmax = " << xbinmax << std::endl;
              //std::cout << "oldbinx = " << oldbinx << std::endl;
              //std::cout << "i = " << i << std::endl;
              //std::cout << "nxgroup = " << nxgroup << std::endl;
            }
            break;
          }
          for (j=0;j<nygroup;j++) {
            if (verbose) std::cout << "j = " << j << std::endl;
            if( ((hnew == old) && (oldbiny+j > nybins)) || ((hnew != old) && (old->GetYaxis()->GetBinCenter(oldbiny+j) > ybinmax))) {
              iymax = j;
              if(verbose) {
                std::cout << "WARNING::Before Y Break!!!!" << std::endl;
              //std::cout << "hnew==old = " << (hnew==old) << std::endl;
              //std::cout << "oldbinx+i > nxbins || oldbiny+j > nybins\t" << (oldbinx+i > nxbins || oldbiny+j > nybins) << std::endl;
              //std::cout << "old->GetYaxis()->GetBinCenter(oldbiny+j) > ybinmax\t" << (old->GetYaxis()->GetBinCenter(oldbiny+j) > ybinmax) << std::endl;
              //std::cout << "old->GetYaxis()->GetBinCenter(oldbiny+j) = " << old->GetYaxis()->GetBinCenter(oldbiny+j) << std::endl;
              //std::cout << "ybinmax = " << ybinmax << std::endl;
              //std::cout << "oldbiny = " << oldbiny << std::endl;
              //std::cout << "j = " << j << std::endl;
              //std::cout << "nygroup = " << nygroup << std::endl;
              }
              break;
            }
            binContent += oldBins[(oldbiny+j) + (oldbinx+i)*(nybins+2)];
            if (oldErrors) binError += oldErrors[(oldbiny+j)+(oldbinx+i)*(nybins+2)]*oldErrors[(oldbiny+j)+(oldbinx+i)*(nybins+2)];
          }
        }
        if (verbose) std::cout << "binx = " << binx << "\tbiny = " << biny << std::endl;
        hnew->SetBinContent(binx,biny,binContent);
        if (oldErrors) hnew->SetBinError(binx,biny,TMath::Sqrt(binError));
        oldbiny += iymax;
      }
      oldbinx += ixmax;
    }

    //  recompute under/overflow contents in y for the new  x bins 
    Double_t binContent0, binContent2;
    Double_t binError0, binError2;
    oldbinx = 1;
    for (binx = 1; binx<=newbinsx; binx++) {
     binContent0 = binContent2 = 0;
     binError0 = binError2 = 0;
     for (i=0; i<nxgroup; i++) {
      if (oldbinx+i > nxbins) break;
            //N.B  convention used for index is opposite than TH1::GetBin(ix,iy)
            Int_t ufbin = (oldbinx+i)*(nybins+2);   // index for y underflow bins 
            Int_t ofbin = (oldbinx+i)*(nybins+2) + (nybins+1);   // index for y overflow bins 
            binContent0 += oldBins[ufbin];
            binContent2 += oldBins[ofbin];
            if (oldErrors)  { 
             binError0 += oldErrors[ufbin] * oldErrors[ufbin];
             binError2 += oldErrors[ofbin] * oldErrors[ofbin];
           }
         }
         hnew->SetBinContent(binx,0,binContent0);
         hnew->SetBinContent(binx,newbinsy+1,binContent2);
         if (oldErrors) { 
          hnew->SetBinError(binx,0,TMath::Sqrt(binError0));
          hnew->SetBinError(binx,newbinsy+1,TMath::Sqrt(binError2) );
        }
        oldbinx += nxgroup;
      }

      //  recompute under/overflow contents in x for the new y bins
      for (biny = 1; biny<=newbinsy; biny++) {
       binContent0 = binContent2 = 0;
       binError0 = binError2 = 0;
       for (i=0; i<nygroup; i++) {
        if (oldbiny+i > nybins) break;
            Int_t ufbin = (oldbiny+i);   // global index for x underflow bins 
            Int_t ofbin = (nxbins+1)*(nybins+2) + (oldbiny+i);   // global index for x overflow bins 
            binContent0 += oldBins[ufbin];
            binContent2 += oldBins[ofbin];
            if (oldErrors)  { 
             binError0 += oldErrors[ufbin] * oldErrors[ufbin];
             binError2 += oldErrors[ofbin] * oldErrors[ofbin];
           }
         }
         hnew->SetBinContent(0,biny,binContent0);
         hnew->SetBinContent(newbinsx+1,biny,binContent2);
         if (oldErrors) { 
          hnew->SetBinError(0,biny, TMath::Sqrt(binError0));
          hnew->SetBinError(newbinsx+1, biny, TMath::Sqrt(binError2));
        }
        oldbiny += nygroup;
      }
    }

   // restore statistics and entries modified by SetBinContent
   hnew->SetEntries(entries);
   if (!resetStat) hnew->PutStats(stat);

   delete [] oldBins;
   if (oldErrors) delete [] oldErrors;
   return hnew;
}

// ----------------------------------------------------------------------------
void DefaultValues::Rebin2DTest(TString Options) {
  /*
  Options:
    Verbose
  */
  TH2D* h = new TH2D("h","h",4,0,40,4,0,40);
  h->Sumw2();
  h->Fill(5,5);
  h->Fill(15,15);
  h->Fill(25,25);
  h->Fill(35,25);
  h->Fill(35,10);
  h->Fill(35,10);
  h->Fill(35,10);
  h->Fill(-1,-1);
  h->Fill(50,50);
  h->Fill(-1,50);
  h->Fill(50,-1);
  Double_t x[3] = {0,30,40};
  TH2D* hh = (TH2D*)Rebin2D(h,2,2,"test",x,0,Options);
  //Print options: range (no uf/of), all (with uf/of)
  h->Print("all");
  hh->Print("all");
}


// ----------------------------------------------------------------------------
void DefaultValues::printSummary(TBenchmark* bench, int precision, Float_t &rt, Float_t &ct, std::vector<std::string> timers) {
  // Prints a summary of all benchmarks.

   rt = 0;
   ct = 0;

   for (unsigned int i=0;i<timers.size();i++) {
      std::cout << Form("%-10s: Real Time = %6.*f seconds Cpu Time = %6.*f seconds",timers[i].c_str(),
                   precision,bench->GetRealTime(timers[i].c_str()),precision,bench->GetCpuTime(timers[i].c_str())) << std::endl;
      rt += bench->GetRealTime(timers[i].c_str());
      ct += bench->GetCpuTime(timers[i].c_str());
   }
   std::cout << Form("%-10s: Real Time = %6.*f seconds Cpu Time = %6.*f seconds","TOTAL",precision,rt,precision,ct) << std::endl;

}
