#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char **words;
int word_count = 0;
int current_index = 0;

int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

void *print_vowels(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (current_index >= word_count) {   
            pthread_mutex_unlock(&mutex);
            break;
        }
        if (is_vowel(words[current_index][0])) {
            printf("Vowel: %s\n", words[current_index]);
            current_index++;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *print_consonants(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (current_index >= word_count) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        if (!is_vowel(words[current_index][0])) {
            printf("Consonant: %s\n", words[current_index]);
            current_index++;
        }
        pthread_mutex_unlock(&mutex);
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
    pthread_create(&cons_thread, NULL, print_consonants, NULL);
    pthread_join(vow_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}