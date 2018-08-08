#ifndef StringUtilities_HH
#define StringUtilities_HH

#include <string>
#include <algorithm>

namespace utilities {

    // ----------------------------------------------------------------------------
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

    // ----------------------------------------------------------------------------
    // find substring (case insensitive)
    template<typename T>
	inline int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
	{
		typename T::const_iterator it = std::search( str1.begin(), str1.end(), 
		                                             str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
		if ( it != str1.end() ) return it - str1.begin();
        else return -1; // not found
    }

    // ----------------------------------------------------------------------------
    // Remove a substring p from a given string s
    template<typename T>
    inline void removeSubstrs(std::basic_string<T>& s, const std::basic_string<T>& p) {
    	typename std::basic_string<T>::size_type n = p.length();
    	for (typename std::basic_string<T>::size_type i = s.find(p); i != std::basic_string<T>::npos; i = s.find(p))
    		s.erase(i, n);
    }

    // ----------------------------------------------------------------------------
    // Taken from https://www.geeksforgeeks.org/wildcard-character-matching/
    // A function that checks if two given strings (character arrays) match. The first string may contain wildcard characters.
    inline bool match(const char *first, const char * second) {
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
}
#endif