#include <iostream>
#include <fstream>
#include <iomanip> // for setw()

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TSystem.h"
#include "TFile.h"
#include "TDatime.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"
#include "TLatex.h"
#include "TMath.h"

ofstream fout;

// Add one more since index starts at 0
const int Nregions = 5;
const int Nbcuts = 4;
const int Njetcuts = 3;
const int Nmetcuts = 3;
const int Nlepcuts = 3;
//const int Nmetjetcuts = (Njetcuts-1)*(Nmetcuts-1)+1;
const int Nmetjetcuts = 5;

// Indices: [Region][b-cut][lep-cut][4 MET and Njet bins]
// Indices are 1 too large so that they match region/cut number (i.e. arrays start at 1)
double total_Bkg[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
double total_f1500_100[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
double total_f1200_800[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];

void PrintRegionBlock(int bCut, int nLep){

  double Bkg_RegTot[Nregions] = {0};
  double Sig_RegTot[Nregions] = {0};
  for(int i=1; i<Nregions; i++){
    for(int l=1; l<Nmetjetcuts; l++){
      Bkg_RegTot[i] += total_Bkg[i][bCut][nLep][l];
      Sig_RegTot[i] += total_f1500_100[i][bCut][nLep][l];
    }
    /*    //DEBUG
    if(i==2){
      cout<<"Bcut: "<<bCut<<endl;
      cout<<"Nlep: "<<nLep<<endl;
      cout<<"BKG Reg Tot: "<<Bkg_RegTot[i]<<endl;    
      cout<<"SIG Reg Tot: "<<Sig_RegTot[i]<<endl;
      }*/
  }

  double sigContam[Nregions][Nmetjetcuts];
  for(int i=1; i<Nregions; i++){
    for(int l=1; l<Nmetjetcuts; l++){
      sigContam[i][l] = total_f1500_100[i][bCut][nLep][l]/(total_Bkg[i][bCut][nLep][l] + total_f1500_100[i][bCut][nLep][l]);
      sigContam[i][l] *= 100.0;
    }
  }
  double tot_SigContam[Nregions];
  for(int i=1; i<Nregions; i++){
    tot_SigContam[i] = Sig_RegTot[i]/(Sig_RegTot[i]+Bkg_RegTot[i]);
    tot_SigContam[i] *= 100.0;
  }
   
  fout<<"{\\color[rgb]{1,0,0}Region 3:} & "
      << Form("\\bf{%.1f}",Bkg_RegTot[3]) << " & "
      << Form("\\bf{%.1f}",Sig_RegTot[3]) << " & "
      << Form("\\bf{%.1f}",tot_SigContam[3]) << " && "
      <<"{\\color[rgb]{1,0,0}Region 4:} & "
      << Form("\\bf{%.1f}",Bkg_RegTot[4]) << " & "
      << Form("\\bf{%.1f}",Sig_RegTot[4]) << " & "
	      << Form("\\bf{%.1f}",tot_SigContam[4])
      <<" \\\\"<<"\n\\hline"<<endl;                
  
  for(int l=1; l<=4; l++){
   
    char* cutName = "";
    if(l==1) cutName = "Low MET, Med Njet";
    if(l==2) cutName = "Low MET, High Njet";
    if(l==3) cutName = "High MET, Med Njet";
    if(l==4) cutName = "High MET, High Njet";

    fout << cutName << " & "
	 << Form("%.1f",total_Bkg[3][bCut][nLep][l]) << " & "
	 << Form("%.1f",total_f1500_100[3][bCut][nLep][l]) << " & "
	 << Form("%.1f",sigContam[3][l])
	 << " && & "
	 << Form("%.1f",total_Bkg[4][bCut][nLep][l]) << " & "
	 << Form("%.1f",total_f1500_100[4][bCut][nLep][l]) << " & "
	 << Form("%.1f",sigContam[4][l])
 	 <<" \\\\"<<endl;
  }
  fout<<"\\hline \\hline"<<endl;
  fout<<"&&&&&&&&  \\\\"<<endl;
  fout<<"\\hline \\hline"<<endl;

  fout<<"{\\color[rgb]{1,0,0}Region 1:} & "
      << Form("\\bf{%.1f}",Bkg_RegTot[1]) << " & "
      << Form("\\bf{%.1f}",Sig_RegTot[1]) << " & "
      << Form("\\bf{%.1f}",tot_SigContam[1]) << " && "
      <<"{\\color[rgb]{1,0,0}Region 2:} & "
      << Form("\\bf{%.1f}",Bkg_RegTot[2]) << " & "
      << Form("\\bf{%.1f}",Sig_RegTot[2]) << " & "    
      << Form("\\bf{%.1f}",tot_SigContam[2])
      <<" \\\\"<<"\n\\hline"<<endl;                
 
  for(int l=1; l<=4; l++){
    
    char* cutName = "";
    if(l==1) cutName = "Low MET, Med Njet";
    if(l==2) cutName = "Low MET, High Njet";
    if(l==3) cutName = "High MET, Med Njet";
    if(l==4) cutName = "High MET, High Njet";    

    fout << cutName << " & "
	 << Form("%.1f",total_Bkg[1][bCut][nLep][l]) << " & "
	 << Form("%.1f",total_f1500_100[1][bCut][nLep][l]) << " & "
	 << Form("%.1f",sigContam[1][l])
	 << " && & "
	 << Form("%.1f",total_Bkg[2][bCut][nLep][l]) << " & "
	 << Form("%.1f",total_f1500_100[2][bCut][nLep][l]) << " & "
	 << Form("%.1f",sigContam[2][l])
	 <<" \\\\"<<endl;
  }
  fout<<"\\hline \\hline"<<endl;
  fout<<"\\end{tabular}"<<endl;
}

void MakeYieldsBook(TString Region[], int Nselections, char* babyName =""){

  TFile* HistFile[Nselections];
 
  // Indices: [Region][b-cut][lep-cut][4 MET and Njet bins]
  // Indices are 1 too large so that they match region/cut number (i.e. arrays start at 1)
  //  double total_Bkg[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
  //  double total_f1500_100[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
  //  double total_f1200_800[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];

  double total_Bkg_err[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
  double total_f1500_100_err[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];
  double total_f1200_800_err[Nregions][Nbcuts][Nlepcuts][Nmetjetcuts];

  for(int iFile=0; iFile<Nselections; iFile++){

    HistFile[iFile] = TFile::Open(Form("HistFiles/YieldsBook/%s/Hist_%s.root", babyName, Region[iFile].Data()));
    
    TH1F *h1_DATA, *h1_T, *h1_TT_sl, *h1_TT_ll, *h1_WJets, *h1_DY, *h1_MC;
    TH1F *h1_f1500_100, *h1_f1200_800;

    h1_DATA      = (TH1F*)HistFile[iFile]->Get("h1_DATA_yields_6fatjet");
    h1_T         = (TH1F*)HistFile[iFile]->Get("h1_T_yields_6fatjet");
    h1_TT_sl     = (TH1F*)HistFile[iFile]->Get("h1_TT_sl_yields_6fatjet");
    h1_TT_ll     = (TH1F*)HistFile[iFile]->Get("h1_TT_ll_yields_6fatjet");
    h1_WJets     = (TH1F*)HistFile[iFile]->Get("h1_WJets_yields_6fatjet");
    h1_DY        = (TH1F*)HistFile[iFile]->Get("h1_DY_yields_6fatjet");
    h1_f1500_100 = (TH1F*)HistFile[iFile]->Get("h1_T1tttt_f1500_100_yields_6fatjet");
    h1_f1200_800 = (TH1F*)HistFile[iFile]->Get("h1_T1tttt_f1200_800_yields_6fatjet");

    h1_MC = (TH1F*)h1_TT_sl->Clone("h1_MC");
    h1_MC->Add(h1_TT_ll);
    h1_MC->Add(h1_WJets);
    h1_MC->Add(h1_T);
    h1_MC->Add(h1_DY);

    // Char to int
    int a = Region[iFile][1]-'0';
    int b = Region[iFile][3]-'0';
    int c = Region[iFile][12]-'0';
    
    int d = Region[iFile][6]-'0';
    int e = Region[iFile][9]-'0';

    int f = -1;
    
    //A pretty bad way to organize the MET and Njet bins
    if(d==1 && e==1) f = 1;
    if(d==1 && e==2) f = 2;
    if(d==2 && e==1) f = 3;
    if(d==2 && e==2) f = 4;

    if(f == -1) cout<<"THERE IS A PROBLEM WITH CHAR TO INT. f = -1"<<endl;

    total_Bkg[a][b][c][f] = h1_MC->IntegralAndError(1,10000,total_Bkg_err[a][b][c][f]);
    total_f1500_100[a][b][c][f] = h1_f1500_100->IntegralAndError(1,10000,total_f1500_100_err[a][b][c][f]);
    total_f1200_800[a][b][c][f] = h1_f1200_800->IntegralAndError(1,10000,total_f1200_800_err[a][b][c][f]);
  }

  // DEBUG
  //
  /*  for(int i=1; i<Nregions; i++){
    for(int j=1; j<Nbcuts; j++){
      for(int k=1; k<Nlepcuts; k++){
	for(int l=1; l<Nmetjetcuts; l++){
	  cout<<Form("R%i.%ib.%iL",i,j,k);
	  if(i==2){
	    cout<<"\n Bkg: "<<total_Bkg[i][j][k][l]<<endl;
	    //cout<<"Bkg Err: "<<total_Bkg_err[i][j][k][l]<<endl;
	    cout<<"f1500_100: "<<total_f1500_100[i][j][k][l]<<endl;
	    //cout<<"f1500_100 Err: "<<total_f1500_100_err[i][j][k][l]<<endl;  
	    cout<<"f1200_800: "<<total_f1200_800[i][j][k][l]<<endl;  
	    //	  cout<<"f1200_800 Err: "<<total_f1200_800_err[i][j][k][l]<<endl; 
	  }
	}
      }
    } 
    }*/
  //
  //

  //Now we want to print this out in LaTeX
  //Use with LaTeXiT, text format
  for(int j=1;j<Nlepcuts;j++){ 
    fout.open(Form("Output/YieldsBook/Tables/%s/TotalYields_%s_%iL.tex", babyName, babyName,j));
    for(int i=1;i<Nbcuts; i++){
      fout<<"\\centering"<<endl;
      fout<<"\\begin{tabular}{| c | c c | c || c || c | c c | c |}"<<endl;
      fout<<Form("\\multicolumn{9}{c}{\\bf{%i Lepton}} \\\\",j)<<endl;
      fout<<"\\hline \\hline"<<endl;
      if(i!=Nbcuts-1) fout<<Form("\\bf{Nb=%i}",i)<<"  & BKG & SIG & \\% SIG &&& BKG & SIG & \\% SIG \\\\"<<endl;
      if(i==Nbcuts-1) fout<<Form("\\bf{Nb=%i+}",i)<<"  & BKG & SIG & \\% SIG &&& BKG & SIG & \\% SIG \\\\"<<endl;
      fout<<"\\hline"<<endl;  
      PrintRegionBlock(i,j);
      if(i!=Nbcuts-1) fout<<"\\newline \\newline"<<endl;
    }   
     fout.close();
  }
}
