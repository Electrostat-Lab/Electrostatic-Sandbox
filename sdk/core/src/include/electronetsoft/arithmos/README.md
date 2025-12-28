# Arithmos _αριθμός_

Arithmos is a set of APIs that target different taxonomies of algorithms to solve problems through providing _algorithm generic utilities_, and several implementations for the common _abstract data types (adt)_ commonly encountered during solving problems while building commercial applications or participating in problem solving contests.

Arithmos is essentially composed of the following:
- [x] Vector2d Library (Finished).
- [x] Vector3d Library (Partially Finished).
- [x] MatrixNd Library (Partially Finished).
- [ ] Discrete Sets Operations (Conjunctive, Disjunctive, Subtraction, Powersets, De'Morgans formulas).
- [ ] Physics Simulation Library (Collision detection - Force Control - Objects interactions).
- [ ] Statistics Algorithms Library (Present in Java - WIP to port).
- [ ] Differential and Integral Calculus Library.
- [ ] Generic Algorithms Utilities Library.
- [ ] Linear Algorithms Library.
- [ ] Graph Algorithms Library.
- [ ] Memory Algorithms Library.
- [ ] Database Algorithms Library.
- [ ] Cryptology Algorithms Library.

Most of these libraries rely on the _Generic Algorithms Utilities Library_; this was studied as a way to build abstractions using constructs commonly known as "Designation". When designation and ontology are combined, the result is a very powerful combinatoric, that is formulated as _A Set of all possible common constructs among the objects in examination._

> [!NOTE]
>
> _Designation_ is assigning _constructs_ from a _Constructs Set_ to an object > from the _Object Set_, while _Denotation_

## Progress:
* Arithmos Linear Data Structures:
    - ADT (List, Map, Queue, Stack).
    - Concrete Data Structures
        - [x] Contiguous Buffers -> List.
        - [ ] Linked Buffers -> List `(WIP)`.
        - [ ] MemoryPool Buffers -> List.
        - [ ] Doubly Linked Buffers -> Linked Buffers.
        - [ ] Circular Linked Buffers -> Linked Buffers.
        - [ ] Linked Queue Buffers -> Queue (+ Linked Buffers) `(WIP)`.
        - [ ] Contiguous Queue Buffers -> Queue (+ Contiguous Buffers)
        - [ ] MemoryPool Queues -> Queue (+ MemoryPools)
      
* Arithmos Linear Algorithms Utilities:
    - Searching Algorithms.
      - [ ] Linear Searching.
      - [ ] Binary Searching.
      - [ ] Pattern Searching (defines a mathematical function for the search).
      - [ ] Breadth-first Searching.
      - [ ] Depth-first Searching. 
    - Sorting Algorithms.
      - [ ] Shuffle Sorting (or Bubble).
      - [ ] Selection Sorting.
      - [ ] Insertion Sorting.
      - [ ] Merge Sorting.
      - [ ] Quick Sorting.   
    - Hashing Algorithms.
      - [ ] Modular Arithmetics.
    - Un-hashing Algorithms.
    - Switching Algebra Algorithms.
      - [ ] Elementary Bit switching.
      - [ ] Elementary Bit shifting.
      - [ ] Elementary Byte switching.
      - [ ] Elementary Byte shifting.
    - Pattern matching Algorithms.