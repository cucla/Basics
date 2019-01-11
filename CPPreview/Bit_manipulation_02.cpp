/*  Bitwise Operators:
 *
 *  NOT ( ~ ):  1's complement, flip 0 to 1; 1 to 0
char a = 0xA5;		// 1010.0101
char b = ~a;      // 0101.1010
 *
 *  AND ( & ):  operates on two equal-length bit patterns; 1 & 1 = 1, otherwise 0
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010
int r = x & y;    // 0100.0010
 *
 *  OR ( | ):   operates on two equal-length bit patterns; 0 | 0 = 0, otherwise 1
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010
int r = x | y;    // 0101.1011
 *
 *  XOR ( ^ ):  takes two equal-length bit patterns; 1 ^ 0 = 1; 0 ^ 1 = 1, otherwise 0
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010
int r = x ^ y;    // 0001.1001
 *
 *  Left Shift ( << ): appends 0s at the end; is equivalent to multiplying with 2^k ( if we are shifting k bits )
char x = 75;      // 0100.1011
char r = x << 4;  // 1011.0000
 *
 *  Right Shift ( >> ): appends 0s at the beginning;
char x = 75;      // 0100.1011
char r = x >> 4;  // 0000.0100
 *
 */
 

// 1. Check if a given number is a power of 2
// 2. Count the number of 1s in the binary representation of a number
// 3. Check if the ith bit is set (is 1) in the binary form of a number
// 4. Generate all the possible subsets of a set
 

// 1. Check if a given number is a power of 2-------------------------------------------------
// x = 4 = (100)2
// x - 1 = 3 = (011)2 
// x & (x-1) = 4 & 3 = (100)2 & (011)2 = (000)2
 
 bool isPowerOfTwo(int x) {
	// x will check if x == 0 and !(x & (x - 1)) will check if x is a power of 2 or not
	return (x && !(x & (x - 1)));
 }
 
// 2. Count the number of 1s in the binary representation of a number------------------------
// 888 = (1101111000)2
// 887 = (1101110111)2
// in n and n-1 the rightmost 1 and bits right to it are flipped
// x & (x - 1) will reduce x to a number containing number of 1s (in its binary form) less than the previous state of x

int count_one (int n) {
    int count = 0;
    while( n ) {
	n = n & (n - 1);
	count++;
	}
    return count;
}

// Complexity: O(K), where K is the number of 1s

// 3. Check if the ith bit is set in the binary form of a number-----------------------------
 bool check (int N) {
        if( N & (1 << i) )
            return true;
        else
            return false;
    }

// 4. Generate all the possible subsets of a set---------------------------------------------
// for a set of N elements: each element has 2 possibilities - in set or not
// total number of subsets in 2^N, 	for 3 -> 2^3 = 8 subsets;  char A[]{ 'a', 'b', 'c' };
[] //empty	0	0
a		1	1
b		2	10
a b		3	11
c		4	100
a c		5	101
b c		6	110
a b c		7	111


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

