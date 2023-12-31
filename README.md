# MIT 6.5210/18.415: Advanced Algorithms

- Course Website: https://6.5210.csail.mit.edu/

- Materials: https://6.5210.csail.mit.edu/materials.html
- Problem Sets: https://6.5210.csail.mit.edu/psets.html

## Course

- [Lecture 01: Fibonacci Heaps](https://www.youtube.com/watch?v=rnwf0dDGNCM&t=879s) :white_check_mark: 2023/12/25

- [Lecture 02: Fibonacci Heap and Persistent Data Structures](https://www.youtube.com/watch?v=TB3Y308PCrA) :white_check_mark:2023/12/30

- [Lecture 03: Persistent Data Structures](https://www.youtube.com/watch?v=nofifCFuPiQ) :white_check_mark:2023/12/30

## Lecture 1:  Fibonacci Heaps

- Minimum Spanning Tree (MST)
  - Overall tutorial (Chinese): [OI-Wiki](https://oi-wiki.org/graph/mst/)
  - Online Judge & Data Format (Chinese): [LG P3366](https://www.luogu.com.cn/problem/P3366)
  - Prim: select "nearest" vertex by heap
    - [with STL priority_queue](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-stl.cpp)
      - $O((n+m)\log{m})$, since there's no `decrease`, heap's maximum size is $m$, with many "out-dated" vertexes
      - [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue): document for STL  priority queues
    - [with pbds priority_queue (thin_heap_tag)](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-pbds.cpp)
      - $O(n\log{n}+m)$, $O(1)$ for `push` / `decrease_key`,  $\Theta(\log{n})$ for `pop`
      - [Priority-Queue Design](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_design.html): document for pbds priority queues
      - [Priority-Queue Performance Tests](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html):  performance tests for difference priority queues
    - [with hand-written binary_heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-binary.cpp)
      - $O((n+m)\log{n})$, $O(\log{n})$ for `push` / `decrease_key` / `pop`
    - [with hand-written d-ary heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-dheap.cpp)
      - $O(m\log_{\frac{m}{n}}{n})$, set $d=\frac{m}{n}$ to balance `push` / `decrease_key` $O(m\times \log_{d}{n})$ and `pop` $O(n\times d\log_{d}{n})$
    - [with hand-written binomial-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-binomial.cpp)
      - $O((n+m)\log{n})$, $O(1)$ for `push` ,  $O(\log{n})$ for `pop` / `decrease_key`
    - [with hand-written Fibonacci-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-fibonacci.cpp)
      - $O(n\log{n}+m)$, $O(1)$ for `push` / `decrease_key`,  $\Theta(\log{n})$ for `pop`
  - [Kruskal](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/kruskal.cpp): select "shortest" edge by DSU
    - $O(m\log{m})$, sorting all edges by `std::sort`
    - [Disjoint Sets Union](https://codeforces.com/edu/course/2/lesson/7): Theory & Practice by [Codeforces ITMO Academy: pilot course](https://codeforces.com/edu/course/2)
      - $O(m\alpha(n))$, DSU `search` with *Union-By-Rank* and *path compression*
      - [code](https://github.com/SkqLiao/codeforces-edu): solution code for practice of [Step 1](https://codeforces.com/edu/course/2/lesson/7/1/practice), [Step 2](https://codeforces.com/edu/course/2/lesson/7/2/practice), [Step 3](https://codeforces.com/edu/course/2/lesson/7/3/practice)
  - [Borůvka](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/boruvka.cpp): connect components with "shortest" edges by DSU
    - $O(m\log{n})$, maximum $O(\log{n})$ iterations to connect all components
  - Ramachandran: [An Optimal Minimum Spanning Tree Algorithm](https://web.eecs.umich.edu/~pettie/papers/jacm-optmsf.pdf)
    - $O(m)$, but runtime not clear
- Amortized Analysis
  - *Stanford CS166* [**Amortized Analysis**](https://web.stanford.edu/class/cs166/lectures/06/Slides06.pdf)
- Binomial Heap
  - Materials:
    - *Stanford CS166* [**Binomial Heaps**](https://web.stanford.edu/class/cs166/lectures/07/Slides07.pdf)
    - *Lecture Slides for Algorithm Design* [**Data Structures II** (*binary and binomial heaps*)](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/BinomialHeaps.pdf)
  - maintain $O(\log{n})$ different order *Binomial Trees*
  - $\Phi(H)=\text{trees}(H)$
- Fibonacci Heap
  - Optimized from *lazy binomial heap*
  - Lectures:
    - *Stanford CS166* [**Fibonacci Heaps**](https://web.stanford.edu/class/cs166/lectures/08/Slides08.pdf)
    - *Lecture Slides for Algorithm Design* [**Data Structures III** (*Fibonacci heaps*)](https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/FibonacciHeaps.pdf)
  - $\Phi(H)=\text{trees}(H)+2\times \text{marks}(H)$
  - Why "Fibonacci" heap?
    - *Maximally-Damaged Tree* of order $k$ has at least $F_{k+2}$ nodes
    - $F_k=\Theta(\varphi^k)$, the number of nodes in a tree grows exponentially, but based on $\varphi(\approx 1.61)$, not $2$
  - Runtime Performance: quite slow, has huge constant factor for operations
    - huge memory requirement (4 pointers to parent/child/siblings + 1 bit for mark + 1 integar for order extra per node)
    - poor locality for caching (using pointers not array)

- Summary

| Operation | Binary heap  | D-ary heap        | Binomial heap(lazy) | Fibonacci heap |
| --------- | ------------ | ----------------- | ------------------- | -------------- |
| push      | $O(\log(n))$ | $O(d\log_{d}{n})$ | $O(1)$              | $O(1)$         |
| pop       | $O(\log(n))$ | $O(d\log_{d}{n})$ | $O(\log{n})$*       | $O(\log{n})$*  |
| top       | $O(1)$       | $O(1)$            | $O(1)$              | $O(1)$         |
| decrease  | $O(\log(n))$ | $O(\log_d{n})$    | $O(\log{n})$        | $O(1)$*        |
| merge     | $O(n)$       | $O(n)$            | $O(1)$              | $O(1)$         |

## Lecture 2: Persistent Data Structures

- Lectures:
  - [OI Wiki(Chinese)](https://oi-wiki.org/ds/persistent/)
  - *Collège de France* [**Persistent data structures**](https://xavierleroy.org/CdF/2022-2023/)

- persistent array (using segment tree)
  - $O(\log n)$ space & time per operation (query & modify)
  - generator: [gen.cpp](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/gen.cpp)
    - task same as [LG P3919](https://www.luogu.com.cn/problem/P3919) (Chinese)
    - sample [input.txt](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/in.txt) [output.txt](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/out.txt)
  - C++ version: [arrary.cpp](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/array.cpp), ~0.7s for sample input (-O2)
    - based on `std::vector`, super fast
  - Haskell version: [array-vec.hs](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/array-vec.hs) / [array-seq.hs](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/src/array-seq.hs), ~ 6.1s / 7.6s for sample input (-O2)
      - based on `Data.Vector.Mutable` / `Data.Sequence`, really slow...
      - using Cabal [lec2.cabal](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec2/lec2.cabal) to compile & run
