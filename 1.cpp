
#define _CRT_SECURE_NO_WARNINGS
#include "list_seq.h"
​
void InitSqList(SqList *L) {
    L->length = 0;
}//chushihua shunxubiao
​
int ReadSqList(SqList *L) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("异常：读取长度失败！\n");
        return 0;
    }
    if (n <= 0) {
        printf("异常：序列长度不能<=0！\n");
        return 0;
    }
    if (n > MAXSIZE) {
        printf("异常：序列长度超过最大容量！\n");
        return 0;
    }
    InitSqList(L);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &L->data[i]) != 1) {
            printf("异常：读取序列元素失败！\n");
            return 0;
        }
    }
    L->length = n;
    return 1;
}//duqushunxubiao
​
int getSum(SqList *L) {
    int sum = 0;
    for (int i = 0; i < L->length; i++) {
        sum += L->data[i];
    }
    return sum;
} 
​
void DelDivElement(SqList *A, SqList *D, int sum) {
    InitSqList(D);
    for (int i = 0; i < A->length; i++) {
        if (sum % A->data[i] != 0) {
            D->data[D->length++] = A->data[i];
        }
    }
}
​
void PrintSqList(SqList *L) {
    if (L->length == 0) {
        printf("空序列\n");
      return;
    }
    for (int i = 0; i < L->length; i++) {
        if (i > 0) printf(",");
        printf("%d", L->data[i]);
    }
    printf("\n");
}
​
//================单链表函数实现================
void InitLinkList(LinkList *L) {
    *L = (LNode*)malloc(sizeof(LNode));
    if (*L == NULL) {
        printf("异常：内存分配失败！\n");
        exit(1);
    }
    (*L)->next = NULL;
}
​
int ReadLinkList(LinkList *L) {
    int n, val;
    if (scanf("%d", &n) != 1) {
        printf("异常：读取链表长度失败！\n");
        return 0;
    }
    if (n <= 0) {
        printf("异常：链表长度不能<=0！\n");
        return 0;
    }
    InitLinkList(L);
    LNode* tail = *L;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &val) != 1) {
            printf("异常：读取链表元素失败！\n");
            return 0;
        }
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        if (newNode == NULL) {
            printf("异常：内存分配失败！\n");
            return 0;
        }
        newNode->data = val;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    return 1;
}
​
void PrintLinkList(LinkList L) {
    if (L->next == NULL) {
        printf("空链表\n");
        return;
    }
    LNode* p = L->next;
    while (p != NULL) {
        if (p != L->next) printf(",");
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
}
​
//链表冒泡升序排序，修复VS未初始化警告
void SortLinkList(LinkList C)
{
    if (C == NULL || C->next == NULL || C->next->next == NULL)
        return;
    LNode *p, *q;//what's this 
    int temp;
    for (p = C->next; p->next != NULL; p = p->next)
    {
        for (q = C->next; q->next != NULL; q = q->next)
        {
            if (q->data > q->next->data)
            {
                temp = q->data;
                q->data = q->next->data;
                q->next->data = temp;
            }
        }
    }
}
​
//合并：D顺序表所有元素 + B链表所有元素，存入C并整体升序
LinkList MergeSqAndLink(SqList *D, LinkList B) {
    LinkList C;
    InitLinkList(&C);
    LNode* tail = C;
    LNode* p;
​
    //拷贝D顺序表
    for (int i = 0; i < D->length; i++)
    {
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        if (newNode == NULL)
        {
            printf("异常：内存分配失败！\n");
            exit(1);
        }
        newNode->data = D->data[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    //拷贝B链表
    p = B->next;
    while (p != NULL)
    {
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        if (newNode == NULL)
        {
            printf("异常：内存分配失败！\n");
            exit(1);
        }
        newNode->data = p->data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        p = p->next;
    }
    SortLinkList(C);
    return C;
}
​
//去重
void DelRepeat(LinkList C) {
    if (C->next == NULL) return;
    LNode* p = C->next;
    while (p != NULL && p->next != NULL) {
        LNode* q = p;
        while (q->next != NULL) {
            if (q->next->data == p->data) {
                LNode* del = q->next;
                q->next = q->next->next;
                free(del);
            }
            else {
                q = q->next;
            }
        }
        p = p->next;
    }
}
​
//递归辅助函数，用于逆序打印
void PrintDescSub(LNode* p, int *first);
​
void PrintDesc(LinkList C) {
    if (C->next == NULL) {
        printf("空序列");
        return;
    }
    int first = 1;
    LNode* p = C->next;
    PrintDescSub(p, &first);
}
​
void PrintDescSub(LNode* p, int *first) {
    if (p == NULL) return;
    PrintDescSub(p->next, first);
    if (!(*first)) {
        printf(",");
    }
    *first = 0;
    printf("%d", p->data);
}
​
void DestroyLinkList(LinkList *L) {
    LNode* p = *L, *q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    *L = NULL;
}
​
//==================== main函数（修复参数缺失bug） ====================
int main()
{
    SqList A, D;
    LinkList B = NULL, C = NULL;
​
    //读取顺序表A
    if (!ReadSqList(&A))
    {
        return EXIT_FAILURE;
    }
​
    int sum = getSum(&A);
    //修复：传入3个参数
    DelDivElement(&A, &D, sum);
    PrintSqList(&D);
​
    //读取单链表B
    if (!ReadLinkList(&B))
    {
        DestroyLinkList(&B);
        return EXIT_FAILURE;
    }
​
    //合并D和B，生成升序链表C
    C = MergeSqAndLink(&D, B);
    PrintLinkList(C);
​
    //对C去重
    DelRepeat(C);
    //降序输出
    PrintDesc(C);
    printf("\n");
​
    //释放内存，防止内存泄漏
    DestroyLinkList(&B);
    DestroyLinkList(&C);
​
    return EXIT_SUCCESS;
}
