void draw_distros()
{
  const Int_t Npmts = 16;
  Int_t new_nums[Npmts] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  // late low gain
  TCanvas * cv1 = new TCanvas("cv1");
  cv1->Divide(4,4);
  TH1F * h_late_lg[Npmts];
  char name[100];
  char draw[100];
  for( int i = 0; i < Npmts; i++ )
    {
      cv1->cd(new_nums[i]);
      sprintf(name,"h_late_lg_%d",new_nums[i]);
      h_late_lg[i] = new TH1F(name,"",16834,0,65536);
      sprintf(draw,"(fpmt_late_lg[%d])>>h_late_lg_%d",i,new_nums[i]);
      t->Draw(draw);
      h_late_lg[i]->GetXaxis()->SetRangeUser(h_late_lg[i]->GetMean()-3*h_late_lg[i]->GetRMS(),h_late_lg[i]->GetMean()+3*h_late_lg[i]->GetRMS());
      h_late_lg[i]->Draw();
  }
  cv1->Print("distros_late_lg.pdf");

  // late high gain
  TCanvas * cv2 = new TCanvas("cv2");
  cv2->Divide(4,4);
  TH1F * h_late_hg[Npmts];
  for( int i = 0; i < Npmts; i++ )
    {
      cv2->cd(new_nums[i]);
      sprintf(name,"h_late_hg_%d",new_nums[i]);
      h_late_hg[i] = new TH1F(name,"",16834,0,65536);
      sprintf(draw,"(fpmt_late_hg[%d])>>h_late_hg_%d",i,new_nums[i]);
      t->Draw(draw);
      h_late_hg[i]->GetXaxis()->SetRangeUser(h_late_hg[i]->GetMean()-3*h_late_hg[i]->GetRMS(),h_late_hg[i]->GetMean()+3*h_late_hg[i]->GetRMS());
      h_late_hg[i]->Draw();
    }
  cv2->Print("distros_late_hg.pdf");
  
  // early
  TCanvas * cv3 = new TCanvas("cv3");
  cv3->Divide(2,2);
  TH1F * h_early_lg[Npmts];
  TH1F * h_early_hg[Npmts];
  char name[100];
  char draw[100];
  for( int i = 0; i < 2; i++ )
    {
      cv3->cd(i+1);
      sprintf(name,"h_early_lg_T%d",i+1);
      h_early_lg[i] = new TH1F(name,"",16834,0,65536);
      sprintf(draw,"(fpmt_early_lg[%d])>>h_early_lg_T%d",i,i+1);
      t->Draw(draw);
      h_early_lg[i]->GetXaxis()->SetRangeUser(h_early_lg[i]->GetMean()-3*h_early_lg[i]->GetRMS(),h_early_lg[i]->GetMean()+3*h_early_lg[i]->GetRMS());
      h_early_lg[i]->Draw();
  }

  for( int i = 0; i < 2; i++ )
    {
      cv3->cd(i+3);
      sprintf(name,"h_early_hg_T%d",i+1);
      h_early_hg[i] = new TH1F(name,"",16834,0,65536);
      sprintf(draw,"(fpmt_early_hg[%d])>>h_early_hg_T%d",i,i+1);
      t->Draw(draw);
      h_early_hg[i]->GetXaxis()->SetRangeUser(h_early_hg[i]->GetMean()-3*h_early_hg[i]->GetRMS(),h_early_hg[i]->GetMean()+3*h_early_hg[i]->GetRMS());
      h_early_hg[i]->Draw();
    }
  cv3->Print("distros_early.pdf");

}
