#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bitwise_encoding.c"
#include "bitwise_encoding.h"

void check(void *pointer)
{
    if(pointer == NULL)
    {
        printf("ALOCARE ESUATA!\n");
        exit(1);
    }
}

typedef struct element
{
    char *sequence;
    bitwise priority;
    bitwise module;
    bitwise paragraph;
}
ELEMENT;

typedef struct crypto
{
    char *sequence;
    bitwise encoded;
}
CRYPTO

/*
    * scot un element dintr-o linie din hashmap și construiesc o structură de tip ELEMENT
*/
CRYPTO construct(char *string)
{
    int i = 0;
    char *token = NULL;
    char **sentence = (char**) malloc(100 * sizeof(char*)); // Allocate memory for array of pointers
    check(sentence);
    token = strtok(string, ",");
    while(token != NULL)
    {
        sentence[i] = (char*)malloc((strlen(token) + 1) * sizeof(char)); // Allocate memory for each string
        check(sentence[i]);
        strcpy(sentence[i], token);
        i ++;
        token = strtok(NULL, ",");
    }

    CRYPTO element;
    element.sequence = (char*) malloc((strlen(sentence[0]) + 1) * sizeof(char));
    check(element.sequence);
    strcpy(element.sequence, sentence[0]);
    element.encoded = atoi(sentence[1]);

    for (int j = 0; j < i; j++) 
    {
        free(sentence[j]);
    }
    free(sentence);

    return element;
}

/*
    ? formez array-ul cu toate structurile de tip ELEMENT din Hashmap
*/
void create_keylist(char *fileName, CRYPTO **keylist, int *nrElements)
{
    FILE *fin;
    char *header = (char*) malloc(1000 * sizeof(char));
    check(header);
    char *string = (char*) malloc(1000 * sizeof(char));
    check(string);

    if((fin = fopen(fileName, "rt")) == NULL)
    {
        printf("Deschidere esuata!\n");
        exit(1);
    }

    fgets(header, 1000, fin);
    free(header);
    while(!feof(fin))
    {
        fgets(string, 1000, fin);
        CRYPTO element = construct(string);
        (*nrElements) ++; 
        *keylist = (CRYPTO*) realloc(*keylist, *nrElements * sizeof(CRYPTO));
        check(keylist);
        (*keylist)[*nrElements - 1] = element; 
    }

    free(string);
    fclose(fin);
}


int minim(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

/*
    ?  Algoritmul general de MergeSort, pentru a sorta lista finală cu elementele dorite din hashmap
*/
void mergesort(void* ptr, int n, size_t size, int (*comp)(const void*, const void*))
{
    if (n == 1) return;
    char *v = ptr;
    int mid = n / 2;
    mergesort(ptr, mid, size, comp);
    mergesort(v + mid * size, n - mid, size, comp);
    char *merge = malloc(size * n);
    check(merge);

    int i, st = 0, dr = mid;
    for (i = 0; st < mid && dr < n; i++)
    {
        if ((*comp)(v + st * size, v + dr * size) < 0) 
        {
            memcpy(merge + i * size, v + st * size, size);
            st++;
        }
        else
        {
            memcpy(merge + i * size, v + dr * size, size);
            dr++;
        }
    }
    while (st < mid)
    {
        memcpy(merge + i * size, v + st * size, size);
        st++; i++;
    }
    while (dr < n)
    {
        memcpy(merge + i * size, v + dr * size, size);
        dr++; i++;
    }
    memcpy(ptr, merge, size * n);
}

/*
    * criteriul de comparatie prin care voi sorta crescător lista rezultatelor în ordinea următoare:
        1. prioritate
        2. string
        3. modul
        4. paragraf
*/
int comp(const void *elemA, const void *elemB)
{
    const CRYPTO *a = (const CRYPTO*) elemA;
    const CRYPTO *b = (const CRYPTO*) elemB;

    return (a->encoded < b->encoded)  
    ||
    (
        (a->encoded == b->encoded) &&
        strcmp(a->sequence, b->sequence) < 0
    ) 
    ;
}

/*
    ! Algoritmul pentru determinarea distantei Levenshtein 
    ** Algoritmul are la bază programanea dinamică pe o matrice de m linii și n coloane
    (
        m - lungimea stringului pattern + 1
        n - lungimea stringului text + 1
        (
            ? șirurile trebuie să fie numerotate de la 1 la m, respectiv la n; 
            ? pentru a avea linia 0 și coloana 0 libere pentru configurația inițială de la care pleacă algoritmul
        ) 
    )
*/
int Levenshtein_distance(char *text, char *pattern)
{
    check(text);
    check(pattern);
    int n = strlen(text); 
    int m = strlen(pattern); 
    int **distance = (int**) calloc((m + 1),  sizeof(int*));
    check(distance);
    int i, j;

    /*
        ? mutarea stringurilor cu o unitate la dreapta
    */

    for(i = 0; i <= m; i ++)
    {
        distance[i] = (int*) calloc((n + 1),  sizeof(int));
        check(distance[i]);
    }

    for(i = 0; i <= m; i ++)
        distance[i][0] = i;
    
    for(j = 0; j <= n; j ++)
        distance[0][j] = j;

    int substitutionCost;
    for(i = 1; i <= m; i ++)
        for(j = 1; j <= n; j ++)
        {
            if(pattern[i - 1] != text[j - 1])
                substitutionCost = 1;
            else
                substitutionCost = 0;

            distance[i][j] = minim(
                    minim(
                        distance[i - 1][j] + 1,
                        distance[i][j - 1] + 1
                    ),
                    distance[i - 1][j - 1] + substitutionCost
            );
        }
    
    /*
        ? resetarea stringurilor la poziția inițială
    */

    int result = distance[m][n];
    for(i = 0; i <= m; i ++)
        free(distance[i]);
    free(distance);

    return result;
}


void create_resultlist(char *input, CRYPTO *keylist, int sizeKeylist, ELEMENT **results, int *nrResults)
{
    int dist_minim = INT_MAX;
    CRYPTO *resultsEncrypted = NULL;
    *nrResults = 0;
    int i;
    for(i = 0; i < sizeKeylist; i ++)
        dist_minim = minim(dist_minim, Levenshtein_distance(input, keylist[i].sequence));

    //generăm rezultatul în forma criptată
    for(i = 0; i < sizeKeylist; i ++)
        if(Levenshtein_distance(input, keylist[i].sequence) == dist_minim)
        {
            *nrResults = *nrResults + 1;
            resultsEncrypted = (CRYPTO*) realloc(results, *nrResults * sizeof(CRYPTO));
            check(resultsEncrypted);
            results[*nrResults - 1] = keylist[i];
        }
    
    mergesort(resultsEncrypted, *nrResults, sizeof(CRYPTO), comp);

    *results = (ELEMENT*) malloc(*nrResults * sizeof(ELEMENT));
    check(*results);
    
    //convertim rezultatul în forma decriptată (ELEMENT)
    for(i = 0; i < *nrResults; i ++)
    {
        ELEMENT element;
        strcmp(element.sequence, resultsEncryped[i].sequence);
        get_info(resultsEncrypted[i].encoded, &(element.priority), &(element.module), &(element.paragraph));
        (*results)[i] = element;
    }
    free(resultsEncrypted);
}

int main()
{
    char input[50];
    CRYPTO *keyList = NULL;
    ELEMENT *resultslist = NULL;
    int nrElements, nrResults;

    int i;

    scanf("%s", input);
    create_keylist("wordlist.csv", &keyList, &nrElements);
    create_resultlist(input, keyList, nrElements, &resultslist, &nrResults);

    for(i = 0; i < nrResults; i ++)
        printf("%50s\t%1d\t%2d\t%3d\n", 
                resultslist[i].sequence, 
                resultslist[i].priority,
                resultslist[i].module,
                resultslist[i].paragraph
              );
    return 0;
}