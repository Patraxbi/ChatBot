## Text processing layer

The current layer of our Chatbot application handles receiving the request from the C# graphical interface, processing it, passing it to our C function(s), and displaying the relevant paragraph(s).

The Python script uses the following libraries/technologies:
- **NLTK** - in particular, its *tokenize*, *stopwords* and *lemmatizer* functions;
- **ctypes** - for integration with our *fuzzy_search* component;
- **sys** - used for reading command line arguments;

The main function of the script is *text_processing_layer*, which takes in a string containing the search query in question, and returns a list of the relevant paragraph(s) within the educational module(s).

First, the function modifies the list of local paths to NLTK's data (*nltk.data.path*) to include the local *nltk_data* folder. This data is stored locally, in the executable's folder, in order to avoid redownloading it for every function call.
The function takes the *question* string and breaks it up into individual words, or *tokens*; said tokens are then filtered through the *stopwords* set from the *stopwords* NLTK module; this is done in order to remove irrelevant terms that have little to no semantic weight.

Every word in this *filtererd_question* set is then taken throgh NLTK's *lemmatizer*, which returns every word's **lemma**, or **dictionary form**, for easier matching within the search function; every lemma that isn't already present in *filtered_questions* is added to the set.

Afterwards, the program loads our C libraries via the *ctypes* module. Since *ctypes* can only accept dynamic libraries (.dll), our *fuzzy_search.c* and *bitwise_encoding.c* programs are compiled and lumped together into **fuzzy_search.dll**. This is done through GCC, via the following commands:
```
gcc -c fuzzy_search.c bitwise_encoding.c
gcc -shared -o fuzzy_search.dll fuzzy_search.o bitwise_encoding.o
```

**NOTE:** It is *very* important that the C compiler that you use is building for the same architecture as your Python interpreter; otherwise, the program is likely to crash.
The most common C compiler on Windows machines, MinGW, only targets 32-bit architecture; as such, one should reorient themselves towards another compiler. In this project, the C libraries were compiled using a 64-bit fork of MinGW, MinGW64

At this point, the program also initializes the *appearances_dict* dictionary, which will contain a tuple of a paragraph's position, as well as the number of times it is mentioned throughout our query.

Then, for every word in *filtered_questions*, the program invokes the *result_driver* function from *fuzzy_search.c*, whose behavior is described elsewhere. Nonetheless, the function returns a list of **Element** objects, (the **Element** class being an implementation of the *ELEMENT* struct from *fuzzy_search.h*, containing the document in which the paragraph is found and the number of the paragraph within the document), as well as the number of *Element*s found. Every element whose key (Element) not already present in the *appearances_dict* dictionary is added, with its number of appearaces initialized to 1; if the key (element) already exists, its value is incremented.

The elements of the dictionary are then sorted in decreasing order according to their number of appearances; this is done in order to only show the paragraphs with the greatest relevance to the search query. 

The dictionary is then converted into a list, *appearances_list*, so that the elements can be accesed via their index. Since the dictionary has been sorted (something not possible in Python up until relatively recently), the first elements will be the ones with the most appearances. 

For every element in *appearances_list*, the function calls the *display_paragraph* helper function, which returns a string containing the desired paragraph within the desired document. 

The *display_paragraph* function is simple: First, it matches the *document* value to the filename of the relevant document via a predefined lookup table. It then opens said file, looks for the *paragraph*-th line of the file, which it then returns. 

All of the paragraphs are added to a list called *paragraph_list*, which the function then returns.

This function is initialized via some **driver code**: the program reads the command line arguments and stores them in *question*, with which it calls the *text_processing_layer*; the resulting output is printed to the console.

The program used the following data structures:
- **sets** - used for the sets of input words, stop words, and word lemmas;
- **lists/arrays** - used for the list of paragraph positions;
- **dictionaries** - used to match a paragraph with its number of occurences during the query, as well as to match the *document* variable to the relevant filename in the *display_paragraph* function;
- **structs** - used to implement the ELEMENT struct from fuzzy_search.h;