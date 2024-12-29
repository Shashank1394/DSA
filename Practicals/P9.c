#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int rollNo;
    char name[50];
    float percentage;
} Student;

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();
    Student* student[n];

    printf("Enter the students details:\n");
    for(int i = 0; i < n; i++) {
        student[i] = (Student*)malloc(sizeof(Student));
        printf("\nStudent %d\n", i+1);
        printf("Name: ");
        fgets(student[i]->name, sizeof(student[i]->name), stdin);
        student[i]->name[strcspn(student[i]->name, "\n")] = '\0';
        printf("Roll No.: ");
        scanf("%d",&student[i]->rollNo);
        getchar();
        printf("Percentage: ");
        scanf("%f", &student[i]->percentage);
        getchar();
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(student[j]->rollNo > student[j + 1]->rollNo) {
                Student* temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }

    int rollNo;
    printf("\nEnter roll number to search: ");
    scanf("%d", &rollNo);

    int low = 0, mid, high = n - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if(student[mid]->rollNo == rollNo) {
            printf("\nStudent found successfully");
            printf("\nName: %s", student[mid]->name);
            printf("\nRoll No.: %d", student[mid]->rollNo);
            printf("\nPercentage: %.2f", student[mid]->percentage);
            break;
        } else if(student[mid]->rollNo < rollNo) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("\n\n\n- Student List -\n");
    for(int i = 0; i < n; i++) {
        printf("Name: %s\n", student[i]->name);
        printf("Roll No.: %d\n", student[i]->rollNo);
        printf("Percentage: %.2f\n", student[i]->percentage);
    }
}