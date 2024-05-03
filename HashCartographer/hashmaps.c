#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gabi-patrascu-nu-ma-uita.h"

const char MODULE_DIRECTORY_PATH[100] = "module_docs\\norm\\";

const char MODULE_TXT_NAMES[7][100] = {
    "Introduction.txt", 
    "MODULE 1 CLIMATE CHANGE.txt", 
    "MODULE 2 GREEN ENERGY.txt", 
    "MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt", 
    "MODULE 4 GREEN AGRICULTURE.txt", 
    "MODULE 5 BIODIVERSITY.txt", 
    "MODULE 6 ZERO POLLUTION.txt"
};

const char MODULE_XML_NAMES[7][100] = {
    "document.xml", 
    "document_mod1.xml", 
    "document_mod2.xml", 
    "document_mod3.xml", 
    "document_mod4.xml", 
    "document_mod5.xml", 
    "document_mod6.xml"
};

int isgoodword(char *word) {
    // aici vin exceptiile
    if(strcmp(word, "EU") ==0 || strcmp(word, "eu") == 0)
        return 1;
    if (strlen(word) < 4)
        return 0;

    // toate cuvintele de legatura imagaginabile
    if (
        strcmp(word, "the") == 0 || strcmp(word, "The") == 0 || 
        strcmp(word, "a") == 0 || strcmp(word, "A") == 0 ||
        strcmp(word, "an") == 0 || strcmp(word, "An") == 0 || 
        strcmp(word, "and") == 0 || strcmp(word, "And") == 0 ||
        strcmp(word, "or") == 0 || strcmp(word, "Or") == 0 || 
        strcmp(word, "but") == 0 || strcmp(word, "But") == 0 ||
        strcmp(word, "for") == 0 || strcmp(word, "For") == 0 || 
        strcmp(word, "nor") == 0 || strcmp(word, "Nor") == 0 ||
        strcmp(word, "so") == 0 || strcmp(word, "So") == 0 || 
        strcmp(word, "yet") == 0 || strcmp(word, "Yet") == 0 ||
        strcmp(word, "after") == 0 || strcmp(word, "After") == 0 || 
        strcmp(word, "although") == 0 || strcmp(word, "Although") == 0 || 
        strcmp(word, "as") == 0 || strcmp(word, "As") == 0 ||
        strcmp(word, "because") == 0 || strcmp(word, "Because") == 0 || 
        strcmp(word, "before") == 0 || strcmp(word, "Before") == 0 || 
        strcmp(word, "if") == 0 || strcmp(word, "If") == 0 ||
        strcmp(word, "since") == 0 || strcmp(word, "Since") == 0 || 
        strcmp(word, "though") == 0 || strcmp(word, "Though") == 0 || 
        strcmp(word, "unless") == 0 || strcmp(word, "Unless") == 0 ||
        strcmp(word, "until") == 0 || strcmp(word, "Until") == 0 || 
        strcmp(word, "when") == 0 || strcmp(word, "When") == 0 || 
        strcmp(word, "where") == 0 || strcmp(word, "Where") == 0 ||
        strcmp(word, "while") == 0 || strcmp(word, "While") == 0 || 
        strcmp(word, "who") == 0 || strcmp(word, "Who") == 0 || 
        strcmp(word, "which") == 0 || strcmp(word, "Which") == 0 ||
        strcmp(word, "whom") == 0 || strcmp(word, "Whom") == 0 || 
        strcmp(word, "whose") == 0 || strcmp(word, "Whose") == 0 ||
        strcmp(word, "that") == 0 || strcmp(word, "That") == 0 || 
        strcmp(word, "what") == 0 || strcmp(word, "What") == 0 ||
        strcmp(word, "where") == 0 || strcmp(word, "Where") == 0 || 
        strcmp(word, "when") == 0 || strcmp(word, "When") == 0 ||
        strcmp(word, "why") == 0 || strcmp(word, "Why") == 0 || 
        strcmp(word, "how") == 0 || strcmp(word, "How") == 0 ||
        strcmp(word, "if") == 0 || strcmp(word, "If") == 0 || 
        strcmp(word, "whether") == 0 || strcmp(word, "Whether") == 0 ||
        strcmp(word, "while") == 0 || strcmp(word, "While") == 0 || 
        strcmp(word, "which") == 0 || strcmp(word, "Which") == 0 ||
        strcmp(word, "who") == 0 || strcmp(word, "Who") == 0 || 
        strcmp(word, "whose") == 0 || strcmp(word, "Whose") == 0 ||
        strcmp(word, "whom") == 0 || strcmp(word, "Where") == 0 || 
        strcmp(word, "why") == 0 || strcmp(word, "Why") == 0 ||
        strcmp(word, "how") == 0 || strcmp(word, "How") == 0 || 
        strcmp(word, "as") == 0 || strcmp(word, "As") == 0 ||
        strcmp(word, "after") == 0 || strcmp(word, "After") == 0 || 
        strcmp(word, "although") == 0 || strcmp(word, "Although") == 0 ||
        strcmp(word, "because") == 0 || strcmp(word, "Because") == 0 || 
        strcmp(word, "before") == 0 || strcmp(word, "Before") == 0 || 
        strcmp(word, "since") == 0 || strcmp(word, "Since") == 0 ||
        strcmp(word, "though") == 0 || strcmp(word, "Until") == 0 || 
        strcmp(word, "when") == 0 || strcmp(word, "When") == 0 ||
        strcmp(word, "where") == 0 || strcmp(word, "Where") == 0 || 
        strcmp(word, "while") == 0 || strcmp(word, "While") == 0 ||
        strcmp(word, "who") == 0 || strcmp(word, "-") == 0 ||
        strcmp(word, "High") == 0 || strcmp(word, "high") == 0 || 
        strcmp(word, "low") == 0 || strcmp(word, "medium") == 0 || strcmp(word, "small") == 0 ||
        strcmp(word, "higher") == 0 || strcmp(word, "huge") == 0
    ) return 0;

    return 1;
}

#define isthewordinside(word, text) strstr(text, word) != NULL

void parsemodule(FILE *output, char *input_txt, char *input_xml, int modul)
{
    char line[1500];
    
    FILE *txt = fopen(input_txt, "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    FILE *xml = fopen(input_xml, "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }

    // scapam de titlu sau modul
    while (fgets(line, 1500, xml) != NULL) {
        if (isthewordinside("title", line))
            break;
        if (isthewordinside("module", line))
            break;
    }

    // pentru fiecare cuvant din xml cautam
    int important = 0;
    while (fgets(line, 1500, xml) != NULL) {
        // <w:sz w:val="32"/> asta e nenorocitu de font de titlu
        // importanta=3 pt titlu
        
        // <w:sz w:val="28"/> asta e de content normal
        // importanta=0 pt content normal
        
        // <w:i/> asta e italicul
        // importanta=2 pt italic
        
        // <w:b/> asta e boldul
        // importanta=1 pt bold

        if (important == 1 || important == 2) {
            // aici se termina boldul si italicul
            if (isthewordinside("</w:r", line)) {
                important = 0;
            }
        }
        if (isthewordinside("<w:sz w:val=\"32\"/>", line)) {
            // e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            // e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            // e bold
            if (important < 2) {
                important = 1;
            }
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            //devine content normal
            important = 0;
        }

        // aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (!isgoodword(content))
                continue;
            
            // acum marea cautare in txt
            rewind(txt);
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    // bagam pe cuvinte
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            // secventa, importanta, modulul, paragraful
                            fprintf(output, "%s,%d,%d,%d\n", word, important, modul, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }
        }
    }
    fclose(txt);
    fclose(xml);
}

int main(void) {
    FILE *output = fopen("wordlist.csv", "wt");
    if (output == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    fprintf(output, "SECVENTA,IMPORTANTA,MODUL,PARAGRAF\n");

    for (int modul = 0; modul < 7; modul++) {
        char path_txt[200] = "\0", path_xml[200] = "\0";
        strcat(strcat(path_txt, MODULE_DIRECTORY_PATH), MODULE_TXT_NAMES[modul]);
        strcat(strcat(path_xml, MODULE_DIRECTORY_PATH), MODULE_XML_NAMES[modul]);
        parsemodule(output, path_txt, path_xml, modul);
    }

    fclose(output);
    return 0;
}