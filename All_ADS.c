1. WAP to convert a given Infix expression into its equivalent Postfix expression and evaluate it using stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to return precedence of operators
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to return associativity of operators
char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L'; // Default to left-associative
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char s[], char result[]) {
    int resultIndex = 0;
    int len = strlen(s);
    char stack[1000];
    int stackIndex = -1;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c)) {
            result[resultIndex++] = c;
        }
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        // If the scanned character is an ‘)’, pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop '('
        }
        // If an operator is scanned
        else {
            while (stackIndex >= 0 && (prec(s[i]) < prec(stack[stackIndex]) ||
                                       (prec(s[i]) == prec(stack[stackIndex]) &&
                                        associativity(s[i]) == 'L'))) {
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (stackIndex >= 0) {
        result[resultIndex++] = stack[stackIndex--];
    }

    result[resultIndex] = '\0';
}

// Function to evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int len = strlen(postfix);
    int stack[1000];
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            stack[++top] = c - '0'; // Convert char to int
        } else {
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            switch (c) {
                case '+':
                    stack[++top] = operand1 + operand2;
                    break;
                case '-':
                    stack[++top] = operand1 - operand2;
                    break;
                case '*':
                    stack[++top] = operand1 * operand2;
                    break;
                case '/':
                    stack[++top] = operand1 / operand2;
                    break;
                case '^':
                    stack[++top] = (int)pow(operand1, operand2);
                    break;
            }
        }
    }
    return stack[top];
}

int main() {
    char infix[1000];
    char postfix[1000];

    // Taking input from the user
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}










2. WAP to convert a given Infix expression into its equivalent Prefix expression and evaluate it using stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to return precedence of operators
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to return associativity of operators
char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L'; // Default to left-associative
}

// Function to reverse a string
void reverse(char *exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - i - 1];
        exp[n - i - 1] = temp;
    }
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char s[], char result[]) {
    int resultIndex = 0;
    int len = strlen(s);
    char stack[1000];
    int stackIndex = -1;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c)) {
            result[resultIndex++] = c;
        }
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        // If the scanned character is an ‘)’, pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop '('
        }
        // If an operator is scanned
        else {
            while (stackIndex >= 0 && (prec(s[i]) < prec(stack[stackIndex]) ||
                                       (prec(s[i]) == prec(stack[stackIndex]) &&
                                        associativity(s[i]) == 'L'))) {
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (stackIndex >= 0) {
        result[resultIndex++] = stack[stackIndex--];
    }

    result[resultIndex] = '\0';
}

// Function to convert infix to prefix expression
void infixToPrefix(char infix[], char prefix[]) {
    // Reverse the infix expression
    reverse(infix);

    // Replace ( with ) and vice versa
    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    // Convert the modified infix to postfix
    char postfix[1000];
    infixToPostfix(infix, postfix);

    // Reverse the postfix expression to get prefix
    reverse(postfix);
    strcpy(prefix, postfix);
}

// Function to evaluate prefix expression
int evaluatePrefix(char* exp) {
    int stack[1000];
    int stackIndex = -1;

    for (int i = strlen(exp) - 1; i >= 0; i--) {
        if (isdigit(exp[i])) {
            stack[++stackIndex] = exp[i] - '0';
        } else {
            int op1 = stack[stackIndex--];
            int op2 = stack[stackIndex--];
            switch (exp[i]) {
                case '+':
                    stack[++stackIndex] = op1 + op2;
                    break;
                case '-':
                    stack[++stackIndex] = op1 - op2;
                    break;
                case '*':
                    stack[++stackIndex] = op1 * op2;
                    break;
                case '/':
                    stack[++stackIndex] = op1 / op2;
                    break;
                case '^':
                    stack[++stackIndex] = (int)pow(op1, op2);
                    break;
            }
        }
    }
    return stack[stackIndex];
}

int main() {
    char infix[1000];
    char prefix[1000];

    // Taking input from the user
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to prefix
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    // Evaluate the prefix expression
    int result = evaluatePrefix(prefix);
    printf("Evaluation result: %d\n", result);

    return 0;
}













3. WAP to implement two stack using array and perform following operations on it. A. PUSH, B. POP, C. StackFull D. StackeEmpty E. Display Stack

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent two stacks
typedef struct {
    int arr[MAX_SIZE];
    int top1; // Top index of the first stack
    int top2; // Top index of the second stack
} TwoStacks;

// Function to initialize the two stacks
void initialize(TwoStacks *ts) {
    ts->top1 = -1;
    ts->top2 = MAX_SIZE;
}

// Function to push an element to the first stack
void push1(TwoStacks *ts, int value) {
    if (ts->top1 < ts->top2 - 1) {
        ts->arr[++ts->top1] = value;
    } else {
        printf("Stack Overflow in stack1 by element: %d\n", value);
    }
}

// Function to push an element to the second stack
void push2(TwoStacks *ts, int value) {
    if (ts->top1 < ts->top2 - 1) {
        ts->arr[--ts->top2] = value;
    } else {
        printf("Stack Overflow in stack2 by element: %d\n", value);
    }
}

// Function to pop an element from the first stack
int pop1(TwoStacks *ts) {
    if (ts->top1 >= 0) {
        return ts->arr[ts->top1--];
    } else {
        printf("Stack UnderFlow in stack1\n");
        exit(EXIT_FAILURE);
    }
}

// Function to pop an element from the second stack
int pop2(TwoStacks *ts) {
    if (ts->top2 < MAX_SIZE) {
        return ts->arr[ts->top2++];
    } else {
        printf("Stack UnderFlow in stack2\n");
        exit(EXIT_FAILURE);
    }
}

// Function to check if both stacks are full
int isStackFull(TwoStacks *ts) {
    return ts->top1 >= ts->top2 - 1;
}

// Function to check if the first stack is empty
int isStack1Empty(TwoStacks *ts) {
    return ts->top1 == -1;
}

// Function to check if the second stack is empty
int isStack2Empty(TwoStacks *ts) {
    return ts->top2 == MAX_SIZE;
}

// Function to display the first stack
void displayStack1(TwoStacks *ts) {
    if (isStack1Empty(ts)) {
        printf("Stack 1 is empty\n");
    } else {
        printf("Stack 1: ");
        for (int i = 0; i <= ts->top1; i++) {
            printf("%d ", ts->arr[i]);
        }
        printf("\n");
    }
}

// Function to display the second stack
void displayStack2(TwoStacks *ts) {
    if (isStack2Empty(ts)) {
        printf("Stack 2 is empty\n");
    } else {
        printf("Stack 2: ");
        for (int i = MAX_SIZE - 1; i >= ts->top2; i--) {
            printf("%d ", ts->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    TwoStacks ts;
    initialize(&ts);

    int choice, stackNumber, value;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Check if Stacks are Full\n4. Check if Stack is Empty\n5. Display Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                printf("Enter value to push: ");
                scanf("%d", &value);
                if (stackNumber == 1) {
                    push1(&ts, value);
                } else if (stackNumber == 2) {
                    push2(&ts, value);
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 2:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    printf("Popped element from stack1: %d\n", pop1(&ts));
                } else if (stackNumber == 2) {
                    printf("Popped element from stack2: %d\n", pop2(&ts));
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 3:
                if (isStackFull(&ts)) {
                    printf("Both stacks are full\n");
                } else {
                    printf("Stacks are not full\n");
                }
                break;
            case 4:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    if (isStack1Empty(&ts)) {
                        printf("Stack 1 is empty\n");
                    } else {
                        printf("Stack 1 is not empty\n");
                    }
                } else if (stackNumber == 2) {
                    if (isStack2Empty(&ts)) {
                        printf("Stack 2 is empty\n");
                    } else {
                        printf("Stack 2 is not empty\n");
                    }
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 5:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    displayStack1(&ts);
                } else if (stackNumber == 2) {
                    displayStack2(&ts);
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}













4. WAP to implement following by using stack.  A. Factorial of a given number B. Generation of Fibonacci series

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Function to push an element to the stack
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(1);
    } else {
        s->arr[++s->top] = value;
    }
}

// Function to pop an element from the stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    } else {
        return s->arr[s->top--];
    }
}

// Function to calculate factorial using stack
int factorial(int n) {
    Stack s;
    initStack(&s);
    int result = 1;

    while (n > 0) {
        push(&s, n);
        n--;
    }

    while (!isEmpty(&s)) {
        result *= pop(&s);
    }

    return result;
}

// Function to generate Fibonacci series using stack
void fibonacci(int n) {
    if (n <= 0) {
        printf("Invalid number of terms. Must be greater than 0.\n");
        return;
    }
    
    Stack s;
    initStack(&s);
    int a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            push(&s, a);
        } else if (i == 1) {
            push(&s, b);
        } else {
            int next = a + b;
            a = b;
            b = next;
            push(&s, next);
        }
    }

    // Display the Fibonacci series
    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");
}

int main() {
    int choice, num;

    while (1) {
        printf("1. Factorial\n2. Fibonacci Series\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to find its factorial: ");
                scanf("%d", &num);
                printf("Factorial of %d is %d\n", num, factorial(num));
                break;
            case 2:
                printf("Enter a number to generate Fibonacci series up to that term: ");
                scanf("%d", &num);
                printf("Fibonacci series up to %d terms: ", num);
                fibonacci(num);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}











5. Write a Program to implement circular double ended queue where user can add and remove the elements from both front and rear of the queue

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int size;
} Deque;

// Function to initialize the deque
void initialize(Deque *dq) {
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
}

// Function to check if the deque is full
int isFull(Deque *dq) {
    return dq->size == MAX;
}

// Function to check if the deque is empty
int isEmpty(Deque *dq) {
    return dq->size == 0;
}

// Function to add an element at the front of the deque
void addFront(Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }

    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1;
    } else {
        dq->front = dq->front - 1;
    }

    dq->arr[dq->front] = value;
    dq->size++;
}

// Function to add an element at the rear of the deque
void addRear(Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }

    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    } else {
        dq->rear = dq->rear + 1;
    }

    dq->arr[dq->rear] = value;
    dq->size++;
}

// Function to delete an element from the front of the deque
void deleteFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return;
    }

    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = 0;
    } else if (dq->front == MAX - 1) {
        dq->front = 0;
    } else {
        dq->front = dq->front + 1;
    }

    dq->size--;
}

// Function to delete an element from the rear of the deque
void deleteRear(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return;
    }

    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = 0;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    } else {
        dq->rear = dq->rear - 1;
    }

    dq->size--;
}

// Function to display the deque
void display(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }

    int i = dq->front;
    printf("Deque elements: ");

    while (1) {
        printf("%d ", dq->arr[i]);
        if (i == dq->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main() {
    Deque dq;
    initialize(&dq);

    int choice, value;

    while (1) {
        printf("\n1. Add at front\n2. Add at rear\n3. Delete from front\n4. Delete from rear\n5. Display\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add at front: ");
                scanf("%d", &value);
                addFront(&dq, value);
                break;
            case 2:
                printf("Enter value to add at rear: ");
                scanf("%d", &value);
                addRear(&dq, value);
                break;
            case 3:
                deleteFront(&dq);
                break;
            case 4:
                deleteRear(&dq);
                break;
            case 5:
                display(&dq);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}










6. Write a Program to implement multiple two queues using array and perform following operations on it. A. Addq, B. Delq, C. Display Queue


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define NUM_QUEUES 3 // Number of queues

// Structure to represent a queue
typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to initialize the queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

// Function to add an element to the queue
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(q)) {
            q->front = 0;
            q->rear = 0;
        } else {
            q->rear = (q->rear + 1) % MAX_SIZE;
        }
        q->arr[q->rear] = value;
        printf("Enqueued %d to the queue.\n", value);
    }
}

// Function to remove an element from the queue
int dequeue(Queue *q) {
    int dequeuedValue;
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else if (q->front == q->rear) {
        dequeuedValue = q->arr[q->front];
        q->front = -1;
        q->rear = -1;
    } else {
        dequeuedValue = q->arr[q->front];
        q->front = (q->front + 1) % MAX_SIZE;
    }
    printf("Dequeued %d from the queue.\n", dequeuedValue);
    return dequeuedValue;
}

// Function to display the elements of the queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue: ");
        int i = q->front;
        while (i != q->rear) {
            printf("%d ", q->arr[i]);
            i = (i + 1) % MAX_SIZE;
        }
        printf("%d\n", q->arr[q->rear]);
    }
}

int main() {
    Queue queues[NUM_QUEUES]; // Array of queues

    // Initialize all queues
    for (int i = 0; i < NUM_QUEUES; i++) {
        initializeQueue(&queues[i]);
    }

    int choice, queueNumber, value;
    while (1) {
        printf("\n1. Addq (Enqueue)\n2. Delq (Dequeue)\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the queue number (1 to %d): ", NUM_QUEUES);
                scanf("%d", &queueNumber);
                if (queueNumber < 1 || queueNumber > NUM_QUEUES) {
                    printf("Invalid queue number\n");
                } else {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &value);
                    enqueue(&queues[queueNumber - 1], value);
                }
                break;
            case 2:
                printf("Enter the queue number (1 to %d): ", NUM_QUEUES);
                scanf("%d", &queueNumber);
                if (queueNumber < 1 || queueNumber > NUM_QUEUES) {
                    printf("Invalid queue number\n");
                } else {
                    dequeue(&queues[queueNumber - 1]);
                }
                break;
            case 3:
                printf("Enter the queue number (1 to %d): ", NUM_QUEUES);
                scanf("%d", &queueNumber);
                if (queueNumber < 1 || queueNumber > NUM_QUEUES) {
                    printf("Invalid queue number\n");
                } else {
                    displayQueue(&queues[queueNumber - 1]);
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}











7. WAP to perform addition of two polynomials using singly linked list

#include <stdio.h>
#include <stdlib.h>

// Node structure to represent a term in the polynomial
typedef struct Node {
    int coeff;
    int power;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertEnd(Node** head, int coeff, int power) {
    Node* newNode = createNode(coeff, power);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display the polynomial
void displayPoly(Node* head) {
    if (head == NULL) {
        printf("0");
        return;
    }
    while (head != NULL) {
        printf("%d*x^%d", head->coeff, head->power);
        head = head->next;
        if (head != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* temp1 = poly1;
    Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->power > temp2->power) {
            insertEnd(&result, temp1->coeff, temp1->power);
            temp1 = temp1->next;
        } else if (temp1->power < temp2->power) {
            insertEnd(&result, temp2->coeff, temp2->power);
            temp2 = temp2->next;
        } else {
            insertEnd(&result, temp1->coeff + temp2->coeff, temp1->power);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        insertEnd(&result, temp1->coeff, temp1->power);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        insertEnd(&result, temp2->coeff, temp2->power);
        temp2 = temp2->next;
    }

    return result;
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* result = NULL;

    int n, coeff, power;

    // Input for the first polynomial
    printf("Enter the number of terms for the first polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power for term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        insertEnd(&poly1, coeff, power);
    }

    // Input for the second polynomial
    printf("Enter the number of terms for the second polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power for term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        insertEnd(&poly2, coeff, power);
    }

    // Displaying the polynomials
    printf("First polynomial: ");
    displayPoly(poly1);
    printf("Second polynomial: ");
    displayPoly(poly2);

    // Adding the polynomials
    result = addPolynomials(poly1, poly2);

    // Displaying the result
    printf("Resultant polynomial: ");
    displayPoly(result);

    return 0;
}













8. Write an iterative Reverse() function that reverses a list by rearranging all the next pointers and the head pointer. Ideally, Reverse() should only need to make one pass of the list

#include <stdio.h>
#include <stdlib.h>

// Node structure to represent a single linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to reverse the linked list iteratively
void reverse(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the current node's pointer
        prev = current;        // Move pointers one position ahead
        current = next;
    }
    *head = prev;
}

// Function to display the linked list
void displayList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int n, data;

    // Input for the linked list
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    // Display the original linked list
    printf("Original list: ");
    displayList(head);

    // Reverse the linked list
    reverse(&head);

    // Display the reversed linked list
    printf("Reversed list: ");
    displayList(head);

    return 0;
}












9. WAP to create doubly linked list and perform following operations on it. A) Insert (all cases) 2. Delete (all cases)

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to insert a node after a given node in the doubly linked list
Node* insertAfter(Node* head, Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return head;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }
    prevNode->next = newNode;
    newNode->prev = prevNode;
    return head;
}

// Function to delete a node from the doubly linked list
Node* deleteNode(Node* head, Node* delNode) {
    if (head == NULL || delNode == NULL) {
        printf("Cannot delete node. List is empty or node does not exist.\n");
        return head;
    }
    if (head == delNode) {
        head = delNode->next;
    }
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    free(delNode);
    return head;
}

// Function to display the doubly linked list
void displayList(Node* head) {
    Node* temp = head;
    printf("Doubly linked list: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int choice, data, prevData;
    Node* prevNode;

    while (1) {
        printf("\n1. Insert at beginning\n2. Insert at end\n3. Insert after a node\n");
        printf("4. Delete first node\n5. Delete last node\n6. Delete a node after a given node\n");
        printf("7. Display list\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter data of the node after which to insert: ");
                scanf("%d", &prevData);
                prevNode = head;
                while (prevNode != NULL && prevNode->data != prevData) {
                    prevNode = prevNode->next;
                }
                if (prevNode != NULL) {
                    head = insertAfter(head, prevNode, data);
                } else {
                    printf("Node with given data not found. Cannot insert.\n");
                }
                break;
            case 4:
                head = deleteNode(head, head);
                break;
            case 5:
                if (head != NULL) {
                    Node* temp = head;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    head = deleteNode(head, temp);
                } else {
                    printf("List is empty. Cannot delete last node.\n");
                }
                break;
            case 6:
                if (head != NULL) {
                    printf("Enter data of the node after which to delete: ");
                    scanf("%d", &prevData);
                    prevNode = head;
                    while (prevNode != NULL && prevNode->data != prevData) {
                        prevNode = prevNode->next;
                    }
                    if (prevNode != NULL && prevNode->next != NULL) {
                        head = deleteNode(head, prevNode->next);
                    } else {
                        printf("Node not found or it is the last node. Cannot delete.\n");
                    }
                } else {
                    printf("List is empty. Cannot delete.\n");
                }
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}














10. WAP to merge two sorted Doubly linked lists and display their result

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to merge two sorted doubly linked lists
Node* mergeSortedLists(Node* list1, Node* list2) {
    Node* mergedList = NULL;
    Node* temp1 = list1;
    Node* temp2 = list2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data <= temp2->data) {
            mergedList = insertAtEnd(mergedList, temp1->data);
            temp1 = temp1->next;
        } else {
            mergedList = insertAtEnd(mergedList, temp2->data);
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        mergedList = insertAtEnd(mergedList, temp1->data);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        mergedList = insertAtEnd(mergedList, temp2->data);
        temp2 = temp2->next;
    }

    return mergedList;
}

// Function to display the doubly linked list
void displayList(Node* head) {
    Node* temp = head;
    printf("Doubly linked list: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Create and populate the first sorted doubly linked list
    Node* list1 = NULL;
    int num1, data1;
    printf("Enter the number of elements in the first list: ");
    scanf("%d", &num1);
    printf("Enter the elements in ascending order: ");
    for (int i = 0; i < num1; i++) {
        scanf("%d", &data1);
        list1 = insertAtEnd(list1, data1);
    }

    // Create and populate the second sorted doubly linked list
    Node* list2 = NULL;
    int num2, data2;
    printf("Enter the number of elements in the second list: ");
    scanf("%d", &num2);
    printf("Enter the elements in ascending order: ");
    for (int i = 0; i < num2; i++) {
        scanf("%d", &data2);
        list2 = insertAtEnd(list2, data2);
    }

    // Merge the two sorted lists
    Node* mergedList = mergeSortedLists(list1, list2);

    // Display the merged list
    displayList(mergedList);

    return 0;
}










11.  Implement Push and POP operations of STACK on Doubly linked lists

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to push a node onto the stack
void push(Node** top, int data) {
    Node* newNode = createNode(data);
    if (*top == NULL) {
        *top = newNode;
    } else {
        newNode->next = *top;
        (*top)->prev = newNode;
        *top = newNode;
    }
}

// Function to pop a node from the stack
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow. Cannot pop from empty stack.\n");
        exit(1);
    }
    int data = (*top)->data;
    Node* temp = *top;
    *top = (*top)->next;
    if (*top != NULL) {
        (*top)->prev = NULL;
    }
    free(temp);
    return data;
}

// Function to display the stack
void displayStack(Node* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    Node* top = NULL;
    int choice, data;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display Stack\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&top, data);
                break;
            case 2:
                printf("Popped element: %d\n", pop(&top));
                break;
            case 3:
                displayStack(top);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}











12. Implement ADD and DELETE operations of QUEUE on Doubly linked lists

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Structure to represent a queue
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the queue
void initializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Function to add an element to the queue
void enqueue(Queue* q, int data) {
    Node* newNode = createNode(data);
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        newNode->prev = q->rear;
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to delete an element from the queue
int dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        exit(1);
    }
    int data = q->front->data;
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    } else {
        q->front->prev = NULL;
    }
    free(temp);
    return data;
}

// Function to display the queue
void displayQueue(Queue q) {
    if (q.front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    Node* temp = q.front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue q;
    initializeQueue(&q);
    int choice, data;

    while (1) {
        printf("\n1. Add\n2. Delete\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to add: ");
                scanf("%d", &data);
                enqueue(&q, data);
                break;
            case 2:
                printf("Deleted element: %d\n", dequeue(&q));
                break;
            case 3:
                displayQueue(q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}











13.  Write a Program to create a Binary Tree and perform following non-recursive operations on it. a. Preorder Traversal b. Count Leaf Nodes c. Count total no. of nodes d. Display height of a tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Stack {
    Node* arr[100];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    stack->arr[++stack->top] = node;
}

Node* pop(Stack* stack) {
    return stack->arr[stack->top--];
}

Node* peek(Stack* stack) {
    return stack->arr[stack->top];
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL) {
            current->left = createNode(data);
            break;
        } else {
            push(&stack, current->left);
        }
        if (current->right == NULL) {
            current->right = createNode(data);
            break;
        } else {
            push(&stack, current->right);
        }
    }
    return root;
}

void preorder(Node* root) {
    if (root == NULL) return;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        printf("%d ", current->data);
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    printf("\n");
}

int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int count = 0;
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    return count;
}

int countTotalNodes(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int count = 0;
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        count++;
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    return count;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int height = 0;
    while (1) {
        int nodeCount = stack.top + 1;
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            Node* node = pop(&stack);
            if (node->left != NULL) push(&stack, node->left);
            if (node->right != NULL) push(&stack, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Preorder Traversal\n");
        printf("3. Count Leaf Nodes\n");
        printf("4. Count Total Nodes\n");
        printf("5. Display Height\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
            case 3:
                printf("Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 4:
                printf("Total Nodes: %d\n", countTotalNodes(root));
                break;
            case 5:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}












14. Write a Program to create a Binary Tree and perform following non-recursive operations on it. a. Inorder Traversal b. Mirror Image c. Count total no. of nodes d. Display height of a tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Stack {
    Node* arr[100];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    stack->arr[++stack->top] = node;
}

Node* pop(Stack* stack) {
    return stack->arr[stack->top--];
}

Node* peek(Stack* stack) {
    return stack->arr[stack->top];
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL) {
            current->left = createNode(data);
            break;
        } else {
            push(&stack, current->left);
        }
        if (current->right == NULL) {
            current->right = createNode(data);
            break;
        } else {
            push(&stack, current->right);
        }
    }
    return root;
}

void inorder(Node* root) {
    Stack stack;
    initStack(&stack);
    Node* current = root;
    while (current != NULL || !isEmpty(&stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

void mirror(Node* root) {
    if (root == NULL) return;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        Node* temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left != NULL) {
            push(&stack, current->left);
        }
        if (current->right != NULL) {
            push(&stack, current->right);
        }
    }
}

int countTotalNodes(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int count = 0;
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        count++;
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    return count;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int height = 0;
    while (1) {
        int nodeCount = stack.top + 1;
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            Node* node = pop(&stack);
            if (node->left != NULL) push(&stack, node->left);
            if (node->right != NULL) push(&stack, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Mirror Image\n");
        printf("4. Count Total Nodes\n");
        printf("5. Display Height\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                break;
            case 3:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 4:
                printf("Total Nodes: %d\n", countTotalNodes(root));
                break;
            case 5:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











15. Write a Program to create a Binary Tree and perform following non-recursive operations on it. a. Postorder Traversal b. Display Leaf Nodes c. Count total no. of  Leaf nodes d. Display height of a tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Stack {
    Node* arr[100];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    stack->arr[++stack->top] = node;
}

Node* pop(Stack* stack) {
    return stack->arr[stack->top--];
}

Node* peek(Stack* stack) {
    return stack->arr[stack->top];
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL) {
            current->left = createNode(data);
            break;
        } else {
            push(&stack, current->left);
        }
        if (current->right == NULL) {
            current->right = createNode(data);
            break;
        } else {
            push(&stack, current->right);
        }
    }
    return root;
}

void postorder(Node* root) {
    if (root == NULL) return;
    Stack stack1, stack2;
    initStack(&stack1);
    initStack(&stack2);
    push(&stack1, root);
    while (!isEmpty(&stack1)) {
        Node* current = pop(&stack1);
        push(&stack2, current);
        if (current->left != NULL) {
            push(&stack1, current->left);
        }
        if (current->right != NULL) {
            push(&stack1, current->right);
        }
    }
    while (!isEmpty(&stack2)) {
        printf("%d ", pop(&stack2)->data);
    }
    printf("\n");
}

void displayLeafNodes(Node* root) {
    if (root == NULL) return;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    printf("\n");
}

int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    int leafCount = 0;
    initStack(&stack);
    push(&stack, root);
    while (!isEmpty(&stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
    return leafCount;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    Stack stack;
    initStack(&stack);
    push(&stack, root);
    int height = 0;
    while (1) {
        int nodeCount = stack.top + 1;
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            Node* node = pop(&stack);
            if (node->left != NULL) push(&stack, node->left);
            if (node->right != NULL) push(&stack, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Postorder Traversal\n");
        printf("3. Display Leaf Nodes\n");
        printf("4. Count Leaf Nodes\n");
        printf("5. Display Height\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
            case 3:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;
            case 4:
                printf("Total Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











16. Write a Program to create a Binary Tree and perform following non-recursive operations on it. a. Level-wise Traversal b. Display Leaf Nodes c. Count total no. of Leaf nodes d. Display height of a tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node* arr[100];
    int front;
    int rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(Queue* queue, Node* node) {
    if (queue->rear == 99) {
        printf("Queue overflow\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = node;
}

Node* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue underflow\n");
        return NULL;
    }
    return queue->arr[queue->front++];
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        if (current->left == NULL) {
            current->left = newNode;
            break;
        } else {
            enqueue(&queue, current->left);
        }
        if (current->right == NULL) {
            current->right = newNode;
            break;
        } else {
            enqueue(&queue, current->right);
        }
    }
    return root;
}

void levelWiseTraversal(Node* root) {
    if (root == NULL) return;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        printf("%d ", current->data);
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    printf("\n");
}

void displayLeafNodes(Node* root) {
    if (root == NULL) return;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    printf("\n");
}

int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    Queue queue;
    int leafCount = 0;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    return leafCount;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    int height = 0;
    while (1) {
        int nodeCount = queue.rear - queue.front + 1;
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            Node* node = dequeue(&queue);
            if (node->left != NULL) enqueue(&queue, node->left);
            if (node->right != NULL) enqueue(&queue, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Level-wise Traversal\n");
        printf("3. Display Leaf Nodes\n");
        printf("4. Count Leaf Nodes\n");
        printf("5. Display Height\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Level-wise Traversal: ");
                levelWiseTraversal(root);
                break;
            case 3:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;
            case 4:
                printf("Total Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}













17.  Write a Program to create a Binary Tree and perform following non-recursive operations on it. a. Levelwise display b. Mirror image c. Display height of a tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node* arr[100];
    int front;
    int rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(Queue* queue, Node* node) {
    if (queue->rear == 99) {
        printf("Queue overflow\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = node;
}

Node* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue underflow\n");
        return NULL;
    }
    return queue->arr[queue->front++];
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        if (current->left == NULL) {
            current->left = newNode;
            break;
        } else {
            enqueue(&queue, current->left);
        }
        if (current->right == NULL) {
            current->right = newNode;
            break;
        } else {
            enqueue(&queue, current->right);
        }
    }
    return root;
}

void levelWiseDisplay(Node* root) {
    if (root == NULL) return;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        printf("%d ", current->data);
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    printf("\n");
}

void mirrorImage(Node* root) {
    if (root == NULL) return;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        Node* temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    int height = 0;
    while (1) {
        int nodeCount = queue.rear - queue.front + 1;
        if (nodeCount == 0) return height;
        height++;
        while (nodeCount > 0) {
            Node* node = dequeue(&queue);
            if (node->left != NULL) enqueue(&queue, node->left);
            if (node->right != NULL) enqueue(&queue, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Level-wise Display\n");
        printf("3. Mirror Image\n");
        printf("4. Display Height\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Level-wise Display: ");
                levelWiseDisplay(root);
                break;
            case 3:
                mirrorImage(root);
                printf("Tree mirrored successfully.\n");
                break;
            case 4:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











18. Write a program to illustrate operations on a BST holding numeric keys The menu must include 1_Insert 2_Delete 3_Find 4_Level wise Display

#include <stdio.h>
#include <stdlib.h>

// Definition of the BST node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new BST node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
// Node* insert(Node* root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else if (data > root->data) {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// Non-recursive function to insert a node in the Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Data already exists in the tree, no need to insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}






// Function to find the minimum value node in the BST
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
Node* delete(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
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
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Function to find a node in the BST
Node* find(Node* root, int data) {
    while (root != NULL) {
        if (data < root->data) {
            root = root->left;
        } else if (data > root->data) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

// Definition of the Queue for level-wise display
typedef struct Queue {
    Node* arr[100];
    int front;
    int rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(Queue* queue, Node* node) {
    if (queue->rear == 99) {
        printf("Queue overflow\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = node;
}

Node* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue underflow\n");
        return NULL;
    }
    return queue->arr[queue->front++];
}

// Function for level-wise display of the BST
void levelWiseDisplay(Node* root) {
    if (root == NULL) return;
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);
    while (!isQueueEmpty(&queue)) {
        Node* current = dequeue(&queue);
        printf("%d ", current->data);
        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    printf("\n");
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Level-wise Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            case 3:
                printf("Enter value to find: ");
                scanf("%d", &value);
                Node* foundNode = find(root, value);
                if (foundNode != NULL) {
                    printf("Node %d found in the BST.\n", value);
                } else {
                    printf("Node %d not found in the BST.\n", value);
                }
                break;
            case 4:
                printf("Level-wise Display: ");
                levelWiseDisplay(root);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}












19. Write a program to illustrate operations on a BST holding numeric keys The menu must include • Insert • Mirror Image • Find • Height of the tree

#include <stdio.h>
#include <stdlib.h>

// Definition of the BST node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new BST node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find a node in the BST
Node* find(Node* root, int data) {
    while (root != NULL) {
        if (data < root->data) {
            root = root->left;
        } else if (data > root->data) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

// Function to create a mirror image of the BST
Node* mirror(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
    return root;
}

// Function to calculate the height of the BST
int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to perform in-order traversal of the BST (for display)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Mirror Image\n");
        printf("3. Find\n");
        printf("4. Height of the tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("In-order traversal of the BST: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                root = mirror(root);
                printf("Mirror image created. In-order traversal of the BST: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Enter value to find: ");
                scanf("%d", &value);
                Node* foundNode = find(root, value);
                if (foundNode != NULL) {
                    printf("Node %d found in the BST.\n", value);
                } else {
                    printf("Node %d not found in the BST.\n", value);
                }
                break;
            case 4:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











20.   Write a Program to create a Binary Tree and perform following Non-recursive operations on it a-Postorder Traversal  c-Display Leaf Nodes d-Mirror Image

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of the Binary Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Queue structure for level-order insertion
typedef struct Queue {
    Node* data;
    struct Queue* next;
} Queue;

Queue* createQueueNode(Node* data) {
    Queue* queueNode = (Queue*)malloc(sizeof(Queue));
    queueNode->data = data;
    queueNode->next = NULL;
    return queueNode;
}

void enqueue(Queue** rear, Node* data) {
    Queue* queueNode = createQueueNode(data);
    if (*rear == NULL) {
        *rear = queueNode;
    } else {
        Queue* temp = *rear;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = queueNode;
    }
}

Node* dequeue(Queue** front) {
    if (*front == NULL) return NULL;
    Queue* temp = *front;
    *front = (*front)->next;
    Node* dequeued = temp->data;
    free(temp);
    return dequeued;
}

bool isQueueEmpty(Queue* front) {
    return !front;
}

// Function to create a new Binary Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Non-recursive function to insert a node in the Binary Tree (level-order)
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Queue* queue = NULL;
    enqueue(&queue, root);

    while (!isQueueEmpty(queue)) {
        Node* current = dequeue(&queue);

        if (current->left == NULL) {
            current->left = newNode;
            break;
        } else {
            enqueue(&queue, current->left);
        }

        if (current->right == NULL) {
            current->right = newNode;
            break;
        } else {
            enqueue(&queue, current->right);
        }
    }

    return root;
}

// Stack structure for iterative tree traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

Stack* createStackNode(Node* data) {
    Stack* stackNode = (Stack*)malloc(sizeof(Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

void push(Stack** root, Node* data) {
    Stack* stackNode = createStackNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

Node* pop(Stack** root) {
    if (*root == NULL) return NULL;
    Stack* temp = *root;
    *root = (*root)->next;
    Node* popped = temp->data;
    free(temp);
    return popped;
}

bool isStackEmpty(Stack* root) {
    return !root;
}

Node* peek(Stack* root) {
    if (isStackEmpty(root)) return NULL;
    return root->data;
}

// Non-recursive function to perform postorder traversal
void postorderTraversal(Node* root) {
    if (root == NULL) return;
    Stack *stack = NULL;
    Node *current = root, *lastVisited = NULL;
    while (!isStackEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(&stack, current);
            current = current->left;
        } else {
            Node *peekNode = peek(stack);
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                printf("%d ", peekNode->data);
                lastVisited = pop(&stack);
            }
        }
    }
    printf("\n");
}

// Non-recursive function to display leaf nodes
void displayLeafNodes(Node* root) {
    if (root == NULL) return;
    Stack *stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node *current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    printf("\n");
}

// Function to create a mirror image of the Binary Tree
void mirror(Node* root) {
    if (root == NULL) return;
    Stack *stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node *current = pop(&stack);
        Node *temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left) push(&stack, current->left);
        if (current->right) push(&stack, current->right);
    }
}

// Main function to demonstrate the operations
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Postorder Traversal\n");
        printf("3. Display Leaf Nodes\n");
        printf("4. Mirror Image\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                break;
            case 3:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;
            case 4:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











21. Write a Program to create a Binary Search Tree and perform following non-recursive operations on it. a. Inorder Traversal b. Display Number of Leaf Nodes c. Mirror Image

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of the Binary Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for iterative tree traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

Stack* createStackNode(Node* data) {
    Stack* stackNode = (Stack*)malloc(sizeof(Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

void push(Stack** root, Node* data) {
    Stack* stackNode = createStackNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

Node* pop(Stack** root) {
    if (*root == NULL) return NULL;
    Stack* temp = *root;
    *root = (*root)->next;
    Node* popped = temp->data;
    free(temp);
    return popped;
}

bool isStackEmpty(Stack* root) {
    return !root;
}

Node* peek(Stack* root) {
    if (isStackEmpty(root)) return NULL;
    return root->data;
}

// Function to create a new Binary Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the Binary Search Tree
// Node* insert(Node* root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else if (data > root->data) {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// Non-recursive function to insert a node in the Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Data already exists in the tree, no need to insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}




// Non-recursive function to perform inorder traversal
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    Stack *stack = NULL;
    Node *current = root;
    while (!isStackEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(&stack, current);
            current = current->left;
        } else {
            current = pop(&stack);
            printf("%d ", current->data);
            current = current->right;
        }
    }
    printf("\n");
}

// Non-recursive function to count leaf nodes
int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    int count = 0;
    Stack *stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node *current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    return count;
}

// Function to create a mirror image of the Binary Tree
void mirror(Node* root) {
    if (root == NULL) return;
    Stack *stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node *current = pop(&stack);
        Node *temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left) push(&stack, current->left);
        if (current->right) push(&stack, current->right);
    }
}

// Main function to demonstrate the operations
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Display Number of Leaf Nodes\n");
        printf("4. Mirror Image\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;
            case 3:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 4:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}











22. Write a Program to create a Binary Search Tree and perform following non-recursive operations on it. a. Ino0rder Traversal b. Display Number of Leaf Nodes c. Mirror Image

#include <stdio.h>
#include <stdlib.h>

// Definition of the Binary Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for iterative tree traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

Stack* createStackNode(Node* data) {
    Stack* stackNode = (Stack*)malloc(sizeof(Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

void push(Stack** root, Node* data) {
    Stack* stackNode = createStackNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

Node* pop(Stack** root) {
    if (*root == NULL) return NULL;
    Stack* temp = *root;
    *root = (*root)->next;
    Node* popped = temp->data;
    free(temp);
    return popped;
}

int isStackEmpty(Stack* root) {
    return !root;
}

// Function to create a new Binary Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the Binary Search Tree
// Node* insert(Node* root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else if (data > root->data) {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// Non-recursive function to insert a node in the Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Data already exists in the tree, no need to insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}



// Non-recursive function to perform preorder traversal
void preorderTraversal(Node* root) {
    if (root == NULL) return;
    Stack* stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node* current = pop(&stack);
        printf("%d ", current->data);
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    printf("\n");
}

// Non-recursive function to count total number of nodes
int countNodes(Node* root) {
    if (root == NULL) return 0;
    int count = 0;
    Stack* stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node* current = pop(&stack);
        count++;
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    return count;
}

// Non-recursive function to display leaf nodes
void displayLeafNodes(Node* root) {
    if (root == NULL) return;
    Stack* stack = NULL;
    push(&stack, root);
    while (!isStackEmpty(stack)) {
        Node* current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    printf("\n");
}

// Main function to demonstrate the operations
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Preorder Traversal\n");
        printf("3. Display total Number of Nodes\n");
        printf("4. Display Leaf nodes\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;
            case 3:
                printf("Total Number of Nodes: %d\n", countNodes(root));
                break;
            case 4:
                printf("Leaf nodes: ");
                displayLeafNodes(root);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}












23. Write a Program to create a Binary Search Tree and perform deletion of a node from it. Also display the tree in nonrecursive postorder way

#include <stdio.h>
#include <stdlib.h>

// Definition of the Binary Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for iterative tree traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

Stack* createStackNode(Node* data) {
    Stack* stackNode = (Stack*)malloc(sizeof(Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

void push(Stack** root, Node* data) {
    Stack* stackNode = createStackNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

Node* pop(Stack** root) {
    if (*root == NULL) return NULL;
    Stack* temp = *root;
    *root = (*root)->next;
    Node* popped = temp->data;
    free(temp);
    return popped;
}

int isStackEmpty(Stack* root) {
    return !root;
}

// Function to create a new Binary Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the Binary Search Tree
// Node* insert(Node* root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else if (data > root->data) {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// Non-recursive function to insert a node in the Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Data already exists in the tree, no need to insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}




// Function to find the minimum value node in a tree
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the Binary Search Tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
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
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the tree in non-recursive postorder traversal
void postorderTraversal(Node* root) {
    if (root == NULL) return;
    Stack* stack1 = NULL;
    Stack* stack2 = NULL;
    push(&stack1, root);
    while (!isStackEmpty(stack1)) {
        Node* current = pop(&stack1);
        push(&stack2, current);
        if (current->left) push(&stack1, current->left);
        if (current->right) push(&stack1, current->right);
    }
    while (!isStackEmpty(stack2)) {
        Node* current = pop(&stack2);
        printf("%d ", current->data);
    }
    printf("\n");
}

// Main function to demonstrate the operations
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display Non-recursive Postorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Non-recursive Postorder Traversal: ");
                postorderTraversal(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}










24. Write a Program to create a Binary Search Tree and display it levelwise. Also perform deletion of a node from it

#include <stdio.h>
#include <stdlib.h>

// Definition of the Binary Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Queue structure for level-wise traversal
typedef struct Queue {
    Node* data;
    struct Queue* next;
} Queue;

Queue* createQueueNode(Node* data) {
    Queue* queueNode = (Queue*)malloc(sizeof(Queue));
    queueNode->data = data;
    queueNode->next = NULL;
    return queueNode;
}

void enqueue(Queue** front, Queue** rear, Node* data) {
    Queue* queueNode = createQueueNode(data);
    if (*rear == NULL) {
        *front = *rear = queueNode;
        return;
    }
    (*rear)->next = queueNode;
    *rear = queueNode;
}

Node* dequeue(Queue** front, Queue** rear) {
    if (*front == NULL) return NULL;
    Queue* temp = *front;
    Node* dequeued = temp->data;
    *front = (*front)->next;
    if (*front == NULL) *rear = NULL;
    free(temp);
    return dequeued;
}

int isQueueEmpty(Queue* front) {
    return !front;
}

// Function to create a new Binary Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the Binary Search Tree
// Node* insert(Node* root, int data) {
//     if (root == NULL) {
//         return createNode(data);
//     }
//     if (data < root->data) {
//         root->left = insert(root->left, data);
//     } else if (data > root->data) {
//         root->right = insert(root->right, data);
//     }
//     return root;
// }


// Non-recursive function to insert a node in the Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // Data already exists in the tree, no need to insert
            free(newNode);
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}



// Function to find the minimum value node in a tree
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the Binary Search Tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
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
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display the tree level-wise
void levelOrderTraversal(Node* root) {
    if (root == NULL) return;
    Queue* front = NULL;
    Queue* rear = NULL;
    enqueue(&front, &rear, root);
    while (!isQueueEmpty(front)) {
        Node* current = dequeue(&front, &rear);
        printf("%d ", current->data);
        if (current->left) enqueue(&front, &rear, current->left);
        if (current->right) enqueue(&front, &rear, current->right);
    }
    printf("\n");
}

// Main function to demonstrate the operations
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display Level-wise\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Level-wise Traversal: ");
                levelOrderTraversal(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}










26. Write a program to efficiently search a particular employee record by using Tree data structure. Also sort the data on emp-id.in ascending order

#include <stdio.h>
#include <stdlib.h>

// Structure for an employee record
typedef struct Employee {
    int emp_id;
    char name[50];
    struct Employee* left;
    struct Employee* right;
} Employee;

// Function to create a new employee record
Employee* createEmployee(int emp_id, const char* name) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if (newEmployee == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert a new employee record into the BST
Employee* insertEmployee(Employee* root, int emp_id, const char* name) {
    if (root == NULL) {
        return createEmployee(emp_id, name);
    }
    if (emp_id < root->emp_id) {
        root->left = insertEmployee(root->left, emp_id, name);
    } else if (emp_id > root->emp_id) {
        root->right = insertEmployee(root->right, emp_id, name);
    }
    return root;
}

// Function to search for an employee record by emp_id
Employee* searchEmployee(Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) {
        return root;
    }
    if (emp_id < root->emp_id) {
        return searchEmployee(root->left, emp_id);
    } else {
        return searchEmployee(root->right, emp_id);
    }
}

// Function to display employee records in ascending order of emp_id (inorder traversal)
void displayEmployees(Employee* root) {
    if (root != NULL) {
        displayEmployees(root->left);
        printf("Emp ID: %d, Name: %s\n", root->emp_id, root->name);
        displayEmployees(root->right);
    }
}

int main() {
    Employee* root = NULL;

    // Insert employee records
    root = insertEmployee(root, 101, "John");
    root = insertEmployee(root, 105, "Alice");
    root = insertEmployee(root, 103, "Bob");
    root = insertEmployee(root, 109, "Emma");
    root = insertEmployee(root, 107, "Michael");

    // Display all employee records sorted by emp_id
    printf("Employee Records (Sorted by Emp ID):\n");
    displayEmployees(root);

    // Search for a particular employee record
    int search_emp_id = 103;
    Employee* found_employee = searchEmployee(root, search_emp_id);
    if (found_employee != NULL) {
        printf("\nEmployee Record Found for Emp ID %d: %s\n", search_emp_id, found_employee->name);
    } else {
        printf("\nEmployee Record not found for Emp ID %d\n", search_emp_id);
    }

    // Free memory allocated for the BST (not necessary in this program)

    return 0;
}









27. Write a Program to create Inorder Threaded Binary Tree and Traverse it in Preorder way

#include <stdio.h>
#include <stdlib.h>

// Definition of Node structure
typedef struct Node {
    int data;
    struct Node *left, *right;
    int leftIsThreaded, rightIsThreaded;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->leftIsThreaded = newNode->rightIsThreaded = 1;
    return newNode;
}

// Function to insert a node in double-threaded binary tree
void insert(Node** root, int data) {
    Node* newNode = createNode(data);

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            if (!current->leftIsThreaded) {
                current = current->left;
            } else {
                newNode->left = current->left;
                newNode->right = current;
                current->left = newNode;
                current->leftIsThreaded = 0;
                return;
            }
        } else {
            if (!current->rightIsThreaded) {
                current = current->right;
            } else {
                newNode->right = current->right;
                newNode->left = current;
                current->right = newNode;
                current->rightIsThreaded = 0;
                return;
            }
        }
    }
}

// Function to find the leftmost node
Node* leftMost(Node* root) {
    if (root == NULL) return NULL;

    while (root->left != NULL && !root->leftIsThreaded) {
        root = root->left;
    }

    return root;
}

// Function to perform inorder traversal of double-threaded binary tree
void inorderTraversal(Node* root) {
    Node* current = leftMost(root);

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->rightIsThreaded) {
            current = current->right;
        } else {
            current = leftMost(current->right);
        }
    }
}

// Function to perform preorder traversal of double-threaded binary tree
void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    Node* current = root;
    while (current != NULL) {
        printf("%d ", current->data);

        if (!current->leftIsThreaded && current->left != NULL) {
            current = current->left;
        } else if (!current->rightIsThreaded && current->right != NULL) {
            current = current->right;
        } else {
            // Traverse up using the threaded links
            while (current != NULL && current->rightIsThreaded) {
                current = current->right;
            }
            if (current != NULL) {
                current = current->right;
            }
        }
    }
}

int main() {
    Node* root = NULL;
    int value, choice;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&root, value);
                break;
            case 2:
                printf("Inorder traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}










28. Write a Program to create Inorder Threaded Binary Tree and Traverse it in Inorder way

#include<stdio.h>
#include<stdlib.h>

struct node{
    int val;
    int lbit; 
    int rbit;
    struct node *left, *right;
};

struct node* insertTBT(struct node *head, int data){
    struct node *temp,*p;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->lbit = temp->rbit = 0;
    temp->val = data;
    if(head->lbit == 0){
        head->left = temp;
        temp->left = temp->right = head;
        head->lbit = 1;
        return head;
    }
    p = head->left;

    while(1){
        if(data < p->val && p->lbit == 1){
            p = p->left;
        }
        else if(data > p->val && p->rbit == 1){
            p = p->right;
        }
        else{
            break;
        }
    }

    if(data < p->val){
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lbit = 1;
    }

    if(data > p->val){
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rbit = 1;
    }
    return head;
}

void inorderTBT(struct node *root) {
    struct node *temp = root->left;

    while(temp->lbit == 1){
        temp = temp->left;
    }

    while(temp != root){
        printf("%d - ",temp->val);
        if(temp->rbit == 1){
            temp = temp->right;
            while(temp->lbit == 1){
                temp = temp->left;
            }
        }
        else{
            temp = temp->right;
        }
    }
}

int main(){
    int data;
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->lbit = 0;
    head->rbit = 1;
    head->left = head->right = head;

    int choice;
    int x;
    
    while(1) {
        printf("\n\n\t Threaded Binary Tree Menu:\n\n");
        printf("1. Create TBT\n");
        printf("2. Insert node \n");
        printf("3. Inorder Traversal\n");
        printf("4. Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the how many nodes :");
                scanf("%d",&x);
                break;
            case 2:
                printf("\nEnter the data : ");
                for(int i=0; i<x; i++){
                    scanf("%d",&data);
                    head = insertTBT(head, data);
                }
                break;
            case 3:
                printf("\nInorder Traversal: ");
                inorderTBT(head);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}











29. Write a Program to implement AVL tree and perform different rotations on it and display it Levelwise

#include <stdio.h>
#include <stdlib.h>

// Structure for a node in AVL Tree
typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Function to create a new node
AVLNode* createNode(int data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to get the height of a node
int getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Function to perform single right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    // Return new root
    return x;
}

// Function to perform single left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL Tree
AVLNode* insert(AVLNode* node, int data) {
    // Perform standard BST insertion
    if (node == NULL) return createNode(data);

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        // Duplicate keys are not allowed
        return node;
    }

    // Update height of this ancestor node
    node->height = 1 + ((getHeight(node->left) > getHeight(node->right)) ? getHeight(node->left) : getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to print AVL tree in level order
void printLevelOrder(AVLNode* root) {
    if (root == NULL) return;

    // Create an auxiliary queue
    AVLNode* queue[1000];
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;

    while (front < rear) {
        AVLNode* tempNode = queue[front++];

        // Print the data of the current node
        printf("%d ", tempNode->data);

        // Enqueue left child
        if (tempNode->left != NULL) {
            queue[rear++] = tempNode->left;
        }

        // Enqueue right child
        if (tempNode->right != NULL) {
            queue[rear++] = tempNode->right;
        }
    }
    printf("\n");
}

int main() {
    AVLNode* root = NULL;
    int numNodes, data;

    // Input the number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    // Input the values of the nodes
    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }

    // Print the AVL Tree level-wise
    printf("AVL Tree Level-wise: ");
    printLevelOrder(root);

    return 0;
}











30. Write a Program to accept a graph from user and represent it with Adjacency Matrix and perform BFS traversals on it

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Function to initialize the graph
void initializeGraph(Graph *graph) {
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->vertices[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph *graph, int from, int to) {
    graph->vertices[from][to] = 1;
    graph->vertices[to][from] = 1; // For undirected graph
    if (from > graph->numVertices) graph->numVertices = from;
    if (to > graph->numVertices) graph->numVertices = to;
}

// Function to perform BFS traversal
void BFS(Graph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    // Enqueue the starting vertex
    queue[++rear] = startVertex;
    visited[startVertex] = 1;

    while (front < rear) {
        // Dequeue a vertex from the queue
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        // Enqueue all adjacent vertices of the dequeued vertex that are not yet visited
        for (int i = 1; i <= graph->numVertices; i++) {
            if (graph->vertices[currentVertex][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

// Function to print the adjacency matrix with row and column names
// Function to print the adjacency matrix with row and column names
void printMatrix(Graph *graph) {
    printf("Adjacency Matrix:\n");
    printf("   |");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    printf("---+");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("---");
    }
    printf("\n");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("%2d |", i);
        for (int j = 1; j <= graph->numVertices; j++) {
            printf("%2d ", graph->vertices[i][j]);
        }
        printf("\n");
    }
}


int main() {
    Graph graph;
    initializeGraph(&graph);

    int numEdges, from, to;

    // Input the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Input the edges
    printf("Enter the edges (from to): \n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &from, &to);
        addEdge(&graph, from, to);
    }

    // Print the adjacency matrix with row and column names
    printMatrix(&graph);

    // Input the starting vertex for BFS
    int startVertex;
    printf("\nEnter the starting vertex for BFS: ");
    scanf("%d", &startVertex);

    printf("BFS Traversal starting from vertex %d: ", startVertex);
    BFS(&graph, startVertex);
    printf("\n");

    return 0;
}












31. Write a Program to accept a graph from user and represent it with Adjacency Lists and perform BFS traversals on it

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for representing a node in adjacency list
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure for representing adjacency list
typedef struct {
    AdjListNode* head;
} AdjList;

// Structure for representing the graph
typedef struct {
    int numVertices;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given number of vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Create an array of adjacency lists. Size of the array will be numVertices.
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src.
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency lists
void printAdjLists(Graph* graph) {
    printf("Adjacency Lists:\n");
    for (int v = 0; v < graph->numVertices; ++v) {
        printf("Vertex %d: ", v);
        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            printf("%d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to perform Breadth First Search (BFS) traversal
void BFS(Graph* graph, int startVertex) {
    // Create a boolean array to mark visited vertices
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    // Create a queue for BFS
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    // Traverse the graph
    printf("BFS Traversal starting from vertex %d: ", startVertex);
    while (front < rear) {
        // Dequeue a vertex from the queue and print it
        int vertex = queue[front++];
        printf("%d ", vertex);

        // Get all adjacent vertices of the dequeued vertex
        AdjListNode* adjNode = graph->array[vertex].head;
        while (adjNode) {
            int adjVertex = adjNode->dest;
            // If adjacent vertex is not visited, mark it as visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            adjNode = adjNode->next;
        }
    }
    printf("\n");

    // Free dynamically allocated memory
    free(visited);
    free(queue);
}

int main() {
    int numVertices, numEdges, from, to;

    // Input the number of vertices and edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    // Create a graph with given number of vertices
    Graph* graph = createGraph(numVertices);

    // Input the edges
    printf("Enter the edges (from to): \n");
    for (int i = 0; i < numEdges; ++i) {
        scanf("%d %d", &from, &to);
        addEdge(graph, from, to);
    }

    // Print the adjacency lists
    printAdjLists(graph);

    // Input the starting vertex for BFS traversal
    int startVertex;
    printf("Enter the starting vertex for BFS traversal: ");
    scanf("%d", &startVertex);

    // Perform BFS traversal starting from the given vertex
    BFS(graph, startVertex);

    // Free dynamically allocated memory
    free(graph);

    return 0;
}










32. Write a Program to accept a graph from user and represent it with Adjacency Matrix and perform DFS traversals on it

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Function to initialize the graph
void initializeGraph(Graph *graph) {
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->vertices[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph *graph, int from, int to) {
    graph->vertices[from][to] = 1;
    graph->vertices[to][from] = 1; // For undirected graph
    if (from > graph->numVertices) graph->numVertices = from;
    if (to > graph->numVertices) graph->numVertices = to;
}

// Function for Depth-First Search traversal
void DFS(Graph *graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 1; i <= graph->numVertices; i++) {
        if (graph->vertices[vertex][i] && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

// Function to perform DFS traversal
void DFSTraversal(Graph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");
}

// Function to print the adjacency matrix with row and column names
void printMatrix(Graph *graph) {
    printf("Adjacency Matrix:\n");
    printf("   |");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    printf("---+");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("---");
    }
    printf("\n");
    for (int i = 1; i <= graph->numVertices; i++) {
        printf("%2d |", i);
        for (int j = 1; j <= graph->numVertices; j++) {
            printf("%2d ", graph->vertices[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph graph;
    initializeGraph(&graph);

    int numEdges, from, to;

    // Input the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Input the edges
    printf("Enter the edges (from to): \n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &from, &to);
        addEdge(&graph, from, to);
    }

    // Print the adjacency matrix with row and column names
    printMatrix(&graph);

    // Input the starting vertex for DFS
    int startVertex;
    printf("\nEnter the starting vertex for DFS: ");
    scanf("%d", &startVertex);

    DFSTraversal(&graph, startVertex);

    return 0;
}










33. Write a Program to accept a graph from user and represent it with Adjacency Lists and perform DFS traversals on it

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for representing a node in the adjacency list
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure for representing adjacency list
typedef struct {
    AdjListNode* head;
} AdjList;

// Structure for representing the graph
typedef struct {
    int numVertices;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given number of vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Create an array of adjacency lists. Size of the array will be numVertices.
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src.
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency lists
void printAdjLists(Graph* graph) {
    printf("Adjacency Lists:\n");
    for (int v = 0; v < graph->numVertices; ++v) {
        printf("Vertex %d: ", v);
        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            printf("%d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to perform Depth First Search (DFS) traversal
void DFSUtil(Graph* graph, int vertex, int visited[]) {
    // Mark the current node as visited and print it
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Recur for all the vertices adjacent to this vertex
    AdjListNode* adjNode = graph->array[vertex].head;
    while (adjNode) {
        int adjVertex = adjNode->dest;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        adjNode = adjNode->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    // Create an array to mark visited vertices
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    // Call the recursive helper function to perform DFS traversal
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    // Free dynamically allocated memory
    free(visited);
}

int main() {
    int numVertices, numEdges, from, to;

    // Input the number of vertices and edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    // Create a graph with the given number of vertices
    Graph* graph = createGraph(numVertices);

    // Input the edges
    printf("Enter the edges (from to): \n");
    for (int i = 0; i < numEdges; ++i) {
        scanf("%d %d", &from, &to);
        addEdge(graph, from, to);
    }

    // Print the adjacency lists
    printAdjLists(graph);

    // Input the starting vertex for DFS traversal
    int startVertex;
    printf("Enter the starting vertex for DFS traversal: ");
    scanf("%d", &startVertex);

    // Perform DFS traversal starting from the given vertex
    DFS(graph, startVertex);

    // Free dynamically allocated memory
    free(graph->array);
    free(graph);

    return 0;
}










34. Write a Program to implement Prim’s algorithm to find minimum spanning tree of a user defined graph. Use Adjacency List to represent a graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printAdjList(Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d: ", i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf("(%d, %d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printMST(int parent[], Graph* graph) {
    printf("Minimum Spanning Tree Edges:\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("Edge: %d - %d\n", parent[i], i);
    }
}

void primMST(Graph* graph) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minKey = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++) {
            if (mstSet[v] == false && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        mstSet[minIndex] = true;
        Node* temp = graph->adjLists[minIndex];

        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = minIndex;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }
    printMST(parent, graph);
}

int main() {
    int vertices, numEdges, src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Enter source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices)
            addEdge(graph, src, dest, weight);
        else {
            printf("Invalid vertices!\n");
            i--;
        }
    }

    printAdjList(graph);
    primMST(graph);
    return 0;
}










35. Write a Program to implement Kruskals’s algorithm to find minimum spanning tree of a user defined graph. Use Adjacency Matrix to represent a graph

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    parent[x] = y;
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
    
    int* parent = (int*)malloc(V * sizeof(int));
    memset(parent, -1, sizeof(int) * V);
    
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];
        
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }
    
    printf("\nMinimum Spanning Tree using Kruskal's algorithm:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", minimumCost);
    
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            int found = 0;
            for (int k = 0; k < e; ++k) {
                if ((result[k].src == i && result[k].dest == j) || (result[k].src == j && result[k].dest == i)) {
                    printf("%d\t", result[k].weight);
                    found = 1;
                    break;
                }
            }
            if (found == 0)
                printf("0\t");
        }
        printf("\n");
    }
    free(parent);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);
    
    struct Graph* graph = createGraph(V, E);
    
    printf("Enter edges and their weights (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
    }
    
    KruskalMST(graph);
    
    return 0;
}










36. Write a Program to implement Kruskal’s algorithm to find minimum spanning tree of a user defined graph. Use Adjacency List to represent a graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent;
    int rank;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // This will store the resultant MST
    int e = 0; // Index variable, used for result[]
    int i = 0; // Index variable, used for sorted edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printf("Minimum Spanning Tree using Kruskal's algorithm:\n");
    for (i = 0; i < e; ++i)
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight, int* edgeIndex) {
    graph->edge[*edgeIndex].src = src;
    graph->edge[*edgeIndex].dest = dest;
    graph->edge[*edgeIndex].weight = weight;
    (*edgeIndex)++;
}

// Function to print the adjacency list representation of graph
void printAdjList(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->V; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->E; j++) {
            if (graph->edge[j].src == i)
                printf("(%d, %d) ", graph->edge[j].dest, graph->edge[j].weight);
            else if (graph->edge[j].dest == i)
                printf("(%d, %d) ", graph->edge[j].src, graph->edge[j].weight);
        }
        printf("\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);
    printf("Enter edges and their weights (src dest weight):\n");
    int edgeIndex = 0;
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight, &edgeIndex);
    }

    printAdjList(graph);
    KruskalMST(graph);

    free(graph->edge);
    free(graph);
    return 0;
}









37. Write a Program to implement Dijkstra’s algorithm to find shortest distance between two nodes of a user defined graph. Use Adjacency List to represent a graph

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

struct node {
    int vertex;
    int weight;
    struct node* next;
};

struct node* A[MAX_VERTICES];
int n;

int vertex(int dist[], int visited[]) {
    int min = 999, a;
    for(int i = 0; i < n; i++) {
        if(dist[i] < min && visited[i] == 0) {
            min = dist[i];
            a = i;
        }
    }
    return a;
}

void display(int dist[]) {
    printf("\nVertex \t Distance from Source:\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

void dj1(struct node* A[]) {
    int s;
    printf("\nEnter starting vertex: ");
    scanf("%d", &s);
    getchar(); // Consume newline character
    int dist[MAX_VERTICES], visited[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = vertex(dist, visited);
        visited[u] = 1;
        struct node* current = A[u];
        while (current != NULL) {
            if (!visited[current->vertex] && dist[u] != 999 && dist[u] + current->weight < dist[current->vertex])
                dist[current->vertex] = dist[u] + current->weight;
            current = current->next;
        }
    }
    display(dist);
}

void list() {
    int u, v, w, num_edges;
    char ch;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    getchar(); // Consume newline character
    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);
    getchar(); // Consume newline character
    for (int i = 0; i < n; i++) {
        A[i] = NULL;
    }
    struct node* new;
    for (int i = 0; i < num_edges; i++) {
        printf("\nEnter edge %d/%d: ", i + 1, num_edges);
        scanf("%d %d", &u, &v);
        getchar(); // Consume newline character
        printf("\nEnter weight from edge %d to %d: ", u, v);
        scanf("%d", &w);
        getchar(); // Consume newline character
        new = (struct node*)malloc(sizeof(struct node));
        new->vertex = v;
        new->weight = w;
        new->next = A[u];
        A[u] = new;
        new = (struct node*)malloc(sizeof(struct node));
        new->vertex = u;
        new->weight = w;
        new->next = A[v];
        A[v] = new;
    }
}

int main() {
    int m;
    while (1) {
        printf("\n\n\t** MST Using Kruskal using Adjacency list and Matrix.");
        printf("\n1. Dijkstras Algorithm using matrix \n2. Dijkstras using Adjacency List \n3. Exit\n");
        printf("\nEnter which algorithm : ");
        scanf("%d", &m);
        getchar(); // Consume newline character
        switch (m) {
            case 1:
                list();
                dj1(A);
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter a valid option.");
        }
    }
    return 0;
}











38. Write a Program to implement Dijkstra’s algorithm to find shortest distance between two nodes of a user defined graph. Use Adjacency Matrix to represent a graph

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

int G[MAX_VERTICES][MAX_VERTICES];
int n;

int vertex(int dist[], int visited[]) {
    int min = 999, a;
    for(int i = 0; i < n; i++) {
        if(dist[i] < min && visited[i] == 0) {
            min = dist[i];
            a = i;
        }
    }
    return a;
}

void display(int dist[]) {
    printf("\nVertex \t Distance from Source:\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

void dj(int G[][MAX_VERTICES]) {
    int s;
    printf("\nEnter starting vertex : ");
    scanf("%d", &s);
    int dist[MAX_VERTICES], visited[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = vertex(dist, visited);
        visited[u] = 1;
        for (int j = 0; j < n; j++) {
            if (visited[j] != 1 && G[u][j] && dist[u] != 999 && dist[u] + G[u][j] < dist[j])
                dist[j] = dist[u] + G[u][j];
        }
    }
    display(dist);
}

void matrix() {
    int e, a, b, w;
    printf("\nEnter the no of vertex : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = 999;
        }
    }
    printf("\nEnter the no of edges : ");
    scanf("%d", &e);
    for (int i = 0; i < e; i++) {
        printf("\nEnter edge : ");
        scanf("%d %d", &a, &b);
        printf("\nEnter weight from edge %d to %d : ", a, b);
        scanf("%d", &w);
        G[a][b] = G[b][a] = w;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", G[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m;
    while (1) {
        printf("\n\n\t** MST Using Kruskal using Adjacency list and Matrix.");
        printf("\n1. Dijkstras Algorithm using matrix \n2. Dijkstras using Adjacency List \n3. Exit\n");
        printf("\nEnter which algorithm : ");
        scanf("%d", &m);
        switch (m) {
            case 1:
                matrix();
                dj(G);
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter a valid option.");
        }
    }
    return 0;
}










39. WAP to implement Heap sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed

#include <stdio.h>
#include <stdlib.h>

int size;
int swap_no = 0;

struct student {
    char n[50];
    int rn;
    int t;
} s[5];

struct student accept() {
    struct student temp;

    printf("\nEnter name: ");
    scanf("%s", temp.n);
    printf("Enter roll: ");
    scanf("%d", &temp.rn);
    printf("Enter total marks: ");
    scanf("%d", &temp.t);

    return temp;
}

void display() {
    for (int i = 0; i < size; i++) {
        printf("\nName: %s\n", s[i].n);
        printf("Roll: %d\n", s[i].rn);
        printf("Marks: %d\n", s[i].t);
    }
}

void swap(struct student *a, struct student *b) {
    swap_no++;
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct student st[], int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && st[left].rn > st[largest].rn)
        largest = left;

    if (right < N && st[right].rn > st[largest].rn)
        largest = right;

    if (largest != i) {
        swap(&st[i], &st[largest]);
        heapify(st, N, largest);
    }
}

void heapSort(struct student st[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(st, N, i);

    for (int i = N - 1; i >= 0; i--) {
        swap(&st[0], &st[i]);
        heapify(st, i, 0);
    }
}

int main() {
    printf("Enter number of students: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        s[i] = accept();
    }

    heapSort(s, size);

    printf("\nNumber of swaps performed: %d\n", swap_no);
    display();

    return 0;
}











40 . WAP to implement Quick sort on 1D array of Employee structure (contains employee_name, emp_no, emp_salary), with key as emp_no. And count the number of swap performed

#include<stdio.h>
#include<stdlib.h>

int size ;

struct emp {
    char na[50];
    int no;
    int sal;
} e[10];

void swap(struct emp *a, struct emp *b) {
    struct emp temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct emp emps[], int lower, int upper) {
    int pivot = upper;
    int i = lower - 1;

    for (int j = lower; j < upper; j++) {
        if (emps[j].no < emps[pivot].no) {
            i++;
            swap(&emps[i], &emps[j]);
        }
    }
    swap(&emps[i + 1], &emps[upper]);
    return (i + 1);
}

void quicksort(struct emp emps[], int lower, int upper) {
    if (lower < upper) {
        int partition_pos = partition(emps, lower, upper);
        quicksort(emps, lower, partition_pos - 1);
        quicksort(emps, partition_pos + 1, upper);
    }
}

void accept() {
    for (int i = 0; i < size; i++) {
        printf("\nEnter name: ");
        scanf("%s", e[i].na);
        printf("Enter emp no: ");
        scanf("%d", &e[i].no);
        printf("Enter salary: ");
        scanf("%d", &e[i].sal);
    }
}

void display() {
    for (int i = 0; i < size; i++) {
        printf("\nName: %s", e[i].na);
        printf("\nEmp no: %d", e[i].no);
        printf("\nSalary: %d", e[i].sal);
    }
}

int main() {
    printf("Enter the number of employees you want to add: ");
    scanf("%d", &size);
    accept();
    quicksort(e, 0, size - 1);
    display();
    return 0;
}












41. Assume that an array A with n elements was sorted in an ascending order, but two of its elements swapped their positions by a mistake while maintaining the array. Write a code

#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int first = -1, second = -1;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            first = i;
            break;
        }
    }
    for (int i = n - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            second = i;
            break;
        }
    }
    printf("Swapped elements: %d and %d\n", arr[first], arr[second]);
    printf("Positions: %d and %d\n", first + 1, second + 1);
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements of the array: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findSwappedElements(arr, n);

    return 0;
}










42.  Hashing Linear Probing with chaining without Replacement

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

struct Node {
    int key;
    struct Node* next;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(int hashTable[], int key, int* collisions) {
    int index = key % TABLE_SIZE;
    if (hashTable[index] == -1) {
        // If the slot is empty, insert the key
        struct Node* newNode = createNode(key);
        hashTable[index] = (int)newNode;
    } else {
        // If the slot is not empty, check if the key already exists
        struct Node* temp = (struct Node*)hashTable[index];
        struct Node* prev = NULL;
        while (temp != NULL && temp->key != key) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL) {
            // Key already exists, replace it
            temp->key = key;
        } else {
            // Key doesn't exist, add it to the end of the linked list
            struct Node* newNode = createNode(key);
            prev->next = newNode;
            (*collisions)++;
        }
    }
}

void display(int hashTable[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i] == -1) {
            printf("Empty\n");
        } else {
            struct Node* temp = (struct Node*)hashTable[i];
            while (temp != NULL) {
                printf("%d -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    int n, key, collisions = 0;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    printf("Enter %d elements to insert:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(hashTable, key, &collisions);
    }

    display(hashTable);
    printf("Number of collisions (chaining): %d\n", collisions);

    return 0;
}











43. Hashing Linear Probing with chaining with replacement

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

struct Node {
    int key;
    struct Node* next;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(int hashTable[], int key, int* collisions) {
    int index = key % TABLE_SIZE;
    if (hashTable[index] == -1) {
        // If the slot is empty, insert the key
        hashTable[index] = key;
    } else {
        // If the slot is not empty, find the next available slot
        int i = index + 1;
        while (i != index) {
            if (i >= TABLE_SIZE) {
                i = 0; // Wrap around
            }
            if (hashTable[i] == -1) {
                // Found an empty slot, insert the key
                hashTable[i] = key;
                break;
            } else {
                i++;
                (*collisions)++;
            }
        }
        if (i == index) {
            // Couldn't find an empty slot
            printf("Hash table is full, could not insert %d\n", key);
        }
    }
}

void display(int hashTable[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i] == -1) {
            printf("Empty\n");
        } else {
            printf("%d", hashTable[i]);
            int current = (i + 1) % TABLE_SIZE;
            while (current != i) {
                if (hashTable[current] != -1) {
                    printf(" -> %d", hashTable[current]);
                }
                current = (current + 1) % TABLE_SIZE;
            }
            printf("\n");
        }
    }
}

int main() {
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    int n, key, collisions = 0;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    printf("Enter %d elements to insert:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(hashTable, key, &collisions);
    }

    display(hashTable);
    printf("Number of collisions (linear probing with chaining and replacement): %d\n", collisions);

    return 0;
}







44. All Binary Tree (BT) operations non-recursive(Mirror Not Working)


#include <stdio.h>
#include <stdlib.h>

// Node structure for Binary Tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Queue structure for Level-wise traversal
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes
Node* createNode(int data);
void insertBinaryTree(Node** root, int data);
void inorderTraversal(Node* root);
void preorderTraversal(Node* root);
void postorderTraversal(Node* root);
void levelwiseTraversal(Node* root);
void displayLeafNodes(Node* root);
int countLeafNodes(Node* root);
int countTotalNodes(Node* root);
int treeHeight(Node* root);
void mirrorTree(Node* root);
void insertQueue(Queue* q, Node* treeNode);
Node* removeQueue(Queue* q);
int isQueueEmpty(Queue* q);

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
void insertBinaryTree(Node** root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }
    Queue q = {NULL, NULL};
    insertQueue(&q, *root);
    while (!isQueueEmpty(&q)) {
        Node* temp = removeQueue(&q);
        if (temp->left != NULL) {
            insertQueue(&q, temp->left);
        } else {
            temp->left = createNode(data);
            return;
        }
        if (temp->right != NULL) {
            insertQueue(&q, temp->right);
        } else {
            temp->right = createNode(data);
            return;
        }
    }
}

// Function to perform inorder traversal of the binary tree
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    Node* stack[100];
    int top = -1;
    Node* current = root;
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to perform preorder traversal of the binary tree
void preorderTraversal(Node* root) {
    if (root == NULL) return;
    Node* stack[100];
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        root = stack[top--];
        printf("%d ", root->data);
        if (root->right != NULL) {
            stack[++top] = root->right;
        }
        if (root->left != NULL) {
            stack[++top] = root->left;
        }
    }
    printf("\n");
}

// Function to perform postorder traversal of the binary tree
void postorderTraversal(Node* root) {
    if (root == NULL) return;
    Node* stack1[100];
    Node* stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1) {
        root = stack1[top1--];
        stack2[++top2] = root;
        if (root->left != NULL) {
            stack1[++top1] = root->left;
        }
        if (root->right != NULL) {
            stack1[++top1] = root->right;
        }
    }
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
    printf("\n");
}

// Function to perform level-wise traversal of the binary tree
void levelwiseTraversal(Node* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        Node* node = removeQueue(&q);
        printf("%d ", node->data);
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    printf("\n");
}

// Function to display leaf nodes of the binary tree
void displayLeafNodes(Node* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        Node* node = removeQueue(&q);
        if (node->left == NULL && node->right == NULL) {
            printf("%d ", node->data);
        }
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    printf("\n");
}

// Function to count the number of leaf nodes in the binary tree
int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int count = 0;
    while (!isQueueEmpty(&q)) {
        Node* node = removeQueue(&q);
        if (node->left == NULL && node->right == NULL) {
            count++;
        }
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    return count;
}

// Function to count the total number of nodes in the binary tree
int countTotalNodes(Node* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int count = 0;
    while (!isQueueEmpty(&q)) {
        Node* node = removeQueue(&q);
        count++;
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    return count;
}

// Function to calculate the height of the binary tree
int treeHeight(Node* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int height = 0;
    while (!isQueueEmpty(&q)) {
        int size = q.rear - q.front + 1;
        while (size--) {
            Node* node = removeQueue(&q);
            if (node->left != NULL) {
                insertQueue(&q, node->left);
            }
            if (node->right != NULL) {
                insertQueue(&q, node->right);
            }
        }
        height++;
    }
    return height;
}

// Function to mirror the binary tree
void mirrorTree(Node* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        Node* node = removeQueue(&q);
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
}



// Function to insert a node into the queue
void insertQueue(Queue* q, Node* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to remove a node from the queue
Node* removeQueue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    Node* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return treeNode;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert into Binary Tree");
        printf("\n2. Inorder Traversal");
        printf("\n3. Preorder Traversal");
        printf("\n4. Postorder Traversal");
        printf("\n5. Level-wise Traversal");
        printf("\n6. Display Leaf Nodes");
        printf("\n7. Count Leaf Nodes");
        printf("\n8. Count Total Nodes");
        printf("\n9. Display Height of Tree");
        printf("\n10. Mirror Image of Tree");
        printf("\n11. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert into Binary Tree: ");
                scanf("%d", &value);
                insertBinaryTree(&root, value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                break;
            case 5:
                printf("Level-wise Traversal: ");
                levelwiseTraversal(root);
                break;
            case 6:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;
            case 7:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 8:
                printf("Total Number of Nodes: %d\n", countTotalNodes(root));
                break;
            case 9:
                printf("Height of Tree: %d\n", treeHeight(root));
                break;
            case 10:
                printf("Mirror Image of Tree\n");
                mirrorTree(root);
                break;
            case 11:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}






45. All Binary Search Tree (BST) operations non-recursive(Mirror and Height of Tree not Working)

#include <stdio.h>
#include <stdlib.h>

// Node structure for Binary Search Tree
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Queue structure for Level-wise traversal
typedef struct QueueNode {
    BSTNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes
BSTNode* createBSTNode(int data);
void insertBST(BSTNode** root, int data);
void deleteBST(BSTNode** root, int data);
BSTNode* findMin(BSTNode* root);
void inorderTraversal(BSTNode* root);
void preorderTraversal(BSTNode* root);
void postorderTraversal(BSTNode* root);
void levelwiseTraversal(BSTNode* root);
void displayLeafNodes(BSTNode* root);
int countLeafNodes(BSTNode* root);
int countTotalNodes(BSTNode* root);
int treeHeight(BSTNode* root);
void mirrorTree(BSTNode* root);
void insertQueue(Queue* q, BSTNode* treeNode);
BSTNode* removeQueue(Queue* q);
int isQueueEmpty(Queue* q);

// Function to create a new node
BSTNode* createBSTNode(int data) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
void insertBST(BSTNode** root, int data) {
    BSTNode* newNode = createBSTNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    BSTNode* current = *root;
    while (1) {
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}


// Function to delete a node from the binary search tree
void deleteBST(BSTNode** root, int data) {
    if (*root == NULL) return;
    if (data < (*root)->data) {
        deleteBST(&((*root)->left), data);
    } else if (data > (*root)->data) {
        deleteBST(&((*root)->right), data);
    } else {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(*root);
            *root = NULL;
        } else if ((*root)->left == NULL) {
            BSTNode* temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            BSTNode* temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            BSTNode* temp = findMin((*root)->right);
            (*root)->data = temp->data;
            deleteBST(&((*root)->right), temp->data);
        }
    }
}

// Function to find the minimum value node in the binary search tree
BSTNode* findMin(BSTNode* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    BSTNode* stack[100];
    int top = -1;
    BSTNode* current = root;
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to perform preorder traversal of the binary search tree
void preorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    BSTNode* stack[100];
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        root = stack[top--];
        printf("%d ", root->data);
        if (root->right != NULL) {
            stack[++top] = root->right;
        }
        if (root->left != NULL) {
            stack[++top] = root->left;
        }
    }
    printf("\n");
}

// Function to perform postorder traversal of the binary search tree
void postorderTraversal(BSTNode* root) {
    if (root == NULL) return;
    BSTNode* stack1[100];
    BSTNode* stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1) {
        root = stack1[top1--];
        stack2[++top2] = root;
        if (root->left != NULL) {
            stack1[++top1] = root->left;
        }
        if (root->right != NULL) {
            stack1[++top1] = root->right;
        }
    }
    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
    printf("\n");
}

// Function to perform level-wise traversal of the binary search tree
void levelwiseTraversal(BSTNode* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        BSTNode* node = removeQueue(&q);
        printf("%d ", node->data);
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
}

// Function to display leaf nodes of the binary search tree
void displayLeafNodes(BSTNode* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        BSTNode* node = removeQueue(&q);
        if (node->left == NULL && node->right == NULL) {
            printf("%d ", node->data);
        }
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
}

// Function to count the number of leaf nodes in the binary search tree
int countLeafNodes(BSTNode* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int count = 0;
    while (!isQueueEmpty(&q)) {
        BSTNode* node = removeQueue(&q);
        if (node->left == NULL && node->right == NULL) {
            count++;
        }
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    return count;
}

// Function to count the total number of nodes in the binary search tree
int countTotalNodes(BSTNode* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int count = 0;
    while (!isQueueEmpty(&q)) {
        BSTNode* node = removeQueue(&q);
        count++;
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
    return count;
}

// Function to calculate the height of the binary search tree
int treeHeight(BSTNode* root) {
    if (root == NULL) return 0;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    int height = 0;
    while (!isQueueEmpty(&q)) {
        int size = q.rear - q.front + 1;
        while (size--) {
            BSTNode* node = removeQueue(&q);
            if (node->left != NULL) {
                insertQueue(&q, node->left);
            }
            if (node->right != NULL) {
                insertQueue(&q, node->right);
            }
        }
        height++;
    }
    return height;
}

// Function to mirror the binary search tree
void mirrorTree(BSTNode* root) {
    if (root == NULL) return;
    Queue q = {NULL, NULL};
    insertQueue(&q, root);
    while (!isQueueEmpty(&q)) {
        BSTNode* node = removeQueue(&q);
        BSTNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
        if (node->left != NULL) {
            insertQueue(&q, node->left);
        }
        if (node->right != NULL) {
            insertQueue(&q, node->right);
        }
    }
}

// Function to insert a node into the queue
void insertQueue(Queue* q, BSTNode* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to remove a node from the queue
BSTNode* removeQueue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    BSTNode* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return treeNode;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

int main() {
    BSTNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert into Binary Search Tree");
        printf("\n2. Delete from Binary Search Tree");
        printf("\n3. Inorder Traversal");
        printf("\n4. Preorder Traversal");
        printf("\n5. Postorder Traversal");
        printf("\n6. Level-wise Traversal");
        printf("\n7. Display Leaf Nodes");
        printf("\n8. Count Leaf Nodes");
        printf("\n9. Count Total Nodes");
        printf("\n10. Display Height of Tree");
        printf("\n11. Mirror Tree");
        printf("\n12. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert into Binary Search Tree: ");
                scanf("%d", &value);
                insertBST(&root, value);
                break;
            case 2:
                printf("Enter value to delete from Binary Search Tree: ");
                scanf("%d", &value);
                deleteBST(&root, value);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Level-wise Traversal: ");
                levelwiseTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 8:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 9:
                printf("Total Number of Nodes: %d\n", countTotalNodes(root));
                break;
            case 10:
                printf("Height of Tree: %d\n", treeHeight(root));
                break;
            case 11:
                printf("Mirror Tree\n");
                mirrorTree(root);
                break;
            case 12:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}




