#ifndef PROGRESSBAR_HH
#define PROGRESSBAR_HH

///////////////////////////////////////////////////////////////////
// ProgressBar.hh
// --------------
//
//            03/19/2014 Alexx Perloff  <aperloff@physics.tamu.edu>
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>

class ProgressBar {
public:

  	// C Versions
  	static void loadbar(unsigned int x, unsigned int n, unsigned int w = 50, std::string prefix = "",
  	                    std::pair<float,float> time = std::make_pair(0.0,0.0));
  	// C++ Version
  	static void loadBar(int x, int n, int r, int w);

};
#endif
