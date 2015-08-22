#include <stdio.h>
#include <string.h>
#include "BSD_defs.h"
#include "cbuffer.h"

//////////////////////////////////////////////////////////////////////////
// These are used for coding/decoding
//////////////////////////////////////////////////////////////////////////
const char Ncmds = 7;
char cmds[Ncmds][12] = {"NOP","GET","SET","EVENT","SHUTDOWN","RESET","RESET_FIFO"};
const unsigned char cmdval[Ncmds] = {0,1,2,3,4,5,6};

const int Nparams = 144;
char params[Nparams][50] = {"FPGA",
			    "PED1H","PED2H","PED3H","PED4H",
			    "THR1","THR2",
			    "D11_DL","D21_DL",
			    "D12_DL","D22_DL",
			    "D13_DL","D23_DL",
			    "D14_DL","D24_DL",
			    "D11_WD","D21_WD",
			    "D12_WD","D22_WD",
			    "D13_WD","D23_WD",
			    "D14_WD","D24_WD",
			    "DON1_DL","DON2_DL","DON3_DL","DON4_DL",
			    "DON1_WD","DON2_WD","DON3_WD","DON4_WD",
			    "TRIG_MODE",
			    "CONF_MODE",
			    "COINC_WD",
			    "RECOV_WD",
			    "DIG_DL",
			    "PULSE1_DL","PULSE2_DL",
			    "PULSE1_WD","PULSE2_WD",
			    "PULSE1_AMP","PULSE2_AMP",
			    "PULSE1_ON","PULSE2_ON",
			    "HV11","HV21","HV31",
			    "HV12","HV22","HV32",
			    "HV13","HV23","HV33",
			    "HV14","HV24","HV34",
			    "HVT1","HVT2",
			    "PEDT1H","PEDT2H",
			    "D1T1_DL","D2T1_DL",
			    "D1T2_DL","D2T2_DL",
			    "D1T1_WD","D2T1_WD",
			    "D1T2_WD","D2T2_WD",
			    "D11_CM","D21_CM",
			    "D12_CM","D22_CM",
			    "D13_CM","D23_CM",
			    "D14_CM","D24_CM",
			    "D1T1_CM","D2T1_CM",
			    "D1T2_CM","D2T2_CM",
			    "DON1_CM","DON2_CM","DON3_CM","DON4_CM",
			    "D11_ON","D21_ON",
			    "D12_ON","D22_ON",
			    "D13_ON","D23_ON",
			    "D14_ON","D24_ON",
			    "D1T1_ON","D2T1_ON",
			    "D1T2_ON","D2T2_ON",
			    "DON1_ON","DON2_ON","DON3_ON","DON4_ON",
			    "TRIG1_RATE","TRIG2_RATE",
			    "TRIG_SELF_RATE",
			    "TRIG_MT_RATE",
			    "TRIG_T0_RATE",
			    "PED1L","PED2L","PED3L","PED4L",
			    "PED5H","PED5L","PED6H","PED6L",
			    "PED7H","PED7L","PED8H","PED8L",
			    "PED9H","PED9L","PED10H","PED10L",
			    "PED11H","PED11L","PED12H","PED12L",
			    "PED13H","PED13L","PED14H","PED14L",
			    "PED15H","PED15L","PED16H","PED16L",
			    "PEDT1L","PEDT2L",
			    "PON_QA","PON_QB","PON_QC","PON_QD",
			    "PON_T1","PON_T2",
			    "PON_FEEX","PON_FEEY","PON_FEEZ"};
	       
const unsigned char paramval[Nparams] = {0,1,2,3,4,5,6,7,8,10,
					 11,13,14,16,17,19,20,
					 22,23,25,26,28,29,
					 31,32,33,34,35,36,37,38,39,40,
					 41,42,43,44,45,46,47,48,49,50,
					 51,52,53,54,55,56,57,58,59,60,
					 61,62,63,64,65,66,67,68,69,
					 71,72,74,75,77,78,
					 80,81,83,84,86,87,89,
					 90,92,93,95,96,98,99,
					 100,101,102,103,105,106,108,109,
					 111,112,114,115,117,118,
					 120,121,122,123,124,125,126,127,128,129,130,131,132,
					 133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167};

int command_resolve(char * text, unsigned int &cmd, unsigned int &param, unsigned short &value)
{
  cbuffer cmdbuf; // buffer containing raw commands
  char curcmd[15];
  char curparam[20];
  char curvalue[10];
  int found = 0;
  
  memset(curcmd,'\0',15);
  memset(curparam,'\0',20);
  memset(curvalue,'\0',10);
  
  cmdbuf.add(text);
    
  cmdbuf.posbegin();

  strcpy(curcmd,cmdbuf.gettosent(" ")); // Grab the command part
  curcmd[strlen(curcmd)-1] = '\0'; // Remove the " "

  strcpy(curparam,cmdbuf.gettosent(" ")); // Grab the command part
  curparam[strlen(curparam)-1] = '\0'; // Remove the " "

  strcpy(curvalue,cmdbuf.gettosent(" ")); // Grab the command part
  curvalue[strlen(curvalue)-1] = '\0'; // Remove the " "

  // Resolve the cmd part
  found = 0;
  for(int i = 0; i < Ncmds; i++)
    {
      if( !strcmp(curcmd,cmds[i]) )
	{
	  cmd = cmdval[i];
	  found = 1;
	  break;
	}
    }
  if( !found )
    {
      printf("CommandResolve: Bad cmd \n");
      return -1;
    }
  
  // Resolve the param part
  found = 0;
  for(int i = 0; i < Nparams; i++)
    {
      if( !strcmp(curparam,params[i]) )
	{
	  param = paramval[i];
	  found = 1;
	  break;
	}
    }
  if( !found )
    {
      printf("CommandResolve: Bad param \n");
      return -1;
    }

  value = (unsigned short)atoi(curvalue);
  
  return 0;
}
