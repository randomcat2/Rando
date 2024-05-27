#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Queue{
    struct Node *node;
    struct Queue *next;
}*front=NULL,*rear=NULL;

struct Stack{
    struct Node *node;
    struct Stack *next;
};

struct Queue *createQueue(struct Node *node)
{
    struct Queue *QueueNode=(struct Queue*)malloc(sizeof(struct Queue));
    QueueNode->node=node;
    QueueNode->next=NULL;
    return QueueNode;
}

struct Stack* createStack(struct Node* node)
{
    struct Stack* stackNode =(struct Stack*)malloc(sizeof(struct Stack));
    stackNode->node=node;
    stackNode->next=NULL;
    return stackNode;
}

void push(struct Stack **stack,struct Node *node)
{
    struct Stack *stackNode = createStack(node);
    stackNode->next=*stack;
    *stack=stackNode;
}

struct Node *pop(struct Stack **stack)
{
    if(*stack==NULL)
       return NULL;
    struct Node *poppedNode =(*stack)->node;
    struct Stack *temp = *stack;
    *stack=(*stack)->next;
    free(temp);
    return poppedNode;   
}

struct Node* insert(struct Node* root, int key) {
    struct Node* temp = newNode(key);
    if (root == NULL) return temp;

    struct Node* p = root;
    struct Node* parent = NULL;

    while (p != NULL) {
        parent = p;
        if (key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (key < parent->key) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }

    return root;
}


void enqueue(struct Node *node)
{
    struct Queue *queueNode = createQueue(node);
    if(rear==NULL)
    {
        front=rear=queueNode;
    }
    else
    {
        rear->next=queueNode;
        rear=queueNode;
    }
}

struct Node *dequeue()
{
    if(front==NULL)
    {
        return NULL;
    }
    struct Queue *temp=front;
    struct Node *node=temp->node;
    front =front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

bool find(struct Node* root, int key) {
    while (root != NULL) {
        if (root->key == key)
            return true;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}

void levelOrder(struct Node *root)
{
    if(root==NULL)
    return;

    enqueue(root);
    
    while(front!=NULL)
    {
        struct Node *current = dequeue();
        printf("%d ",current->key);

        if(current->left!=NULL)
        {
            enqueue(current->left);
        }
        if(current->right != NULL)
        {
            enqueue(current->right);
        }
    }
}

void Postorder(struct Node *root)
{
    struct Stack *top=NULL;
    struct Node *prev=NULL;
    do{
        while(root != NULL)
        {
            push(&top,root);
            root=root->left;
        }
        while(root==NULL && top != NULL)
        {
            root=pop(&top);
            if(root->right==NULL || root->right==prev)
            {
                printf("%d ",root->key);
                prev=root;
                root=NULL;
            }
            else
            {
                push(&top,root);
                root=root->right;
            }
        }
    }
    while(top != NULL);
    
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Level-wise Display\n");
        printf("5. Post Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key))
                    printf("Key found.\n");
                else
                    printf("Key not found.\n");
                break;
            case 4:
                printf("Level-wise display of BST:\n");
                levelOrder(root);
                break;
            case 5:
                printf("Postorder display of BST:\n");
                Postorder(root);
                break;    
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
