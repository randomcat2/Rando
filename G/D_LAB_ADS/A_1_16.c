#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int emp_id;
    char name[50];
    float salary;
    struct Employee *left, *right;
} Employee;

Employee* create_node(int emp_id, char name[50], float salary) {
    Employee *new_node = (Employee*) malloc(sizeof(Employee));
    new_node->emp_id = emp_id;
    strcpy(new_node->name, name);
    new_node->salary = salary;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Employee* insert_node(Employee *root, int emp_id, char name[50], float salary) {
    if (root == NULL) {
        return create_node(emp_id, name, salary);
    }

    if (emp_id < root->emp_id) {
        root->left = insert_node(root->left, emp_id, name, salary);
    } else if (emp_id > root->emp_id) {
        root->right = insert_node(root->right, emp_id, name, salary);
    }

    return root;
}

Employee* search_node(Employee *root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) {
        return root;
    }

    if (emp_id < root->emp_id) {
        return search_node(root->left, emp_id);
    } else {
        return search_node(root->right, emp_id);
    }
}

void inorder_traversal(Employee *root) {
    if (root == NULL) {
        return;
    }

    inorder_traversal(root->left);
    printf("Emp ID: %d, Name: %s, Salary: %.2f\n", root->emp_id, root->name, root->salary);
    inorder_traversal(root->right);
}

int main() {
    Employee *root = NULL;
    int emp_id, choice;
    char name[50];
    float salary;

    while (1) {
        printf("\n1. Insert Employee\n2. Search Employee\n3. Display Employees\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp_id);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                printf("Enter Employee Salary: ");
                scanf("%f", &salary);
                root = insert_node(root, emp_id, name, salary);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &emp_id);
                Employee *result = search_node(root, emp_id);
                if (result != NULL) {
                    printf("Emp ID: %d, Name: %s, Salary: %.2f\n", result->emp_id, result->name, result->salary);
                } else {
                    printf("Employee not found\n");
                }
                break;
            case 3:
                printf("Employees:\n");
                inorder_traversal(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}