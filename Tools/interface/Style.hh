#ifndef STYLE_HH
#define STYLE_HH

#include "TStyle.h"
#include "TROOT.h"
#include "TPad.h"
#include "TFrame.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraph.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TString.h"
#include "TLine.h"
#include "TColor.h"

#include <iostream>
#include <string>
#include <assert.h>

using std::cout;
using std::endl;
using std::string;


TColor uscb_blue(5000, 1/255.,57/255.,166/255.); 
TColor penn_red(5002, 149/255.,0/255.,26/255.); 
TColor uo_green(5004, 0/255.,79/255.,39/255.);

TColor ucsb_blue_lite(2000, 13/255.,67/255.,255/255.);
TColor carrot(2003, 230/255., 91/255., 20/255.);

TColor uo_green_lite(2004, 23/255.,160/255.,74/255.);
TColor tcu_purple_lite(2005, 86/255.,69/255.,203/255.);

TColor qcd_uscb_gold(2001, 255/255.,200/255.,47/255);
TColor znn_penn_red(2002, 255/255.,0/255.,43/255.);
TColor lost_lep_dusk_blue(2006, 105/255.,166/255., 202/255.);
TColor had_tau_grayed_jade(2007, 133/255.,189/255., 164/255.);
TColor heather(2008, 133/255.,99/255., 163/255.);
TColor c_iso(3002, 201/255., 191/255., 138/255.);

TColor uw_gold(3003, 145/255., 123/255., 76/255.);
TColor pretty_purple(3004, 185/255., 141/255., 226/255.);
TColor rose_quartz(3005, 240/255., 187/255., 183/255.);

class Style {
public:
  Style() {reset_globals();}
  ~Style() {;}
 
  void tdrDraw(TH1* h, string opt,
               int marker=kFullCircle, int mcolor = kBlack,
               int lstyle=kSolid, int lcolor=-1,
               int fstyle=1001, int fcolor=kYellow+1);
  void tdrDraw(TProfile* h, string opt,
               int marker=kFullCircle, int mcolor = kBlack,
               int lstyle=kSolid, int lcolor=-1,
               int fstyle=1001, int fcolor=kYellow+1);
  void tdrDraw(THStack* s, string opt);
  void tdrDraw(TGraph* g, string opt,
               int marker=kFullCircle, int mcolor = kBlack,
               int lstyle=kSolid, int lcolor=-1,
               int fstyle=1001, int fcolor=kYellow+1);
  TLegend *tdrLeg(double x1, double y1, double x2, double y2);
  TPaveText *tdrText(double x1, double y1, double x2, double y2, int alignment = 21);

  void tdrGrid(bool gridOn);

  void fixOverlay();

  void Pal1() {gStyle->SetPalette(51);}
  void Pal2() {gStyle->SetPalette(53);}
  void set_palette_style();
  void set_deep_sea_palette();
  void set_avocado_palette();
  void set_temperature_palette();
  void set_jbradmil_style(TH1 * h, const TString& p, const bool dashes=false);
  void set_jbradmil_style_lite_(TH1 * h, const TString& p, const bool dashes=false);
  void set_jbradmil_style(TLegend* leg, float text_size=0.045, bool transparent=false);
  void setTDRStyle();

  void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10, string options = "" );
  void reset_globals();

  TCanvas* tdrCanvas(const char* canvName, TH1D *h, int iPeriod = 2, int iPos = 11,
                     bool square = kRectangular, double lumiOverride = -1, string options = "");
  TCanvas* tdrDiCanvas(const char* canvName, TH1D *hup, TH1D *hdw, int iPeriod = 2,
                       int iPos = 11, double lumiOverride = -1);

private:
  static const bool kSquare = true;
  static const bool kRectangular = false;

  // colors to use
  //EColor tdrColors[13] = {kBlack, kBlue, kRed, kGreen, kYellow, kMagenta, kCyan,
  //                        kOrange, kSpring, kTeal, kAzure, kViolet, kPink};

  TString cmsText;
  float cmsTextFont;  // default is helvetic-bold
  
  bool writeExtraText;//false;
  TString extraText;
  TString extraText2; // For Simulation Preliminary on two lines
  float extraTextFont;  // default is helvetica-italics
  
  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  float lumiTextSize;
  float lumiTextOffset;
  float cmsTextSize;
  float cmsTextOffset;  // only used in outOfFrame version
  
  float relPosX;
  float relPosY;
  float relExtraDY;

  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize;
  
  TString lumi_13TeV;
  TString lumi_8TeV;
  TString lumi_7TeV;
  
  bool drawLogo;
};

#endif
