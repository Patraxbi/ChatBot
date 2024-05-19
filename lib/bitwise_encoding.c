#include "bitwise_encoding.h"
#include <stdio.h>

/*
int main(void){

    bitwise encoded, importance, module , paragraph;
	bitwise outimportance, outmodule, outparagraph;
	for ( importance = 0; importance < 5; importance++)
		for( module = 0; module< 7; module++)
			for (paragraph = 0; paragraph < 1000; paragraph++){
    			encode_info(&encoded, importance, module, paragraph);
    			get_info(encoded, &outimportance, &outmodule, &outparagraph);
					if( importance != outimportance || module != outmodule || paragraph != outparagraph){
    			printf("\n   importance= %lu\t   module= %lu\t   paragraph= %lu \n", importance, module, paragraph);
				printf("outimportance= %lu\toutmodule= %lu\toutparagraph= %lu \n", outimportance, outmodule, outparagraph);

					}
	}
}
*/

int encode_info(bitwise *encoded, bitwise importance, bitwise module,
				bitwise paragraph)
{
	*encoded = 0;
	return (encode(encoded, PARAGRAPH_BITS + MODULE_BITS , PARAGRAPH_BITS + MODULE_BITS + IMPORTANCE_BITS-1, importance) |
			encode(encoded, PARAGRAPH_BITS , PARAGRAPH_BITS + MODULE_BITS-1, module) |
			encode(encoded, 0, PARAGRAPH_BITS-1, paragraph));
}

int encode(bitwise *encoded, bitwise bit_start, bitwise bit_end, bitwise info)
{
	if (bit_start > 30 || bit_end > 30 || bit_end < bit_start)
		return -1;

	// checking if info is small enough to get in bit_end - bit_start + 1 bits
	bitwise auxiliar = 1;
	auxiliar = auxiliar << (bit_end - bit_start + 1);
	auxiliar--;

	if (auxiliar < info)
		return -1;

	// mask with 0s from bit_start to bit_end
	*encoded = *encoded &
		((UNSIGNED_INT_MAX >> bit_end) << bit_end + (1 << bit_start) - 1);

	// inserting info in en;coding
	// inserting info in encoding
	auxiliar = info;
	auxiliar = auxiliar << bit_start;
	*encoded = *encoded | auxiliar;

	return 0;
}

bitwise decode(bitwise encoded, bitwise bit_start, bitwise bit_end){
    
    encoded = encoded >> bit_start; // deleting first bits

    bitwise auxiliar = 1;
    auxiliar = auxiliar << bit_end -bit_start +1; // creating a mask for specified bits
									// previously was +2 because I forgot 1 is a bit on itself
	// formula is (bit_end - bitstart +1) - bits for the mask
	// + 1 , because u need one more bit for then to decrement and all to be 1s
	// -1, because we start form auxiliar=1, which already has bit on pos 0
    auxiliar--;
    return (encoded & auxiliar); // getting information
}

void get_info( bitwise encoded, bitwise *importance, bitwise *module, bitwise *paragraph){
    *importance = decode(encoded, PARAGRAPH_BITS + MODULE_BITS , PARAGRAPH_BITS + MODULE_BITS + IMPORTANCE_BITS-1);
	*module = decode(encoded, PARAGRAPH_BITS , PARAGRAPH_BITS + MODULE_BITS-1);
	*paragraph = decode(encoded, 0, PARAGRAPH_BITS-1);
}