//
//  main.c
//  progetto_2.c
//
//  Created by Luigi Altamura on 05/09/2019.
//  Copyright © 2019 Luigi Altamura. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 6
#define M 40
int flag;
typedef enum { red, black } color;

struct rbnode_entita {
    char data [M+1];
    color c;
    struct rbnode_entita *left, *right, *up;
};
typedef struct rbnode_entita rbnode_entita;
typedef struct {
    rbnode_entita *root, *nil;
} rbtree_entita;


struct rbnode_mittrel {
    char data [M+1];
    color c;
    struct rbnode_mittrel *left, *right, *up;
};
typedef struct rbnode_mittrel rbnode_mittrel;

typedef struct {
    rbnode_mittrel *root, *nil;
} rbtree_mittrel;


struct rbnode_destrel {
    char data [M+1];
    color c;
    int count_dr;
    struct rbnode_destrel *left, *right, *up;
    rbtree_mittrel *albero_mr;
};
typedef struct rbnode_destrel rbnode_destrel;
typedef struct {
    rbnode_destrel *root, *nil;
} rbtree_destrel;


struct rbnode_relazioni {
    char data [M+1];
    color c;
    int count_r;
    struct rbnode_relazioni *left, *right, *up;
    rbtree_destrel *albero_dr;
};
typedef struct rbnode_relazioni rbnode_relazioni;
typedef struct {
    rbnode_relazioni *root, *nil;
} rbtree_relazioni;

int max_glob;
int max_glob_dr;

rbtree_entita *createrbtree_entita(void);
void leftrotate_entita(rbtree_entita *r, rbnode_entita *x);
void rightrotate_entita(rbtree_entita *r, rbnode_entita *x);
void rbinsert_entita(rbtree_entita *tree, char *data);
rbnode_entita *simpleinsert_entita(rbtree_entita *tree,char *data);
void rbdelete_entita(rbtree_entita *tree, rbnode_entita *q);
void fixup_entita(rbtree_entita *tree, rbnode_entita *x);
rbnode_entita *treesucc_entita(rbnode_entita* x, rbtree_entita* head);
void FreeTree(rbtree_entita *head);
rbnode_entita *Search_entita(rbnode_entita *node, rbtree_entita*head, char*data);
rbnode_entita *treeminimum_entita(rbnode_entita *x, rbtree_entita *head );

rbtree_relazioni *createrbtree_relazioni(void);
void leftrotate_relazioni(rbtree_relazioni *r, rbnode_relazioni *x);
void rightrotate_relazioni(rbtree_relazioni *r, rbnode_relazioni *x);
void rbinsert_relazioni(rbtree_relazioni *tree, char *data);
rbnode_relazioni *simpleinsert_relazioni(rbtree_relazioni *tree,char *data);
void rbdelete_relazioni(rbtree_relazioni *tree, rbnode_relazioni *q);
void fixup_relazioni(rbtree_relazioni *tree, rbnode_relazioni *x);
rbnode_relazioni *treesucc_relazioni(rbnode_relazioni* x, rbtree_relazioni* head);
rbnode_relazioni *Search_relazioni(rbnode_relazioni *node, rbtree_relazioni*head, char*data);
rbnode_relazioni *treeminimum_relazioni(rbnode_relazioni *x, rbtree_relazioni *head );

rbtree_destrel *createrbtree_destrel(void);
void leftrotate_destrel(rbtree_destrel *r, rbnode_destrel *x);
void rightrotate_destrel(rbtree_destrel *r, rbnode_destrel *x);
void rbinsert_destrel(rbtree_destrel *tree, char *data);
rbnode_destrel *simpleinsert_destrel(rbtree_destrel *tree,char *data);
void rbdelete_destrel(rbtree_destrel *tree, rbnode_destrel *q);
void fixup_destrel(rbtree_destrel *tree, rbnode_destrel *x);
rbnode_destrel *treesucc_destrel(rbnode_destrel* x, rbtree_destrel* head);
rbnode_destrel *Search_destrel(rbnode_destrel *node, rbtree_destrel*head, char*data);
rbnode_destrel *treeminimum_destrel(rbnode_destrel *x, rbtree_destrel *head );

rbtree_mittrel *createrbtree_mittrel(void);
void leftrotate_mittrel(rbtree_mittrel *r, rbnode_mittrel *x);
void rightrotate_mittrel(rbtree_mittrel *r, rbnode_mittrel *x);
void rbinsert_mittrel(rbtree_mittrel *tree, char *data);
rbnode_mittrel *simpleinsert_mittrel(rbtree_mittrel *tree,char *data);
void rbdelete_mittrel(rbtree_mittrel *tree, rbnode_mittrel *q);
void fixup_mittrel(rbtree_mittrel *tree, rbnode_mittrel *x);
rbnode_mittrel *treesucc_mittrel(rbnode_mittrel* x, rbtree_mittrel* head);
rbnode_mittrel *Search_mittrel(rbnode_mittrel *node, rbtree_mittrel*head, char*data);
rbnode_mittrel *treeminimum_mittrel(rbnode_mittrel *x, rbtree_mittrel *head );
void add_ent(rbnode_entita *root ,rbtree_entita *t, char*key);
void add_rel(rbtree_relazioni *t , char *mitt,char *dest, char *id_rel);
void report_print(rbnode_relazioni *root, rbtree_relazioni *tree);
void report_destrel(rbnode_destrel *node, rbtree_destrel *tree, int max);
void del_rel( rbtree_relazioni *node, char* mitt,char*dest,char* id_rel);
void del_ent(rbnode_relazioni *node,rbtree_relazioni *tree, char *entita );
void del_ent_dr (rbnode_destrel* node, rbtree_destrel *tree,  char *entita);
void del_ent_mr (rbnode_mittrel* node, rbtree_mittrel *tree,  char*entita);
void free_mr (rbnode_mittrel*node, rbtree_mittrel *tree);
void search_new_max(rbnode_destrel *node, rbtree_destrel *tree, int* max);
void elimina_dest (rbnode_destrel*node, rbtree_destrel *tree, char*entita);
/*
void add_rel(relazioni_tree*root,entita_tree *root_e, char *mitt,char *dest, char *id_rel);
void add_ent(entita_tree*root,char*key);
void del_ent(entita_tree*root_e,relazioni_tree *root, char*enita );
void del_rel(entita_tree *root_e, relazioni_tree *root, char* mitt,char*dest,char* id_rel);
void Inorder_delent(relazioni_tree* root, char*entita);
void Inorder_delent_er(entrel_tree* node_er,entrel_tree*root, char*entita);
void Inorder_delent_mr(mittrel_tree* node_mr,mittrel_tree*root, entrel_tree*node_er, entrel_tree*root_er, char*entita);
void report_print(relazioni_tree* root);
void report_entrel(entrel_tree* node_er, int max);

relazioni_tree *pNil = NULL;
entita_tree *pNil_e = NULL;
entrel_tree *pNil_er= NULL;
mittrel_tree *pNil_mr= NULL;

*/
int main(){
    
    char line [M + 1];
    char mitt[M+1];
    char dest[M+1];
    char id_rel[M+1];
    
    rbnode_entita *x;
    rbtree_entita *node_e;
    rbtree_relazioni *node_r;
    
    node_e = createrbtree_entita();
    node_r = createrbtree_relazioni();
    
    do{
        scanf( "%s", line);
        if (strcmp(line,"addent" )==0){
            scanf("%s",mitt);
            add_ent(node_e->root,node_e, mitt);
            
        }
        if (strcmp(line,"addrel")==0){
            scanf("%s",mitt);
            scanf("%s",dest);
            scanf("%s",id_rel);
            x=Search_entita(node_e->root, node_e, mitt);
            if (x != node_e->nil){
                x=Search_entita(node_e->root, node_e, dest);
                if (x!=node_e->nil)
                add_rel(node_r,mitt,dest, id_rel);
            }
        }
        if (strcmp(line,"delent")==0){
            scanf("%s",line);
            x=Search_entita(node_e->root, node_e, line);
            if (x != node_e->nil){
                del_ent(node_r->root,node_r, line);
                rbdelete_entita(node_e, x);
            }
        }
        if (strcmp(line,"delrel")==0){
            scanf("%s",mitt);
            scanf("%s",dest);
            scanf("%s",id_rel);
            x=Search_entita(node_e->root, node_e, mitt);
            if (x != node_e->nil){
                x=Search_entita(node_e->root, node_e, dest);
                if (x!=node_e->nil)
                    del_rel(node_r, mitt, dest, id_rel);
            }
        }
       
        if (strcmp(line,"report")==0){
            flag=0;
            if(node_r->root!= node_r->nil){
                report_print(node_r->root, node_r);
            if(flag!=0)
                fputs ("\n",stdout);
            }
            if (flag==0)
                fputs ("none\n", stdout);
        }
    }while(strcmp(line,"end")!=0);
    
    return 0;
    
}

rbtree_entita *createrbtree_entita(void)
{
    rbtree_entita *t = malloc(sizeof(rbtree_entita));
    if(!t) {
        fprintf(stderr,"Errore di allocazione A\n");
        exit(-1);
    }
    if(!(t->root = malloc(sizeof(rbnode_entita)))) {
        fprintf(stderr,"Errore di allocazione B\n");
        exit(-2); }
    t->nil = t->root;
    t->nil->left = t->nil->right = t->nil->up = t->nil;
    t->nil->c = black;
    return t;
}


void leftrotate_entita(rbtree_entita *r, rbnode_entita *x){
    rbnode_entita *y = x->right;
    x->right = y->left;
    if(y->left != r->nil)
        y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->left)
            y->up->left = y;
        else
            y->up->right = y;
    y->left = x;
    x->up = y;
}


void rightrotate_entita(rbtree_entita *r, rbnode_entita *x) {
    rbnode_entita *y = x->left;
    x->left = y->right;
    if(y->right != r->nil)
        y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->right)
            y->up->right = y;
        else
            y->up->left = y;
    y->right = x;
    x->up = y;
}

void rbinsert_entita(rbtree_entita *tree, char *data)
{
    rbnode_entita *x = simpleinsert_entita(tree, data);
    rbnode_entita *y;
    
    while(x != tree->root && x->up->c == red) {
        if(x->up == x->up->up->left) {
            y = x->up->up->right;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->right)
                    leftrotate_entita(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                rightrotate_entita(tree,x->up->up);
            }
        }else {
            y = x->up->up->left;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->left)
                    rightrotate_entita(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                leftrotate_entita(tree,x->up->up);
            
            }
        }
    }
    tree->root->c = black;
}
rbnode_entita *simpleinsert_entita(rbtree_entita *tree,char *data)
{
    rbnode_entita *q = malloc(sizeof(rbnode_entita));
    rbnode_entita *r = tree->root;
    rbnode_entita *s = tree->nil;
    if(!q) {
        fprintf(stderr,"Errore di allocazione C\n");
        exit(-4);
    }
    
    strcpy (q->data, data);
    q->left = q->right = tree->nil;
    q->c = red;
    while(r != tree->nil) {
        s = r;
        /* colora red il nodo da inserire */
        r = strcmp(data, r->data)<0 ? r->left : r->right;
    }
    q->up = s;
    if(s == tree->nil)
        tree->root = q;
    if(strcmp(data,s->data)<0)
        s->left = q;
    else
        s->right = q;
    return q;
}

void rbdelete_entita(rbtree_entita *tree, rbnode_entita *q)
{
    rbnode_entita *r, *s;
    if(q->left == tree->nil || q->right == tree->nil)
        r = q;
    else
        r = treesucc_entita(q,tree);
    s = r->left != tree->nil ? r->left : r->right;
    s->up = r->up;
    if(r->up == tree->nil)
        tree->root = s;
    else{
        if(r == r->up->left)
            r->up->left = s;
        else
            r->up->right = s;
    }
    if(r != q)
        strcpy(q->data, r->data);
    
    if(r->c == black)
        fixup_entita(tree, s);
    free(r);
}


void fixup_entita(rbtree_entita *tree, rbnode_entita *x) {
    rbnode_entita *w;
    while(x != tree->root && x->c == black) {
        if(x == x->up->left) {
            if((w = x->up->right)->c == red) {
                w->c = black;
                x->up->c = red;
                leftrotate_entita(tree,x->up);
                w = x->up->right;
            }
            if(w->left->c == black && w->right->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->right->c == black) {
                    w->left->c = black; w->c = red;
                    rightrotate_entita(tree,w);
                    w = x->up->right;
                }
                w->c = x->up->c;    x->up->c = black;
                w->right->c = black;
                leftrotate_entita(tree,x->up);
                x = tree->root;
            }
        } else {
            if((w = x->up->left)->c == red) {
                w->c = black;
                x->up->c = red;
                rightrotate_entita(tree,x->up);
                w = x->up->left;
            }
            if(w->right->c == black && w->left->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->left->c == black) {
                    w->right->c = black; w->c = red;
                    leftrotate_entita(tree,w);
                    w = x->up->left;
                }
                w->c = x->up->c;
                x->up->c = black;
                w->left->c = black;
                rightrotate_entita(tree,x->up);
                x = tree->root;
            }
        }
        
    }
x->c = black;
}

rbnode_entita *treesucc_entita(rbnode_entita *x, rbtree_entita *head)
{
    
    rbnode_entita *y;
    if (x->right!= head->nil)
            return treeminimum_entita(x->right, head);
    y=x->up;
    while (y!= head->nil && x==y->right){
        x=y;
        y=y->up;
    }
    return y;
    
}
rbnode_entita *treeminimum_entita(rbnode_entita *x, rbtree_entita *head )
{
    while (x->left != head->nil){
        x=x->left;
    }
    return x;
}

rbnode_entita *Search_entita(rbnode_entita *node, rbtree_entita*head, char*data){
    
    if (node==head->nil || strcmp(data,node->data)==0){
        return node;
    }
    if(strcmp(data,node->data )<0)
        return Search_entita(node->left,head,data);
    else
        return Search_entita (node->right, head, data);
}

rbtree_relazioni *createrbtree_relazioni(void)
{
    rbtree_relazioni *t = malloc(sizeof(rbtree_relazioni));
    if(!t) {
        fprintf(stderr,"Errore di allocazione A\n");
        exit(-1);
    }
    if(!(t->root = malloc(sizeof(rbnode_relazioni)))) {
        fprintf(stderr,"Errore di allocazione B\n");
        exit(-2); }
    t->nil = t->root;
    t->nil->left = t->nil->right = t->nil->up = t->nil;
    t->nil->c = black;
    return t;
}


void leftrotate_relazioni(rbtree_relazioni *r, rbnode_relazioni *x){
    rbnode_relazioni *y = x->right;
    x->right = y->left;
    if(y->left != r->nil)
        y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->left)
            y->up->left = y;
        else
            y->up->right = y;
    y->left = x;
    x->up = y;
}


void rightrotate_relazioni(rbtree_relazioni *r, rbnode_relazioni *x) {
    rbnode_relazioni *y = x->left;
    x->left = y->right;
    if(y->right != r->nil)
        y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->right)
            y->up->right = y;
        else
            y->up->left = y;
    y->right = x;
    x->up = y;
}

void rbinsert_relazioni(rbtree_relazioni *tree, char *data)
{
    rbnode_relazioni *x = simpleinsert_relazioni(tree, data);
    rbnode_relazioni *y;
    
    while(x != tree->root && x->up->c == red) {
        if(x->up == x->up->up->left) {
            y = x->up->up->right;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->right)
                    leftrotate_relazioni(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                rightrotate_relazioni(tree,x->up->up);
            }
        }else {
            y = x->up->up->left;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->left)
                    rightrotate_relazioni(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                leftrotate_relazioni(tree,x->up->up);
                
            }
        }
    }
    tree->root->c = black;
}
rbnode_relazioni *simpleinsert_relazioni(rbtree_relazioni *tree,char *data)
{
    rbnode_relazioni *q = malloc(sizeof(rbnode_relazioni));
    rbnode_relazioni *r = tree->root;
    rbnode_relazioni *s = tree->nil;
    if(!q) {
        fprintf(stderr,"Errore di allocazione C\n");
        exit(-4);
    }
    
    strcpy (q->data, data);
    q->count_r=1;
    q->left = q->right = tree->nil;
    q->c = red;
    while(r != tree->nil) {
        s = r;
        /* colora red il nodo da inserire */
        r = strcmp(data, r->data)<0 ? r->left : r->right;
    }
    q->up = s;
    if(s == tree->nil)
        tree->root = q;
    if(strcmp(data,s->data)<0)
        s->left = q;
    else
        s->right = q;
    return q;
}

void rbdelete_relazioni(rbtree_relazioni *tree, rbnode_relazioni *q)
{
    rbnode_relazioni *r, *s;
    if(q->left == tree->nil || q->right == tree->nil)
        r = q;
    else
        r = treesucc_relazioni(q,tree);
    s = r->left != tree->nil ? r->left : r->right;
    s->up = r->up;
    if(r->up == tree->nil)
        tree->root = s;
    else
        if(r == r->up->left)
            r->up->left = s;
        else
            r->up->right = s;
    if(r != q){
        strcpy(q->data, r->data);
        q->albero_dr=r->albero_dr;
        q->count_r=r->count_r;
    }
    if(r->c == black)
        fixup_relazioni(tree, s);
    free(r);
    
}


void fixup_relazioni(rbtree_relazioni *tree, rbnode_relazioni *x) {
    rbnode_relazioni *w;
    while(x != tree->root && x->c == black) {
        if(x == x->up->left) {
            if((w = x->up->right)->c == red) {
                w->c = black;
                x->up->c = red;
                leftrotate_relazioni(tree,x->up);
                w = x->up->right;
            }
            if(w->left->c == black && w->right->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->right->c == black) {
                    w->left->c = black; w->c = red;
                    rightrotate_relazioni(tree,w);
                    w = x->up->right;
                }
                w->c = x->up->c;    x->up->c = black;
                w->right->c = black;
                leftrotate_relazioni(tree,x->up);
                x = tree->root;
            }
        } else {
            if((w = x->up->left)->c == red) {
                w->c = black;
                x->up->c = red;
                rightrotate_relazioni(tree,x->up);
                w = x->up->left;
            }
            if(w->right->c == black && w->left->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->left->c == black) {
                    w->right->c = black; w->c = red;
                    leftrotate_relazioni(tree,w);
                    w = x->up->left;
                }
                w->c = x->up->c;
                x->up->c = black;
                w->left->c = black;
                rightrotate_relazioni(tree,x->up);
                x = tree->root;
            }
        }
        
    }
    x->c = black;
}

rbnode_relazioni *treesucc_relazioni(rbnode_relazioni *x, rbtree_relazioni *head)
{
    
    rbnode_relazioni *y;
    if (x->right!= head->nil)
        return treeminimum_relazioni(x->right, head);
    y=x->up;
    while (y!= head->nil && x==y->right){
        x=y;
        y=y->up;
    }
    return y;
    
}
rbnode_relazioni *treeminimum_relazioni(rbnode_relazioni *x, rbtree_relazioni *head )
{
    while (x->left != head->nil){
        x=x->left;
    }
    return x;
}

rbnode_relazioni *Search_relazioni(rbnode_relazioni *node, rbtree_relazioni*head, char*data){
    
    if (node==head->nil || strcmp(data,node->data)==0){
        return node;
    }
    if(strcmp(data,node->data )<0)
        return Search_relazioni(node->left,head,data);
    else
        return Search_relazioni (node->right, head, data);
}

rbtree_destrel *createrbtree_destrel(void)
{
    rbtree_destrel *t = malloc(sizeof(rbtree_destrel));
    if(!t) {
        fprintf(stderr,"Errore di allocazione A\n");
        exit(-1);
    }
    if(!(t->root = malloc(sizeof(rbnode_destrel)))) {
        fprintf(stderr,"Errore di allocazione B\n");
        exit(-2); }
    t->nil = t->root;
    t->nil->left = t->nil->right = t->nil->up = t->nil;
    t->nil->c = black;
    return t;
}


void leftrotate_destrel(rbtree_destrel *r, rbnode_destrel *x){
    rbnode_destrel *y = x->right;
    x->right = y->left;
    if(y->left != r->nil)
        y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->left)
            y->up->left = y;
        else
            y->up->right = y;
    y->left = x;
    x->up = y;
}


void rightrotate_destrel(rbtree_destrel *r, rbnode_destrel *x) {
    rbnode_destrel *y = x->left;
    x->left = y->right;
    if(y->right != r->nil)
        y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->right)
            y->up->right = y;
        else
            y->up->left = y;
    y->right = x;
    x->up = y;
}

void rbinsert_destrel(rbtree_destrel *tree, char *data)
{
    rbnode_destrel *x = simpleinsert_destrel(tree, data);
    rbnode_destrel *y;
    
    while(x != tree->root && x->up->c == red) {
        if(x->up == x->up->up->left) {
            y = x->up->up->right;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->right)
                    leftrotate_destrel(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                rightrotate_destrel(tree,x->up->up);
            }
        }else {
            y = x->up->up->left;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->left)
                    rightrotate_destrel(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                leftrotate_destrel(tree,x->up->up);
                
            }
        }
    }
    tree->root->c = black;
}
rbnode_destrel *simpleinsert_destrel(rbtree_destrel *tree,char *data)
{
    rbnode_destrel *q = malloc(sizeof(rbnode_destrel));
    rbnode_destrel *r = tree->root;
    rbnode_destrel *s = tree->nil;
    if(!q) {
        fprintf(stderr,"Errore di allocazione C\n");
        exit(-4);
    }
    
    strcpy (q->data, data);
    q->left = q->right = tree->nil;
    q->c = red;
    q->count_dr=1;
    while(r != tree->nil) {
        s = r;
        /* colora red il nodo da inserire */
        r = strcmp(data, r->data)<0 ? r->left : r->right;
    }
    q->up = s;
    if(s == tree->nil)
        tree->root = q;
    if(strcmp(data,s->data)<0)
        s->left = q;
    else
        s->right = q;
    return q;
}

void rbdelete_destrel(rbtree_destrel *tree, rbnode_destrel *q)
{
    rbnode_destrel *r, *s;
    if(q->left == tree->nil || q->right == tree->nil)
        r = q;
    else
        r = treesucc_destrel(q,tree);
    s = r->left != tree->nil ? r->left : r->right;
    s->up = r->up;
    if(r->up == tree->nil)
        tree->root = s;
    else
        if(r == r->up->left)
            r->up->left = s;
        else
            r->up->right = s;
    if(r != q){
        strcpy(q->data, r->data);
        q->albero_mr=r->albero_mr;
        q->count_dr=r->count_dr;
    }
    if(r->c == black)
        fixup_destrel(tree, s);
    free(r);
}


void fixup_destrel(rbtree_destrel *tree, rbnode_destrel *x) {
    rbnode_destrel *w;
    while(x != tree->root && x->c == black) {
        if(x == x->up->left) {
            if((w = x->up->right)->c == red) {
                w->c = black;
                x->up->c = red;
                leftrotate_destrel(tree,x->up);
                w = x->up->right;
            }
            if(w->left->c == black && w->right->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->right->c == black) {
                    w->left->c = black; w->c = red;
                    rightrotate_destrel(tree,w);
                    w = x->up->right;
                }
                w->c = x->up->c;    x->up->c = black;
                w->right->c = black;
                leftrotate_destrel(tree,x->up);
                x = tree->root;
            }
        } else {
            if((w = x->up->left)->c == red) {
                w->c = black;
                x->up->c = red;
                rightrotate_destrel(tree,x->up);
                w = x->up->left;
            }
            if(w->right->c == black && w->left->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->left->c == black) {
                    w->right->c = black; w->c = red;
                    leftrotate_destrel(tree,w);
                    w = x->up->left;
                }
                w->c = x->up->c;
                x->up->c = black;
                w->left->c = black;
                rightrotate_destrel(tree,x->up);
                x = tree->root;
            }
        }
        
    }
    x->c = black;
}

rbnode_destrel *treesucc_destrel(rbnode_destrel *x, rbtree_destrel *head)
{
    
    rbnode_destrel *y;
    if (x->right!= head->nil)
        return treeminimum_destrel(x->right, head);
    y=x->up;
    while (y!= head->nil && x==y->right){
        x=y;
        y=y->up;
    }
    return y;
    
}
rbnode_destrel *treeminimum_destrel(rbnode_destrel *x, rbtree_destrel *head )
{
    while (x->left != head->nil){
        x=x->left;
    }
    return x;
}

rbnode_destrel *Search_destrel(rbnode_destrel *node, rbtree_destrel*head, char*data){
    
    if (node==head->nil || strcmp(data,node->data)==0){
        return node;
    }
    if(strcmp(data,node->data )<0)
        return Search_destrel(node->left,head,data);
    else
        return Search_destrel (node->right, head, data);
}

rbtree_mittrel *createrbtree_mittrel(void)
{
    rbtree_mittrel *t = malloc(sizeof(rbtree_mittrel));
    if(!t) {
        fprintf(stderr,"Errore di allocazione A\n");
        exit(-1);
    }
    if(!(t->root = malloc(sizeof(rbnode_mittrel)))) {
        fprintf(stderr,"Errore di allocazione B\n");
        exit(-2); }
    t->nil = t->root;
    t->nil->left = t->nil->right = t->nil->up = t->nil;
    t->nil->c = black;
    return t;
}


void leftrotate_mittrel(rbtree_mittrel *r, rbnode_mittrel *x){
    rbnode_mittrel *y = x->right;
    x->right = y->left;
    if(y->left != r->nil)
        y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->left)
            y->up->left = y;
        else
            y->up->right = y;
    y->left = x;
    x->up = y;
}


void rightrotate_mittrel(rbtree_mittrel *r, rbnode_mittrel *x) {
    rbnode_mittrel *y = x->left;
    x->left = y->right;
    if(y->right != r->nil)
        y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
        r->root = y;
    else
        if(x == x->up->right)
            y->up->right = y;
        else
            y->up->left = y;
    y->right = x;
    x->up = y;
}

void rbinsert_mittrel(rbtree_mittrel *tree, char *data)
{
    rbnode_mittrel *x = simpleinsert_mittrel(tree, data);
    rbnode_mittrel *y;
    
    while(x != tree->root && x->up->c == red) {
        if(x->up == x->up->up->left) {
            y = x->up->up->right;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->right)
                    leftrotate_mittrel(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                rightrotate_mittrel(tree,x->up->up);
            }
        }else {
            y = x->up->up->left;
            if(y->c == red) {
                x->up->c = black;
                y->c = black;
                x->up->up->c = red;
                x = x->up->up;
            } else {
                if(x == x->up->left)
                    rightrotate_mittrel(tree,x = x->up);
                x->up->c = black;
                x->up->up->c = red;
                leftrotate_mittrel(tree,x->up->up);
                
            }
        }
    }
    tree->root->c = black;
}
rbnode_mittrel *simpleinsert_mittrel(rbtree_mittrel *tree,char *data)
{
    rbnode_mittrel *q = malloc(sizeof(rbnode_mittrel));
    rbnode_mittrel *r = tree->root;
    rbnode_mittrel *s = tree->nil;
    if(!q) {
        fprintf(stderr,"Errore di allocazione C\n");
        exit(-4);
    }
    
    strcpy (q->data, data);
    q->left = q->right = tree->nil;
    q->c = red;
    while(r != tree->nil) {
        s = r;
        /* colora red il nodo da inserire */
        r = strcmp(data, r->data)<0 ? r->left : r->right;
    }
    q->up = s;
    if(s == tree->nil)
        tree->root = q;
    if(strcmp(data,s->data)<0)
        s->left = q;
    else
        s->right = q;
    return q;
}

void rbdelete_mittrel(rbtree_mittrel *tree, rbnode_mittrel *q)
{
    rbnode_mittrel *r, *s;
    if(q->left == tree->nil || q->right == tree->nil)
        r = q;
    else
        r = treesucc_mittrel(q,tree);
    s = r->left != tree->nil ? r->left : r->right;
    s->up = r->up;
    if(r->up == tree->nil)
        tree->root = s;
    else
        if(r == r->up->left)
            r->up->left = s;
        else
            r->up->right = s;
    if(r != q)
        strcpy(q->data, r->data);
    if(r->c == black)
        fixup_mittrel(tree, s);
    free(r);
}


void fixup_mittrel(rbtree_mittrel *tree, rbnode_mittrel *x) {
    rbnode_mittrel *w;
    while(x != tree->root && x->c == black) {
        if(x == x->up->left) {
            if((w = x->up->right)->c == red) {
                w->c = black;
                x->up->c = red;
                leftrotate_mittrel(tree,x->up);
                w = x->up->right;
            }
            if(w->left->c == black && w->right->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->right->c == black) {
                    w->left->c = black; w->c = red;
                    rightrotate_mittrel(tree,w);
                    w = x->up->right;
                }
                w->c = x->up->c;    x->up->c = black;
                w->right->c = black;
                leftrotate_mittrel(tree,x->up);
                x = tree->root;
            }
        } else {
            if((w = x->up->left)->c == red) {
                w->c = black;
                x->up->c = red;
                rightrotate_mittrel(tree,x->up);
                w = x->up->left;
            }
            if(w->right->c == black && w->left->c == black) {
                w->c = red;
                x = x->up;
            } else {
                if(w->left->c == black) {
                    w->right->c = black; w->c = red;
                    leftrotate_mittrel(tree,w);
                    w = x->up->left;
                }
                w->c = x->up->c;
                x->up->c = black;
                w->left->c = black;
                rightrotate_mittrel(tree,x->up);
                x = tree->root;
            }
        }
        
    }
    x->c = black;
}

rbnode_mittrel *treesucc_mittrel(rbnode_mittrel *x, rbtree_mittrel *head)
{
    
    rbnode_mittrel *y;
    if (x->right!= head->nil)
        return treeminimum_mittrel(x->right, head);
    y=x->up;
    while (y!= head->nil && x==y->right){
        x=y;
        y=y->up;
    }
    return y;
    
}
rbnode_mittrel *treeminimum_mittrel(rbnode_mittrel *x, rbtree_mittrel *head )
{
    while (x->left != head->nil){
        x=x->left;
    }
    return x;
}

rbnode_mittrel *Search_mittrel(rbnode_mittrel *node, rbtree_mittrel*head, char*data){
    
    if (node==head->nil || strcmp(data,node->data)==0){
        return node;
    }
    if(strcmp(data,node->data )<0)
        return Search_mittrel(node->left,head,data);
    else
        return Search_mittrel (node->right, head, data);
}

void add_ent(rbnode_entita *root ,rbtree_entita *t, char*key){
    rbnode_entita *x;
    x = Search_entita(root, t, key);
    if( x == t->nil){
        rbinsert_entita(t, key);
    }
}

void add_rel(rbtree_relazioni *t , char *mitt,char *dest, char *id_rel){
    rbnode_relazioni *y;
    rbnode_destrel *z;
    rbnode_mittrel *w;

    y=Search_relazioni(t->root, t, id_rel) ;
            
    if (y==t->nil){
        rbinsert_relazioni(t, id_rel);
        y=Search_relazioni(t->root, t, id_rel);
        y->albero_dr=createrbtree_destrel();
        rbinsert_destrel(y->albero_dr, dest);
        z=Search_destrel(y->albero_dr->root, y->albero_dr, dest);
        z->albero_mr=createrbtree_mittrel();
        rbinsert_mittrel(z->albero_mr, mitt);
    }else{
        z=Search_destrel(y->albero_dr->root, y->albero_dr, dest);
        if(z==y->albero_dr->nil){
        rbinsert_destrel(y->albero_dr, dest);
        z=Search_destrel(y->albero_dr->root, y->albero_dr, dest);
        z->albero_mr=createrbtree_mittrel();
        rbinsert_mittrel(z->albero_mr, mitt);
        if (y->count_r==0)
            y->count_r++;
        }else{
            w=Search_mittrel(z->albero_mr->root, z->albero_mr, mitt);
            if (w==z->albero_mr->nil){
                rbinsert_mittrel(z->albero_mr, mitt);
                z->count_dr++;
            }
            if (z->count_dr > y->count_r)
                y->count_r=z->count_dr;
            }
    }
}
    

void del_rel(rbtree_relazioni *node, char* mitt,char*dest,char* id_rel){
    
    rbnode_relazioni *x;
    rbnode_destrel *y;
    rbnode_mittrel *z;
    
    x=Search_relazioni(node->root, node, id_rel);
    if(x!= node->nil){
        y=Search_destrel(x->albero_dr->root, x->albero_dr, dest);
        if(y!=x->albero_dr->nil){
            z=Search_mittrel(y->albero_mr->root, y->albero_mr, mitt);
            if(z!= y->albero_mr->nil){
                rbdelete_mittrel(y->albero_mr, z);
                y->count_dr--;
                if(x->count_r == y->count_dr+1){
                    int temp;
                    temp = y->count_dr;
                    search_new_max (x->albero_dr->root,x->albero_dr, &temp);
                    x->count_r=temp;
                }
                if (y->albero_mr->root==y->albero_mr->nil){
                    rbdelete_destrel(x->albero_dr, y);
                    int temp;
                    temp =0;
                    search_new_max (x->albero_dr->root,x->albero_dr, &temp);
                    x->count_r=temp;
                }
                if(x->albero_dr->root==x->albero_dr->nil){
                    rbdelete_relazioni(node, x);
                }
            }
        }
    }
}

void search_new_max(rbnode_destrel *node, rbtree_destrel *tree, int* max){
    if(node==tree->nil)
        return;
    
    search_new_max(node->left, tree, max);
    
        if(node->count_dr>*max)
            *max=node->count_dr;
    
    search_new_max(node->right, tree, max);
    return;

}

void del_ent(rbnode_relazioni *node,rbtree_relazioni *tree, char*entita ){
   
    if (node==tree->nil)
         return;
    
    del_ent(node->left,tree, entita);
    
    elimina_dest(node->albero_dr->root, node->albero_dr, entita);
    
    del_ent_dr(node->albero_dr->root,node->albero_dr, entita);
    
    int temp=0;
    search_new_max(node->albero_dr->root, node->albero_dr, &temp );
    node->count_r=temp;
    
    
    del_ent(node->right, tree, entita);
    return;
    
}


void del_ent_dr (rbnode_destrel* node, rbtree_destrel *tree,  char*entita)
{
 
   if(node==tree->nil)
        return;
    
    del_ent_dr(node->left, tree, entita);
    
    rbnode_mittrel *x;
    x=Search_mittrel(node->albero_mr->root, node->albero_mr, entita);
   if (x!= node->albero_mr->nil){
        rbdelete_mittrel(node->albero_mr, x);
        node->count_dr--;
    }
    del_ent_dr (node->right, tree, entita);
    
    return;
  
}
void elimina_dest (rbnode_destrel*node, rbtree_destrel *tree, char*entita){
    
    rbnode_destrel *x;
    x=Search_destrel(node, tree, entita);
    if (x!=tree->nil){
        free_mr(x->albero_mr->root, x->albero_mr);
        rbdelete_destrel(tree, x);
    }
}

void free_mr (rbnode_mittrel*node, rbtree_mittrel *tree){
    if (node==tree->nil)
        return;
    free_mr (node->left, tree);
    free_mr (node->right,tree);
    free(node);
}

void report_print(rbnode_relazioni *root, rbtree_relazioni *tree){
    if ( root == tree->nil ){
        return;
    }
    
    report_print(root->left, tree);
    if(root->count_r !=0 && root->albero_dr->root != root->albero_dr->nil){
        flag++;
        fputs(root->data, stdout);
        fputs(" ", stdout);
        report_destrel(root->albero_dr->root, root->albero_dr, root->count_r);
        printf("%d; ",root->count_r);
    }
    
    report_print(root->right, tree);
    
    return;
    
    
}

void report_destrel(rbnode_destrel *node, rbtree_destrel *tree, int max){
    
    if ( node == tree->nil )
        return;
    
    report_destrel( node->left,tree, max );
    if(node->count_dr==max){
        fputs(node->data, stdout);
        fputs(" ", stdout);
    }
    
    report_destrel (node->right, tree, max);
        
    return;
    
    
}
