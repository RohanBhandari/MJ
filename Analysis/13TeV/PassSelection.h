// 
bool manuel2 = false;
//bool manuel2 = true;

bool PassNLep(unsigned int Nlep)
{
  if(!manuel2){
    if( (RA4MusPt_->size()+RA4ElsPt_->size())==Nlep 
        && RA4MusVetoPt_->size()==0 
        && RA4ElsVetoPt_->size()==0 
	) return true;
    else return false;
  }
  else{
    if(nmus_+nels_==static_cast<int>(Nlep)) 
      return true;
    else return false;	
  }
}

// 
bool PassBaselineSelection(float HT, float MET, int Ncsvm, int Nskinny, int nGoodIsoTrks=0)
{
  //  return  (HT>750 && MET>250 && Ncsvm>1 && Nskinny>5); 

  // Veto events with 1 or more isolated tracks (since now cleaned). Though right now we are interested in the 1 lep + iso trk case so we veto on 2+.
  //  return  (HT>750 && MET>250 && Nskinny>5 && nGoodIsoTrks<2); //For yields book. No Nbtag cut
  return  (HT>500 && MET>200 && Nskinny>5); //For yields book. No Nbtag cut
}
 
//
bool PassSelection(TString Region, float HT, float MET, int Nb, int Njet, float mT, float MJ, int nGoodIsoTrks)
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
    int Nlep = -5;
    
    // Nlep = 1/2 for 1/2 leptons + 0 veto + 0 isotrk. Nlep = 3/4 for 1 lepton + 1 veto lepton/iso trk

    if(!manuel2){
      if((RA4MusPt_->size()+RA4ElsPt_->size())<=2 && (RA4MusVetoPt_->size() + RA4ElsVetoPt_->size())==0) 
      //    if((RA4MusPt_->size()+RA4ElsPt_->size())<=2 && (RA4MusVetoPt_->size() + RA4ElsVetoPt_->size())==0 && (nGoodIsoTrks)==0) 
      Nlep = RA4MusPt_->size()+RA4ElsPt_->size();
    //    else if((RA4MusPt_->size()+RA4ElsPt_->size())==1 && (RA4MusVetoPt_->size() + RA4ElsVetoPt_->size())==1 && (nGoodIsoTrks)==0)
    //      Nlep = 3;
    //    else if((RA4MusPt_->size()+RA4ElsPt_->size())==1 && (RA4MusVetoPt_->size() + RA4ElsVetoPt_->size())==0 && (nGoodIsoTrks)==1)
    //      Nlep = 4;
    } else {
      if((nmus_+nels_)<=2 && ((nvmus_-nmus_) + (nvels_-nels_))==0) 
	//    if((nmus_+nels_)<=2 && ((nvmus_-nmus_) + (nvels_-nels_))==0 && (nGoodIsoTrks)==0) 
	Nlep = nmus_+nels_;
      //    else if((nmus_+nels_)==1 && ((nvmus_-nmus_) + (nvels_-nels_))==1 && (nGoodIsoTrks)==0)
      //      Nlep = 3;
      //    else if((nmus_+nels_)==1 && ((nvmus_-nmus_) + (nvels_-nels_))==0 && (nGoodIsoTrks)==1)
      //      Nlep = 4;
    }


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
	    METMax = 400;    METMin = 200;
	  }
	  if(k==2){
	    METMax = 99999;  METMin = 400;
	  }
	  
	  // Nj
	  for(int l=0; l<=2; l++){
	    if(l==0){
	      NjMax = 5;	    NjMin = 5;
	    }
	    if(l==1){
	      NjMax = 7;	    NjMin = 5;
	    }
	    if(l==2){
	      NjMax = 99999;  NjMin = 8;
	    }
	    
	    // Lep
	    for(int m=1; m<=4; m++){	  
	      if(m==1){ // 1 lepton
		NlepMax = 2;  NlepMin = 1;
	      }
	      if(m==2){ // 2 lepton
		NlepMax = 3;  NlepMin = 2;
	      }
	      if(m==3){ // 1 lepton + 1 veto
		NlepMax = 4;  NlepMin = 3;
	      }
	      if(m==4){ //1 lepton + 1 iso trk
		NlepMax = 5;  NlepMin = 4;
	      }
            
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
    
    if(Region=="R1" 
        && HT   > -1 
        && MET  > -1
        && Nb   > -1 
        && Njet > -1 
        && mT   < 150 
        && MJ   < 600 
    )  passed = true;

    if(Region=="R2" 
        && HT   > -1 
        && MET  > -1
        && Nb   > -1 
        && Njet > -1 
        && mT   < 150 
        && MJ   > 600 
    )  passed = true;

    if(Region=="R3" 
        && HT   > -1 
        && MET  > -1
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   < 600 
    )  passed = true;

    if(Region=="R4" 
        && HT   > -1 
        && MET  > -1
        && Nb   > -1 
        && Njet > -1 
        && mT   > 150 
        && MJ   > 600
    )  passed = true;

    if(Region=="test" 
        && HT   > -1 
        && MET  > -1
        && Nb   > -1 
        && Njet > -1 
        && mT   > -1
        && MJ   > -1
    )  passed = true;
        
   return passed;
}
