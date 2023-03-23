#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
#define ERROR 0
#define OK 1
 
typedef struct Node {
	ElemType element;     //����������
	struct Node * link;   //����ָ����
}Node;
 
typedef struct {
	struct Node* head;    //��ͷ���
	int n;
}HeaderList;
 
//����ͷ��㵥����ĳ�ʼ��
int Init(HeaderList *h) {
    h->head=(Node*)malloc(sizeof(Node));      
    if(!h->head){
        return ERROR;
    }
	h->head->link = NULL;                    
	h->n = 0;
	return OK;
}
 
 
//����ͷ��㵥����Ĳ���
int Find(HeaderList *h,int i,ElemType *x){
    Node *p;
    int j;
    if(i<0||i>h->n-1){
        return ERROR;
    }
    p=h->head->link;
    for(j=0;j<i;j++){
        p=p->link;
    }
    *x=p->element;
    return OK;
}
 
 
//����ͷ��㵥����Ĳ���
int Insert(HeaderList *h, int i, ElemType x) {
	Node *p, *q;
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	p = h->head;                     
	for (j = 0; j <= i; j++) {
		p = p->link;
	}
	q = (Node*)malloc(sizeof(Node));  
	q->element = x;
	q->link = p->link;                
	p->link = q;
	h->n++;
	return OK;
}
 
 
//����ͷ��㵥�����ɾ��
int Delete(HeaderList *h,int i){
    int j;
    Node *p,*q;
    if(!h->n){
        return ERROR;
        if(i<0||i>h->n-1){
            return ERROR;
        }
    }
    q=h->head;
    for(j=0;j<i;j++){
        q=q->link;
    }
    p=q->link;
    q->link=p->link;                //�ӵ�������ɾ��p��ָ���
    free(p);                        
    h->n--;
    return OK;
}
//����ͷ��㵥��������
int Output(HeaderList *h) {
	Node *p;
	if (!h->n)
		return ERROR;
	p = h->head->link;
	while (p) {
		printf("%d ",p->element);
		p = p->link;
	}
	return OK;
}
//����ͷ��㵥����ĳ���
void Destroy(HeaderList *h){
    Node *p,*present=h->head; 
    
    while(present)
    {p=present->link;
    free(present);
    present=p;
	}
}
int main()
{
	int i;
	int x;
	HeaderList list;
	Init(&list);
	for (i = 0; i < 11; i++) {
		Insert(&list, i - 1, i);    //����0~10
	}
	Output(&list);
    Delete(&list,0);                //ɾ��0
    printf("\nɾ���±�0��Ԫ����:\n");
    Output(&list);
    Find(&list,1,&x);               //�����±�Ϊ1��Ԫ��
	printf("\n�±�1��Ԫ����:");
	printf("%d ",x);
    Destroy(&list);
    return 0; 
}
