#include <stdio.h>

int main() {
    int m, n;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &n, &m);

    int matrix[n][m];
    printf("Enter the matrix elements:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n- Original Matrix -\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(matrix[i][j] != 0) {
                count++;
            }
        }
    }

    (count < (n * m)) ? printf("\nIt's a sparse matrix\n") : printf("\nIt's not a sparse matrix\n");

    int sparse_matrix[count + 1][3];
    sparse_matrix[0][0] = n;
    sparse_matrix[0][1] = m;
    sparse_matrix[0][2] = count;

    int k = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(matrix[i][j] != 0) {
                sparse_matrix[k][0] = i;
                sparse_matrix[k][1] = j;
                sparse_matrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    printf("\n- Sparse Matrix -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", sparse_matrix[i][j]);
        }
        printf("\n");
    }

    int simple_transpose[count + 1][3];
    simple_transpose[0][0] = sparse_matrix[0][1];
    simple_transpose[0][1] = sparse_matrix[0][0];
    simple_transpose[0][2] = sparse_matrix[0][2];

    for(int i = 1; i <= count; i++) {
        simple_transpose[i][0] = sparse_matrix[i][1];
        simple_transpose[i][1] = sparse_matrix[i][0];
        simple_transpose[i][2] = sparse_matrix[i][2];
    }

    printf("\n- Simple Transpose -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", simple_transpose[i][j]);
        }
        printf("\n");
    }

    int fast_transpose[count + 1][3];
    int frequency[m], starting_pos[m];

    for(int i = 0; i < m; i++) {
        frequency[i] = 0;
    }   

    for(int i = 1; i <= count; i++) {
        frequency[sparse_matrix[i][1]]++;
    }

    starting_pos[0] = 1;
    for(int i = 1; i < m; i++) {
        starting_pos[i] = starting_pos[i - 1] + frequency[i - 1];
    }

    fast_transpose[0][0] = sparse_matrix[0][1];
    fast_transpose[0][1] = sparse_matrix[0][0];
    fast_transpose[0][2] = sparse_matrix[0][2];

    for(int i = 1; i <= count; i++) {
        int pos = starting_pos[sparse_matrix[i][1]]++;
        fast_transpose[pos][0] = sparse_matrix[i][1];
        fast_transpose[pos][1] = sparse_matrix[i][0];
        fast_transpose[pos][2] = sparse_matrix[i][2];
    }

    printf("\n- Fast Transpose -\n");
    for(int i = 0; i <= count; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", fast_transpose[i][j]);
        }
        printf("\n");
    }
    return 0;
}
