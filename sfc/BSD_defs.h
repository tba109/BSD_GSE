/*
 * Tyler Anderson
 * Wed Jan 23 13:45:04 EST 2013
 * This is the BSD command format
 */
#ifndef _BSD_DEFS_H_
#define _BSD_DEFS_H_

/////////////////////////////////////////////////
// Target defines
/////////////////////////////////////////////////
// b7 is the recoverable error bit. Only set when BSD responds that the
// command has an error.
#define ERROR 0x80
#define ERRORMASK 0x80
#define ERROROFFSET 7

// Action related definitions
#define NOP 0x00
#define GET 0x01
#define SET 0x02
#define EVENT 0x03
#define SHUTDOWN 0x04
#define RESET 0x05 
#define RESET_FIFO 0x06

#define ACTIONMASK 0x07 
#define ACTIONOFFSET 0

// Parameter related definitions
#define FPGA 0x00
#define PED1H 0x01
#define PED2H 0x02
#define PED3H 0x03
#define PED4H 0x04
#define THR1 0x05
#define THR2 0x06
#define D11_DL 0x07
#define D21_DL 0x08
#define D12_DL 0x0A
#define D22_DL 0x0B
#define D13_DL 0x0D
#define D23_DL 0x0E
#define D14_DL 0x10
#define D24_DL 0x11
#define D11_WD 0x13
#define D21_WD 0x14
#define D12_WD 0x16
#define D22_WD 0x17
#define D13_WD 0x19
#define D23_WD 0x1A
#define D14_WD 0x1C
#define D24_WD 0x1D
#define DON1_DL 0x1F
#define DON2_DL 0x20
#define DON3_DL 0x21
#define DON4_DL 0x22
#define DON1_WD 0x23
#define DON2_WD 0x24
#define DON3_WD 0x25
#define DON4_WD 0x26
#define TRIG_MODE 0x27
#define CONF_MODE 0x28
#define COINC_WD 0x29
#define RECOV_WD 0x2A
#define DIG_DL 0x2B
#define PULSE1_DL 0x2C
#define PULSE2_DL 0x2D
#define PULSE1_WD 0x2E
#define PULSE2_WD 0x2F
#define PULSE1_AMP 0x30
#define PULSE2_AMP 0x31
#define PULSE1_ON 0x32
#define PULSE2_ON 0x33
#define HV11 0x34
#define HV21 0x35
#define HV31 0x36
#define HV12 0x37
#define HV22 0x38
#define HV32 0x39
#define HV13 0x3A
#define HV23 0x3B
#define HV33 0x3C
#define HV14 0x3D
#define HV24 0x3E
#define HV34 0x3F
#define HVT1 0x40
#define HVT2 0x41
#define PEDT1H 0x42
#define PEDT2H 0x43
#define D1T1_DL 0x44
#define D2T1_DL 0x45
#define D1T2_DL 0x47
#define D2T2_DL 0x48
#define D1T1_WD 0x4A
#define D2T1_WD 0x4B
#define D1T2_WD 0x4D
#define D2T2_WD 0x4E
#define D11_CM 0x50
#define D21_CM 0x51
#define D12_CM 0x53
#define D22_CM 0x54
#define D13_CM 0x56
#define D23_CM 0x57
#define D14_CM 0x59
#define D24_CM 0x5A
#define D1T1_CM 0x5C
#define D2T1_CM 0x5D
#define D1T2_CM 0x5F
#define D2T2_CM 0x60
#define DON1_CM 0x62
#define DON2_CM 0x63
#define DON3_CM 0x64
#define DON4_CM 0x65
#define D11_ON 0x66
#define D21_ON 0x67
#define D12_ON 0x69
#define D22_ON 0x6A
#define D13_ON 0x6C
#define D23_ON 0x6D
#define D14_ON 0x6F
#define D24_ON 0x70
#define D1T1_ON 0x72
#define D2T1_ON 0x73
#define D1T2_ON 0x75
#define D2T2_ON 0x76
#define DON1_ON 0x78
#define DON2_ON 0x79
#define DON3_ON 0x7A
#define DON4_ON 0x7B
#define TRIG1_RATE 0x7C
#define TRIG2_RATE 0x7D
#define TRIG_SELF_RATE 0x7E
#define TRIG_MT_RATE 0x7F
#define TRIG_T0_RATE 0x80
#define PED1L 0x81
#define PED2L 0x82
#define PED3L 0x83
#define PED4L 0x84
#define PED5H 0x85
#define PED5L 0x86
#define PED6H 0x87
#define PED6L 0x88
#define PED7H 0x89
#define PED7L 0x8A
#define PED8H 0x8B
#define PED8L 0x8C
#define PED9H 0x8D
#define PED9L 0x8E
#define PED10H 0x8F
#define PED10L 0x90
#define PED11H 0x91
#define PED11L 0x92
#define PED12H 0x93
#define PED12L 0x94
#define PED13H 0x95
#define PED13L 0x96
#define PED14H 0x97
#define PED14L 0x98
#define PED15H 0x99
#define PED15L 0x9A
#define PED16H 0x9B
#define PED16L 0x9C
#define PEDT1L 0x9D
#define PEDT2L 0x9E
#define PON_QA 0x9F
#define PON_QB 0xA0
#define PON_QC 0xA1
#define PON_QD 0xA2
#define PON_T1 0xA3
#define PON_T2 0xA4
#define PON_FEEX 0xA5
#define PON_FEEY 0xA6
#define PON_FEEZ 0xA7



#define NGETCONF_PARAMS 144

#endif
