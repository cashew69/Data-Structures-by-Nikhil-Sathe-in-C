#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// Helpers
Node* insertNode(Node* currentNode, int value) {
    if (currentNode == NULL)
    {
        Node * newNode = malloc(sizeof(Node));
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (value < currentNode->value)
    {
        currentNode->left = insertNode(currentNode->left, value);
    }
    else if (value > currentNode -> value)
    {
        currentNode->right = insertNode(currentNode->right, value);
    }

    return currentNode;
}

/*Node *getFarLeft(Node * currentNode)
{
    if (currentNode != NULL)
    {   
        if(currentNode->left != NULL)
        {
            return getFarLeft(currentNode->left);
        }
        return currentNode;
    }

    return NULL;
}*/


// Operations
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

    // TODO: Visit left subtree first
    inOrderTraversal(node->left);
    // TODO: Print current node
    printf("%d ", node->value);
    // TODO: Visit right subtree
    inOrderTraversal(node->right);
}

int main(int argc, char *argv[]) {


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
    Node* root = createBST(inputArrayLength, inputArray);
    printf("BST created successfully!\n");
    printf("In-order traversal (sorted): ");
    inOrderTraversal(root);
    printf("\n");
    }    else 
    {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}
