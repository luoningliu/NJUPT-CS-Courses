#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef char ElemType;
typedef struct BinaryTreeNode{
    ElemType Data;
    struct BinaryTreeNode *LChild, *RChild;
}BinaryTreeNode;
 
 
//�������
void PreOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    printf("%c",t->Data);           //��ӡ�������㣬�˴����Զ�����������
    PreOrderTransverse(t->LChild);  //Ȼ���������������
    PreOrderTransverse(t->RChild);  //����������������
}
 
 
//�������
void InOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->LChild);  //�������������������
    printf("%c",t->Data);          //��ӡ�������㣬�˴����Զ�����������
    InOrderTransverse(t->RChild);  //����������������������
}
 
 
//�������
void PostOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    PostOrderTransverse(t->LChild);  //�������������������
    PostOrderTransverse(t->RChild);  //Ȼ��������������������
    printf("%c",t->Data);            //����ӡ�������㣬�˴����Զ�����������
}
 
 
//�����������������
BinaryTreeNode *PreCreateBt(BinaryTreeNode *t){
    char ch;
    ch = getchar();
    if(ch == '#'){                           //����Ϊ#��ʾ���ｨ���ն��������������㷨�Ŀղ���
        t = NULL;
    }
    else{
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->Data = ch;                        //��������
        t->LChild = PreCreateBt(t->LChild);  //����������
        t->RChild = PreCreateBt(t->RChild);  //����������
    }
    return t;
}

//�������������
int Size(BinaryTreeNode *t){
    if(!t) return 0;
    return Size(t->LChild) + Size(t->RChild) + 1;
}
 
//�������Ҷ�ӽ�����
int Leaf(BinaryTreeNode *t){
    if(!t) return 0;
    if((t->LChild == NULL) && (t->RChild == NULL)) return 1;
    return Leaf(t->LChild) + Leaf(t->RChild);
}
 
//��������ĸ߶� 
//�߶ȴӵ�һ�㿪ʼ 
int Depth(BinaryTreeNode *t){
    if(!t) return 0;
    else return 1 + max(Depth(t->LChild) , Depth(t->RChild));
}

void Exchange(BinaryTreeNode *t){
	if(!t) return;
	else 
	{ BinaryTreeNode *q = t->LChild;
        t->LChild = t->RChild;
        t->RChild = q;
	
	Exchange(t->LChild), Exchange(t->RChild);
}
	}

int main(){
    BinaryTreeNode *t = NULL;
    printf("�����������:\n");
    t = PreCreateBt(t);                     //�з���ֵ������ǰ��Ҫ�Ӹ�t = ����Ȼ����û�������
    printf("\n�������:\n");
	PreOrderTransverse(t);
    printf("\n\n�������:\n");
    InOrderTransverse(t);
    printf("\n\n�������:\n");
    PostOrderTransverse(t);
    printf("\n");
    printf("������Ϊ:%d\n",Size(t));
    printf("Ҷ�ӽ�����Ϊ:%d\n",Leaf(t));
    printf("�������ĸ߶�Ϊ:%d\n",Depth(t));
    Exchange(t);
    printf("\n������������������:\n\n");
    printf("�������:\n");
    PreOrderTransverse(t);
    printf("\n\n�������:\n");
    InOrderTransverse(t);
    printf("\n\n�������:\n");
    PostOrderTransverse(t);
    printf("\n");


    return 0;
}
