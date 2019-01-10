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
  *  binary arithmetic:		0 + 0 = 0; 	0 + 1 = 1;	1 + 0 = 1;	1 + 1 = 10
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
  */

 /* FLOAT
  *  Floating point numbers are divided into sign bit, exponent and mantissa
  *
  *  Scientific notation: 	9.87654e+06 for 9876543.21
  *  The precision - defines how many significant digits it can represent without information loss
  *  float	4 bytes		6-9 significant digits, typically 7
  *  double	8 bytes		15-18 significant digits, typically 16
  */
float y{ 5.0f };
double z1{ 5e4 };   // 50000
double z2{ 5e-2 };  // 0.05


// 1. Convert Decimal number to Binary number
// 2. Conver Binary number to Deciml number


// 1. Convert Decimal number to Binary number------------------------------------------------
// IMPPORTANT:
	std::cout << 1 / 2 << std::endl;   // 0
	std::cout << 1 % 2 << std::endl;   // 1
// if n = 97: 97 % 2, 48 % 2, 24 % 2, 12 % 2... in reverse order

void decToBinary(int n) {
	if (n / 2 != 0) {
		decToBinary(n / 2);
	}
	std::cout << n % 2;
}

// 2. Convert Binary number to Deciml number-------------------------------------------------
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

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------

// 1. Convert Decimal number to Binary number------------------------------------------------
//-------------------------------------------------------------------------------------------
