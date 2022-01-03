#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../lib/constants.h"
#include "translation.h"

int main(int argc, char *argv[]) {
    char *protein;
    char * filePath;
    int request_file = 0;
    char *rna_sequence;

    request_file = get_path_from_user(&filePath, "Please entre a valid RNA sequence : ");
    extract_sequence(filePath, &rna_sequence);

    if (request_file == 1) {
        while (valid_rna_sequence(rna_sequence) == 0) {
            printf("\nInvalid sequence rna. Please enter a valid rna sequence: ");
            get_path_from_user(&filePath, "");
            extract_sequence(filePath, &rna_sequence);
        }

        char tmp[200];
        sprintf(tmp, PROTEIN_SEQUENCE_FILE, timeInMilliseconds());
        removeAllSpaceAndReturnAline(&rna_sequence);
        translateRnaToProtein(rna_sequence, &protein);
        int is_saved = save_sequence(rna_sequence, tmp, MAX_LINE_LENGTH);
        if(is_saved == 1) {
            printf("file is saved in %s", tmp);
        }
    }
    return 1;
}
