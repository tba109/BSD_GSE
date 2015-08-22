/*
 * Tyler Anderson Mon Nov 12 13:26:01 EST 2012
 * Write to EP6
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

  unsigned char buf[2000];
  for( int i = 0; i < 2000; i++ )
    buf[i] = 0;
  int nbytes = 8; // Default
  
  if( argc > 1 )
    nbytes = atoi(argv[1]);

  if( dev.BSDUsb_initialization(0x04b4,0x1801) )
    { 
      cout << "Initialization unsuccessful :-(" << endl;
      return -1;
    }
 
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
