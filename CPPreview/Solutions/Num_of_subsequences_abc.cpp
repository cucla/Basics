/* Given a string, count number of subsequences of the form a^ib^jc^k, i.e., it consists of i ’a’ characters, 
followed by j ’b’ characters, followed by k ’c’ characters where i >= 1, j >=1 and k >= 1.
Note: Two subsequences are considered different if the set of array indexes picked for the 2 subsequences are different.
Expected Time Complexity : O(n)

Examples:

Input  : abbc
Output : 3
abc, abc, abbc

Input  : abcabc
Output : 7
abc, abc, abbc, aabc, abcc, abc, abc
 */
 
Solution:
Going from left to right, keep track of the number of sequences until the current position, which are of these three forms:
1) a^i 
2) a^i b^j 
3) a^i b^j c^k 
Suppose that these are stored in three variables a,b,c respectively. 
Whenever you see the character 'a', it can extend the strings of type 1, and also, be the starting position for a string of type 1, 
so a+=(a+1), whenever you see a 'b', it can extend previous strings of type 1 and 2, so b+=(a+b), for 'c', it will extend all 
strings of type 2 and 3, so c+=(b+c).
