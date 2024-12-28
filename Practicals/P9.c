#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rollNo;
    char name[50];
    float percentage;
} Student;

void bubbleSort(Student students[], int n);
int binarySearch(Student students[], int size, int rollNo);
void displayStudent(Student student);

int main() {
    int n, searchRollNo;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    Student students[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);
        getchar();
        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';
        printf("Percentage: ");
        scanf("%f", &students[i].percentage);
    }

    bubbleSort(students, n);

    printf("\nEnter the Roll No of the student to search: ");
    scanf("%d", &searchRollNo);

    int index = binarySearch(students, n, searchRollNo);

    if (index != -1) {
        printf("\nStudent found:\n");
        displayStudent(students[index]);
    } else {
        printf("\nStudent with Roll No %d not found.\n", searchRollNo);
    }

    return 0;
}

void bubbleSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (students[j].rollNo > students[j+1].rollNo) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int binarySearch(Student students[], int size, int rollNo) {
    int low = 0, high = size - 1;
    while(low <= high) {
        int mid = (low + high) / 2;

        if (students[mid].rollNo == rollNo) {
            return mid;
        } else if (students[mid].rollNo < rollNo) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void displayStudent(Student student) {
    printf("Roll No: %d\n", student.rollNo);
    printf("Name: %s\n", student.name);
    printf("Percentage: %.2f\n", student.percentage);
}
