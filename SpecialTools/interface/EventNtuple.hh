//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 23 07:53:40 2018 by ROOT version 6.10/09
// from TTree PreSelection/PreSelection
// found on file: root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV15/Run2018B-PromptReco-v1.SingleMuon_84_RA2AnalysisTree.root
//////////////////////////////////////////////////////////

#ifndef EVENTNTUPLE_HH
#define EVENTNTUPLE_HH

//
// User Defined Includes
//
#include "CUAnalysis/SpecialTools/interface/Defs.hh"

//
// ROOT includes
//
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

//
// Standard Library Includes
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//
// Namespace
//
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::left;

////////////////////////////////////////////////////////////////////////////////
// class definition
////////////////////////////////////////////////////////////////////////////////

class EventNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   bool            isMC;     //!If true, indicates that all branches, including the ones only found in MC samples, should be used

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   ULong64_t       EvtNum;
   Bool_t          BadChargedCandidateFilter;
   Bool_t          BadPFMuonFilter;
   Int_t           BTags;
   Int_t           BTagsclean;
   Int_t           BTagsDeepCSV;
   Int_t           BTagsDeepCSVclean;
   Int_t           BTagsDeepCSVJECdown;
   Int_t           BTagsDeepCSVJECup;
   Int_t           BTagsDeepCSVJERdown;
   Int_t           BTagsDeepCSVJERup;
   Int_t           BTagsJECdown;
   Int_t           BTagsJECup;
   Int_t           BTagsJERdown;
   Int_t           BTagsJERup;
   Double_t        CaloMET;
   Double_t        CaloMETPhi;
   Double_t        CrossSection;
   Int_t           CSCTightHaloFilter;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi1_AK8;
   Double_t        DeltaPhi1clean;
   Double_t        DeltaPhi1JECdown;
   Double_t        DeltaPhi1JECup;
   Double_t        DeltaPhi1JERdown;
   Double_t        DeltaPhi1JERup;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi2_AK8;
   Double_t        DeltaPhi2clean;
   Double_t        DeltaPhi2JECdown;
   Double_t        DeltaPhi2JECup;
   Double_t        DeltaPhi2JERdown;
   Double_t        DeltaPhi2JERup;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi3clean;
   Double_t        DeltaPhi3JECdown;
   Double_t        DeltaPhi3JECup;
   Double_t        DeltaPhi3JERdown;
   Double_t        DeltaPhi3JERup;
   Double_t        DeltaPhi4;
   Double_t        DeltaPhi4clean;
   Double_t        DeltaPhi4JECdown;
   Double_t        DeltaPhi4JECup;
   Double_t        DeltaPhi4JERdown;
   Double_t        DeltaPhi4JERup;
   Double_t        DeltaPhiMin_AK8;
   Int_t           ecalBadCalibFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   vector<TLorentzVector> *Electrons;
   vector<int>     *Electrons_charge;
   vector<bool>    *Electrons_mediumID;
   vector<double>  *Electrons_MiniIso;
   vector<double>  *Electrons_MT2Activity;
   vector<double>  *Electrons_MTW;
   vector<bool>    *Electrons_passIso;
   vector<bool>    *Electrons_tightID;
   vector<TLorentzVector> *GenElectrons;
   vector<bool>    *GenElectrons_fromTau;
   vector<double>  *GenElectrons_MT2Activity;
   vector<double>  *GenElectrons_RecoTrkAct;
   vector<double>  *GenElectrons_RecoTrkd3;
   vector<double>  *GenElectrons_RecoTrkIso;
   Double_t        GenHT;
   vector<TLorentzVector> *GenJets;
   vector<bool>    *GenJets_HTMask;
   vector<bool>    *GenJets_MHTMask;
   vector<TLorentzVector> *GenJetsAK8;
   vector<double>  *GenJetsAK8_prunedMass;
   vector<double>  *GenJetsAK8_softDropMass;
   Double_t        GenMET;
   Double_t        GenMETPhi;
   Double_t        GenMHT;
   Double_t        GenMHTPhi;
   vector<TLorentzVector> *GenMuons;
   vector<bool>    *GenMuons_fromTau;
   vector<double>  *GenMuons_MT2Activity;
   vector<double>  *GenMuons_RecoTrkAct;
   vector<double>  *GenMuons_RecoTrkd3;
   vector<double>  *GenMuons_RecoTrkIso;
   vector<TLorentzVector> *GenParticles;
   vector<int>     *GenParticles_ParentId;
   vector<int>     *GenParticles_ParentIdx;
   vector<int>     *GenParticles_PdgId;
   vector<int>     *GenParticles_Status;
   vector<bool>    *GenParticles_TTFlag;
   vector<TLorentzVector> *GenTaus;
   vector<bool>    *GenTaus_had;
   vector<double>  *GenTaus_LeadRecoTrkAct;
   vector<double>  *GenTaus_LeadRecoTrkd3;
   vector<double>  *GenTaus_LeadRecoTrkIso;
   vector<TLorentzVector> *GenTaus_LeadTrk;
   vector<double>  *GenTaus_MT2Activity;
   vector<int>     *GenTaus_NNeutralHadrons;
   vector<int>     *GenTaus_NProngs;
   vector<TLorentzVector> *GenTaus_Nu;
   vector<TLorentzVector> *GenTops;
   Double_t        GenTopWeight;
   Int_t           globalTightHalo2016Filter;
   Int_t           globalSuperTightHalo2016Filter;
   Bool_t          hasGenPromptPhoton;
   Int_t           HBHEIsoNoiseFilter;
   Int_t           HBHENoiseFilter;
   Double_t        HT;
   Double_t        HT5;
   Double_t        HT5clean;
   Double_t        HT5JECdown;
   Double_t        HT5JECup;
   Double_t        HT5JERdown;
   Double_t        HT5JERup;
   Double_t        HTclean;
   Double_t        HTOnline;
   Double_t        HTJECdown;
   Double_t        HTJECup;
   Double_t        HTJERdown;
   Double_t        HTJERup;
   Int_t           isoElectronTracks;
   Int_t           isoElectronTracksclean;
   Int_t           isoMuonTracks;
   Int_t           isoMuonTracksclean;
   Int_t           isoPionTracks;
   Int_t           isoPionTracksclean;
   Bool_t          JetID;
   Bool_t          JetIDAK8;
   Bool_t          JetIDAK8Clean;
   Bool_t          JetIDclean;
   Bool_t          JetIDJECdown;
   Bool_t          JetIDJECup;
   Bool_t          JetIDJERdown;
   Bool_t          JetIDJERup;
   vector<TLorentzVector> *Jets;
   vector<double>  *Jets_axismajor;
   vector<double>  *Jets_axisminor;
   vector<double>  *Jets_bDiscriminatorCSV;
   vector<double>  *Jets_bJetTagDeepCSVBvsAll;
   vector<double>  *Jets_bJetTagDeepCSVCvsB;
   vector<double>  *Jets_bJetTagDeepCSVCvsL;
   vector<double>  *Jets_bJetTagDeepCSVprobb;
   vector<double>  *Jets_bJetTagDeepCSVprobbb;
   vector<double>  *Jets_bJetTagDeepCSVprobc;
   vector<double>  *Jets_bJetTagDeepCSVprobudsg;
   vector<double>  *Jets_bJetTagDeepFlavourprobb;
   vector<double>  *Jets_bJetTagDeepFlavourprobbb;
   vector<double>  *Jets_bJetTagDeepFlavourprobc;
   vector<double>  *Jets_bJetTagDeepFlavourprobg;
   vector<double>  *Jets_bJetTagDeepFlavourproblepb;
   vector<double>  *Jets_bJetTagDeepFlavourprobuds;
   vector<double>  *Jets_chargedEmEnergyFraction;
   vector<double>  *Jets_chargedHadronEnergyFraction;
   vector<int>     *Jets_chargedHadronMultiplicity;
   vector<int>     *Jets_chargedMultiplicity;
   vector<double>  *Jets_electronEnergyFraction;
   vector<int>     *Jets_electronMultiplicity;
   vector<int>     *Jets_hadronFlavor;
   vector<double>  *Jets_hfEMEnergyFraction;
   vector<double>  *Jets_hfHadronEnergyFraction;
   vector<bool>    *Jets_HTMask;
   vector<bool>    *Jets_ID;
   vector<bool>    *Jets_ISRMask;
   vector<double>  *Jets_jecFactor;
   vector<double>  *Jets_jecUnc;
   vector<double>  *Jets_jerFactor;
   vector<double>  *Jets_jerFactorDown;
   vector<double>  *Jets_jerFactorUp;
   vector<bool>    *Jets_LeptonMask;
   vector<bool>    *Jets_MHTMask;
   vector<int>     *Jets_multiplicity;
   vector<double>  *Jets_muonEnergyFraction;
   vector<int>     *Jets_muonMultiplicity;
   vector<double>  *Jets_neutralEmEnergyFraction;
   vector<double>  *Jets_neutralHadronEnergyFraction;
   vector<int>     *Jets_neutralHadronMultiplicity;
   vector<int>     *Jets_neutralMultiplicity;
   vector<int>     *Jets_origIndex;
   vector<int>     *Jets_partonFlavor;
   vector<double>  *Jets_photonEnergyFraction;
   vector<int>     *Jets_photonMultiplicity;
   vector<double>  *Jets_ptD;
   vector<double>  *Jets_qgLikelihood;
   vector<TLorentzVector> *JetsAK8;
   vector<double>  *JetsAK8_axismajor;
   vector<double>  *JetsAK8_axisminor;
   vector<double>  *JetsAK8_doubleBDiscriminator;
   vector<double>  *JetsAK8_ecfN2b1;
   vector<double>  *JetsAK8_ecfN2b2;
   vector<double>  *JetsAK8_ecfN3b1;
   vector<double>  *JetsAK8_ecfN3b2;
   vector<double>  *JetsAK8_girth;
   vector<double>  *JetsAK8_hDiscriminatorDeep;
   vector<bool>    *JetsAK8_ID;
   vector<double>  *JetsAK8_lean;
   vector<double>  *JetsAK8_momenthalf;
   vector<int>     *JetsAK8_multiplicity;
   vector<double>  *JetsAK8_NsubjettinessTau1;
   vector<double>  *JetsAK8_NsubjettinessTau2;
   vector<double>  *JetsAK8_NsubjettinessTau3;
   vector<int>     *JetsAK8_NumBhadrons;
   vector<int>     *JetsAK8_NumChadrons;
   vector<double>  *JetsAK8_overflow;
   vector<double>  *JetsAK8_prunedMass;
   vector<double>  *JetsAK8_ptD;
   vector<double>  *JetsAK8_ptdrlog;
   vector<double>  *JetsAK8_softDropMass;
   vector<vector<TLorentzVector> > *JetsAK8_subjets;
   vector<vector<double> > *JetsAK8_subjets_axismajor;
   vector<vector<double> > *JetsAK8_subjets_axisminor;
   vector<vector<double> > *JetsAK8_subjets_bDiscriminatorCSV;
   vector<vector<int> > *JetsAK8_subjets_multiplicity;
   vector<vector<double> > *JetsAK8_subjets_ptD;
   vector<double>  *JetsAK8_tDiscriminatorDeep;
   vector<double>  *JetsAK8_wDiscriminatorDeep;
   vector<double>  *JetsAK8_zDiscriminatorDeep;
   vector<TLorentzVector> *JetsAK8Clean;
   vector<double>  *JetsAK8Clean_doubleBDiscriminator;
   vector<double>  *JetsAK8Clean_ecfN2b1;
   vector<double>  *JetsAK8Clean_ecfN2b2;
   vector<double>  *JetsAK8Clean_ecfN3b1;
   vector<double>  *JetsAK8Clean_ecfN3b2;
   vector<bool>    *JetsAK8Clean_ID;
   vector<double>  *JetsAK8Clean_NsubjettinessTau1;
   vector<double>  *JetsAK8Clean_NsubjettinessTau2;
   vector<double>  *JetsAK8Clean_NsubjettinessTau3;
   vector<int>     *JetsAK8Clean_NumBhadrons;
   vector<int>     *JetsAK8Clean_NumChadrons;
   vector<double>  *JetsAK8Clean_prunedMass;
   vector<double>  *JetsAK8Clean_softDropMass;
   vector<vector<TLorentzVector> > *JetsAK8Clean_subjets;
   vector<vector<double> > *JetsAK8Clean_subjets_bDiscriminatorCSV;
   vector<TLorentzVector> *Jetsclean;
   vector<double>  *Jetsclean_bDiscriminatorCSV;
   vector<double>  *Jetsclean_bJetTagDeepCSVBvsAll;
   vector<double>  *Jetsclean_bJetTagDeepCSVCvsB;
   vector<double>  *Jetsclean_bJetTagDeepCSVCvsL;
   vector<double>  *Jetsclean_bJetTagDeepCSVprobb;
   vector<double>  *Jetsclean_bJetTagDeepCSVprobbb;
   vector<double>  *Jetsclean_bJetTagDeepCSVprobc;
   vector<double>  *Jetsclean_bJetTagDeepCSVprobudsg;
   vector<double>  *Jetsclean_bJetTagDeepFlavourprobb;
   vector<double>  *Jetsclean_bJetTagDeepFlavourprobbb;
   vector<double>  *Jetsclean_bJetTagDeepFlavourprobc;
   vector<double>  *Jetsclean_bJetTagDeepFlavourprobg;
   vector<double>  *Jetsclean_bJetTagDeepFlavourproblepb;
   vector<double>  *Jetsclean_bJetTagDeepFlavourprobuds;
   vector<double>  *Jetsclean_chargedHadronEnergyFraction;
   vector<int>     *Jetsclean_hadronFlavor;
   vector<bool>    *Jetsclean_HTMask;
   vector<bool>    *Jetsclean_ID;
   vector<bool>    *Jetsclean_ISRMask;
   vector<bool>    *Jetsclean_MHTMask;
   vector<double>  *Jetsclean_muonEnergyFraction;
   vector<int>     *Jetsclean_partonFlavor;
   vector<TLorentzVector> *JetsJECdown;
   vector<double>  *JetsJECdown_jerFactor;
   vector<int>     *JetsJECdown_origIndex;
   vector<TLorentzVector> *JetsJECup;
   vector<double>  *JetsJECup_jerFactor;
   vector<int>     *JetsJECup_origIndex;
   vector<TLorentzVector> *JetsJERdown;
   vector<int>     *JetsJERdown_origIndex;
   vector<TLorentzVector> *JetsJERup;
   vector<int>     *JetsJERup_origIndex;
   Double_t        madHT;
   Int_t           madMinDeltaRStatus;
   Double_t        madMinPhotonDeltaR;
   Double_t        MET;
   Double_t        METclean;
   vector<double>  *METDown;
   Double_t        METPhi;
   Double_t        METPhiclean;
   vector<double>  *METPhiDown;
   vector<double>  *METPhiUp;
   Double_t        METSignificance;
   Double_t        METSignificanceclean;
   vector<double>  *METUp;
   Double_t        MHT;
   Double_t        MHTclean;
   Double_t        MHTOnline;
   Double_t        MHTJECdown;
   Double_t        MHTJECup;
   Double_t        MHTJERdown;
   Double_t        MHTJERup;
   Double_t        MHTPhi;
   Double_t        MHTPhiclean;
   Double_t        MHTPhiJECdown;
   Double_t        MHTPhiJECup;
   Double_t        MHTPhiJERdown;
   Double_t        MHTPhiJERup;
   Double_t        MJJ_AK8;
   Double_t        Mmc_AK8;
   Double_t        MT2;
   Double_t        MT_AK8;
   vector<TLorentzVector> *Muons;
   vector<int>     *Muons_charge;
   vector<double>  *Muons_MiniIso;
   vector<double>  *Muons_MT2Activity;
   vector<double>  *Muons_MTW;
   vector<bool>    *Muons_passIso;
   vector<bool>    *Muons_tightID;
   Int_t           nAllVertices;
   Int_t           NElectrons;
   Int_t           NJets;
   Int_t           NJetsclean;
   Int_t           NJetsISR;
   Int_t           NJetsISRclean;
   Int_t           NJetsISRJECdown;
   Int_t           NJetsISRJECup;
   Int_t           NJetsISRJERdown;
   Int_t           NJetsISRJERup;
   Int_t           NJetsJECdown;
   Int_t           NJetsJECup;
   Int_t           NJetsJERdown;
   Int_t           NJetsJERup;
   Int_t           NMuons;
   Double_t        NumEvents;
   Int_t           NumInteractions;
   Int_t           NVtx;
   vector<int>     *PDFids;
   vector<double>  *PDFweights;
   Double_t        PFCaloMETRatio;
   vector<TLorentzVector> *Photons;
   vector<bool>    *Photons_electronFakes;
   vector<bool>    *Photons_fullID;
   vector<double>  *Photons_genMatched;
   vector<double>  *Photons_hadTowOverEM;
   vector<double>  *Photons_hasPixelSeed;
   vector<double>  *Photons_isEB;
   vector<bool>    *Photons_nonPrompt;
   vector<double>  *Photons_passElectronVeto;
   vector<double>  *Photons_pfChargedIso;
   vector<double>  *Photons_pfChargedIsoRhoCorr;
   vector<double>  *Photons_pfGammaIso;
   vector<double>  *Photons_pfGammaIsoRhoCorr;
   vector<double>  *Photons_pfNeutralIso;
   vector<double>  *Photons_pfNeutralIsoRhoCorr;
   vector<double>  *Photons_sigmaIetaIeta;
   Double_t        PrescaleWeightHT;
   Double_t        PmssmId;
   Int_t           PrimaryVertexFilter;
   Double_t        puSysDown;
   Double_t        puSysUp;
   Double_t        puWeight;
   vector<double>  *ScaleWeights;
   Double_t        SusyLSPMass;
   Double_t        SusyMotherMass;
   vector<TLorentzVector> *TAPElectronTracks;
   vector<double>  *TAPElectronTracks_activity;
   vector<int>     *TAPElectronTracks_charge;
   vector<double>  *TAPElectronTracks_mT;
   vector<double>  *TAPElectronTracks_trkiso;
   vector<TLorentzVector> *TAPMuonTracks;
   vector<double>  *TAPMuonTracks_activity;
   vector<int>     *TAPMuonTracks_charge;
   vector<double>  *TAPMuonTracks_mT;
   vector<double>  *TAPMuonTracks_trkiso;
   vector<TLorentzVector> *TAPPionTracks;
   vector<double>  *TAPPionTracks_activity;
   vector<int>     *TAPPionTracks_charge;
   vector<double>  *TAPPionTracks_mT;
   vector<double>  *TAPPionTracks_trkiso;
   vector<string>  *TriggerNames;
   vector<int>     *TriggerPass;
   vector<int>     *TriggerPrescales;
   vector<int>     *TriggerVersion;
   Double_t        TrueNumInteractions;
   Double_t        Weight;
   vector<TLorentzVector> *ZCandidates;

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_BadChargedCandidateFilter;   //!
   TBranch        *b_BadPFMuonFilter;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_BTagsclean;   //!
   TBranch        *b_BTagsDeepCSV;   //!
   TBranch        *b_BTagsDeepCSVclean;   //!
   TBranch        *b_BTagsDeepCSVJECdown;   //!
   TBranch        *b_BTagsDeepCSVJECup;   //!
   TBranch        *b_BTagsDeepCSVJERdown;   //!
   TBranch        *b_BTagsDeepCSVJERup;   //!
   TBranch        *b_BTagsJECdown;   //!
   TBranch        *b_BTagsJECup;   //!
   TBranch        *b_BTagsJERdown;   //!
   TBranch        *b_BTagsJERup;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CrossSection;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi1_AK8;   //!
   TBranch        *b_DeltaPhi1clean;   //!
   TBranch        *b_DeltaPhi1JECdown;   //!
   TBranch        *b_DeltaPhi1JECup;   //!
   TBranch        *b_DeltaPhi1JERdown;   //!
   TBranch        *b_DeltaPhi1JERup;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi2_AK8;   //!
   TBranch        *b_DeltaPhi2clean;   //!
   TBranch        *b_DeltaPhi2JECdown;   //!
   TBranch        *b_DeltaPhi2JECup;   //!
   TBranch        *b_DeltaPhi2JERdown;   //!
   TBranch        *b_DeltaPhi2JERup;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi3clean;   //!
   TBranch        *b_DeltaPhi3JECdown;   //!
   TBranch        *b_DeltaPhi3JECup;   //!
   TBranch        *b_DeltaPhi3JERdown;   //!
   TBranch        *b_DeltaPhi3JERup;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_DeltaPhi4clean;   //!
   TBranch        *b_DeltaPhi4JECdown;   //!
   TBranch        *b_DeltaPhi4JECup;   //!
   TBranch        *b_DeltaPhi4JERdown;   //!
   TBranch        *b_DeltaPhi4JERup;   //!
   TBranch        *b_DeltaPhiMin_AK8;   //!
   TBranch        *b_ecalBadCalibFilter;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_Electrons;   //!
   TBranch        *b_Electrons_charge;   //!
   TBranch        *b_Electrons_mediumID;   //!
   TBranch        *b_Electrons_MiniIso;   //!
   TBranch        *b_Electrons_MT2Activity;   //!
   TBranch        *b_Electrons_MTW;   //!
   TBranch        *b_Electrons_passIso;   //!
   TBranch        *b_Electrons_tightID;   //!
   TBranch        *b_GenElectrons;   //!
   TBranch        *b_GenElectrons_fromTau;   //!
   TBranch        *b_GenElectrons_MT2Activity;   //!
   TBranch        *b_GenElectrons_RecoTrkAct;   //!
   TBranch        *b_GenElectrons_RecoTrkd3;   //!
   TBranch        *b_GenElectrons_RecoTrkIso;   //!
   TBranch        *b_GenHT;   //!
   TBranch        *b_GenJets;   //!
   TBranch        *b_GenJets_HTMask;   //!
   TBranch        *b_GenJets_MHTMask;   //!
   TBranch        *b_GenJetsAK8;   //!
   TBranch        *b_GenJetsAK8_prunedMass;   //!
   TBranch        *b_GenJetsAK8_softDropMass;   //!
   TBranch        *b_GenMET;   //!
   TBranch        *b_GenMETPhi;   //!
   TBranch        *b_GenMHT;   //!
   TBranch        *b_GenMHTPhi;   //!
   TBranch        *b_GenMuons;   //!
   TBranch        *b_GenMuons_fromTau;   //!
   TBranch        *b_GenMuons_MT2Activity;   //!
   TBranch        *b_GenMuons_RecoTrkAct;   //!
   TBranch        *b_GenMuons_RecoTrkd3;   //!
   TBranch        *b_GenMuons_RecoTrkIso;   //!
   TBranch        *b_GenParticles;   //!
   TBranch        *b_GenParticles_ParentId;   //!
   TBranch        *b_GenParticles_ParentIdx;   //!
   TBranch        *b_GenParticles_PdgId;   //!
   TBranch        *b_GenParticles_Status;   //!
   TBranch        *b_GenParticles_TTFlag;   //!
   TBranch        *b_GenTaus;   //!
   TBranch        *b_GenTaus_had;   //!
   TBranch        *b_GenTaus_LeadRecoTrkAct;   //!
   TBranch        *b_GenTaus_LeadRecoTrkd3;   //!
   TBranch        *b_GenTaus_LeadRecoTrkIso;   //!
   TBranch        *b_GenTaus_LeadTrk;   //!
   TBranch        *b_GenTaus_MT2Activity;   //!
   TBranch        *b_GenTaus_NNeutralHadrons;   //!
   TBranch        *b_GenTaus_NProngs;   //!
   TBranch        *b_GenTaus_Nu;   //!
   TBranch        *b_GenTops;   //!
   TBranch        *b_GenTopWeight;   //!
   TBranch        *b_globalTightHalo2016Filter;   //!
   TBranch        *b_globalSuperTightHalo2016Filter;   //!
   TBranch        *b_hasGenPromptPhoton;   //!
   TBranch        *b_HBHEIsoNoiseFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_HT5;   //!
   TBranch        *b_HT5clean;   //!
   TBranch        *b_HT5JECdown;   //!
   TBranch        *b_HT5JECup;   //!
   TBranch        *b_HT5JERdown;   //!
   TBranch        *b_HT5JERup;   //!
   TBranch        *b_HTclean;   //!
   TBranch        *b_HTOnline;   //!
   TBranch        *b_HTJECdown;   //!
   TBranch        *b_HTJECup;   //!
   TBranch        *b_HTJERdown;   //!
   TBranch        *b_HTJERup;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoElectronTracksclean;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoMuonTracksclean;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_isoPionTracksclean;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_JetIDAK8;   //!
   TBranch        *b_JetIDAK8Clean;   //!
   TBranch        *b_JetIDclean;   //!
   TBranch        *b_JetIDJECdown;   //!
   TBranch        *b_JetIDJECup;   //!
   TBranch        *b_JetIDJERdown;   //!
   TBranch        *b_JetIDJERup;   //!
   TBranch        *b_Jets;   //!
   TBranch        *b_Jets_axismajor;   //!
   TBranch        *b_Jets_axisminor;   //!
   TBranch        *b_Jets_bDiscriminatorCSV;   //!
   TBranch        *b_Jets_bJetTagDeepCSVBvsAll;   //!
   TBranch        *b_Jets_bJetTagDeepCSVCvsB;   //!
   TBranch        *b_Jets_bJetTagDeepCSVCvsL;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobb;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobbb;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobc;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobudsg;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobbb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobc;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobg;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourproblepb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobuds;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_chargedMultiplicity;   //!
   TBranch        *b_Jets_electronEnergyFraction;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_hadronFlavor;   //!
   TBranch        *b_Jets_hfEMEnergyFraction;   //!
   TBranch        *b_Jets_hfHadronEnergyFraction;   //!
   TBranch        *b_Jets_HTMask;   //!
   TBranch        *b_Jets_ID;   //!
   TBranch        *b_Jets_ISRMask;   //!
   TBranch        *b_Jets_jecFactor;   //!
   TBranch        *b_Jets_jecUnc;   //!
   TBranch        *b_Jets_jerFactor;   //!
   TBranch        *b_Jets_jerFactorDown;   //!
   TBranch        *b_Jets_jerFactorUp;   //!
   TBranch        *b_Jets_LeptonMask;   //!
   TBranch        *b_Jets_MHTMask;   //!
   TBranch        *b_Jets_multiplicity;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_neutralMultiplicity;   //!
   TBranch        *b_Jets_origIndex;   //!
   TBranch        *b_Jets_partonFlavor;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_Jets_ptD;   //!
   TBranch        *b_Jets_qgLikelihood;   //!
   TBranch        *b_JetsAK8;   //!
   TBranch        *b_JetsAK8_axismajor;   //!
   TBranch        *b_JetsAK8_axisminor;   //!
   TBranch        *b_JetsAK8_doubleBDiscriminator;   //!
   TBranch        *b_JetsAK8_ecfN2b1;   //!
   TBranch        *b_JetsAK8_ecfN2b2;   //!
   TBranch        *b_JetsAK8_ecfN3b1;   //!
   TBranch        *b_JetsAK8_ecfN3b2;   //!
   TBranch        *b_JetsAK8_girth;   //!
   TBranch        *b_JetsAK8_hDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_ID;   //!
   TBranch        *b_JetsAK8_lean;   //!
   TBranch        *b_JetsAK8_momenthalf;   //!
   TBranch        *b_JetsAK8_multiplicity;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau1;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau2;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau3;   //!
   TBranch        *b_JetsAK8_NumBhadrons;   //!
   TBranch        *b_JetsAK8_NumChadrons;   //!
   TBranch        *b_JetsAK8_overflow;   //!
   TBranch        *b_JetsAK8_prunedMass;   //!
   TBranch        *b_JetsAK8_ptD;   //!
   TBranch        *b_JetsAK8_ptdrlog;   //!
   TBranch        *b_JetsAK8_softDropMass;   //!
   TBranch        *b_JetsAK8_subjets;   //!
   TBranch        *b_JetsAK8_subjets_axismajor;   //!
   TBranch        *b_JetsAK8_subjets_axisminor;   //!
   TBranch        *b_JetsAK8_subjets_bDiscriminatorCSV;   //!
   TBranch        *b_JetsAK8_subjets_multiplicity;   //!
   TBranch        *b_JetsAK8_subjets_ptD;   //!
   TBranch        *b_JetsAK8_tDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_wDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_zDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8Clean;   //!
   TBranch        *b_JetsAK8Clean_doubleBDiscriminator;   //!
   TBranch        *b_JetsAK8Clean_ecfN2b1;   //!
   TBranch        *b_JetsAK8Clean_ecfN2b2;   //!
   TBranch        *b_JetsAK8Clean_ecfN3b1;   //!
   TBranch        *b_JetsAK8Clean_ecfN3b2;   //!
   TBranch        *b_JetsAK8Clean_ID;   //!
   TBranch        *b_JetsAK8Clean_NsubjettinessTau1;   //!
   TBranch        *b_JetsAK8Clean_NsubjettinessTau2;   //!
   TBranch        *b_JetsAK8Clean_NsubjettinessTau3;   //!
   TBranch        *b_JetsAK8Clean_NumBhadrons;   //!
   TBranch        *b_JetsAK8Clean_NumChadrons;   //!
   TBranch        *b_JetsAK8Clean_prunedMass;   //!
   TBranch        *b_JetsAK8Clean_softDropMass;   //!
   TBranch        *b_JetsAK8Clean_subjets;   //!
   TBranch        *b_JetsAK8Clean_subjets_bDiscriminatorCSV;   //!
   TBranch        *b_Jetsclean;   //!
   TBranch        *b_Jetsclean_bDiscriminatorCSV;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVBvsAll;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVCvsB;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVCvsL;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVprobb;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVprobbb;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVprobc;   //!
   TBranch        *b_Jetsclean_bJetTagDeepCSVprobudsg;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourprobb;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourprobbb;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourprobc;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourprobg;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourproblepb;   //!
   TBranch        *b_Jetsclean_bJetTagDeepFlavourprobuds;   //!
   TBranch        *b_Jetsclean_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jetsclean_hadronFlavor;   //!
   TBranch        *b_Jetsclean_HTMask;   //!
   TBranch        *b_Jetsclean_ID;   //!
   TBranch        *b_Jetsclean_ISRMask;   //!
   TBranch        *b_Jetsclean_MHTMask;   //!
   TBranch        *b_Jetsclean_muonEnergyFraction;   //!
   TBranch        *b_Jetsclean_partonFlavor;   //!
   TBranch        *b_JetsJECdown;   //!
   TBranch        *b_JetsJECdown_jerFactor;   //!
   TBranch        *b_JetsJECdown_origIndex;   //!
   TBranch        *b_JetsJECup;   //!
   TBranch        *b_JetsJECup_jerFactor;   //!
   TBranch        *b_JetsJECup_origIndex;   //!
   TBranch        *b_JetsJERdown;   //!
   TBranch        *b_JetsJERdown_origIndex;   //!
   TBranch        *b_JetsJERup;   //!
   TBranch        *b_JetsJERup_origIndex;   //!
   TBranch        *b_madHT;   //!
   TBranch        *b_madMinDeltaRStatus;   //!
   TBranch        *b_madMinPhotonDeltaR;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METclean;   //!
   TBranch        *b_METDown;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METPhiclean;   //!
   TBranch        *b_METPhiDown;   //!
   TBranch        *b_METPhiUp;   //!
   TBranch        *b_METSignificance;   //!
   TBranch        *b_METSignificanceclean;   //!
   TBranch        *b_METUp;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHTclean;   //!
   TBranch        *b_MHTOnline;   //!
   TBranch        *b_MHTJECdown;   //!
   TBranch        *b_MHTJECup;   //!
   TBranch        *b_MHTJERdown;   //!
   TBranch        *b_MHTJERup;   //!
   TBranch        *b_MHTPhi;   //!
   TBranch        *b_MHTPhiclean;   //!
   TBranch        *b_MHTPhiJECdown;   //!
   TBranch        *b_MHTPhiJECup;   //!
   TBranch        *b_MHTPhiJERdown;   //!
   TBranch        *b_MHTPhiJERup;   //!
   TBranch        *b_MJJ_AK8;   //!
   TBranch        *b_Mmc_AK8;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_MT_AK8;   //!
   TBranch        *b_Muons;   //!
   TBranch        *b_Muons_charge;   //!
   TBranch        *b_Muons_MiniIso;   //!
   TBranch        *b_Muons_MT2Activity;   //!
   TBranch        *b_Muons_MTW;   //!
   TBranch        *b_Muons_passIso;   //!
   TBranch        *b_Muons_tightID;   //!
   TBranch        *b_nAllVertices;   //!
   TBranch        *b_NElectrons;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NJetsclean;   //!
   TBranch        *b_NJetsISR;   //!
   TBranch        *b_NJetsISRclean;   //!
   TBranch        *b_NJetsISRJECdown;   //!
   TBranch        *b_NJetsISRJECup;   //!
   TBranch        *b_NJetsISRJERdown;   //!
   TBranch        *b_NJetsISRJERup;   //!
   TBranch        *b_NJetsJECdown;   //!
   TBranch        *b_NJetsJECup;   //!
   TBranch        *b_NJetsJERdown;   //!
   TBranch        *b_NJetsJERup;   //!
   TBranch        *b_NMuons;   //!
   TBranch        *b_NumEvents;   //!
   TBranch        *b_NumInteractions;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_PDFids;   //!
   TBranch        *b_PDFweights;   //!
   TBranch        *b_PFCaloMETRatio;   //!
   TBranch        *b_Photons;   //!
   TBranch        *b_Photons_electronFakes;   //!
   TBranch        *b_Photons_fullID;   //!
   TBranch        *b_Photons_genMatched;   //!
   TBranch        *b_Photons_hadTowOverEM;   //!
   TBranch        *b_Photons_hasPixelSeed;   //!
   TBranch        *b_Photons_isEB;   //!
   TBranch        *b_Photons_nonPrompt;   //!
   TBranch        *b_Photons_passElectronVeto;   //!
   TBranch        *b_Photons_pfChargedIso;   //!
   TBranch        *b_Photons_pfChargedIsoRhoCorr;   //!
   TBranch        *b_Photons_pfGammaIso;   //!
   TBranch        *b_Photons_pfGammaIsoRhoCorr;   //!
   TBranch        *b_Photons_pfNeutralIso;   //!
   TBranch        *b_Photons_pfNeutralIsoRhoCorr;   //!
   TBranch        *b_Photons_sigmaIetaIeta;   //!
   TBranch        *b_PrescaleWeightHT;   //!
   TBranch        *b_PmssmId;   //!
   TBranch        *b_PrimaryVertexFilter;   //!
   TBranch        *b_puSysDown;   //!
   TBranch        *b_puSysUp;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_SusyLSPMass;   //!
   TBranch        *b_SusyMotherMass;   //!
   TBranch        *b_TAPElectronTracks;   //!
   TBranch        *b_TAPElectronTracks_activity;   //!
   TBranch        *b_TAPElectronTracks_charge;   //!
   TBranch        *b_TAPElectronTracks_mT;   //!
   TBranch        *b_TAPElectronTracks_trkiso;   //!
   TBranch        *b_TAPMuonTracks;   //!
   TBranch        *b_TAPMuonTracks_activity;   //!
   TBranch        *b_TAPMuonTracks_charge;   //!
   TBranch        *b_TAPMuonTracks_mT;   //!
   TBranch        *b_TAPMuonTracks_trkiso;   //!
   TBranch        *b_TAPPionTracks;   //!
   TBranch        *b_TAPPionTracks_activity;   //!
   TBranch        *b_TAPPionTracks_charge;   //!
   TBranch        *b_TAPPionTracks_mT;   //!
   TBranch        *b_TAPPionTracks_trkiso;   //!
   TBranch        *b_TriggerNames;   //!
   TBranch        *b_TriggerPass;   //!
   TBranch        *b_TriggerPrescales;   //!
   TBranch        *b_TriggerVersion;   //!
   TBranch        *b_TrueNumInteractions;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_ZCandidates;   //!

   EventNtuple(TTree *tree=0, bool isMC_=false, bool debug=false);
   virtual ~EventNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree, bool debug=false);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   // form a string which contains the Lorentz vector information in the form (Pt, Eta, Phi, E)
   virtual string   getLVString(const TLorentzVector &lv);
};

#endif
