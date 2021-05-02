#include <stdio.h>

#define MAXSIZE 20

typedef struct SqList {
    int data[MAXSIZE];
    int length;
} SqList;

void InitList(SqList *);
void CreateList(SqList *, int *, int);
void OutPut(SqList *);
int ListFull(SqList *);
void Sert(SqList *, int, int);
int ListEmpty(SqList *);
void Search(SqList *, int);
void Delete(SqList *, int);

int main(void)
{
    int number[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqList L;
    InitList(&L);
    CreateList(&L, number, 10);
    OutPut(&L);
    Sert(&L, 5, 12);
    OutPut(&L);
    Delete(&L, 6);
    OutPut(&L);
    Search(&L, 7);

    return 0;
}

void InitList(SqList *L)
{
    L->length = 0;
}

void CreateList(SqList *L, int *a, int N)
{
    for(int n = 0; n < N; ++n){
        L->data[n] = a[n];
        L->length++;
    }
}

void OutPut(SqList *L)
{
    for(int n = 0; n < L->length; ++n){
        printf("%d ", L->data[n]);
    }
    printf("\n");
}

int ListFull(SqList *L)
{
    return L->length == MAXSIZE ? 0 : 1;
}

void Sert(SqList *L, int position, int num)
{
    if(ListFull(L)){ //不满则执行
        if(position < 1 || L->length == MAXSIZE || position > L->length+1){
            return;
        }
        for(int n = L->length-1; n >= position-1; --n){
            L->data[n+1] = L->data[n];
        }
        L->data[position-1] = num;
        L->length++;
    }
}

int ListEmpty(SqList *L)
{
    return L->length == 0;
}

void Search(SqList *L, int num)
{
    int n;
    for(n = 0; L->data[n] != num; ++n){
    }
    printf("The position is %d\n", n+1);
}

void Delete(SqList *L, int position)
{
    if(ListEmpty(L)){
        return;
    }
    if(position < 0 || position > L->length){
        return;
    }
    for(int n = position; n < L->length; ++n){
        L->data[n-1] = L->data[n];
    }
    L->length--;
}