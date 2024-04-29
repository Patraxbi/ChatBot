import random
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize


# adaug la lista de date subfolderul din directorul proiectului, ca să am toate datele pre-descărcate
(nltk.data.path).insert(0,"nltk_data")
print(nltk.data.path)


# Main function accessed by interface layer
def text_processing_layer(question: str):
    nltk.download('stopwords')
    