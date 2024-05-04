import random
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import os

# Main function accessed by interface layer
def text_processing_layer(question: str):
    
    # adaug la lista de date subfolderul din directorul proiectului, ca să am toate datele pre-descărcate
    (nltk.data.path).insert(0,"nltk_data")
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

    file_output = open('temp/filtered_words', 'w')
    # acum introducem setul de cuvinte într-un fișier temporar    
    # sunt nevoit sa fac asa pentru că altfel nu mi le pune pe linii diferite
    for word in filtered_question:
        file_output.write(word)
        file_output.write('\n')


    # după ce va fi implementată partea de C, o să și sterg fișierul ăsta temporar
    file_output.close()
    #os.remove("temp/filtered_words")



text_processing_layer("This is a programmer and a bug building kites babies dogs")