#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include <queue>
#include<vector>
#include<iostream>
#include<map>
#include<string> 
using namespace std;
typedef char ElementType;

typedef struct HFMTreeNode{
ElementType element;//�ַ� 
int w;  //Ȩֵ
struct HFMTreeNode * lchild, *rchild;
}HFMTreeNode; 

typedef struct HFMbinarytree //�������ṹ�壬��һ��ָ��ָ������ 
{HFMTreeNode *root;
}HFMbinarytree;

HFMTreeNode * NewNode(ElementType x,int w,HFMTreeNode * ln,HFMTreeNode *rn)//�����½ڵ� 
{HFMTreeNode *p=(HFMTreeNode *)malloc(sizeof(HFMTreeNode));
p->element=x;
p->w=w;
p->lchild=ln;
p->rchild=rn;
return p;
}

void MakeHFMTree(HFMbinarytree *bt,ElementType e,int w,HFMbinarytree *left,HFMbinarytree * right)//��bt��Ϊ�������� ��left��right�ֱ���Ϊ�������������ݵĶ��������ͣ��Խڵ�����һ�ΰ�װ 
{if(bt->root||(left==right&&left!=NULL))return;//���bt->root��Ϊnull ,ֱ�ӷ��� 
if((left==right&&left==NULL)){bt->root=NewNode(e,w,NULL,NULL);return;}//����ֻ��btһ��������������������Ϊ�գ� 
bt->root=NewNode(e,w,left->root,right->root);
left->root=right->root=NULL;
}

struct tree_compare
{
	bool operator() ( HFMbinarytree a,  HFMbinarytree b) const
	{   
	       
		return (a.root->w) > (b.root->w);	// С����
	}
};

HFMbinarytree CreateHFMTree(int w[],char c[],int m)
{priority_queue <HFMbinarytree,vector<HFMbinarytree>,struct tree_compare >q;//С����

for(int i=0;i<m;i++)
{ HFMbinarytree x;
   x.root=NULL;  
  MakeHFMTree(&x,c[i],w[i],NULL,NULL);
  q.push(x);
}

while(q.size()>1)
{HFMbinarytree z;
   z.root=NULL;//ÿ�½�һ��������Ҫ�ֶ���ʼ��������z.root��=null 
  HFMbinarytree x=q.top();
  q.pop();
 HFMbinarytree y=q.top();
 q.pop();
 if((x.root)->w < (y.root)->w)
 {MakeHFMTree(&z,'#',x.root->w+y.root->w,&x,&y); 
 }
 else
 {MakeHFMTree(&z,'#',x.root->w+y.root->w,&y,&x); 
 }
 q.push(z);
}
return q.top();
}

void InOrderTransverse(HFMTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->lchild);  //�������������������
    printf("%d ",t->w);          //��ӡ�������㣬�˴����Զ�����������
    InOrderTransverse(t->rchild);  //����������������������
}
//dfs�����������ÿ���ַ��Ĺ��������� 
void InOrderTransverse_plus(HFMTreeNode *t,string code, map<char, string> &charcode){
    if(t==NULL){
        return;
    }
    if(t->element!='#'){charcode[t->element]=code;}
    InOrderTransverse_plus(t->lchild,code.append("0"), charcode);  //�������������������
     code.erase(code.end() - 1);;//���ݣ�ɾȥcode�����һ���ַ� 
    InOrderTransverse_plus(t->rchild,code.append("1"), charcode);  //����������������������
}
//���빦�� 
char decode(HFMTreeNode *t,string &code){
	if(t->element!='#')
	{return t->element;
	}
	char ch=code.at(0);
	if(ch=='0')
	{code.erase(0,1);decode(t->lchild,code);//ɾȥ��һ���ַ� 
	}
	if(ch=='1')
	{code.erase(0,1);decode(t->rchild,code);
	}
	
}

int main()
{int W[8]={29,9,26,27,2,23,8,24};
char c[8] ={'A','B','C','D','E','F','G','H'};


HFMbinarytree hfmtree=CreateHFMTree(W,c,8); //������������ 


	
//�����ӡ���ַ����������� 
cout<<endl;
map<char, string> charcode;//<�ַ�������>
string code="";
InOrderTransverse_plus(hfmtree.root,code,charcode);
for(map<char,string>::iterator it=charcode.begin();it!=charcode.end();it++)
   {
       cout<<(it->first)<<" :"<<it->second<<endl;
        
   }
//���빦�� 
code="01011";
cout<<"01011������ַ�Ϊ" <<decode(hfmtree.root,code); 
return 0;
} 
