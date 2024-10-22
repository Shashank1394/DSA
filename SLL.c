// Singly Linked List

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char book_name[100];
    struct node *next;
};

struct node *head = NULL;
struct node *curr = NULL;

void insertFirst();
void insertLast();
void insertAt();
void deleteFirst();
void deleteLast();
void deleteAt();
void display();
void search();
void countBooks();

int main() {
    int ch;
    while(1) {
        printf("\n\n- Book List -");
        printf("\n1. Insert First");
        printf("\n2. Insert Last");
        printf("\n3. Insert At Location");
        printf("\n4. Delete First");
        printf("\n5. Delete Last");
        printf("\n6. Delete At Location");
        printf("\n7. Display");
        printf("\n8. Search");
        printf("\n9. Count Books");
        printf("\n10. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: insertFirst(); break;
            case 2: insertLast(); break;
            case 3: insertAt(); break;
            case 4: deleteFirst(); break;
            case 5: deleteLast(); break;
            case 6: deleteAt(); break;
            case 7: display(); break;
            case 8: search(); break;
            case 9: countBooks(); break;
            case 10: printf("\nExiting..."); exit(0);
            default: printf("\nInvalid input! Try again...");
        }
    } 
    return 0;
}

void insertFirst() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;

    printf("\nEnter the book name: ");
    getchar();  // Clear newline buffer
    fgets(newnode->book_name, 100, stdin);
    newnode->book_name[strcspn(newnode->book_name, "\n")] = 0; // Remove trailing newline

    if(head == NULL) {
        head = newnode;
        printf("List not found! Created a new list.");
    } else {
        newnode->next = head;
        head = newnode;
        printf("New book added successfully at the beginning of the list.");
    }
}

void insertLast() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;

    printf("\nEnter the book name: ");
    getchar();  // Clear newline buffer
    fgets(newnode->book_name, 100, stdin);
    newnode->book_name[strcspn(newnode->book_name, "\n")] = 0; // Remove trailing newline

    if(head == NULL) {
        head = newnode;
        printf("List not found! Created a new list.");
    } else {
        curr = head;
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = newnode;
        printf("New book added successfully at the end of the list.");
    }
}

void insertAt() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;

    printf("Enter a location to insert: ");
    int n; scanf("%d", &n);

    if(n == 0 || head == NULL) {
        insertFirst();
    } else {
        printf("\nEnter the book name: ");
        getchar();  // Clear newline buffer
        fgets(newnode->book_name, 100, stdin);
        newnode->book_name[strcspn(newnode->book_name, "\n")] = 0; // Remove trailing newline

        curr = head;
        for(int i = 0; i < n - 1; i++)
            curr = curr->next;
        newnode->next = curr->next;
        curr->next = newnode;
        printf("New book added successfully at index %d.", n);
    }
}

void deleteFirst() {
    if(head == NULL) {
        printf("\nList not found!");
    } else if(head->next == NULL) {
        free(head);
        head = NULL;
        printf("\nFirst and only book deleted.");
    } else {
        curr = head;
        head = head->next;
        free(curr);
        printf("\nFirst book deleted.");
    }
}

void deleteLast() {
    if(head == NULL) {
        printf("\nList not found!");
    } else if(head->next == NULL) {
        free(head);
        head = NULL;
        printf("\nLast book deleted. List is now empty.");
    } else {
        curr = head;
        while(curr->next->next != NULL)
            curr = curr->next;
        free(curr->next);
        curr->next = NULL;
        printf("Last book deleted.");
    }
}

void deleteAt() {
    if(head == NULL) {
        printf("\nList not found!");
    } else {
        printf("\nEnter an index to delete: ");
        int n; scanf("%d", &n);

        if(n == 0) {
            deleteFirst();
        } else {
            curr = head;
            for(int i = 0; i < n - 1; i++) {
                if(curr->next == NULL) {
                    printf("List index out of bounds.\n");
                    return;
                } 
                curr = curr->next;
            }
            struct node *temp = curr->next;
            curr->next = temp->next;
            free(temp);
            printf("Deleted book at index %d.", n);
        }
    }
}

void display() {
    if(head == NULL) {
        printf("\nList is empty.");
    } else {
        printf("\nBook list is: ");
        for(curr = head; curr != NULL; curr = curr->next)
            printf("%s -> ", curr->book_name);
        printf("NULL");
    }
}

void search() {
    if(head == NULL) {
        printf("\nList is empty.");
    } else {
        char search[100];
        printf("\nEnter the book name to search: ");
        getchar();  // Clear newline buffer
        fgets(search, 100, stdin);
        search[strcspn(search, "\n")] = 0;  // Remove trailing newline

        int i = 0;
        curr = head;
        while(curr != NULL) {
            if(strcmp(curr->book_name, search) == 0) {
                printf("'%s' found at index %d.", search, i);
                return;
            } else {
                curr = curr->next;
                i++;
            }
        }
        printf("Book not found.");
    }
}

void countBooks() {
    int count = 0;
    curr = head;
    while(curr != NULL) {
        count++;
        curr = curr->next;
    }
    printf("\nTotal number of books: %d", count);
}
