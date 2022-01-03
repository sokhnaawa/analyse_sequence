#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
/**
 *  function find codons stop
 * @param D
 * @param seqLength
 * @param startIndice
 * @return
 */
int findCodStop(char *D, int seqLength, int startIndice) {
    int ind = -1;
    int finded = 0;
    int i = startIndice;
    int stop = seqLength - 2;

    while (i < stop && finded == 0) {
        if (D[i] != 'T') {
            i = i + 3;
        } else {

            if (D[i + 1] == 'A') {
                if (D[i + 2] == 'A' || D[i + 2] == 'G') {
                    finded = 1;
                    ind = i;
                    break;
                } else {
                    i = i + 3;
                }
            }
            else {
                if (D[i + 1] == 'G' && D[i + 2] == 'A') {
                    finded = 1;
                    ind = i;
                    break;
                } else {
                    i = i + 3;
                }
            }
        }
    }
    return ind;
}

/**
 * find codon start
 * @param D
 * @param startIndex
 * @param endIndex
 * @return
 */
int findCodStart(char *D, int startIndex, int endIndex)
{
    int indCodStart = -1;
    int finded = -1;
     int i = startIndex;
     while (i <= endIndex && finded == -1) {
         if(D[i] == 'A' && D[i+1] == 'T' && D[i+2] == 'G') {
             finded = 1;
             indCodStart = i;
             break;
         }
        i++;
     }

    return indCodStart;
}

/**
 * get condon sequence
 * @param D
 * @param start
 * @param end
 * @return
 */
char * getCodonSequence(char *D, int start, int end) {
    if(start > -1 && end > -1 ) {
        int n = end - start;
        int i;
        char *str= malloc(n * sizeof(char*));
        str[0] = '\0';

        for(i = start; i < end; i++) {
            char codon[1];
            sprintf(codon, "%.*s", 1, D+i);
            strcat(str, codon);
        }

        return str;
    }
    return "";
}

/**
 *
 * @param sequence
 * @return
 */
int valid_dna_sequence(char *sequence) {
    int is_valid = 1;

    for (int i = 0; sequence[i] != '\0'; ++i) {
        char c = toupper(sequence[i]);

        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            is_valid = 0;
            break;
        }
    }

    return is_valid;
}

/**
 *
 * @param dna_sequence
 * @param maxSequence
 * @return
 */
void getAllCodonSequencesFromDNA(char * dna_sequence, char ** maxSequence)
{
    int starIndex1 = 0;
    int dna_length = strlen(dna_sequence);

    while (starIndex1 < dna_length) {
        int codStop1 = findCodStop(dna_sequence, dna_length, starIndex1);
        int codStop2 = -1;
        if(codStop1 > 0) {
            codStop2 =  findCodStop(dna_sequence, dna_length, codStop1+3);
        }
        int indCodStart = -1;
        if(codStop1 > -1 && codStop2 > -1 && codStop2 > codStop1) {
            indCodStart = findCodStart(dna_sequence, codStop1+3, codStop2-3);
            char *tmp = getCodonSequence(dna_sequence, indCodStart, codStop2);
            if(strlen(tmp) > strlen(*maxSequence))
            {
                *maxSequence = tmp;
            }

        }
        starIndex1 += codStop2+2;
    }
}