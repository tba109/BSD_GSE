/*
 * Tyler Anderson Tue Mar 12 15:56:58 EDT 2013
 * Simple program for sending commands
 * Sai Im Mon Apr 01 20:48:30 EDT 2013: changed pneumonic to mnemonic.
 */
#include <iostream>
#include <fstream> // Tyler Anderson Tue Jan 21 12:18:48 EST 2014
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HBSD.h"
#include "BSD_defs.h"
#include "BSD_err.h"
#include "command_resolve.h"
#include "error_resolve.h"

using namespace std;

int main(int argc, char * argv[])
{
  string filename;
  ifstream fin;
  HBSD bsdinstr;
  int retval = 0;
  if( error_resolve(bsdinstr.open(0x04b4,0x1801))) 
    return -1;

  char sendbuf[100];
  unsigned int cmd = 0, param = 0;
  unsigned short value = 0;
  
  if( argc > 1 )
    {
      cout << "Opening File " << argv[1] << endl;
      fin.open(argv[1]);
    }
  else
    {
      cout << "No script file specfied! Exiting!\n\n";
      return -1;
    }
  
  printf("\nEnter commands in mnemonic form, and the "
	 "\nresponse will be shown, along with any "
	 "\nerror messages\n");

    
  while(fin.good())
    {
      printf("------------------------------------------------\n");
      printf("Send command: \n");
      memset(sendbuf,'\0',100);
      fin.getline(sendbuf,100);
      printf("%s",sendbuf);
      
      if(sendbuf[strlen(sendbuf)-1] != ' ') // put space as last thing
	sendbuf[strlen(sendbuf)] = ' ';
	      
      printf("\n");

      if( !strcmp(sendbuf,"END ") )
	{
	  fin.close();
	  break;
	}
      
      if (command_resolve(sendbuf,cmd,param,value) )
	continue;
	      
      // cout << "cmd = " << cmd << " param = " << param << " value = " << value  << endl;
      error_resolve(bsdinstr.BSD_execute(cmd,param,&value));
      printf("Response value: ");
      
      // cout << endl;
      //printf("0x%X\n", cmd & 0x000000FF);
      //printf("0x%X\n", param & 0x000000FF);
      //printf("0x%X\n", value & 0x0000FFFF);
      printf("%d\n", value & 0x0000FFFF);
    }
  
  if( error_resolve(bsdinstr.close()) )
    return -1;
  
  printf("\n");
  return 0;
}
