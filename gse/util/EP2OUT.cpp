/*
 * Tyler Anderson Mon Nov 12 13:26:01 EST 2012
 * Write to EP2
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
  buf[0] = 0x8F; // Default
  buf[1] = 0xC7; // Default
  buf[2] = 0xAB; // Default
  buf[3] = 0xBA; // Default
  buf[4] = 0x00; // Default
  buf[5] = 0x00; // Default
  buf[6] = 0x00; // Default
  buf[7] = 0x00; // Default
  int nbytes = 8;

  if( argc > 1 )
    {
      nbytes = 0;
      for( int i = 1; i < argc; i++ )
	{
	  // buf[i-1] = atoi(argv[i]);
	  buf[i-1] = strtol(argv[i], NULL, 16);
	  nbytes++;
	}
    }

  //   for( int i = 0 ; i < nbytes; i++ )
  //   printf("0x%X ", buf[i] & 0x000000FF);
  //  cout << endl;

  if( dev.BSDUsb_initialization(0x04b4,0x1801) )
    { 
      cout << "Initialization unsuccessful :-(" << endl;
      return -1;
    }
  
  if( dev.BSDUsb_bulk_write_EP2OUT(buf,nbytes) )
    {
      cout << "Write unsuccessful :-( " << endl;
      return -1;
    }

  cout << "EP2OUT Write: " ;
  for( int i = 0; i < nbytes; i++ )
    printf("0x%02X ",0x000000FF & buf[i]);
  cout << endl;

  return 0;
}
