#ifndef VectorUtilities_HH
#define VectorUtilities_HH

#include "TString.h"
#include <string>
#include <vector>

namespace utilities {

    // ----------------------------------------------------------------------------
    // Returns the index of the location of b within a, or -1 if b is not found in a
    template<typename T>
    inline int vfind(std::vector<T> a, T b) {
        for (unsigned int i=0; i<a.size(); i++) {
            if (a[i]==b) return i;
        }
        return -1;
    }
    template<>
    inline int vfind<std::string>(std::vector<std::string> a, std::string b) {
        for (unsigned int i=0; i<a.size(); i++) {
            if (a[i].compare(b)==0) return i;
        }
        return -1;
    }
    template<>
    inline int vfind<TString>(std::vector<TString> a, TString b) {
        for (unsigned int i=0; i<a.size(); i++) {
            if (a[i].CompareTo(b)==0) return i;
        }
        return -1;
    }

    // ----------------------------------------------------------------------------
    // Returns the indices within "find_in" for several search values in "to_find." Returns an empty std::vector otherwise.
    inline std::vector<int> vfind_many(std::vector<std::string> find_in, std::vector<std::string> to_find, bool debug = false) {
        std::vector<int> indices;
        for(unsigned h = 0; h < to_find.size(); h++){
            std::vector<std::string>::iterator lb = lower_bound(find_in.begin(),find_in.end(),to_find[h]);
            if(debug){
                cout << to_find[h] << " " << *lb << endl;
            }
            if(lb != find_in.end() && lb->find(to_find[h]) != std::string::npos){
                indices.push_back(distance(find_in.begin(),lb));
            }
        }
        if(debug){
            for(unsigned h = 0; h < indices.size(); h++){
                cout << to_find[h] << ": " << indices[h] << endl;
            }
        }
        return indices;
    }
}

#endif