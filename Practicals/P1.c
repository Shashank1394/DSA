#include <stdio.h>

void input_matrix(int rows, int cols, int matrix[rows][cols]);
void display_matrix(int rows, int cols, int matrix[rows][cols]);
int is_sparse_matrix(int rows, int cols, int matrix[rows][cols], int *non_zero_count);
void create_sparse_matrix(int rows, int cols, int matrix[rows][cols], int non_zero_count, int sparse_matrix[][3]);
void display_sparse_matrix(int count, int sparse_matrix[][3]);
void simple_transpose(int count, int sparse_matrix[][3], int transpose[][3]);
void fast_transpose(int count, int sparse_matrix[][3], int transpose[][3], int cols);

int main() {
    int rows, cols;

    printf("Enter the number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Invalid input! Rows and columns must be positive integers.\n");
        return 1;
    }

    // Input matrix
    int matrix[rows][cols];
    printf("Enter matrix elements:\n");
    input_matrix(rows, cols, matrix);
    printf("\n- Original Matrix -\n");
    display_matrix(rows, cols, matrix);

    // Check if the matrix is sparse and count non-zero elements
    int non_zero_count = 0;
    if (is_sparse_matrix(rows, cols, matrix, &non_zero_count)) {
        printf("\nThe given matrix is a sparse matrix.\n");
    } else {
        printf("\nThe given matrix is not a sparse matrix.\n");
    }

    // Create and display the sparse matrix
    int sparse_matrix[non_zero_count + 1][3];
    create_sparse_matrix(rows, cols, matrix, non_zero_count, sparse_matrix);
    printf("\n- Sparse Matrix Representation -\n");
    display_sparse_matrix(non_zero_count + 1, sparse_matrix);

    // Simple transpose
    int simple_transpose_matrix[non_zero_count + 1][3];
    simple_transpose(non_zero_count + 1, sparse_matrix, simple_transpose_matrix);
    printf("\n- Simple Transpose of Sparse Matrix -\n");
    display_sparse_matrix(non_zero_count + 1, simple_transpose_matrix);

    // Fast transpose
    int fast_transpose_matrix[non_zero_count + 1][3];
    fast_transpose(non_zero_count + 1, sparse_matrix, fast_transpose_matrix, cols);
    printf("\n- Fast Transpose of Sparse Matrix -\n");
    display_sparse_matrix(non_zero_count + 1, fast_transpose_matrix);

    return 0;
}

// Function to input the matrix elements
void input_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display a matrix
void display_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the matrix is sparse and count non-zero elements
int is_sparse_matrix(int rows, int cols, int matrix[rows][cols], int *non_zero_count) {
    int total_elements = rows * cols;
    *non_zero_count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                (*non_zero_count)++;
            }
        }
    }

    return (*non_zero_count) <= (total_elements - *non_zero_count);
}

// Function to create the sparse matrix representation
void create_sparse_matrix(int rows, int cols, int matrix[rows][cols], int non_zero_count, int sparse_matrix[][3]) {
    sparse_matrix[0][0] = rows;
    sparse_matrix[0][1] = cols;
    sparse_matrix[0][2] = non_zero_count;

    int k = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse_matrix[k][0] = i;
                sparse_matrix[k][1] = j;
                sparse_matrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }
}

// Function to display the sparse matrix
void display_sparse_matrix(int count, int sparse_matrix[][3]) {
    for (int i = 0; i < count; i++) {
        printf("%d %d %d\n", sparse_matrix[i][0], sparse_matrix[i][1], sparse_matrix[i][2]);
    }
}

// Function to perform simple transpose of the sparse matrix
void simple_transpose(int count, int sparse_matrix[][3], int transpose[][3]) {
    transpose[0][0] = sparse_matrix[0][1];
    transpose[0][1] = sparse_matrix[0][0];
    transpose[0][2] = sparse_matrix[0][2];

    for (int i = 1; i < count; i++) {
        transpose[i][0] = sparse_matrix[i][1];
        transpose[i][1] = sparse_matrix[i][0];
        transpose[i][2] = sparse_matrix[i][2];
    }
}

// Function to perform fast transpose of the sparse matrix
void fast_transpose(int count, int sparse_matrix[][3], int transpose[][3], int cols) {
    int frequency[cols], starting_pos[cols];

    // Initialize frequency array
    for (int i = 0; i < cols; i++) {
        frequency[i] = 0;
    }

    // Count frequencies of column indices
    for (int i = 1; i < count; i++) {
        frequency[sparse_matrix[i][1]]++;
    }

    // Calculate starting positions
    starting_pos[0] = 1;
    for (int i = 1; i < cols; i++) {
        starting_pos[i] = starting_pos[i - 1] + frequency[i - 1];
    }

    // Perform the fast transpose
    transpose[0][0] = sparse_matrix[0][1];
    transpose[0][1] = sparse_matrix[0][0];
    transpose[0][2] = sparse_matrix[0][2];

    for (int i = 1; i < count; i++) {
        int pos = starting_pos[sparse_matrix[i][1]]++;
        transpose[pos][0] = sparse_matrix[i][1];
        transpose[pos][1] = sparse_matrix[i][0];
        transpose[pos][2] = sparse_matrix[i][2];
    }
}
