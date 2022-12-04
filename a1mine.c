/*A1 (50 pts). Linked AVL tree (Recursive):
 Search, Insert, Delete, together with a proper test.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct AVL_NODE_s *AVL_NODE;
typedef struct AVL_NODE_s
{
    AVL_NODE left;
    AVL_NODE right;
    int key;
    int height;
    void *data;
} AVL_NODE_t[1];

typedef struct AVL_s
{
    AVL_NODE root;
} AVL_t[1], *AVL;

AVL_NODE leftRotation(AVL_NODE parent);
AVL_NODE rightRotation(AVL_NODE parent);

void printBST(AVL_NODE root, int h)
{

    if (root != NULL)
    {
        printBST(root->right, h + 1);
        for (int i = 0; i < h; i++)
        {
            printf("   ");
        }
        printf("%d\n", root->key);
        printBST(root->left, h + 1);
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

AVL initBST()
{
    AVL bst = (AVL)malloc(sizeof(AVL_t));
    bst->root = NULL;
    return bst;
}

AVL_NODE initNode(int key, void *data)
{
    AVL_NODE node = (AVL_NODE)malloc(sizeof(AVL_NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->height = 1;
    node->key = key;

    return node;
}

AVL_NODE insertRecAVL(AVL_NODE node, int key, void *data)
{

    if (node == NULL)
    {
        node = initNode(key, data);
    }
    else
    {
        if (key < node->key)
        {
            node->left = insertRecAVL(node->left, key, data);
        }
        else if (key > node->key)
        {
            node->right = insertRecAVL(node->right, key, data);
        }
        else
        {
            printf("ERROR:Dublicate key: %d \n", key);
        }
    }
    // Update node->height
    node->height = chooseMax(NodeHightNULLCheker(node->left), NodeHightNULLCheker(node->right)) + 1;

    // Compute balance factor
    int balanceFactor = NodeHightNULLCheker(node->left) - NodeHightNULLCheker(node->right);

    if (balanceFactor == -2)
    {
        // Choose RR or RL
        if ((NodeHightNULLCheker(node->right->left) > NodeHightNULLCheker(node->right->right)) && key > node->right->key)
        { // RL
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        else
        { // RR
            return leftRotation(node);
        }
    }
    else if (balanceFactor == 2)
    {
        // Choose LL or LR
        if ((NodeHightNULLCheker(node->left->left) > NodeHightNULLCheker(node->left->right) && key < node->left->key))
        { // LL
            return rightRotation(node);
        }
        else
        { // LR
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
    }

    return node;
}

void AVL_Insert(AVL tree, int key, void *data)
{
    if (tree != NULL)
    {
        if (tree->root != NULL)
        {
            tree->root = insertRecAVL(tree->root, key, data);
        }
        else
        {
            tree->root = initNode(key, data);
        }
    }
    else
    {
        printf("ERROR: invalid tree! \n");
    }
}

AVL_NODE findMax(AVL_NODE node)
{
    AVL_NODE tempNode;
    if (node->right != NULL)
    {
        
        tempNode = findMax(node->right);

        if (tempNode == NULL)
        {
            tempNode = node->right;
            node->right = node->right->left;
            node->height = chooseMax(NodeHightNULLCheker(node->left), NodeHightNULLCheker(node->right)) + 1;
        }

        node = tempNode;
    }
    else
    {
        node = NULL;
    }

    return node;
}

AVL_NODE searchNode(AVL tree, int key)
{

    AVL_NODE currentNode = tree->root;
    while (currentNode->key != key)
    {
        if (key < currentNode->key && currentNode->left != NULL)
        {
            currentNode = currentNode->left;
        }
        else if (key > currentNode->key && currentNode->right != NULL)
        {
            currentNode = currentNode->right;
        }
        else
        {
            printf("Key is not an element of tree");
            break;
        }
    }
    return currentNode;
}

AVL_NODE leftRotation(AVL_NODE parent)
{
    AVL_NODE child = parent->right;
    AVL_NODE subTree = child->left;

    parent->right = subTree;
    child->left = parent;

    parent->height = chooseMax(NodeHightNULLCheker(parent->left), NodeHightNULLCheker(parent->right)) + 1;
    child->height = chooseMax(NodeHightNULLCheker(child->left), NodeHightNULLCheker(child->right)) + 1;

    return child;
}

AVL_NODE rightRotation(AVL_NODE parent)
{
    AVL_NODE child = parent->left;

    AVL_NODE subTree = child->right;

    child->right = parent;
    parent->left = subTree;

    parent->height = chooseMax(NodeHightNULLCheker(parent->left), NodeHightNULLCheker(parent->right)) + 1;
    child->height = chooseMax(NodeHightNULLCheker(child->left), NodeHightNULLCheker(child->right)) + 1;

    return child;
}

AVL_NODE RecursiveDelete(AVL_NODE node, int key)
{

    if (node == NULL)
    {
        return node;
    }
    else
    { //////////////////
        if (key < node->key)
        {
            node->left = RecursiveDelete(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = RecursiveDelete(node->right, key);
        }
        else
        {

            AVL_NODE tempNode;

            if ((node->left == NULL) && (node->right == NULL))
            { /* No child */

                tempNode = node;
                node = NULL;
            }
            else if ((node->left == NULL) && (node->right != NULL))
            { /* A single right child. */
                tempNode = node->right;
                free(node);
                node = tempNode;
            }
            else if ((node->left != NULL) && (node->right == NULL))
            { /* A single left child. */

                tempNode = node->left;
                free(node);
                node = tempNode;
            }
            else
            { /* Two children. */

                tempNode = node;
                node = findMax(node->left);
                if (node == NULL)
                {
                    node = tempNode->left;
                }
                else
                {
                    node->left = tempNode->left;
                }
                node->right = tempNode->right;

            }

            // return node;
        }
    }

    if (node != NULL)
    {
        // Update node->height
        node->height = chooseMax(NodeHightNULLCheker(node->left), NodeHightNULLCheker(node->right)) + 1;

        // Compute balance factor
        int balanceFactor = NodeHightNULLCheker(node->left) - NodeHightNULLCheker(node->right);

        if (balanceFactor == -2)
        {
            // Choose RR or RL
            if ((NodeHightNULLCheker(node->right->left) > NodeHightNULLCheker(node->right->right)) && key > node->right->key)
            { // RL
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
            else
            { // RR
                return leftRotation(node);
            }
        }
        else if (balanceFactor == 2)
        {
            // Choose LL or LR
            if ((NodeHightNULLCheker(node->left->left) > NodeHightNULLCheker(node->left->right) && key < node->left->key))
            { // LL
                return rightRotation(node);
            }
            else
            { // LR
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
    }

    return node;
}

void AVL_Delete(AVL tree, int key)
{
    if (tree != NULL)
    {
        if (tree->root != NULL)
        {
            tree->root = RecursiveDelete(tree->root, key);
        }
        else
        {
            printf("ERROR");
        }
    }
    else
    {
        printf("ERROR: invalid tree! \n");
    }
}

void testFunction()
{

    AVL tree1 = initBST();
    printf("Inserting nodes to AVL tree:\n----------------------------------");
    AVL_Insert(tree1, 11, NULL);
    AVL_Insert(tree1, 20, NULL);
    AVL_Insert(tree1, 23, NULL);
    AVL_Insert(tree1, 59, NULL);
    AVL_Insert(tree1, 30, NULL);
    AVL_Insert(tree1, 15, NULL);
    AVL_Insert(tree1, 70, NULL);
    AVL_Insert(tree1, 6, NULL);
    AVL_Insert(tree1, 5, NULL);
    AVL_Insert(tree1, 4, NULL);
    AVL_Insert(tree1, 3, NULL);
    AVL_Insert(tree1, 2, NULL);
    AVL_Insert(tree1, 1, NULL);

    printBST(tree1->root, 0);

    printf("--------------------------------\n");
    printf("Searching node with key 15 :\n----------------------------------\n");
    AVL_NODE node = searchNode(tree1, 15);
    printf("Information of searched node:\n");
    printf("Key: %d , Height: %d Left: %p , Right: %p \n\n\n", node->key, node->height, node->left, node->right);

    printf("Deleting nodes from AVL tree:\n----------------------------------\n");
    printf("Deleting 15.... \n");
    AVL_Delete(tree1, 15);
    printBST(tree1->root, 0);

    printf("Deleting 23.... \n");
    AVL_Delete(tree1, 23);
    printBST(tree1->root, 0);

    printf("Deleting 4.... \n");
    AVL_Delete(tree1, 4);
    printBST(tree1->root, 0);    
   
    printf("Deleting 20.... \n");
    AVL_Delete(tree1, 20);
    printBST(tree1->root, 0);

    printf("Deleting 59.... \n");
    AVL_Delete(tree1, 59);
    printBST(tree1->root, 0);

     printf("Deleting 1.... \n");
    AVL_Delete(tree1, 1);
    printBST(tree1->root, 0);

     printf("Deleting 5.... \n");
    AVL_Delete(tree1, 5);
    printBST(tree1->root, 0);

     printf("Deleting 11.... \n");
    AVL_Delete(tree1, 11);
    printBST(tree1->root, 0);

     printf("Deleting 30.... \n");
    AVL_Delete(tree1, 30);
    printBST(tree1->root, 0);
    free(tree1);
}

int main()
{
    testFunction();

    return 0;
}