#include <string.h>
#include <stdio.h>
#include <ctype.h>
int valid_sequence(char *sequence) {

    int is_valid = 1;
    int length = strlen(sequence);
    if (length % 3 != 0) {
        printf("Sequence invalid, length is %d, please enter a valid sequence\n", length);
        return 0;
    }

    for (int i = 0; sequence[i] != '\0'; ++i) {
        char c = toupper(sequence[i]);

        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            is_valid = 0;
            break;
        }
    }

    if (
            (toupper(sequence[0]) == 'A') &&
            (toupper(sequence[1]) == 'T') &&
            (toupper(sequence[2]) == 'G')
            ) {
        return 1;
    } else {
        printf("Codon code is invalid, please enter a sequence starting with ATG \n");
        return 0;
    }

    return is_valid;
}