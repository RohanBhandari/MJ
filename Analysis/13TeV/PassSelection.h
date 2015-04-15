// 
bool PassNLep(unsigned int Nlep)
{
    if( (RA4MusPt_->size()+RA4ElsPt_->size())==Nlep 
        && RA4MusVetoPt_->size()==0 
        && RA4ElsVetoPt_->size()==0 
      ) return true;
    else return false;
       
}

// 
bool PassBaselineSelection(float HT, float MET, int Ncsvm, int Nskinny)
{
  //  return  (HT>750 && MET>250 && Ncsvm>1 && Nskinny>5); 
  return  (HT>750 && MET>250 && Nskinny>3); //For yields book. No Nbtag cut
}
 
// 
bool PassSelection(TString Region, float HT, float MET, int Nb, int Njet, float mT, float MJ)
{
    bool passed=false;

    if(Region=="Baseline" 
        && HT   > -1
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;

    //The following selections are for the synchronization exercise. Note that they may be redundant to the "SR"-labeled regions
    //
   
    if(Region=="R1" 
        && HT   > -1
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   <=150 
        && MJ   <=600 
       )  passed = true;

    if(Region=="R2" 
        && HT   > -1
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   <=150 
        && MJ   > 600 
       )  passed = true;

    if(Region=="R3" 
        && HT   > -1
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   <=600 
       )  passed = true;

    if(Region=="R4" 
        && HT   > -1
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 600 
       )  passed = true; 

    int Nlep = -1;
    
    if((RA4MusVetoPt_->size() + RA4ElsVetoPt_->size())==0)
      Nlep = RA4MusPt_->size()+RA4ElsPt_->size();

    int MJMax = -1;
    int MJMin = -1;
    int mTMax = -1;
    int mTMin = -1;
    int NbMax = -1;
    int NbMin = -1;
    int METMax = -1;
    int METMin = -1;
    int NjMax = -1;
    int NjMin = -1;
    int NlepMax = -1;
    int NlepMin = -1;
    
    //Regions
    for(int i=1; i<=4; i++){ 
      if(i==1){ //R1
	MJMax = 600;	MJMin = -1;
	mTMax = 150;	mTMin = -1;
      }
      if(i==2){ //R2
	MJMax = 99999;	MJMin = 600;
	mTMax = 150;	mTMin = -1;
      }
      if(i==3){ //R3
	MJMax = 600;	MJMin = -1;
	mTMax = 99999;	mTMin = 150;
      }
      if(i==4){ //R4
	MJMax = 99999;	MJMin = 600;
	mTMax = 99999;	mTMin = 150;
      }
      // Nb
      for(int j=1; j<=3; j++){
	NbMax = j+1;	NbMin = j;
	if(j==3){
	  NbMax = 99999;  NbMin = j;
	}
	
	// MET
	for(int k=1; k<=2; k++){
	  if(k==1){
	    METMax = 400;    METMin = 250;
	  }
	  if(k==2){
	    METMax = 99999;  METMin = 400;
	  }
	  
	  // Nj
	  for(int l=0; l<=2; l++){
	    if(l==0){
	      NjMax = 5;	    NjMin = 4;
	    }
	    if(l==1){
	      NjMax = 7;	    NjMin = 6;
	    }
	    if(l==2){
	      NjMax = 99999;  NjMin = 8;
	    }
	    
	    // Lep
	    for(int m=1; m<=2; m++){	  
	      NlepMax = m+1;  NlepMin = m;
            
	      if(Region==Form("R%i.%ib.%iM.%iJ.%iL",i,j,k,l,m)
		 && HT   >  -1
		 && MJ   >  MJMin   &&  MJ   <= MJMax  
		 && mT   >  mTMin   &&  mT   <= mTMax
		 && Nb   >= NbMin   &&  Nb   <  NbMax 
		 && MET  >  METMin  &&  MET  <  METMax
		 && Njet >= NjMin   &&  Njet <= NjMax 	 
		 && Nlep >= NlepMin &&  Nlep <  NlepMax
		 )  passed = true;      
	    }
	  }
	}
      }	 
    }
    //
    //

    
    // Standard Signal Region selection
    if(Region=="SR0" 
        && HT   > -1 
        && MET  > 400
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 600 
    )  passed = true;
    
    // SR with reduced MJ cut
    if(Region=="SR0p1" 
        && HT   > -1 
        && MET  > 400
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 500 
    )  passed = true;
    
    // SR with reduced MJ cut
    if(Region=="SR0p2" 
        && HT   > -1 
        && MET  > 400
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 400 
    )  passed = true;
    
    // mT cut is reversed
    if(Region=="SR1" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   < 150 
        && MJ   > -1 
    )  passed = true;
    
    // only mT cut
    if(Region=="SR2" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // only MJ400 cut
    if(Region=="SR2p1" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1 
        && MJ   > 400 
    )  passed = true;
    
    // only reduced mT cut
    if(Region=="SR2p2" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 100 
        && MJ   > -1 
    )  passed = true;
    
    // only increased mT cut
    if(Region=="SR2p3" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 200 
        && MJ   > -1 
    )  passed = true;
    
    // only Njet 8+ cut
    if(Region=="SR3" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 7 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
    // only Njet 9+ cut
    if(Region=="SR4" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 8 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
    // low MET region
    if(Region=="SR5" 
        && HT   > -1 
        && MET  > -1 && MET < 350 
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
    // medium MET region
    if(Region=="SR6" 
        && HT   > -1 
        && MET  > 350 && MET < 450 
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
    // high MET region
    if(Region=="SR7" 
        && HT   > -1 
        && MET  > 450 
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
    // Njet 7+ and mT cut
    if(Region=="SR8" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 6 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // Njet 8+ and mT cut
    if(Region=="SR9" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 7 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // Njet 9+ and mT cut
    if(Region=="SR10" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 8 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // mT and MJ cut
    if(Region=="SR11" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 600 
    )  passed = true;
    
    // mT and reduced MJ cut
    if(Region=="SR12" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 500 
    )  passed = true;
    
    // mT and reduced MJ cut
    if(Region=="SR13" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 400 
    )  passed = true;
    
    // mT, MJ, and Njet 6+ cut
    if(Region=="SR14" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > 5 
        && mT   > 150 
        && MJ   > 600 
    )  passed = true;
    
    // Redundant signal region (SR0)
    if(Region=="SR15" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 600 
    )  passed = true;

    // MET, Njet 4+, and mT
    if(Region=="SR16" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > -1 
        && Njet > 3 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 5+, and mT
    if(Region=="SR17" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > -1 
        && Njet > 4 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;

    // MET, Njet 4+, mT, and Nb 2+
    if(Region=="SR18" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > 1 
        && Njet > 3 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 5+, mT, and Nb 2+
    if(Region=="SR19" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > 1 
        && Njet > 4 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 6+, mT, and Nb 2+
    if(Region=="SR20" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > 1 
        && Njet > 5 
        && mT   > 150 
        && MJ   > 400 
    )  passed = true;

    // MET, Njet 5+, mT, Nb 2+, and MJ    
    if(Region=="SR20p1" 
        && HT   > -1 
        && MET  > 400 
        && Nb   > 1 
        && Njet > 5 
        && mT   > 150 
        && MJ   > 500 
    )  passed = true;
    
    // MET, Njet 6+, and mT 
    if(Region=="SR21" 
        && HT   > -1 
        && MET  > 350 
        && Nb   > -1 
        && Njet > 5 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 7+, mT
    if(Region=="SR22" 
        && HT   > -1 
        && MET  > 350 
        && Nb   > -1 
        && Njet > 6 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 8+, mT
    if(Region=="SR23" 
        && HT   > -1 
        && MET  > 350 
        && Nb   > -1 
        && Njet > 7 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // MET, Njet 9+, mT
    if(Region=="SR24" 
        && HT   > -1 
        && MET  > 350 
        && Nb   > -1 
        && Njet > 8 
        && mT   > 150 
        && MJ   > -1 
    )  passed = true;
    
    // mT and low MJ region
    if(Region=="SR25" 
        && HT   > -1 
        && MET  > -1 
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 300 
    )  passed = true;

    // mT and low MJ region
    if(Region=="SR26" 
        && HT   > 500 
        && MET  > 200
        && Nb   > -1 
        && Njet > 3 
        && mT   > -1 
        && MJ   > -1 
    )  passed = true;
    
   return passed;
}
