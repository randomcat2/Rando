#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack{
    struct TreeNode *node;
    struct Stack *next;
};

struct Queue{
    struct TreeNode *node;
    struct Queue *next;
}*front=NULL,*rear=NULL;

struct Queue *createQueue(struct TreeNode *node)
{
    struct Queue *QueueNode=(struct Queue*)malloc(sizeof(struct Queue));
    QueueNode->node=node;
    QueueNode->next=NULL;
    return QueueNode;
}

struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode =(struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    return newNode;
}

struct Stack* createStack(struct TreeNode* node)
{
    struct Stack* stackNode =(struct Stack*)malloc(sizeof(struct Stack));
    stackNode->node=node;
    stackNode->next=NULL;
    return stackNode;
}

void push(struct Stack **stack,struct TreeNode *node)
{
    struct Stack *stackNode = createStack(node);
    stackNode->next=*stack;
    *stack=stackNode;
}

struct TreeNode *pop(struct Stack **stack)
{
    if(*stack==NULL)
       return NULL;
    struct TreeNode *poppedNode =(*stack)->node;
    struct Stack *temp = *stack;
    *stack=(*stack)->next;
    free(temp);
    return poppedNode;   
}

void enqueue(struct TreeNode *node)
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

struct TreeNode *dequeue()
{
    if(front==NULL)
    {
        return NULL;
    }
    struct Queue *temp=front;
    struct TreeNode *node=temp->node;
    front =front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return node;
}


struct TreeNode* insert(struct TreeNode* root, int key) {
    struct TreeNode* temp = createNode(key);
    if (root == NULL) return temp;

    struct TreeNode* p = root;
    struct TreeNode* parent = NULL;

    while (p != NULL) {
        parent = p;
        if (key < p->data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (key < parent->data) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }

    return root;
}

// struct Node* insert(struct Node* node, int key) {
//     if (node == NULL) return newNode(key);

//     if (key < node->key)
//         node->left = insert(node->left, key);
//     else if (key > node->key)
//         node->right = insert(node->right, key);

//     return node;
// }



bool Find(struct TreeNode* root, int num) {
    while(root != NULL)
    {
        if(num > root->data)
        {
            root=root->right;
        }
        else if(num < root->data)
        {
            root=root->left;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void Preorder(struct TreeNode *root)
{
    struct Stack *top=NULL;
    while(root!=NULL)
    {
        printf("%d ",root->data);
        push(&top,root);
        root=root->left;
    }
    while(top!=NULL)
    {
        root=pop(&top);
        root=root->right;
        while(root!=NULL)
       {
        printf("%d ",root->data);
        push(&top,root);
        root=root->left;
       }
    }
}

void Inorder(struct TreeNode *root)
{
    struct Stack *top=NULL;
    struct TreeNode *temp=root;
    while(temp !=NULL || top != NULL)
    {
        while(temp != NULL)
       {
        push(&top,temp);
        temp=temp->left;
       }
    temp=pop(&top);
    printf("%d ",temp->data);
    temp=temp->right;
    }

}

void Postorder(struct TreeNode *root)
{
    struct Stack *top=NULL;
    struct TreeNode *prev=NULL;
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
                printf("%d ",root->data);
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

void levelOrder(struct TreeNode *root)
{
    if(root==NULL)
    return;

    enqueue(root);
    
    while(front!=NULL)
    {
        struct TreeNode *current = dequeue();
        printf("%d ",current->data);

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

int count(struct TreeNode *root)
{
    if(root==NULL)
      return 0;

    int count=0;
    struct Stack *top=NULL;
    push(&top,root);

    while(top != NULL)
    {
        struct TreeNode *temp=pop(&top);
        count++;

        if(temp->right) push(&top,temp->right);
        if(temp->left)  push(&top,temp->left);
    } 
    return count; 
}

int calculateHeight(struct TreeNode* root) {
    if (root == NULL) return 0;
    enqueue(root);
    int height = 0;

    while (front != NULL) {
        int nodeCount = 0;
        struct Queue* temp = front;
        while (temp) {
            nodeCount++;
            temp = temp->next;
        }

        height++;
        while (nodeCount > 0) {
            struct TreeNode* current = dequeue();
            if (current->left) enqueue(current->left);
            if (current->right) enqueue(current->right);
            nodeCount--;
        }
    }
    return height;
}

int leafcount(struct TreeNode *root)
{
    if(root==NULL)
      return 0;

    int count=0;
    struct Stack *top=NULL;
    push(&top,root);

    while(top != NULL)
    {
        struct TreeNode *temp=pop(&top);
    
        if(temp->left==NULL && temp->right==NULL)
        {
            count++;
        }

        if(temp->right) push(&top,temp->right);
        if(temp->left)  push(&top,temp->left);
    } 
    return count; 
}

void mirror(struct TreeNode *root)
{
    if(root==NULL) return;

    enqueue(root);

    while(front != NULL)
    {
        struct TreeNode *current = dequeue();

        struct TreeNode *temp=current->left;
        current->left=current->right;
        current->right=temp;

        if(current->left) enqueue(current->left);
        if(current->right)  enqueue(current->right);
    }
}

int main()
{
    struct TreeNode* root = NULL;

    root = insert(root, 50);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 30);
    root = insert(root, 45);
    root = insert(root, 55);
    root = insert(root, 70);
    root = insert(root, 10);
    root = insert(root, 35);
    root = insert(root, 65);
    root = insert(root, 90);
    printf("\nPreorder Traversal: ");
    Preorder(root);
    printf("\nInorder Traversal: ");
    Inorder(root);
    printf("\nPostorder Traversal: ");
    Postorder(root);
    printf("\nLevelorder Traversal: ");
    levelOrder(root);
    printf("\nHeight is:%d",calculateHeight(root));
    printf("\nCount of nodes is:%d",count(root));
    printf("\nleaf Count of nodes is:%d",leafcount(root));
    mirror(root);
    printf("\nInorder Traversal: ");
    Inorder(root);
    printf("\n");
    int numToFind = 10;
    if (Find(root, numToFind)) {
        printf("Number %d found in the tree.\n", numToFind);
    } else {
        printf("Number %d not found in the tree.\n", numToFind);
    }
    printf("\nInorder Traversal: ");
    Inorder(root);

}