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

#include "LinSlave.h"

Define_Module(LinSlave)

LinSlave::LinSlave()
{}

LinSlave::~LinSlave()
{}

void LinSlave::receiveFrame(cMessage *msg) {
    /*
     * todo: handle received Frames, send responses
     */
    /*
         * check if directly addressed (with getIndex)
         * if directly addressed:
         *  if unconditional:
         *      sendLinResponse()
         *  else: // sporadic:
         *      getResponse()
         *      sendLinResponse()
         *  return
         *
         *  if(isResponsibleForEventTriggered(messageId)):
         *      ...
         *
         */
        // Handle the request based on the message type
    auto requestFrame = dynamic_cast<LinRequestFrame*>(msg);

    if(requestFrame && (getIndex() == requestFrame->getMessageId() || (isResponsibleForEventTriggered(requestFrame->getMessageId()) && hasUpdatedData()))){
         sendLinResponse(requestFrame->getMessageId(), getResponse());
    }
}



void LinSlave::sendLinResponse(int messageId, int response) {
    std::cout << simTime().ustr() << ": Slave " << getIndex() << " sends response on " << messageId << " with " << response << std::endl;
    LinResponseFrame* frame = new LinResponseFrame();
    frame->setMessageId(messageId);
    frame->setResponse(response);

    sendFrame(frame);
}

int LinSlave::getResponse() const {
    return getFrameType(getIndex()) != SPORADIC_FRAME ? 42 : omnetpp::intuniform(getRNG(2), 0, 1);
}

bool LinSlave::hasUpdatedData() const {
    return omnetpp::intuniform(getRNG(3), 0, 1);
}
