#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  
#include <sys/wait.h> 


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
    exit(0);
}

void *print_consonants(void *arg) {
    for (int i = 0; i < word_count; i++) {
        if (!is_vowel(words[i][0])) {
            printf("Consonant: %s\n", words[i]);
        }
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word1> <word2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    word_count = argc - 1;
    words = &argv[1];

    pid_t vow_pid = fork();
    if (vow_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (vow_pid == 0) {
        print_vowels(NULL);          
    }
    waitpid(vow_pid, NULL, 0);       

    pid_t cons_pid = fork();
    if (cons_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (cons_pid == 0) {
        print_consonants(NULL);      
    }
    waitpid(cons_pid, NULL, 0);      

    return EXIT_SUCCESS;
}