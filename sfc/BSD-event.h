#ifndef _BSD_EVENT_H_
#define _BSD_EVENT_H_

#define NUM_RAW_BYTES 84 // number of raw bytes from USB
#define NUM_LATE 16
#define NUM_EARLY 2

// New naming convention
typedef struct BSD_event_struct
{
  unsigned int event_number; /* 32 bit instrument event number */
  unsigned char event_count; /* 8-bit event counter */
  unsigned char trig_mode; /* the trigger mode for this event */
  unsigned char conf_mode; /* the confirmation mode for this event */
  unsigned char trig2; /* flagged if trig2 was involved in this event's trigger */
  unsigned char trig1; /* flagged if trig1 was involved in this event's trigger */
  unsigned char extin; /* flagged if extin was involved in this event's trigger */
  unsigned short bsdlate_hg[NUM_LATE]; /* late PMT data high gain */
  unsigned short bsdlate_lg[NUM_LATE]; /* late PMT data low gain */
  unsigned short bsdearly_hg[NUM_EARLY]; /* early PMT data high gain */
  unsigned short bsdearly_lg[NUM_EARLY]; /* early PMT data low gain */
} BSD_event;

// blanks
#define BSD_EVENT_EMPTY { 0, 0, 0, 0, 0, 0, 0, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0}, {0,0} }

#endif /* _BSD_EVENT_H_ */
