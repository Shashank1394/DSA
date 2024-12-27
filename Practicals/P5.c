#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct {
    int id;
    char description[100];
} Ticket;

typedef struct {
    Ticket tickets[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

void initQueue(CircularQueue *q);
int isFull(CircularQueue *q);
int isEmpty(CircularQueue *q);
void submitTicket(CircularQueue *q, int id, const char *description);
void processTicket(CircularQueue *q);
void displayQueue(CircularQueue *q);

int main() {
    CircularQueue queue;
    initQueue(&queue);

    int choice, id;
    char description[100];

    while (1) {
        printf("\n--- Customer Support Ticket System ---\n");
        printf("1. Submit Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Current Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Ticket ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Ticket Description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] == '\0';
                submitTicket(&queue, id, description);
                break;

            case 2:
                processTicket(&queue);
                break;

            case 3:
                displayQueue(&queue);
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isFull(CircularQueue *q) {
    return q->size == MAX;
}

int isEmpty(CircularQueue *q) {
    return q->size == 0;
}

void submitTicket(CircularQueue *q, int id, const char *description) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->tickets[q->rear].id = id;
    strcpy(q->tickets[q->rear].description, description);
    q->size++;

    printf("Ticket ID %d submitted successfully!\n", id);
}

void processTicket(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("No ticket to process. Queue is empty!\n");
        return;
    }

    printf("Processing Ticket ID %d: %s\n", q->tickets[q->front].id, q->tickets[q->front].description);
    q->front = (q->front + 1) % MAX;
    q->size--;

    if (q->size == 0) {
        q->front = -1;
        q->rear = -1;
    }
}

void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("The queue is empty.\n");
        return;
    }

    printf("Current Tickets in Queue: \n");
    int i = q->front;
    for(int count = 0; count < q->size; count++) {
        printf("Ticket ID: %d, Descritpion: %s", q->tickets[i].id, q->tickets[i].description);
        i = (i + 1) % MAX;
    }
}
