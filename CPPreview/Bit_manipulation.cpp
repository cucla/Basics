/*  1 byte = 8 bits
 *  1 byte is the smallest addressable unit of memory; bit does not get its own address
 *  a variable with n bits can hold 2^n possible values
 *
 *  bool      [1 byte,  8 bits]    0000.0000             -> 2^8, 256 possible values
 *  char      [1 byte,  8 bits]    0000.0000             -> 2^8, 256 possible values
 *  short     [2 bytes,  16 bits]  0000.0000.0000.0000   -> 2^16, 65,536 possible values
 *  int       [2 bytes,  16 bits]  0000.0000.0000.0000.0000.0000.0000.0000   -> 2^32, 65,536 possible values
 *  long      [4 bytes,  32 bits]  0000.0000.0000.0000.0000.0000.0000.0000   -> 2^32, 4,294,967,296 possible values
 *  long long [8 bytes,  64 bits]  0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000   -> 2^64
 *  float     [4 bytes,  32 bits]  0000.0000.0000.0000.0000.0000.0000.0000   -> 2^32, 4,294,967,296 possible values
 *  double    [8 bytes,  64 bits]  0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000   -> 2^64
 */
 
 /* CHAR
  * In ASCII - letters and numbers [0 - 127] codes, which can be represented using bits
  *   signed char     holds at least the values [-127 - 127] 
  *   unsigned char   holds at least the values [0 - 255]
  */

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
