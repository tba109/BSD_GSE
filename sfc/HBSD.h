#ifndef _HBSD_
#define _HBSD_

#include "BSDUsb.h"
#include "BSDCmd.h"
#include "BSDEvt.h"
#include "crmevt_fake.h" // TODO: replace this with the real header

/*
 * Tyler Anderson Tue Dec 13 10:28:29 EST 2011
 * This is the tcd2 USB class for the CREAM CDAQ
 */
class HBSD
{
 public:
  //////////////////////////////////////////////////////////////////////////////
  // Default constructor
  //////////////////////////////////////////////////////////////////////////////
  HBSD();

  /////////////////////////////////////////////////////////////////////////////
  // Default destructor
  /////////////////////////////////////////////////////////////////////////////
  virtual ~HBSD();

  /////////////////////////////////////////////////////////////////////////////
  // Open the USB routines and libraries
  // Returns    0 : good
  //           <0 : error code
  /////////////////////////////////////////////////////////////////////////////
  int open(int vendor = 0x04b4, int product = 0x1800);

  /////////////////////////////////////////////////////////////////////////////
  // Close all the USB routine stuff
  // Returns    0 : good
  //           <0 : error code
  /////////////////////////////////////////////////////////////////////////////
  int close();

  /////////////////////////////////////////////////////////////////////////////
  // Reopen the USB connection
  // Returns    0 : good
  //           <0 : error code
  /////////////////////////////////////////////////////////////////////////////
  int reopen(int vendor = 0x04b4, int product = 0x1800);
  
  ////////////////////////////////////////////////////////////////////////////
  // Check a commands, send it, and read back the response
  // Parameters unsigned int cmd: the numerical command value
  //            unsigned int param, the numerical parameter number
  //            unsigned short * value, pointer to the data value, used for
  //                 a SET and readback from a GET
  // Returns    0 : good
  //           <0 : error code
  ////////////////////////////////////////////////////////////////////////////
  int BSD_execute(unsigned int cmd, unsigned int param, unsigned short * value);
    
  ///////////////////////////////////////////////////////////////////////////
  // Get the configuration data and update it to the tcf structures
  // Parameters tcf_data &tcf_for_bsd, the BSD config 
  // Returns    0 : good
  //           <0 : error code
  //////////////////////////////////////////////////////////////////////////
  int BSD_getconf(tcf_data &tcf_for_bsd);

  ////////////////////////////////////////////////////////////////////////////
  // Readout BSD data and store the results in the character buffers
  // Returns    0 good
  //           <0 error code
  ////////////////////////////////////////////////////////////////////////////
  int BSD_readout(int *count_BSDdata, unsigned char *BSD_buf);

  ////////////////////////////////////////////////////////////////////////////
  // Readout BSD data generated by a command
  // Store the results in the character buffers
  // Returns    0 good
  //           <0 error code
  ////////////////////////////////////////////////////////////////////////////
  int BSD_readout_software_generated(int *count_BSDdata, unsigned char *BSD_buf);

  //////////////////////////////////////////////////////////////////////////////
  // USB initialization. Wrapper to the USB initialization function
  // Parameters unsigned int vendor, vendor ID number (0x04b4 in development)
  //            unsigned int product, product ID number (0x1801 in development)
  // Returns    0 everything worked okay
  //           -1 there was an error
  /////////////////////////////////////////////////////////////////////////////
  int BSD_initialization(unsigned int vendor=0x04b4, unsigned int product=0x0098);
  
  /////////////////////////////////////////////////////////////////////////////
  // USB shutdown
  // Returns   0 shutdown successful
  // Returns  -1 shutdown unsuccessful
  ////////////////////////////////////////////////////////////////////////////
  int BSD_shutdown();

  ////////////////////////////////////////////////////////////////////////////
  // Wrapper for reinitializing the TCD USB board
  // Parameters const char * path, path for FX2LP firmware
  //            unsigned int vendor, vendor ID number (0x04b4 in development)
  //            unsigned int product, product ID number (0x0098 in development)
  // Returns    0 everything worked okay
  //           -1 there was an error
  ///////////////////////////////////////////////////////////////////////////
  int BSD_fx2lp_reset(const char * path = "./sfc/BSD_firmware.ihx", unsigned int vendor=0x04b4, unsigned int product=0x1800);

  ////////////////////////////////////////////////////////////////////////////
  // Data members
  ////////////////////////////////////////////////////////////////////////////
  BSDUsb dev;
  BSDCmd cmdproc;
  BSDEvt evtproc;
};

#endif // _HBSD__
