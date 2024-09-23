#include <stdio.h>

int main() {
    int m, n, i, j, k = 1, count = 0;
    
    printf("Enter the number of rows & columns: ");
    scanf("%d%d", &m, &n);

    int matrix[m][n];

    printf("Enter the matrix elements: ");
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            scanf("%d", &matrix[i][j]);

    printf("\n- Original matrix -\n");
    for(i=0; i<m; i++) {
        for(j=0; j<n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    int transpose_matrix[n][m];
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            transpose_matrix[j][i] = matrix[i][j];

    printf("\n- Transposed matrix -\n");
    for(i=0; i<m; i++) {
        for(j=0; j<n; j++)
            printf("%d ", transpose_matrix[i][j]);
        printf("\n");
    }

    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            if(matrix[i][j] != 0) count++;

    if((count <= (m * n - count)) ? printf("\nGiven matrix is a sparse matrix") : printf("\nGiven matrix is not a sparse matrix"));

    int sparse_matrix[count+1][3];

    sparse_matrix[0][0] = m;
    sparse_matrix[0][1] = n;
    sparse_matrix[0][2] = count;

    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            if(matrix[i][j] != 0) {
                sparse_matrix[k][0] = i;
                sparse_matrix[k][1] = j;
                sparse_matrix[k][2] = matrix[i][j];
                k++;
            }

    printf("\n- Sparse matrix -\n");
    for(i=0; i<=count; i++) {
        for(j=0; j<3; j++)
            printf("%d ", sparse_matrix[i][j]);
        printf("\n");
    }

    return 0;
}
