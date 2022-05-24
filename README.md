# 42-lem-in
Lem-in is an algorithmic project focusing on graphs. The goal is to reproduce the behaviours of an ant farm manager.

I built a program that takes in the number of ants, and the graph nodes and edges with the source and the sink defined. The program outputs the instructions for each ant to get from the source to the sink in the least amount of time.

## Usage
Run `make`. Works with Linux and MacOS.

Run with `./lem-in < Filename`.

A collection of maps are found in `/maps`.

For the visualizer you need Raylib installed. To run with visualizer first run the `make` command inside `/lem-in-visualizer` folder. After that run `./lem-in < Filename | ./lem-in-visualizer/a.out`.

![GIF](gif.gif)
