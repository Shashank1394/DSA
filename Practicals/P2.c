#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *book_name;  // Dynamically allocated string
    struct node *next;
};

struct node *head = NULL;

void add_book();
void remove_book();
void display_books();
void search_book();
void count_books();
void free_memory();

int main() {
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Display Books\n");
        printf("4. Search Book\n");
        printf("5. Count Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number between 1 and 6.\n");
            while (getchar() != '\n'); // Clear the buffer
            continue;
        }
        getchar(); // Clear the newline left by scanf

        switch (choice) {
            case 1: add_book(); break;
            case 2: remove_book(); break;
            case 3: display_books(); break;
            case 4: search_book(); break;
            case 5: count_books(); break;
            case 6: 
                printf("\nExiting...\n");
                free_memory(); // Free allocated memory before exiting
                return 0;
            default: 
                printf("\nInvalid input! Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}

void add_book() {
    struct node* newbook = (struct node*)malloc(sizeof(struct node));
    if (!newbook) {
        printf("\nError: Memory allocation failed.\n");
        return;
    }

    newbook->book_name = (char*)malloc(100 * sizeof(char));  // Dynamically allocate space for book name
    if (!newbook->book_name) {
        printf("\nError: Memory allocation failed for book name.\n");
        free(newbook);  // Free previously allocated memory
        return;
    }

    printf("\nEnter the name of the book: ");
    fgets(newbook->book_name, 100, stdin);
    newbook->book_name[strcspn(newbook->book_name, "\n")] = '\0'; // Remove trailing newline
    newbook->next = head;
    head = newbook;

    printf("\nBook '%s' added successfully!\n", newbook->book_name);
}

void remove_book() {
    if (head == NULL) {
        printf("\nStorage is empty!\n");
        return;
    }

    printf("\nEnter the name of the book you want to remove: ");
    char name[100];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    // Check if the head node matches
    if (strcmp(head->book_name, name) == 0) {
        struct node *temp = head;
        head = head->next;
        free(temp->book_name);  // Free the dynamically allocated name
        free(temp);  // Free the node
        printf("\nBook '%s' removed successfully!\n", name);
        return;
    }

    // Traverse the list to find and remove the node
    struct node *curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (strcmp(curr->next->book_name, name) == 0) {
            struct node *temp = curr->next;
            curr->next = curr->next->next;
            free(temp->book_name);  // Free the book name
            free(temp);  // Free the node
            printf("\nBook '%s' removed successfully!\n", name);
            return;
        }
        curr = curr->next;
    }

    printf("\nBook '%s' not found!\n", name);
}

void display_books() {
    if (head == NULL) {
        printf("\nNo books in storage.\n");
        return;
    }

    printf("\nBooks in storage:\n");
    struct node *curr = head;
    while (curr != NULL) {
        printf("- %s\n", curr->book_name);
        curr = curr->next;
    }
}

void search_book() {
    if (head == NULL) {
        printf("\nNo books in storage.\n");
        return;
    }

    printf("\nEnter the name of the book to search: ");
    char name[100];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    struct node *curr = head;
    int index = 0; // Initialize index to 0

    while (curr != NULL) {
        if (strcmp(curr->book_name, name) == 0) {
            printf("\nBook '%s' found at index %d.\n", name, index);
            return;
        }
        curr = curr->next;
        index++; // Increment the index
    }

    printf("\nBook '%s' not found in storage.\n", name);
}

void count_books() {
    int count = 0;
    struct node *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    printf("\nTotal number of books: %d\n", count);
}

void free_memory() {
    struct node *curr = head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp->book_name);  // Free book name
        free(temp);  // Free node
    }
    head = NULL;
}
