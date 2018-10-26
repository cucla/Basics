# Stack

LIFO - a restricted linear list (addition and deletion of data is restricted to the end, called the top).<br>
Basic operations:
<ul>
  <li>Push - insert data. If there is not enough room, result in overflow</li>
  <li>Pop - remove data. If stack is empty, result in underflow</li>
  <li>Top - read the top without deleting. If stack is empty, result in underflow</li>
</ul>
<br>
Stack operations are constant time operations.
<br>
<br>
Four common stack applications are: reversing data, parsing data, postponing data usage, and backtracking steps.<br>
The idea of reversing can be used to CONVERT DECIMAL TO BINARY:
<code>read (number)</code>
<code>loop (number > 0)</code>
<code>  set digit to number modulo 2</code>
<code>  push digit to stack</code>
<code>  set number to quotient of number / 2</code>
<code>end loop</code>
