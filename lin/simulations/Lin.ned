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

package lin.simulations;

import lin.LinMaster;
import lin.LinSlave;


//ned defining the LIN network
network Lin
{
    parameters:
        //number of slaves in the LIN network
        int numSlaves = 50;

        @display("bgb=730,367");
    submodules:
        //todo: place the slaves and master node. define the number of gates for the master
       master: LinMaster;
       slaves[numSlaves] : LinSlave;
    connections:
        //todo: connect each slave with the master
        for i=0..numSlaves-1 {
           master.gate[i] <--> { delay = 100us; } <--> slaves[i].gate;            
        }
}
