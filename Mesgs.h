/*Mesg.h
 * A generic message sending class for defined message types.
 */
 
#ifndef MESGS_H
#define MESGS_H
#include "extern.h"

#ifdef CMDR
#include "i2c_cmd.h"
#else
#include "i2c_rcv.h"
#endif

class mesg0 : public Mesg
{
  public:
#ifdef CMDR
    void send()
    {
      HEADER h;
      h.id = 0;
      h.num = 0;

      Serial.println("MSG0 send");
      sendAll( sizeof(HEADER), (byte *)&h );  //Notify all the receivers of the change.
    };
#else
    void receive(int num_bytes) {
      Serial.println("MSG0: No Dat");
    };
#endif
    void query() {};
 };

class mesg1 : public Mesg
{
  private:
    struct BODY {
      char c;
    }; // __attribute__((packed)); 
    
    struct MSG {
      HEADER h;
      struct BODY b;
    }; // __attribute__((packed));
  public:
#ifdef CMDR
    void send()
    {
      struct MSG msg;
      msg.h.id = 1;
      msg.h.num = sizeof(struct BODY);
      msg.b.c = 'a';

      Serial.println("MSG1 send 'a'");
      
      sendAll( sizeof(struct MSG), (byte *)&msg );  //Notify all the receivers of the change.
    };
#else
    void receive(int num_bytes)
    {
      struct BODY b;
      if (num_bytes != sizeof(b))
      {
        Serial.println("MSG1 ERR");
      }
      int c=receiveBytes(num_bytes, (char *)&b);
      sprintf(s_buff, "MSG1 LEN: %d BUF_SZ: %d RCV_LEN: %d CHAR: %c", num_bytes, sizeof(b), c, b.c);
      Serial.println(s_buff);
    }
#endif
    void query() {};
 };


class mesg2 : public Mesg
{
  private:
    struct BODY {
      char c[10];
    }; // __attribute__((packed)); 
    
    struct MSG {
      HEADER h;
      struct BODY b;
    }; // __attribute__((packed));
  public:
#ifdef CMDR
    void send()
    {
      struct MSG msg;
      msg.h.id = 2;
      msg.h.num = sizeof(struct BODY);
      char c[]="Testing.\n";
      strcpy(msg.b.c,c);

      Serial.println("MSG2 send Testing");
      sendAll( sizeof(struct MSG), (byte *)&msg );  //Notify all the receivers of the change.
    };
#else
    void receive(int num_bytes)
    {
      struct BODY b;
      if (num_bytes != sizeof(struct BODY))
      {
        Serial.println("MSG2 ERR");
      }
      int c = receiveBytes(num_bytes, (char *)&b);
      sprintf(s_buff, "MSG2 Body_LEN: %d msg_LEN: %d rcv_LEN: %d Rcv_STR: %s", sizeof(struct BODY), num_bytes, c, b.c);
      Serial.println(s_buff);
    }
#endif
    void query() {};
 };
#endif
