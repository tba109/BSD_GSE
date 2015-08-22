#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_resolve.h"
#include "BSD-event.h"
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

BSD_event curevt;

time_t curtime;

void FillData(int nbytes, unsigned char * bufin, FILE * fp)
{
  if( fp <= 0 )
    return; // just an error


  curtime = time(&curtime);

  //memset(bufin,0,1000);
  
  /*
  if( ( (bufin[0] & 0x000000FF) != 0x0000008F) || 
      ( (bufin[1] & 0x000000FF) != 0x000000C7) || 
      ( (bufin[2] & 0x000000FF) != 0x000000CD) || 
      ( (bufin[3] & 0x000000FF) != 0x000000DC) ) 
  */
   if( ( bufin[0] != 0x0000008F) || 
       ( bufin[1] != 0x000000C7) || 
       ( bufin[2] != 0x000000CD) || 
       ( bufin[3] != 0x000000DC) ) 
     {
       printf("event_resolve::FillData: Error: Sync slip! Fill data packet with zeros!\n");
       printf("%x %x %x %x\n",bufin[0],bufin[1],bufin[2],bufin[3]);
       return;
     }
  
  int rbc = 0;
  
  rbc += 4;

  // Fill in the data structure
  curevt.event_number =   
    ( (bufin[4] << 24) & 0xFF000000 ) |
    ( (bufin[5] << 16) & 0x00FF0000 ) |
    ( (bufin[6] <<  8) & 0x0000FF00 ) |
    ( (bufin[7]      ) & 0x000000FF );
 
  printf("curevt.event_number = %d\n", curevt.event_number);
  curevt.event_count = bufin[8];
  curevt.trig_mode = 0x3F & (bufin[9]);
  curevt.conf_mode = 0x0F & (bufin[10]);
  curevt.trig2 = 0x01 & (bufin[11] >> 2);
  curevt.trig1 = 0x01 & (bufin[11] >> 1);
  curevt.extin = 0x01 & (bufin[11]);

  rbc += 8;

  for( int i = 0; i < NUM_LATE; i++ )
    {
      curevt.bsdlate_lg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
      curevt.bsdlate_hg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
    }
  
  for( int i = 0; i < NUM_EARLY; i++ )
    {
      curevt.bsdearly_lg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
      curevt.bsdearly_hg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
    }
  
  fprintf(fp,"%d ",curtime);

  fprintf(fp,"%d %d %d %d %d %d %d ",curevt.event_number, curevt.event_count, curevt.trig_mode, curevt.conf_mode, curevt.trig2, curevt.trig1, curevt.extin);
  
  for( int i = 0; i < NUM_LATE; i++ )
    {
      fprintf(fp,"%d %d ", curevt.bsdlate_lg[i],curevt.bsdlate_hg[i]);
    }
  
  for( int i = 0; i < NUM_EARLY; i++ )
    {
      fprintf(fp,"%d %d ", curevt.bsdearly_lg[i],curevt.bsdearly_hg[i]);
    }
  fprintf(fp,"\n");
  
  return;
}

// Convert a hex number to a four bit
char * fourbitstr(int num)
{
  static char retstr[5];
  for(int i = 4; i != 0; i--)
    {
      retstr[i-1] = num & 1 ? '1' : '0';
      num /= 2;
    }
  retstr[4] = '\0';
  return retstr;
}

void PrintAll()
{
  printf("\n");
  printf("%s",ctime(&curtime));
  printf("     EVTNO    EVTCNT     TRIG_MODE     CONF_MODE     TRIG2     TRIG1     EXTIN\n");
  printf("%10d",curevt.event_number);
  printf("%10d",curevt.event_count);
  printf("%14d",curevt.trig_mode);
  printf("%14d",curevt.conf_mode);
  printf("%10d",curevt.trig2);
  printf("%10d",curevt.trig1);
  printf("%10d",curevt.extin);
  printf("\n");
  printf("\n");

  printf("          PMT1   PMT2   PMT3   PMT4   PMT5   PMT6   PMT7   PMT8   PMT9   PMT10   PMT11   PMT12   PMT13   PMT14   PMT15   PMT16  PMTT1  PMTT2\n"); 
  
  printf("LG:    ");
  for(int i = 0; i < NUM_LATE; i++ )
    {
      if( i < 9 )
	printf("%7d",curevt.bsdlate_lg[i]);
      else
	printf("%8d",curevt.bsdlate_lg[i]);
    }
  
  printf("%7d",curevt.bsdearly_lg[0]);
  printf("%7d",curevt.bsdearly_lg[1]);
  printf("\n");

  printf("HG:    ");
  for(int i = 0; i < NUM_LATE; i++ )
    {
      if( i < 9 )
	printf("%7d",curevt.bsdlate_hg[i]);
      else
	printf("%8d",curevt.bsdlate_hg[i]);
    }
  
  printf("%7d",curevt.bsdearly_hg[0]);
  printf("%7d",curevt.bsdearly_hg[1]);
  printf("\n");
}
