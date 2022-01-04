#include "../lib/utils.h"
#include "../lib/constants.h"
#include "module_transcription.h"

int main(int argc, char *argv[]) {
    char *filePath;
    char *sequence;
    char  message[60];
    char *rna_sequence = NULL;

    system("setterm -bold on");
    sprintf(message, "%sPlease entre a valid codon sequence : %s", BLU, RESET);
    get_path_from_user(&filePath, message);
    system("setterm -bold off");

    extract_sequence(filePath, &sequence);

    while (valid_sequence(sequence) == 0) {
        printf("%s%s%s", RED, "\nInvalid sequence. Please enter a valid codon sequence: ", RESET);
        get_path_from_user(&filePath, "");
        extract_sequence(filePath, &sequence);
    }
    char tmp[200];
    sprintf(tmp, RNA_SEQUENCE_FILE, timeInMilliseconds());

    rna_sequence = replaceWord(sequence, NEC_C, NEC_U);
    int is_saved = save_sequence(rna_sequence, tmp, MAX_LINE_LENGTH);
    if (is_saved == 1) {
        printf("%s file is saved in %s %s", GRN, tmp, RESET);
    }
    return 0;
}