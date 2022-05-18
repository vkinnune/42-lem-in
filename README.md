# 42-lem-in
The goal of this project is to find the quickest way to get n ants across the farm.
![Gif](box-220517-2345-01.gif)

In Lem_in, we are given the number of ants, rooms and links to the rooms. There are the start and end rooms, and our goal is to get all the ants from beginning to end in the least amount of time.
<h2>The input:</h2>

```
10          //here are the number of ants
1 0 2       //here is the room names and their x y coordinates
##start
0 2 0
##end
4 2 6
2 4 2
3 4 4
0-1         //room links are here
0-2
2-3
3-4
4-1
0-4
0-2
```

The problem in Lem_in is to find all the different "sets of paths" and find the set suited for the given ant amount. As in our other projects, in Lem_in, it's also a problem where there is no copy and pastes answers, and we had to think about the issue and make a custom solution based on the Edmonds–Karp algorithm.

Only one ant can be in one room at a time, so finding the shortest path using something like Dijkstra's algorithm is not enough. We need to find the max flow of the graph and different "sets of paths" because there can be multiple solutions. After all, some paths can block others from forming.
<h2>The output:</h2>

```
10
1 0 2
##start
0 2 0
##end
4 2 6
2 4 2
3 4 4
0-1
0-2
2-3
3-4
4-1
0-4
0-2

L1-1 L4-2 L5-4 L8-4
L1-4 L2-1 L4-3 L6-4 L9-4
L2-4 L3-1 L4-4 L7-4 L10-4
L3-4
```
