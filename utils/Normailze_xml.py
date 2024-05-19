TARGET_DIRECTORY = "documents"
TARGET_FILE_NAMES = [
    "document.xml", 
    "document_mod1.xml", 
    "document_mod2.xml", 
    "document_mod3.xml", 
    "document_mod4.xml", 
    "document_mod5.xml", 
    "document_mod6.xml"
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
    inputFile = open(TARGET_DIRECTORY + "\\" + filename, "rt", encoding = "utf-8")
    outputFile = open("norm\\" + filename, "wt", encoding = "utf-8")
    
    # same issue as in txt
    for line in inputFile:
        # filter for text lines
        if line.startswith("<w:t"):
            outputFile.write("<w:t>") 
            line = line[(line.find('>') + 1) : -7]
            # as a convenient side-effect, this turns floating <w:t xml:space="preserve"> tags into basic <w:t>, 
            # easier for the C program to parse
            for word in line.split():
                word = normalize(word)
                if word:
                    outputFile.write(word + ' ')
            outputFile.write("</w:t>\n")
        else:
            # leave format tags intact
            outputFile.write(line)

    inputFile.close()
    outputFile.close()




