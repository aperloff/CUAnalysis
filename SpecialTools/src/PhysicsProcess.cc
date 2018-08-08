// Name: PhysicsProcess.cc
// Author: Travis Lamb

// This class will eventually replace an older Physics class. It is a base class that simply holds data members.

#include "CUAnalysis/SpecialTools/interface/PhysicsProcess.hh"

// ##################################################
// ################ PHYSICS PROCESS #################
// ##################################################

PhysicsProcess::PhysicsProcess (std::string procName,
                                std::string groupingName,
                                std::string fileNameTmp,
                                std::string treeName,
                                bool debug):
name(procName),
groupName(groupingName),
fileName(fileNameTmp),
chain (new TChain(treeName.c_str()))
{
    std::cout << "PhysicsProcess:PhysicsProcess Getting files for the process \e[4m" << name << "\e[24m" << std::endl;

    // Initial sanity check
    if (chain == nullptr) {
        std::cout << "ERROR PhysicsProcess::PhysicsProcess() The chain is null!" << std::endl;
        return;
    }

    // Enable a thread that will effectively prefetch the next cache chunk while processing is going on
    gEnv->SetValue("TFile.AsyncPrefetching", 1);

    TFile* file = nullptr;
    int file_count(0);
    std::string currentDir = gDirectory->GetPathStatic();
    if (fileName.find("*")==std::string::npos && fileName.find("root://cmseos.fnal.gov/")!=std::string::npos) {
        if(debug) std::cout << "\tAdding " << fileName << std::endl;
        file_count = chain->Add(fileName.c_str());
    }
    #if(has_xrdcl)
        else {
            XrdCl::DirectoryList *response;
            XrdCl::DirListFlags::Flags flags = XrdCl::DirListFlags::None;

            std::string redirector = "root://cmseos.fnal.gov/";
            std::string url_string = fileName.substr(0,fileName.find(redirector)+redirector.size());
            std::string just_file = fileName.substr(fileName.rfind("/")+1);
            std::string input = fileName.substr(redirector.size(),fileName.size()-just_file.size()-redirector.size());

            XrdCl::URL url(url_string);
            XrdCl::FileSystem fs(url);
            fs.DirList(input,flags,response);
            for(auto iresp=response->Begin(); iresp!=response->End(); iresp++) {
                if((*iresp)->GetName().find(".root")!=std::string::npos && utilities::match(just_file.c_str(),(*iresp)->GetName().c_str())) {
                    if(debug) std::cout << "\tAdding " << url_string << input << (*iresp)->GetName() << std::endl;
                    file_count = chain->Add((url_string+input+(*iresp)->GetName()).c_str());
                }
            }
        }
    #else
        std::cout << "Can't find the header file \"xrootd/XrdCl/XrdClFileSystem.hh\" and thus can't use xrootd." << std::endl;
        return;
    #endif

    // Post chain making sanity checks
    TChainElement* chEl = (TChainElement*)chain->GetListOfFiles()->First();
    file = TFile::Open(chEl->GetTitle(),"READ");
    if (!file) {
        std::cout << "ERROR PhysicsProcess::PhysicsProcess() could not open file " << fileName << std::endl;
        return;
    }
    if (file_count==0){ std::cout<<"No files found! Aborting."<<std::endl; return; }

    // Try to speed up the reading of the chain
    TTreeCache::SetLearnEntries(100);
    chain->SetCacheSize(200*1024*1024); //200MB cache size
    chain->SetCacheEntryRange(0, chain->GetEntries());
    chain->AddBranchToCache("*", true);
    chain->StopCacheLearningPhase();

    // Return the working directory to its initial state
    gDirectory->cd(currentDir.c_str());
}

std::vector<std::string> PhysicsProcess::getListOfFiles(bool print, std::string appendChar) {
    if(chain->GetNtrees()<1 || chain->GetNtrees()>1e6) {
        std::cout << "WARNING::PhysicsProcess::getListOfFiles There are either no trees in the chain or more than 1e6." << std::endl
             << " It is likely there is something wrong with the chain." << std::endl;
        return {};
    }

    TObjArray* array = chain->GetListOfFiles();
    unsigned int nentries = array->GetEntries();
    std::vector<std::string> files;
    files.reserve(nentries);
 
    int len = 0;
    if(print) {
        std::stringstream ss;
        ss << nentries;
        len = ss.str().size();
        printf("%s%*s | Files\n",appendChar.c_str(),len,"#");
        printf("%s%s\n",appendChar.c_str(),std::string(len+3+std::string(array->At(0)->GetTitle()).size(), '-').c_str());
    }

    for(unsigned int i=0; i<nentries; i++) {
        files.push_back(array->At(i)->GetTitle());
        if(print) {
            printf("%s%*i | %s\n",appendChar.c_str(),len,i,files.back().c_str());
        }
    }

    return files;
}

// ##################################################
// ############ COLORED PHYSICS PROCESS #############
// ##################################################

PlotterPhysicsProcess::PlotterPhysicsProcess (std::string procName,
                                              std::string groupingName,
                                              std::string fileNameTmp,
                                              std::string treeName,
                                              int color_,
                                              int marker_):
   PhysicsProcess(procName, groupingName, fileNameTmp, treeName), color(color_), marker(marker_) {}
