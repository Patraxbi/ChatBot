#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "gabi-patrascu-nu-ma-uita.h"

int isgoodword(char word[]) {
    if (strcmp(word, "the") == 0 || strcmp(word, "The") == 0 || strcmp(word, "a") == 0 || strcmp(word, "A") == 0 ||
        strcmp(word, "an") == 0 || strcmp(word, "An") == 0 || strcmp(word, "and") == 0 || strcmp(word, "And") == 0 ||
        strcmp(word, "or") == 0 || strcmp(word, "Or") == 0 || strcmp(word, "but") == 0 || strcmp(word, "But") == 0 ||
        strcmp(word, "for") == 0 || strcmp(word, "For") == 0 || strcmp(word, "nor") == 0 || strcmp(word, "Nor") == 0 ||
        strcmp(word, "so") == 0 || strcmp(word, "So") == 0 || strcmp(word, "yet") == 0 || strcmp(word, "Yet") == 0 ||
        strcmp(word, "after") == 0 || strcmp(word, "After") == 0 || strcmp(word, "although") == 0 ||
        strcmp(word, "Although") == 0 || strcmp(word, "as") == 0 || strcmp(word, "As") == 0 ||
        strcmp(word, "because") == 0 || strcmp(word, "Because") == 0 || strcmp(word, "before") == 0 ||
        strcmp(word, "Before") == 0 || strcmp(word, "if") == 0 || strcmp(word, "If") == 0 ||
        strcmp(word, "since") == 0 || strcmp(word, "Since") == 0 || strcmp(word, "though") == 0 ||
        strcmp(word, "Though") == 0 || strcmp(word, "unless") == 0 || strcmp(word, "Unless") == 0 ||
        strcmp(word, "until") == 0 || strcmp(word, "Until") == 0 || strcmp(word, "when") == 0 ||
        strcmp(word, "When") == 0 || strcmp(word, "where") == 0 || strcmp(word, "Where") == 0 ||
        strcmp(word, "while") == 0 || strcmp(word, "While") == 0 || strcmp(word, "who") == 0 ||
        strcmp(word, "Who") == 0 || strcmp(word, "which") == 0 || strcmp(word, "Which") == 0 ||
        strcmp(word, "whom") == 0 ||
        strcmp(word, "Whom") == 0 || strcmp(word, "whose") == 0 || strcmp(word, "Whose") == 0 ||
        strcmp(word, "that") == 0 ||
        strcmp(word, "That") == 0 || strcmp(word, "what") == 0 || strcmp(word, "What") == 0 ||
        strcmp(word, "where") == 0 ||
        strcmp(word, "Where") == 0 || strcmp(word, "when") == 0 || strcmp(word, "When") == 0 ||
        strcmp(word, "why") == 0 || strcmp(word, "Why") == 0 || strcmp(word, "how") == 0 || strcmp(word, "How") == 0 ||
        strcmp(word, "if") == 0 ||
        strcmp(word, "If") == 0 || strcmp(word, "whether") == 0 || strcmp(word, "Whether") == 0 ||
        strcmp(word, "while") == 0 || strcmp(word, "While") == 0 || strcmp(word, "which") == 0 ||
        strcmp(word, "Which") == 0 ||
        strcmp(word, "who") == 0 || strcmp(word, "Who") == 0 || strcmp(word, "whose") == 0 ||
        strcmp(word, "Whose") == 0 ||
        strcmp(word, "whom") == 0 || strcmp(word, "Where") == 0 || strcmp(word, "why") == 0 ||
        strcmp(word, "Why") == 0 ||
        strcmp(word, "how") == 0 || strcmp(word, "How") == 0 || strcmp(word, "as") == 0 || strcmp(word, "As") == 0 ||
        strcmp(word, "after") == 0 ||
        strcmp(word, "After") == 0 || strcmp(word, "although") == 0 || strcmp(word, "Although") == 0 ||
        strcmp(word, "because") == 0 || strcmp(word, "Because") == 0 || strcmp(word, "before") == 0 ||
        strcmp(word, "Before") == 0 || strcmp(word, "since") == 0 || strcmp(word, "Since") == 0 ||
        strcmp(word, "though") == 0 || strcmp(word, "Until") == 0 || strcmp(word, "when") == 0 ||
        strcmp(word, "When") == 0 ||
        strcmp(word, "where") == 0 || strcmp(word, "Where") == 0 || strcmp(word, "while") == 0 ||
        strcmp(word, "While") == 0 ||
        strcmp(word, "who") == 0 || strcmp(word, "-") == 0 || strcmp(word, "high") == 0 ||
        strcmp(word, "low") == 0 || strcmp(word, "medium") == 0 || strcmp(word, "small") == 0 ||
        strcmp(word, "High") == 0 || strcmp(word, "higher") == 0 || strcmp(word, "huge") == 0) {
        return 0;
    }
    ///aici vin exceptiile
    if (strcmp(word, "EU") == 0 || strcmp(word, "eu") == 0) {
        return 1;
    }
    if (strlen(word) < 4) {
        return 0;
    }
    return 1;
}

int isthewordinside(char word[], char text[]) {
    ///aici am nevoie de functia lui David de aproximat din cauza comparatiei textului UTF-8 cu ASCII
    char *p = strstr(text, word);
    if (p) {
        return 1;
    }
    return 0;
}

int main(void) {
    setlocale(LC_ALL, "");
    FILE *output = fopen("hashmap.txt", "wt");
    if (output == NULL) {
        printf("File not found\n");
        exit(-1);
    }

    FILE *txt = fopen("Introduction.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    FILE *xml = fopen("document.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }


    char line[10000];
    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    int important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("Introduction.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/
                if (isthewordinside(content, txtparagraph)) {
                    /*printf("Cuvantul < %s > a fost gasit in text\n", content);
                    printf("Importanta secventei e:%d\n", important);
                    printf("Acesta se afla in paragraful %d\n\n", paragraph);*/

                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d, Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 0, paragraph);*/
                    /// bagam pe cuvinte

                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 0, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("Introduction.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 0, paragraph);
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
    printf("\n\nAcum modulul 1\n\n");

    ///modul 1

    txt = fopen("MODULE 1 CLIMATE CHANGE.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod1.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 1 CLIMATE CHANGE.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/
                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/
                    ///bagam in hash pe cuvinte

                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 1, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 1 CLIMATE CHANGE.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 1, paragraph);
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
    printf("\n\nAcum modulul 2\n\n");

    ///modul 2

    txt = fopen("MODULE 2 GREEN ENERGY.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod2.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        /// mai merge si 28
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 2 GREEN ENERGY.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/
                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/
                    ///bagam in hash pe cuvinte

                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 2, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 2 GREEN ENERGY.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 2, paragraph);
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
    printf("\n\nAcum modulul 3\n\n");

    ///modul 3

    txt = fopen("MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod3.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/

                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/

                    ///bagam in hash pe cuvinte
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 3, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 3 INDUSTRIAL STRATEGY FOR CIRCULAR ECONOMY.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 3, paragraph);
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
    printf("\n\nAcum modulul 4\n\n");

    ///modul 4

    txt = fopen("MODULE 4 GREEN AGRICULTURE.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod4.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 4 GREEN AGRICULTURE.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/

                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/

                    ///bagam in hash pe cuvinte
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 4, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL CA LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 4 GREEN AGRICULTURE.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 4, paragraph);
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
    printf("\n\nAcum modulul 5\n\n");

    ///modul 5

    txt = fopen("MODULE 5 BIODIVERSITY.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod5.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 5 BIODIVERSITY.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/

                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/

                    ///bagam in hash pe cuvinte
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 5, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL CA LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 5 BIODIVERSITY.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 5, paragraph);
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
    printf("\n\nAcum modulul 6\n\n");

    ///modul 6

    txt = fopen("MODULE 6 ZERO POLLUTION.txt", "rt");
    if (txt == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    xml = fopen("document_mod6.xml", "rt");
    if (xml == NULL) {
        printf("File not found\n");
        exit(-1);
    }



    /// scapam de titlu sau modul
    while (fgets(line, 10000, xml) != NULL) {
        if (isthewordinside("Title", line)) {
            break;
        }
        if (isthewordinside("MODULE", line)) {
            break;
        }
    }
    ///pentru fiecare cuvant din xml cautam
    important = 0;
    while (fgets(line, 10000, xml) != NULL) {

        ///<w:sz w:val="32"/> asta e nenorocitu de font de titlu
        ///importanta=3 pt titlu
        ///<w:sz w:val="28"/> asta e de content normal
        ///importanta=0 pt content normal
        /// ///<w:i/> asta e italicul
        ///importanta=2 pt italic
        ///<w:b/> asta e boldul
        ///importanta=1 pt bold

        if (important == 1 || important == 2) {
            ///aici se termina boldul si italicul
            if (isthewordinside("</w:r>", line)) {
                important = 0;
            }
        }


        if (isthewordinside("<w:sz w:val=\"32\"/>", line) || isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            /// e titlu
            important = 3;
        }
        if (isthewordinside("<w:i/>", line)) {
            /// e italic
            if (important < 2) {
                important = 2;
            }
        } else if (isthewordinside("<w:b/>", line)) {
            if (important < 2) {
                important = 1;
            }
            /// e bold
        }
        if (important == 3 && isthewordinside("<w:sz w:val=\"28\"/>", line)) {
            important = 0;
            ///devine content normal
        }

        ///aici luam secventa/cuvantul cheie=content

        if (isthewordinside("<w:t>", line)) {
            char *content = &line[5];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {
                /*printf("\nSecventa e:%s\n", content);
                printf("Importanta secventei e:%d\n\n", important);*/
            } else {
                continue;
            }
            ///acum marea cautare in txt
            fclose(txt);
            txt = fopen("MODULE 6 ZERO POLLUTION.txt", "rt");
            if (txt == NULL) {
                printf("File not found\n");
                exit(-1);
            }
            char txtparagraph[5000];
            int paragraph = 0;

            while (fgets(txtparagraph, 5000, txt) != NULL) {
                paragraph++;
                /*printf("Cautam in: %s\n", txtparagraph);*/

                if (isthewordinside(content, txtparagraph)) {
                    /* printf("Cuvantul < %s > a fost gasit in text\n", content);
                     printf("Importanta secventei e:%d\n", important);
                     printf("Acesta se afla in paragraful %d\n\n", paragraph);*/
                    /*fprintf(output,
                            "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                            content, important, 1, paragraph);*/

                    ///bagam in hash pe cuvinte
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 6, paragraph);
                        }
                        word = strtok(NULL, " ");
                    }
                    break;
                }
            }

        }

        if (isthewordinside("<w:t xml:space=\"preserve\">", line)) {
            ///ASTEA SUNT GEN LA FEL CA LA <w:t> DAR CU SPATII
            char *content = &line[26];
            content[strlen(content) - 7] = '\0';
            if (isgoodword(content)) {

            } else {
                continue;
            }
            fclose(txt);
            txt = fopen("MODULE 6 ZERO POLLUTION.txt", "rt");
            char txtparagraph[1000];
            int paragraph = 0;

            while (fgets(txtparagraph, 1000, txt) != NULL) {
                paragraph++;
                if (isthewordinside(content, txtparagraph)) {
                    char *word = strtok(content, " ");
                    while (word != NULL) {
                        if (isgoodword(word)) {
                            fprintf(output,
                                    "Secventa relevanta este: %s , Importanta secventei e: %d, Modulul este %d,Paragraful este %d, Gabi pe astea tu trebuia sa le faci hash\n",
                                    word, important, 6, paragraph);
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

    fclose(output);
    return 0;
}