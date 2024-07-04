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

#ifndef LINNODE_H_
#define LINNODE_H_

#include <omnetpp.h>
#include "LinRequestFrame_m.h"
#include "LinResponseFrame_m.h"

using namespace omnetpp;

//ranges for message ids
/**
 * 40 unconditional frames. For simplicity, message #i is
 * handled by ECU #i
 */
#define FIRST_UNCONDITIONAL     0
#define LAST_UNCONDITIONAL      39

/**
 * 10 sporadic frames
 */
#define FIRST_SPORADIC          40
#define LAST_SPORADIC           49

/**
 * 10 event triggered frames: for simplicity, 1 for 4 ECUs.
 * For example, E.T. frame #50, is for ECUs #0, 1, 2 and 3
 * E.T. frame #51 is for ECUs #4, 5, 6 and 7 and so on
 */
#define UNCONDITIONALS_PER_EVENT_TRIGGERED 4
#define FIRST_EVENT_TRIGGERED   50
#define LAST_EVENT_TRIGGERED    59


enum FRAME_TYPE {
    UNCONDITIONAL_FRAME,
    EVENT_TRIGGERED_FRAME,
    SPORADIC_FRAME,
    UNKNOWN
};

class LinNode: public cSimpleModule {
public:
    LinNode();
    virtual ~LinNode();

protected:
    virtual void initialize() {};
    virtual void handleMessage(cMessage *msg);
    virtual void handleSelfMessage(cMessage *msg);
    virtual void finish() {};

    /**
     * Invoked when a LIN frame is received
     */
    virtual void receiveFrame(cMessage *msg);


protected:
    /**
     * Internally used to send a frame via the port(s).
     */
    void sendFrame(cMessage* msg);

    /**
      * Given the id of an event triggered message, returns
      * the set of message ids that the event triggered message
      * regards. Basically, given the id, the list contains
      * the ECUs that might reply.
      */
     std::list<int> getEventTriggeredIds(int messageId) const;

     /**
       * Given the id of an event triggered message, returns if
       * the LinNode is responsible for the event and might have
       * to send updated data.
       */
     bool isResponsibleForEventTriggered(int messageId) const;

     /**
       * Tells the type of the give message id (unconditional, event
       * triggered, or sporadic)
       */
      FRAME_TYPE getFrameType(int messageId) const;

private:
    /**
     * Tells whether the given message id is an unconditional frame
     */
    inline bool isUnconditional(int messageId) const {return (messageId >= FIRST_UNCONDITIONAL && messageId <= LAST_UNCONDITIONAL);}
    /**
     * Tells whether the given message id is an event triggered frame
     */
    inline bool isEventTriggered(int messageId) const {return (messageId >= FIRST_EVENT_TRIGGERED && messageId <= LAST_EVENT_TRIGGERED);}
    /**
     * Tells whether the given message id is a sporadic frame
     */
    inline bool isSporadic(int messageId) const { return (messageId >= FIRST_SPORADIC && messageId <= LAST_SPORADIC);}

};

#endif /* LINNODE_H_ */
