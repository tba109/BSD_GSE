/* 
 * Tyler Anderson Mon Nov 12 13:43:52 EST 2012
 * BSDUsb class methods
 */
#include <usb.h>
#include <stdio.h>

#include "BSDUsb.h"
#include "BSD_err.h"

BSDUsb::BSDUsb()
{
  usbdev = NULL;
  usbhdl = NULL;
  claimed = 0;
  release_ret = 0;
}

int BSDUsb::BSDUsb_initialization(unsigned int vendor, unsigned int product)
{
  // Initialize the USB library
  usb_init();  
  printf("BSDUsb::BSDUsb_initialization: USB library initialized\n");

  // Find the buses
  if(usb_find_busses() < 0)
    {  
      printf("BSDUsb::BSDUsb_initialization: usb_find_busses failed \n");  
      return -BSDUSB_SYS_FIND_BUSSES_ERR; 
    }
  printf("BSDUsb::BSDUsb_initialization: USB system bus list updated\n");

  // Find the devices
  if(usb_find_devices() < 0)
    {  
      printf("BSDUsb::BSDUsb_initialization: usb_find_devices failed \n");  
      return -BSDUSB_SYS_FIND_DEVICES_ERR;
    }
  printf("BSDUsb::BSDUsb_initialization: USB system device list updated\n");

  // Assign the device to usbdev
  if(!(usbdev=findDevice(vendor,product)))
    {
      printf("BSDUsb::BSDUsb_initialization: No BSD USB device attached.\n");
      return -BSDUSB_FIND_DEVICE_ERR;
    }
  printf("BSDUsb::BSDUsb_initialization: BSD USB device found\n");
  printf("BSDUsb::BSDUsb_initialization: Using ID %04x:%04x on %s.%s.\n",usbdev->descriptor.idVendor,usbdev->descriptor.idProduct,usbdev->bus->dirname,usbdev->filename);

  // Open the USB device
  if( open() != 0 )
    {
      printf("BSDUsb::BSDUsb_initialization: Open failed.\n");
      return -BSDUSB_OPEN_ERR;
    }
  printf("BSDUsb::BSDUsb_initialization: BSD USB device opened\n");

  // Claim the interface (This is the only class using it after all, so why not claim it now?
  
  if(claim_interface())
    {  
      printf("BSDUsb::BSDUsb_initialization: Failed to claim interface 0: %s\n",usb_strerror());  
      return -BSDUSB_CLAIM_ERR;
    }
  
  // Set the alternate interface
  if(usb_set_altinterface(usbhdl,0)<0)
    {
      printf("BSDUsb::BSDUsb_initialize: Failed to set altinterface 0: %s\n",usb_strerror());
      return -BSDUSB_ALTINTERFACE_ERR;
    }
  
    // All's well!
  return 0;
}

int BSDUsb::BSDUsb_reinitialization(unsigned int vendor, unsigned int product)
{
  close_all();
  return BSDUsb_initialization(vendor,product);
}

int BSDUsb::BSDUsb_shutdown()
{
  return close_all();
}


int BSDUsb::BSDUsb_bulk_write_EP2OUT(const char *buf, size_t nbytes)
{ 
  int retval = 0;
  
  // EP2OUT only takes 512 bytes total
  if( nbytes > 512 )
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP2OUT: > 64 bytes for EP1OUT write\n");
      return -BSDUSB_WRITE_TOO_MANY_BYTES_ERR;
    }
  
  // Check if TCD USB device is open
  if(!IsOpen())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP2OUT: BSD USB device not open!\n");
      return -BSDUSB_OPEN_ERR;
    }
  
  // Check if TCD USB device is claimed
  if(!IsClaimed())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP1IN: BSD USB device not claimed!\n");
      return -BSDUSB_CLAIM_ERR;
    }
  
  // Write to EP2OUT
  if( (retval = usb_bulk_write(usbhdl,2,(char*)buf,nbytes,10)) < 0 )// timeout is ms  
    {
      printf("BSDUsb::BSDUsb_bulk_write: Write attempt failed. Returned %d\n",retval);
      printf("usbhdl = %d\n",usbhdl);
      return -BSDUSB_WRITE_ERR;
    }
  //printf("Was able to write\n");
  return 0;
}

int BSDUsb::BSDUsb_bulk_write_EP4OUT(const char *buf, size_t nbytes)
{ 
  int retval = 0;
  
  // EP2OUT only takes 512 bytes total
  if( nbytes > 512 )
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP2OUT: > 64 bytes for EP1OUT write\n");
      return -BSDUSB_WRITE_TOO_MANY_BYTES_ERR;
    }
  
  // Check if TCD USB device is open
  if(!IsOpen())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP2OUT: BSD USB device not open!\n");
      return -BSDUSB_OPEN_ERR;
    }
  
  // Check if TCD USB device is claimed
  if(!IsClaimed())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP1IN: BSD USB device not claimed!\n");
      return -BSDUSB_CLAIM_ERR;
    }
  
  // Write to EP4OUT
  if( (retval = usb_bulk_write(usbhdl,4,(char*)buf,nbytes,10)) < 0 )// timeout is ms  
    {
      printf("BSDUsb::BSDUsb_bulk_write: Write attempt failed. Returned %d\n",retval);
      printf("usbhdl = %d\n",usbhdl);
      return -BSDUSB_WRITE_ERR;
    }
  //printf("Was able to write\n");
  return 0;
}

int BSDUsb::BSDUsb_bulk_read_EP8IN(unsigned char *buf, size_t nbytes)
{
  int retval = 0;
  if(!IsClaimed())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP1IN: BSD USB device not claimed!\n");
      return -BSDUSB_CLAIM_ERR;
    }
  // TODO change this timeout to something more reasonable, like 10ms
  if( (retval = usb_bulk_read(usbhdl,8,(char*)buf,nbytes,10)) < 0 ) // timeout is in ms
    {
      // printf("BSDUsb::BSDUsb_bulk_read_EP8IN: Read attempt failed. Returned %d\n",retval);
      // printf("usbhdl = %d\n",usbhdl);
      return -BSDUSB_READ_ERR;
    }
  
  // printf("BSDUsb::BSDUsb_bulk_read_EP6IN: returned from reading!\n");
      
  return 0;
 
}

int BSDUsb::BSDUsb_bulk_read_EP8IN_block(unsigned char *buf, size_t nbytes)
{
  int retval = 0;
  if(!IsClaimed())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP1IN: BSD USB device not claimed!\n");
      return -BSDUSB_CLAIM_ERR;
    }
  // TODO change this timeout to something more reasonable, like 10ms
  if( (retval = usb_bulk_read(usbhdl,8,(char*)buf,nbytes,1000000)) < 0 ) // timeout is in ms
    {
      // printf("BSDUsb::BSDUsb_bulk_read_EP8IN: Read attempt failed. Returned %d\n",retval);
      // printf("usbhdl = %d\n",usbhdl);
      return -BSDUSB_READ_ERR;
    }
  
  // printf("BSDUsb::BSDUsb_bulk_read_EP6IN: returned from reading!\n");
      
  return 0;
 
}

int BSDUsb::BSDUsb_bulk_read_EP6IN(unsigned char *buf, size_t nbytes)
{
  int retval = 0;
  if(!IsClaimed())
    {
      // printf("BSDUsb::BSDUsb_bulk_write_EP1IN: BSD USB device not claimed!\n");
      return -BSDUSB_CLAIM_ERR;
    }
  // TODO change this timeout to something more reasonable, like 10ms
  if( (retval = usb_bulk_read(usbhdl,6,(char*)buf,nbytes,150)) < 0 ) // timeout is in ms
    {
      // printf("BSDUsb::BSDUsb_bulk_read_EP6IN: Read attempt failed. Returned %d\n",retval);
      // printf("usbhdl = %d\n",usbhdl);
      return -BSDUSB_READ_ERR;
    }
  
  // printf("BSDUsb::BSDUsb_bulk_read_EP6IN: returned from reading!\n");
      
  return 0;
 
}

// Reset the BSD USB device
int BSDUsb::BSDUsb_fx2lp_reset(const char * path, unsigned int vendor, unsigned int product)
{
  int retval = 0;
  BSDUsb_reinitialization();
  
  // Reset is accomplished by writing a 1 to address 0xE600. 
  const size_t reset_addr = 0xe600;
  
  unsigned char val = 1;
  if( (retval = write_RAM(reset_addr,&val,1)) )
    {
      printf("BSDUsb::BSDUsb_fx2lp_reset: Error resetting FX2LP \n");
      return -BSDUSB_RESET_FX2LP_ERR;
    }
  

  if( (retval =  BSDUsb_reinitialization()) )
    return retval;
  
  FILE *fp = fopen(path,"r");
  if(!fp)
    {  
      // printf("BSDUsb::BSDUsb_fx2lp_reset: Failed to open %s \n",path);
      return -BSDUSB_OPEN_IHX_FILE_ERR;
    }
  
  const size_t buflen=1024;  // Hopefully much too long for real life...
  char buf[buflen];
  unsigned char data[1024];
  unsigned char cksum = 0;
  unsigned int d = 0;
  unsigned int file_cksum = 0;

  char * s;
  unsigned int nbytes = 0, addr = 0, type = 0;
  while(1)
    {
      *buf='\0';
      nbytes = 0;
      addr = 0;
      type = 0;
      cksum = 0;
      d = 0;
      file_cksum = 0;

      // Read in and error check
      if(!fgets(buf,buflen,fp))
	{
	  if( feof(fp) )
	    break;
	  
	  // printf("Error reading %s \n",path);
	  fclose(fp);  
	  fp=NULL;
	  return -BSDUSB_READ_IHX_FILE_ERR;
	}
      
      // Check for format violations
      s = buf;
      if( *s != ':' )
	{
	  // printf("BSDUsb::BSDUsb_fx2lp_reset: Format violation 1 \n");
	  return -BSDUSB_IHX_FORMAT_VIOLATION1_ERR;
	}
      s++;

      if( sscanf(s,"%02x%04x%02x",&nbytes,&addr,&type) != 3 )
	{
	  printf("BSDUsb::BSDUsb_fx2lp_reset: Format violation 2. nbytes = %02x addr = %04x, type = %02x \n",nbytes,addr,type);
	  return -BSDUSB_IHX_FORMAT_VIOLATION2_ERR;
	}
      s+=8;
      
      if( type == 0 )
	{
	  //printf("BSDUsb::BSDUsb_fx2lp_reset: Writing nbytes=%d at addr=0x%04x\n",nbytes,addr);
	  if( (nbytes < 0) || (nbytes > 256) )
	    return -BSDUSB_IHX_NBYTES_ERR;
	  
	  // Calc 
	  cksum=nbytes+addr+(addr>>8)+type;
	  for(unsigned int i=0; i<nbytes; i++)
	    {
	      d = 0;
	      if( sscanf(s,"%02x",&d) != 1 )
		{  
		  // printf("BSDUsb::BSDUsb_fx2lp_reset: Format violation 3 \n");
		  return -BSDUSB_IHX_FORMAT_VIOLATION3_ERR;  
		}
	      s+=2;
	      data[i]=d;
	      cksum+=d;
	    }
	  
	  if( sscanf(s,"%02x",&file_cksum) != 1 )
	    {
	      // printf("BSDUsb::BSDUsb_fx2lp_reset: Format violation 4 \n");
	      return -BSDUSB_IHX_FORMAT_VIOLATION4_ERR;  
	    }
	  
	  if( (cksum+file_cksum) & 0xff )
	    {  
	      // printf("BSDUsb::BSDUsb_fx2lp_reset: Checksum mismatch \n");  
	      return -BSDUSB_CHECKSUM_ERR;  
	    }
	  
	  if( (retval = write_RAM(addr,data,nbytes)) )
	    return -BSDUSB_WRITE_RAM_ERR;  
	    
	}
      else if(type == 1) // EOF marker. Oh well, trust it. 
	break;
	
      else
	{
	  // printf("BSDUsb::BSDUsb_fx2lp_reset: Unknown entry type \n");
	  return -BSDUSB_UNKNOWN_TYPE_ERR;
	}
    }

  if(fp)
    fclose(fp);  

  // Start running by writing a 0 to that address.  
  val = 0;
  if( (retval = write_RAM(reset_addr,&val,1)) )
    {
      printf("BSDUsb::BSDUsb_fx2lp_reset: Error restarting FX2LP after reset \n");
      return -BSDUSB_RESTART_FX2LP_ERR;
    }
  
  return 0;
}

int BSDUsb::write_RAM(size_t addr, const unsigned char *data, size_t nbytes)
{
  if(!IsOpen())
    {  
      // printf("BSDUsb::write_RAM: Not connected! \n");  
      return -BSDUSB_WRITE_RAM_CONNECTION_ERR;  
    }
  
  int n_errors = 0;
  
  const size_t chunk_size = 16;
  const unsigned char *d = data;
  const unsigned char *dend = data+nbytes;
  
  while( d < dend )
    {
      size_t bs = dend-d;
      if( bs > chunk_size )  
	bs = chunk_size;
      size_t dl_addr = addr + ( d - data );
      int rv = usb_control_msg(usbhdl,0x40,0xa0, /*addr=*/dl_addr,0, /*buf=*/(char*)d,/*size=*/bs, /*timeout=*/1000/*msec*/);
      
      if( rv < 0 )
	{  
	  // printf("BSDUsb::write_RAM: Writing %zu bytes at 0x%zx \n", bs, dl_addr);  
	  ++n_errors;  
	}
      d += bs;
    }
  
  return n_errors;
}

// Claim the USB interface
int BSDUsb::claim_interface()
{
  if( !claimed )
    {
      usb_claim_interface(usbhdl,0);
      claimed = 1;
    }
  
  return 0;
}

// Release the USB interface
int BSDUsb::release_interface()
{
  if( claimed )
    if( (release_ret = usb_release_interface(usbhdl,0)) == 0 )
      claimed = 0;
  
  return 0;
}

// Close the USB handle
int BSDUsb::close_hdl()
{
  // printf("BSDUsb::close_hdl: usbhdl = %d\n",usbhdl);
  //printf("BSDUsb::close_hdl: usbdev = %d\n",usbdev);
  
  // Close the USB handle
  if(usbhdl)
    {
      // Release the interface
      release_interface();
      
      // Close the handler
      usb_close(usbhdl);  

    }
  
  // Reset pointer
  usbhdl=NULL;
  
  // printf("exiting close_hdl\n");
  return 0;
}

// Close handle and reinitialize the device pointer
int BSDUsb::close_all()
{
  // printf("BSDUsb::close_all: usbhdl = %d\n",usbhdl);
  // printf("BSDUsb::close_all: usbdev = %d\n",usbdev);
  
  if(usbhdl)
    {
      // Release the interface
      release_interface();
      // printf("inteface release\n");

      // Close the handler
      usb_close(usbhdl);
      // printf("handle closed\n");
    }

  // Reset pointers
  usbhdl=NULL;
  usbdev=NULL;
  
  // printf("exiting close_all\n");
  return 0;
}

int BSDUsb::open()
{
  // Close any open USB handle here
  close_hdl();
    
  // printf("BSDUsb::open(): Old BSD USB handle closed\n");

  // Open handle
  if(!(usbhdl=usb_open(usbdev)))
    {
      // printf("BSDUsb::open(): Failed to open device: %s\n",usb_strerror());
      return -BSDUSB_OPEN_ERR;  
    }
  // printf("BSDUsb::open(): New USB handle opened\n");
  return 0;
}

// Find the device in the list of avaliable devices
struct usb_device * BSDUsb::findDevice(int vendor,int product)
{
  for(usb_bus *b=usb_busses; b; b=b->next)
    for(struct usb_device *d=b->devices; d; d=d->next)
      if(d->descriptor.idVendor==vendor && d->descriptor.idProduct==product)
	return(d);
  return(NULL);
}


BSDUsb::~BSDUsb()
{
  ;
}

