void draw_index()
{
  const Int_t Npmts = 16;
  // Int_t new_nums[Npmts] = {1,2,3,4,13,14,5,6,7,8,15,9,10,11,12,16};
  Int_t new_nums[Npmts] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  // late high gain
  TCanvas * cv1 = new TCanvas("cv1");
  cv1->Divide(4,4);
  char draw[100];
  for( int i = 0; i < Npmts; i++ )
    {
      cv1->cd(new_nums[i]);
      sprintf(draw,"fpmt_late_hg[%d]:findex",i);
      t->Draw(draw);
    }
  cv1->Print("index_late_hg.pdf");

  // late low gain
  TCanvas * cv2 = new TCanvas("cv2");
  cv2->Divide(4,4);
  char draw[100];
  for( int i = 0; i < Npmts; i++ )
    {
      cv2->cd(new_nums[i]);
      sprintf(draw,"fpmt_late_lg[%d]:findex",i);
      t->Draw(draw);
    }
  cv2->Print("index_late_lg.pdf");

  // early
  TCanvas * cv3 = new TCanvas("cv3");
  cv3->Divide(2,2);
  char draw[100];
  for( int i = 0; i < 2; i++ )
    {
      cv3->cd(i+1);
      sprintf(draw,"fpmt_early_lg[%d]:findex",i);
      t->Draw(draw);
    }
  
  for( int i = 0; i < 2; i++ )
    {
      cv3->cd(i+3);
      sprintf(draw,"fpmt_early_hg[%d]:findex",i);
      t->Draw(draw);
    }
  
  cv3->Print("index_early_lg.pdf");

}
