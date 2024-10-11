// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
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

int main() {
    int ch;
    while(1) {
        printf("\n\n- Singly Linked List -");
        printf("\n1. Insert First");
        printf("\n2. Insert Last");
        printf("\n3. Insert At Location");
        printf("\n4. Delete First");
        printf("\n5. Delete Last");
        printf("\n6. Delete At Location");
        printf("\n7. Display");
        printf("\n8. Exit");
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
            case 8: printf("\nExiting..."); exit(0);
            default: printf("\nInvalid input! Try again...");
        }
    } return 0;
}

void insertFirst() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;
    
    printf("\nEnter the data: ");
    scanf("%d", &newnode->data);

    if(head == NULL) {
        head = newnode;
        printf("List not found! Created a new list.");
    } else {
        newnode->next = head;
        head = newnode;
        printf("New node added successfully at the beginning of the list.");
    }
}

void insertLast() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;
    
    printf("\nEnter the data: ");
    scanf("%d", &newnode->data);
    
    if(head == NULL) {
        head = newnode;
        printf("List not found! Created a new list.");
    } else {
        curr = head;
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = newnode;
        printf("New node added successfully at the end of the list.");
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
        printf("\nEnter the data: ");
        scanf("%d", &newnode->data);
        curr = head;
        for(int i = 0; i < n - 1; i++)
            curr = curr->next;
        newnode->next = curr->next;
        curr->next = newnode;
        printf("New node added successfully at index %d.", n);
    }
}

void deleteFirst() {
    if(head == NULL) {
        printf("\nList not found!");
    } else {
        curr = head;
        head = head->next;
        free(curr);
        printf("\nFirst node deleted.");
    }
}

void deleteLast() {
    if(head == NULL) {
        printf("\nList not found!");
    } else if(head->next == NULL) {
        free(head);
        head = NULL;
        printf("\nLast node is deleted. List is now empty.");
    } else {
        curr = head;
        while(curr->next->next != NULL)
            curr = curr->next;
        free(curr->next);
        curr->next = NULL;
        printf("Last node is deleted.");
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
            printf("Deleted node at index %d.", n);
        }
    }
}

void display() {
    if(head == NULL) {
        printf("\nList is empty.");
    } else {
        printf("\nList is: ");
        for(curr = head; curr != NULL; curr = curr->next)
            printf("%d -> ", curr->data);
        printf("NULL");
    }
}