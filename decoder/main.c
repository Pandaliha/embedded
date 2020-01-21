#include <stdio.h>
#include "Generator.h"

int crossCorrelate(int *sumsignal, int *chipsequence, int delta) {
    int product = 0;
    int tempDelta = 0;
    for (int i = 0; i < 1023; i++) {
        tempDelta = (i + delta) % 1023;
        //Kreuzkorrelationsprodukt
        product += sumsignal[i] * chipsequence[tempDelta];
    }
    return product;
}
// Gipfel für Satelliten finden
int findDelta(int *sumsignal, int *chipsequence) {
    int correlation;
    for (int i = 0; i < 1023; i++) {
        correlation = crossCorrelate(sumsignal, chipsequence, i);

        if (1023 - 195 <= correlation && correlation <= 1023 + 195) {
            return i;
        }
    }
    return -1;
}

void testGPSId(int id, int sumsignal[], int chipsequence[]) {
    int delta = -1;
    delta = findDelta(sumsignal, chipsequence);
    if (delta != -1) {
        printf("Satellite %i has sent bit %c (delta = %i)\n", id, '1', delta);
    } else {
        //inverting chip sequence
        for (int i = 0; i < 1023; i++) {
            if (chipsequence[i] == -1) {
                chipsequence[i] = 1;
            } else {
                chipsequence[i] = -1;
            }
        }
        delta = findDelta(sumsignal, chipsequence);
        if (delta != -1) {
            printf("Satellite %i has sent bit %c (delta = %i)\n", id, '0', delta);
        }
    }
}


int main(int argc, char *argv[]) {

    generateCode();
    int *chipSequence;
    int input[1023];

    FILE *file;
    file = fopen(argv[1], "r");
    //file = fopen("./assets/gps_sequence_10.txt", "r");
    for (int i = 0; i < 1023; i++) {
        fscanf(file, "%d", &input[i]);
    }

    for (int j = 1; j <= 24; j++) {
        chipSequence = get(j);
        testGPSId(j, input, chipSequence);
    }
    return 0;
}