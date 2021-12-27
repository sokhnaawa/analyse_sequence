#include "../lib/utils.h"
#include "../lib/constants.h"
#include "recherche_sequence.h"
int main(int argc, char *argv[]) {
    char * filePath;
    int request_file = 0;
    char *dna_sequence;
    char * maxSequence;

    request_file = get_path_from_user(&filePath, "Please entre a valid DNA sequence : ");
    extract_sequence(filePath, &dna_sequence);

    if (request_file == 1)
    {
        while (valid_dna_sequence(dna_sequence) == 0) {
            printf("\nInvalid DNA sequence. Please enter a valid DNA sequence: ");
            get_path_from_user(&filePath, "");
            extract_sequence(filePath, &dna_sequence);
        }
        removeAllSpaceAndReturnAline(&dna_sequence);
        getAllCodonSequencesFromDNA(dna_sequence, &maxSequence);
        if(strlen(maxSequence) > 0)
        {
            char tmp[200];
            sprintf(tmp, MAX_CONDON_SEQUENCE_FILE, timeInMilliseconds());

            int is_saved = save_sequence(maxSequence, tmp, MAX_LINE_LENGTH);
            if(is_saved == 1) {
                printf("file is saved in %s", tmp);
            }
        }
    }

    return 1;
}