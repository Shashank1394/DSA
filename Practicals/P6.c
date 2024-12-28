#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 15

typedef struct node {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    struct node* left;
    struct node* right;
} Node;

Node* create_node(const char* name, const char* phone) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newnode->name, name);
    strcpy(newnode->phone, phone);
    newnode->left = newnode->right = NULL;
    return newnode;
}

Node* insert(Node* root, const char* name, const char* phone) {
    if (root == NULL) {
        return create_node(name, phone);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, phone);
    }
    return root;
}

Node* search(Node* root, const char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

Node* find_min(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

Node* delete(Node* root, const char* name) {
    if (root == NULL) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        root->left = delete(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = delete(root->right, name);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = find_min(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);
        root->right = delete(root->right, temp->name);
    }
    return root;
}

void print_list(Node* root) {
    if (root != NULL) {
        print_list(root->left);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        print_list(root->right);
    }
}

int main() {
    int ch;
    Node* root = NULL;
    char name[MAX_NAME_LEN], phone[MAX_PHONE_LEN];

    while (1) {
        printf("\n--- Phonebook Menu ---\n");
        printf("1. Insert new entry\n");
        printf("2. Delete an entry\n");
        printf("3. Search for an entry\n");
        printf("4. Print phone list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar(); // Consume newline left by scanf

        switch (ch) {
            case 1:
                printf("\nEnter name: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                printf("Enter phone: ");
                fgets(phone, MAX_PHONE_LEN, stdin);
                phone[strcspn(phone, "\n")] = '\0'; // Remove newline
                root = insert(root, name, phone);
                printf("Contact added successfully.\n");
                break;

            case 2:
                printf("\nEnter name to delete: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                root = delete(root, name);
                printf("Contact deleted if it existed.\n");
                break;

            case 3:
                printf("\nEnter a name to search: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                {
                    Node* result = search(root, name);
                    if (result) {
                        printf("Name: %s, Phone: %s\n", result->name, result->phone);
                    } else {
                        printf("Name not found!\n");
                    }
                }
                break;

            case 4:
                printf("Phonebook:\n");
                print_list(root);
                break;

            case 5:
                printf("\nExiting...\n");
                exit(0);

            default:
                printf("\nInvalid input! Please try again.\n");
        }
    }
}
