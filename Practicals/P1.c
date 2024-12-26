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
    int sparse_matrix[count + 1][3];
    sparse_matrix[0][0] = rows;
    sparse_matrix[0][1] = cols;
    sparse_matrix[0][2] = count;

    // Filling up the sparse matrix
    int k = 1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0) {
                sparse_matrix[k][0] = i;
                sparse_matrix[k][1] = j;
                sparse_matrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    // Printing the sparse matrix
    printf("\n- Sparse Matrix -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d ", sparse_matrix[i][j]);
        printf("\n");
    }

    // Transpose the sparse matrix

    int transpose_sparse_matrix[count + 1][3];

    transpose_sparse_matrix[0][0] = sparse_matrix[0][1];
    transpose_sparse_matrix[0][1] = sparse_matrix[0][0];
    transpose_sparse_matrix[0][2] = sparse_matrix[0][2];

    for(int i = 1; i <= count; i++) {
        transpose_sparse_matrix[i][0] = sparse_matrix[i][1];
        transpose_sparse_matrix[i][1] = sparse_matrix[i][0];
        transpose_sparse_matrix[i][2] = sparse_matrix[i][2];
    }

    printf("\n- Simple Transpose of Sparse Matrix -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d ", transpose_sparse_matrix[i][j]);
        printf("\n");
    }

    int n;
    int fast_transpose[count + 1][3];
    int frequency[cols], startingPos[cols];

    for(int i = 0; i < cols; i++)
        frequency[i] = 0;

    for(int i = 1; i <= count; i++)
        frequency[sparse_matrix[i][1]]++;

    startingPos[0] = 1;
    for(int i = 1; i < cols; i++)
        startingPos[i] = startingPos[i - 1] + frequency[i - 1];

    fast_transpose[0][0] = sparse_matrix[0][1];
    fast_transpose[0][1] = sparse_matrix[0][0];
    fast_transpose[0][2] = sparse_matrix[0][2];

    for(int i = 1; i <= count; i++) {
        int j = startingPos[sparse_matrix[i][1]]++;
        fast_transpose[j][0] = sparse_matrix[i][1];
        fast_transpose[j][1] = sparse_matrix[i][0];
        fast_transpose[j][2] = sparse_matrix[i][2];
    }

    printf("\n- Fast Transpose of Sparse Matrix -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d ", fast_transpose[i][j]);
        printf("\n");
    }
    
    return 0;
}
