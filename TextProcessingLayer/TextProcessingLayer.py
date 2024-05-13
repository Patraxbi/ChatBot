# TODO: rewrite all the comments in english
import random
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import os
import ctypes

# Element class that matches the ELEMENT struct from fuzzy_search.h
class Element(ctypes.Structure):
    _fields_ = [('sequence', ctypes.c_char_p),
                ('priority', ctypes.c_uint),
                ('modul', ctypes.c_uint),
                ('paragraph', ctypes.c_uint)]

# Main function accessed by interface layer
def text_processing_layer(question: str):
    
    # adaug la lista de date subfolderul din directorul proiectului, ca să am toate datele pre-descărcate
    (nltk.data.path).insert(0,os.getcwd()+"\\TextProcessingLayer\\nltk_data")
    print(os.getcwd())
    # print(nltk.data.path)
    stop_words_set = set(stopwords.words('english'))
    question_set=word_tokenize(question)

    filtered_question= { w for w in question_set if not w.lower() in stop_words_set}

    #acum am query-ul fără cuvintele de legătură/cuvintele fără prea multă importanță semantică

    #adaug și forma lemmatizată la query
    wnl = WordNetLemmatizer()
    #print(type(filtered_question))
    word_lemmas = set()
    for words in filtered_question:
        lemma = wnl.lemmatize(words)
        # print(words + " -> " + lemma)
        if words != lemma:
            word_lemmas.add(lemma)
    
    # print(word_lemmas)
    filtered_question=filtered_question.union(word_lemmas)
    # print(filtered_question)

    # possibly unnecesarry
    #file_output = open('TextProcessingLayer/temp/filtered_words', 'w')
    
    # acum introducem setul de cuvinte într-un fișier temporar    
    # sunt nevoit sa fac asa pentru că altfel nu mi le pune pe linii diferite
    #for word in filtered_question:
    #    file_output.write(word)
    #    file_output.write('\n')


    # după ce va fi implementată partea de C, o să și sterg fișierul ăsta temporar
    #file_output.close()
    #os.remove("temp/filtered_words")

    



text_processing_layer("This is a programmer and a bug building kites babies dogs")