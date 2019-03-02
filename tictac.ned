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

simple TxcBase
{
	parameters:
		bool sendMsgOnInit = default(false);
	    int limit = default(5);
	    @display("i=block/routing");
	gates:
		input in;
		output out;
}


simple Tic extends TxcBase
{
    parameters:
        @display("i=,cyan"); // add a default icon
        sendMsgOnInit = true; // whether the module should send out a message on initialization
}

simple Tac extends TxcBase
{
    parameters:
        @display("i=,gold"); // add a default icon
        sendMsgOnInit = true; // whether the module should send out a message on initialization
}

network TicTac2 {
    submodules: 
        tic: Tic;
        tac: Tac;
    connections:
        tic.out --> { delay = 100ms; } --> tac.in;
        tic.in <-- { delay = 100ms; } <-- tac.out;
}