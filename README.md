# Computer-Architecture-PA-5

**This was the fifth project assigned in Rutgers 01:198:211 (Computer Architecture).

In this project, I experimented with different cache designs, and saw how they impact the ability for caches to create an illusion of fast access from the CPU to main memory. I also wrote programs in a way that maximizes spatial and temporal locality, so that caches can further improve program performance. Below you can find a description of each folder of the programming assignment.

- fullyAssociative: Simulating a fully associative cache with FIFO cache replacement policy
  - Simulates the behavior of a fully associative CPU cache.
- directMapped: Simulating a direct-mapped cache
  - Modifies the previous simulator so that it simulates a direct-mapped cache.
- setAssociative: Simulating a 4-way set-associative cache
  - Modifies the previous simulator so that it simulates a set-associative cache.
- cacheBlocking: Optimizing matrix multiplication using cache blocking
  - Improves a program that does matrix multiplication so that it works better with a cache.
- cacheOblivous: Optimizing matrix transpose for better performance with a cache
  - Improves a program that does matrix transpose so that it works better with a cache.
