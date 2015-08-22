/*
 * Tyler Anderson Tue Dec 20 23:11:08 EST 2011
 * This is just a simple error function for the working main programs
 */

#include <stdio.h>
#include "BSD_err.h"

int error_resolve( int error_code )
{
  switch( error_code )
    {
      
    case 0 :
      break;
      
    case -BSDUSB_OPEN_ERR :
      printf("BSDUsb: Open failed \n");
      break;
      
    case -BSDUSB_SYS_FIND_BUSSES_ERR :
      printf("BSDUsb: usb_find_busses failed \n");  
      break;
      
    case -BSDUSB_SYS_FIND_DEVICES_ERR :
      printf("BSDUsb: usb_find_devices failed \n");  
      break;

    case -BSDUSB_FIND_DEVICE_ERR : 
      printf("BSDUsb: could not find requested USB device in system device list \n");
      break;

    case -BSDUSB_CLAIM_ERR :
      printf("BSDUsb: Failed to claim interface 0 \n");  
      break;
      
    case -BSDUSB_ALTINTERFACE_ERR :
      printf("BSDUsb: Failed to set altinterface 2 \n");

    case -BSDUSB_READ_ERR :
      printf("BSDUsb: Read attempt failed \n");
      break;
      
    case -BSDUSB_WRITE_ERR :
      printf("BSDUsb: Write attempt failed \n");
      break;

    case -BSDUSB_WRITE_TOO_MANY_BYTES_ERR :
      printf("BSDUsb: > 64 bytes for EP1OUT write \n");
      break;
      
    case -BSDCMD_CHECK_NOP_ERR :
      printf("BSDCMD: Error in checking NOP \n");
      break;
      
    case -BSDCMD_CHECK_GET_ERR :
      printf("BSDCMD: Error in checking GET \n");
      break;

    case -BSDCMD_CHECK_SET_ERR :
      printf("BSDCMD: Error in checking SET \n");
      break;
      
    case -BSDCMD_CHECK_NODE_ERR :
      printf("BSDCMD: Error in checking node \n");
      break;
    
    case -BSDCMD_CHECK_PARAM_ERR :
      printf("BSDCMD: Error in checking parameter \n");
      break;
      
    case -BSDCMD_CHECK_HV_ERR :
      printf("BSDCMD: Error in checking HV range \n");
      break;

    case -BSDCMD_CHECK_ROSTACK_ERR :
      printf("BSDCMD: Error in checking ROSTACK \n");
      break;
      
    case -BSDEVT_EVENT_BYTE_NUM_ERR :
      printf("BSDEVT: Wrong number of bytes for event \n");
      break;

    case -BSDCMD_CHECK_CLR_NODE_ERR :
      printf("BSDCmd: Bad node \n");
      break;

    case -BSDCMD_CHECK_CLR_PARAM_ERR :
      printf("BSDCmd: Bad param \n");
      break;

    case -BSDUSB_OPEN_IHX_FILE_ERR :
      printf("BSDUsb: Failed to open .ihx file for programming \n");
      break;

    case -BSDUSB_READ_IHX_FILE_ERR :
      printf("BSDUsb: Failed in reading .ihx file for programming \n");
      break;

    case -BSDUSB_IHX_FORMAT_VIOLATION1_ERR :
      printf("BSDUsb: IHX format violation type 1 \n");
      break;
      
    case -BSDUSB_IHX_FORMAT_VIOLATION2_ERR :
      printf("BSDUsb: IHX format violation type 2 \n");
      break;

    case -BSDUSB_IHX_NBYTES_ERR :
      printf("BSDUsb: Number of bytes either < 0 or > 256 \n");
      break;

    case -BSDUSB_IHX_FORMAT_VIOLATION3_ERR :
      printf("BSDUsb: IHX format violation type 3 \n");
      break;

    case -BSDUSB_IHX_FORMAT_VIOLATION4_ERR :
      printf("BSDUsb: IHX format violation type 4 \n");
      break;

    case -BSDUSB_CHECKSUM_ERR :
      printf("BSDUsb: Checksum mismatch \n");
      break;

    case -BSDUSB_WRITE_RAM_ERR :
      printf("BSDUsb: Error writing to FX2LP RAM \n");
      break;

    case -BSDUSB_UNKNOWN_TYPE_ERR :
      printf("BSDUsb: Unknown type of .ihx file \n");
      break;

    case -BSDUSB_WRITE_RAM_CONNECTION_ERR :
      printf("BSDUsb: Error in trying to write to RAM \n");
      break;

    case -BSDUSB_RESET_FX2LP_ERR :
      printf("BSDUsb: Error in resetting the FX2LP \n");
      break;
      
    case -BSDUSB_RESTART_FX2LP_ERR :
      printf("BSDUsb: Error in restarting the FX2LP \n");
      break;
      
    case -BSDCMD_CHECK_DATAVAL_ERR :
      printf("BSDCmd: Error in data value \n");
      break;

    case -BSDCMD_EVENT_ERR :
      printf("BSDCmd: Error! The BSDCmd class does not handle event collection\n");
      break;

    case -USB_SYNC_ERR :
      printf("USB sync error!\n");
      break;

    case -BSDCMD_ACTION_UNKNOWN_ERR :
      printf("BSDCmd: Error! Action unknown\n");
      break;
            
    default :
      printf("Unknown error: %d\n",error_code);
      
    }

  return error_code;
}

