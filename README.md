## bitwise copression - decompression of information

### type introduced

typedef unsigned long bitwise 
### void encode_info(bitwise *encoded, bitwise importance, bitwise module, bitwise paragraph);
<p>is used to compress the information <br>
encoded - the adress where the function will save the information <br>
importance, module, paragraph - the information that will be compressed </p>

### void get_info( bitwise encoded, bitwise *importance, bitwise *module, bitwise *paragraph);
<p> is used to decompress the information <br>
encoded - compressed information. <br>
importance, module, paragraph - the adresses where the function will save the information </p>

