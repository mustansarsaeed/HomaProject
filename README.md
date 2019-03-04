# HomaProject
This repository provides the progress of HomaSimulation project. There are different branches for in-progress development.

* master 
	- This is the latest code merged from the **develop** branch
* MultipleNodeNetwork
	- This provides the simple messaging network containing multiple nodes. 
	- It shows multiple hop counts to reach at the destination and it also creates a channel between the noders
* NetworkStats
	- This branch was created to show the simulations of the network created in branch **MultipleNodeNetwork**
	- It collects the stats of hops count by emitting signals. 
	- It shows the stats of different operations using Vector and Scalar values
	- It does the experimentation with Line, Bar, Dotted Line etc graphs with Data sets created using Vectors
	
	**Mean Hop Count**
	- ![Mean Hop Count](/MeanHopcount.png)
	
	**Dotted Line Plots for 100 intermediate nodes based on Vector values**
	- ![Dotted Line Plots for 100 intermediate nodes based on Vector values](/LinePlot-Hopcount.png)
