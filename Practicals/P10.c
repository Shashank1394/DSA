#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100

// Define the Sales record structure
typedef struct {
    int sales_id;
    char customer_name[MAX_NAME_LEN];
    char product_name[MAX_NAME_LEN];
    int quantity_sold;
    float total_sale_amount;
} SaleRecord;

void merge(SaleRecord arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    SaleRecord leftArr[n1], rightArr[n2];

    for(int i = 0; i < n1; i ++)
        leftArr[i] = arr[left + i];
    for(int i = 0; i < n2; i ++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(leftArr[i].total_sale_amount >= rightArr[j].total_sale_amount) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(SaleRecord arr[], int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printSalesData(SaleRecord arr[], int size) {
    printf("Sales ID\tCustomer Name\tProduct Name\tQuantity Sold\tTotal Sale Amount\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n",
               arr[i].sales_id,
               arr[i].customer_name,
               arr[i].product_name,
               arr[i].quantity_sold,
               arr[i].total_sale_amount);
    }
}

int main() {
    // Define some sample sales data
    SaleRecord sales[] = {
        {101, "John Doe", "Laptop", 2, 1500.50},
        {102, "Jane Smith", "Smartphone", 5, 1200.00},
        {103, "Alice Brown", "Tablet", 3, 900.00},
        {104, "Bob White", "Headphones", 7, 350.75},
        {105, "Charlie Green", "Smartwatch", 4, 800.25}
    };

    int n = sizeof(sales) / sizeof(sales[0]);

    // Sort the sales data based on total sale amount in descending order
    mergeSort(sales, 0, n - 1);

    // Print the sorted sales data
    printSalesData(sales, n);

    return 0;
}