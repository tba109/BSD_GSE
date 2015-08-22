/*
 * Tyler Anderson Wed Jan 23 06:52:11 EST 2013
 */
#ifndef _BSDEVT_H_
#define _BSDEVT_H_

#include "BSD_defs.h"
#include "BSDUsb.h"
#include "BSD-event.h"

class BSDEvt
{
 public:
  //////////////////////////////////////////////////////////////////
  // Default constructor
  //////////////////////////////////////////////////////////////////
  BSDEvt();

  /////////////////////////////////////////////////////////////////
  // Default destructor
  /////////////////////////////////////////////////////////////////
  virtual ~BSDEvt();

  ////////////////////////////////////////////////////////////////
  // Tyler Anderson Wed Jan 23 16:33:28 EST 2013
  // Convert the incoming event to the proper format
  // Returns    0 : good
  //           <0 : error code
  ////////////////////////////////////////////////////////////////
  int BSDEvt_ProcessEvent(int * count_BSDdata, unsigned char * BSD_buf, BSDUsb * dev);

 private:
  //////////////////////////////////////////////////////////////
  // Initilaize the data members
  //////////////////////////////////////////////////////////////
  void initialize();

  ///////////////////////////////////////////////////////////////
  // Fill the data into local data structures
  // Parameters int nbytes, number of bytes in buffer to convert
  // I'm adding this function just in case we need it, but
  // in reality, it may do us no good.
  //            unsigned char * bufin, buffer to convert
  // Returns    0 : good
  //           <0 : error code
  ///////////////////////////////////////////////////////////////
  int conv_buf(int nbytes, unsigned char * bufin);

  //////////////////////////////////////////////////////////////
  // Initialize all the data members
  //////////////////////////////////////////////////////////////
  void intialize();

  ///////////////////////////////////////////////////////////////
  // Data members
  ///////////////////////////////////////////////////////////////
  BSD_event currevent;
};

#endif //_BSDEVT_H_
