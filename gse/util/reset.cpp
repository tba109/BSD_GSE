/*
 * Tyler Anderson Tue Mar 12 11:56:33 EDT 2013
 * Standalone routine for reseting the BSD
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BSDUsb.h"
#include "BSD_err.h"

using namespace std;

int main(int argc, char * argv[])
{
  BSDUsb dev;
  
  //////////////////////////////////////////////////////////////////////
  // Download the USB firmware
  //////////////////////////////////////////////////////////////////////
  if( dev.BSDUsb_initialization() )
    { 
      cout << "Initialization unsuccessful :-(" << endl;
      return -1;
    }
  
  if( dev.BSDUsb_fx2lp_reset("./sfc/BSD_firmware.ihx") )
  {
      cout << "Error downloading firmware :-(" << endl;
      return -1;
    }

  cout << "Reset and download successful! :-)" << endl;
  printf("shutdown: %d \n",dev.BSDUsb_shutdown());
  //////////////////////////////////////////////////////////////////////
  // Read once from EP6IN to get the reset response
  //////////////////////////////////////////////////////////////////////
  unsigned char buf[2000];
  for( int i = 0; i < 2000; i++ )
    buf[i] = 0;
  int nbytes = 8; // Default
  
  // TBA Fri Apr 18 14:47:51 EDT 2014
  // Added for PID = 0x1800 to 0x1801 change
  usleep(2000*1000);
  if( dev.BSDUsb_reinitialization(0x04b4,0x1801) )
    {
      cout << "Initialization unsuccessful :-(" << endl;
      return -1;
    }

  if( argc > 1 )
    nbytes = atoi(argv[1]);
  
  if( dev.BSDUsb_bulk_read_EP6IN(buf,nbytes) )
    {
      cout << "Error reading from device :-( " << endl;
      return -1;
    }
  else
    {
      cout << "EP6IN Read:   ";
      for( int i = 0; i < nbytes; i++ )
	printf("0x%02X ",buf[i]);
      cout << endl;
    }

  return 0;
}
