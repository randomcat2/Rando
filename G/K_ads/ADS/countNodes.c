// Online C compiler to run C program online
#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode
{
    int data;
    struct TreeNode* right;
    struct TreeNode* left;
}TreeNode;
typedef struct StackNode
{
    struct StackNode* next;
    struct TreeNode* node;
}StackNode;
typedef struct Stack
{
    struct StackNode* top;
}Stack;
void push(Stack* stack,TreeNode* node)
{
    StackNode* newnode=(StackNode*)malloc(sizeof(StackNode));
    newnode->node=node;
    newnode->next=stack->top;
    stack->top=newnode;
}
int stackempty(Stack* stack)
{
    return stack->top==NULL;
}
TreeNode* pop(Stack* stack)
{
    if(stackempty(stack))
    {
        return 0;
    }
    StackNode* temp=stack->top;
    stack->top=stack->top->next;
    TreeNode* treenode=temp->node;
    free(temp);
    return treenode;
}
TreeNode* createTree(int data)
{
    TreeNode* newnode=(TreeNode*)malloc(sizeof(TreeNode));
    newnode->data=data;
    newnode->left=newnode->right=NULL;
    return newnode;
}
Stack* createStack()
{
    Stack* stack=(Stack*)malloc(sizeof(Stack));
    stack->top=NULL;
    return stack;
}
TreeNode* insert(TreeNode* root,int data)
{
    if(root==NULL)
       return createTree(data);
    if(root->data < data)
    {
        root->right=insert(root->right,data);
    }
    if(root->data > data)
    {
        root->left=insert(root->left,data);
    }
    return root;
}
int countnodes(TreeNode* root)
{
    if(root==NULL)
        return 0;
    Stack* s=createStack();
    TreeNode* current=root;
    int count=0;
    while(current!=NULL||!stackempty(s))
    {
        if(current!=NULL)
        {
            push(s,current);
            current=current->left;
        }
        else
        {
            current=pop(s);
            count++;
            current=current->right;
        }
    }
    free(s);
    return count;
}
int countleafnodes(TreeNode* root)
{
    if(root==NULL)
        return 0;
    Stack* s=createStack();
   
    int count=0;
    push(s,root);
   while(!stackempty(s))
   {
      
        TreeNode* t=pop(s);
        if(t->left==NULL&&t->right==NULL)
       {
           count++;
       }
       if(t->left)
       {
           push(s,t->left);
          
       }
        if(t->right)
       {
           push(s,t->right);
           
       }
   }
    free(s);
    return count;
}
   int main(){
    TreeNode *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 60);

 

    printf("Number of nodes :%d\n",  countnodes(root));
    printf("Number of nodes :%d\n",  countleafnodes(root));
   
    return 0;
}
