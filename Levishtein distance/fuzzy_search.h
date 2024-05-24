#ifndef FUZZY_SEARCH
#define FUZZY_SEARCH

#include "bitwise_encoding.h"

#define minim(a, b) a < b ? a : b

// * the CRYPTO function
typedef struct crypto
{
    char *sequence;
    bitwise encoded;
}
CRYPTO;

// * the ELEMENT function
typedef struct element
{
    char *sequence;
    bitwise priority;
    bitwise modul;
    bitwise paragraph;
}
ELEMENT;

//the check function used to prevent accesing unalocated memory
void check(void *pointer);

// * Converting a line from the HashMap into a CRYPTO element
CRYPTO construct(char *string);

// * generating the keylist array from the hashmap
void create_keylist(char *fileName, CRYPTO **keylist, int *nrElements);


/*
    * sorting criteria priority:
        1. ascending order after encoded
        2. alphabetical order of the sequence elements
*/
int comp(const void *elemA, const void *elemB);

/*
    ! the Algorithm for determing the Levenshtein distance 
    * the base of the algorithm is the dynamic programming method using a m x n matrix 
    (
        m - strlen(pattern) + 1
        n - strlen(text) + 1
        (
            ? the characters in each string should be counted from 1 to strlen(string); 
            ? the line 0 and column 0 are used for initial changes
        ) 
    )
*/
int Levenshtein_distance(char *text, char *pattern);

// * generating the resultlist array
void create_resultlist(char *input, CRYPTO *keylist, int sizeKeylist, ELEMENT **results, int *nrResults);

// * outer access function
ELEMENT* result_driver(char *input, int *count);

// * free exposed memory
void free_mem(void *ptr);

#endif