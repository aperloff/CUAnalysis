#ifndef PLOTS_DEF
#define PLOTS_DEF

// ROOT libraries
#include "TStyle.h"
#include "TROOT.h"
#include "TFile.h"
#include "TKey.h"
#include "TChain.h"
#include "TPad.h"
#include "TFrame.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TString.h"
#include "TAxis.h"
#include "TGaxis.h"

// Our libraries
#include "CUAnalysis/SpecialTools/interface/PhysicsProcess.hh"
#include "CUAnalysis/SpecialTools/interface/Defs.hh"
#include "CUAnalysis/SpecialTools/interface/DefaultValues.hh"
#include "CUAnalysis/Tools/interface/Style.hh"

// C++ libraries
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>

// ##################################################
// ################### PLOT CLASS ###################
// ##################################################

// A basic class that holds all of the process histograms for a given plot. 
class Plot: public TNamed
{
public :

   // Constructor
   Plot() : scaled(false) { }
   Plot(TH1* templateHisto_) : templateHisto(templateHisto_), scaled(false) { }
   ~Plot() {};

   // Create a new histo here
   void prepareToFillProcess(TString suffix, TString groupName);
      
   // Fill the last histo here
   void Fill(double x, double w = 1);
   void Fill(double x, double y, double w);
   void Fill(std::vector<Double_t> coord, double v, double w);

   // Do the scaling to luminosity or data.
   void scaleToData(std::vector<PhysicsProcess*> procs, DEFS::LeptonCat lepCat);
   
   // Saves the histograms to the filename
   void saveHistogramsToFile(string histoFile, string option = "RECREATE", string directory = "");
   void saveHistogramsToFile(TFile &ofile, string directory = "");

   // Loads the histograms from a preexisting file
   void loadHistogramsFromFile(TDirectoryFile* dir, std::vector<PhysicsProcess*> procs, DEFS::LeptonCat lepCat, bool procNameOnly = false, TDirectoryFile* data_dir = 0);
   void loadHistogramsFromCombinedFile(TDirectoryFile* dir, DEFS::LeptonCat lepCat);

   // Sets the scaled variable
   void setScaled(bool s) {scaled = s;}

   // Prints a list of histograms loaded into the plot
   void printList();

   // Do the grouping of the histograms according to some rules.
   // For example join all histos for singleTop into a single one, 
   // also WW and WZ are usually put together...
   // I don't see the NEED FOR THIS std::vector<TH1*>  doGrouping(std::vector<PhysicsProcess*> procs);
   
   std::vector<TH1*> getHistos() { return histos; }

   TH1* templateHisto;
   std::vector<TH1*> histos;
   
   bool stacked;
   bool normToData;

protected:
   bool scaled;

   ClassDef (Plot,2);   
};

// ##################################################
// ############## FORMATTED PLOT CLASS ##############
// ##################################################

// Adds some formatting options to Plot
class FormattedPlot: public Plot
{
public:
   FormattedPlot();
   FormattedPlot(TH1*,std::vector<std::string>,std::pair<double,double>);
   FormattedPlot(const FormattedPlot &fp);
   ~FormattedPlot() {};
   
   // Make the canvas here
   vector<TCanvas*> getCanvasTDR(std::vector<PhysicsProcess*> procs);
   vector<TCanvas*> getCanvas1DTDR(std::vector<PhysicsProcess*> procs);
   vector<TCanvas*> getCanvas2DRatioTDR(std::vector<PhysicsProcess*> procs);
   vector<TCanvas*> getStackedCanvas(std::vector<PhysicsProcess*> procs);
   vector<TCanvas*> getStackedCanvasTDR(std::vector<PhysicsProcess*> procs);

   // Do the grouping of histograms according to histo->title, which is process groupName;
   std::vector<TH1*> doGrouping(std::vector<PhysicsProcess*> procs);
   
   // Do the grouping of the histograms according to some rules.
   // For example join all histos for singleTop into a single one, 
   // also WW and WZ are usually put together...
   //std::vector<TH1*> doGroupingOLD(std::vector<PhysicsProcess*> procs);

   //Make a graph to plot the error bands from the statistical errors in a histogram
   TGraphAsymmErrors* makeSystematicErrors(TH1* nominal, double totalNormalizationError = 0);
   // Add the systematic errors to the statistical errors
   void addSystematicErrors(TGraphAsymmErrors* g, TH1* nominal, TH1* sysUp, TH1* sysDown, string type = "");

   // Function to get chi2 and KS
   void drawKSandChi2Tests(TH1* totalData, TH1* all, pair<double, double> range, bool doTDR = false, Style* st = 0);

   // Function to get luminosity
   void drawLumi(float intLum);

   // Function to draw the bin information
   void drawBinInfo();

   // Return an integer rounded to the nearest N
   int RoundToNearest(int iNumberToRound, int iToNearest = 100);

   std::vector<std::string> axisTitles;
   std::pair<double,double> range;
   std::pair<bool,bool> logxy;
   
   // The lepton that this plot is for
   DEFS::LeptonCat leptonCat;

   // The jet bin that this plot is for
   DEFS::JetBin jetBin;

   // The tag cat bin that this plot is for
   DEFS::TagCat tagCat;

   // The cut flow used to make the plot
   DEFS::ControlRegion controlRegion;

   // The name and multiplicative factor for the signal histogram
   double overlaySignalFactor;
   TString overlaySignalName;

private:
   // Take care of the formatting
   void formatColors(std::vector<PhysicsProcess*> procs);
   void formatColorsStack(std::vector<PhysicsProcess*> procs);
   void formatRatio(TH1* hRatio);
   void formatStack(THStack * stack, double maxi);
   TH1 * findTitleInTH1Vector(TString title, std::vector<TH1*> groupedHistos);
   TH1 * titleContainedInTH1Vector(TString title, vector<TH1*> groupedHistos);

   ClassDef (FormattedPlot,3);
};

#endif
