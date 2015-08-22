void plot_all()
{
  gROOT->ProcessLine(".x ../scripts/draw_distros.C");
  gROOT->ProcessLine(".x ../scripts/draw_index.C");
  gROOT->ProcessLine(".x ../scripts/hg_vs_lg.C");
  gROOT->ProcessLine(".q");
}
