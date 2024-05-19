from nltk.data import path
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer

# Main function accessed by interface layer
def text_processing_layer(question: str)->str:
    
    # adaug la lista de date subfolderul din directorul proiectului, ca să am toate datele pre-descărcate
    path.insert(0,"nltk_data")
    stop_words_set = set(stopwords.words('english'))
    question_set = word_tokenize(question)

    filtered_question= { w.lower() for w in question_set if not w.lower() in stop_words_set }
    #acum am query-ul fără cuvintele de legătură/cuvintele fără prea multă importanță semantică

    #adaug și forma lemmatizată la query
    wnl = WordNetLemmatizer()
    word_lemmas = set()
    for words in filtered_question:
        lemma = wnl.lemmatize(words)
        word_lemmas.add(lemma)
    
    answer:str = word_lemmas.pop()
    return answer