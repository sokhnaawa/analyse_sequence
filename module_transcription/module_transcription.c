#include "../lib/utils.h"
#include "../lib/constants.h"
#include "module_transcription.h"

int main(int argc, char *argv[]) {
    char * filePath;
    int request_file = 0;
    char *sequence;
    char *rna_sequence = NULL;

    request_file = get_path_from_user(&filePath, "Please entre a valid codon sequence : ");

    if (request_file == 1) {
        extract_sequence(filePath, &sequence);
        while (valid_sequence(sequence) == 0) {
            printf("\nInvalid sequence. Please enter a valid codon sequence: ");
            get_path_from_user(&filePath, "");
            extract_sequence(filePath, &sequence);
        }
        char tmp[200];
        sprintf(tmp, RNA_SEQUENCE_FILE, timeInMilliseconds());

        rna_sequence = replaceWord(sequence, NEC_C, NEC_U);
        int is_saved = save_sequence(rna_sequence, tmp, MAX_LINE_LENGTH);
        if(is_saved == 1) {
            printf("file is saved in %s", tmp);
        }
    }
    return 0;
}