#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

// Function declarations
Node* insertNode(Node* currentNode, int value);
Node* createBST(int arrSize, int *inputArray);
void inOrderTraversal(Node* node);
Node* search(Node* node, int searchvalue);
Node* getMinimum(Node* currentNode);
Node* getMaximum(Node* currentNode);
Node* successor(Node* node);
Node* predecessor(Node* node);


// Operations
Node* insertNode(Node* currentNode, int value) {
    if (currentNode == NULL)
    {
        Node * newNode = malloc(sizeof(Node));
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        return newNode;
    }
    if (value < currentNode->value)
    {
        currentNode->left = insertNode(currentNode->left, value);
        currentNode->left->parent = currentNode;
    }
    else if (value > currentNode -> value)
    {
        currentNode->right = insertNode(currentNode->right, value);
        currentNode->right->parent = currentNode;
    }

    return currentNode;
}

Node * createBST(int arrSize, int *inputArray)
{
    if (arrSize > 0)
        {
            Node* root = NULL;
            root = insertNode(root, inputArray[0]);

            for (int i = 1; i < arrSize; i++)
            {
                root = insertNode(root, inputArray[i]);
            }
            return root;
        }

    return NULL;
}

void inOrderTraversal(Node* node) {
    if (node == NULL)
        return;  // Base case

    inOrderTraversal(node->left);
    printf("%d ", node->value);
    inOrderTraversal(node->right);
}

Node * search(Node * node, int searchvalue) 
{
    if (node == NULL || searchvalue == node->value)
    {
        return node;
    }
    if (searchvalue < node->value)
    {
        return search(node->left, searchvalue);
    }
    else
    {
        return search(node->right, searchvalue);
    }
}

Node * successor(Node * node) 
{
    if (node->right !=NULL)
    {
        return getMinimum(node->right);
    }
    else 
    {
        Node * parent = node->parent;
        while (parent != NULL && node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;

    }
}

Node * predecessor(Node * node) 
{
    if (node->left !=NULL)
    {
        return getMaximum(node->left);
    }
    else 
    {
        Node * parent = node->parent;
        while (parent != NULL && node == parent->left)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;

    }
}

Node *getMinimum(Node * currentNode)
{
   if (currentNode == NULL || currentNode->left == NULL) 
   {
    return currentNode;
   }
    return getMinimum(currentNode->left);
}

Node *getMaximum(Node * currentNode)
{
   if (currentNode == NULL || currentNode->right == NULL) 
   {
    return currentNode;
   }
    return getMaximum(currentNode->right);
}

int main(int argc, char *argv[]) {
    Node* root = NULL;
    char input[256];
    char command[50];
    int value;
    
    if (argc < 2) 
    {
        printf("Usage: %s <command> [numbers...]\n", argv[0]);
        printf("Commands: -create\n");
        return 1;
    }

     int inputArrayLength = argc - 2;
    if (inputArrayLength <= 0)
    {
        printf("No numbers provided.\n");
        return 1;
    }
    int inputArray[inputArrayLength];

    for (int i = 2; i < argc; i++) 
    {
        inputArray[i - 2] = atoi(argv[i]);  // Note: i - 2
        printf("Added %d to inputArray[%d]\n", inputArray[i - 2], i - 2);
    }
    if (strcmp(argv[1], "-create") == 0) 
    {
    root = createBST(inputArrayLength, inputArray);
    printf("BST created successfully!\n");
    }

    printf("╔════════════════════════════════╗\n");
    printf("║   BST Interactive Shell        ║\n");
    printf("╚════════════════════════════════╝\n");
    printf("Type 'help' for available commands\n\n");
    
    while (1) {
        printf("BST> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        if (strlen(input) == 0) {
            continue;
        }
        
        int args = sscanf(input, "%s %d", command, &value);
        
        if (strcmp(command, "insert") == 0 && args == 2) {
            root = insertNode(root, value);
            printf("✓ Inserted %d\n", value);
        }
        else if (strcmp(command, "search") == 0 && args == 2) {
            Node* result = search(root, value);
            if (result != NULL) {
                printf("✓ Found %d\n", value);
            } else {
                printf("✗ %d not found\n", value);
            }
        }
        else if (strcmp(command, "print") == 0) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                printf("Tree (in-order): ");
                inOrderTraversal(root);
                printf("\n");
            }
        }
        else if (strcmp(command, "min") == 0) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                Node* minNode = getMinimum(root);
                printf("Minimum: %d\n", minNode->value);
            }
        }
        else if (strcmp(command, "max") == 0) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                Node* maxNode = getMaximum(root);
                printf("Maximum: %d\n", maxNode->value);
            }
        }
        else if (strcmp(command, "successor") == 0 && args == 2) {
            Node* node = search(root, value);
            if (node == NULL) {
                printf("✗ %d not in tree\n", value);
            } else {
                Node* succ = successor(node);
                if (succ != NULL) {
                    printf("Successor of %d: %d\n", value, succ->value);
                } else {
                    printf("%d has no successor (largest value)\n", value);
                }
            }
        }
        else if (strcmp(command, "predecessor") == 0 && args == 2) {
            Node* node = search(root, value);
            if (node == NULL) {
                printf("✗ %d not in tree\n", value);
            } else {
                Node* pred = predecessor(node);
                if (pred != NULL) {
                    printf("Predecessor of %d: %d\n", value, pred->value);
                } else {
                    printf("%d has no predecessor (smallest value)\n", value);
                }
            }
        }
        else if (strcmp(command, "clear") == 0) {
            // TODO: Properly free memory
            root = NULL;
            printf("✓ Tree cleared\n");
        }
        else if (strcmp(command, "help") == 0) {
            printf("\nAvailable commands:\n");
            printf("  insert <n>       - Insert number into BST\n");
            printf("  search <n>       - Search for number\n");
            printf("  print            - Display tree (in-order)\n");
            printf("  min              - Find minimum value\n");
            printf("  max              - Find maximum value\n");
            printf("  successor <n>    - Find successor of n\n");
            printf("  predecessor <n>  - Find predecessor of n\n");
            printf("  clear            - Clear the tree\n");
            printf("  help             - Show this help\n");
            printf("  quit             - Exit program\n\n");
        }
        else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
            printf("Goodbye! 👋\n");
            break;
        }
        else {
            printf("Unknown command or missing arguments. Type 'help' for usage.\n");
        }
    }
    
    // TODO: Free all nodes before exiting
    return 0;
}
