#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;

void InitList(LinkList);
void HeadList(LinkList, int *, int);
void OutPut(LinkList);
void DestoryList(LinkList);
void TailList(LinkList, int *, int);
void InsertList(LinkList, int, int);
void Search(LinkList, int);

int main(void)
{
    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkList L = (LinkList) malloc(sizeof(LinkNode));
    InitList(L);
    HeadList(L, num, 10);
    OutPut(L);
    DestoryList(L);
    L = (LinkList) malloc(sizeof(LinkNode));
    InitList(L);
    TailList(L, num, 10);
    OutPut(L);
    InsertList(L, 5, 11);
    OutPut(L);
    Search(L, 7);

    return 0;
}

void InitList(LinkList L)
{
    L->next = NULL;
}

void HeadList(LinkList L, int *a, int N)
{
    for(int n = 0; n < N; ++n){
        LinkNode *node = (LinkNode *) malloc(sizeof(LinkNode));
        node->next = L->next;
        L->next = node;
        node->data = a[n];
    }
}

void OutPut(LinkList L)
{
    LinkNode *p = L->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void DestoryList(LinkList L)
{
    LinkNode *prenode = L;
    LinkNode *p = L->next;
    while(p != NULL){
        free(prenode);
        prenode = p;
        p = p->next;
    }
}

void TailList(LinkList L, int *a, int N)
{
    LinkNode *p = L;
    for(int n = 0; n < N; ++n){
        LinkNode *node = (LinkNode *) malloc(sizeof(LinkNode));
        node->next = p->next;
        p->next = node;
        p = node;
        node->data = a[n];
    }
}

void InsertList(LinkList L, int position, int num)
{
    int n = 1;
    LinkNode *p = L->next;
    if(position < 1){
        return;
    }
    while(p&&n<position-1){
        p = p->next;
        ++n;
    }
    if(p == NULL && n > position-1){
        return;
    }
    LinkNode *node = (LinkNode *) malloc(sizeof(LinkNode));
    node->data = num;
    node->next = p->next;
    p->next = node;
}

void Search(LinkList L, int num)
{
    int n = 1;
    LinkNode *p = L->next;
    while(p->data != num){
        p = p->next;
        ++n;
    }
    printf("The position is %d\n", n);
}