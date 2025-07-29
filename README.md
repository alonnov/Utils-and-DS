# Utils-and-DS
This repository provides a comprehensive collection of data structures and utility modules implemented in C. It is organized into two main components:

- **Data Structures (`ds/`)**: A variety of classic and advanced data structures, each with its own header and source files.
- **Utilities (`utils/`)**: Networking and system utilities for building robust C applications.

## Directory Structure

```
ds/
  include/   # Header files for data structures
  src/       # Source files for data structures

utils/
  include/   # Header files for utilities (networking, UID, etc.)
  src/       # Source files for utilities
```

---

## Data Structures

Located in `ds/include/` and `ds/src/`. Each data structure is implemented in C with a clear, modular interface.

- **AVL Tree (`avl.h`, `avl.c`)**: Self-balancing binary search tree.
- **Bit Array (`bit_arr.h`, `bit_arr.c`)**: Efficient manipulation of bit arrays.
- **Binary Search Tree (`bst.h`, `bst.c`)**: Standard BST implementation.
- **Circular Buffer (`cbuff.h`, `cbuff.c`)**: FIFO buffer for streaming data.
- **DHCP (`dhcp.h`, `dhcp.c`)**: Dynamic Host Configuration Protocol logic.
- **Doubly Linked List (`dll.h`, `dll.c`)**: List with fast insert/remove at both ends.
- **Dynamic Vector (`dvector.h`, `dvector.c`)**: Resizable array.
- **Fixed Size Allocator (`fsa.h`, `fsa.c`)**: Memory pool for fixed-size allocations.
- **Hash Table (`hash.h`, `hash.c`)**: Key-value store with fast lookup.
- **Heap (`heap.h`, `heap.c`)**: Binary heap for priority queue operations.
- **Heap-based Priority Queue (`heap_PQ.h`, `heap_PQ.c`)**: Priority queue using a heap.
- **Heap-based Scheduler (`heap_scheduler.h`, `heap_scheduler.c`)**: Task scheduler using a heap.
- **Priority Queue (`pqueue.h`, `pqueue.c`)**: General priority queue.
- **Queue (`queue.h`, `queue.c`)**: FIFO queue.
- **Scheduler (`scheduler.h`, `scheduler.c`)**: Task scheduling system.
- **Singly Linked List (`sll.h`, `sll.c`)**: Simple linked list.
- **Stack (`stack.h`, `stack.c`)**: LIFO stack.
- **Variable Size Allocator (`vsa.h`, `vsa.c`)**: Memory pool for variable-size allocations.
- **Sorted List (`slist.h`, `slist.c`)**: Linked list maintaining sorted order.

Each module is documented in its header file, describing its API and usage.

---

## Utilities

Located in `utils/include/` and `utils/src/`. These modules provide reusable components for networking and system programming.

- **Server (`server.h`, `server.c`)**: TCP/UDP server framework.
- **Sockets (`sockets.h`, `sockets.c`)**: Abstractions for socket operations.
- **TCP Listener (`tcp_listener.h`, `tcp_listener.c`)**: Listen and accept TCP connections.
- **TCP Talker (`tcp_talker.h`, `tcp_talker.c`)**: TCP client utilities.
- **UDP (`udp.h`, `udp.c`)**: UDP socket utilities.
- **UID (`uid.h`, `uid.c`)**: Unique identifier generation and comparison.

---

## Usage

1. **Include the relevant header** in your C source file.
2. **Link the corresponding source file** when compiling.
3. **Refer to the header documentation** for API details and usage examples.

Example (compiling with GCC):

```sh
gcc -I./ds/include -I./utils/include your_program.c ds/src/heap.c utils/src/sockets.c -o your_program
```

## License

created by Alon Nov

---

Let me know if you want to add build instructions, usage examples, or more detailed module descriptions! 
