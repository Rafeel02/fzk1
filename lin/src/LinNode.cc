//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "LinNode.h"

Define_Module(LinNode)

LinNode::LinNode() {
}

LinNode::~LinNode() {
}

void LinNode::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
    }
    else {
        receiveFrame(msg);
    }
}

void LinNode::handleSelfMessage(cMessage *msg) {
    //supposed to be overridden by master and slave classes
}

void LinNode::receiveFrame(cMessage *frame) {
    //supposed to be overridden by master and slave classes
    delete frame;
}


void LinNode::sendFrame(cMessage* msg) {
    int n = gateSize("gate");
    if (n==1){
        send(msg, "gate$o");
        return;
    }
    send(msg, "gate$o", 0);
    for (int i = 1; i < n; i++) {
        auto* newMsg = msg->dup();
        send(newMsg, "gate$o", i);
    }
}

FRAME_TYPE LinNode::getFrameType(int messageId) const {
    if (isUnconditional(messageId)) {
        return UNCONDITIONAL_FRAME;
    }
    else {
        if (isEventTriggered(messageId)) {
            return EVENT_TRIGGERED_FRAME;
        }
        else {
            if (isSporadic(messageId)) {
                return SPORADIC_FRAME;
            }
            else {
                return UNKNOWN;
            }
        }
    }
}

std::list<int> LinNode::getEventTriggeredIds(int messageId) const {

         std::list<int> ids;

         if (!isEventTriggered(messageId)) {
             ASSERT2(false, "Bad programmer! This should never happen!");
         }

         /* for simplicity, we assume that each event triggered message
          * regards four unconditional messages, so we map each event
          * triggered id with four unconditional ids
          */

         messageId -= FIRST_EVENT_TRIGGERED;
         messageId *= UNCONDITIONALS_PER_EVENT_TRIGGERED;
         for (int i = 0; i < UNCONDITIONALS_PER_EVENT_TRIGGERED; i++){
             ids.push_back(messageId + i);
         }
         return ids;

     }

bool LinNode::isResponsibleForEventTriggered(int messageId) const {

    if (!isEventTriggered(messageId)) {
        return false;
    }

    messageId -= FIRST_EVENT_TRIGGERED;
    messageId *= UNCONDITIONALS_PER_EVENT_TRIGGERED;

    //check whether the ECU id is within the range of messages that the event
    //triggered message regards
    if (getIndex() >= messageId && getIndex() < messageId + UNCONDITIONALS_PER_EVENT_TRIGGERED) {
       return true;
    }
    return false;
}
