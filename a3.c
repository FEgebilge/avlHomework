/*A3 (100 pts). Array AVL tree (Iterative):
 Search, Insert, Delete, together with a proper test.
*/

#include <stdio.h>
#include <stdlib.h>




void printAVL(int* tree, int size){
    for(int i=0;i<size;i++){
        printf("| %d ", tree[i]);
    }
}

int* initAVL(int size){
    int* AVL_tree = malloc(sizeof(int)*size);
    return AVL_tree;
}

void insertNode(int* tree, int key){

    int i=0;
    if(tree[i]==0){
     tree[i]=key;   
    }
    while(tree[i]==0){
        if(key<tree[i]){
            i=(2*i)+1;
        }
        else if(key>tree[i]){
            i=(2*i)+2;
        }else{
            printf("Error: Dublicate key : %d", key);
        }
    }

    tree[i]=key;

}


int main(){

    int* tree=initAVL(30);

    printAVL(tree,30);
    printf("\n");

    insertNode(tree,12);
    insertNode(tree,2);

    printAVL(tree,30);
    free(tree);
    return 0;
}