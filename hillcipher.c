//Travis Escovar
//2/28/2016

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXS 100
#define MAXF 10000
#define MATS 10
#define LINEL 80

void rFile(char plain[], char argv[1]) ;
void encrypt(char plain[], int mat[][MATS], int n, char cipher[]);
void pad(char text[], int n);
void wOut(char cipher[], char argv[3]);

int main(int argc, char *argv[]) {

	// argument logic allowing for 3 arguments to be input
    if( argc == 3) {

// read in file input file
    FILE* ifp = fopen(argv[1], "r");
    int n, i, j;
    fscanf(ifp, "%d", &n);
    int mat[MATS][MATS];
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            fscanf(ifp, "%d", &mat[i][j]);
    fclose(ifp);

    printf("Sample Key File: %s\n", &argv[1]);

    
    char plain[MAXF];
    rFile(plain, argv[2]);

    printf("Sample Input File: %s\n", &plain);

    
    char cipher[MAXF];
    encrypt(plain, mat, n, cipher);

    
    wOut(cipher, argv[3]);

    printf("Output Cipher Text: %s\n", &cipher);
}
else if( argc > 3 ) {
    printf("Too many arguments supplied.\n");
}
 else {
    printf("One argument expected.\n");
 }


    return 0;
}

// function which allows for input file to be read in
void rFile(char plain[], char argv[1]) {

    FILE* ifp = fopen(argv[1], "r");

    
    int index = 0;
    while (!feof(ifp)) {

        char c = fgetc(ifp);

        
        if (isalpha(c)) {
            plain[index] = tolower(c);
            index++;
        }
    }

    
    plain[index] = '\0';
    fclose(ifp);
}

// encryption function
void encrypt(char plain[], int mat[][MAXS], int n, char cipher[]) {

    pad(plain, n);

    
    int i = 0;
    while (i < strlen(plain)) {

        int j, k;

        
        for (j=0; j<n; j++) {

            
            int value = 0;
            for (k=0; k<n; k++)
                value = (value + mat[j][k]*(plain[i+k] - 'a'))%26;
            cipher[i+j] = (char)('a' + value);
        }

        
        i += n;
    }

    
    cipher[i] = '\0';
}
// Pad function
void pad(char text[], int n) {

    
    int oldlen = strlen(text);
    int padding = (n - oldlen%n)%n;
    int newlen = oldlen + padding;

    
    int i;
    for (i=oldlen; i<newlen; i++)
        text[i] = 'x';
    text[newlen] = '\0';
}
// function which allows cipher to be written out
void wOut(char cipher[], char argv[3]) {

    FILE* ofp = fopen(argv[3], "w");

    
    int i = 0;
    while (i < strlen(cipher)) {

        
        int j;
        for (j=0; j<LINEL && i+j<strlen(cipher); j++)
            fprintf(ofp, "%c", cipher[i+j]);
        fprintf(ofp, "\n");
        i += LINEL;
    }
}
