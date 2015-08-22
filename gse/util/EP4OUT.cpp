/*
 * Tyler Anderson Mon Nov 12 13:26:01 EST 2012
 * Write to EP4
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
  
  char buf[2000];
  buf[0] = 0x8f; // Default
  buf[1] = 0xc7; // Default
  buf[2] = 0xab; // Default
  buf[3] = 0xba; // Default
  buf[4] = 0x06;
  buf[5] = 0x00;
  buf[6] = 0x00;
  buf[7] = 0x00;
  int nbytes = 8;

  if( argc > 1 )
    {
      nbytes = 0;
      for( int i = 1; i < argc; i++ )
	{
	  buf[i-1] = strtol(argv[i], NULL, 16);
	  nbytes++;
	}
    }

  if( dev.BSDUsb_initialization(0x04b4,0x1801) )
    { 
      cout << "Initialization unsuccessful :-(" << endl;
      return -1;
    }
  
  if( dev.BSDUsb_bulk_write_EP4OUT(buf,nbytes) )
    {
      cout << "Write unsuccessful :-( " << endl;
      return -1;
    }

  cout << "EP4OUT Write: " ;
  for( int i = 0; i < nbytes; i++ )
    printf("0x%02X ", 0x000000FF & buf[i]);
  cout << endl;

  return 0;
}
