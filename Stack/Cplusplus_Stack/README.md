# C++ Stack
In C++ Stack is a container adaptor. C++ Sequential Container Types:
<ul>
  <li>vector&emsp;&emsp;fast random access; inserting/deleting other than at the back may be slow</li>
  <li>deque&emsp;&emsp;fast random access; fast insert/delete at front or back</li>
  <li>list&emsp;&emsp;(doubly linked list) only bidirectional sequential access; fast insert/delete at any point</li>
  <li>forward_list&emsp;&emsp;(singly linked list) access in one direction; fast insert/delete at any point</li>
  <li>array&emsp;&emsp;fast random access; cannot add or remove elements</li>
  <li>string&emsp;&emsp;fast random access; inserting/deleting other than at the back may be slow</li>
</ul>
<br>The stack adaptor takes an existing sequential container type and makes it act like a stack. Uses deque by default because as the container grows, a reallocation for a vector requires copying all the elements into the new block of memory. Growing a deque allocates a new block and links it to the list of blocks - no copies are required. Can also be implemented on a list or vector.<br>
C++ std::stack doesn't support random access or expose iterators; it has not been designed for iterating over elements. Use std::vector (or see get_underlying_container.cpp).
