/*A2 (50 pts). Array AVL tree (Recursive):
 Search, Insert, Delete, together with a proper test.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct AVL_NODE_s *AVL_NODE;
typedef struct AVL_NODE_s
{
    int key;
    int height;
    void *data;
} AVL_NODE_t[1];

void printBST(AVL_NODE *tree, int index, int h)
{

    if (tree[index] != NULL)
    {
        printBST(tree, (index * 2) + 2, h + 1);
        for (int i = 0; i < h; i++)
        {
            printf("   ");
        }
        printf("%d\n", tree[index]->key);
        printBST(tree, (index * 2) + 1, h + 1);
    }
}

int NodeHightNULLCheker(AVL_NODE node)
{
    if (node == NULL)
        return 0;
    else
        return node->height;
}

int chooseMax(int num1, int num2)
{
    if (num1 >= num2)
        return num1;
    else
        return num2;
}

AVL_NODE *initAVLTree(int size)
{
    AVL_NODE *tree = malloc(sizeof(AVL_NODE) * size);
    for (int i = 0; i < size; i++)
    {
        tree[i] = NULL;
    }
    return tree;
}

AVL_NODE initNode(int key, void *data)
{
    AVL_NODE node = (AVL_NODE)malloc(sizeof(AVL_NODE_t));
    node->data = data;
    node->key = key;
    node->height = 1;

    return node;
}

AVL_NODE leftRotation(int index,AVL_NODE* tree)
{
    AVL_NODE child = parent->right;
    AVL_NODE subTree = child->left;

    parent->right = subTree;
    child->left = parent;

    parent->height = chooseMax(NodeHightNULLCheker(parent->left), NodeHightNULLCheker(parent->right)) + 1;
    child->height = chooseMax(NodeHightNULLCheker(child->left), NodeHightNULLCheker(child->right)) + 1;

    return child;
}

AVL_NODE insertRecAVL(AVL_NODE *tree, int index, int key, void *data)
{

    if (tree[index] == NULL)
    {
        tree[index] = initNode(key, data);
    }
    else
    {
        if (key < tree[index]->key)
        {
            tree[index * 2 + 1] = insertRecAVL(tree, index * 2 + 1, key, data);
        }
        else if (key > tree[index]->key)
        {
            tree[index * 2 + 2] = insertRecAVL(tree, index * 2 + 2, key, data);
        }
        else
        {
            printf("ERROR:Dublicate key: %d \n", key);
        }
    }
    return tree[index];
    
    // Update node->height
    tree[index]->height = chooseMax(NodeHightNULLCheker(tree[index*2+1]), NodeHightNULLCheker(tree[index*2+2])) + 1;

    // Compute balance factor
    int balanceFactor = NodeHightNULLCheker(tree[index*2+1]) - NodeHightNULLCheker(tree[index*2+2]);

    if (balanceFactor == -2)
    {
        // Choose RR or RL
        if ((NodeHightNULLCheker(tree[((index*2+2)*2)+1]) > NodeHightNULLCheker(tree[((index*2+2)*2)+2])) && key > tree[index*2+2]->key)
        { // RL
            tree[index*2+2] = rightRotation(tree[index*2+2]);
            return leftRotation(index,tree);
        }
        else
        { // RR
            return leftRotation(index,tree);
        }
    }
    else if (balanceFactor == 2)
    {
        // Choose LL or LR
        if ((NodeHightNULLCheker(tree[((index*2+1)*2)+1]) > NodeHightNULLCheker(tree[((index*2+1)*2)+2]) && key < tree[index*2+1]->key))
        { // LL
            return rightRotation(tree[index]);
        }
        else
        { // LR
            tree[index*2+1] = leftRotation(tree[index*2+1]);
            return rightRotation(tree[index]);
        }
    }
    
}

void AVL_Insert(AVL_NODE *tree, int key, void *data)
{
    if (tree != NULL)
    {
        if (tree[0] != NULL)
        {
            tree[0] = insertRecAVL(tree, 0, key, data);
        }
        else
        {
            tree[0] = initNode(key, data);
        }
    }
    else
    {
        printf("ERROR: invalid tree! \n");
    }
}

void printAsArray(AVL_NODE *tree, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ,", ((AVL_NODE)tree[i])->key);
    }
    printf("\n\n");
}

void testFunction()
{
    AVL_NODE *tree = initAVLTree(100);
    AVL_Insert(tree, 12, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 15, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 6, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 20, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 100, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 8, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 10, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 5, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 4, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 1, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    AVL_Insert(tree, 13, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");

    free(tree);
}

int main()
{
    testFunction();
    return 0;
}