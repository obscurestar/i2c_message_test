/*I2C_rcv.h
 * Listen for orders and requests from the commander.
 */
#ifdef RCVR
#ifndef I2C_RCV_H
#define I2C_RCV_H

#include <Wire.h>
#include "extern.h"

int receiveBytes(int num, byte* dest)
{
  int i=0;
  byte c;
  Serial.println("-------");
  while( Wire.available() )
  {
    if (i >= num) break;
    c = Wire.read();
    Serial.print(c);
    dest[i] = (byte)c;
    ++i;
  }
  Serial.println("\n------");
  return i;
}

/*Function/Event call****************************************************************************/
void RecvCallbackFunc(int Press)
{
  HEADER hdr;
  int x = receiveBytes(sizeof(hdr), (byte *)&hdr);

  sprintf(s_buff,"RCVD HDR LEN: %d MSG_ID: %d BOD_SZ: %d", x, hdr.id, hdr.num);
  Serial.println(s_buff);
  
  mesg[ hdr.id ]->receive(hdr.num);
  msg_id = hdr.id;
}


void ReqCallbackFunc()
{
  /*This function gets called as an interrupt whenever the commander 
   * wants status. 
   */
   /*Until the code is more sophisticated, this is a simple request 
    * for a the loop_status global variable. See enum for mask attributes.
    */
  Wire.write(1);
  //TODO might want to clear some status here? 
}
#endif
#endif
