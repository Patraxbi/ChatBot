# ChatBot
>
>- Fișierul sursă fuzzy_search.c
>>1. Stuctura de bază a codului este **ELEMENT**, în care reținem o linie din Hashmap (string-ul **sequence**, int-ul **priority**, int-ul **module** și int-ul **paragraph**) (pe care o prelucrăm în structura **ELEMENT** prin funcția ***construct***)
>>2. În funcția ***create_keylist***, preluăm elementele din Hashmap (fișierul *wordlist.csv*) și generăm tabloul *keylist* cu *nrElements* unități de tipul **ELEMENT**.
>>3. Funcția ***Levenshtein_distance***, ce îmi returnează distanța Levenshtein dintre 2 string-uri (distanța Levenshtein reprezintă prioritatea în aproximarea cuvântului primit din codul Python cu cele din Hashmap, distanța mai mică reprezentând o potrivire mai bună a celor 2 string-uri):
>>>- Funcția are 2 parametri: 
>>>>1. string-ul *pattern* de lungime *m*;
>>>>2. string-ul *text* de lungime *n*.
>>>>
>>>>(string-urile trebuie să fie numerotate de la *1* la *m*, respectiv de la *1* la *n*)
>>>- generăm o matrice *distance* cu *m + 1* linii și *n + 1* coloane, unde toate elementele sunt inițializate cu *0*;
>>>- pentru prima coloană: *distance[i][0] = i; (i de la 1 la m)*
>>>- pentru prima linie: *distance[0][j] = j; (j de la 1 la n)*
>>>- pentru toate celelalte elemente trebuie să ținem cont de cele 3 operații prin care ajungem de la primul string la al doilea string:
>>>>1. Ștergere (*co**a**t* --> *cot*);
>>>>2. Inserate (*cot* --> *co**a**t*);
>>>>3. Substituție (*co**a**t* --> *co**s**t*).
>>>- definim variabila *substitutionCost*, care la fiecare iterație este: 1 dacă pattern[i] != text[j] sau 0 în caz contrar
>>>*distance[i][j]* = minim dintre:
>>>>>*distance[i - 1][j] + 1* (pentru operația de ștergere);
>>>>>
>>>>>*distance[i][j - 1] + 1* (pentru operația de inserare);
>>>>>
>>>>>*distance[i - 1][j - 1] + substitutionCost* (pentru operația de substituție);
>>>
>>>- distanța Levenshtein va fi dată de valoarea *distance[m][n]*, fiind generată prin programare dinamică prin parcurgerea top-bottom a matricei *distance*;
>>4. Funcția ***create_resultlist*** returnează tabloul *results* cu *nrResults* unități de tip **ELEMENT**. Parcurge toate elementele din *keylist* și va genera tabloul *results* cu toate elementele din *keylist*, a căror *sequence* are distanța Levenshtein minimă față de string-ul introdus. La final, tabloul *results* este sortat crescător prin ***MergeSort*** în următoarea ordine:
>>>1. crescător după **priority**;
>>>2. alfabetic crescător după **sequence**;
>>>3. crescător după **module**;
>>>4. crescător după **paragraph**;

## Modul de apelare a funcțiilor din *fuzzy_search.c* la încorporarea lor în program:
>1. apelați funcția ***create_keylist*** pentru a prelucra datele din *wordlist.csv* într-un tablou unidimensional de tip **ELEMENT**;
>2. apelați funcția ***create_resultlist*** pentru a obține un tablou unidimensional cu cele mai apropiate cuvinte de *input*;
>3. extragerea datelor de localizare (**module** și **paragraph**) pentru returnarea paragrafelor dorite după prioritate, ordine alfabetică și localizare.