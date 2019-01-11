// book: http://sandbox.mc.edu/~bennet/cs110/index.html
// https://www.cs.cornell.edu/~tomf/notes/cps104/

/*  1 byte = 8 bits
 *  1 byte is the smallest addressable unit of memory; bit does not get its own address
 *  a variable with n bits can hold 2^n possible values,
 *	an n-bit unsigned variable has a range of 0 to (2^n)-1
 *	an n-bit signed variable has a range of -2^(n-1) to 2^(n-1)-1
 *
 *  bool      [1 byte,  8 bits]    00000000             -> 2^8, 256 possible values
 *  char      [1 byte,  8 bits]    00000000             -> 2^8, 256 possible values
 *  short     [2 bytes,  16 bits]  00000000.00000000    -> 2^16, 65,536 possible values
 *  int       [4 bytes,  32 bits]  00000000.00000000.00000000.00000000   -> 2^32, 65,536 possible values
 *  long      [4 bytes,  32 bits]  00000000.00000000.00000000.00000000   -> 2^32, 4,294,967,296 possible values
 *  long long [8 bytes,  64 bits]  00000000.00000000.00000000.00000000.00000000.00000000.00000000.00000000   -> 2^64
 *  float     [4 bytes,  32 bits]  00000000.00000000.00000000.00000000   -> 2^32, 4,294,967,296 possible values
 *  double    [8 bytes,  64 bits]  00000000.00000000.00000000.00000000.00000000.00000000.00000000.00000000   -> 2^64
 *  long double  [8, 12, or 16 bytes]
 *
 *  OVERFLOW - when bits are lost because a variable has not been allocated enough memory to store them,
 *  see 'Limits on Integer Constants', like INT_MAX [2147483647]
 *  automatic promotion follows the general progression:  char->short->int->long->float->double
 *
 *  CONVERTING TO 2s COMPLEMENT
 *  0000.0000   ->  2^8,  256 possible values
 *  [-128 to -1]  : 128 values		1000.0000 to 1111.1111
 *  [0 to 127]    : 128 values		0000.0000 to 0111.1111
 *  		In normal unsigned binary numbers 1000.0000 represents 128, but in 2's complement this represents -128
 *  		The normal behaviour of adding 1, 1000.0001 represents -127
 * Find negative of 75:
 *	1001011		Convert to Binary (unsigned)
 *	01001011	Pad out to required number of bits
 *	10110100	Invert the digits
 *	10110101	Add 1, and you are done :)
 *  		!!! to find the negative of an n-bit number -> subtract the number from 0 or 2^n (one bit followed by n zero bits)
 *		to find positive -> add negative to 2^n (positive is negative of negative)
 * Find negative of 75:
 *	   1111 111
 *	 1.0000.0000   // 256
 *	-  0100.1011   // 75
 *	------------
 *	 0.1011.0101
 */
 

 /* CHARS
  * In ASCII - letters and numbers [0 - 127] codes, which can be represented using bits
  *   signed char     holds at least the values [-127 to 127] 
  *   unsigned char   holds at least the values [0 to 255]
  */
char ch1(97);	// initialize with integer 97
char ch2('a');	// initialize with code point for 'a' (97)
std::cout << static_cast<int>(ch1) << std::endl;	// 97 -> ASCII code
std::cout << sizeof(char) << std::endl;			// 1


 /* INTEGERS
  *   signed short     holds at least the values [-32,768 to 32,767] 
  *   unsigned short   holds at least the values [0 to 65,535]
  *   signed int       holds at least the values [-2,147,483,648 to 2,147,483,647] 
  *   unsigned int     holds at least the values [0 to 4,294,967,295]
  *
  *  Binary arithmetic:		
  *	0 + 0 = 0; 		0 x 0 = 0;
  *	0 + 1 = 1;		0 x 1 = 0;
  *	1 + 0 = 1;		1 x 0 = 0;
  *	1 + 1 = 10;		1 x 1 = 1;
  *
  *     add 7 + 4 = 11
  *	4       00000000 00000000 00000000 00000100
  *	7       00000000 00000000 00000000 00000111
  *	-------------------------------------------
  *	        00000000 00000000 00000000 00001011
  *
  *	subtract 7 - 6 = 1
  *     First form the complement of 6  
  *	  6 = 0000 0000 0000 0000 0000 0000 0000 0110
  *	      1111 1111 1111 1111 1111 1111 1111 1001  invert bits
  *           0000 0000 0000 0000 0000 0000 0000 0001  add one
  *       -------------------------------------------
  *           1111 1111 1111 1111 1111 1111 1111 1010  -6
  *           0000 0000 0000 0000 0000 0000 0000 0111  add 7
  *       -------------------------------------------
  *          10000 0000 0000 0000 0000 0000 0000 0001  1       ignore the final carry as it is overflow
  *
  *  Literal suffixes:
  *	int	u or U						unsigned int
  *	int	l or L						long
  *	int	ul, uL, Ul, UL, lu, lU, Lu, or LU		unsigned long
  *	int	ll or LL					long long
  *	int	ull, uLL, Ull, ULL, llu, llU, LLu, or LLU	unsigned long long
  *	double	f or F						float
  *	double	l or L						long double
  *
  */

 /* FLOAT
  *  Floating point numbers are divided into sign bit, exponent and mantissa
  *  Single precision, which uses 32 bits		Double precision, which uses 64 bits
  *	1 bit for the sign					1 bit for the sign
  *	8 bits for the exponent					11 bits for the exponent
  *	23 bits for the mantissa				52 bits for the mantissa
  *
  *  Scientific notation: 	9.87654e+06 for 9876543.21
  *  The precision - defines how many significant digits it can represent without information loss
  *  float	4 bytes		6-9 significant digits, typically 7
  *  double	8 bytes		15-18 significant digits, typically 16
  *
  *  Convert 17.125 to floating point:							101.101 translates as:
  *	i. Convert 17 to Binary									1 * 2^2	   4
  *	    17 / 2 = 8  r 1									0 * 2^1	   0
  *	    8  / 2 = 4  r 0									1 * 2^0	   1
  *	    4  / 2 = 2  r 0									1 * 2^-1   1/2  double the denominator
  *	    2  / 2 = 1  r 0					dec  bin			0 * 2^-2   0
  *	    1  / 2 = 0  r 1  stop read backwards,		17 = 10001			1 * 2^-3   1/8
  *	ii. Convert .125 to binary							     	    5.625
  *	    .125 x 2 = 0.25   0
  *	    .25  x 2 = 0.50   0
  *	    .5   x 2 = 1.0    1					 dec    bin
  *	     0   stop when zero or you run out of bits, 	.125 = .001
  *	iii. 17.125 = 10001.001 
  *	iv. Move the decimal point 4 digits to the left (4 = 100) 
  *	    1.0001001 x 2^100 
  *     v. Bias the exponent by 127  (add 127 to 4 = 100)
  *        0111 1111  (127 in binary)
  *	   0000 0100
  *	   ----------
  *        1000 0011
  *	   	The 8 bits of exponent allow us to encode unsigned numbers [0 .. 255[. 
  *	   	The IEEE standard uses a midpoint bias to center this range at zero and allow negative numbers. 
  *	   	The range of (exponent-127) is [-127 .. 128], which allows negative exponents up to -127.
  *	vi.   Sign bit = 0
  *	vii.  Exponent = 10000011
  *	viii. Mantissa = 0001001   (before storing the mantissa we drop the leading 1 to store 1 more bit of data)
  *     ix.   17.125 = 0 10000011 000100100000000000000000 = 0x43120000
  *
  *  Special cases:
  *  1 = 0  01111111 00000000000000000000000
  *  2 = 0  10000000 00000000000000000000000
  */
float y{ 5.0f };
float f = 4.1;   // is treated as double by default
double z1{ 5e4 };   // 50000
double z2{ 5e-2 };  // 0.05

// BOOL
bool b1 { true };
bool b2 = !true; // false
std::cout << std::boolalpha; // print bools as true or false
std::cout << true << std::endl;
std::cout << false << std::endl;   // std::noboolalpha to turn it back off

// OCTAL
int x1 = 012; // 0 before the number means this is octal

/* HEXADECIMAL
 *	Hex	Decimal		Binary
 *	0	0		0000
 *	1	1		0001
 *	2	2		0010
 * 	3	3		0011
 *	4	4		0100
 * 	5	5		0101
 *	6	6		0110
 *	7	7		0111
 *	8	8		1000
 *	9	9		1001
 *	A	10		1010
 *	B	11		1011
 *	C	12		1100
 *	D	13		1101
 *	E	14		1110
 *	F	15		1111
 *	10	16
 *	11	17
 * Because there are 16 different values for a hexadecimal digit - a single hexadecimal digit encompasses 4 bits, 0000
 * A pair of hexadecimal digits can be used to exactly represent a full byte, 00000000
 */

// Properties for numbers which are powers of 2, is that they have one and only one bit set in their binary representation

int bin(0);
bin = 0x01;   // binary 0000 0001  	1
bin = 0x02;   // binary 0000 0010  	2
bin = 0x04;   // binary 0000 0100  	4
bin = 0x08;   // binary 0000 1000  	8
bin = 0x10;   // binary 0001 0000  	16
bin = 0x20;   // binary 0010 0000  	32
bin = 0x40;   // binary 0100 0000  	64
bin = 0x80;   // binary 1000 0000  	128
bin = 0xFF;   // binary 1111 1111  	255

// BINARY, C++14
int bin;
bin = 0b1;		// binary 0000 0001		1	
bin = 0b10;		// binary 0000 0010		2
bin = 0b100;		// binary 0000 0100		4
bin = 0b1'000;		// binary 0000 1000		8
bin = 0b10'000;		// binary 0001 0000		16
bin = 0b100'000;	// binary 0010 0000		32
bin = 0b1'000'000;  	// binary 0100 0000		64
bin = 0b10'000'000;	// binary 1000 0000		128


// 1. Convert positive Decimal int to Binary
// 2. Convert char (8 bits) positive/negative to Binary
// 3. Conver Binary number to Deciml number


// 1. Convert positive Decimal int to Binary-------------------------------------------------
// if n = 97: 97 % 2, 48 % 2, 24 % 2, 12 % 2... in reverse order
// IMPPORTANT:
	std::cout << 1 / 2 << std::endl;   // 0
	std::cout << 1 % 2 << std::endl;   // 1

void decToBinary(int n) {
	if (n / 2 != 0) {
		decToBinary(n / 2);
	}
	std::cout << n % 2;
}

// 2. Convert char (8 bits) positive/negative to Binary--------------------------------------
// IMPPORTANT:		'0' ASCII code 48
//			'1' ASCII code 49

std::string decimal_to_binary(int n) {
	if (n < 0) {		// check if negative
		n = 256 + n;    // for char input 8 bits; for int, 32 bits, input 65,536
	}
	std::string result = "";
	while (n > 0) {
		result = std::string(1, (char)(n % 2 + 48)) + result;
		n = n / 2;
	}
	return result;
}

// 3. Convert Binary number to Deciml number-------------------------------------------------
// if n = 1100001 : 1 * 2^6 + 1 * 2^5 + 0 * 2^4 + 0 * 2^3 + 0 * 2^2 + 0 * 2^1 + 1 * 2^0 
void binToDecimal(int n) {
	int power = 1;
	int result = 0;

	while (n != 0) {
		result += (n % 10) * power;
		power *= 2;
		n /= 10;
	}
	std::cout << result << std::endl;
}
