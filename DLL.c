#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char model_name[50];
    int price;
    char manufacturer[50];
    int engine_capacity;
    struct node *next, *prev;
};

struct node *head = NULL;
struct node *curr = NULL;

void insertCar();
void deleteCar();
void updatePrice();
void display();
void searchByModel();
void listByPriceRange();

int main() {
    int ch;
    while(1) {
        printf("\n\n- Car Inventory System -");
        printf("\n1. Insert New Car Model");
        printf("\n2. Delete Car Model");
        printf("\n3. Update Car Price");
        printf("\n4. Display All Cars");
        printf("\n5. Search Car by Model");
        printf("\n6. List Cars by Price Range");
        printf("\n7. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: insertCar(); break;
            case 2: deleteCar(); break;
            case 3: updatePrice(); break;
            case 4: display(); break;
            case 5: searchByModel(); break;
            case 6: listByPriceRange(); break;
            case 7: printf("\nExiting..."); exit(0);
            default: printf("\nInvalid input! Try again...");
        }
    }
    return 0;
}

void insertCar() {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->prev = newnode->next = NULL;

    printf("\nEnter car model name: ");
    scanf(" %[^\n]", newnode->model_name);
    printf("Enter price: $");
    scanf("%d", &newnode->price);
    printf("Enter manufacturer: ");
    scanf(" %[^\n]", newnode->manufacturer);
    printf("Enter engine capacity (in cc): ");
    scanf("%d", &newnode->engine_capacity);

    if (head == NULL) {
        head = newnode;
        printf("Added new car model as the first entry.");
    } else {
        curr = head;
        while (curr->next != NULL) 
            curr = curr->next;
        curr->next = newnode;
        newnode->prev = curr;
        printf("New car model added successfully at the end of the list.");
    }
}

void deleteCar() {
    if (head == NULL) {
        printf("\nList is empty!");
        return;
    }

    char model[50];
    printf("\nEnter model name to delete: ");
    scanf(" %[^\n]", model);

    curr = head;
    while (curr != NULL && strcmp(curr->model_name, model) != 0)
        curr = curr->next;

    if (curr == NULL) {
        printf("Model not found!");
    } else {
        if (curr->prev != NULL)
            curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
        if (curr == head)
            head = curr->next;
        free(curr);
        printf("Car model %s deleted successfully.", model);
    }
}

void updatePrice() {
    if (head == NULL) {
        printf("\nList is empty!");
        return;
    }

    char model[50];
    printf("\nEnter model name to update price: ");
    scanf(" %[^\n]", model);

    curr = head;
    while (curr != NULL && strcmp(curr->model_name, model) != 0)
        curr = curr->next;

    if (curr == NULL) {
        printf("Model not found!");
    } else {
        printf("Enter new price for %s: $", model);
        scanf("%d", &curr->price);
        printf("Price updated successfully.");
    }
}

void display() {
    if (head == NULL) {
        printf("\nNo cars in the inventory.");
    } else {
        printf("\nCar Inventory:");
        for (curr = head; curr != NULL; curr = curr->next) {
            printf("\nModel: %s, Price: $%d, Manufacturer: %s, Engine Capacity: %dcc", 
                   curr->model_name, curr->price, curr->manufacturer, curr->engine_capacity);
        }
    }
}

void searchByModel() {
    if (head == NULL) {
        printf("\nList is empty.");
        return;
    }

    char model[50];
    printf("\nEnter model name to search: ");
    scanf(" %[^\n]", model);

    curr = head;
    while (curr != NULL && strcmp(curr->model_name, model) != 0)
        curr = curr->next;

    if (curr == NULL) {
        printf("Model not found!");
    } else {
        printf("\nModel: %s, Price: $%d, Manufacturer: %s, Engine Capacity: %dcc",
               curr->model_name, curr->price, curr->manufacturer, curr->engine_capacity);
    }
}

void listByPriceRange() {
    if (head == NULL) {
        printf("\nList is empty.");
        return;
    }

    int min, max;
    printf("\nEnter minimum price: ");
    scanf("%d", &min);
    printf("Enter maximum price: ");
    scanf("%d", &max);

    int found = 0;
    printf("\nCars within price range %d - %d:", min, max);
    for (curr = head; curr != NULL; curr = curr->next) {
        if (curr->price >= min && curr->price <= max) {
            printf("\nModel: %s, Price: $%d, Manufacturer: %s, Engine Capacity: %dcc", 
                   curr->model_name, curr->price, curr->manufacturer, curr->engine_capacity);
            found = 1;
        }
    }
    if (!found) {
        printf("\nNo cars found within the specified price range.");
    }
}
