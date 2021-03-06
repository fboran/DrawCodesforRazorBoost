float Fit(TString MRR2, TString mW, TString EBEE){
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();
  TString dir = "/uscms_data/d3/chuh/added/";
  //TFile* file1 = TFile::Open(dir+"Multijet.root");
  TFile* file1 = TFile::Open(dir+"QCD.root");
  TFile* file2 = TFile::Open(dir+"SinglePhoton.root");
  TFile* file3 = TFile::Open(dir+"GJet.root");
  
  TString histname_SR = "ChargedIso_"+MRR2+"_SR_"+mW+"_"+EBEE;
  TString histname_CR = "ChargedIso_"+MRR2+"_CR_"+mW+"_"+EBEE;
  
  TH1F* data = (TH1F*)file2->Get(histname_SR);
  data->Rebin(5); // # of bin : 100, -> 20
  TH1F* prompt_template = (TH1F*)file3->Get(histname_SR);
  prompt_template->Rebin(5);
  TH1F* fake_template = (TH1F*)file1->Get(histname_CR);
  fake_template->Rebin(5);

  TObjArray *mc = new TObjArray(3);
  mc->Add(prompt_template);
  mc->Add(fake_template);

  TFractionFitter* fit = new TFractionFitter(data,mc);
  fit->Constrain(0,0.,1.);
  fit->Constrain(1,0.,1.);

	TCanvas* c1 = new TCanvas("c1","",700,700);
  c1->SetLogy();

  Double_t prompt_value=0., prompt_error=0., fake_value=0., fake_error=0.;
  int status = fit->Fit();
  if(status == 0){
    TH1F* result = (TH1F*)fit->GetPlot();
		fit->GetResult(0, prompt_value, prompt_error);
		fit->GetResult(1, fake_value, fake_error);
    cout << "prmpt : " << prompt_value << " fake_value : " << fake_value << endl;
    data->Draw("EP");
    result->SetLineColor(2);
    result->Draw("same");
  	leg = new TLegend(0.28,0.70,0.9,0.9);
    leg->SetTextSize(0.03);
		leg->SetHeader("Purity : "+std::to_string(prompt_value)+" in "+MRR2+", "+mW+", "+EBEE);
		leg->AddEntry(data, "Data", "LPE");
		leg->AddEntry(result, "Total Fit", "L");
		leg->Draw();
  }
	TString Dir = "/uscms_data/d3/chuh/DrawCodesforRazorBoost/ZBackgroundEstimation/plot/";
  c1->SaveAs(Dir+"ChargedIso_"+MRR2+"_"+mW+"_"+EBEE+".png");
  return prompt_value;
}

void ZpurityFit(){

  int nbn_MR = 7, nbn_R2 = 7;
  float bn_MR[] = {0.,600.,800.,1000.,1200.,1600.,2000.,4000.};
  float bn_R2[] = {0.,0.04,0.08,0.12,0.16,0.24,0.5,1.};
  TH2D* hPurity_MR_R2_0mW_EB = new TH2D("Purity_MR_R2_0mW_EB",";MR [GeV] ;R^{2}", nbn_MR, bn_MR, nbn_R2, bn_R2);
  TH2D* hPurity_MR_R2_1mW_EB = new TH2D("Purity_MR_R2_1mW_EB",";MR [GeV] ;R^{2}", nbn_MR, bn_MR, nbn_R2, bn_R2);
  TH2D* hPurity_MR_R2_0mW_EE = new TH2D("Purity_MR_R2_0mW_EE",";MR [GeV] ;R^{2}", nbn_MR, bn_MR, nbn_R2, bn_R2);
  TH2D* hPurity_MR_R2_1mW_EE = new TH2D("Purity_MR_R2_1mW_EE",";MR [GeV] ;R^{2}", nbn_MR, bn_MR, nbn_R2, bn_R2);
  TH1D* hPurity_MR_0mW_EB = new TH1D("Purity_MR_0mW_EB",";MR [GeV]", nbn_MR, bn_MR);
  TH1D* hPurity_R2_0mW_EB = new TH1D("Purity_R2_0mW_EB",";R^{2}", nbn_R2, bn_R2);
  TH1D* hPurity_MR_1mW_EB = new TH1D("Purity_MR_1mW_EB",";MR [GeV]", nbn_MR, bn_MR);
  TH1D* hPurity_R2_1mW_EB = new TH1D("Purity_R2_1mW_EB",";R^{2}", nbn_R2, bn_R2);
  TH1D* hPurity_MR_0mW_EE = new TH1D("Purity_MR_0mW_EE",";MR [GeV]", nbn_MR, bn_MR);
  TH1D* hPurity_R2_0mW_EE = new TH1D("Purity_R2_0mW_EE",";R^{2}", nbn_R2, bn_R2);
  TH1D* hPurity_MR_1mW_EE = new TH1D("Purity_MR_1mW_EE",";MR [GeV]", nbn_MR, bn_MR);
  TH1D* hPurity_R2_1mW_EE = new TH1D("Purity_R2_1mW_EE",";R^{2}", nbn_R2, bn_R2);
  float purity[5][5][2][2];
  float MR_purity[5][2][2];
  float R2_purity[5][2][2];
  //e.g ChargedIso_MR_1100_R2_010_CR_0mW_EB
  purity[0][0][0][0] = Fit("MR_900_R2_010","0mW","EB");
  purity[1][0][0][0] = Fit("MR_1100_R2_010","0mW","EB");
  purity[2][0][0][0] = Fit("MR_1400_R2_010","0mW","EB");
  purity[3][0][0][0] = Fit("MR_1800_R2_010","0mW","EB");
  purity[4][0][0][0] = Fit("MR_3000_R2_010","0mW","EB");
  purity[0][1][0][0] = Fit("MR_900_R2_014","0mW","EB");
  purity[1][1][0][0] = Fit("MR_1100_R2_014","0mW","EB");
  purity[2][1][0][0] = Fit("MR_1400_R2_014","0mW","EB");
  purity[3][1][0][0] = Fit("MR_1800_R2_014","0mW","EB");
  purity[4][1][0][0] = Fit("MR_3000_R2_014","0mW","EB");
  purity[0][2][0][0] = Fit("MR_900_R2_020","0mW","EB");
  purity[1][2][0][0] = Fit("MR_1100_R2_020","0mW","EB");
  purity[2][2][0][0] = Fit("MR_1400_R2_020","0mW","EB");
  purity[3][2][0][0] = Fit("MR_1800_R2_020","0mW","EB");
  purity[4][2][0][0] = Fit("MR_3000_R2_020","0mW","EB");
  purity[0][3][0][0] = Fit("MR_900_R2_037","0mW","EB");
  purity[1][3][0][0] = Fit("MR_1100_R2_037","0mW","EB");
  purity[2][3][0][0] = Fit("MR_1400_R2_037","0mW","EB");
  purity[3][3][0][0] = Fit("MR_1800_R2_037","0mW","EB");
  purity[4][3][0][0] = Fit("MR_3000_R2_037","0mW","EB");
  purity[0][4][0][0] = Fit("MR_900_R2_075","0mW","EB");
  purity[1][4][0][0] = Fit("MR_1100_R2_075","0mW","EB");
  purity[2][4][0][0] = Fit("MR_1400_R2_075","0mW","EB");
  purity[3][4][0][0] = Fit("MR_1800_R2_075","0mW","EB");
  purity[4][4][0][0] = Fit("MR_3000_R2_075","0mW","EB");
  purity[0][0][1][0] = Fit("MR_900_R2_010","1mW","EB");
  purity[1][0][1][0] = Fit("MR_1100_R2_010","1mW","EB");
  purity[2][0][1][0] = Fit("MR_1400_R2_010","1mW","EB");
  purity[3][0][1][0] = Fit("MR_1800_R2_010","1mW","EB");
  purity[4][0][1][0] = Fit("MR_3000_R2_010","1mW","EB");
  purity[0][1][1][0] = Fit("MR_900_R2_014","1mW","EB");
  purity[1][1][1][0] = Fit("MR_1100_R2_014","1mW","EB");
  purity[2][1][1][0] = Fit("MR_1400_R2_014","1mW","EB");
  purity[3][1][1][0] = Fit("MR_1800_R2_014","1mW","EB");
  purity[4][1][1][0] = Fit("MR_3000_R2_014","1mW","EB");
  purity[0][2][1][0] = Fit("MR_900_R2_020","1mW","EB");
  purity[1][2][1][0] = Fit("MR_1100_R2_020","1mW","EB");
  purity[2][2][1][0] = Fit("MR_1400_R2_020","1mW","EB");
  purity[3][2][1][0] = Fit("MR_1800_R2_020","1mW","EB");
  purity[4][2][1][0] = Fit("MR_3000_R2_020","1mW","EB");
  purity[0][3][1][0] = Fit("MR_900_R2_037","1mW","EB");
  purity[1][3][1][0] = Fit("MR_1100_R2_037","1mW","EB");
  purity[2][3][1][0] = Fit("MR_1400_R2_037","1mW","EB");
  purity[3][3][1][0] = Fit("MR_1800_R2_037","1mW","EB");
  purity[4][3][1][0] = Fit("MR_3000_R2_037","1mW","EB");
  purity[0][4][1][0] = Fit("MR_900_R2_075","1mW","EB");
  purity[1][4][1][0] = Fit("MR_1100_R2_075","1mW","EB");
  purity[2][4][1][0] = Fit("MR_1400_R2_075","1mW","EB");
  purity[3][4][1][0] = Fit("MR_1800_R2_075","1mW","EB");
  purity[4][4][1][0] = Fit("MR_3000_R2_075","1mW","EB");
  purity[0][0][0][1] = Fit("MR_900_R2_010","0mW","EE");
  purity[1][0][0][1] = Fit("MR_1100_R2_010","0mW","EE");
  purity[2][0][0][1] = Fit("MR_1400_R2_010","0mW","EE");
  purity[3][0][0][1] = Fit("MR_1800_R2_010","0mW","EE");
  purity[4][0][0][1] = Fit("MR_3000_R2_010","0mW","EE");
  purity[0][1][0][1] = Fit("MR_900_R2_014","0mW","EE");
  purity[1][1][0][1] = Fit("MR_1100_R2_014","0mW","EE");
  purity[2][1][0][1] = Fit("MR_1400_R2_014","0mW","EE");
  purity[3][1][0][1] = Fit("MR_1800_R2_014","0mW","EE");
  purity[4][1][0][1] = Fit("MR_3000_R2_014","0mW","EE");
  purity[0][2][0][1] = Fit("MR_900_R2_020","0mW","EE");
  purity[1][2][0][1] = Fit("MR_1100_R2_020","0mW","EE");
  purity[2][2][0][1] = Fit("MR_1400_R2_020","0mW","EE");
  purity[3][2][0][1] = Fit("MR_1800_R2_020","0mW","EE");
  purity[4][2][0][1] = Fit("MR_3000_R2_020","0mW","EE");
  purity[0][3][0][1] = Fit("MR_900_R2_037","0mW","EE");
  purity[1][3][0][1] = Fit("MR_1100_R2_037","0mW","EE");
  purity[2][3][0][1] = Fit("MR_1400_R2_037","0mW","EE");
  purity[3][3][0][1] = Fit("MR_1800_R2_037","0mW","EE");
  purity[4][3][0][1] = Fit("MR_3000_R2_037","0mW","EE");
  purity[0][4][0][1] = Fit("MR_900_R2_075","0mW","EE");
  purity[1][4][0][1] = Fit("MR_1100_R2_075","0mW","EE");
  purity[2][4][0][1] = Fit("MR_1400_R2_075","0mW","EE");
  purity[3][4][0][1] = Fit("MR_1800_R2_075","0mW","EE");
  purity[4][4][0][1] = Fit("MR_3000_R2_075","0mW","EE");
  purity[0][0][1][1] = Fit("MR_900_R2_010","1mW","EE");
  purity[1][0][1][1] = Fit("MR_1100_R2_010","1mW","EE");
  purity[2][0][1][1] = Fit("MR_1400_R2_010","1mW","EE");
  purity[3][0][1][1] = Fit("MR_1800_R2_010","1mW","EE");
  purity[4][0][1][1] = Fit("MR_3000_R2_010","1mW","EE");
  purity[0][1][1][1] = Fit("MR_900_R2_014","1mW","EE");
  purity[1][1][1][1] = Fit("MR_1100_R2_014","1mW","EE");
  purity[2][1][1][1] = Fit("MR_1400_R2_014","1mW","EE");
  purity[3][1][1][1] = Fit("MR_1800_R2_014","1mW","EE");
  purity[4][1][1][1] = Fit("MR_3000_R2_014","1mW","EE");
  purity[0][2][1][1] = Fit("MR_900_R2_020","1mW","EE");
  purity[1][2][1][1] = Fit("MR_1100_R2_020","1mW","EE");
  purity[2][2][1][1] = Fit("MR_1400_R2_020","1mW","EE");
  purity[3][2][1][1] = Fit("MR_1800_R2_020","1mW","EE");
  purity[4][2][1][1] = Fit("MR_3000_R2_020","1mW","EE");
  purity[0][3][1][1] = Fit("MR_900_R2_037","1mW","EE");
  purity[1][3][1][1] = Fit("MR_1100_R2_037","1mW","EE");
  purity[2][3][1][1] = Fit("MR_1400_R2_037","1mW","EE");
  purity[3][3][1][1] = Fit("MR_1800_R2_037","1mW","EE");
  purity[4][3][1][1] = Fit("MR_3000_R2_037","1mW","EE");
  purity[0][4][1][1] = Fit("MR_900_R2_075","1mW","EE");
  purity[1][4][1][1] = Fit("MR_1100_R2_075","1mW","EE");
  purity[2][4][1][1] = Fit("MR_1400_R2_075","1mW","EE");
  purity[3][4][1][1] = Fit("MR_1800_R2_075","1mW","EE");
  purity[4][4][1][1] = Fit("MR_3000_R2_075","1mW","EE");

  MR_purity[0][0][0] = Fit("MR_900","0mW","EB");
  MR_purity[1][0][0] = Fit("MR_1100","0mW","EB");
  MR_purity[2][0][0] = Fit("MR_1400","0mW","EB");
  MR_purity[3][0][0] = Fit("MR_1800","0mW","EB");
  MR_purity[4][0][0] = Fit("MR_3000","0mW","EB");
  R2_purity[0][0][0] = Fit("R2_010","0mW","EB");
  R2_purity[1][0][0] = Fit("R2_014","0mW","EB");
  R2_purity[2][0][0] = Fit("R2_020","0mW","EB");
  R2_purity[3][0][0] = Fit("R2_037","0mW","EB");
  R2_purity[4][0][0] = Fit("R2_075","0mW","EB");
  MR_purity[0][1][0] = Fit("MR_900","1mW","EB");
  MR_purity[1][1][0] = Fit("MR_1100","1mW","EB");
  MR_purity[2][1][0] = Fit("MR_1400","1mW","EB");
  MR_purity[3][1][0] = Fit("MR_1800","1mW","EB");
  MR_purity[4][1][0] = Fit("MR_3000","1mW","EB");
  R2_purity[0][1][0] = Fit("R2_010","1mW","EB");
  R2_purity[1][1][0] = Fit("R2_014","1mW","EB");
  R2_purity[2][1][0] = Fit("R2_020","1mW","EB");
  R2_purity[3][1][0] = Fit("R2_037","1mW","EB");
  R2_purity[4][1][0] = Fit("R2_075","1mW","EB");
  MR_purity[0][0][1] = Fit("MR_900","0mW","EE");
  MR_purity[1][0][1] = Fit("MR_1100","0mW","EE");
  MR_purity[2][0][1] = Fit("MR_1400","0mW","EE");
  MR_purity[3][0][1] = Fit("MR_1800","0mW","EE");
  MR_purity[4][0][1] = Fit("MR_3000","0mW","EE");
  R2_purity[0][0][1] = Fit("R2_010","0mW","EE");
  R2_purity[1][0][1] = Fit("R2_014","0mW","EE");
  R2_purity[2][0][1] = Fit("R2_020","0mW","EE");
  R2_purity[3][0][1] = Fit("R2_037","0mW","EE");
  R2_purity[4][0][1] = Fit("R2_075","0mW","EE");
  MR_purity[0][1][1] = Fit("MR_900","1mW","EE");
  MR_purity[1][1][1] = Fit("MR_1100","1mW","EE");
  MR_purity[2][1][1] = Fit("MR_1400","1mW","EE");
  MR_purity[3][1][1] = Fit("MR_1800","1mW","EE");
  MR_purity[4][1][1] = Fit("MR_3000","1mW","EE");
  R2_purity[0][1][1] = Fit("R2_010","1mW","EE");
  R2_purity[1][1][1] = Fit("R2_014","1mW","EE");
  R2_purity[2][1][1] = Fit("R2_020","1mW","EE");
  R2_purity[3][1][1] = Fit("R2_037","1mW","EE");
  R2_purity[4][1][1] = Fit("R2_075","1mW","EE");


  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      hPurity_MR_R2_0mW_EB->SetBinContent(i+3,j+3,purity[i][j][0][0]);
      hPurity_MR_R2_1mW_EB->SetBinContent(i+3,j+3,purity[i][j][1][0]);
      hPurity_MR_R2_0mW_EE->SetBinContent(i+3,j+3,purity[i][j][0][1]);
      hPurity_MR_R2_1mW_EE->SetBinContent(i+3,j+3,purity[i][j][1][1]);
    }
    hPurity_MR_0mW_EB->SetBinContent(i+3,MR_purity[i][0][0]);
    hPurity_R2_0mW_EB->SetBinContent(i+3,R2_purity[i][0][0]);
    hPurity_MR_1mW_EB->SetBinContent(i+3,MR_purity[i][1][0]);
    hPurity_R2_1mW_EB->SetBinContent(i+3,R2_purity[i][1][0]);
    hPurity_MR_0mW_EE->SetBinContent(i+3,MR_purity[i][0][1]);
    hPurity_R2_0mW_EE->SetBinContent(i+3,R2_purity[i][0][1]);
    hPurity_MR_1mW_EE->SetBinContent(i+3,MR_purity[i][1][1]);
    hPurity_R2_1mW_EE->SetBinContent(i+3,R2_purity[i][1][1]);
  }

  TCanvas* c1 = new TCanvas("c1","",700,700);
  hPurity_MR_R2_0mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_MR_R2_0mW_EB.png");
  hPurity_MR_R2_1mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_MR_R2_1mW_EB.png");
  hPurity_MR_R2_0mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_MR_R2_0mW_EE.png");
  hPurity_MR_R2_1mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_MR_R2_1mW_EE.png");
  hPurity_MR_0mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_MR_0mW_EB.png");
  hPurity_R2_0mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_R2_0mW_EB.png");
  hPurity_MR_1mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_MR_1mW_EB.png");
  hPurity_R2_1mW_EB->Draw("colz");
  c1->SaveAs("plot/Purity_R2_1mW_EB.png");
  hPurity_MR_0mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_MR_0mW_EE.png");
  hPurity_R2_0mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_R2_0mW_EE.png");
  hPurity_MR_1mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_MR_1mW_EE.png");
  hPurity_R2_1mW_EE->Draw("colz");
  c1->SaveAs("plot/Purity_R2_1mW_EE.png");

}
