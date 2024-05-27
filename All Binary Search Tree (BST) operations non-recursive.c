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

