# TODO: rewrite all the comments in english
import random
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import os
from ctypes import *
import ctypes

lookup_table={

}
# Element class that matches the ELEMENT struct from fuzzy_search.h
class Element(ctypes.Structure):
    _fields_ = [('sequence', ctypes.c_char_p),
                ('priority', ctypes.c_uint),
                ('modul', ctypes.c_uint),
                ('paragraph', ctypes.c_uint)]

def display_paragraph(document, paragraph):
    print("tessst")

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


    print(os.getcwd()+"\\fuzzy_search.dll")

    test=CDLL(os.getcwd()+"\\fuzzy_search.dll")
    
    result_driver=test.result_driver

    result_driver.argtypes=[ctypes.c_char_p]
    result_driver.restype=ctypes.POINTER(Element)

    elements_found=ctypes.c_int32()

    # the appearances dictionary uses as its key a tuple of the position of the relevant paragraph 
    # the value is the number of times said paragraph is references throughout the query
    appeareances_dict = dict()

    # I iterate over all of the elements in the filtered_question set, find out their position in the document(s)
    # And add those positions to my set
    for query in filtered_question:
        output_test=result_driver(query.encode('utf-8'), byref(elements_found))
        for i in range(0,elements_found.value):
            print(output_test[i].sequence, end=' ')
            print(output_test[i].priority, end=' ')
            print(output_test[i].modul, end=' ')
            print(output_test[i].paragraph)
            
            temp_element=(output_test[i].priority, output_test[i].modul, output_test[i].paragraph)
            if temp_element in appeareances_dict:
                appeareances_dict[temp_element]=appeareances_dict[temp_element]+1
            else:
                appeareances_dict[temp_element]=1
        
    print(appeareances_dict)
    '''
    output_test=result_driver("test".encode('utf-8'), byref(elements_found))
    for i in range(0,elements_found.value):
        print(output_test[i].sequence, end=' ')
        print(output_test[i].priority, end=' ')
        print(output_test[i].modul, end=' ')
        print(output_test[i].paragraph)
        
        temp_element=(output_test[i].priority, output_test[i].modul, output_test[i].paragraph)
        element_set.add(temp_element)
    print(element_set)
    '''
    # după ce va fi implementată partea de C, o să și sterg fișierul ăsta temporar
    #file_output.close()
    #os.remove("temp/filtered_words")

    




text_processing_layer("agriculture")