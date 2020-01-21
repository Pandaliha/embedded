#include "Generator.h"
#include <stdlib.h>

int *chipSequences[24];

// Muttersequenzen
int motherseq1[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int motherseq2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int registerNos[48] = {2, 6, 3, 7, 4, 8, 5, 9, 1, 9, 2, 10, 1, 8, 2, 9, 3, 10, 2, 3, 3, 4, 5, 6, 6, 7, 7, 8, 8,
                       9, 9, 10, 1, 4, 2, 5, 3, 6, 4, 7, 5, 8, 6, 9, 1, 3, 4, 6};

// Verschiebung der Bits, Index 0 ist XOR Ergebnis
void shiftSequence(int *array, int newValue) {
    for (int k = 9; k > 0; k--) {
        array[k] = array[k - 1];
    }
    array[0] = newValue;
}

void generateCode() {
    int *sumsignal[1023];
    int goldCode;

    //printf("/n/n GOLD-CODE %d /n/n");

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 1023; j++) {

            //berechnet Gold-Code Bits
            goldCode = motherseq1[9] ^ (motherseq2[registerNos[i * 2] - 1] ^
                                        motherseq2[registerNos[i * 2 + 1] - 1]);

            //printf("%d", goldCode);

            if (goldCode == 0) {
                *(sumsignal + j) = -1;
            } else {
                *(sumsignal + j) = 1;
            }

            // XOR Bits der Muttersequenz + setze Ergebnis als neues erstes Bit
            int newFirst1 = motherseq1[2] ^motherseq1[9];
            shiftSequence(motherseq1, newFirst1);

            // XOR Bits der Muttersequenz + setze Ergebnis als neues erstes Bit
            int newFirst2 = motherseq2[1] ^motherseq2[2] ^motherseq2[5] ^motherseq2[7] ^motherseq2[8] ^
                            motherseq2[9];
            shiftSequence(motherseq2, newFirst2);
        }

        int *saveArray = malloc(1023 * sizeof(int));

        for (int f = 0; f < 1023; f++) {
            saveArray[f] = sumsignal[f];
            //printf("%d", saveArray[f]);
        }


        chipSequences[i] = saveArray;
        //printf("%d", chipSequences[i]);

        int resetGeneratorSeq1[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int resetGeneratorSeq2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        *motherseq1 = *resetGeneratorSeq1;
        *motherseq2 = *resetGeneratorSeq2;
    }
};

int *get(int id) {
        return chipSequences[id - 1];
};