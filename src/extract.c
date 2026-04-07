#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 3000
#define WORD_LEN 6

char words[MAX_WORDS][WORD_LEN];
int nb_words = 0;

int comparer(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

void load_words(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier\n");
        return;
    }
    char token[100];
    while (fscanf(f, "%s", token) == 1) {
        if (strlen(token) == 5) {
            int valide = 1;
            for (int i = 0; i < 5; i++) {
                if (!isalpha(token[i])) {
                    valide = 0;
                    break;
                }
                token[i] = tolower(token[i]);
            }
            if (valide) {
                strcpy(words[nb_words], token);
                nb_words++;
            }
        }
    }
    fclose(f);
}

int main() {
    load_words("ressource/bdd_wordle.txt");
    qsort(words, nb_words, WORD_LEN, comparer);

    FILE *out = fopen("ressource/mots.txt", "w");
    for (int i = 0; i < nb_words; i++) {
        fprintf(out, "[%d] %s\n", i + 1, words[i]);
    }
    fclose(out);

    printf("%d mots extraits dans ressource/mots.txt\n", nb_words);
    return 0;
}
