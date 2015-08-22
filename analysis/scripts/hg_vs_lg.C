void hg_vs_lg()
{
  const Int_t Npmts = 16;
  Int_t new_nums[Npmts] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  
  // late
  TCanvas * cv1 = new TCanvas("cv1");
  cv1->Divide(4,4);
  // TH2F * h_late[Npmts];
  char name[100];
  char draw[100];
  for( int i = 0; i < Npmts; i++ )
    {
      cv1->cd(new_nums[i]);
      sprintf(name,"h_late_%d",new_nums[i]);
      // h_late[i] = new TH2F(name,"",16834,0,65536,16834,0,65536);
      sprintf(draw,"fpmt_late_hg[%d]:fpmt_late_lg[%d]>>h_late_%d",i,i,new_nums[i]);
      t->Draw(draw,"","COLZ");
    }	
  cv1->Print("hg_vs_lg_late.pdf");
  
  // early
  TCanvas * cv3 = new TCanvas("cv3");
  cv3->Divide(2,1);
  // TH2F * h_early[Npmts];
  char name[100];
  char draw[100];
  for( int i = 0; i < 2; i++ )
    {
      cv3->cd(i+1);
      sprintf(name,"h_early_T%d",i+1);
      // h_early[i] = new TH2F(name,"",16834,0,65536,16834,0,65536);
      sprintf(draw,"fpmt_early_hg[%d]:fpmt_early_lg[%d]>>h_early_T%d",i,i,i+1);
      t->Draw(draw,"","COLZ");
    }
  cv3->Print("hg_vs_lg_early.pdf");

}
