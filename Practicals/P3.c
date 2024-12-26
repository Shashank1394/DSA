#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Car structure
struct car {
    char car_model[50];
    double price;
    char mfg_name[50];
    float engine_cap;
};

// Node structure for doubly linked list
struct node {
    struct car data;
    struct node *next;
    struct node *prev;
};

// Head pointer for the doubly linked list
struct node *head = NULL;

// Function prototypes
struct node* create_car_node(char *model, double price, char *mfg_name, float engine_cap);
struct node* find_car_by_model(char *model);
void add_car();
void delete_car();
void update_price();
void list_cars_in_price_range();
void list_car_details();
void display_all_cars();

// Main function
int main() {
    int choice;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add New Car Model\n");
        printf("2. Delete Car Model\n");
        printf("3. Update Car Price\n");
        printf("4. List Cars in Price Range\n");
        printf("5. List Details of a Specific Car\n");
        printf("6. Display All Cars\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_car(); break;
            case 2: delete_car(); break;
            case 3: update_price(); break;
            case 4: list_cars_in_price_range(); break;
            case 5: list_car_details(); break;
            case 6: display_all_cars(); break;
            case 7: printf("Exiting...\n"); exit(0);
            default: printf("\nInvalid input! Please enter a number between 1 & 7\n");
        }
    }
    return 0;
}

// Utility function to create a new car node
struct node* create_car_node(char *model, double price, char *mfg_name, float engine_cap) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    strcpy(new_node->data.car_model, model);
    new_node->data.price = price;
    strcpy(new_node->data.mfg_name, mfg_name);
    new_node->data.engine_cap = engine_cap;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Utility function to find a car node by model name
struct node* find_car_by_model(char *model) {
    struct node *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->data.car_model, model) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Function to add a new car
void add_car() {
    char model[50], mfg_name[50];
    double price;
    float engine_cap;

    printf("Enter car model: ");
    scanf("%s", model);
    printf("Enter price: $");
    scanf("%lf", &price);
    printf("Enter manufacturer name: ");
    scanf("%s", mfg_name);
    printf("Enter engine capacity: ");
    scanf("%f", &engine_cap);

    struct node *new_car = create_car_node(model, price, mfg_name, engine_cap);

    if (head == NULL) {
        head = new_car;
    } else {
        struct node *curr = head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new_car;
        new_car->prev = curr;
    }

    printf("Car '%s' added successfully!\n", model);
}

// Function to delete a car by model
void delete_car() {
    if (head == NULL) {
        printf("No cars available to delete.\n");
        return;
    }

    char model[50];
    printf("\nEnter the car model to delete: ");
    scanf("%s", model);

    struct node *to_delete = find_car_by_model(model);
    if (!to_delete) {
        printf("Car model '%s' not found.\n", model);
        return;
    }

    if (to_delete->prev)
        to_delete->prev->next = to_delete->next;
    else
        head = to_delete->next;

    if (to_delete->next)
        to_delete->next->prev = to_delete->prev;

    free(to_delete);
    printf("Car model '%s' deleted successfully!\n", model);
}

// Function to update the price of a car
void update_price() {
    if (head == NULL) {
        printf("No cars available to update.\n");
        return;
    }

    char model[50];
    double new_price;
    printf("\nEnter the car model to update: ");
    scanf("%s", model);
    printf("Enter the new price: $");
    scanf("%lf", &new_price);

    struct node *car = find_car_by_model(model);
    if (!car) {
        printf("Car model '%s' not found.\n", model);
        return;
    }

    car->data.price = new_price;
    printf("Price of '%s' updated successfully to $%.2lf.\n", model, new_price);
}

// Function to list cars in a price range
void list_cars_in_price_range() {
    if (head == NULL) {
        printf("No cars available.\n");
        return;
    }

    double min_price, max_price;
    printf("\nEnter the minimum price: $");
    scanf("%lf", &min_price);
    printf("Enter the maximum price: $");
    scanf("%lf", &max_price);

    struct node *curr = head;
    int found = 0;

    printf("\nCars within price range $%.2lf - $%.2lf:\n", min_price, max_price);
    while (curr != NULL) {
        if (curr->data.price >= min_price && curr->data.price <= max_price) {
            printf("- %s\n", curr->data.car_model);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found) {
        printf("No cars found in the specified price range.\n");
    }
}

// Function to list details of a specific car
void list_car_details() {
    if (head == NULL) {
        printf("No cars available.\n");
        return;
    }

    char model[50];
    printf("\nEnter the car model to get details: ");
    scanf("%s", model);

    struct node *car = find_car_by_model(model);
    if (!car) {
        printf("Car model '%s' not found.\n", model);
        return;
    }

    printf("\nDetails of '%s':\n", model);
    printf("Price: $%.2lf\n", car->data.price);
    printf("Manufacturer: %s\n", car->data.mfg_name);
    printf("Engine Capacity: %.2f\n", car->data.engine_cap);
}

// Function to display all cars
void display_all_cars() {
    if (head == NULL) {
        printf("No cars available.\n");
        return;
    }

    struct node *curr = head;

    printf("\nAll Cars:\n");
    while (curr != NULL) {
        printf("Model: %s, Price: $%.2lf, Manufacturer: %s, Engine: %.2f\n",
               curr->data.car_model, curr->data.price, curr->data.mfg_name, curr->data.engine_cap);
        curr = curr->next;
    }
}
