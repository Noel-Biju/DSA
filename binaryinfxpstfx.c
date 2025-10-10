#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    char opStack[100];
    int top = -1, k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            opStack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && opStack[top] != '(')
                postfix[k++] = opStack[top--];
            if (top != -1) top--;  // pop '('
        } else {
            while (top != -1 && getPrecedence(infix[i]) <= getPrecedence(opStack[top]))
                postfix[k++] = opStack[top--];
            opStack[++top] = infix[i];
        }
    }
    while (top != -1)
        postfix[k++] = opStack[top--];
    postfix[k] = '\0';
}

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* buildExpressionTree(char* postfix) {
    TreeNode* nodeStack[100];
    int top = -1;
    TreeNode *node, *rightChild, *leftChild;
    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            node = createNode(postfix[i]);
            nodeStack[++top] = node;
        } else {
            node = createNode(postfix[i]);
            rightChild = nodeStack[top--];
            leftChild = nodeStack[top--];
            node->left = leftChild;
            node->right = rightChild;
            nodeStack[++top] = node;
        }
    }
    return nodeStack[top];
}

// Print prefix (preorder) traversal
void printPrefix(TreeNode* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}

// Print postfix (postorder) traversal
void printPostfix(TreeNode* root) {
    if (root == NULL) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c ", root->data);
}

// Print expression tree with branches
void printTree(TreeNode* root, char* prefix, int isLeft) {
    if (root == NULL) return;
    printf("%s", prefix);
    printf("%s", isLeft ? "├──" : "└──");
    printf("%c\n", root->data);
    char newPrefix[100];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLeft ? "│ " : " ");
    if (root->left || root->right) {
        printTree(root->left, newPrefix, 1);
        printTree(root->right, newPrefix, 0);
    }
}

int main() {
    char infix[100], postfix[100];
    printf("Enter Infix Expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);
    TreeNode* root = buildExpressionTree(postfix);

    printf("\nPrefix Expression: ");
    printPrefix(root);
    printf("\n");

    printf("Postfix Expression: ");
    printPostfix(root);
    printf("\n");

    printf("\nExpression Tree:\n");
    printTree(root, "", 0);

    return 0;
}
