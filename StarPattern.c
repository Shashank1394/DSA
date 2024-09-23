#include <stdio.h>

int main() {

    for(int i=1; i<=5; i++) { // Number of rows
        for(int j=i; j<5; j++)  // Number of spaces i.e. rows-1
            printf(" ");

        for(int k=1; k<=(2*i-1); k++) // Number of stars
            printf("*");

        printf("\n");
    }

    return 0;
}
