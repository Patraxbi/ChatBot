#ifndef BITWISE_ENCODING
#define BITWISE_ENCODING

// * the following macros can be changed depending on
// * how many bits we want to use for each value
// * for n bits, the value can be between 0 and 2^n -1

#define UNSIGNED_INT_MAX 0xFFFFFFFF
#define IMPORTANCE_BITS 4 // 0-15
#define MODULE_BITS 3 // 0-7
#define PARAGRAPH_BITS 16 // 0 - 65.535  ( 2^16-1 )

typedef unsigned int bitwise;
// bitwise has 32 bits to work with
// ! bitwise (00000000000)(000)(0000)(00000000000000)
// !         (unused)(importance)(module)(paragraph)    
// ! ALWAYS LET 1 UNUSED BIT ( lazy implementation of decode and encode)
// so basically only 31 bits to work with

// gets importance, module and paragraph from encoded
void get_info( bitwise encoded, bitwise *importance, bitwise *module, bitwise *paragraph);

//encodes importance, module and paragraph
// normally returns 0, returns -1 if an error has appeared
int encode_info(bitwise *encoded, bitwise importance, bitwise module, bitwise paragraph);


//encodes info in encoded from
// bit_start to bit_end
// bit_start ( 0 - 31)
// 31 >= bit_end >= bit_start
// normally returns 0, returns -1 if an error has appeared
int encode(bitwise *encoded, bitwise bit_start, bitwise bit_end, bitwise info);

// returns the value from bit_start to bit_end
bitwise decode(bitwise encoded, bitwise bit_start, bitwise bit_end);

// error case has not been handled for decode because everything to be decoded
// was already encoded with encode, so errors must not be there

#endif