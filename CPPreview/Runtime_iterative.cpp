// Example 1, O(n)

   x = n
   while ( x > 0 ) {
       x = x - 1
   }
   
// Example 2, O(log_n)

   x = n
   while ( x > 0 ) {
       x = x / 2
   }
   
// Example 3, O(n^2)

   x = n
   while ( x > 0 ) {
      y = n
      while ( y > 0 ) {
          y = y - 1
      }
      x = x - 1
   }
   
// Example 4, O(n^2)

   x = n
   while ( x > 0 ) {
      y = x
      while ( y > 0 ) {
          y = y - 1
      }
      x = x - 1
   }
   
// Example 5, O(n * log_n)

   x = n
   while ( x > 0 ) {
      y = n
      while ( y > 0 ) {
          y = y / 2
      }
      x = x - 1
   }
   
// Example 6, O(n * log_n)

   x = n
   while ( x > 0 ) {
      y = x
      while ( y > 0 ) {
          y = y / 2
      }
      x = x - 1
   }
   
// Example 7, O(n * log_n)

   x = n
   while ( x > 0 ) {
      y = n
      while ( y > 0 ) {
          y = y - 1
      }
      x = x / 2
   }
   
// Example 8, O(n)

   x = n
   while ( x > 0 ) {
      y = x
      while ( y > 0 ) {
          y = y - 1
      }
      x = x / 2
   }
   
// Example 9, O(log^2_n)

   x = n
   while ( x > 0 ) {
      y = n
      while ( y > 0 ) {
          y = y / 2
      }
      x = x / 2
   }
   
// Example 10, O(log^2_n)

   x = n
   while ( x > 0 ) {
      y = x
      while ( y > 0 ) {
          y = y / 2
      }
      x = x / 2
   }
   
/* 
Explanation of recursive Fibonacci runtime, which is exponential O(2^n):

     T(n) = T(n-1) + T(n-2) <
     T(n-1) + T(n-1) 

     = 2*T(n-1)   
     = 2*2*T(n-2)
     = 2*2*2*T(n-3)
     ....
     = 2^i*T(n-i)
     ...
     ==> O(2^n)
 */
