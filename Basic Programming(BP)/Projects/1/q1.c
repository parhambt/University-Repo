#include <stdio.h>

#define MAX_COLUMNS 100  

int main(void) {
    int rows, columns;
    scanf("%d %d", &rows, &columns);



    int P = 0, N = 0, A = 0; 
    int total_votes = rows * columns;

    char votes[MAX_COLUMNS + 1]; 

    
    for (int i = 0; i < rows; i++) {
        scanf("%s", votes); 

        for (int j = 0; j < columns; j++) {
            if (votes[j] == 'P') P++;     
            else if (votes[j] == 'N') N++; 
            else if (votes[j] == 'A') A++; 

        }
    }
    float percentage_P = (P / (float)(P+N)) * 100;
    float percentage_N = (N / (float)(P+N)) * 100;

    
    char result;
    if (P > N) result = 'P';
    else if (N > P) result = 'N';
    else result = 'A';

    
    printf("Positive: %d\n", P);
    printf("Negative: %d\n", N);
    printf("Absent: %d\n", A);
    printf("P: %.2f %%\n", percentage_P);
    printf("N: %.2f %%\n", percentage_N);
    printf("Result: %c\n", result);
    return 0;
}
