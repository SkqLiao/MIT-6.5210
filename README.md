# MIT 6.5210/18.415: Advanced Algorithms

- Course Website: https://6.5210.csail.mit.edu/

- Materials: https://6.5210.csail.mit.edu/materials.html
- Problem Sets: https://6.5210.csail.mit.edu/psets.html

## Course

- [Lecture 01: Fibonacci Heaps](https://www.youtube.com/watch?v=rnwf0dDGNCM&t=879s) :white_check_mark: 2023/12/25

- [Lecture 02: Fibonacci Heap and Persistent Data Structures](https://www.youtube.com/watch?v=TB3Y308PCrA) 

## Lecture 1:  Fibonacci Heaps

- Minimum Spanning Tree (MST)
  - Overall tutorial (Chinese): [OI-Wiki](https://oi-wiki.org/graph/mst/)
  - Online Judge & Data Format (Chinese): [LG P3366](https://www.luogu.com.cn/problem/P3366)
  - Prim: select "nearest" vertex by heap
    - [with STL priority_queue](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-stl.cpp) (no `modify`/`decrease_key`)
      - $O((n+m)\log{m})$, since there's no `decrease`, pq's maximum size is $m$, with many "out-dated" vertexes
      - [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue): document for STL pq
    - [with pbds priority_queue (thin_heap_tag)](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-pbds.cpp) (has `modify`)
      - $O(n\log{n}+m)$, $O(1)$ for `push` / `decrease_key`,  $\Theta(\log{n})$ for `pop`
      - [Priority-Queue Design](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_design.html): document for pbds pq
      - [Priority-Queue Performance Tests](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html):  performance tests for difference pqs
    - [with hand-written binary_heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-binary.cpp) (has `decrease_key`)
      - $O((n+m)\log{n})$, $O(\log{n})$ for `push` / `decrease_key` / `pop`
    - [with hand-written d-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-dheap.cpp) (has `decrease_key`)
      - $O(m\log_{\frac{m}{n}}{n})$, set $d=\frac{m}{n}$ to balance `push` / `decrease_key` $O(m\times \log_{d}{n})$ and `pop` $O(n\times d\log_{d}{n})$
    - [with hand-written binomial-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-binomial.cpp) (has `decrease_key`)
      - $O((n+m)\log{n})$, $O(1)$ for `push` ,  $O(\log{n})$ for `pop` / `decrease_key`
  - [Kruskal](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/kruskal.cpp): select "shortest" edge by DSU
    - $O(m\log{m})$, sorting all edges by `std::sort`
    - [Disjoint Sets Union](https://codeforces.com/edu/course/2/lesson/7): Theory & Practice by [Codeforces ITMO Academy: pilot course](https://codeforces.com/edu/course/2)
      - $O(m\alpha(n))$, DSU `search` with *Union-By-Rank* and *path compression*
      - [code](https://github.com/SkqLiao/codeforces-edu): solution code for practice of [Step 1](https://codeforces.com/edu/course/2/lesson/7/1/practice), [Step 2](https://codeforces.com/edu/course/2/lesson/7/2/practice), [Step 3](https://codeforces.com/edu/course/2/lesson/7/3/practice)
  - [Borůvka](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/boruvka.cpp): connect components with "shortest" edges by DSU
    - $O(m\log{n})$, maximum $O(\log{n})$ iterations to connect all components
- Binomial Heap
  - *Stanford CS166* **Amortized Analysis**: [Lecture Slides](https://web.stanford.edu/class/cs166/lectures/06/Slides06.pdf), [Condensed Slides](https://web.stanford.edu/class/cs166/lectures/06/Small06.pdf)
  - *Stanford CS166* **Binomial Heaps**: [Lecture Slides](https://web.stanford.edu/class/cs166/lectures/07/Slides07.pdf), [Condensed Slides](https://web.stanford.edu/class/cs166/lectures/07/Small07.pdf)
- Fibonacci Heap
  - *Stanford CS166* **Fibonacci Heaps**: [Lecture Slides](https://web.stanford.edu/class/cs166/lectures/08/Slides08.pdf), [Condensed Slides](https://web.stanford.edu/class/cs166/lectures/08/Small08.pdf)
