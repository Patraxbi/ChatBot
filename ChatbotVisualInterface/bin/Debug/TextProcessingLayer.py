import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import ctypes
import sys

paragraph_number=3

docs_path = ".\\documents\\module_docs\\"
docs_table={
    0:docs_path+"Introduction.txt",
    1:docs_path+"MODULE 1 CLIMATE CHANGE.txt",
    2:docs_path+"MODULE 2 GREEN ENERGY.txt",
    3:docs_path+"MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt",
    4:docs_path+"MODULE 4 GREEN AGRICULTURE.txt",
    5:docs_path+"MODULE 5 BIODIVERSITY.txt",
    6:docs_path+"MODULE 6 ZERO POLLUTION.txt"
}


# Element class that matches the ELEMENT struct from fuzzy_search.h
class Element(ctypes.Structure):
    _fields_ = [('sequence', ctypes.c_char_p),
                ('priority', ctypes.c_uint),
                ('modul', ctypes.c_uint),
                ('paragraph', ctypes.c_uint)]

def display_paragraph(document, paragraph):
    if not(document in docs_table):
        print("The requested paragraph could not be found in any module.")
        return

    module_file=open(docs_table[document])
    lines=module_file.readlines()
    # indexing starts at 0, but the line numbering starts at 1, so we have to compensate
    return lines[paragraph+1]

# Main function accessed by interface layer
def text_processing_layer(question: str)->list[str]:
    
    # adaug la lista de date subfolderul din directorul proiectului, ca să am toate datele pre-descărcate
    (nltk.data.path).insert(0, ".\\TextProcessingLayer\\nltk_data")
    stop_words_set = set(stopwords.words('english'))
    question_set=word_tokenize(question)

    filtered_question= { w for w in question_set if not w.lower() in stop_words_set}
    #acum am query-ul fără cuvintele de legătură/cuvintele fără prea multă importanță semantică

    #adaug și forma lemmatizată la query
    wnl = WordNetLemmatizer()
    word_lemmas = set()
    for words in filtered_question:
        lemma = wnl.lemmatize(words)
        if words != lemma:
            word_lemmas.add(lemma)
    
    filtered_question=filtered_question.union(word_lemmas)

    test=ctypes.CDLL(".\\fuzzy_search.dll")
    
    result_driver=test.result_driver
    free_mem=test.free_mem
    result_driver.argtypes=[ctypes.c_char_p]
    result_driver.restype=ctypes.POINTER(Element)

    elements_found=ctypes.c_int32()

    # the appearances dictionary uses as its key a tuple of the position of the relevant paragraph 
    # the value is the number of times said paragraph is references throughout the query
    appeareances_dict = dict()

    # I iterate over all of the elements in the filtered_question set, find out their position in the document(s)
    # And add those positions to my set
    for query in filtered_question:
        output_test=result_driver(query.encode('utf-8'), ctypes.byref(elements_found))
        for i in range(0,elements_found.value):
            temp_element=(output_test[i].priority, output_test[i].modul, output_test[i].paragraph)
            if temp_element in appeareances_dict:
                appeareances_dict[temp_element]=appeareances_dict[temp_element]+1
            else:
                appeareances_dict[temp_element]=1
        free_mem(output_test)

    # sorting the dictionary using a lambda function
    appeareances_dict={k: v for k, v in sorted(appeareances_dict.items(), key=lambda item: item[1], reverse=True)}

    #this list contains a tuple containing the paragraph location, as well as the value
    appeareances_list=[(k,v) for k,v in appeareances_dict.items()]
    paragraph_list:list[str] = []
    for i in range(paragraph_number):
        # the 0 selects for the inner tuple
        paragraph_list.append(display_paragraph(appeareances_list[i][0][1], appeareances_list[i][0][2]))
    
    return paragraph_list

# string in "" for command line argument
question: str = sys.argv[1]
answers = text_processing_layer(question)
for line in answers:
    print(line)