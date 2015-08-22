#ifndef _BSDCMD_H_
#define _BSDCMD_H_

#include "BSD_defs.h"
#include "BSDUsb.h"
#include "BSDCmd.h"

/* 
 * Tyler Anderson Wed Jan 23 13:16:08 EST 2013
 * This is the class for command processing, including checking and conversion from a 
 * given incomming command specified as "cmd, param, value" to actual bytes. 
 */

class BSDCmd
{
 public:
  /////////////////////////////////////////////////////////////////////////
  // Default constructor
  /////////////////////////////////////////////////////////////////////////
  BSDCmd();
  
  /////////////////////////////////////////////////////////////////////////
  // Default destructor
  ////////////////////////////////////////////////////////////////////////
  virtual ~BSDCmd();

  ///////////////////////////////////////////////////////////////////////
  // Check the command, convert it, send it, receive the response
  // and convert it.
  ///////////////////////////////////////////////////////////////////////
  int BSDCmd_ProcessCommand(unsigned int cmd, unsigned int param, unsigned short * value, BSDUsb * dev );

  /////////////////////////////////////////////////////////////////////
  // Get the configuration info for the TCD
  /////////////////////////////////////////////////////////////////////
  int BSDCmd_GetConf(unsigned short * buf, BSDUsb * dev);
  
 private:
  // Some of these checkers really don't do much, but it's nice to have them, in case we
  // want to check more things later
  
  int checkNop();
  
  int checkGet();
  
  int checkSet();
  
  int checkShutdown();
  
  int checkEvent();

  int checkReset();

  int checkResetFifo();

  //////////////////////////////////////////////////////////////////
  // Data members
  /////////////////////////////////////////////////////////////////
  unsigned int dcmd;
  unsigned dparam;
  unsigned short * dvalue;
  unsigned char ddoresp; // only read the response when this is 1 otherwise don't
};

#endif // _BSDCMD_
