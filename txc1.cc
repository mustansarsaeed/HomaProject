/*
 * txc1.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: mustansar
 */

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class TxcBase : public cSimpleModule {
    private:
        int counter;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *cmsg) override;
};

Define_Module(TxcBase);

void TxcBase::initialize() {
    counter = par("limit");
    WATCH(counter);
    if(par("sendMsgOnInit").boolValue() == true) {
        cMessage* cmsg = new cMessage("Hello Toc");
        EV << "Sending initial message\n";
        send(cmsg, "out");
    }
}

void TxcBase::handleMessage(cMessage* cmsg) {
    counter--;
    if(counter == 0) {
        EV << cmsg->getName() << "'s counter reached zero\n";
        delete cmsg;
    } else {
        EV << getName() << "'s counter is " << counter << ", sending back message\n";
        send(cmsg, "out");
    }

}
