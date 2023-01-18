#include <string.h>
#include <stdio.h>
#include "ex1.h"

/* Returns the number of times LETTER appears in STR.
There are two different ways to iterate through a string.
1st way hint: strlen() may be useful
2nd way hint: all strings end in a null terminator */
int num_occurrences(char *str, char letter) {
    int cnt = 0;
    while (*str != '\0') {
        if (letter == *str) {
            ++ cnt;
        }
        ++ str;
    }
    return cnt;
}

/* Populates DNA_SEQ with the number of times each nucleotide appears.
Each sequence will end with a NULL terminator and will have up to 20 nucleotides.
All letters will be upper case. */
void compute_nucleotide_occurrences(DNA_sequence *dna_seq) {
#if 0
    // 初始化
    dna_seq->A_count = 0;
    dna_seq->C_count = 0;
    dna_seq->G_count = 0;
    dna_seq->T_count = 0;

    // 计算
    char *ptr = dna_seq->sequence;
    while (*ptr != '\0') {
        switch (*ptr) {
            case 'A':
                ++ dna_seq->A_count;
                break;
            case 'C':
                ++ dna_seq->C_count;
                break;
            case 'G':
                ++ dna_seq->G_count;
                break;
            case 'T':
                ++ dna_seq->T_count;
                break;
        }
        ++ ptr;
    }
#endif

    dna_seq->A_count = num_occurrences(dna_seq->sequence, 'A');
    dna_seq->C_count = num_occurrences(dna_seq->sequence, 'C');
    dna_seq->G_count = num_occurrences(dna_seq->sequence, 'G');
    dna_seq->T_count = num_occurrences(dna_seq->sequence, 'T');

    return;
}
