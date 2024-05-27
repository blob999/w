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

