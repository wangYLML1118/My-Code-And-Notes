#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct Node
{
    int date;//数据域
    struct Node* pNext;//指针域
}*PNODE;


//函数声明
PNODE creat_List(void);//创建一个链表
void traverse(PNODE pHead);//遍历
int is_empty(PNODE pHead);//判空
int length_List(PNODE pHead);//链表长度
int Insert(PNODE pHead,int pos,int val);//查找
int moveout(PNODE pHead,int pos);//删除
PNODE FindNode(PNODE pHead,int val);//查找

int main(void)
{
    PNODE pHead=NULL;
    printf("     线性表子系统     \n");
    printf("*********************\n");
    printf("*    1、建表        *\n");
    printf("*    2、插入       *\n");
    printf("*    3、删除        *\n");
    printf("*    4、显示        *\n");
    printf("*    5、查找        *\n");
    printf("*    6、求表长      *\n");
    printf("*    0、返回        *\n");
    printf("请输入要执行操作的序号(0-6):    ");
    printf("输入其他数字将会退出系统！");
    int n;
    scanf("%d",&n);stack->size=0;

    while(n!=0)
    {
        if(n<0||n>6)
        {
            printf("输入错误！！！");
            exit(-1);
        }
        if(n==1)
        {
            pHead=creat_List();
            printf("创建成功！\n请输入要执行的操作序号：");
        }
        if(n==2)
        {
            int pos,val;
            printf("请输入要插入的位置（插入在此位置之前）：");
            scanf("%d",&pos);
            printf("请输入要插入节点的值：");
            scanf("%d",&val);
            int k;
            k=Insert(pHead,pos,val);
            if(k==1)
            {
                printf("插入成功!\n请输入要执行的操作：");
            }
        }
        if(n==3)
        {
            int pos;
            printf("请输入要删除的值的位置：");
            scanf("%d",&pos);
            if(moveout(pHead,pos))
            {
                printf("删除成功！\n请输入要执行的操作：");
            }
        }
        if(n==4)
        {
            traverse(pHead);
            printf("请输入要执行的操作：");
        }
        if(n==5)
        {
            int val;
            printf("请输入要查找的节点的值(整数))：");
            scanf("%d",&val);
            PNODE p=FindNode(pHead,val);
            printf("请输入要执行的操作：");
        }
        if(n==6)
        {
            int length;
            length=length_List(pHead);
            printf("表长为%d",length);
            printf("请输入要执行的操作：");
        }
        scanf("%d",&n);
    }
}
PNODE creat_List(void)
{
    int len;//用来存放有效节点的数目
    int i;
    int val;//用来临时存放用户输入的节点的值
    //分配了一个不存放有效数字的头结点
    PNODE pHead=(PNODE)malloc(sizeof(struct Node));
    if(NULL==pHead)
    {
        printf("分配失败，程序终止\n");
            exit(-1);
    }
    PNODE pTail=pHead;
    pTail->pNext=NULL;
    printf("请输入您想要生成的节点个数：len=");
    scanf("%d",&len);
    for(i=0;i<len;++i)
    {
        printf("请输入第%d个节点的值：",i+1);
        scanf("%d",&val);

        PNODE pNew=(PNODE)malloc(sizeof(struct Node));
        if(NULL==pNew)
        {
            printf("分配失败！,程序终止！");
            exit(-1);
        }
        pNew->date=val;
        pTail->pNext=pNew;
        pNew->pNext=NULL;
        pTail=pNew;
    }
    return pHead;
}


int Insert(PNODE pHead,int pos,int val)
{
    int i=0;
    PNODE p=pHead;
    while(NULL!=p&&i<pos-1)
    {
        p=p->pNext;
        ++i;
    }
    if(i>pos-1||NULL==p)
    {
        return 0;
    }
    PNODE pNew=(PNODE)malloc(sizeof(struct Node));
    if(NULL==pNew)
    {
        printf("动态内存分配失败！\n");
        exit(-1);
    }
    pNew->date=val;
    PNODE q=p->pNext;
    p->pNext=pNew;
    pNew->pNext=q;

    return 1;
}
void traverse(PNODE pHead)
{
    PNODE p=pHead->pNext;//头结点指向p
    while(NULL!=p)
    {
        printf("%d",p->date);
        p=p->pNext;
		if(p!=NULL)
		{
	    	printf("->");
		}
    }
    printf("\n");
    return;
}



int is_empty(PNODE pHead)
{
    if(NULL==pHead->pNext)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int length_List(PNODE pHead)
{
    PNODE p=pHead->pNext;
    int len=0;
    while(p!=NULL)
    {
        ++len;
        p=p->pNext;
    }
    return len;
}
int moveout(PNODE pHead,int pos)
{
    int i=0;
    PNODE p=pHead;
    while(NULL!=p&&i<pos-1)
    {
        p=p->pNext;
        ++i;
    }
    if(i>pos-1||NULL==p)
    {
        return 0;
    }
    PNODE q=p->pNext;


    //删除p节点后面的一个节点
    p->pNext=q->pNext;
    free(q);
    q=NULL;
    return 1;
}
PNODE FindNode(PNODE pHead,int val)
{
    PNODE p=NULL;
    while(p&&!pHead)
    {
        if(pHead->date==val)
        {
            p=pHead;
            printf("查找成功\n");
        }
        pHead=pHead->pNext;
    }
    return p;
}

