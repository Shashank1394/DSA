#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

typedef struct Stack {
    int top;
    int items[MAX];
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
int isFull(Stack* s) { return s->top == MAX - 1; }
void push(Stack* s, int item) { s->items[++s->top] = item; }
int pop(Stack* s) { return s->items[s->top--]; }
int peek(Stack* s) { return s->items[s->top]; }
int precedence(char op) { return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/' || op == '%') ? 2 : (op == '^') ? 3 : 0; }
int isOperator(char ch) { return strchr("+-*/%^", ch) != NULL; }

void infixToPostfix(const char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for(int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if(isdigit(ch)) {
            do {
                postfix[j++] = infix[i++]; 
            } while(isdigit(infix[i]));
            postfix[j++] = ' ';
            i--;
        } else if(ch == '(') {
            push(&s, ch);
        } else if(ch == ')') {
            while(peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);
        } else if(isOperator(ch)) {
            while(!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }
    while(!isEmpty(&s))
        postfix[j++] = pop(&s);
    postfix[j] = '\0';
}

int evaluatePostfix(const char* postfix) {
    Stack s;
    initStack(&s);

    for(int i = 0; postfix[i] != '\0'; i++) {
        if(isdigit(postfix[i])) {
            int num = 0;
            while(isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            push(&s, num);
        } else if(isOperator(postfix[i])) {
            int b = pop(&s), a = pop(&s);
            switch(postfix[i]) {
                case '+' : push(&s, a + b); break;
                case '-' : push(&s, a - b); break;
                case '*' : push(&s, a * b); break;
                case '/' : push(&s, a / b); break;
                case '%' : push(&s, a % b); break;
                case '^' : push(&s, (int)pow(a,b)); break;
            }
        } else if(postfix[i] == ' ') {
            continue;
        }
    }
    return pop(&s);
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%[^\n]", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    printf("Evaluation Result: %d\n", evaluatePostfix(postfix));
    return 0;
}