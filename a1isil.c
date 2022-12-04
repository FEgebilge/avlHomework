/*
A1 (50 pts). Linked AVL tree (Recursive): Search, Insert, Delete, together with a proper test.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s
{
    NODE left;
    NODE right;
    int key;
    void *data;
    int height;
} NODE_t[1], *NODE;

typedef struct
{
    NODE root;
} AVL_t[1], *AVL;

void preorder(NODE node)
{
    if (node != NULL)
    {
        printf("%d ", node->key);
        preorder(node->left);
        preorder(node->right);
    }
}

void avl_print(NODE node, int l)
{
    int i;
    if (node != NULL)
    {
        avl_print(node->right, l + 1);
        for (i = 0; i < l; ++i)
        {
            printf("     ");
        }
        printf("%d\n", node->key);
        avl_print(node->left, l + 1);
    }
}

AVL avl_init()
{
    AVL t = (AVL)malloc(sizeof(AVL_t));
    t->root = NULL;
    return t;
}

void avl_free(AVL t)
{
    free(t);
}

NODE avl_init_node(int key, void *data)
{
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    return node;
}

void avl_free_node(NODE n)
{
    free(n);
}

int height(NODE n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int balance_factor(NODE n)
{
    if (n == NULL)
    {
        return 0;
    }
    return (height(n->left) - height(n->right));
}

int find_max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

NODE find_min(NODE node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

NODE rightrotation(NODE parent)
{
    NODE ch = parent->left;
    NODE subtree = ch->right;
    ch->right = parent;
    parent->left = subtree;
    parent->height = find_max(height(parent->left), height(parent->right)) + 1;
    ch->height = find_max(height(ch->left), height(ch->right)) + 1;
    return ch;
}

NODE leftrotation(NODE parent)
{
    NODE ch = parent->right;
    NODE subtree = ch->left;
    ch->left = parent;
    parent->right = subtree;
    parent->height = find_max(height(parent->left), height(parent->right)) + 1;
    ch->height = find_max(height(ch->left), height(ch->right)) + 1;
    return ch;
}

// SEARCH +
int search(NODE node, int key)
{

    if (node == NULL)
        return 0;

    else if (node->key == key)
        return 1;

    else if (node->key > key)
    {
        int result = search(node->left, key);
        return result;
    }

    else
    {
        int result = search(node->right, key);
        return result;
    }
}
// INSERT +
/*
NODE insert_avl_iterative(AVL tree, NODE node, int key, void *data)
{
    if (node == NULL)
    {
        node->data = data;
        node->key = key;
    }
    else
    {
        if (node->key < key)
        {
            node->right = insert_avl_iterative(tree, node->right, key, data);
        }
        if (node->key > key)
        {
            node->left = insert_avl_iterative(tree, node->left, key, data);
        }
        else
            printf("dublicate key\n");
    }

    node->height = find_max(node->left->height, node->right->height);
    int balance_f = balance_factor(node);

    if (balance_factor(node) <= -2)
    { // rr or rl
        if (balance_factor(node->right) <= 0)
            return leftrotation(node); // RR
        else
            node->right = rightrotation(node->right); // RL
        return leftrotation(node);
    }

    if (balance_factor(node) >= 2) // ll or lr
    {
        if (balance_factor(node->left) >= 0)
            return rightrotation(node); // LL
        else
            node->left = leftrotation(node->left);
        return rightrotation(node); // LR
    }
    // update height!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return node;
}*/

NODE balanced_tree(NODE node, int key)
{
    
    int bfactor = balance_factor(node);
    if (bfactor > 1)
    {
        if (key < node->left->key)
        {
            return rightrotation(node); // LL
        }
        else
        {
            node->left = leftrotation(node->left); // LR
            return rightrotation(node);
        }
    }
    else if (bfactor < -1)
    {
        if (key < node->right->key)
        {
            node->right = rightrotation(node->right); // RL
            return leftrotation(node);
        }
        else
        {
            return leftrotation(node); // RR
        }
    }
    return node;
    
}

NODE avl_insert_rec(NODE node, int key, void *data)
{
    if (node == NULL)
    {
        node = avl_init_node(key, data);
    }
    else
    {
        if (key < node->key)
        {
            node->left = avl_insert_rec(node->left, key, data);
        }
        else if (key > node->key)
        {
            node->right = avl_insert_rec(node->right, key, data);
        }
        else
        {
            printf("dublicate key : %d \n", key);
        }
        node->height = find_max(height(node->left), height(node->right)) + 1;
        node = balanced_tree(node,key);
    }
    return node;
}

void avl_insert(AVL tree, int key, void *data)
{
    if (tree == NULL)
    {
        printf("ERROR. Uninitialized tree\n");
    }
    else
    {
        if (tree->root == NULL)
        {
            tree->root = avl_init_node(key, data);
        }
        else
        {
            tree->root = avl_insert_rec(tree->root, key, data);
        }
    }
}
// DELETE +
NODE delete_avl_iterative(NODE parent, NODE node, int key)
{
    if (node == NULL)
    {
        printf("node is NULL\n");
    }
    else
    {
        // divide problems to cases
        // no child
        if (node->right == NULL && node->left == NULL)
        {
            if (node == parent->left)
            {
                parent->left == NULL;
            }
            if (node == parent->right)
            {
                parent->right == NULL;
            }
        }

        // SINGLE CHILD
        // ON LEFT
        if (node->left != NULL && node->right == NULL)
        {
            if (node == parent->left)
            {
                parent->left = node->right;
            }
            else
            {
                parent->right = node->right;
            }
        }
        // ON RIGHT
        if (node->right != NULL && node->left == NULL)
        {
            if (node == parent->left)
            {
                parent->left = node->left;
            }
            else
            {
                parent->right = node->left;
            }
        }

        // TWO CHILD
        else
        {
        }
    }
}

NODE avl_delete_rec(NODE node, int key)
{
    if (node == NULL)
        return node;

    if (key < node->key)
        node->left = avl_delete_rec(node->left, key);

    else if (key > node->key)
        node->right = avl_delete_rec(node->right, key);

    else
    {
        if ((node->left == NULL) && (node->right == NULL))
        {
            avl_free_node(node);
        }
        if ((node->left == NULL) && (node->right != NULL))
        {
            NODE temp = node->right;
            node = temp;
            avl_free_node(temp);
        }
        if ((node->left != NULL) && (node->right == NULL))
        {
            NODE temp = node->left;
            node = temp;
            avl_free_node(temp);
        }
        else
        {
            // two child
            NODE temp = find_min(node->right);
            node->key = temp->key;
            node->right = avl_delete_rec(node->right, temp->key);
        }
    }
    node->height = find_max(height(node->left), height(node->right)) + 1;
    node = balanced_tree(node,key);
    return node;
}

void avl_delete(AVL tree, int key)
{
    if (tree == NULL)
    {
        printf("ERROR. Uninitialized tree\n");
    }
    else
    {
        if (tree->root == NULL)
        {
            tree->root = avl_delete_rec(tree->root,key);
        }
        else
        {
            tree->root = avl_delete_rec(tree->root, key);
        }
    }
}

int main()
{
    AVL tree = avl_init();
    avl_insert(tree, 44, NULL);
    avl_insert(tree, 11, NULL);
    avl_insert(tree, 34, NULL);
    avl_insert(tree, 52, NULL);
    avl_insert(tree, 89, NULL);
    avl_insert(tree, 62, NULL);
    avl_insert(tree, 23, NULL);
    avl_insert(tree, 72, NULL);
    avl_insert(tree, 93, NULL);
    printf("x");
    preorder(tree->root);
    avl_print(tree->root, 0);
    printf("\n");
    //printf("%d", search(tree->root, 62));
    printf("\n");
    //printf("%d", search(tree->root, 60));
    printf("\n");
    //avl_delete(tree, 44);
    //avl_print(tree->root, 0);
    avl_free(tree);
    return 0;
}
