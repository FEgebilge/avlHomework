/*Array AVL tree (Recursive):
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

int NodeHightNULLCheker(AVL_NODE *tree, int index)
{
    if (tree[index] == NULL)
        return 0;
    else
        return tree[index]->height;
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

void insertRecBST(AVL_NODE *tree, int index, int key, void *data)
{

    if (tree[index] == NULL)
    {
        tree[index] = initNode(key, data);
    }
    else
    {
        if (key < tree[index]->key)
        {
            insertRecBST(tree, index * 2 + 1, key, data);
        }
        else if (key > tree[index]->key)
        {
            insertRecBST(tree, index * 2 + 2, key, data);
        }
        else
        {
            printf("ERROR:Dublicate key: %d \n", key);
        }
    }
}
void BST_Insert(AVL_NODE *tree, int key, void *data)
{
    if (tree != NULL)
    {
        if (tree[0] != NULL)
        {
            insertRecBST(tree, 0, key, data);
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
        if (tree[i] != NULL)
            printf("%d ,", ((AVL_NODE)tree[i])->key);
    }
    printf("\n\n");
}

void CompleteTreeFromArray(AVL_NODE *tree, AVL_NODE *tempArray, int index, int tempsize)
{

    for (int i = 0; i < tempsize; i++)
    {
        if (tempArray[i] != NULL)
        {
            insertRecBST(tree, index, tempArray[i]->key, NULL);
            tempArray[i] = NULL;
        }
    }
}

int preorder(AVL_NODE *tree, AVL_NODE *array, int index, int fillIndex)
{
    if (tree[index] != NULL)
    {
        array[fillIndex] = tree[index];
        tree[index] = NULL;
        fillIndex++;
        index = preorder(tree, array, index * 2 + 1, index);
        preorder(tree, array, index * 2 + 2, index);
    }

    return index;
}

void rightRotation(AVL_NODE *tree, int index)
{
    int tempsize = 300;
    AVL_NODE *t3 = initAVLTree(tempsize);
    AVL_NODE *t2 = initAVLTree(tempsize);
    AVL_NODE *t1 = initAVLTree(tempsize);

    preorder(tree, t3, index * 2 + 2, 0);
    CompleteTreeFromArray(tree, t3, (index * 2 + 2) * 2 + 2, tempsize);

    tree[index * 2 + 2] = tree[index];
    tree[index] = tree[index * 2 + 1];
    tree[index * 2 + 1] = NULL;
    preorder(tree, t2, (index * 2 + 1) * 2 + 2, 0);
    CompleteTreeFromArray(tree, t2, (index * 2 + 2) * 2 + 1, tempsize);
    preorder(tree, t1, (index * 2 + 1) * 2 + 1, 0);
    CompleteTreeFromArray(tree, t1, index * 2 + 1, tempsize);

    tree[index * 2 + 2]->height = chooseMax(NodeHightNULLCheker(tree, (index * 2 + 2) * 2 + 1), NodeHightNULLCheker(tree, (index * 2 + 2) * 2 + 2)) + 1;
    tree[index]->height = chooseMax(NodeHightNULLCheker(tree, index * 2 + 1), NodeHightNULLCheker(tree, index * 2 + 2)) + 1;
    free(t1);
    free(t2);
    free(t3);
}
void leftRotation(AVL_NODE *tree, int index)
{
    int tempsize = 300;
    AVL_NODE *t3 = initAVLTree(tempsize);
    AVL_NODE *t2 = initAVLTree(tempsize);
    AVL_NODE *t1 = initAVLTree(tempsize);

    preorder(tree, t3, index * 2 + 1, 0);
    CompleteTreeFromArray(tree, t3, (index * 2 + 1) * 2 + 1, tempsize);

    tree[index * 2 + 1] = tree[index];
    tree[index] = tree[index * 2 + 2];
    tree[index * 2 + 2] = NULL;
    preorder(tree, t2, (index * 2 + 2) * 2 + 1, 0);
    CompleteTreeFromArray(tree, t2, (index * 2 + 1) * 2 + 2, tempsize);
    preorder(tree, t1, (index * 2 + 2) * 2 + 2, 0);
    CompleteTreeFromArray(tree, t1, index * 2 + 2, tempsize);

    tree[index * 2 + 1]->height = chooseMax(NodeHightNULLCheker(tree, (index * 2 + 1) * 2 + 1), NodeHightNULLCheker(tree, (index * 2 + 1) * 2 + 2)) + 1;
    tree[index]->height = chooseMax(NodeHightNULLCheker(tree, index * 2 + 1), NodeHightNULLCheker(tree, index * 2 + 2)) + 1;
    free(t1);
    free(t2);
    free(t3);
}

void balanceFactor(AVL_NODE* tree,int index){
     // Update node->height
    tree[index]->height = chooseMax(NodeHightNULLCheker(tree, index * 2 + 1), NodeHightNULLCheker(tree, index * 2 + 2)) + 1;

    // Compute balance factor
    int balanceFactor = NodeHightNULLCheker(tree, index * 2 + 1) - NodeHightNULLCheker(tree, index * 2 + 2);

    if (balanceFactor == -2)
    {
        // Choose RR or RL
        if ((NodeHightNULLCheker(tree, ((index * 2 + 2) * 2) + 1) > NodeHightNULLCheker(tree, ((index * 2 + 2) * 2) + 2)))
        { // RL
            rightRotation(tree, index * 2 + 2);
            leftRotation(tree, index);
        }
        else
        { // RR
            leftRotation(tree, index);
        }
    }
    else if (balanceFactor == 2)
    {
        // Choose LL or LR
        if ((NodeHightNULLCheker(tree, ((index * 2 + 1) * 2) + 1) > NodeHightNULLCheker(tree, ((index * 2 + 1) * 2) + 2)))
        { // LL
            rightRotation(tree, index);
        }
        else
        { // LR
            leftRotation(tree, index * 2 + 1);
            rightRotation(tree, index);
        }
    }
}

void insertRecAVL(AVL_NODE *tree, int index, int key, void *data)
{

    if (tree[index] == NULL)
    {
        tree[index] = initNode(key, data);
    }
    else
    {
        if (key < tree[index]->key)
        {
            insertRecAVL(tree, index * 2 + 1, key, data);
        }
        else if (key > tree[index]->key)
        {
            insertRecAVL(tree, index * 2 + 2, key, data);
        }
        else
        {
            printf("ERROR:Dublicate key: %d \n", key);
        }
    }

    balanceFactor(tree,index);
}



void AVL_Search(AVL_NODE *tree, int key,int i)
{
    if(tree[i]!=NULL){
        if(tree[i]->key < key){
            AVL_Search(tree,key,i*2+2);
        }else if(tree[i]->key > key){
            AVL_Search(tree,key,i*2+1);
        }else{
            printf("Key found! Information of searched node: \n");
            printf("Key :%d , Height: %d, Data: %d", tree[i]->key, tree[i]->height,tree[i]->data);
        }
    }
}

void AVL_Delete(AVL_NODE *tree, int key, int i)
{
    if (tree[i] == NULL)
    {
        printf("ERROR: Empty tree..");
    }
    else
    {
        if (key < tree[i]->key)
        {
            AVL_Delete(tree, key, i * 2 + 1);
        }
        else if (key > tree[i]->key)
        {
            AVL_Delete(tree, key, i * 2 + 2);
        }
        else
        {
            if ((tree[i * 2 + 1] == NULL) && (tree[i * 2 + 2] == NULL))
            {
                // No child
                tree[i] = NULL;
            }
            else if ((tree[i * 2 + 1] == NULL) && (tree[i * 2 + 2] != NULL))
            {
                // Single right
                tree[i] = tree[i * 2 + 2];
                tree[i * 2 + 2] = NULL;
            }
            else if ((tree[i * 2 + 2] == NULL) && (tree[i * 2 + 1] != NULL))
            {
                // Single left
                tree[i] = tree[i * 2 + 1];
                tree[i * 2 + 1] = NULL;
            }
            else
            {
                int max = 2 * i + 1;
                int parentMax = max;
                while (tree[2 * max + 2] != NULL)
                {
                    parentMax = max;
                    max = 2 * max + 2;
                }
                tree[i] = tree[max];
                if (max == parentMax)
                {
                    tree[parentMax] = tree[2 * parentMax + 1];
                    tree[2 * parentMax + 1] = NULL;
                }
                else
                {
                    tree[2 * parentMax + 2] = tree[2 * max + 1];
                }
                balanceFactor(tree, parentMax);
                balanceFactor(tree, i);
            }
        }

    }
    if(tree[i]!=NULL)
    balanceFactor(tree,i);
}

void AVL_Insert(AVL_NODE *tree, int key, void *data)
{
    if (tree != NULL)
    {
        if (tree[0] != NULL)
        {
            insertRecAVL(tree, 0, key, data);
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

void testFunction()
{
    AVL_NODE *tree = initAVLTree(100000);

    printf("INSERT FUNCTION TESTING.........\n\n");
    AVL_Insert(tree, 51, NULL);
    AVL_Insert(tree, 42, NULL);
    AVL_Insert(tree, 33, NULL); 
    AVL_Insert(tree, 17, NULL);
    AVL_Insert(tree, 10, NULL);
    AVL_Insert(tree, 6, NULL);
    AVL_Insert(tree, 4, NULL);
    AVL_Insert(tree, 2, NULL);
    printBST(tree, 0, 0);
    printf("\n -------------------------- \n");
    printf("SEARCH FUNCTION TESTING.........\n\n");
    AVL_Search(tree,33,0);
    printf("\n -------------------------- \n");
    printf("DELETE FUNCTION TESTING.........\n\n");
    printf("Deleting 51.. \n\n");
    AVL_Delete(tree,51,0);
    printBST(tree,0,0);
    printf("\n -------------------------- \n");
    printf("Deleting 17.. \n\n");
    AVL_Delete(tree,17,0);
    printBST(tree,0,0);
    printf("\n -------------------------- \n");
    printf("Deleting 33.. \n\n");
    AVL_Delete(tree,33,0);
    printBST(tree,0,0);
    printf("\n -------------------------- \n");
    printf("Deleting 6.. \n\n");
    AVL_Delete(tree,6,0);
    printBST(tree,0,0);
    printf("\n -------------------------- \n");


    free(tree);
}

int main()
{
    testFunction();
    return 0;
}