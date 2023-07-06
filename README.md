# Optimalisatie_Project - Tank game
Jesse de Vries - 06-06-2023

## Installation
The provided thread pool as been replaces with [BSThreadPool](https://github.com/bshoshany/thread-pool). Using this threadpool speeds the application up with around 1.0<br>
To install [BSThreadPool](https://github.com/bshoshany/thread-pool) use the following steps:
1. Install [Vcpkg](https://github.com/microsoft/vcpkg)
2. Install BSThreadPool using the following command: `vcpkg install thread-pool`

## Optimization

### Grid
I've added a grid to use this for the neighbour function. The grid has been implemented in the following places:
- Rocket explosions
- Laser beam updates
- Tank nudging

### Changed Breadth First Search to Dijkstra's
The existing BFS algorithm isn't optimal. This is because the amount of nodes in the first step can have a huge amount.
This is because the BFS algorithm doesn't take the distance into account. This can be solved by using Dijkstra's algorithm.
This algorithm takes the distance into account. This means that the algorithm will always find the shortest path.

When implementing the A* algorithm I've noticed that tanks sometimes make weird movements. After changing to Dijkstra's algorithm this problem was solved.
Considering the size of the program and its fast enough performance I've decided to not implement the A* algorithm but to use Dijkstra's algorithm.
I've also attempted to use `Jump point search (JPS)` but failed to implement it due to the code base setup.

### Sorting
The default sorting algorithm was made using insertion sort. This algorithm has a time complexity of O(n^2) when we give it a descending ordered list. This can be improved by using a faster sorting algorithm.
I've tested the following algorithms:
- Bucket Sort
- Count Sort
- Radix Sort
- HeapSort

The fastest algorithm was HeapSort. This algorithm has a time complexity of O(n log n). This is a huge improvement over the insertion sort algorithm.

### Thread Pool
The provided thread pool has been replaced by BSThreadPool. This thread pool is faster than the provided thread pool. This is because the provided thread pool uses a mutex to lock the queue. This means that only one thread can access the queue at a time. BSThreadPool uses a lock free queue. This means that multiple threads can access the queue at the same time. This speeds up the application with around 1.0.

### Result
![tankgame-speedup](https://github.com/NHLStenden-HBO-ICT-SE/tank-opdracht-Jessedev1/assets/60600868/774a1453-016f-4acd-82dd-0a4fe4dd47d7)
