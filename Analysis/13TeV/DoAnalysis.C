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
    //TString BabyDir = "Phys14_HT500MET200/";
    //TString BabyDir = "/net/cms26/cms26r0/jaehyeok/baby/Fatjet/13TeV/Phys14/";
    
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
   

    // Loop over SR and CR : make sure that these regions exist in "PassSelection.h"
    //        
    //TString Region[] = {"Baseline"}; 
    //TString Region[] = {"R1.1b.1M.1J.2L", "R1.1b.1M.2J.2L", "R1.1b.2M.1J.2L", "R1.1b.2M.2J.2L"}; 
    //TString Region[] = {"R1", "R2", "R3", "R4"}; 

    // Set regions for making the "yield book"
    //
    int idx=0;   
    TString Region[144];
    for(int i=1; i<=4; i++){
      for(int j=1; j<=3; j++){
	for(int k=1; k<=2; k++){
	  for(int l=0; l<=2; l++){
	    for(int m=1; m<=2; m++){
	      Region[idx] = Form("R%i.%ib.%iM.%iJ.%iL",i,j,k,l,m);
	      idx++;
	    }
	  }
	}
      }
    }
    //
    //    

    int NRegion = sizeof(Region)/sizeof(Region[0]);

    for(int iregion=0; iregion<NRegion; iregion++)
    {
        cout << endl;
        cout << "[MJ Analysis] Analyzing " << Region[iregion].Data() << endl;
        cout << endl;
        cout << "[MJ Analysis] Making directory for figures : Figures/" << Region[iregion].Data() << endl;
        gSystem->mkdir(Form("Output/YieldsBook/Figures/%s",Region[iregion].Data())); 

        if(!OnlyDraw) 
        {
            // ----------------------------------------
            //  Fill histrograms 
            // ----------------------------------------
	    MakeHists(ch_data,	    Region[iregion].Data()); 
            MakeHists(ch_ttbar_sl,  Region[iregion].Data()); 
            MakeHists(ch_ttbar_ll,  Region[iregion].Data()); 
            MakeHists(ch_wjets,     Region[iregion].Data()); 
            MakeHists(ch_dy,	    Region[iregion].Data()); 
            MakeHists(ch_t,         Region[iregion].Data()); 
            MakeHists(ch_f1500_100, Region[iregion].Data());  
            MakeHists(ch_f1200_800, Region[iregion].Data()); 

            // ----------------------------------------
            //  Make the final histogram file
            // ----------------------------------------
            cout << "[MJ Analysis] Merging result files" << endl;
            gSystem->Exec(Form("rm HistFiles/YieldsBook/Hist_%s.root", Region[iregion].Data()));
            gSystem->Exec(Form("hadd -f HistFiles/YieldsBook/Hist_%s.root HistFiles/YieldsBook/*_%s.root", Region[iregion].Data(), Region[iregion].Data()));
            gSystem->Exec(Form("mv HistFiles/YieldsBook/Hist_%s.root HistFiles/YieldsBook/Hist_%s.root.tmp", Region[iregion].Data(), Region[iregion].Data()));
            gSystem->Exec(Form("rm HistFiles/YieldsBook/*_%s.root", Region[iregion].Data()));
            gSystem->Exec(Form("mv HistFiles/YieldsBook/Hist_%s.root.tmp HistFiles/YieldsBook/Hist_%s.root", Region[iregion].Data(), Region[iregion].Data()));
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
        MakeTables(0,   Region[iregion].Data(), false);
        MakeTables(11,  Region[iregion].Data(), false);
        MakeTables(13,  Region[iregion].Data(), false);
        
        // ----------------------------------------
        //  Make cards for combine/LandS 
        // ---------------------------------------- 
        MakeCards(0,   Region[iregion].Data());
        MakeCards(11,  Region[iregion].Data());
        MakeCards(13,  Region[iregion].Data());

	// ----------------------------------------
        //  Make Yields Book 
        // ---------------------------------------- 
	

    } // Loop over regions

}
