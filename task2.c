#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char **words;
int word_count = 0;

int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

void *print_vowels(void *arg) {
    for (int i = 0; i < word_count; i++) {
        if (is_vowel(words[i][0])) {
            printf("Vowel: %s\n", words[i]);
        }
    }
    return NULL;
}

void *print_consonants(void *arg) {
    for (int i = 0; i < word_count; i++) {
        if (!is_vowel(words[i][0])) {
            printf("Consonant: %s\n", words[i]);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word1> <word2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    word_count = argc - 1;
    words = &argv[1];

    pthread_t vow_thread, cons_thread;
    pthread_create(&vow_thread, NULL, print_vowels, NULL);
    pthread_join(vow_thread, NULL);
    pthread_create(&cons_thread, NULL, print_consonants, NULL);
    pthread_join(cons_thread, NULL);

    return EXIT_SUCCESS;
}