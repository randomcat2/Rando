#include <stdlib.h>
#include <stdio.h>
typedef struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
}BSTNode;

typedef struct StackNode
{
    struct StackNode* next;
    struct BSTNode* bstnode;
}StackNode;
typedef struct Stack
{
   StackNode* top;
}Stack;
BSTNode* createnewnode(int data)
{
    BSTNode* newnode =( BSTNode*)malloc(sizeof(BSTNode));
    newnode->data=data;
    newnode->right=newnode->left=NULL;
    return newnode;
}

void push(Stack* stack, BSTNode* node) {
    StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));
    newnode->bstnode = node;
    newnode->next = stack->top;
    stack->top = newnode;
}

int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}
BSTNode* pop(Stack* stack)
{
    if (isStackEmpty(stack)) {
        return NULL;
    } 
    else
    {
        StackNode* temp=stack->top;
        stack->top=stack->top->next;
        BSTNode* node=temp->bstnode;
        free(temp);
        return node;
    }
}
BSTNode* insertBST(int data,BSTNode* root)
{
    if(root==NULL){
        return createnewnode(data);
    }
    if(data<root->data)
    {
        root->left=insertBST(data,root->left);
    }
    else if(data>root->data)
    {
        root->right=insertBST(data,root->right);
    }
    return root;
}

Stack* createstack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void preorder(BSTNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    Stack *stack=createstack();
    push(stack,root);
    while (!isStackEmpty(stack))
    {
        BSTNode* node=pop(stack);
        printf("%d ",node->data);
        if(node->right)
        {
            push(stack,node->right);
        }
        if(node->left)
        {
            push(stack,node->left);
        }
    }
    printf("\n");
}
void inorder(BSTNode* root)
{
   
    Stack* stack=createstack();
    BSTNode* current=root;
  
    while(!isStackEmpty(stack)||current!=NULL)
    {

       if(current!=NULL)
       {
            push(stack,current);
            current=current->left;
        
       }
       else
       {
           current=pop(stack);
           printf("%d ",current->data);
           current=current->right;
       }
    }
    

       printf("\n");
       free(stack);
  }  
  void mirrorTree(struct TreeNode *root) {
    if (root == NULL) {
        return;
    }

    struct StackNode *stack = NULL;
    struct TreeNode *current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        
        // Swap the left and right children
        struct TreeNode *temp = current->left;
        current->left = current->right;
        current->right = temp;

        current = current->left;  // Continue mirroring the left subtree
    }
}
   

int main()
{
    BSTNode *root=NULL;
    root=insertBST(50,root);
    root=insertBST(30,root);
    root=insertBST(20,root);
    root=insertBST(40,root);
    root=insertBST(70,root);
    root=insertBST(80,root);
    root=insertBST(60,root);
    // preorder(root);
    inorder(root);
    return 0;
}
