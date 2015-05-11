#include <vector>
#include <string>
#include "TChain.h"

    int             event_;
    float           EventWeight_;
    float           EventWeightNeg_;
    int             Npu_;
    int             Npv_;
    int             Nfatjet_;
    int             Nskinnyjet_;
    int             NBtagCSVM_;
    float           MJ_;
    float           MET_;
    float           HT_;
    float           METPhi_;
    vector<float>   *mj_;
    vector<float>   *FatjetPt_;
    vector<float>   *FatjetEta_;
    vector<float>   *FatjetPhi_;
    vector<float>   *FatjetN_;
    vector<float>   *RA4MusPt_;
    vector<float>   *RA4MusPhi_;
    vector<float>   *RA4MusEta_;
    vector<float>   *RA4ElsPt_;
    vector<float>   *RA4ElsPhi_;
    vector<float>   *RA4ElsEta_;
    vector<float>   *JetPt_;
    vector<float>   *JetEta_;
    vector<float>   *JetPhi_;
    vector<float>   *JetCSV_;
    vector<float>   *RA4MusVetoPt_;
    vector<float>   *RA4MusVetoEta_;
    vector<float>   *RA4MusVetoPhi_;
    vector<float>   *RA4ElsVetoPt_;
    vector<float>   *RA4ElsVetoEta_;
    vector<float>   *RA4ElsVetoPhi_;
    vector<float>   *GenPt_;
    vector<float>   *GenEta_;
    vector<float>   *GenPhi_;
    vector<float>   *GenId_;
    vector<float>   *GenMId_;
    vector<float>   *GenGMId_;

    vector<float>   *IsoTrkVetoElsPt_;
    vector<float>   *IsoTrkVetoElsEta_;
    vector<float>   *IsoTrkVetoElsPhi_;
    vector<float>   *IsoTrkVetoMusPt_;
    vector<float>   *IsoTrkVetoMusEta_;
    vector<float>   *IsoTrkVetoMusPhi_;
    vector<float>   *IsoTrkVetoHadPt_;
    vector<float>   *IsoTrkVetoHadEta_;
    vector<float>   *IsoTrkVetoHadPhi_;

    // Change for Manuel's Code // 
    vector<bool> *JetIsLep_;
    int nels_;
    int nmus_;
    int nvels_;
    int nvmus_;
    float mt_;
    unsigned int  mc_type_;

    vector<int> *tks_id_;
    vector<float> *tks_pt_;
    vector<float> *tks_eta_;
    vector<float> *tks_phi_;
    vector<float> *tks_mini_ch_;
    //                      //

    bool        TrigMuon_;
    bool        TrigSingleMuon_;
    float        top1pT_;
    float        top1Phi_;
    float        top2pT_;
    float        top2Phi_;
    
    TBranch         *b_event;   //!
    TBranch         *b_EventWeight;   //!
    TBranch         *b_EventWeightNeg;   //!
    TBranch         *b_Npu;   //!
    TBranch         *b_Npv;   //!
    TBranch         *b_Nfatjet;   //!
    TBranch         *b_Nskinnyjet;   //!
    TBranch         *b_NBtagCSVM;   //!
    TBranch         *b_MJ;   //!
    TBranch         *b_MET;   //!
    TBranch         *b_HT;   //!
    TBranch         *b_METPhi;   //!
    TBranch         *b_mj;   //!
    TBranch         *b_FatjetPt;   //!
    TBranch         *b_FatjetEta;   //!
    TBranch         *b_FatjetPhi;   //!
    TBranch         *b_FatjetN;   //!
    TBranch         *b_RA4MusPt;   //!
    TBranch         *b_RA4MusPhi;   //!
    TBranch         *b_RA4MusEta;   //!
    TBranch         *b_RA4ElsPt;   //!
    TBranch         *b_RA4ElsPhi;   //!
    TBranch         *b_RA4ElsEta;   //!
    TBranch         *b_JetPt;   //!
    TBranch         *b_JetEta;   //!
    TBranch         *b_JetPhi;   //!
    TBranch         *b_JetCSV;   //!
    TBranch         *b_RA4MusVetoPt;   //!
    TBranch         *b_RA4MusVetoEta;   //!
    TBranch         *b_RA4MusVetoPhi;   //!
    TBranch         *b_RA4ElsVetoPt;   //!
    TBranch         *b_RA4ElsVetoEta;   //!
    TBranch         *b_RA4ElsVetoPhi;   //!
    TBranch         *b_GenPt;   //!
    TBranch         *b_GenEta;   //!
    TBranch         *b_GenPhi;   //!
    TBranch         *b_GenId;   //!
    TBranch         *b_GenMId;   //!
    TBranch         *b_GenGMId;   //!

    TBranch         *b_IsoTrkVetoElsPt;
    TBranch         *b_IsoTrkVetoElsEta;
    TBranch         *b_IsoTrkVetoElsPhi;
    TBranch         *b_IsoTrkVetoMusPt;
    TBranch         *b_IsoTrkVetoMusEta;
    TBranch         *b_IsoTrkVetoMusPhi;
    TBranch         *b_IsoTrkVetoHadPt;
    TBranch         *b_IsoTrkVetoHadEta;
    TBranch         *b_IsoTrkVetoHadPhi;

    TBranch         *b_TrigMuon; 
    TBranch         *b_TrigSingleMuon; 
    TBranch         *b_top1pT; 
    TBranch         *b_top1Phi; 
    TBranch         *b_top2pT; 
    TBranch         *b_top2Phi;     
// Changes for Manuel's Code //
TBranch *b_nmus;
TBranch *b_nels;
TBranch *b_nvmus;
TBranch *b_nvels;
TBranch *b_mt;
TBranch *b_mc_type;
TBranch *b_JetIsLep;

TBranch *b_tks_id;
TBranch *b_tks_pt;
TBranch *b_tks_eta;
TBranch *b_tks_phi;
TBranch *b_tks_mini_ch;

//                         //

void InitBaby(TChain *ch)
{
    mj_        = 0;
    FatjetPt_  = 0;
    FatjetEta_ = 0;
    FatjetPhi_ = 0;
    FatjetN_ = 0;
    RA4MusPt_  = 0;
    RA4MusPhi_ = 0;
    RA4MusEta_ = 0;
    RA4ElsPt_  = 0;
    RA4ElsPhi_  = 0;
    RA4ElsEta_  = 0;
    JetPt_  = 0;
    JetEta_ = 0;
    JetPhi_ = 0;
    JetCSV_ = 0;
    RA4MusVetoPt_  = 0;
    RA4MusVetoEta_  = 0;
    RA4MusVetoPhi_  = 0;
    RA4ElsVetoPt_  = 0;
    RA4ElsVetoEta_  = 0;
    RA4ElsVetoPhi_  = 0;
    GenPt_  = 0;
    GenEta_  = 0;
    GenPhi_  = 0;
    GenId_  = 0;
    GenMId_  = 0;
    GenGMId_  = 0;

    //Added for Manuel Code \\
    JetIsLep_ = 0;
    //                      \\

    IsoTrkVetoElsPt_  = 0;
    IsoTrkVetoElsEta_  = 0;
    IsoTrkVetoElsPhi_  = 0;
    IsoTrkVetoMusPt_  = 0;
    IsoTrkVetoMusEta_  = 0;
    IsoTrkVetoMusPhi_  = 0;
    IsoTrkVetoHadPt_  = 0;
    IsoTrkVetoHadEta_  = 0;
    IsoTrkVetoHadPhi_  = 0;

    // Changed for manuel tuples                   \\
    ch->SetBranchAddress("event",           &event_,         &b_event);
    ch->SetBranchAddress("weight",     &EventWeight_,   &b_EventWeight);
    ch->SetBranchAddress("ntrupv",             &Npu_,           &b_Npu);
    ch->SetBranchAddress("npv",             &Npv_,           &b_Npv);
    ch->SetBranchAddress("nfjets",    &Nfatjet_,       &b_Nfatjet);
    ch->SetBranchAddress("njets",      &Nskinnyjet_,    &b_Nskinnyjet);
    ch->SetBranchAddress("nbm",       &NBtagCSVM_,     &b_NBtagCSVM);
    ch->SetBranchAddress("mj",         &MJ_,            &b_MJ);
    ch->SetBranchAddress("met",             &MET_,           &b_MET);
    ch->SetBranchAddress("ht",              &HT_,            &b_HT);
    ch->SetBranchAddress("met_phi",          &METPhi_,        &b_METPhi);
    ch->SetBranchAddress("fjets_m",         &mj_,            &b_mj);
    ch->SetBranchAddress("fjets_pt",   &FatjetPt_,      &b_FatjetPt);
    ch->SetBranchAddress("fjets_eta",  &FatjetEta_,     &b_FatjetEta);
    ch->SetBranchAddress("fjets_phi",  &FatjetPhi_,     &b_FatjetPhi);   

    ch->SetBranchAddress("nels",        &nels_,      &b_nels);
    ch->SetBranchAddress("nmus",        &nmus_,      &b_nmus);
    ch->SetBranchAddress("nvels",       &nvels_,     &b_nvels);
    ch->SetBranchAddress("nvmus",       &nvmus_,     &b_nvmus);
    ch->SetBranchAddress("mt",          &mt_,        &b_mt);
    ch->SetBranchAddress("mc_type",     &mc_type_,   &b_mc_type);
  //                                                                    \\
    
    // Changed for Manuel Tuples \\
    ch->SetBranchAddress("mus_pt",        &RA4MusPt_,      &b_RA4MusPt);
    ch->SetBranchAddress("mus_phi",       &RA4MusPhi_,     &b_RA4MusPhi);
    ch->SetBranchAddress("mus_eta",       &RA4MusEta_,     &b_RA4MusEta);
    ch->SetBranchAddress("els_pt",        &RA4ElsPt_,      &b_RA4ElsPt);
    ch->SetBranchAddress("els_phi",       &RA4ElsPhi_,     &b_RA4ElsPhi);
    ch->SetBranchAddress("els_eta",       &RA4ElsEta_,     &b_RA4ElsEta);

    ch->SetBranchAddress("jets_pt",           &JetPt_,         &b_JetPt);
    ch->SetBranchAddress("jets_phi",          &JetPhi_,        &b_JetPhi);
    ch->SetBranchAddress("jets_eta",          &JetEta_,        &b_JetEta);
    ch->SetBranchAddress("jets_csv",          &JetCSV_,        &b_JetCSV);
    ch->SetBranchAddress("jets_islep",        &JetIsLep_,      &b_JetIsLep);

    ch->SetBranchAddress("mc_id",           &GenId_,         &b_GenId);
    ch->SetBranchAddress("mc_mom",          &GenMId_,        &b_GenMId);
    //    ch->SetBranchAddress("mc_gmom",         &GenGMId_,       &b_GenGMId);
    ch->SetBranchAddress("mc_pt",           &GenPt_,         &b_GenPt);
    ch->SetBranchAddress("mc_eta",          &GenEta_,        &b_GenEta);
    ch->SetBranchAddress("mc_phi",          &GenPhi_,        &b_GenPhi);
    
    ch->SetBranchAddress("tks_id",        &tks_id_,      &b_tks_id);
    ch->SetBranchAddress("tks_pt",        &tks_pt_,      &b_tks_pt);
    ch->SetBranchAddress("tks_phi",        &tks_phi_,      &b_tks_phi);
    ch->SetBranchAddress("tks_eta",        &tks_eta_,      &b_tks_eta);
    ch->SetBranchAddress("tks_mini_ch",        &tks_mini_ch_,      &b_tks_mini_ch);
    //                              //

    //ch->SetBranchAddress("top1pT",        &top1pT_, &b_top1pT);
    //ch->SetBranchAddress("top1Phi",       &top1Phi_, &b_top1Phi);
    //ch->SetBranchAddress("top2pT",        &top2pT_, &b_top2pT);
    //ch->SetBranchAddress("top2Phi",       &top2Phi_, &b_top2Phi);
    //ch->SetBranchAddress("TrigMuon",      &TrigMuon_, &b_TrigMuon);
    //ch->SetBranchAddress("TrigSingleMuon", &TrigSingleMuon_, &b_TrigSingleMuon);
}
