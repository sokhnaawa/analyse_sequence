#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#include "../lib/utils.h"
#include "proteins.h"

int valid_rna_sequence(char *sequence) {

    int is_valid = 1;
    int length = strlen(sequence);
    if (length % 3 != 0) {
        printf("RNA sequence is invalid length sequence is %d", length);
        return 0;
    }

    for (int i = 0; sequence[i] != '\0'; ++i) {
        char c = toupper(sequence[i]);

        if (c != 'A' && c != 'C' && c != 'G' && c != 'U') {
            is_valid = 0;
            break;
        }
    }

    if (
            (toupper(sequence[0]) == 'A') &&
            (toupper(sequence[1]) == 'U') &&
            (toupper(sequence[2]) == 'G')
            ) {
        return 1;
    } else {
        printf("RNA codon code is invalid \n");
        return 0;
    }

    return is_valid;
}

int translateRnaToProtein(char * sequence, char ** protein)
{
    int i = 0;
    int numbis = 0;
    size_t n =  strlen(sequence);
    printf("%s", "Translate RNA to protein... \n");

    char *str=(char *)malloc(n*1000);
    str[0] = '\0';
    while (numbis < n-2) {
        char codon[3];
        sprintf(codon, "%.*s", 3, sequence + numbis);

        if (in_array(ala, 4, codon)) {strcat(str, "ALA");}
        if (in_array(arg, 6, codon)) { strcat(str, "ARG");}
        if (in_array(asn, 2, codon)) { strcat(str, "ASN");}
        if (in_array(asp, 2, codon)) { strcat(str, "ASP");}
        if (in_array(cys, 2, codon)) { strcat(str, "CYS");}
        if (in_array(gln, 2, codon)) { strcat(str, "GLN");}
        if (in_array(glu, 2, codon)) { strcat(str, "GLU");}
        if (in_array(gly, 4, codon)) { strcat(str, "GLY");}
        if (in_array(his, 2, codon)) { strcat(str, "HIS");}
        if (in_array(ile, 3, codon)) { strcat(str, "ILE");}
        if (in_array(leu, 6, codon)) { strcat(str, "LEU"); }
        if (in_array(lys, 2, codon)) {  strcat(str, "LYS");}

        if (in_array(met, 1, codon)) { strcat(str, "MET"); }
        if (in_array(phe, 2, codon)) { strcat(str, "PHE"); }
        if (in_array(pro, 4, codon)) { strcat(str, "PRO"); }
        if (in_array(ser, 6, codon)){ strcat(str, "SER"); }
        if (in_array(thr, 4, codon)) { strcat(str, "THR"); }
        if (in_array(trp, 1, codon)) { strcat(str, "TRP"); }
        if (in_array(tyr, 2, codon)) { strcat(str, "TYR"); }
        if (in_array(val, 4, codon)) { strcat(str, "VAL"); }
        if (in_array(stop, 3, codon)) { break; }

        numbis +=3;
        printf("\rIn progress %d", i/100);
    }
    *protein = str;

    return 1;
}
