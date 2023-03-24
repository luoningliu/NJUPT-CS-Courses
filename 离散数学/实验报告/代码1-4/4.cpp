#include <iostream>
#include <stack>
#include<cstring> 

#define INF 100000

using namespace std;

int G[100][100];
int m;int n;//mΪ����,nΪ������

int path[50], k = 0;  //��¼ŷ��·��·��
int visitEdge[100][100];
bool visted[50];  //��ǵ��Ƿ񱻷���
int begin1;  //���Ƿ�Ϊ��ͨͼ�����������

stack<int> s;//fluery

int fa[INF]={0};//���鼯

void allDfs(int x,int edgeNumber=0)//dfs���ȫ��ŷ��· 
{if(edgeNumber==0){k=0;} //ÿ�δ�һ���µ���㿪ʼʱ����ʼ�� 
   path[k++]=x;
  if (edgeNumber==m)
  {
    for(int i=0;i<m+1;i++)
    {cout<<path[i]<<" ";
	}
	cout<<endl;
	return;
  }
  else 
  {for(int i=0;i<n;i++)
  {
   if(G[x][i])
  
     { G[x][i]--;G[i][x]--;
       
      allDfs(i,edgeNumber+1);
      G[x][i]++;G[i][x]++;
       k--;
      }
  }
  }
}

void DFS(int x)
{   
    visted[x] = true;
    for(int i = 0; i < n; i++)
        if(!visted[i] && G[x][i])
            DFS(i);
}   
 
//�����趨�����������ȱ���ͼ������һ����û�����ʣ���Ϊ����ͨͼ
bool Judge()//dfs�ж�ͼ��ͨ��
{
    DFS(0);
    for(int i = 0; i < n; i++)
        if(!visted[i])
            return false;
    return true;
}

void init()//���鼯��ʼ����ÿ��������Ϊһ������
{
    for (int i = 0; i < n; ++i)
        fa[i] = i;
}

int find(int x)//Ѱ��x������
{    

    if(fa[x]==x) return fa[x];
    else 
	{fa[x]=find(fa[x]);//·��ѹ��
	  return fa[x];}
		
}
int unionn(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx==fy) return 0;
    fa[fx]=fy;
    return 1;
}

void dfsfleury(int x)
{
    s.push(x);

    for(int i = 0; i < n; i++)
    {
        if(G[i][x] > 0)
        {
            G[x][i] --;
            G[i][x] --;
            dfsfleury(i);
            break;
        }
    }
}

void fleury(int x)
{
    int b;
    s.push(x);

    while(!s.empty())
    {
        b = 0;
        for(int i =0 ; i < n; i++)
        {
            if(G[s.top()][i] > 0)
            {
                b = 1;
                break;
            }
        }
        if(b == 0)//ջ��Ԫ��û�б���i���� �����䶥Ԫ�س�ջ 
        {
            cout << s.top() << " ";
            s.pop();
        }
        else//ջ��Ԫ����i���������Ը�Ԫ��Ϊ��㣬����һ��·��ֱ����·����·����ջ��·���ϵ����б�ɾ�� 
        {
            int t = s.top();
            s.pop();
            dfsfleury(t);
        }
    }
}

int main()
{   int num = 0;//����������
    int start[50]= {0};int j=0;//ŷ��·��ʼ��� ������ָ��j 
    cout<<"����������ͱ���"<<endl;
    
    while(cin >> n >> m,n)
    {   
		int l=0;//������ͨ���ж� 
        while(!s.empty())//��ʼ��ջs
            s.pop();
        memset(G,0,sizeof(G));
		init();//��ʼ�����鼯
		k=0;j=0;num = 0;//��ʼ��k ,j,num
		cout<<"��������ߣ�����Ŵ�0��ʼ��"<<endl;
        for(int i = 0; i < m; i++)
        {
            int a,b;

            cin >> a >> b;
            G[a][b] ++;
            G[b][a] ++;
			l+=unionn(a,b); 
        }
     if(l!=n-1)//���һ��ͼ����ͨͼ�����������С�������ı���Ϊ����-1 ��n-1 
	{cout << "Non-connected graph" << endl;
	 cout<<"����������ͱ���"<<endl;
       continue; 
	 } 
	  /*if(!Judge())// dfs�ж���ͨ�� 
    {
        cout << "Non-connected graph" << endl;
		cout<<"����������ͱ���"<<endl;
         continue;   
    }*/
        
        for(int i = 0; i <= n-1; i++)
        {
            int d = 0;//ÿ�������
            for(int j = 0; j <= n-1; j++)
                d += G[i][j];
            if(d % 2 == 1)//�������Ϊ����
            {   num++;
                if(num>2){break;}
                start[j++] = i;
               
            }
        }
		
        if(num == 0 || num == 2)
            {
		     if(num == 0)
			 {cout << "ŷ����·��" << endl;
			 for(int i=0;i<n;i++)
			   {allDfs(i,0);
			   //fleury(i);
			   }
			}
			  else 
			 {cout << "ŷ��·�ǣ��޻�·��" << endl;
			   for(int i=0;i<2;i++)
			   {allDfs(start[i],0);
			   //fleury(start[i]);
			   }
			   }
			 
			  
		     
			 cout<<endl;}
        else
            cout << "No Euler path" << endl;

		cout<<"����������ͱ���"<<endl;
    }
    return 0;
}