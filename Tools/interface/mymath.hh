////////////////////////////////////////////////////////////////////////////////
//
// define deltaPhi & deltaR
// ------------------------
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MYMATH_HH
#define MYMATH_HH 1


#include <TMath.h>
#include <cmath>


namespace mymath {
   double phi(double x, double y) {
        double phi_ = atan2(y, x);
        return (phi_ >= 0) ?  phi_ : phi_ + 2*TMath::Pi();
    }
   double deltaPhi(double phi1, double phi2)
   {
      double phi1_ = phi( cos(phi1), sin(phi1) );
      double phi2_ = phi( cos(phi2), sin(phi2) );
      double dphi_ = phi1_ - phi2_;
      while (dphi_ > TMath::Pi())   dphi_ -= 2*TMath::Pi();
      while (dphi_ <= -TMath::Pi()) dphi_ += 2*TMath::Pi();
      return dphi_;
   }
   double deltaR(double eta1,double phi1,double eta2,double phi2)
   {
      double deta = eta1 - eta2;
      double dphi = deltaPhi(phi1, phi2);
      return std::sqrt(deta*deta + dphi*dphi);
   }
}


#endif
