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

char * getCodonSequence(char *D, int start, int end)
{
    if(start > -1 && end > -1 )
    {
        int n = end - start;
        int i;
        char *str= malloc(n * sizeof(char*));
        str[0] = '\0';

        for(i = start; i < end; i++) {
            char codon[1];
            sprintf(codon, "%.*s", 1, D+i);
            char s = D[i];
            strcat(str, codon);
        }

       // printf("start is %d and end is %d ===> condon sequence is ===> %s \n", start, end, str);
        return str;
    }
    return "";
}

char * getAllCodonSequencesFromDNA(char * dna_sequence, char ** maxSequence)
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