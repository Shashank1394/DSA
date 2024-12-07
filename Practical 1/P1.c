#include <stdio.h>

int main() {
    int rows, cols;
    printf("Enter number of rows and cols: ");
    scanf("%d%d", &rows, &cols);

    int matrix[rows][cols];

    printf("Enter matrix elements:\n");
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);

    printf("\n- Matrix -\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    // Counting the non-zero elements
    int count = 0; // Count of non-zero elements
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(matrix[i][j] != 0) count++;

    // Check if the matrix is a sparse matrix or not
    if(count <= (rows * cols - count))
        printf("\nGiven matrix is a sparse matrix.");
    else
        printf("\nGiven matrix is not a sparse matrix.");

    // Create a sparse matrix
    int sm[count + 1][3];
    sm[0][0] = rows;
    sm[0][1] = cols;
    sm[0][2] = count;

    // Filling up the sparse matrix
    int k = 1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0) {
                sm[k][0] = i;
                sm[k][1] = j;
                sm[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    // Printing the sparse matrix
    printf("\n- Sparse Matrix -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d ", sm[i][j]);
        printf("\n");
    }

    return 0;
}