#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Function to create and insert a new node into the BST
struct node* create(struct node* root, int key) {
    if (root == NULL) {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = key;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }

    if (key < root->data) {
        root->left = create(root->left, key);
    } else if (key > root->data) {
        root->right = create(root->right, key);
    }

    return root;
}

// Function to print the tree in-order (for testing purposes)
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        preorder(root->left);
        preorder(root->right);
        printf("%d ",root->data);
    }
}

int leaf_nodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return leaf_nodes(root->left) + leaf_nodes(root->right);
}

int number_of_node(struct node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        return 1+ number_of_node(root->left) + number_of_node(root->right);

    }
}

int height(struct node* root)
{
    if(root==NULL)
    {
        return 0;
    }

    int x,y;
    x = height(root->left);
    y = height(root->right);
    if(x>y)
    {
        return x+1;
    }
    else
    {
        return y+1;
    }
}

void print_current_level(struct node*root, int level)
{
    if (root==NULL)
    {
        return;
    }

    if(level==1)
    {
        printf("%d", root->data);
    }
    else
    {
        print_current_level(root->left,level-1);
        print_current_level(root->right,level-1);
    }
}

void level_display(struct node*root)
{
    int h = height(root);
    int i;
    for( i =1;i<=h;i++)
    {
        print_current_level(root,i);
    }
}

int mirror(struct node*root)
{
    if(root==NULL){
        return 1;
    }
    else{
    struct node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
    }

}



int main() {
    struct node* root = NULL;
    int key;

    printf("Enter the data for the nodes (enter -1 to stop):\n");

    while (1) {
        printf("Enter data: ");
        scanf("%d", &key);

        if (key == -1) {
            break;
        }

        root = create(root, key);
    }

    printf("In-order traversal of the tree: ");
    inorder(root);
    printf("\n");

    printf("Pre-order traversal of the tree: ");
    preorder(root);
    printf("\n");

    printf("Post-order traversal of the tree: ");
    postorder(root);
    printf("\n");

    printf("Number of leaf nodes are: ");
    printf("%d\n",leaf_nodes(root));

    printf("Number of main nodes are: ");
    printf("%d\n",number_of_node(root));

    printf("Height is: ");
    printf("%d\n",height(root));

    printf("Level wise dislay is: ");
    level_display(root);

    printf("Mirroring the tree...\n");
    mirror(root);

    printf("In-order traversal of the mirrored tree: ");
    inorder(root);
    printf("\n");


    return 0;
}
