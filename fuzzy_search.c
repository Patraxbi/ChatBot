#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bitwise_encoding.h"
#include "bitwise_encoding.c"
#include "fuzzy_search.h"

void check(void *pointer)
{
    if(pointer == NULL)
    {
        printf("ALOCARE ESUATA!\n");
        exit(1);
    }
}

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

    *keylist = malloc(sizeof(CRYPTO));
    *nrElements = 0;

    while(fgets(string, 1000, fin) != NULL)
    {
       CRYPTO element = construct(string);
       (*nrElements)++;
       *keylist = (CRYPTO*) realloc(*keylist, *nrElements * sizeof(CRYPTO));
        check(*keylist);
        (*keylist)[*nrElements - 1] = element;
    }

    free(string);
    fclose(fin);
}

/*
    * criteriul de comparatie prin care voi sorta crescător lista rezultatelor în ordinea următoare:
        1. cifru
        2. string
*/
int comp(const void *elemA, const void *elemB)
{
    const CRYPTO *a = (const CRYPTO*) elemA;
    const CRYPTO *b = (const CRYPTO*) elemB;

    return (a->encoded > b->encoded)  
    ||
    (
        (a->encoded == b->encoded) &&
        strcmp(a->sequence, b->sequence) > 0
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
    int *distances = malloc(sizeKeylist * sizeof(int));
    int dist_minim = INT_MAX;
    CRYPTO *resultsEncrypted = NULL;
    *nrResults = 0;
    int i;
    for(i = 0; i < sizeKeylist; i ++)
    {
        distances[i] = Levenshtein_distance(input, keylist[i].sequence);
        if (distances[i] < dist_minim)
            dist_minim = distances[i];
    }

    // Nu au fost găsite rezultate suficient de apropiate
    if (dist_minim > 3) return;

    //generăm rezultatul în forma criptată
    for(i = 0; i < sizeKeylist; i ++)
        if(distances[i] == dist_minim)
        {
            *nrResults = *nrResults + 1;
            resultsEncrypted = (CRYPTO*) realloc(resultsEncrypted, *nrResults * sizeof(CRYPTO));
            check(resultsEncrypted);
            resultsEncrypted[*nrResults - 1] = keylist[i];
        }
    
    // mergesort(resultsEncrypted, *nrResults, sizeof(CRYPTO), comp);

    *results = (ELEMENT*) malloc(*nrResults * sizeof(ELEMENT));
    check(*results);
    
    //convertim rezultatul în forma decriptată (ELEMENT)
    for(i = 0; i < *nrResults; i ++)
    {
        ELEMENT element;
        strcpy(element.sequence, resultsEncrypted[i].sequence);
        get_info(resultsEncrypted[i].encoded, &(element.priority), &(element.modul), &(element.paragraph));
        (*results)[i] = element;
    }
    free(resultsEncrypted);
}

int scanPriority(char *input, int prio, ELEMENT **results, int *count)
{
    CRYPTO *keyList = NULL;
    ELEMENT *resultslist = NULL;
    int nrElements, nrResults;

    char filename[] = "Output\\prio0.csv";
    filename[11] = prio + '0';
    
    create_keylist(filename, &keyList, &nrElements);
    create_resultlist(input, keyList, nrElements, &resultslist, &nrResults);

    printf("\tPRIORITY %i:\n", prio);
    if (nrResults == 0)
    {
        printf("%50s\n", "ERROR 404");
        *results = NULL;
        *count = 0;
        return 0;
    }
    
    for(int i = 0; i < nrResults; i ++)
        printf("%50s\t%1d\t%2d\t%3d\n", 
                resultslist[i].sequence, 
                resultslist[i].priority,
                resultslist[i].modul,
                resultslist[i].paragraph
            );
    *results = resultslist;
    *count = nrResults;
    return *count;
}

int main()
{
    ELEMENT *resultlist; int count; char input[50];
    scanf("%s", input);
    for (int i = 0; i < 4; i++)
        scanPriority(input, i, &resultlist, &count);
    return 0;
}