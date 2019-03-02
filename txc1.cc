/*
 * txc1.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: mustansar
 */

#include <string.h>
#include <omnetpp.h>
#include "tictactoe_m.h"
using namespace omnetpp;

class Txc10 : public cSimpleModule
{
private :
    long numSent = 0;
    long numReceived = 0;
protected:
    TicTocMsg * generateMessage();
    virtual void forwardMessage(TicTocMsg *msg);
    virtual void initialize() override;
    virtual void refreshDisplay() const override;
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
        WATCH(numSent);
        WATCH(numReceived);
        TicTocMsg *msg = generateMessage();
        scheduleAt(0.0, msg);
    }
}

void Txc10::refreshDisplay() const{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void Txc10::handleMessage(cMessage *msg)
{
    TicTocMsg *ttmsg = check_and_cast<TicTocMsg *>(msg);

    if (ttmsg->getDestination() == getIndex()) {
        // Message arrived
        int hopcount = ttmsg->getHopCount();
        EV << "Message " << ttmsg << " arrived after " << hopcount << " hops.\n";
        numReceived++;
        delete ttmsg;
        bubble("ARRIVED, starting new one!");

        // Generate another one.
        EV << "Generating another message: ";
        TicTocMsg *newmsg = generateMessage();
        EV << newmsg << endl;
        forwardMessage(newmsg);
        numSent++;
    }
    else {
        // We need to forward the message.
        forwardMessage(ttmsg);
    }
}

void Txc10::forwardMessage(TicTocMsg *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

TicTocMsg *Txc10::generateMessage()
{
    // Produce source and destination addresses.
    int src = getIndex();  // our module index
    int n = getVectorSize();  // module vector size
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    TicTocMsg *msg = new TicTocMsg(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
