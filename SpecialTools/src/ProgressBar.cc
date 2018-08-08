#include "CUAnalysis/SpecialTools/interface/ProgressBar.hh"

//-----------------------------------------------------------------------------
void ProgressBar::loadbar(unsigned int x, unsigned int n, unsigned int w, std::string prefix, std::pair<float,float> time) {
    if ( (x != n) && (x % (n/100) != 0) ) return;
 
    float ratio  =  x/(float)n;
    int   c      =  ratio * w;

    std::cout << prefix << " [";
    for (int x=0; x<c; x++) std::cout << "=";
    for (unsigned int x=c; x<w; x++) std::cout << " ";
    if(time.first == 0.0 && time.second == 0.0)
        std::cout << "] " << std::setw(3) << (int)(ratio*100) << "% (" << x << "/" << n << ")\r" << std::flush;
    else
        std::cout << "] " << std::setw(3) << (int)(ratio*100) << "% (" << x << "/" << n << ")\n"
                  << "  (CPU: " << time.first << "s | Real: " << time.second << "s) (CPU: "
                  << n/time.first << "<evts>/s | Real: " << n/time.second << "<evts>/s)\r" << std::flush;
}//loadbar

//-----------------------------------------------------------------------------
// Process has done i out of n rounds,
// and we want a bar of width w and resolution r.
void ProgressBar::loadBar(int x, int n, int r, int w) {
    // Only update r times.
    if ( x % (n/r) != 0 ) return;
 
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
 
    // Show the load bar.
    for (int x=0; x<c; x++)
        printf("=");
 
    for (int x=c; x<w; x++)
        printf(" ");
 
    // ANSI Control codes to go back to the
    // previous line and clear it.
    //printf("]\n\033[F\033[J");
    printf("]\n33[1A33[2K");
}

//ClassImp(ProgressBar)
