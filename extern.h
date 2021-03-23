#ifndef EXTERN_H
#define EXTERN_H

#include "mesg.h"

typedef struct HEADER_S
{
  byte id;    //Pattern ID
  byte num;   //Length of message.
} HEADER; // __attribute__((packed)) HEADER;

extern const byte NUM_RECV;     //Number of receivers to address
extern const int SDI;           //Serial PIN Red wire (not the red 5v wire) 
extern const int CKI;           //Clock PIN Green wire
extern Mesg* mesg[];
extern const int S_BUFF_LEN;
extern char s_buff[];
extern byte msg_id;

#ifdef RCVR
//void RecvCallbackFunc(int Press);
//void ReqCallbackFunc();
int receiveBytes(int num, byte* dest);
#endif

#endif
