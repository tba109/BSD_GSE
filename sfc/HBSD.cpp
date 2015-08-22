/*
 * Tyler Anderson Wed Jan 23 17:40:59 EST 2013
 * HBSD
 */

// These are necessary system headers
#include <stdio.h>
#include <string.h>

// These are necessary program headers
#include "HBSD.h"
#include "BSD_defs.h"
#include "BSD_err.h"

HBSD::HBSD()
{
  ;
}

int HBSD::open(int vendor, int product)
{
  return dev.BSDUsb_initialization(vendor, product);
}

int HBSD::close()
{
  return dev.BSDUsb_shutdown();
}

int HBSD::reopen(int vendor, int product)
{
  return dev.BSDUsb_reinitialization(vendor, product);
}

int HBSD::BSD_execute(unsigned int cmd, unsigned int param, unsigned short *value)
{
  int retval = 0;
  unsigned short lval[0];

  //printf("HBSD::BSD_execute: Entering BSDCmdProc::BSDCmdProc_ConvertCommand\n");
  if( (retval = cmdproc.BSDCmd_ProcessCommand(cmd,param,value,&dev)) )
    {
      // Make one attempt to resync if there was a slip
      // Then, if you still can't fix it, write the error message
      if( retval == -USB_SYNC_ERR ) 
	{
	  lval[0] = 0;
	  
	  retval = cmdproc.BSDCmd_ProcessCommand(RESET_FIFO,FPGA,lval,&dev);
	  if( retval == 0 ) // okay, looks like it's fixed, so return everything to normal
	    {
	      retval = cmdproc.BSDCmd_ProcessCommand(cmd,param,value,&dev);
	    }
	}

      // printf("HBSD::BSD_execute: Error processing command\n");
      return retval;
    }
  
  return 0;
}

int HBSD::BSD_getconf(tcf_data &tcf_for_bsd)
{
  int retval = 0;

  if( (retval = cmdproc.BSDCmd_GetConf(&(tcf_for_bsd.h),(&dev))) )
    {
      // printf("HBSD::BSD_getconf: error getting configuration for BSD: %d \n",retval);
      return retval;
    }
  
  // TODO need to fill out the rest of the tcf_data struct
  
  return 0;
}

int HBSD::BSD_readout(int *count_BSDdata, unsigned char *BSD_buf)
{
  int retval = 0;
  unsigned short lval[0];
  
  if( (retval = evtproc.BSDEvt_ProcessEvent(count_BSDdata,BSD_buf,&(dev))) )
    {
      // If sync error, throw out event and reset USB interface
      if( retval == -USB_SYNC_ERR ) 
	{
	  lval[0] = 0;
	  retval = cmdproc.BSDCmd_ProcessCommand(RESET_FIFO,FPGA,lval,&dev);
	}
      // printf("HBSD::BSD_readout: Error reading in BSD bytes\n");    
      return retval;
    }
  
  // printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
  // for( int i = 0; i < *count_BSDdata; i++ )
  //  printf("%hu\n",BSD_buf[i]);
  // printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
  
  // printf("%s %d\n","BSDEvent::ProcessEvent: retval = ",retval);
  // printf("%s %d\n","BSDEvent::ProcessEvent: *count_BSDdata = ",*count_BSDdata);
       
  return 0;
}

int HBSD::BSD_readout_software_generated(int *count_BSDdata, unsigned char *BSD_buf)
{
  int retval = 0;
  unsigned short lval[0];
  char rawcmd[8] = {0x8F,0xC7,0xAB,0xBA,EVENT,FPGA,0,0};
  
  if( (retval = dev.BSDUsb_bulk_write_EP2OUT(rawcmd,8) ) )
    return retval;

  if( (retval = evtproc.BSDEvt_ProcessEvent(count_BSDdata,BSD_buf,&(dev))) )
    {
      // If sync error, throw out event and reset USB interface
      if( retval == -USB_SYNC_ERR ) 
	{
	  lval[0] = 0;
	  retval = cmdproc.BSDCmd_ProcessCommand(RESET_FIFO,FPGA,lval,&dev);
	}
      // printf("HBSD::BSD_readout: Error reading in BSD bytes\n");    
      return retval;
    }
  
  // printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
  // for( int i = 0; i < *count_BSDdata; i++ )
  //  printf("%hu\n",BSD_buf[i]);
  // printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
  
  // printf("%s %d\n","BSDEvent::ProcessEvent: retval = ",retval);
  // printf("%s %d\n","BSDEvent::ProcessEvent: *count_BSDdata = ",*count_BSDdata);
       
  return 0;
}

int HBSD::BSD_fx2lp_reset(const char * path, unsigned int vendor, unsigned int product)
{
  return dev.BSDUsb_fx2lp_reset(path,vendor,product);
}

int HBSD::BSD_initialization(unsigned int vendor, unsigned int product)
{
  return 0;
}

HBSD::~HBSD()
{
  ; 
}
