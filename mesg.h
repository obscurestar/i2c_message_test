#ifndef MESG_H
#define MESG_H
#include "extern.h"

class Mesg
{
  public:
#ifdef CMDR
    virtual void send() = 0;
#else
    virtual void receive(int num_bytes) = 0;
#endif
    virtual void query() = 0;
};
#endif
