#include<stdio.h>
#include<stdlib.h>
 
typedef struct PNode{
    int coef;             //ϵ��
    int exp;              //ָ��
    struct PNode* link;
}PNode;
 
typedef struct{
    struct PNode *head;
}polynominal;
 

//����ʽ�Ĵ���
void Create(polynominal *p){
    PNode *pn,*pre,*q;
    p->head = (PNode*)malloc(sizeof(PNode));//��ͷ�ڵ� 
    p->head->exp = -1;//��ͷ�ڵ��expΪ-1 
    p->head->link = p->head;               //ѭ������ 
    for(;;){
        pn=(PNode*)malloc(sizeof(PNode));
        printf("ϵ��:\n");
        scanf("%d",&pn->coef);
        printf("ָ��:\n");
        scanf("%d",&pn->exp);
        if(pn->exp<0) {free(pn);break;}//ֱ��exp����-1������ 
        pre = p->head;
        q = p->head->link;
        while(q && q->exp > pn->exp){
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}
//����ʽ���
void Output(polynominal p){
    PNode *q;
    int flag = 1;                                   //�Ƿ�Ϊ��һ��
    q = p.head->link;//ͷ��� 
    if (!q){
        return;
    }
    while(q != p.head){
        if (!flag && (q->coef > 0)) printf("+");    //�ڷǵ�һ�����ϵ��ǰ���+��
        flag = 0;                                   //flag��Ϊ0,��ʾ���ǵ�һ��
        if(q->coef == 0){                           //��ǰ��ϵ��Ϊ0
            return;
        }
        printf("%d",q->coef);                       
        switch(q->exp){                             //�жϵ�ǰ��ָ��
            case 0:break;                          
            case 1:printf("X");break;               
            default:printf("X^%d",q->exp);break;   
        }
        q = q->link;
    }
}
//����ʽ�����,�������qx��
void Add(polynominal *px,polynominal *qx){
    PNode *q,*q1 = qx->head,*p, *p1,*temp;    //q1ָ��qx�ı�ͷ���
    p = px->head->link;                       //pָ�����ʽpx�ĵ�һ�����
    p1 = px->head;
    q = q1->link;                             
    while(p->exp >= 0){
        while(p->exp < q->exp){               
            q1 = q;
            q = q->link;
        }
        if(p->exp == q->exp){                
            q->coef = q->coef + p->coef;
            if(q->coef == 0){                 
                q1->link = q->link;           
                free(q);                      
                q = q1->link;                
                p = p->link;
            } 
            else{                             //����Ӻ�ϵ����Ϊ0
                q1 = q;                       //q1����
                q = q->link;
                p = p->link;                  //pҲ����
            }
        }
        else{                                 
            temp = (PNode*)malloc(sizeof(PNode));     
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
   }
   
}
//����ʽ�˷� 
void Multiply(polynominal *px,polynominal *qx)
{  polynominal result;//�Ƚ���result����Ϊ�˷�����Ĵ��λ�� 
   PNode* headnode=(PNode*)malloc(sizeof(PNode)); //��ʼ��result����ʽ 
   PNode* firstnode=(PNode*)malloc(sizeof(PNode));
   headnode->exp=-1;
   headnode->link=firstnode;
   result.head=headnode;
   firstnode->coef=0;
   firstnode->exp=0;
   firstnode->link=headnode;
 int rcoef,rexp;
 PNode *p1=px->head->link;//pxͷ�ڵ� 
 PNode *p2=qx->head->link;//qxͷ�ڵ� 
 
 while(p1->exp >=0)//��ʼ���� 
 {int coef1=p1->coef;
  int exp1=p1->exp;
      while(p2->exp >=0)
      { int coef2=p2->coef;
        int exp2=p2->exp;
        rcoef=coef1*coef2;
        rexp=exp1+exp2;
        polynominal temppoly;//���ÿ��С����˵ļ����� 
        PNode *temphead = (PNode*)malloc(sizeof(PNode));
        temphead->exp=-1;
        temppoly.head=temphead;
        PNode *temp = (PNode*)malloc(sizeof(PNode));
		temp->coef=rcoef;
        temp->exp=rexp;
        temp->link=temphead;
        temphead->link=temp;
		Add(&temppoly,&result);//ÿ��С����˵ļ����� �ӵ�result�� 
		p2=p2->link;
		}
	p2=qx->head->link;//��ʼ��p2ָ��λ��	
	p1=p1->link;	
	}
    Output(result); //��ӡ�˷����     
}
int main(){
    polynominal p,q;
    int x;
    printf("�����һ������ʽ:\n");
    Create(&p);
    printf("\n����ڶ�������ʽ:\n");
    Create(&q);
    printf("\n��һ������ʽΪ:\n");
    Output(p);
    printf("\n�ڶ�������ʽΪ:\n");
    Output(q);
    printf("\n");
    printf("\n���Ϊ:\n");
    Multiply(&p,&q);
    printf("\n���Ϊ:\n");
    Add(&p,&q);
    Output(q);    
    return 0;
}
