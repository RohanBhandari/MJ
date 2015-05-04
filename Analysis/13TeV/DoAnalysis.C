//
// main 
//
void DoAnalysis(bool OnlyDraw=false) 
{
    // Style
  //    gROOT->ProcessLine(".L rootlogon.C");
    // Load macros 
    gROOT->LoadMacro("MakeHists.C+");
    gROOT->LoadMacro("Make1DPlots.C+");
    gROOT->LoadMacro("Make2DPlots.C+");
    gROOT->LoadMacro("MakeTables.C+");
    gROOT->LoadMacro("MakeCards.C+");
    gROOT->LoadMacro("MakeYieldsBook.C+");

    // ----------------------------------------
    //  Define chains  
    // ----------------------------------------
    TChain *ch_data         = new TChain("tree", "DATA");
    TChain *ch_ttbar_sl     = new TChain("tree", "TT_sl");
    TChain *ch_ttbar_ll     = new TChain("tree", "TT_ll");
    TChain *ch_wjets        = new TChain("tree", "WJets");
    TChain *ch_dy           = new TChain("tree", "DY");
    TChain *ch_t            = new TChain("tree", "T");
    TChain *ch_f1500_100    = new TChain("tree", "T1tttt_f1500_100");
    TChain *ch_f1200_800    = new TChain("tree", "T1tttt_f1200_800");
    
    TString BabyDir = "Phys14/";

    //    TString babyName = "Test";

    //MINI ISOLATION

    TString babyName = "HT750MET250_MI";
    //TString babyName = "HT750MET200_MI";

    //TString babyName = "HT500MET250_MI";
    //TString babyName = "HT500MET200_MI";

    //TString babyName = "HT750MET250Nsj4_MI";
    //TString babyName = "HT750MET200Nsj4_MI";

    //    TString babyName = "HT500MET200Nsj4_MI";

    //MINI ISOLATION + Iso Trk Veto

    //TString babyName = "HT750MET250-MI+ITV";
    //TString babyName = "HT750MET200-MI+ITV";

    //TString babyName = "HT500MET250-MI+ITV";
    //TString babyName = "HT500MET200-MI+ITV";

    //TString babyName = "HT750MET250Nsj5-MI+ITV";       ///Change nJetStart///
    //    TString babyName = "HT750MET200Nsj5-MI+ITV";

    //TString babyName = "HT500MET200Nsj5-MI+ITV";    

   
    // Loop over SR and CR : make sure that these regions exist in "PassSelection.h"
    //        
    //TString Region[] = {"Baseline"}; 
    //TString Region[] = {"R3.1b.1M.1J.1L", "R3.1b.1M.2J.1L","R3.1b.2M.1J.1L", "R3.1b.2M.2J.1L","R3.2b.1M.1J.1L", "R3.2b.1M.2J.1L","R3.2b.2M.1J.1L", "R3.2b.2M.2J.1L"}; 
    //TString Region[] = {"R3.1b.1M.1J.1L", "R3.1b.1M.2J.1L","R3.1b.2M.1J.1L", "R3.1b.2M.2J.1L"}; 
    //    TString Region[] = {"R3.1b.1M.1J.1L", "R3.1b.1M.1J.2L","R3.1b.1M.1J.3L", "R3.1b.1M.1J.4L"}; 
    //    TString Region[] = {"R1", "R2", "R3", "R4"};     
    //    TString Region[] = {"R4.1b.1M.1J.1L"}; 

    //int NRegion = sizeof(Region)/sizeof(Region[0]);
    
    
    // Set regions for making the "yield book"
    //
    int nReg = 4;
    int nBcut = 3;
    int nMetcut = 2;
    int nJetcut = 2;  int nJetStart = 1;
    int nLepcut = 4;

    int NRegion = (nReg*nBcut*nMetcut*(nJetcut-(nJetStart-1))*nLepcut);
    TString Region[NRegion];

    //    int NRegion = sizeof(Region)/sizeof(Region[0]);
    //TString Region[96];  //int l=1  &  nLep = 2
    //TString Region[144]; //int l=0  &  nLep = 2
    //TString Region[192]; //int l=1  &  nLep = 4
    //TString Region[288]; //int l=0  &  nLep = 4    

    int idx=0;   
    for(int i=1; i<=nReg; i++){
      for(int j=1; j<=nBcut; j++){
	for(int k=1; k<=nMetcut; k++){
	  for(int l=nJetStart; l<=nJetcut; l++){
	    for(int m=1; m<=nLepcut; m++){
	      Region[idx] = Form("R%i.%ib.%iM.%iJ.%iL",i,j,k,l,m);
	      idx++;
	    }
	  }
	}
      }
    }
    //           
    

    // Data
    //ch_data->Add(BabyDir+"baby_MuHad_*.root");                            
    
    // TT 
    ch_ttbar_sl->Add(BabyDir+"baby_TTJets*.root");
    ch_ttbar_ll->Add(BabyDir+"baby_TTJets*.root");
    // WJets 
    ch_wjets->Add(BabyDir+"baby_WJetsToLNu*.root");
    // DY 
    ch_dy->Add(BabyDir+"baby_DYJetsToLL*.root");
    // Single top 
    ch_t->Add(BabyDir+"baby_*channel*_f*.root");

    // Signal
    ch_f1500_100->Add(BabyDir+"baby_*1500*.root");
    ch_f1200_800->Add(BabyDir+"baby_*1200*.root");
    
    
    // ----------------------------------------
    //  Get number of entries 
    // ----------------------------------------
    cout << "data               : " << ch_data->GetEntries()        << endl;
    cout << "ttbarl             : " << ch_ttbar_sl->GetEntries()    << endl;
    cout << "ttbarll            : " << ch_ttbar_ll->GetEntries()    << endl;
    cout << "wjets              : " << ch_wjets->GetEntries()       << endl;
    cout << "dy                 : " << ch_dy->GetEntries()          << endl;
    cout << "Single top         : " << ch_t->GetEntries()           << endl;
    cout << "T1tttt(1500,100)   : " << ch_f1500_100->GetEntries()    << endl;
    cout << "T1tttt(1200,8000)  : " << ch_f1200_800->GetEntries()  << endl;
   
    for(int iregion=0; iregion<NRegion; iregion++)
    {
        cout << endl;
        cout << "[MJ Analysis] Analyzing " << Region[iregion].Data() << endl;
        cout << endl;
        cout << "[MJ Analysis] Making directory for figures : Figures/" << Region[iregion].Data() << endl;
        gSystem->mkdir(Form("~/cms26/MJ_Out/Output/YieldsBook/Figures/%s",Region[iregion].Data())); 

        if(!OnlyDraw) 
        {
            // ----------------------------------------
            //  Fill histrograms 
            // ----------------------------------------
	  MakeHists(ch_data,	    Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_ttbar_sl,  Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_ttbar_ll,  Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_wjets,     Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_dy,	    Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_t,         Region[iregion].Data(), babyName.Data()); 
	  MakeHists(ch_f1500_100, Region[iregion].Data(), babyName.Data());  
	  MakeHists(ch_f1200_800, Region[iregion].Data(), babyName.Data()); 
	    
            // ----------------------------------------
            //  Make the final histogram file
            // ----------------------------------------
	    cout << "[MJ Analysis] Merging result files" << endl;
            gSystem->Exec(Form("rm ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root", babyName.Data(), Region[iregion].Data()));
            gSystem->Exec(Form("hadd -f ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/*_%s.root", babyName.Data(), Region[iregion].Data(), babyName.Data(), Region[iregion].Data()));
            gSystem->Exec(Form("mv ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root.tmp", babyName.Data(), Region[iregion].Data(), babyName.Data(), Region[iregion].Data()));
            gSystem->Exec(Form("rm ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/*_%s.root", babyName.Data(), Region[iregion].Data()));
            gSystem->Exec(Form("mv ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root.tmp ~/cms26/MJ_Out/HistFiles/YieldsBook/%s/Hist_%s.root", babyName.Data(), Region[iregion].Data(), babyName.Data(), Region[iregion].Data())); 
        }

        // ----------------------------------------
        //  Draw histograms 
        // ---------------------------------------- 
	/*        Make1DPlots("dRlep",        Region[iregion].Data());
        Make1DPlots("dPhiMET",      Region[iregion]);
        Make1DPlots("dRbmin",       Region[iregion]);
        Make1DPlots("dPhiMETlep",   Region[iregion]);
        Make1DPlots("muspT",        Region[iregion]);
        Make1DPlots("musPhi",       Region[iregion]);
        Make1DPlots("musEta",       Region[iregion]);
        Make1DPlots("elspT",        Region[iregion]);
        Make1DPlots("elsPhi",       Region[iregion]);
        Make1DPlots("elsEta",       Region[iregion]);
        Make1DPlots("mT",           Region[iregion]);
        Make1DPlots("mj",           Region[iregion]);
        Make1DPlots("MJ",           Region[iregion]);
        Make1DPlots("MJ_ISR",       Region[iregion]);
        Make1DPlots("HT",           Region[iregion]);
        Make1DPlots("Nfatjet",      Region[iregion]);
        Make1DPlots("Nskinnyjet",   Region[iregion]);
        Make1DPlots("Ncsvm",        Region[iregion]);
        Make1DPlots("MET",          Region[iregion]);
        Make1DPlots("METPhi",       Region[iregion]);
        Make1DPlots("WpT",          Region[iregion]);
        Make1DPlots("FatjetPt1",    Region[iregion]);
        Make1DPlots("FatjetPt2",    Region[iregion]);
        Make1DPlots("FatjetPt3",    Region[iregion]);
        Make1DPlots("FatjetPt4",    Region[iregion]);
        Make1DPlots("FatjetPhi1",   Region[iregion]);
        Make1DPlots("FatjetPhi2",   Region[iregion]);
        Make1DPlots("FatjetPhi3",   Region[iregion]);
        Make1DPlots("FatjetPhi4",   Region[iregion]);
        Make1DPlots("FatjetEta1",   Region[iregion]);
        Make1DPlots("FatjetEta2",   Region[iregion]);
        Make1DPlots("FatjetEta3",   Region[iregion]);
        Make1DPlots("FatjetEta4",   Region[iregion]);
        Make1DPlots("mj1",          Region[iregion]);
        Make1DPlots("mj2",          Region[iregion]);
        Make1DPlots("mj3",          Region[iregion]);
        Make1DPlots("mj4",          Region[iregion]);
        Make1DPlots("mj1OverMJ",    Region[iregion]);
        Make1DPlots("mj2OverMJ",    Region[iregion]);
        Make1DPlots("mj3OverMJ",    Region[iregion]);
        Make1DPlots("mj4OverMJ",    Region[iregion]);
        Make1DPlots("N1",           Region[iregion]);
        Make1DPlots("N2",           Region[iregion]);
        Make1DPlots("N3",           Region[iregion]);
        Make1DPlots("N4",           Region[iregion]);
        Make1DPlots("mjOverPt1",    Region[iregion]);
        Make1DPlots("mjOverPt2",    Region[iregion]);
        Make1DPlots("mjOverPt3",    Region[iregion]);
        Make1DPlots("mjOverPt4",    Region[iregion]);
        Make1DPlots("mj3overmj2",   Region[iregion]);
        Make1DPlots("mj2overmj1",   Region[iregion]); */

        // ----------------------------------------
        //  Make table of yields 
        // ---------------------------------------- 
	MakeTables(0,   Region[iregion].Data(), babyName.Data(), false);
        MakeTables(11,  Region[iregion].Data(), babyName.Data(), false);
        MakeTables(13,  Region[iregion].Data(), babyName.Data(), false);
        
        // ----------------------------------------
        //  Make cards for combine/LandS 
        // ---------------------------------------- 
        /*MakeCards(0,   Region[iregion].Data());
        MakeCards(11,  Region[iregion].Data());
        MakeCards(13,  Region[iregion].Data()); */

    } // Loop over regions

    // ----------------------------------------
    //  Make Yields Book 
    // ---------------------------------------- 
    MakeYieldsBook(Region, NRegion, babyName.Data());
}
