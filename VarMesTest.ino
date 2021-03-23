//#define CMDR
#ifndef CMDR
#define RCVR
#endif

#include <Wire.h> //Arduino library that enables I2C functionality
#include "Mesgs.h"

#ifdef CMDR
#include "i2c_cmd.h"
#else
#include "i2c_rcv.h"
byte RCVR_ID = 1; //Change this ID for each reciever when uploading.
#endif 

//Globals
const byte NUM_RECV=1;      //Number of receivers to address
const int S_BUFF_LEN=120;    //Serial buffer length

byte msg_id=0;
char s_buff[S_BUFF_LEN];    //Serial buffer

Mesg* mesg[]  = { new mesg0(), new mesg1(), new mesg2() };
byte MMAX = 3;

/*Setup loop******************************************************/
void setup() 
{
  const int SDI = 2;          //Serial PIN Red wire (not the red 5v wire) 
  const int CKI = 3;          //Clock PIN Green wire

  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);

  Serial.begin(19200);

#ifdef CMDR
  Wire.begin(); // join I2C bus (address here is optional for master)
  
  Serial.println("CMDR");
#else
  Wire.begin(RCVR_ID);                 // Join I2C bus as a listener
  Wire.onReceive(RecvCallbackFunc);    // The commander commands us
  Wire.onRequest(ReqCallbackFunc);     // The commander asks us to report.
  
  sprintf(s_buff,"RCVR %d",RCVR_ID);
  Serial.println(s_buff);
#endif
}

/*Main loop****************************************************/
void loop() 
{
  msg_id = msg_id % MMAX;


#ifdef CMDR
  mesg[ msg_id ]->send();  
  mesg [ msg_id ]->query();
  if (msg_id == (MMAX-1)) delay(5000);
#endif
  
  msg_id ++;
}
