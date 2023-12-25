# MIT 6.5210/18.415: Advanced Algorithms

- Course Website: https://6.5210.csail.mit.edu/

- Materials: https://6.5210.csail.mit.edu/materials.html
- Problem Sets: https://6.5210.csail.mit.edu/psets.html

## Lecture 1:  Fibonacci Heaps

- Minimum Spanning Tree (MST)
  - Overall tutorial(Chinese): [OI-Wiki](https://oi-wiki.org/graph/mst/)
  - Online Judge & input format(Chinese): [Luogu P3366](https://www.luogu.com.cn/problem/P3366)
  - Prim: select "nearest" vertex by heap
    - [with STL priority_queue](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-stl.cpp) (no `modify`/`decrease_key`)
      - $O((n+m)\log{n})$
      - [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue): document for STL pq
    - [with pbds priority_queue (thin_heap_tag)](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-pbds.cpp) (has `modify`)
      - $O(n\log{n}+m)$
      - [Priority-Queue Design](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_design.html): document for pbds pq
    - [with hand-written binary_heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-binary.cpp) (has `decrease_key`)
      - $O((n+m)\log{n})$
    - [with hand-written d-heap](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/prim-dheap.cpp) (has `decrease_key`)
      - $O(m\log_{\frac{m}{n}}{n})$
  - [Kruskal](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/kruskal.cpp): select "shortest" edge by DSU
    - $O(m\log{m})$
    - [Disjoint Sets Union](https://codeforces.com/edu/course/2/lesson/7): Tutorial & Exercise by [Codeforces ITMO Academy: pilot course](https://codeforces.com/edu/course/2)
      - [Solution code](https://github.com/SkqLiao/codeforces-edu)
  - [Borůvka](https://github.com/SkqLiao/MIT-6.5210/blob/main/lec1/boruvka.cpp): connect components with "shortest" edge by DSU
    - $O(m\log{n})$
