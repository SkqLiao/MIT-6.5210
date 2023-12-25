## [6.5210/18.415: Advanced Algorithms](https://6.5210.csail.mit.edu/)

- Materials: https://6.5210.csail.mit.edu/materials.html
- Problem Sets: https://6.5210.csail.mit.edu/psets.html

## Lecture 1:  Fibonacci Heaps

- Minimum Spanning Tree (MST)
  - Prim: select "nearest" vertex by heap
    - with STL's priority_queue (no `modify`/`decrease_key`): $O((n+m)\log{n})$
    - with pbds's priority_queue(thin_heap_tag) (has `modify`): $O(n\log{n}+m)$
    - with hand-written binary_heap (has `decrease_key`): $O((n+m)\log{n})$
    - with hand-written d-heap (has `decrease_key`) : $O(m\log_{\frac{m}{n}}{n})$
  - Kruskal: select "shortest available" edge by DSU: $O(m\log{m})$
  - Borůvka: connect components with "shortest" edge by DSU: $O(m\log{n})$
