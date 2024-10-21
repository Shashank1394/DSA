#include <stdio.h>

int main() {
    int m, n, i, j, k = 1, count = 0;
    
    printf("Enter the number of rows & columns: ");
    scanf("%d%d", &m, &n);

    int matrix[m][n];

    printf("Enter the matrix elements:\n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    printf("\n- Original matrix -\n");
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            if(matrix[i][j] != 0) count++;

    if(count <= (m * n - count)) {
        printf("\nGiven matrix is a sparse matrix\n");
    } else {
        printf("\nGiven matrix is not a sparse matrix\n");
    }

    int sparse_matrix[count + 1][3];
    sparse_matrix[0][0] = m;
    sparse_matrix[0][1] = n;
    sparse_matrix[0][2] = count;

    k = 1;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(matrix[i][j] != 0) {
                sparse_matrix[k][0] = i;
                sparse_matrix[k][1] = j;
                sparse_matrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    printf("\n- Sparse matrix -\n");
    for(i = 0; i <= count; i++) {
        for(j = 0; j < 3; j++)
            printf("%d ", sparse_matrix[i][j]);
        printf("\n");
    }

    int simple_transpose[count + 1][3];

    simple_transpose[0][0] = sparse_matrix[0][1];
    simple_transpose[0][1] = sparse_matrix[0][0];
    simple_transpose[0][2] = sparse_matrix[0][2];

    for(i = 1; i <= count; i++) {
        simple_transpose[i][0] = sparse_matrix[i][1]; 
        simple_transpose[i][1] = sparse_matrix[i][0]; 
        simple_transpose[i][2] = sparse_matrix[i][2]; 
    }

    printf("\n- Simple Transposed Sparse matrix -\n");
    for(i = 0; i <= count; i++) {
        for(j = 0; j < 3; j++)
            printf("%d ", simple_transpose[i][j]);
        printf("\n");
    }

    int fast_transpose[count + 1][3];
    int rowTerms[n], startingPos[n];

    for(i = 0; i < n; i++)
        rowTerms[i] = 0;

    for(i = 1; i <= count; i++)
        rowTerms[sparse_matrix[i][1]]++;

    startingPos[0] = 1;
    for(i = 1; i < n; i++)
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

    fast_transpose[0][0] = sparse_matrix[0][1];
    fast_transpose[0][1] = sparse_matrix[0][0];
    fast_transpose[0][2] = sparse_matrix[0][2];

    for(i = 1; i <= count; i++) {
        j = startingPos[sparse_matrix[i][1]]++;
        fast_transpose[j][0] = sparse_matrix[i][1];
        fast_transpose[j][1] = sparse_matrix[i][0];
        fast_transpose[j][2] = sparse_matrix[i][2];
    }

    printf("\n- Fast Transposed Sparse matrix -\n");
    for(i = 0; i <= count; i++) {
        for(j = 0; j < 3; j++)
            printf("%d ", fast_transpose[i][j]);
        printf("\n");
    }

    return 0;
}
