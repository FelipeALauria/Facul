#include <stdbool.h>

typedef struct {
    int num;
} data;

typedef struct no {
    data info;
    struct no *right;
    struct no *left;
} no;

typedef struct no *tree;

void define(tree t) {
    t = NULL;
}

tree createRoot (tree t, data elem) {
    t = malloc(sizeof(no));
    t->info = elem;
    t->right = NULL;
    t->left = NULL;
    return t;
}

bool empty(tree t) {
    if(t == NULL)
        return(false);
    return(true);    
}

void insertright(tree dad, data elem) {
    if(dad == NULL)
        return;

    if(dad->right != NULL)
        return;

    dad->right = malloc(sizeof(no));
    dad->right->info = elem;
    dad->right->right = NULL;
    dad->right->left = NULL;
}

void insertleft(tree dad, data elem) {
    if(dad == NULL)
        return;

    if(dad->left != NULL)
        return;

    dad->left = malloc(sizeof(no));
    dad->left->info = elem;
    dad->left->right = NULL;
    dad->left->left = NULL;
}

int height (tree t) {
    if(t == NULL)
        return 0;

    int heightleft = height(t->left);
    int heightright = height(t->right);

    if(heightleft > heightright)
        return(heightleft + 1);

    return(heightright + 1);
}

int numberknots (tree t) {
    if(t == NULL)
        return 0;

    int numberleft = numberknots(t->left);
    int numberright = numberknots(t->right);

    return(numberleft + numberright + 1);
}