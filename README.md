The Six Degrees of Kevin Bacon game where any actor can be connected to Bacon through movies within 6 connections. It uses an
actor as a node and connects two actors with an edge if they were in the same movie. This is found by adding actors to the cast
of each Movie object necessary. 

Breadth First Search is used to find an unweighted path and Dijkstra's is used to find a weighted path from any actor to Kevin
Bacon. A pathfinder program will output the path from Kevin Bacon to another actor.

Actorconnections uses BFS or Union Find to find what year two actors become connected. The Six Degrees concept can also apply
to regular people. For example, it can find a path from one Facebook user to another throught their mutual friends.
