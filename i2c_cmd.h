/*I2C_Cmd.h
 * Command and poll the subprocessors
 */
#ifdef CMDR
#ifndef I2C_CMD_H
#define I2C_CMD_H

#include "extern.h"

void sendAll(int msgLen, byte* msg)   //Sends the message to all receivers.
{
  byte rcv=0;
  int i;
  Serial.print("Sending HDR: ");
  for (i=0;i<2;++i)
  {
    sprintf(s_buff,"%d ", msg[i]);
    Serial.print(s_buff);
  }
  Serial.print(" ");
  if(msgLen >2)
  {
    Serial.print("BUF: ");
    for(i=2;i<msgLen;++i)
    {
      sprintf(s_buff,"%c ", msg[i]);
      Serial.print(s_buff);
    }
  }
  Serial.print("  LEN: ");
  Serial.println(msgLen);
  

  for (rcv=1;rcv<=NUM_RECV;rcv++)
  {
    Wire.beginTransmission(rcv);
    Wire.write(msg,msgLen);
    Wire.endTransmission();
  }
}

byte askAllCompleteMask( byte mask )
{
  //Until we need more sophisticated responses, let's assume a  bitmask is our ack
  //If all the flags in the mask are set on all the receivers return t else f.
  //This is a little inefficient. The first recvs get queried even  after they're done.
  byte rcv=0;
  Serial.println("Ask COMPL");
  for (rcv=0;rcv<NUM_RECV;rcv++)
  {
    Wire.requestFrom((int)rcv, 1);
    while( Wire.available() )
    {
      if ( ! ( mask & Wire.read() ) ) 
        return false;
    }
  }
  return true;
}

#endif
#endif
