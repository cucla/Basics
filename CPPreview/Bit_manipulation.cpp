/*  1 byte = 8 bits
 *  1 byte is the smallest addressable unit of memory; bit does not get its own address
 *
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
  * 
  * In ASCII - letters and numbers [0 - 127]
  *   signed char     holds at least the values [-127 - 127] 
  *   unsigned char   holds at least the values [0 - 255]
  */
