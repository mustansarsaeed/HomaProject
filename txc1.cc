/*
 * txc1.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: mustansar
 */

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc10 : public cSimpleModule
{
  protected:
    virtual void forwardMessage(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc10);
//
//Txc10::Txc10()
//{
////    timeoutEvent = nullptr;
//}
//
//Txc10::~Txc10()
//{
//    // Dispose of dynamically allocated the objects
////    cancelAndDelete(timeoutEvent);
//}

void Txc10::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}
void Txc10::handleMessage(cMessage *msg)
    {
        if (getIndex() == 3) {
            // Message arrived.
            EV << "Message " << msg << " arrived.\n";
            delete msg;
        }
        else {
            // We need to forward the message.
            forwardMessage(msg);
        }
}

void Txc10::forwardMessage(cMessage *msg)
    {
        // In this example, we just pick a random gate to send it on.
        // We draw a random number between 0 and the size of gate `out[]'.
        int n = gateSize("out");
        int k = intuniform(0, n-1);

        EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
        send(msg, "out", k);
    }
