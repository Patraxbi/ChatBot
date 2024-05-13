# fuzzy_search.c
>1. The code's fundamental data structures are **ELEMENT**, where we keep a line from the HashMap file (named *wordlist.csv*) (the string **sequence**, the *bitwise* **priority**, the *bitwise* **modul** and the *bitwise* **paragraph**), and its encoded version **CRYPTO**, where the parameters **modul**, **paragraph** and **priority** are encoded in the bitwise **encoded** (the ***construct*** function converts the string line from the HashMap file into an **CRYPTO** structure).
>2. Through the ***create_keylist*** function we generate the *keylist* array with *nrElements* data units of **CRYPTO** type.
>3. To decide how close the *input* word is from the one saved in the HashMap file, we will use the *Levenshtein distance*, which is integrated through the function of the same name:
>>- The function will have 2 parameters:  
>>>1. the *pattern* string with *m* characters;
>>>2. the *text* string with *n* characters.
>>>
>>>(the strings must be counted from *1* to *strlen(*string*)*, because we need to save separate memory for the initial version of the string)
>>- we will generate the *distance* matrix with *m + 1* lines and *n + 1* columns, where every unit is initialized with *0*;
>>- for the first column: *distance[i][0] = i; (i goes from 1 to m)*
>>- for the first line: *distance[0][j] = j; (j goes from 1 to n)*
>>- for every other unit, we will determine the minimum cost of the changes through the 3 fundamental operations:
>>>1. Deletion (*co**a**t* --> *cot*);
>>>2. Insertion (*cot* --> *co**a**t*);
>>>3. Substitution (*co**a**t* --> *co**s**t*).
>>- we define the *substitutionCost* value, which is: 1 if pattern[i] != text[j] or 0 otherwise
>>*distance[i][j]* = minimum between:
>>>>*distance[i - 1][j] + 1* (**deletion**);
>>>>
>>>>*distance[i][j - 1] + 1* (**insertion**);
>>>>
>>>>*distance[i - 1][j - 1] + substitutionCost* (**substitution**);
>>
>>- the *Levenshtein distance* between the 2 words will be calcuated in the *distance[m][n]* value;
>4. The ***create_resultlist*** function return the *results* array with *nrResults* units of **CRYPTO** type. It will take each unit from the *keylist* array and will generate the *results* array with all the elements from *keylist*, whose *sequence* has the minimum Levenshtein distance to the *input* . Finally, the *results* array is sorted in ascending order using the ***MergeSort*** algoritm in this priority:
>>1. **encoded**;
>>2. **sequence**;
>>
>5. After generating the encrypted *resutltlist*, we convert it into the **ELEMENT** type also in the ***create_resultlist***, to have acces at the localizing parameters(**modul** and **paragraph**).

## The usage of the functions from *fuzzy_search.c* file in the final application:
>1. Use the ***create_keylist*** function to convert the *wordlist.csv* HashMap into an **CRYPTO** array;
>2. Use the ***create_resultlist*** function to obtain an result array with the closest words to the *input* word;
>3. Extract the localizing data (**module** and **paragraph**) for returning the wanted paragraphs after priority, alphabetical order and location.
>4. In case of an *input* with 2 or more words, split the *input* string into individual words, use the ***create_resultlist*** function for each word and keep only the **ELEMENT** structures from each *result* array with identical localizing data (the **modul** and **paragraph** must be equal in different *result* arrays)

## Restrictions:
>- the lines in the HashMap cannot be longer than 1000 characters.