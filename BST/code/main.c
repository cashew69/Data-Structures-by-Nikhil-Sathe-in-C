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

Node * successor(Node * node, int searchvalue) 
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


    if (argc < 2) 
    {
        printf("Usage: %s <command> [numbers...]\n", argv[0]);
        printf("Commands: -create\n");
        printf("          -search\n");
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
    Node* root = NULL;
    if (strcmp(argv[1], "-create") == 0) 
    {
    root = createBST(inputArrayLength, inputArray);
    printf("BST created successfully!\n");
    printf("In-order traversal (sorted): ");
    inOrderTraversal(root);
    printf("\n");
    }    
    else if (root && strcmp(argv[1], "-search") == 0)
    {
        Node *searchNode = search(root, inputArray[2]);
        if (searchNode)
        {
            printf("Found Search Value %d\n", searchNode->value);
        }
        else
        {
            printf("Search Value Not Found\n");
        }

    }
    else if (root && strcmp(argv[1], "-minimums") == 0)
    {
        Node * minimumNode = minimum(root);
        printf("Minium Value: %d \n", minimumNode->value);
    }
    else 
    {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}
