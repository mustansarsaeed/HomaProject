/*
 * txc1.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: mustansar
 */

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Tic : public cSimpleModule
{
  private:
    simtime_t timeout;
    cMessage *timeoutEvent;
    int seq;  // message sequence number
    cMessage *message;

  public:
    Tic();
    virtual ~Tic();

  protected:
    virtual cMessage *generateNewMessage();
    virtual void sendCopyOf(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tic);

Tic::Tic()
{
    timeoutEvent = nullptr;
}

Tic::~Tic()
{
    // Dispose of dynamically allocated the objects
    cancelAndDelete(timeoutEvent);
}

void Tic::initialize()
{
    timeout = 1.0;
    seq = 0;
    timeoutEvent = new cMessage("timeoutEvent");
    EV << "Sending initial messages\n";
    cMessage *cmsg = new cMessage ("TicTocMessage");
    send(cmsg, "out");
    scheduleAt(simTime()+timeout, timeoutEvent);
}
void Tic::handleMessage(cMessage *msg)
{
    if(msg == timeoutEvent) {
        EV << "Timeout expired, resending message and restarting timer\n";
        sendCopyOf(message);
        scheduleAt(simTime()+timeout, timeoutEvent);
    } else {
        EV << "Received: " << msg->getName() << "\n";
       delete msg;

       EV << "Timer cancelled.\n";
      cancelEvent(timeoutEvent);
      delete message;

      // Ready to send another one.
      message = generateNewMessage();
      sendCopyOf(message);
      scheduleAt(simTime()+timeout, timeoutEvent);
    }
}

void Tic::sendCopyOf(cMessage *msg)
{
    cMessage *copy = (cMessage *)msg->dup();
    send(copy, "out");
}


class Toc : public cSimpleModule
{
  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Toc);

void Toc::handleMessage(cMessage *msg)
{
    EV << "uniform(0, 1) = " << uniform(0, 1) ;
    if (uniform(0, 1) < 0.5) {
        EV << "\"Losing\" message.\n";
        bubble("message lost");  // making animation more informative...
        delete msg;
    }
    else {
        EV << "Sending back same message as acknowledgement.\n";
        send(new cMessage("ack"), "out");
    }
}




cMessage *Tic::generateNewMessage()
{
    // Generate a message with a different name every time.
    char msgname[20];
    sprintf(msgname, "tic-%d", ++seq);
    cMessage *msg = new cMessage(msgname);
    return msg;
}
