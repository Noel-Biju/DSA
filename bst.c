#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int val;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode* new_node(int v) {
    BSTNode *n = malloc(sizeof(BSTNode));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->val = v;
    n->left = n->right = NULL;
    return n;
}

BSTNode* insert(BSTNode *root, int v) {
    if (!root) return new_node(v);
    if (v < root->val)
        root->left = insert(root->left, v);
    else if (v > root->val)
        root->right = insert(root->right, v);
    return root;
}

BSTNode* search(BSTNode *root, int v) {
    if (!root) return NULL;
    if (v == root->val) return root;
    if (v < root->val) return search(root->left, v);
    return search(root->right, v);
}

BSTNode* find_min(BSTNode *root) {
    while (root && root->left)
        root = root->left;
    return root;
}

BSTNode* delete_node(BSTNode *root, int v) {
    if (!root) return NULL;

    if (v < root->val)
        root->left = delete_node(root->left, v);
    else if (v > root->val)
        root->right = delete_node(root->right, v);
    else {
        // Case 1: No children
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        // Case 2: One child
        else if (!root->left) {
            BSTNode *r = root->right;
            free(root);
            return r;
        } else if (!root->right) {
            BSTNode *l = root->left;
            free(root);
            return l;
        }
        // Case 3: Two children
        else {
            BSTNode *succ = find_min(root->right);
            root->val = succ->val;
            root->right = delete_node(root->right, succ->val);
        }
    }
    return root;
}

void inorder(BSTNode *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void free_tree(BSTNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    BSTNode *root = NULL;
    int choice, val;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Insert\n2. Search\n3. Delete\n5. Exit\n"); // Removed option 4
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printf("Enter integer to insert: ");
            if (scanf("%d", &val) != 1) break;
            root = insert(root, val);
            printf("%d inserted.\n", val);

            // Display tree after insertion
            printf("Inorder Traverse: ");
            inorder(root);
            printf("\n");
        }

        else if (choice == 2) {
            printf("Enter integer to search: ");
            if (scanf("%d", &val) != 1) break;
            BSTNode *res = search(root, val);
            if (res)
                printf("%d found in BST.\n", val);
            else
                printf("%d not found.\n", val);

            // Display tree after search
            printf("Inorder Traverse: ");
            inorder(root);
            printf("\n");
        }

        else if (choice == 3) {
            printf("Enter integer to delete: ");
            if (scanf("%d", &val) != 1) break;
            root = delete_node(root, val);
            printf("If present, %d deleted.\n", val);

            // Display tree after deletion
            printf("Inorder Traverse: ");
            inorder(root);
            printf("\n");
        }

        else if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    free_tree(root);
    return 0;
}
