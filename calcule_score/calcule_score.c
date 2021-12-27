#include "../lib/utils.h"
#include "../lib/constants.h"

int main() {
    char * filePath1;
    char * filePath2;

    int request_file1 = 0;
    int request_file2 = 0;
    char *sequence1;
    char *sequence2;

    char *rna_sequence = NULL;

    request_file1 = get_path_from_user(&filePath1, "Please entre a valid codon sequence 1: ");
    request_file2 = get_path_from_user(&filePath2, "Please entre a valid codon sequence 2: ");
    extract_sequence(filePath1, &sequence1);
    extract_sequence(filePath2, &sequence2);
    if(strlen(sequence1) != strlen(sequence2))
    {
        printf("KOKO");
        return 0;
    }
    float  countSeq = strlen(sequence1);
    float countIdent = 0;
    char ident[ strlen(sequence1)];

    for(int i=0; i < countSeq && sequence1[i] != '\0'; i++) {
        if(sequence1[i] == sequence2[i]) {
            countIdent++;
            ident[i] = sequence1[i];
        } else {
            ident[i] = '-';
        }
    }
    float p;
    p = (countIdent / (countSeq-1))*100;

    printf("Identité de séqence : %.0f/%.0f %.2f%%\n", countIdent, countSeq-1, p );
    printf("seq1 %s\r", sequence1);
    printf("seq1 %s\r", sequence2);
    printf("-id- %s", ident);




    return 0;
}
