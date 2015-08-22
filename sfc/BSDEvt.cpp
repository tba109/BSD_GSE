#include <string.h>
#include <stdio.h>
#include "BSDEvt.h"
#include "BSD-event.h"
#include "BSD_err.h"

// Tyler Anderson Wed Jan 23 06:53:28 EST 2013

BSDEvt::BSDEvt()
{
  initialize();
}

void BSDEvt::initialize()
{
  // Initialize the event structure
  currevent.event_number = 0;
  currevent.event_count = 0;
  currevent.trig_mode = 0;
  currevent.conf_mode = 0;
  currevent.trig2 = 0;
  currevent.trig1 = 0;
  currevent.extin = 0;
  
  for( int i = 0; i < NUM_LATE; i++ )
    currevent.bsdlate_hg[i] = 0;

  for( int i = 0; i < NUM_LATE; i++ )
    currevent.bsdlate_lg[i] = 0;

  for( int i = 0; i < NUM_EARLY; i++ )
    currevent.bsdearly_hg[i] = 0;

  for( int i = 0; i < NUM_EARLY; i++ )
    currevent.bsdearly_lg[i] = 0;

  return;
}

int BSDEvt::BSDEvt_ProcessEvent(int * count_BSDdata, unsigned char * BSD_buf, BSDUsb * dev)
{
  int retval = 0;
  initialize();
  
  unsigned char bufin[512];
  int nbytesin = NUM_RAW_BYTES;

  if( (retval = dev->BSDUsb_bulk_read_EP8IN_block(bufin,nbytesin)) )
    {
      // printf("BSDEvt::BSDEvt_ProccessEvent: Read from TCD USB device failed: %d\n",retval);
      return retval;
    }
  
  if( nbytesin != NUM_RAW_BYTES )
    return -USB_SYNC_ERR;

  if( (bufin[0] != 0x8F) && (bufin[1] != 0xC7) && (bufin[2] != 0xCD) && (bufin[3] != 0xDC) ) 
    return -USB_SYNC_ERR;

  // hard copy the data to the buffer
  for( int i = 0; i < nbytesin; i++ )
    BSD_buf[i] = bufin[i];
  
  *count_BSDdata = nbytesin; 

  // printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
  // for( int i = 0; i < *count_BSDdata; i++ )
  // printf("%hu\n",BSD_buf[i]);
  // 	 printf("-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");

  // printf("%s %d\n","BSDEvent::ProcessEvent: retval = ",retval);
  // printf("%s %d\n","BSDEvent::ProcessEvent: *count_BSDdata = ",*count_BSDdata);
  return retval;
}

int BSDEvt::conv_buf(int nbytesin, unsigned char *bufin)
{

  int rbc = 0;

   // Make sure we have the right number of bytes in
  if( nbytesin != NUM_RAW_BYTES ) // raw number of data bytes
    {
      // printf("BSDEvt::BSDEvt_ConvertEvent: Wrong number of bytes %d, needs to be %d\n",nbytesin, NUM_RAW_BYTES);
      return -BSDEVT_EVENT_BYTE_NUM_ERR;
    }

  if( !( bufin[0] == 0x8F && bufin[1] == 0xC7 && bufin[2] == 0xCD && bufin[3] == 0xDC ) )
    {
      // printf("BSDEvt::BSDEvt_ConvertEvent: Bad header\n");
      return -BSDEVT_BAD_HEADER;
    }
  
  rbc += 4;

  // Fill in the data structure
  currevent.event_number =   
    ( (bufin[4] << 24) & 0xFF000000 ) |
    ( (bufin[5] << 16) & 0x00FF0000 ) |
    ( (bufin[6] <<  8) & 0x0000FF00 ) |
    ( (bufin[7]      ) & 0x000000FF );
  currevent.event_count = bufin[8];
  currevent.trig_mode = 0x07 & (bufin[9] >> 5);
  currevent.conf_mode = 0x07 & (bufin[9] >> 3);
  currevent.trig2 = 0x01 & (bufin[9] >> 2);
  currevent.trig1 = 0x01 & (bufin[9] >> 1);
  currevent.extin = 0x01 & (bufin[9]);

  rbc += 6;

  for( int i = 0; i < NUM_LATE; i++ )
    {
      currevent.bsdlate_lg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
      currevent.bsdlate_hg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
    }
  
  for( int i = 0; i < NUM_EARLY; i++ )
    {
      currevent.bsdearly_lg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
      currevent.bsdearly_hg[i] = (0xFF00 & (bufin[rbc] << 8)) | (0x00FF & (bufin[rbc+1]));
      rbc+=2;
    }

  
  return 0;
}

BSDEvt::~BSDEvt()
{
  ;
}
