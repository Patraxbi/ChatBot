TARGET_DIRECTORY = "module_docs"
TARGET_FILE_NAMES = [
    "Introduction.txt", 
    "MODULE 1 CLIMATE CHANGE.txt", 
    "MODULE 2 GREEN ENERGY.txt", 
    "MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt", 
    "MODULE 4 GREEN AGRICULTURE.txt", 
    "MODULE 5 BIODIVERSITY.txt", 
    "MODULE 6 ZERO POLLUTION.txt"
]

import string
import re as regex
from pattern.text.en import singularize
from nltk.stem.wordnet import WordNetLemmatizer

def normalize(word: str) -> str:
    """
    Strip formatting and find root of given word
    """
    word = word.lower()

    # remove punctuation at the end
    word = word.translate(str.maketrans("", "", string.punctuation))
    
    # remove contraction
    word = regex.sub("\'.*", "", word)

    word = singularize(word)

    # check every part of speech
    noun = WordNetLemmatizer().lemmatize(word, 'n')
    if word != noun:
        return noun

    verb = WordNetLemmatizer().lemmatize(word, 'v')
    if word != verb:
        return verb

    adjective = WordNetLemmatizer().lemmatize(word, 'a')
    if word != adjective:
        return adjective

    adverb = WordNetLemmatizer().lemmatize(word, 'r')
    if word != adverb:
        return adverb
    
    return WordNetLemmatizer().lemmatize(word, 's')


for filename in TARGET_FILE_NAMES:
    inputFile = open(TARGET_DIRECTORY + "\\" + filename, "rt")
    outputFile = open(TARGET_DIRECTORY + "\\norm\\" + filename, "wt")

    for line in inputFile:
        """
        Here is something interesting:

        line = regex.sub('-', ' ', line)
        
        It would split compound words for normalization.
        This does not really work because we have neologisms like "e-learning" and "e-forms" 
        that can't be normalized by nltk.
        But we also have "self-assessment" and "target-groups" that sould be normalized as separate words
        Hope you figure something out! :)
        """
        for word in line.split():
            word = normalize(word)
            if word:
                outputFile.write(word + ' ')
        outputFile.write('\n')
    
    inputFile.close()
    outputFile.close()