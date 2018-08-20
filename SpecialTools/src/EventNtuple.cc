/////////////////////////////////////////////////////////////////////////////////////////////////
//// CMS 
//// WW CrossSection Measurement using Matrix Element 
//// Created by Osipenkov, Ilya : ilyao@fnal.gov
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "CUAnalysis/SpecialTools/interface/EventNtuple.hh"

////////////////////////////////////////////////////////////////////////////////
// construction/destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
EventNtuple::EventNtuple(TTree *tree, bool isMC_, bool debug) : fChain(0), isMC(isMC_)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV15/Run2018B-PromptReco-v1.SingleMuon_84_RA2AnalysisTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV15/Run2018B-PromptReco-v1.SingleMuon_84_RA2AnalysisTree.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV15/Run2018B-PromptReco-v1.SingleMuon_84_RA2AnalysisTree.root:/TreeMaker2");
      dir->GetObject("PreSelection",tree);

   }
   Init(tree,debug);
}

//______________________________________________________________________________
EventNtuple::~EventNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

////////////////////////////////////////////////////////////////////////////////
// implementation of member functions
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
Int_t EventNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

//______________________________________________________________________________
Long64_t EventNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

//______________________________________________________________________________
void EventNtuple::Init(TTree *tree, bool debug)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Electrons = 0;
   Electrons_charge = 0;
   Electrons_mediumID = 0;
   Electrons_MiniIso = 0;
   Electrons_MT2Activity = 0;
   Electrons_MTW = 0;
   Electrons_passIso = 0;
   Electrons_tightID = 0;
   GenElectrons = 0;
   GenElectrons_fromTau = 0;
   GenElectrons_MT2Activity = 0;
   GenElectrons_RecoTrkAct = 0;
   GenElectrons_RecoTrkd3 = 0;
   GenElectrons_RecoTrkIso = 0;
   GenJets = 0;
   GenJets_HTMask = 0;
   GenJets_MHTMask = 0;
   GenJetsAK8 = 0;
   GenJetsAK8_prunedMass = 0;
   GenJetsAK8_softDropMass = 0;
   GenMuons = 0;
   GenMuons_fromTau = 0;
   GenMuons_MT2Activity = 0;
   GenMuons_RecoTrkAct = 0;
   GenMuons_RecoTrkd3 = 0;
   GenMuons_RecoTrkIso = 0;
   GenParticles = 0;
   GenParticles_ParentId = 0;
   GenParticles_ParentIdx = 0;
   GenParticles_PdgId = 0;
   GenParticles_Status = 0;
   GenParticles_TTFlag = 0;
   GenTaus = 0;
   GenTaus_had = 0;
   GenTaus_LeadRecoTrkAct = 0;
   GenTaus_LeadRecoTrkd3 = 0;
   GenTaus_LeadRecoTrkIso = 0;
   GenTaus_LeadTrk = 0;
   GenTaus_MT2Activity = 0;
   GenTaus_NNeutralHadrons = 0;
   GenTaus_NProngs = 0;
   GenTaus_Nu = 0;
   GenTops = 0;
   Jets = 0;
   Jets_axismajor = 0;
   Jets_axisminor = 0;
   Jets_bDiscriminatorCSV = 0;
   Jets_bJetTagDeepCSVBvsAll = 0;
   Jets_bJetTagDeepCSVCvsB = 0;
   Jets_bJetTagDeepCSVCvsL = 0;
   Jets_bJetTagDeepCSVprobb = 0;
   Jets_bJetTagDeepCSVprobbb = 0;
   Jets_bJetTagDeepCSVprobc = 0;
   Jets_bJetTagDeepCSVprobudsg = 0;
   Jets_bJetTagDeepFlavourprobb = 0;
   Jets_bJetTagDeepFlavourprobbb = 0;
   Jets_bJetTagDeepFlavourprobc = 0;
   Jets_bJetTagDeepFlavourprobg = 0;
   Jets_bJetTagDeepFlavourproblepb = 0;
   Jets_bJetTagDeepFlavourprobuds = 0;
   Jets_chargedEmEnergyFraction = 0;
   Jets_chargedHadronEnergyFraction = 0;
   Jets_chargedHadronMultiplicity = 0;
   Jets_chargedMultiplicity = 0;
   Jets_electronEnergyFraction = 0;
   Jets_electronMultiplicity = 0;
   Jets_hadronFlavor = 0;
   Jets_hfEMEnergyFraction = 0;
   Jets_hfHadronEnergyFraction = 0;
   Jets_HTMask = 0;
   Jets_ID = 0;
   Jets_ISRMask = 0;
   Jets_jecFactor = 0;
   Jets_jecUnc = 0;
   Jets_jerFactor = 0;
   Jets_jerFactorDown = 0;
   Jets_jerFactorUp = 0;
   Jets_LeptonMask = 0;
   Jets_MHTMask = 0;
   Jets_multiplicity = 0;
   Jets_muonEnergyFraction = 0;
   Jets_muonMultiplicity = 0;
   Jets_neutralEmEnergyFraction = 0;
   Jets_neutralHadronEnergyFraction = 0;
   Jets_neutralHadronMultiplicity = 0;
   Jets_neutralMultiplicity = 0;
   Jets_origIndex = 0;
   Jets_partonFlavor = 0;
   Jets_photonEnergyFraction = 0;
   Jets_photonMultiplicity = 0;
   Jets_ptD = 0;
   Jets_qgLikelihood = 0;
   JetsAK8 = 0;
   JetsAK8_axismajor = 0;
   JetsAK8_axisminor = 0;
   JetsAK8_doubleBDiscriminator = 0;
   JetsAK8_ecfN2b1 = 0;
   JetsAK8_ecfN2b2 = 0;
   JetsAK8_ecfN3b1 = 0;
   JetsAK8_ecfN3b2 = 0;
   JetsAK8_girth = 0;
   JetsAK8_hDiscriminatorDeep = 0;
   JetsAK8_ID = 0;
   JetsAK8_lean = 0;
   JetsAK8_momenthalf = 0;
   JetsAK8_multiplicity = 0;
   JetsAK8_NsubjettinessTau1 = 0;
   JetsAK8_NsubjettinessTau2 = 0;
   JetsAK8_NsubjettinessTau3 = 0;
   JetsAK8_NumBhadrons = 0;
   JetsAK8_NumChadrons = 0;
   JetsAK8_overflow = 0;
   JetsAK8_prunedMass = 0;
   JetsAK8_ptD = 0;
   JetsAK8_ptdrlog = 0;
   JetsAK8_softDropMass = 0;
   JetsAK8_subjets = 0;
   JetsAK8_subjets_axismajor = 0;
   JetsAK8_subjets_axisminor = 0;
   JetsAK8_subjets_bDiscriminatorCSV = 0;
   JetsAK8_subjets_multiplicity = 0;
   JetsAK8_subjets_ptD = 0;
   JetsAK8_tDiscriminatorDeep = 0;
   JetsAK8_wDiscriminatorDeep = 0;
   JetsAK8_zDiscriminatorDeep = 0;
   JetsAK8Clean = 0;
   JetsAK8Clean_doubleBDiscriminator = 0;
   JetsAK8Clean_ecfN2b1 = 0;
   JetsAK8Clean_ecfN2b2 = 0;
   JetsAK8Clean_ecfN3b1 = 0;
   JetsAK8Clean_ecfN3b2 = 0;
   JetsAK8Clean_ID = 0;
   JetsAK8Clean_NsubjettinessTau1 = 0;
   JetsAK8Clean_NsubjettinessTau2 = 0;
   JetsAK8Clean_NsubjettinessTau3 = 0;
   JetsAK8Clean_NumBhadrons = 0;
   JetsAK8Clean_NumChadrons = 0;
   JetsAK8Clean_prunedMass = 0;
   JetsAK8Clean_softDropMass = 0;
   JetsAK8Clean_subjets = 0;
   JetsAK8Clean_subjets_bDiscriminatorCSV = 0;
   Jetsclean = 0;
   Jetsclean_bDiscriminatorCSV = 0;
   Jetsclean_bJetTagDeepCSVBvsAll = 0;
   Jetsclean_bJetTagDeepCSVCvsB = 0;
   Jetsclean_bJetTagDeepCSVCvsL = 0;
   Jetsclean_bJetTagDeepCSVprobb = 0;
   Jetsclean_bJetTagDeepCSVprobbb = 0;
   Jetsclean_bJetTagDeepCSVprobc = 0;
   Jetsclean_bJetTagDeepCSVprobudsg = 0;
   Jetsclean_bJetTagDeepFlavourprobb = 0;
   Jetsclean_bJetTagDeepFlavourprobbb = 0;
   Jetsclean_bJetTagDeepFlavourprobc = 0;
   Jetsclean_bJetTagDeepFlavourprobg = 0;
   Jetsclean_bJetTagDeepFlavourproblepb = 0;
   Jetsclean_bJetTagDeepFlavourprobuds = 0;
   Jetsclean_chargedHadronEnergyFraction = 0;
   Jetsclean_hadronFlavor = 0;
   Jetsclean_HTMask = 0;
   Jetsclean_ID = 0;
   Jetsclean_ISRMask = 0;
   Jetsclean_MHTMask = 0;
   Jetsclean_muonEnergyFraction = 0;
   Jetsclean_partonFlavor = 0;
   JetsJECdown = 0;
   JetsJECdown_jerFactor = 0;
   JetsJECdown_origIndex = 0;
   JetsJECup = 0;
   JetsJECup_jerFactor = 0;
   JetsJECup_origIndex = 0;
   JetsJERdown = 0;
   JetsJERdown_origIndex = 0;
   JetsJERup = 0;
   JetsJERup_origIndex = 0;
   METDown = 0;
   METPhiDown = 0;
   METPhiUp = 0;
   METUp = 0;
   Muons = 0;
   Muons_charge = 0;
   Muons_MiniIso = 0;
   Muons_MT2Activity = 0;
   Muons_MTW = 0;
   Muons_passIso = 0;
   Muons_tightID = 0;
   PDFids = 0;
   PDFweights = 0;
   Photons = 0;
   Photons_electronFakes = 0;
   Photons_fullID = 0;
   Photons_genMatched = 0;
   Photons_hadTowOverEM = 0;
   Photons_hasPixelSeed = 0;
   Photons_isEB = 0;
   Photons_nonPrompt = 0;
   Photons_passElectronVeto = 0;
   Photons_pfChargedIso = 0;
   Photons_pfChargedIsoRhoCorr = 0;
   Photons_pfGammaIso = 0;
   Photons_pfGammaIsoRhoCorr = 0;
   Photons_pfNeutralIso = 0;
   Photons_pfNeutralIsoRhoCorr = 0;
   Photons_sigmaIetaIeta = 0;
   ScaleWeights = 0;
   TAPElectronTracks = 0;
   TAPElectronTracks_activity = 0;
   TAPElectronTracks_charge = 0;
   TAPElectronTracks_mT = 0;
   TAPElectronTracks_trkiso = 0;
   TAPMuonTracks = 0;
   TAPMuonTracks_activity = 0;
   TAPMuonTracks_charge = 0;
   TAPMuonTracks_mT = 0;
   TAPMuonTracks_trkiso = 0;
   TAPPionTracks = 0;
   TAPPionTracks_activity = 0;
   TAPPionTracks_charge = 0;
   TAPPionTracks_mT = 0;
   TAPPionTracks_trkiso = 0;
   TriggerNames = 0;
   TriggerPass = 0;
   TriggerPrescales = 0;
   TriggerVersion = 0;
   ZCandidates = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   //if(isMC) fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("BTagsclean", &BTagsclean, &b_BTagsclean);
   fChain->SetBranchAddress("BTagsDeepCSV", &BTagsDeepCSV, &b_BTagsDeepCSV);
   fChain->SetBranchAddress("BTagsDeepCSVclean", &BTagsDeepCSVclean, &b_BTagsDeepCSVclean);
   if(isMC) {
      fChain->SetBranchAddress("BTagsDeepCSVJECdown", &BTagsDeepCSVJECdown, &b_BTagsDeepCSVJECdown);
      fChain->SetBranchAddress("BTagsDeepCSVJECup", &BTagsDeepCSVJECup, &b_BTagsDeepCSVJECup);
      fChain->SetBranchAddress("BTagsDeepCSVJERdown", &BTagsDeepCSVJERdown, &b_BTagsDeepCSVJERdown);
      fChain->SetBranchAddress("BTagsDeepCSVJERup", &BTagsDeepCSVJERup, &b_BTagsDeepCSVJERup);
      fChain->SetBranchAddress("BTagsJECdown", &BTagsJECdown, &b_BTagsJECdown);
      fChain->SetBranchAddress("BTagsJECup", &BTagsJECup, &b_BTagsJECup);
      fChain->SetBranchAddress("BTagsJERdown", &BTagsJERdown, &b_BTagsJERdown);
      fChain->SetBranchAddress("BTagsJERup", &BTagsJERup, &b_BTagsJERup);
   }
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   if(isMC) fChain->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi1_AK8", &DeltaPhi1_AK8, &b_DeltaPhi1_AK8);
   fChain->SetBranchAddress("DeltaPhi1clean", &DeltaPhi1clean, &b_DeltaPhi1clean);
   if(isMC) {
      fChain->SetBranchAddress("DeltaPhi1JECdown", &DeltaPhi1JECdown, &b_DeltaPhi1JECdown);
      fChain->SetBranchAddress("DeltaPhi1JECup", &DeltaPhi1JECup, &b_DeltaPhi1JECup);
      fChain->SetBranchAddress("DeltaPhi1JERdown", &DeltaPhi1JERdown, &b_DeltaPhi1JERdown);
      fChain->SetBranchAddress("DeltaPhi1JERup", &DeltaPhi1JERup, &b_DeltaPhi1JERup);
   }
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi2_AK8", &DeltaPhi2_AK8, &b_DeltaPhi2_AK8);
   fChain->SetBranchAddress("DeltaPhi2clean", &DeltaPhi2clean, &b_DeltaPhi2clean);
   if(isMC) {
      fChain->SetBranchAddress("DeltaPhi2JECdown", &DeltaPhi2JECdown, &b_DeltaPhi2JECdown);
      fChain->SetBranchAddress("DeltaPhi2JECup", &DeltaPhi2JECup, &b_DeltaPhi2JECup);
      fChain->SetBranchAddress("DeltaPhi2JERdown", &DeltaPhi2JERdown, &b_DeltaPhi2JERdown);
      fChain->SetBranchAddress("DeltaPhi2JERup", &DeltaPhi2JERup, &b_DeltaPhi2JERup);
   }
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi3clean", &DeltaPhi3clean, &b_DeltaPhi3clean);
   if(isMC) {
      fChain->SetBranchAddress("DeltaPhi3JECdown", &DeltaPhi3JECdown, &b_DeltaPhi3JECdown);
      fChain->SetBranchAddress("DeltaPhi3JECup", &DeltaPhi3JECup, &b_DeltaPhi3JECup);
      fChain->SetBranchAddress("DeltaPhi3JERdown", &DeltaPhi3JERdown, &b_DeltaPhi3JERdown);
      fChain->SetBranchAddress("DeltaPhi3JERup", &DeltaPhi3JERup, &b_DeltaPhi3JERup);
   }
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("DeltaPhi4clean", &DeltaPhi4clean, &b_DeltaPhi4clean);
   if(isMC) {
      fChain->SetBranchAddress("DeltaPhi4JECdown", &DeltaPhi4JECdown, &b_DeltaPhi4JECdown);
      fChain->SetBranchAddress("DeltaPhi4JECup", &DeltaPhi4JECup, &b_DeltaPhi4JECup);
      fChain->SetBranchAddress("DeltaPhi4JERdown", &DeltaPhi4JERdown, &b_DeltaPhi4JERdown);
      fChain->SetBranchAddress("DeltaPhi4JERup", &DeltaPhi4JERup, &b_DeltaPhi4JERup);
   }
   fChain->SetBranchAddress("DeltaPhiMin_AK8", &DeltaPhiMin_AK8, &b_DeltaPhiMin_AK8);
   fChain->SetBranchAddress("ecalBadCalibFilter", &ecalBadCalibFilter, &b_ecalBadCalibFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   //if(isMC) fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("Electrons_charge", &Electrons_charge, &b_Electrons_charge);
   fChain->SetBranchAddress("Electrons_mediumID", &Electrons_mediumID, &b_Electrons_mediumID);
   fChain->SetBranchAddress("Electrons_MiniIso", &Electrons_MiniIso, &b_Electrons_MiniIso);
   fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
   fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
   fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);
   fChain->SetBranchAddress("Electrons_tightID", &Electrons_tightID, &b_Electrons_tightID);
   if(isMC) {
      fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
      fChain->SetBranchAddress("GenElectrons_fromTau", &GenElectrons_fromTau, &b_GenElectrons_fromTau);
      fChain->SetBranchAddress("GenElectrons_MT2Activity", &GenElectrons_MT2Activity, &b_GenElectrons_MT2Activity);
      fChain->SetBranchAddress("GenElectrons_RecoTrkAct", &GenElectrons_RecoTrkAct, &b_GenElectrons_RecoTrkAct);
      fChain->SetBranchAddress("GenElectrons_RecoTrkd3", &GenElectrons_RecoTrkd3, &b_GenElectrons_RecoTrkd3);
      fChain->SetBranchAddress("GenElectrons_RecoTrkIso", &GenElectrons_RecoTrkIso, &b_GenElectrons_RecoTrkIso);
      fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
      fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
      fChain->SetBranchAddress("GenJets_HTMask", &GenJets_HTMask, &b_GenJets_HTMask);
      fChain->SetBranchAddress("GenJets_MHTMask", &GenJets_MHTMask, &b_GenJets_MHTMask);
      fChain->SetBranchAddress("GenJetsAK8", &GenJetsAK8, &b_GenJetsAK8);
      fChain->SetBranchAddress("GenJetsAK8_prunedMass", &GenJetsAK8_prunedMass, &b_GenJetsAK8_prunedMass);
      fChain->SetBranchAddress("GenJetsAK8_softDropMass", &GenJetsAK8_softDropMass, &b_GenJetsAK8_softDropMass);
      fChain->SetBranchAddress("GenMET", &GenMET, &b_GenMET);
      fChain->SetBranchAddress("GenMETPhi", &GenMETPhi, &b_GenMETPhi);
      fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
      fChain->SetBranchAddress("GenMHTPhi", &GenMHTPhi, &b_GenMHTPhi);
      fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
      fChain->SetBranchAddress("GenMuons_fromTau", &GenMuons_fromTau, &b_GenMuons_fromTau);
      fChain->SetBranchAddress("GenMuons_MT2Activity", &GenMuons_MT2Activity, &b_GenMuons_MT2Activity);
      fChain->SetBranchAddress("GenMuons_RecoTrkAct", &GenMuons_RecoTrkAct, &b_GenMuons_RecoTrkAct);
      fChain->SetBranchAddress("GenMuons_RecoTrkd3", &GenMuons_RecoTrkd3, &b_GenMuons_RecoTrkd3);
      fChain->SetBranchAddress("GenMuons_RecoTrkIso", &GenMuons_RecoTrkIso, &b_GenMuons_RecoTrkIso);
      fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
      fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
      fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
      fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
      fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
      fChain->SetBranchAddress("GenParticles_TTFlag", &GenParticles_TTFlag, &b_GenParticles_TTFlag);
      fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
      fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);
      fChain->SetBranchAddress("GenTaus_LeadRecoTrkAct", &GenTaus_LeadRecoTrkAct, &b_GenTaus_LeadRecoTrkAct);
      fChain->SetBranchAddress("GenTaus_LeadRecoTrkd3", &GenTaus_LeadRecoTrkd3, &b_GenTaus_LeadRecoTrkd3);
      fChain->SetBranchAddress("GenTaus_LeadRecoTrkIso", &GenTaus_LeadRecoTrkIso, &b_GenTaus_LeadRecoTrkIso);
      fChain->SetBranchAddress("GenTaus_LeadTrk", &GenTaus_LeadTrk, &b_GenTaus_LeadTrk);
      fChain->SetBranchAddress("GenTaus_MT2Activity", &GenTaus_MT2Activity, &b_GenTaus_MT2Activity);
      fChain->SetBranchAddress("GenTaus_NNeutralHadrons", &GenTaus_NNeutralHadrons, &b_GenTaus_NNeutralHadrons);
      fChain->SetBranchAddress("GenTaus_NProngs", &GenTaus_NProngs, &b_GenTaus_NProngs);
      fChain->SetBranchAddress("GenTaus_Nu", &GenTaus_Nu, &b_GenTaus_Nu);
      fChain->SetBranchAddress("GenTops", &GenTops, &b_GenTops);
      fChain->SetBranchAddress("GenTopWeight", &GenTopWeight, &b_GenTopWeight);
   }
   if(fChain->GetBranch("globalTightHalo2016Filter"))
      fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   else if(fChain->GetBranch("globalSuperTightHalo2016Filter"))
      fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalSuperTightHalo2016Filter, &b_globalSuperTightHalo2016Filter);
   fChain->SetBranchAddress("hasGenPromptPhoton", &hasGenPromptPhoton, &b_hasGenPromptPhoton);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
   fChain->SetBranchAddress("HT5clean", &HT5clean, &b_HT5clean);
   if(isMC) {
      fChain->SetBranchAddress("HT5JECdown", &HT5JECdown, &b_HT5JECdown);
      fChain->SetBranchAddress("HT5JECup", &HT5JECup, &b_HT5JECup);
      fChain->SetBranchAddress("HT5JERdown", &HT5JERdown, &b_HT5JERdown);
      fChain->SetBranchAddress("HT5JERup", &HT5JERup, &b_HT5JERup);
   }
   fChain->SetBranchAddress("HTclean", &HTclean, &b_HTclean);
   //fChain->SetBranchAddress("HTOnline", &HTOnline, &b_HTOnline);
   if(isMC) {
      fChain->SetBranchAddress("HTJECdown", &HTJECdown, &b_HTJECdown);
      fChain->SetBranchAddress("HTJECup", &HTJECup, &b_HTJECup);
      fChain->SetBranchAddress("HTJERdown", &HTJERdown, &b_HTJERdown);
      fChain->SetBranchAddress("HTJERup", &HTJERup, &b_HTJERup);
   }
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoElectronTracksclean", &isoElectronTracksclean, &b_isoElectronTracksclean);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoMuonTracksclean", &isoMuonTracksclean, &b_isoMuonTracksclean);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("isoPionTracksclean", &isoPionTracksclean, &b_isoPionTracksclean);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDAK8", &JetIDAK8, &b_JetIDAK8);
   fChain->SetBranchAddress("JetIDAK8Clean", &JetIDAK8Clean, &b_JetIDAK8Clean);
   fChain->SetBranchAddress("JetIDclean", &JetIDclean, &b_JetIDclean);
   if(isMC) {
      fChain->SetBranchAddress("JetIDJECdown", &JetIDJECdown, &b_JetIDJECdown);
      fChain->SetBranchAddress("JetIDJECup", &JetIDJECup, &b_JetIDJECup);
      fChain->SetBranchAddress("JetIDJERdown", &JetIDJERdown, &b_JetIDJERdown);
      fChain->SetBranchAddress("JetIDJERup", &JetIDJERup, &b_JetIDJERup);
   }
   fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
   fChain->SetBranchAddress("Jets_axismajor", &Jets_axismajor, &b_Jets_axismajor);
   fChain->SetBranchAddress("Jets_axisminor", &Jets_axisminor, &b_Jets_axisminor);
   fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVBvsAll", &Jets_bJetTagDeepCSVBvsAll, &b_Jets_bJetTagDeepCSVBvsAll);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVCvsB", &Jets_bJetTagDeepCSVCvsB, &b_Jets_bJetTagDeepCSVCvsB);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVCvsL", &Jets_bJetTagDeepCSVCvsL, &b_Jets_bJetTagDeepCSVCvsL);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobb", &Jets_bJetTagDeepCSVprobb, &b_Jets_bJetTagDeepCSVprobb);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobbb", &Jets_bJetTagDeepCSVprobbb, &b_Jets_bJetTagDeepCSVprobbb);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobc", &Jets_bJetTagDeepCSVprobc, &b_Jets_bJetTagDeepCSVprobc);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobudsg", &Jets_bJetTagDeepCSVprobudsg, &b_Jets_bJetTagDeepCSVprobudsg);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobb", &Jets_bJetTagDeepFlavourprobb, &b_Jets_bJetTagDeepFlavourprobb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobbb", &Jets_bJetTagDeepFlavourprobbb, &b_Jets_bJetTagDeepFlavourprobbb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobc", &Jets_bJetTagDeepFlavourprobc, &b_Jets_bJetTagDeepFlavourprobc);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobg", &Jets_bJetTagDeepFlavourprobg, &b_Jets_bJetTagDeepFlavourprobg);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourproblepb", &Jets_bJetTagDeepFlavourproblepb, &b_Jets_bJetTagDeepFlavourproblepb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobuds", &Jets_bJetTagDeepFlavourprobuds, &b_Jets_bJetTagDeepFlavourprobuds);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
   fChain->SetBranchAddress("Jets_electronEnergyFraction", &Jets_electronEnergyFraction, &b_Jets_electronEnergyFraction);
   fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
   fChain->SetBranchAddress("Jets_hfEMEnergyFraction", &Jets_hfEMEnergyFraction, &b_Jets_hfEMEnergyFraction);
   fChain->SetBranchAddress("Jets_hfHadronEnergyFraction", &Jets_hfHadronEnergyFraction, &b_Jets_hfHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
   fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);
   if(isMC) {
      fChain->SetBranchAddress("Jets_ISRMask", &Jets_ISRMask, &b_Jets_ISRMask);
      fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
      fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
      fChain->SetBranchAddress("Jets_jerFactor", &Jets_jerFactor, &b_Jets_jerFactor);
      fChain->SetBranchAddress("Jets_jerFactorDown", &Jets_jerFactorDown, &b_Jets_jerFactorDown);
      fChain->SetBranchAddress("Jets_jerFactorUp", &Jets_jerFactorUp, &b_Jets_jerFactorUp);
   }
   fChain->SetBranchAddress("Jets_LeptonMask", &Jets_LeptonMask, &b_Jets_LeptonMask);
   fChain->SetBranchAddress("Jets_MHTMask", &Jets_MHTMask, &b_Jets_MHTMask);
   fChain->SetBranchAddress("Jets_multiplicity", &Jets_multiplicity, &b_Jets_multiplicity);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
   if(isMC) fChain->SetBranchAddress("Jets_origIndex", &Jets_origIndex, &b_Jets_origIndex);
   fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor, &b_Jets_partonFlavor);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("Jets_ptD", &Jets_ptD, &b_Jets_ptD);
   fChain->SetBranchAddress("Jets_qgLikelihood", &Jets_qgLikelihood, &b_Jets_qgLikelihood);
   fChain->SetBranchAddress("JetsAK8", &JetsAK8, &b_JetsAK8);
   fChain->SetBranchAddress("JetsAK8_axismajor", &JetsAK8_axismajor, &b_JetsAK8_axismajor);
   fChain->SetBranchAddress("JetsAK8_axisminor", &JetsAK8_axisminor, &b_JetsAK8_axisminor);
   fChain->SetBranchAddress("JetsAK8_doubleBDiscriminator", &JetsAK8_doubleBDiscriminator, &b_JetsAK8_doubleBDiscriminator);
   fChain->SetBranchAddress("JetsAK8_ecfN2b1", &JetsAK8_ecfN2b1, &b_JetsAK8_ecfN2b1);
   fChain->SetBranchAddress("JetsAK8_ecfN2b2", &JetsAK8_ecfN2b2, &b_JetsAK8_ecfN2b2);
   fChain->SetBranchAddress("JetsAK8_ecfN3b1", &JetsAK8_ecfN3b1, &b_JetsAK8_ecfN3b1);
   fChain->SetBranchAddress("JetsAK8_ecfN3b2", &JetsAK8_ecfN3b2, &b_JetsAK8_ecfN3b2);
   fChain->SetBranchAddress("JetsAK8_girth", &JetsAK8_girth, &b_JetsAK8_girth);
   fChain->SetBranchAddress("JetsAK8_hDiscriminatorDeep", &JetsAK8_hDiscriminatorDeep, &b_JetsAK8_hDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_ID", &JetsAK8_ID, &b_JetsAK8_ID);
   fChain->SetBranchAddress("JetsAK8_lean", &JetsAK8_lean, &b_JetsAK8_lean);
   fChain->SetBranchAddress("JetsAK8_momenthalf", &JetsAK8_momenthalf, &b_JetsAK8_momenthalf);
   fChain->SetBranchAddress("JetsAK8_multiplicity", &JetsAK8_multiplicity, &b_JetsAK8_multiplicity);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau1", &JetsAK8_NsubjettinessTau1, &b_JetsAK8_NsubjettinessTau1);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau2", &JetsAK8_NsubjettinessTau2, &b_JetsAK8_NsubjettinessTau2);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau3", &JetsAK8_NsubjettinessTau3, &b_JetsAK8_NsubjettinessTau3);
   fChain->SetBranchAddress("JetsAK8_NumBhadrons", &JetsAK8_NumBhadrons, &b_JetsAK8_NumBhadrons);
   fChain->SetBranchAddress("JetsAK8_NumChadrons", &JetsAK8_NumChadrons, &b_JetsAK8_NumChadrons);
   fChain->SetBranchAddress("JetsAK8_overflow", &JetsAK8_overflow, &b_JetsAK8_overflow);
   fChain->SetBranchAddress("JetsAK8_prunedMass", &JetsAK8_prunedMass, &b_JetsAK8_prunedMass);
   fChain->SetBranchAddress("JetsAK8_ptD", &JetsAK8_ptD, &b_JetsAK8_ptD);
   fChain->SetBranchAddress("JetsAK8_ptdrlog", &JetsAK8_ptdrlog, &b_JetsAK8_ptdrlog);
   fChain->SetBranchAddress("JetsAK8_softDropMass", &JetsAK8_softDropMass, &b_JetsAK8_softDropMass);
   fChain->SetBranchAddress("JetsAK8_subjets", &JetsAK8_subjets, &b_JetsAK8_subjets);
   fChain->SetBranchAddress("JetsAK8_subjets_axismajor", &JetsAK8_subjets_axismajor, &b_JetsAK8_subjets_axismajor);
   fChain->SetBranchAddress("JetsAK8_subjets_axisminor", &JetsAK8_subjets_axisminor, &b_JetsAK8_subjets_axisminor);
   fChain->SetBranchAddress("JetsAK8_subjets_bDiscriminatorCSV", &JetsAK8_subjets_bDiscriminatorCSV, &b_JetsAK8_subjets_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsAK8_subjets_multiplicity", &JetsAK8_subjets_multiplicity, &b_JetsAK8_subjets_multiplicity);
   fChain->SetBranchAddress("JetsAK8_subjets_ptD", &JetsAK8_subjets_ptD, &b_JetsAK8_subjets_ptD);
   fChain->SetBranchAddress("JetsAK8_tDiscriminatorDeep", &JetsAK8_tDiscriminatorDeep, &b_JetsAK8_tDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_wDiscriminatorDeep", &JetsAK8_wDiscriminatorDeep, &b_JetsAK8_wDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_zDiscriminatorDeep", &JetsAK8_zDiscriminatorDeep, &b_JetsAK8_zDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8Clean", &JetsAK8Clean, &b_JetsAK8Clean);
   fChain->SetBranchAddress("JetsAK8Clean_doubleBDiscriminator", &JetsAK8Clean_doubleBDiscriminator, &b_JetsAK8Clean_doubleBDiscriminator);
   fChain->SetBranchAddress("JetsAK8Clean_ecfN2b1", &JetsAK8Clean_ecfN2b1, &b_JetsAK8Clean_ecfN2b1);
   fChain->SetBranchAddress("JetsAK8Clean_ecfN2b2", &JetsAK8Clean_ecfN2b2, &b_JetsAK8Clean_ecfN2b2);
   fChain->SetBranchAddress("JetsAK8Clean_ecfN3b1", &JetsAK8Clean_ecfN3b1, &b_JetsAK8Clean_ecfN3b1);
   fChain->SetBranchAddress("JetsAK8Clean_ecfN3b2", &JetsAK8Clean_ecfN3b2, &b_JetsAK8Clean_ecfN3b2);
   fChain->SetBranchAddress("JetsAK8Clean_ID", &JetsAK8Clean_ID, &b_JetsAK8Clean_ID);
   fChain->SetBranchAddress("JetsAK8Clean_NsubjettinessTau1", &JetsAK8Clean_NsubjettinessTau1, &b_JetsAK8Clean_NsubjettinessTau1);
   fChain->SetBranchAddress("JetsAK8Clean_NsubjettinessTau2", &JetsAK8Clean_NsubjettinessTau2, &b_JetsAK8Clean_NsubjettinessTau2);
   fChain->SetBranchAddress("JetsAK8Clean_NsubjettinessTau3", &JetsAK8Clean_NsubjettinessTau3, &b_JetsAK8Clean_NsubjettinessTau3);
   fChain->SetBranchAddress("JetsAK8Clean_NumBhadrons", &JetsAK8Clean_NumBhadrons, &b_JetsAK8Clean_NumBhadrons);
   fChain->SetBranchAddress("JetsAK8Clean_NumChadrons", &JetsAK8Clean_NumChadrons, &b_JetsAK8Clean_NumChadrons);
   fChain->SetBranchAddress("JetsAK8Clean_prunedMass", &JetsAK8Clean_prunedMass, &b_JetsAK8Clean_prunedMass);
   fChain->SetBranchAddress("JetsAK8Clean_softDropMass", &JetsAK8Clean_softDropMass, &b_JetsAK8Clean_softDropMass);
   fChain->SetBranchAddress("JetsAK8Clean_subjets", &JetsAK8Clean_subjets, &b_JetsAK8Clean_subjets);
   fChain->SetBranchAddress("JetsAK8Clean_subjets_bDiscriminatorCSV", &JetsAK8Clean_subjets_bDiscriminatorCSV, &b_JetsAK8Clean_subjets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jetsclean", &Jetsclean, &b_Jetsclean);
   fChain->SetBranchAddress("Jetsclean_bDiscriminatorCSV", &Jetsclean_bDiscriminatorCSV, &b_Jetsclean_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVBvsAll", &Jetsclean_bJetTagDeepCSVBvsAll, &b_Jetsclean_bJetTagDeepCSVBvsAll);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVCvsB", &Jetsclean_bJetTagDeepCSVCvsB, &b_Jetsclean_bJetTagDeepCSVCvsB);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVCvsL", &Jetsclean_bJetTagDeepCSVCvsL, &b_Jetsclean_bJetTagDeepCSVCvsL);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVprobb", &Jetsclean_bJetTagDeepCSVprobb, &b_Jetsclean_bJetTagDeepCSVprobb);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVprobbb", &Jetsclean_bJetTagDeepCSVprobbb, &b_Jetsclean_bJetTagDeepCSVprobbb);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVprobc", &Jetsclean_bJetTagDeepCSVprobc, &b_Jetsclean_bJetTagDeepCSVprobc);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepCSVprobudsg", &Jetsclean_bJetTagDeepCSVprobudsg, &b_Jetsclean_bJetTagDeepCSVprobudsg);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourprobb", &Jetsclean_bJetTagDeepFlavourprobb, &b_Jetsclean_bJetTagDeepFlavourprobb);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourprobbb", &Jetsclean_bJetTagDeepFlavourprobbb, &b_Jetsclean_bJetTagDeepFlavourprobbb);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourprobc", &Jetsclean_bJetTagDeepFlavourprobc, &b_Jetsclean_bJetTagDeepFlavourprobc);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourprobg", &Jetsclean_bJetTagDeepFlavourprobg, &b_Jetsclean_bJetTagDeepFlavourprobg);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourproblepb", &Jetsclean_bJetTagDeepFlavourproblepb, &b_Jetsclean_bJetTagDeepFlavourproblepb);
   fChain->SetBranchAddress("Jetsclean_bJetTagDeepFlavourprobuds", &Jetsclean_bJetTagDeepFlavourprobuds, &b_Jetsclean_bJetTagDeepFlavourprobuds);
   fChain->SetBranchAddress("Jetsclean_chargedHadronEnergyFraction", &Jetsclean_chargedHadronEnergyFraction, &b_Jetsclean_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jetsclean_hadronFlavor", &Jetsclean_hadronFlavor, &b_Jetsclean_hadronFlavor);
   fChain->SetBranchAddress("Jetsclean_HTMask", &Jetsclean_HTMask, &b_Jetsclean_HTMask);
   fChain->SetBranchAddress("Jetsclean_ID", &Jetsclean_ID, &b_Jetsclean_ID);
   if(isMC) fChain->SetBranchAddress("Jetsclean_ISRMask", &Jetsclean_ISRMask, &b_Jetsclean_ISRMask);
   fChain->SetBranchAddress("Jetsclean_MHTMask", &Jetsclean_MHTMask, &b_Jetsclean_MHTMask);
   fChain->SetBranchAddress("Jetsclean_muonEnergyFraction", &Jetsclean_muonEnergyFraction, &b_Jetsclean_muonEnergyFraction);
   fChain->SetBranchAddress("Jetsclean_partonFlavor", &Jetsclean_partonFlavor, &b_Jetsclean_partonFlavor);
   if(isMC) {
      if(debug) fChain->SetBranchAddress("JetsJECdown", &JetsJECdown, &b_JetsJECdown);
      fChain->SetBranchAddress("JetsJECdown_jerFactor", &JetsJECdown_jerFactor, &b_JetsJECdown_jerFactor);
      fChain->SetBranchAddress("JetsJECdown_origIndex", &JetsJECdown_origIndex, &b_JetsJECdown_origIndex);
      if(debug) fChain->SetBranchAddress("JetsJECup", &JetsJECup, &b_JetsJECup);
      fChain->SetBranchAddress("JetsJECup_jerFactor", &JetsJECup_jerFactor, &b_JetsJECup_jerFactor);
      fChain->SetBranchAddress("JetsJECup_origIndex", &JetsJECup_origIndex, &b_JetsJECup_origIndex);
      if(debug) fChain->SetBranchAddress("JetsJERdown", &JetsJERdown, &b_JetsJERdown);
      fChain->SetBranchAddress("JetsJERdown_origIndex", &JetsJERdown_origIndex, &b_JetsJERdown_origIndex);
      if(debug) fChain->SetBranchAddress("JetsJERup", &JetsJERup, &b_JetsJERup);
      fChain->SetBranchAddress("JetsJERup_origIndex", &JetsJERup_origIndex, &b_JetsJERup_origIndex);
      fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
      fChain->SetBranchAddress("madMinDeltaRStatus", &madMinDeltaRStatus, &b_madMinDeltaRStatus);
      fChain->SetBranchAddress("madMinPhotonDeltaR", &madMinPhotonDeltaR, &b_madMinPhotonDeltaR);
   }
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METclean", &METclean, &b_METclean);
   if(isMC) fChain->SetBranchAddress("METDown", &METDown, &b_METDown);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METPhiclean", &METPhiclean, &b_METPhiclean);
   if(isMC) {
      fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
      fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
   }
   fChain->SetBranchAddress("METSignificance", &METSignificance, &b_METSignificance);
   fChain->SetBranchAddress("METSignificanceclean", &METSignificanceclean, &b_METSignificanceclean);
   if(isMC) fChain->SetBranchAddress("METUp", &METUp, &b_METUp);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHTclean", &MHTclean, &b_MHTclean);
   //fChain->SetBranchAddress("MHTOnline", &MHTOnline, &b_MHTOnline);
   if(isMC) {
      fChain->SetBranchAddress("MHTJECdown", &MHTJECdown, &b_MHTJECdown);
      fChain->SetBranchAddress("MHTJECup", &MHTJECup, &b_MHTJECup);
      fChain->SetBranchAddress("MHTJERdown", &MHTJERdown, &b_MHTJERdown);
      fChain->SetBranchAddress("MHTJERup", &MHTJERup, &b_MHTJERup);
   }
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
   fChain->SetBranchAddress("MHTPhiclean", &MHTPhiclean, &b_MHTPhiclean);
   if(isMC) {
      fChain->SetBranchAddress("MHTPhiJECdown", &MHTPhiJECdown, &b_MHTPhiJECdown);
      fChain->SetBranchAddress("MHTPhiJECup", &MHTPhiJECup, &b_MHTPhiJECup);
      fChain->SetBranchAddress("MHTPhiJERdown", &MHTPhiJERdown, &b_MHTPhiJERdown);
      fChain->SetBranchAddress("MHTPhiJERup", &MHTPhiJERup, &b_MHTPhiJERup);
   }
   fChain->SetBranchAddress("MJJ_AK8", &MJJ_AK8, &b_MJJ_AK8);
   fChain->SetBranchAddress("Mmc_AK8", &Mmc_AK8, &b_Mmc_AK8);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("MT_AK8", &MT_AK8, &b_MT_AK8);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("Muons_charge", &Muons_charge, &b_Muons_charge);
   fChain->SetBranchAddress("Muons_MiniIso", &Muons_MiniIso, &b_Muons_MiniIso);
   fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
   fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
   fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
   fChain->SetBranchAddress("Muons_tightID", &Muons_tightID, &b_Muons_tightID);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NElectrons", &NElectrons, &b_NElectrons);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsclean", &NJetsclean, &b_NJetsclean);
   if(isMC) {
      fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
      fChain->SetBranchAddress("NJetsISRclean", &NJetsISRclean, &b_NJetsISRclean);
      fChain->SetBranchAddress("NJetsISRJECdown", &NJetsISRJECdown, &b_NJetsISRJECdown);
      fChain->SetBranchAddress("NJetsISRJECup", &NJetsISRJECup, &b_NJetsISRJECup);
      fChain->SetBranchAddress("NJetsISRJERdown", &NJetsISRJERdown, &b_NJetsISRJERdown);
      fChain->SetBranchAddress("NJetsISRJERup", &NJetsISRJERup, &b_NJetsISRJERup);
      fChain->SetBranchAddress("NJetsJECdown", &NJetsJECdown, &b_NJetsJECdown);
      fChain->SetBranchAddress("NJetsJECup", &NJetsJECup, &b_NJetsJECup);
      fChain->SetBranchAddress("NJetsJERdown", &NJetsJERdown, &b_NJetsJERdown);
      fChain->SetBranchAddress("NJetsJERup", &NJetsJERup, &b_NJetsJERup);
   }
   fChain->SetBranchAddress("NMuons", &NMuons, &b_NMuons);
   if(isMC) {
      fChain->SetBranchAddress("NumEvents", &NumEvents, &b_NumEvents);
      fChain->SetBranchAddress("NumInteractions", &NumInteractions, &b_NumInteractions);
   }
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   if(isMC) {
      fChain->SetBranchAddress("PDFids", &PDFids, &b_PDFids);
      fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
   }
   fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
   fChain->SetBranchAddress("Photons", &Photons, &b_Photons);
   fChain->SetBranchAddress("Photons_electronFakes", &Photons_electronFakes, &b_Photons_electronFakes);
   fChain->SetBranchAddress("Photons_fullID", &Photons_fullID, &b_Photons_fullID);
   fChain->SetBranchAddress("Photons_genMatched", &Photons_genMatched, &b_Photons_genMatched);
   fChain->SetBranchAddress("Photons_hadTowOverEM", &Photons_hadTowOverEM, &b_Photons_hadTowOverEM);
   fChain->SetBranchAddress("Photons_hasPixelSeed", &Photons_hasPixelSeed, &b_Photons_hasPixelSeed);
   fChain->SetBranchAddress("Photons_isEB", &Photons_isEB, &b_Photons_isEB);
   fChain->SetBranchAddress("Photons_nonPrompt", &Photons_nonPrompt, &b_Photons_nonPrompt);
   fChain->SetBranchAddress("Photons_passElectronVeto", &Photons_passElectronVeto, &b_Photons_passElectronVeto);
   fChain->SetBranchAddress("Photons_pfChargedIso", &Photons_pfChargedIso, &b_Photons_pfChargedIso);
   fChain->SetBranchAddress("Photons_pfChargedIsoRhoCorr", &Photons_pfChargedIsoRhoCorr, &b_Photons_pfChargedIsoRhoCorr);
   fChain->SetBranchAddress("Photons_pfGammaIso", &Photons_pfGammaIso, &b_Photons_pfGammaIso);
   fChain->SetBranchAddress("Photons_pfGammaIsoRhoCorr", &Photons_pfGammaIsoRhoCorr, &b_Photons_pfGammaIsoRhoCorr);
   fChain->SetBranchAddress("Photons_pfNeutralIso", &Photons_pfNeutralIso, &b_Photons_pfNeutralIso);
   fChain->SetBranchAddress("Photons_pfNeutralIsoRhoCorr", &Photons_pfNeutralIsoRhoCorr, &b_Photons_pfNeutralIsoRhoCorr);
   fChain->SetBranchAddress("Photons_sigmaIetaIeta", &Photons_sigmaIetaIeta, &b_Photons_sigmaIetaIeta);
   //fChain->SetBranchAddress("PrescaleWeightHT", &PrescaleWeightHT, &b_PrescaleWeightHT);
   if(isMC) fChain->SetBranchAddress("PmssmId", &PmssmId, &b_PmssmId);
   fChain->SetBranchAddress("PrimaryVertexFilter", &PrimaryVertexFilter, &b_PrimaryVertexFilter);
   if(isMC) {
      fChain->SetBranchAddress("puSysDown", &puSysDown, &b_puSysDown);
      fChain->SetBranchAddress("puSysUp", &puSysUp, &b_puSysUp);
      fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
      fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
      fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
      fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
   }
   fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
   fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
   fChain->SetBranchAddress("TAPElectronTracks_charge", &TAPElectronTracks_charge, &b_TAPElectronTracks_charge);
   fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
   fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
   fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
   fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
   fChain->SetBranchAddress("TAPMuonTracks_charge", &TAPMuonTracks_charge, &b_TAPMuonTracks_charge);
   fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
   fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
   fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
   fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
   fChain->SetBranchAddress("TAPPionTracks_charge", &TAPPionTracks_charge, &b_TAPPionTracks_charge);
   fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
   fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
   fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
   fChain->SetBranchAddress("TriggerVersion", &TriggerVersion, &b_TriggerVersion);
   if(isMC) {
      fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
      fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   }
   fChain->SetBranchAddress("ZCandidates", &ZCandidates, &b_ZCandidates);
   Notify();
}

//______________________________________________________________________________
Bool_t EventNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

//______________________________________________________________________________
void EventNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

//______________________________________________________________________________
Int_t EventNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

//______________________________________________________________________________
string EventNtuple::getLVString(const TLorentzVector &lv) {
    std::stringstream ss;
    ss << "(" << lv.Pt() << "," << lv.Eta() << "," << lv.Phi() << "," << lv.E() << ")";
    return ss.str();
}
