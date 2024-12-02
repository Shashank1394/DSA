#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define NAME_LEN 50
#define ISSUE_LEN 100

int ticketIDQ[SIZE];
char custNameQ[SIZE][NAME_LEN];
char issueQ[SIZE][ISSUE_LEN];
int front = -1, rear = -1;

int isFull();
int isEmpty();
void enqueue(int ticketID, char custName[], char issue[]);
void dequeue();
void display();

int main() {
    int ch, ticketID;
    char custName[NAME_LEN], issue[ISSUE_LEN];

    printf("\n- Customer Support Tickets -\n");
    while(1) {
        printf("\n1. Add Ticket");
        printf("\n2. Process Ticket");
        printf("\n3. View Ticket");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                if(isFull()) {
                    printf("Queue is full! Cannot add any more tickets.\n");
                } else {
                    printf("\nEnter Ticket ID: ");
                    scanf("%d", &ticketID);
                    getchar();
                    printf("Enter Customer Name: ");
                    fgets(custName, NAME_LEN, stdin);
                    custName[strcspn(custName, "\n")] = '\0';
                    printf("Enter your issue: ");
                    fgets(issue, ISSUE_LEN, stdin);
                    issue[strcspn(issue, "\n")] = '\0';
                    enqueue(ticketID, custName, issue);
                    printf("Ticket added successfully!\n");
                }
                break;
            
            case 2:
                if(isEmpty())
                    printf("\nQueue is empty!");
                else
                    dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("\nExiting program...\n");
                exit(0);

            default: printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}

int isFull() {
    return ((rear + 1) % SIZE) == front;
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int ticketID, char custName[], char issue[]) {
    if(isFull()) {
        printf("\nQueue is full! Cannot add any more tickets.\n");
        return;
    }

    if(isEmpty()) front = 0;

    rear = (rear + 1) % SIZE;
    ticketIDQ[rear] = ticketID;
    strcpy(custNameQ[rear], custName);
    strcpy(issueQ[rear], issue);
}

void dequeue() {
    if(isEmpty()) {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\nTicket ID: %d, Customer Name: %s, Issue: %s\n", ticketIDQ[front], custNameQ[front], issueQ[front]);

    if(front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

void display() {
    if(isEmpty()) {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\nTickets in the queue:\n");
    for(int i = front; i != (rear + 1) % SIZE; i = (i + 1) % SIZE)
        printf("\nTicket ID: %d, Customer Name: %s, Issue: %s\n", ticketIDQ[i], custNameQ[i], issueQ[i]);
}