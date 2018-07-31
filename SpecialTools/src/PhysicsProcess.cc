// Name: PhysicsProcess.cc
// Author: Travis Lamb

// This class will eventually replace an older Physics class. It is a base class that simply holds data members.

#include "CUAnalysis/SpecialTools/interface/PhysicsProcess.hh"

// ##################################################
// ################ PHYSICS PROCESS #################
// ##################################################

PhysicsProcess::PhysicsProcess (string procName,
                                string groupingName,
                                string fileNameTmp,
                                string treeName,
                                bool debug):
name(procName),
groupName(groupingName),
fileName(fileNameTmp),
chain (new TChain(treeName.c_str()))
{
    cout << "PhysicsProcess:PhysicsProcess Getting files for the process \e[4m" << name << "\e[24m" << endl;

    // Initial sanity check
    if (chain == nullptr) {
        cout << "ERROR PhysicsProcess::PhysicsProcess() The chain is null!" << endl;
        return;
    }

    // Enable a thread that will effectively prefetch the next cache chunk while processing is going on
    gEnv->SetValue("TFile.AsyncPrefetching", 1);

    TFile* file = nullptr;
    int file_count(0);
    TString currentDir = gDirectory->GetPathStatic();
    if (fileName.find("*")==string::npos && fileName.find("root://cmseos.fnal.gov/")!=string::npos) {
        if(debug) cout << "\tAdding " << fileName << endl;
        file_count = chain->Add(fileName.c_str());
    }
    #if(has_xrdcl)
        else {
            XrdCl::DirectoryList *response;
            XrdCl::DirListFlags::Flags flags = XrdCl::DirListFlags::None;

            string redirector = "root://cmseos.fnal.gov/";
            string url_string = fileName.substr(0,fileName.find(redirector)+redirector.size());
            string just_file = fileName.substr(fileName.rfind("/")+1);
            string input = fileName.substr(redirector.size(),fileName.size()-just_file.size()-redirector.size());

            XrdCl::URL url(url_string);
            XrdCl::FileSystem fs(url);
            fs.DirList(input,flags,response);
            for(auto iresp=response->Begin(); iresp!=response->End(); iresp++) {
                if((*iresp)->GetName().find(".root")!=std::string::npos && match(just_file.c_str(),(*iresp)->GetName().c_str())) {
                    if(debug) cout << "\tAdding " << url_string << input << (*iresp)->GetName() << endl;
                    file_count = chain->Add((url_string+input+(*iresp)->GetName()).c_str());
                }
            }
        }
    #else
        cout << "Can't find the header file \"xrootd/XrdCl/XrdClFileSystem.hh\" and thus can't use xrootd." << endl;
        return;
    #endif

    // Post chain making sanity checks
    TChainElement* chEl = (TChainElement*)chain->GetListOfFiles()->First();
    file = TFile::Open(chEl->GetTitle(),"READ");
    if (!file) {
        cout << "ERROR PhysicsProcess::PhysicsProcess() could not open file " << fileName << endl;
        return;
    }
    if (file_count==0){ cout<<"No files found! Aborting."<<endl; return; }

    // Try to speed up the reading of the chain
    TTreeCache::SetLearnEntries(100);
    chain->SetCacheSize(200*1024*1024); //200MB cache size
    chain->SetCacheEntryRange(0, chain->GetEntries());
    chain->AddBranchToCache("*", true);
    chain->StopCacheLearningPhase();

    // Return the working directory to its initial state
    gDirectory->cd(currentDir);

    PhysParMap blankD;
    PhysParMapUI blankUI;
    for(unsigned int i = 0; i<DEFS::nLeptonCat; i++) {
        blankD[(DEFS::LeptonCat)i] = 0.0;
        blankUI[(DEFS::LeptonCat)i] = 1;
    }
    sigma = blankD;
    branching_ratio = blankD;
    intLum = blankD;
    initial_events = blankUI;
    scaleFactor = blankD;
}

void PhysicsProcess::setPhysicsParameters(PhysParMap cross_section, PhysParMap lum, PhysParMap br, PhysParMapUI in_ev, PhysParMap sf){
   for(PhysParMap::iterator it = cross_section.begin(); it!=cross_section.end(); it++) {
      sigma[it->first] = it->second;
   }
   for(PhysParMap::iterator it = br.begin(); it!=br.end(); it++) {
      branching_ratio[it->first] = it->second;
   }
   for(PhysParMap::iterator it = lum.begin(); it!=lum.end(); it++) {
      intLum[it->first] = it->second;
   }
   for(PhysParMapUI::iterator it = in_ev.begin(); it!=in_ev.end(); it++) {
      initial_events[it->first] = it->second;
   }
   for(PhysParMap::iterator it = sf.begin(); it!=sf.end(); it++) {
      scaleFactor[it->first] = it->second;
   }
}

//Taken from https://www.geeksforgeeks.org/wildcard-character-matching/
bool PhysicsProcess::match(const char *first, const char * second) {
    // If we reach at the end of both strings, we are done
    if (*first == '\0' && *second == '\0')
        return true;
 
    // Make sure that the characters after '*' are present
    // in second string. This function assumes that the first
    // string will not contain two consecutive '*'
    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return false;
 
    // If the first string contains '?', or current characters
    // of both strings match
    if (*first == '?' || *first == *second)
        return match(first+1, second+1);
 
    // If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
    if (*first == '*')
        return match(first+1, second) || match(first, second+1);
    return false;
}

vector<string> PhysicsProcess::getListOfFiles(bool print, string appendChar) {
    if(chain->GetNtrees()<1 || chain->GetNtrees()>1e6) {
        cout << "WARNING::PhysicsProcess::getListOfFiles There are either no trees in the chain or more than 1e6." << endl
             << " It is likely there is something wrong with the chain." << endl;
        return {};
    }

    TObjArray* array = chain->GetListOfFiles();
    unsigned int nentries = array->GetEntries();
    vector<string> files;
    files.reserve(nentries);
 
    int len = 0;
    if(print) {
        stringstream ss;
        ss << nentries;
        len = ss.str().size();
        printf("%s%*s | Files\n",appendChar.c_str(),len,"#");
        printf("%s%s\n",appendChar.c_str(),std::string(len+3+string(array->At(0)->GetTitle()).size(), '-').c_str());
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

PlotterPhysicsProcess::PlotterPhysicsProcess (string procName,
                                              string groupingName,
                                              string fileNameTmp,
                                              string treeName,
                                              int color_,
                                              int marker_):
   PhysicsProcess(procName, groupingName, fileNameTmp, treeName), color(color_), marker(marker_) {}
