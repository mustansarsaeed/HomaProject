simple Txc10
{
    parameters:
        @display("i=block/routing");
        @signal[arrival](type="long");
	    @statistic[hopCount](title="hop count"; source="arrival"; record=vector,stats; interpolationmode=none);
    gates:
        inout gate[];  // declare in[] and out[] to be vector gates
}



network Tictoc10
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        
    submodules:
	        tic[6]: Txc10;
	    connections:
	        tic[0].gate++ <--> Channel <--> tic[1].gate++;
	        tic[1].gate++ <--> Channel <--> tic[2].gate++;
	        tic[1].gate++ <--> Channel <--> tic[4].gate++;
	        tic[3].gate++ <--> Channel <--> tic[4].gate++;
	        tic[4].gate++ <--> Channel <--> tic[5].gate++;
}
