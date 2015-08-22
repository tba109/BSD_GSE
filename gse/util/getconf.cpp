//////////////////////////////////////////////////////
// Tyler Anderson Wed Mar 13 05:27:07 EDT 2013
// Get the current configuration and print it
//////////////////////////////////////////////////////
#include <stdio.h>
#include "HBSD.h"
#include "BSD_defs.h"
#include "error_resolve.h"

int main()
{
  tcf_data tcf_for_bsd;
  
  HBSD BSDinstr;

  printf("main: Opening BSD USB device\n");
  if( error_resolve(BSDinstr.open(0x04b4,0x1801)) )
    return -1;
    
  if( error_resolve(BSDinstr.BSD_getconf(tcf_for_bsd)) )
    return -1;
    
  // Print the data read for testing purposes
  printf("tcf_for_bsd.h = %x\n",tcf_for_bsd.h);  
  printf("\n\n");

  // printf("%x\n",tcf_for_bsd.length);
  // printf("%x\n",tcf_for_bsd.crc16);
  // printf("%x\n",tcf_for_bsd.type);
  // printf("%x\n",tcf_for_bsd.fmt);
  // printf("%x\n",tcf_for_bsd.reserved);
  // printf("%x\n",tcf_for_bsd.serial);

  // for( int i = 0; i < 144; i++ )
  //  printf("%d:) %hu\n",i,tcf_for_bsd.data[i]);
  


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PEDXH + PEDXL 1-16
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  char horz_peds[16][50] = {"PED1:  ","PED2:  ","PED3:  ","PED4:  ","PED5:  ","PED6:  ","PED7:  ","PED8:  ","PED9:  ","PED10: ","PED11: ","PED12: ","PED13: ","PED14: ","PED15: ","PED16: "};
  int pos = 0;
  
  printf("               PEDXH     PEDXL\n");
  
  for( int j = 0; j < 4; j++ )
    {pos++;
      for( int i = 0; i < 4; i++)
	{ printf("%s",horz_peds[j*4+i]);
	  printf("%10d",tcf_for_bsd.data[pos++]);
	  printf("%10d",tcf_for_bsd.data[pos++]);
	  printf("\n");
	}
      pos+=14;
    }
  
  printf("\n\n");




  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Quartets 1-4
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  char horz_quartets[4][50] = {"Quartet1:  ","Quartet2:  ","Quartet3:  ","Quartet4:  "};
  pos = -3;

  printf("               D1X_DL    D1X_WD    D2X_DL    D2X_WD   DONX_DL   DONX_WD      HV1X      HV2X      HV3X\n");

  for( int j = 0; j < 4; j++ )
    {pos+=8;
       printf("%s", horz_quartets[j]);
      for( int i = 0; i < 3; i++ )
	{pos+=4;
	  if( tcf_for_bsd.data[pos] == 0 )
	    {
	      printf("%10d",tcf_for_bsd.data[pos+2]);
	      printf("%10d",tcf_for_bsd.data[pos+3]);
	    }
	  else
	    {
	      if( tcf_for_bsd.data[pos+1] == 1 )
		printf("%10s","ON");
	      else
		printf("%10s","OFF");
	      
	      printf("%10s","Inf");
	    }
	}
      pos+=4;

      printf("%10d",tcf_for_bsd.data[pos++]);
      printf("%10d",tcf_for_bsd.data[pos++]);
      printf("%10d",tcf_for_bsd.data[pos++]);
      printf("\n");
      pos-=4;
    }
  
  printf("\n\n");
  
  

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Trigger Tubes 1-2
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  char horz_trig[2][50] = {"Trigger1:  ","Trigger2:  "};
  printf("              PEDTXH   PEDTXL   D1TX_DL   D1TX_WD   D2TX_DL   D2TX_WD      THRX      HVTX\n");
  pos = 93;
  for(int j = 0; j < 2; j++ )
    {
      printf("%s",horz_trig[j]);
      printf("%8d",tcf_for_bsd.data[pos]);
      printf("%8d",tcf_for_bsd.data[pos+1]);
      pos-=2;
      for( int i = 0; i < 2; i++ )
	{
	  pos+=4;
	  if( tcf_for_bsd.data[pos] == 0 )
	    {
	      printf("%10d",tcf_for_bsd.data[pos+2]);
	      printf("%10d",tcf_for_bsd.data[pos+3]);
	    }
	  else
	    {
	      if( tcf_for_bsd.data[pos+1] == 1 )
		printf("%10s","ON");
	      else
		printf("%10s","OFF");
	      
	      printf("%10s","Inf");
	    }
	}
      pos+=4;
      printf("%10d",tcf_for_bsd.data[pos++]);
      printf("%10d",tcf_for_bsd.data[pos++]);
      printf("\n");
    }
  printf("\n\n");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // FPGA specific parameters
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  printf("            TRIG_MODE      CONF_MODE       COINC_WD       RECOV_WD         DIG_DL     TRIG1_RATE     TRIG2_RATE      SELF_RATE        MT_RATE        T0_RATE\n");
  printf("FPGA: ");
  for( int i = 0; i < 10; i++ )
    {
      printf("%15d",tcf_for_bsd.data[pos++]);
    }
  printf("\n\n");


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Pulser 1 and 2
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  printf("            PULSEX_DL    PULSEX_WD   PULSEX_AMP    PULSEX_ON\n");
  printf("PULSE1: ");
  for( int i = 0; i < 4; i++ )
    {
      printf("%13d",tcf_for_bsd.data[pos++]);
    }
  printf("\n");

  printf("PULSE2: ");
  for( int i = 0; i < 4; i++ )
    {
      printf("%13d",tcf_for_bsd.data[pos++]);
    }
  
  printf("\n\n");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PON
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  pos = 135;
  printf("            QA      QB      QC      QD      T1      T2      FEEX    FEEY    FEEZ\n");
  printf("PON: ");
  for( int i = 0; i < 9; i++ )
    {
      printf("%8d",tcf_for_bsd.data[pos++]);
    }
  printf("\n\n");




  if( error_resolve(BSDinstr.close()) )
    return -1;
  
  return 0;
}
