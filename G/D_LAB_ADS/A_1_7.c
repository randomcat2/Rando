#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum length for strings
#define MAX_NAME_LENGTH 100
#define DATE_LENGTH 11

// Define the structure for a product
typedef struct Product {
    int code;
    char name[MAX_NAME_LENGTH];
    float price;
    int amount_in_stock;
    char date_received[DATE_LENGTH];
    char expiration_date[DATE_LENGTH];
    struct Product* left;
    struct Product* right;
} Product;

// Define the structure for a stack node
typedef struct StackNode {
    Product* product;
    struct StackNode* next;
} StackNode;

// Function to create a new product
Product* createProduct(int code, char* name, float price, int amount_in_stock, char* date_received, char* expiration_date) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (!newProduct) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newProduct->code = code;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->amount_in_stock = amount_in_stock;
    strcpy(newProduct->date_received, date_received);
    strcpy(newProduct->expiration_date, expiration_date);
    newProduct->left = NULL;
    newProduct->right = NULL;
    return newProduct;
}

// Function to insert a product into the BST
Product* insertProduct(Product* root, Product* newProduct) {
    if (root == NULL)
        return newProduct;

    if (strcmp(newProduct->name, root->name) < 0)
        root->left = insertProduct(root->left, newProduct);
    else if (strcmp(newProduct->name, root->name) > 0)
        root->right = insertProduct(root->right, newProduct);
    return root;
}

// Function to find a product by its code
Product* findProductByCode(Product* root, int code) {
    if (root == NULL)
        return NULL;

    if (root->code == code)
        return root;

    Product* leftResult = findProductByCode(root->left, code);
    if (leftResult != NULL)
        return leftResult;

    return findProductByCode(root->right, code);
}

// Function to update a product's information
void updateProduct(Product* product, float price, int amount_in_stock, char* date_received, char* expiration_date) {
    product->price = price;
    product->amount_in_stock = amount_in_stock;
    strcpy(product->date_received, date_received);
    strcpy(product->expiration_date, expiration_date);
}

// Function to create a new stack node
StackNode* createStackNode(Product* product) {
    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newStackNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newStackNode->product = product;
    newStackNode->next = NULL;
    return newStackNode;
}

// Function to push a product onto the stack
void push(StackNode** top, Product* product) {
    StackNode* newStackNode = createStackNode(product);
    newStackNode->next = *top;
    *top = newStackNode;
}

// Function to pop a product from the stack
Product* pop(StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }
    StackNode* temp = *top;
    *top = (*top)->next;
    Product* poppedProduct = temp->product;
    free(temp);
    return poppedProduct;
}

// Function to check if the stack is empty
int isStackEmpty(StackNode* top) {
    return top == NULL;
}

// Function to perform in-order traversal of the BST using a stack
void inOrderTraversal(Product* root) {
    StackNode* stack = NULL;
    Product* current = root;

    while (!isStackEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(&stack, current);
            current = current->left;
        } else {
            current = pop(&stack);
            if (current != NULL) {
                printf("Code: %d, Name: %s, Price: %.2f, Amount in Stock: %d, Date Received: %s, Expiration Date: %s\n",
                       current->code, current->name, current->price, current->amount_in_stock, current->date_received, current->expiration_date);
                current = current->right;
            }
        }
    }
}

int main() {
    Product* root = NULL;

    // Insert some products
    root = insertProduct(root, createProduct(101, "Milk", 1.5, 50, "2024-01-01", "2024-01-10"));
    root = insertProduct(root, createProduct(102, "Bread", 2.0, 30, "2024-01-05", "2024-01-15"));
    root = insertProduct(root, createProduct(103, "Butter", 3.0, 20, "2024-01-02", "2024-01-12"));

    // Find and update a product
    Product* product = findProductByCode(root, 104);
    if (product) {
        printf("The Product with code %d is %s\n", product->code, product->name);
        updateProduct(product, 2.5, 25, "2024-01-06", "2024-01-16");
    } else {
        printf("Product not found\n");
    }

    // List all products in lexicographic order of their names
    printf("Products in lexicographic order:\n");
    inOrderTraversal(root);

    return 0;
}