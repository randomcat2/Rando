void preorderTraversal(TreeNode* current) {
    Stack* stack = createStack();
    while (current != NULL || !isEmpty(stack)) {
        if (current != NULL) {
            printf("%d ", current->data);
            push(stack, current);
            current = current->left;
        } else {
            current = pop(stack);
            current = current->right;
        }
    }
    destroyStack(stack);
}