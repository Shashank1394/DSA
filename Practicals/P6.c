#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[50];
    char phoneNumber[20];
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(char *name, char *phoneNumber) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new contact into the BST
struct Node* insert(struct Node* root, char *name, char *phoneNumber) {
    if (root == NULL) {
        return createNode(name, phoneNumber);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, phoneNumber);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, phoneNumber);
    }

    return root;
}

// Function to search for a contact by name
struct Node* search(struct Node* root, char *name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

// Function to find the minimum value node in the tree (for deletion)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a contact by name
struct Node* delete(struct Node* root, char *name) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = delete(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = delete(root->right, name);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phoneNumber, temp->phoneNumber);
        root->right = delete(root->right, temp->name);
    }

    return root;
}

// Function to print the entire phone list in alphabetical order (in-order traversal)
void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%s: %s\n", root->name, root->phoneNumber);
        printInOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice;
    char name[50], phoneNumber[20];

    while (1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Insert a new contact\n");
        printf("2. Search for a contact\n");
        printf("3. Delete a contact\n");
        printf("4. Print all contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character from input
                printf("Enter phone number: ");
                fgets(phoneNumber, sizeof(phoneNumber), stdin);
                phoneNumber[strcspn(phoneNumber, "\n")] = '\0';  // Remove newline character from input
                root = insert(root, name, phoneNumber);
                printf("Contact inserted.\n");
                break;

            case 2:
                printf("Enter name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character
                struct Node* searchResult = search(root, name);
                if (searchResult != NULL) {
                    printf("Phone Number: %s\n", searchResult->phoneNumber);
                } else {
                    printf("Contact not found.\n");
                }
                break;

            case 3:
                printf("Enter name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character
                root = delete(root, name);
                printf("Contact deleted (if found).\n");
                break;

            case 4:
                printf("Phone Book Contacts:\n");
                printInOrder(root);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
