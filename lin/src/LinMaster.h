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

#ifndef LINMASTER_H_
#define LINMASTER_H_

#include "LinNode.h"
#include <queue>

class LinMaster: public LinNode {
public:
    LinMaster();
    virtual ~LinMaster();

    /*
     * todo: declare needed member variables
     */
    int frameCounter = 0;
    int lastEventId = 0;
    int responsesOnEvent = 0;
    std::list<int> uncon_queue;
    cMessage* sendNextFrame = nullptr;
    cMessage* checkCollision = nullptr;

protected:

    /* This is a message to simulate some kind of system dynamics.
     * The master changes the need for sporadic messages every now and then
     * using this selfmsg.
     */
    cMessage* changeSporadic = nullptr;

    // This boolean value holds the information whether a sporadic message should be sent.
    bool needSporadic;

    virtual void initialize();
    virtual void handleSelfMessage(cMessage *msg);
    virtual void receiveFrame(cMessage *msg);
    virtual void finish();

private:
    /**
     * Generate a random message id for a provided frame type.
     */
    int getRandomMessageId(FRAME_TYPE frameType) const;

    /**
     * Send LIN request message with the given id.
     */
    void sendLinRequest(int messageId);

    /* The test method is called after your simulation completed.
     * If any of the tests fail, it will try to provide you with
     * a hint, what went wrong.
     */
    void test() const;

    // A vector for recording the message IDs at the start of the simulation, to perform later tests.
    std::vector<int> testRecording0;
    // A vector for recording the message IDs in the middle of the simulation, to perform later tests.
    std::vector<int> testRecording1;
    // A vector for recording the total amount of send messages, to perform later tests.
    std::vector<int> testSent = {0, 0, 0};
};

#endif /* LINMASTER_H_ */
