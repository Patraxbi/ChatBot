#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct element
{
    char *sequence;
    int priority;
    int module;
    int paragraph;
}
ELEMENT;

/*
    * scot un element dintr-o linie din hashmap și construiesc o structură de tip ELEMENT
*/
ELEMENT construct(char *string)
{
    int i = 0;
    char *token = NULL;
    char **sentence = (char**) malloc(100 * sizeof(char*)); // Allocate memory for array of pointers
        
    token = strtok(string, ",");
    while(token != NULL)
    {
        sentence[i] = (char*)malloc((strlen(token) + 1) * sizeof(char)); // Allocate memory for each string
        strcpy(sentence[i], token);
        i ++;
        token = strtok(NULL, ",");
    }

    ELEMENT element;
    element.sequence = (char*) malloc((strlen(sentence[0]) + 1) * sizeof(char));
    strcpy(element.sequence, sentence[0]);
    element.priority = atoi(sentence[1]);
    element.module = atoi(sentence[2]);
    element.paragraph = atoi(sentence[3]);

    // Free allocated memory for each string
    for (int j = 0; j < i; j++) 
    {
        free(sentence[j]);
    }
    // Free memory for array of pointers
    free(sentence);

    return element;
}

/*
    ? formez array-ul cu toate structurile de tip ELEMENT din Hashmap
*/

void create_keylist(char *fileName, ELEMENT *keylist, int *nrElements)
{
    char *header = (char*) malloc(1000 * sizeof(char));
    char *string = (char*) malloc(1000 * sizeof(char));

    if((fin = fopen(fileName, "rt")) == NULL)
    {
        printf("Deschidere esuata!\n");
        exit(1);
    }

    fgets(header, 50, fin);
    free(header);
    while(!feof(fin))
    {
        fgets(string, 50, fin);
        ELEMENT element = construct(string);
        (*nrElements) ++; 
        keylist = (ELEMENT*) realloc(keylist, *nrElements * sizeof(ELEMENT));
        keylist[*nrElements - 1] = edge; 
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
    ** criteriul de comparatie prin care voi sorta crescător lista rezultatelor în ordinea următoare:
        1. prioritate
        2. string
        3. modul
        4. paragraf
*/
int comp(ELEMENT a, ELEMENT b)
{
    return (a.priority < b.priority) 
    ||
    (
        (a.priority == b.priority) &&
        strcmp(a.sequence, b.sequence) < 0
    ) 
    ||
    (
        (a.priority == b.priority) &&
        strcmp(a.sequence, b.sequence) == 0 &&
        (a.module < b.module)
    )
    ||
    (
        (a.priority == b.priority) &&
        strcmp(a.sequence, b.sequence) == 0 &&
        (a.module == b.module) &&
        (a.paragraph < b.paragraph)
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
    int n = strlen(text); 
    int m = strlen(pattern); 
    int **distance = (int**) calloc((m + 1) * sizeof(int*));
    int i, j;

    /*
        ? mutarea stringurilor cu o unitate la dreapta
    */
    strcpy(text + 1, text);
    strcpy(pattern + 1, pattern);

    for(i = 0; i <= m; i ++)
        distance[i] = (int*) calloc((n + 1) * sizeof(int));

    for(i = 0; i <= m; i ++)
        distance[i][0] = i;
    
    for(j = 0; j <= n; j ++)
        distance[0][j] = j;

    int substitutionCost;
    for(i = 1; i <= m; i ++)
        for(j = 1; j <= n; j ++)
        {
            if(pattern[i] != text[j])
                substitutionCost = 1;
            else
                substitutionCost = 0;

            distance[i][j] = minim(
                    minin(
                        distance[i - 1][j] + 1,
                        distance[i][j - 1] + 1
                    ),
                    distance[i - 1][j - 1] + substitutionCost;
            )
        }
    
    /*
        ? resetarea stringurilor la poziția inițială
    */
    strcpy(text, text + 1);
    strcpy(pattern, pattern + 1);

    int result = distance[m][n];
    for(i = 0; i <= m; i ++)
        free(distance[i]);
    free(distance);

    return result;
}


void create_resultlist(char *input, ELEMENT *keylist, int sizeKeylist, ELEMENT *results, int *nrResults)
{
    int dist_minim = INT_MAX;
    *nr_results = 0;
    results = NULL;
    int i;
    for(i = 0; i < sizeKeylist; i ++)
        dist_min = minim(dist_min, Levenshtein_distance(input, keylist[i].sequence));

    for(i = 0; i < sizeKeylist; i ++)
        if(Levenshtein_distance(input, keylist[i].sequence) == dist_min)
        {
            *nrResults = *nrResults + 1;
            results = (ELEMENT*) realloc(results, *nrResults * sizeof(ELEMENT));
            results[*nrResults - 1] = keylist[i];
        }
    
    mergesort(results, nrResuts, sizeof(ELEMENT), comp);
}


/*
    TODO apelarea funcției create_keylist cu fileName = "wordlist.csv" pentru a obține array-ul *keylist de dimensiune nrElements
    TODO preluarea cuvântului input din Python și apelarea sa în funcția create_resultlist pentru a obține array-ul *resultlist de dimensiune nrResults
    TODO extragerea datelor de localizare pentru returnarea paragrafului dorit
*/