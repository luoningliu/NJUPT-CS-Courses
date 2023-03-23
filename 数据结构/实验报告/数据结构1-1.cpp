#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef struct {
	int n;               //˳���ĳ��ȣ�Ԫ�ظ����� 
	int maxLength;       //˳�������������
	ElemType *element;   //��Ŷ�̬����һά�����׵�ַ
}SeqList;

void merge(int *a,int left,int mid,int right)
{
	int temp[100];int k=0;
	int i=left,j=mid+1;
	while (i<=mid&&j<=right)
	{if(a[i]<=a[j]){temp[k++]=a[i++];}
	   else{temp[k++]=a[j++];}
	}
	
	if(i==mid+1)
	{while(j<=right)
	{temp[k++]=a[j++];
	}
	}
	
	if(j==right+1)
	{while(i<=mid)
	{temp[k++]=a[i++];
	}
	}
	for(int i=0,j=left;i<k;i++,j++)
	{a[j]=temp[i];
	}

} 

//�鲢���� 
void SeqListSort(SeqList *L,int left,int right)
{ if(left>=right){return;}
  int* array=L->element;
  int mid=(right+left)/2;
  SeqListSort(L, left, mid);
  SeqListSort(L, mid+1, right);
  merge(array,left,mid,right);
}

 
//˳����ʼ��
int Init(SeqList *L, int maxSize) {
	L->maxLength = maxSize;
	L->n = 0;
	L->element = (ElemType*)malloc(sizeof(ElemType)*maxSize);
    if(!L->element)
    return OK;
}
//˳���Ĳ���
int Find(SeqList L,int i,ElemType *x){
    if(i<0||i>L.n-1){
        return ERROR;    //�ж�Ԫ���±�i�Ƿ�Խ��
    }
    *x=L.element[i];     //��element[i]��ֵ����x 
    return OK;
}
 
//��ʼ������
int Insert(SeqList *L, int i, ElemType x) {
	int j;
	if (i<-1 || i>L->n - 1)                      //�ж��±�i�Ƿ�Խ��
		return ERROR;
	if (L->n == L->maxLength)                    //�ж�˳���洢�ռ��Ƿ�����
		return ERROR;
	for (j = L->n - 1; j > i; j--) {
		L->element[j + 1] = L->element[j];   //�Ӻ���ǰ�������Ԫ��
	}
	L->element[i + 1] = x;                       //����Ԫ�ط����±�Ϊi+1��λ��
	L -> n = L->n + 1;                           //����+1
	return OK;
}
//˳����ɾ��
int Delete(SeqList *L, int i){
    int j;
    if(i<0||i>L->n-1){                   //�±�i�Ƿ�Խ��
        return ERROR;
    }
    if(!L->n){                           //˳����Ƿ�Ϊ��
        return ERROR;
    }
    for(j=i+1;j<L->n;j++){
        L->element[j-1]=L->element[j];   //��ǰ�������ǰ��Ԫ��
    }
    L->n--;                              //����1
    return OK;
}
//˳������
int Output(SeqList *L) {
	int i;
	if (!L->n)
		return ERROR;                 //�ж�˳����Ƿ�Ϊ��
	for (i = 0; i <= L->n - 1; i++)
		printf("%d ", L->element[i]);  //��ǰ����������Ԫ��
	return OK;
}
//˳���ĳ���
void Destroy(SeqList *L){
    (*L).n=0;
    (*L).maxLength=0;
    free((*L).element);
}
int main()
{
	int i,x;
	SeqList list;
	Init(&list, 10);                   //�����Ա��ʼ��
	for (i = 0; i < 9; i++) {
		Insert(&list, i - 1, -i);   //��0-8���뵽˳�����
	}
	Output(&list);
    printf("\n");
    Delete(&list,0);                       //ɾ��0
    printf("\nɾ��0��Ԫ��Ϊ:\n");
	Output(&list);
	printf("\n");
	SeqListSort(&list,0,7);         //���±꣨0��7������ 
	printf("\n��С���������Ϊ:\n");
	Output(&list);
    Destroy(&list);
    return 0;
}
