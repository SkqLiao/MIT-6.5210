# MIT 6.5210/18.415: Advanced Algorithms

- Course Website: https://6.5210.csail.mit.edu/

- Materials: https://6.5210.csail.mit.edu/materials.html
- Problem Sets: https://6.5210.csail.mit.edu/psets.html

## Course

- [Lecture 01: Fibonacci Heaps](https://www.youtube.com/watch?v=rnwf0dDGNCM&t=879s) :white_check_mark: 2023/12/25

- [Lecture 02: Fibonacci Heap and Persistent Data Structures](https://www.youtube.com/watch?v=TB3Y308PCrA) :white_check_mark:2023/12/30

- [Lecture 03: Persistent Data Structures](https://www.youtube.com/watch?v=nofifCFuPiQ) :white_check_mark:2023/12/30

- [Lecture 04: Splay Trees](https://youtu.be/56AGGEkdA2g) :white_check_mark:2024/02/06

- [Lecture 05: Splay Trees Continued and Buckets](https://www.youtube.com/watch?v=HCQJfTyMwi8) :white_check_mark:2024/02/07

## Lecture 1-2:  Fibonacci Heaps

- Minimum Spanning Tree (MST)
  - Overall tutorial (Chinese): [OI-Wiki](https://oi-wiki.org/graph/mst/)
  - Online Judge & Data Format (Chinese): [LG P3366](https://www.luogu.com.cn/problem/P3366)
  - Prim: select "nearest" vertex by heap
    - [with STL priority_queue](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-stl.cpp)
      - $O((n+m)\log{m})$, since there's no `decrease`, heap's maximum size is $m$, with many "out-dated" vertexes
      - [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue): document for STL  priority queues
    - [with pbds priority_queue (thin_heap_tag)](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-pbds.cpp)
      - $O(n\log{n}+m)$, $O(1)$ for `push` / `decrease_key`,  $\Theta(\log{n})$ for `pop`
      - [Priority-Queue Design](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_design.html): document for pbds priority queues
      - [Priority-Queue Performance Tests](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html):  performance tests for difference priority queues
    - [with hand-written binary_heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-binary.cpp)
      - $O((n+m)\log{n})$, $O(\log{n})$ for `push` / `decrease_key` / `pop`
    - [with hand-written d-ary heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-dheap.cpp)
      - $O(m\log_{\frac{m}{n}}{n})$, set $d=\frac{m}{n}$ to balance `push` / `decrease_key` $O(m\times \log_{d}{n})$ and `pop` $O(n\times d\log_{d}{n})$
    - [with hand-written binomial-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-binomial.cpp)
      - $O((n+m)\log{n})$, $O(1)$ for `push` ,  $O(\log{n})$ for `pop` / `decrease_key`
    - [with hand-written Fibonacci-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/prim-fibonacci.cpp)
      - $O(n\log{n}+m)$, $O(1)$ for `push` / `decrease_key`,  $\Theta(\log{n})$ for `pop`
  - [Kruskal](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/kruskal.cpp): select "shortest" edge by DSU
    - $O(m\log{m})$, sorting all edges by `std::sort`
    - [Disjoint Sets Union](https://codeforces.com/edu/course/2/lesson/7): Theory & Practice by [Codeforces ITMO Academy: pilot course](https://codeforces.com/edu/course/2)
      - $O(m\alpha(n))$, DSU `search` with *Union-By-Rank* and *path compression*
      - [code](https://github.com/SkqLiao/codeforces-edu): solution code for practice of [Step 1](https://codeforces.com/edu/course/2/lesson/7/1/practice), [Step 2](https://codeforces.com/edu/course/2/lesson/7/2/practice), [Step 3](https://codeforces.com/edu/course/2/lesson/7/3/practice)
  - [Borůvka](https://github.com/SkqLiao/MIT-6.5210/blob/main/fibonacci-heap/boruvka.cpp): connect components with "shortest" edges by DSU
    - $O(m\log{n})$, maximum $O(\log{n})$ iterations to connect all components
  - Ramachandran: [An Optimal Minimum Spanning Tree Algorithm](https://web.eecs.umich.edu/~pettie/papers/jacm-optmsf.pdf)
    - $O(m)$, but runtime not clear
- Amortized Analysis
  - *Stanford CS166* [**Amortized Analysis**](https://web.stanford.edu/class/cs166/lectures/06/Slides06.pdf)
- Binomial Heap
  - Materials
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

## Lecture 2-3: Persistent Data Structures

- Lectures
  - [OI Wiki (Chinese)](https://oi-wiki.org/ds/persistent/)
  - *Collège de France* [**Persistent data structures**](https://xavierleroy.org/CdF/2022-2023/)
- Persistent array (using segment tree)
  - $O(\log n)$ space & time per operation (query & modify)
  - generator: [gen.cpp](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/gen.cpp)
    - task same as [LG P3919](https://www.luogu.com.cn/problem/P3919) (Chinese)
    - sample [input.txt](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/in.txt) [output.txt](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/out.txt)
  - C++ version: [array.cpp](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/array.cpp), ~0.7s for sample input (-O2)
    - based on `std::vector`, super fast
  - Haskell version: [array-vec.hs](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/array-vec.hs) / [array-seq.hs](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/src/array-seq.hs), ~ 6.1s / 7.6s for sample input (-O2)
      - based on `Data.Vector.Mutable` / `Data.Sequence`, really slow...
      - using Cabal [lec2.cabal](https://github.com/SkqLiao/MIT-6.5210/blob/main/persistent-ds/lec2.cabal) to compile & run

## Lecture 4-5: Splay Trees

- Lectures
  - [OI Wiki (Chinese)](https://oi-wiki.org/ds/splay/)
- Analysis
  - **Potential** $\Phi=\sum{r(x)}$
    - Weight $w(x)$
    - Size $s(x)=\sum_{y\in \text{subtree}(x)}{w(y)}$
    - Rank $r(x)=\log{s(x)}$
  - **Access Lemma**
    - Amortized time to splay a node $x$ given root $t$ is at most $3(r(t) − r(x)) + 1 = O(\log(s(t)/s(x)))$
  - Total real cost for $m$ operations
    - $O(m \log n) − (\Phi_{m} − \Phi_{0}) = O(m \log n) + \Phi_{0} − \Phi_{m}$
    - $\Phi_0 − \Phi_m \leq n \log W − \sum{x w_x} = \sum{x\log W/w_i}$
  - **Balance theorem**
    - Total cost for $m$ operations is as good as *any* balanced tree
    - Set $w(x)=\frac{1}{n}$
    - Total cost: $O((n+m)\log{n})$ 
  - **Static Optimality**
    - Total cost for $m$ operations is as good as of *any* fixed tree (even with opeation sequence known)
    - If node accessed $mp_x$ times, set $w_x=mp_x$
    - Total cost: $O(m\log_x{\log{1/p_x}})$
    - Matches the lower bound for static access: Huffman coding
  - **Static Finger Optimality**
    - Total cost for $m$ operations is as good as of *any* fixed tree in which additionally we start our search from any fixed node $f$
    - set $w_x=\frac{1}{1+|x-f|^2}$，where $|x-f|$ is the distance between $x$ and finger $f$
    - Amortized cost of search(x): $O(\log{|x-f|})$
    - Is optimal for *dynamic* finger too
  - **Working Set/Cache Optimality**
    - At access $j$ to node $x_j$, let be number of distinct nodes accessed since that node $x_j$ was previously accessed
    - Time: $O(n\log n +\sum{\log t_j})$
  - **Best-of-the-Above Optimality**
    -  Cost is at most as good as the *best* one of the choices stemming from the above optimality conditions
  - **Dynamic Optimality Conjecture**
    -  The performance of splay tree matches (up to constant) the performance of the best *dynamic* BST
- [cpp code 1](https://github.com/SkqLiao/MIT-6.5210/blob/main/splay-tree/splay.cpp)
  - [LOJ 104](https://loj.ac/p/104)
  - insert / delete / kth / rank / pre / nxt
  
- [cpp code 2](https://github.com/SkqLiao/MIT-6.5210/blob/main/splay-tree/splay-rev.cpp)
  - [LOJ 105](https://loj.ac/p/105)
  - reverse interval


## Lecture 5: Buckets

- Analysis: SSSP problem
  - OJ Submission: [CSES Shortest Routes I](https://cses.fi/problemset/task/1671/)
  - Suppose max edge distance is $C$
  - heap min increasing
  - Dial’s algorithm
    - Use $nC$ buckets to store node with different distance
    - Time Complexity: $O(m+nC)$ or $O(m+D)$, $D$ stands for max distance
    - Using circular storing: $C$ buckets only
    - [C++ code](https://github.com/SkqLiao/MIT-6.5210/blob/main/buckets/naive.cpp)
      - *without* decrase_key (push same node multiple times)
      - **RE** if $C$ is huge (space: $O(C)$)
  - Two-level block
    - $b$ buckets a block
    - Time Complexity: $O(m+nC/b+nb)=O(m+n\sqrt{C})$ where $b=\sqrt{C}$
    - [C++ code](https://github.com/SkqLiao/MIT-6.5210/blob/main/buckets/sqrt-block.cpp) 
      - *without* decrase_key (push same node multiple times)
      - **RE** if $C$ is huge (space: $O(C)$​)
    - [C++ code2](https://github.com/SkqLiao/MIT-6.5210/blob/main/buckets/sqrt-list-block.cpp) 
      - *without* decrase_key (push same node multiple times)
      - space allocated when necessary (but without rubbish collection)
  - $k$ level block: Trie
    - depth $k$ tree over arrays of size $\Delta=(C+1)^{1/k}$
    - Time Complexity: $O(km+knC^{1/k})=O(m\log_{m/n}{C})$ where $k=\log{C}/\log{(m/n)}$
  - Lazy Trie
    - Time Complexity: $O(m+n(k+C^{1/k}))=O(m+n\log{C}/\log{\log{C}})$ where $k=2\log{C}/\log{\log{C}}$
    - [C++ code](https://github.com/SkqLiao/MIT-6.5210/blob/main/buckets/sqrt-trie-block.cpp) 
      - *with* decrease_key
      - space allocated when necessary (but without rubbish collection)
  - Summary
    - slower than dijkstra in practice
    - due to high constant factor
