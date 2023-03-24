#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <algorithm>
#include<queue> 
using namespace std;

int isBST=1;//�Ƿ�ΪBST 
int node_arr[100]={0};//���нڵ�������� 
int node_num=0;//���нڵ������
 
typedef struct BinaryTreeNode{
    int value;                                //�������ڵ��ֵ 
    struct BinaryTreeNode *LChild, *RChild;   //��������ǰ�ڵ�����Һ��� 
}BinaryTreeNode;
 
 
//�������
void PreOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    printf("%d ",t->value);           //��ӡ�������㣬�˴����Զ�����������
    PreOrderTransverse(t->LChild);  //Ȼ���������������
    PreOrderTransverse(t->RChild);  //����������������
}
//�������
void InOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    InOrderTransverse(t->LChild);  //�������������������
    printf("%d ",t->value);          //��ӡ�������㣬�˴����Զ�����������
    InOrderTransverse(t->RChild);  //����������������������
}
//�������
void PostOrderTransverse(BinaryTreeNode *t){
    if(t==NULL){
        return;
    }
    PostOrderTransverse(t->LChild);  //�������������������
    PostOrderTransverse(t->RChild);  //Ȼ��������������������
    printf("%d ",t->value);            //����ӡ�������㣬�˴����Զ�����������
}
void Transverse(BinaryTreeNode *t) //���ֱ��� 
{   printf("\n�������:\n");
	PreOrderTransverse(t);
    printf("\n�������:\n");
    InOrderTransverse(t);
    printf("\n�������:\n");
    PostOrderTransverse(t);
    printf("\n");
    printf("\n");
}

BinaryTreeNode *PreCreateBt_IsBST(BinaryTreeNode *t,int parent_value,int flag){
    int ch;
    //scanf("%d",&ch);
    cin>>ch;
    getchar();
    if(ch == -1)//����Ϊ-1��ʾ���ｨ���ն��������������㷨�Ŀղ���
	{                           
        t = NULL;
    }
    else{
        t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
        t->value = ch;                        //��������
        
        node_arr[node_num++]=ch;//���´����ڵ��ֵ����ڵ�����
		 
        if(flag==2)//��ǰ�����Ľڵ��Ǹ��ڵ� 
        {
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //����������
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //����������
		}
		if(flag==0)//��ǰ�����Ľڵ������ӽڵ�
        {   
            if(t->value > parent_value)// ��ǰ�����Ľڵ��ֵ�����丸�ڵ� 
            { 
			   isBST=0; //�����Ƕ��������� 
			}
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //����������
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //����������
		}
		if(flag==1)//��ǰ�����Ľڵ������ӽڵ�
        {   
            if(t->value < parent_value)// ��ǰ�����Ľڵ��ֵС���丸�ڵ� 
            { 
			  isBST=0; //�����Ƕ��������� 
			}
        	t->LChild = PreCreateBt_IsBST(t->LChild,t->value,0);  //����������
            t->RChild = PreCreateBt_IsBST(t->RChild,t->value,1);  //����������
		}   
    }
    return t;
}


int Balanced_height(BinaryTreeNode* root) {//�����rootΪ���ڵ�Ķ�����ƽ�⣬������rootΪ�������ĸ߶ȣ�ֻ��һ�����ڵ�������߶�1�������򷵻�-1 
    if (root == NULL) {
        return 0;
    }
    int leftHeight = Balanced_height(root->LChild);//�����������߶� 
    int rightHeight = Balanced_height(root->RChild);//�����������߶� 
    //������ú����������Լʱ�� 
    if (leftHeight == -1 || rightHeight == -1 || fabs(leftHeight - rightHeight) > 1) 
	{//leftHeight, rightHeight=-1���� root�������Ѿ���ƽ�� ����ʱ�ͰѲ�ƽ����Ϣ������ȥ 
        return -1; //����-1�Ȱ���������������ƽ���������ְ�������������Ϊ�߶Ȳ��ȵ��µ�ǰ�ڵ㲻ƽ������ 
    } 
	else {
        return fmax(leftHeight, rightHeight) + 1;
    }
}
bool isBalanced(BinaryTreeNode* root) {//�ж϶������Ƿ�ƽ�� 
    return Balanced_height(root) >= 0;
}


BinaryTreeNode* sortedArrayToAVL_helper(int* nums, int left, int right) {//��nums�����[left��right����]�ؽ���AVL
    if (left > right) {
        return NULL;
    }
    
    int mid = (left + right) / 2;// ����ѡ���м�λ����ߵ�������Ϊ���ڵ�

    BinaryTreeNode* root = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    root->value = nums[mid];
    root->LChild = sortedArrayToAVL_helper(nums, left, mid - 1);
    root->RChild = sortedArrayToAVL_helper(nums, mid + 1, right);
    return root;
}
BinaryTreeNode* sortedArrayToAVL(int* nums, int numsSize) {
    return sortedArrayToAVL_helper(nums, 0, numsSize - 1);
}

//��������ĸ߶�
int Depth(BinaryTreeNode *t){
    if(!t) return 0;
    // else return (1 + Depth(t->LChild) > Depth(t->RChild) ? Depth(t->LChild) : Depth(t->RChild));
    else return 1 + max(Depth(t->LChild) , Depth(t->RChild));
}

void Print_Tree(BinaryTreeNode *t)//���ӻ���ӡ�������ṹ 
{

    if(t==NULL) return; 
    
	queue<BinaryTreeNode*> q_node;//��Žڵ��ָ��
	queue<int> q_value;//��Žڵ��ֵ 
	 
    q_node.push(t);
    q_value.push(t->value);//�����Ȳ�����ڵ� 
    int depth=1;//��������ǰ��ȣ����ڵ����Ϊ1
	int real_depth=Depth(t);//��������ʵ��� 
    int cnt=1;//����ڵ������ 
    
    while(!q_node.empty()&&depth<=real_depth)//Ҫ���㵱ǰ�����˵Ķ��������С�ڵ���ʵ����� 
    {   
	   if(cnt>pow(2,depth)-1)//������������£��ڵ���=2^���� -1 
        {
		  depth++;   //���ڵ�Ϊ��һ�� �����ϸ������ 
		}
		
        if(q_node.front()->LChild!=NULL)//�����ǰ�ڵ�����ӷǿգ������������ 
        {
              q_node.push(q_node.front()->LChild);
              q_value.push(q_node.front()->LChild->value);//���ӵ�ֵ 
              cnt++; //�����˵Ľڵ���+1 
        }
        else//�����ǰ�ڵ������Ϊ�� ������һ���սڵ㣨value=0��������� 
        {
         BinaryTreeNode* t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));//����ս��
         t->value = -1;                        
         t->LChild=NULL;
         t->RChild=NULL;
         q_node.push(t);
         q_value.push(t->value);
         cnt++;
		}
		
		
        if(q_node.front()->RChild!=NULL)
        {
              q_node.push(q_node.front()->RChild);
              q_value.push(q_node.front()->RChild->value);
              cnt++; 
        }
        else//�����ǰ�ڵ���Һ���Ϊ�� ������һ���սڵ㣨value=0��������� 
        {
         BinaryTreeNode* t = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode)); //����ս��
         t->value = -1;                       
         t->LChild=NULL;
         t->RChild=NULL;
         q_node.push(t);
         q_value.push(t->value);
         cnt++;
		}
         
         q_node.pop();//��ǰ�ڵ㴦���꣬������ 
    
	}
	
    for (int i = 1; i <= real_depth; i++) 
	{
        int layer_node_num = pow(2,i-1);//��i���м����ڵ� 
        int layer_margin_num = pow(2,real_depth-i)-1;//��i��ÿ���ڵ������м����ո� 
        for (int j = 1; j <=layer_node_num; j++)//��һ���м����ո� 
         {
            for(int k=1;k<=layer_margin_num;k++)
            {
			  cout<<' ';
			  cout<<' ';
			}
		
			cout<<q_value.front();
			for(int k=1;k<=layer_margin_num;k++)
            {
			  cout<<' ';
			  cout<<' ';
			}
			
			cout<<' ';
			cout<<' ';
			
            q_value.pop();
         }
        printf("\n");
    }
    
}

int main(){
	cout<<"����������������пսڵ���-1��ʾ��ÿ���ڵ�֮���пո�" <<endl; 
    BinaryTreeNode *t = NULL;            
    t =PreCreateBt_IsBST(t,100,2);   //�ڶ����������⣬������������100 
    
	cout<<endl;
	Print_Tree(t) ;//���ӻ� 
	Transverse(t); //��ӡ���ֱ��� 
      
    if(isBST&&isBalanced(t))
    {cout<<"������AVL��"<<endl; 
	}
	
	if (isBST==0||isBalanced(t)==0)
	{   cout<< endl<<"------------------------------------"<<endl<<endl;
	    cout<< "��������AVL����ԭ��";
		if(isBST==0) 
		{ cout<<"���Ƕ���������;"; 
		}
		if(isBalanced(t)==0) 
		{ cout<<"������ƽ��Ҫ��;"<<endl; 
		}
     cout<<endl; 
	 cout<<endl<<"���潫�����ؽ���AVL��"<<endl;
	 sort(node_arr,node_arr+node_num);//�ڵ��������� 
	 t=sortedArrayToAVL(node_arr,node_num);//������õĽڵ������ؽ��ɶ��������� 
	 
	 cout<<endl;
	 Print_Tree(t); //���ӻ� 
	 Transverse(t); //��ӡ���ֱ���
	}
	cout<<endl;
    system("pause");
    
	return 0;
}
