# 42-lem-in
Lem-in is an algorithmic project focusing on graphs. The goal is to reproduce the behaviours of an ant farm manager.

Our goal is to get the most ants from the source to the sink in the least time possible. Two ants cannot be in the same room at the same time expect the starting and ending nodes. The input data tells us the number of ants, nodes, and edges.

I use a variation of Edmond-Karp’s with the breadth-first search algorithm. With 4000 nodes and 8000 edges the solution generates in 2-3 seconds. For less than that it's almost instant.

## Usage
Run `make`. Works with Linux and MacOS.

Run with `./lem-in < Filename`.

A collection of maps are found in `/maps`.

For the visualizer you need Raylib installed. To run with visualizer first run the `make` command inside `/lem-in-visualizer` folder. After that run `./lem-in < Filename | ./lem-in-visualizer/a.out`.

![GIF](gif.gif)
