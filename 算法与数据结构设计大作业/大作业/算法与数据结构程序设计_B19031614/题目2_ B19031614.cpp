#include<iostream>
#include <stack>
#include <vector>
#include<queue>
using namespace std;

void print_situation(queue<int> enter,vector< stack<int> > temp, queue<int> ready,int k)//������ô�ֵ��ʽ ,��ӡ������������ 
{   
    cout<<endl; 
	cout<<"����������Ϊ�����ף���";
	while(!enter.empty())
	{
		cout<<enter.front();
		enter.pop();
	}

	for(int j=0;j<k;j++)
    {   stack<int> s=temp[j];
        cout<<endl<<j+1<<"�Ż����������Ϊ��������������"; 
        while(!s.empty())
        { 
          cout<<s.top();
          s.pop();
	    }	
	}
	cout<<endl; 
	
	cout<<"�����������Ϊ�����ף���";
	while(!ready.empty())
	{
		cout<<ready.front();
		ready.pop();
	}
	
	
	cout<<endl<<"-----------------------------------------"<<endl<<endl;
	//getchar(); 
}	
	


int solution(int *train,int num,int k)// numΪ�������� kΪ���������� 
{   vector< stack<int> > temp;//������ 
    for(int j=0;j<k;j++)
    {   stack<int> s;
    	temp.push_back(s);
	}
	queue<int>enter;//�����
	queue<int>ready;//������ 
	for(int i=0;i<num;i++)
	{
		enter.push(train[i]);//��ʼ������� 
    }
    
	int correct_id=1;//��˳����Ӧ��һ�����쳵���id 
	int min_id=100000;//���ڻ����������Сid����ʼ��Ϊ������Ÿ������ 
	int min_k_id=-1;///min_id�����Ӧ�Ļ������ţ��±��Ǵ�0��ʼ�ģ� �������ʼ��Ϊһ�������ܵ���-1 
	print_situation(enter,temp,ready,k);
	for(int i=0;i<num;i++)
	{
		int id=train[i];
		if(id==correct_id)//�����ǰ�������ÿ��Խ��ϳ����� 
		{   
		    enter.pop(); //ʻ������� 
		    ready.push(correct_id);//���³����� 
		    cout << "������������ " << id << " ������� " "���������� "  << endl;
		    print_situation(enter,temp,ready,k);
		    
			correct_id=id+1;//ֻҪ�г���������ȡ��correct_id��Ҫ���� 
			
			while(min_id==correct_id)//�������������С�ĳ���id���Խ��ϳ����� 
			{ 
			 
			 //��ջ������ 
			 temp[min_k_id].pop();//��ջ(���������) 
			 ready.push(correct_id);//���³����� 
			 cout << "������������ " << min_id << " �ӻ����� " << min_k_id << " ����������" << endl;
			 print_situation(enter,temp,ready,k);
			 
			 min_id=100000; //�ȼ��� min_idΪ������Ÿ������ 
			 for (int j = 0; j <k; j++)//�������еĻ����������³�ջ��Ļ����� 
			 {
                  if (!temp[j].empty() ) //����������Ĳ��ǿ�ջ 
				  {     
				        if(temp[j].top() < min_id)////���ջ��Ԫ�رȵ�ǰ��min_idС 
                        {
						  min_id = temp[j].top();
                          min_k_id = j;
                        }
				  }
             }
             correct_id++; //ֻҪ�г���������ȡ��correct_id��Ҫ����
			}
		}
		else//�����ǰ���᲻�����ý��ϳ���������Ҫ������ջ 
		{   int Best_id = 100000; // �����������Ų���λ����Best_id���������(��С�Ĵ���id����).��ʼֵ��Ϊ��num���� 
		    int Best_k_id = -1; //���Ų���λ�� ���ĸ��������� 
            
			for(int j=0;j<k;j++)
			{ 
			  
			  if (!temp[j].empty() ) //����������Ĳ��ǿ�ջ 
			  {
			  	if (id < temp[j].top() && temp[j].top() < Best_id) //Ҫ�ҳ��������иմ���id���Ǹ������λ�ã�Ȼ����³���������� 
				  {
                     Best_id=temp[j].top(); 
                     Best_k_id=j;
			      }
				
			  }
			  else //��������ջ 
			  {
			  	if (Best_k_id==-1)//��û�ҵ����Բ����λ�� 
			  	{
				 Best_k_id=j; 
			    }
			  }
			  
		   }
		   if(Best_id==100000&&Best_k_id==-1)
		   {
		   	 cout<<"��������������"<<endl; 
		   	 return 0;
		   }
		   else//������������ 
		   {
		     enter.pop(); //ʻ������� 
		     temp[Best_k_id].push(id);//��id������뻺��������λ�� 
		     cout << "������������ " << id << " ������� " "���������� " << Best_k_id << endl;
		     print_situation(enter,temp,ready,k);
		   
		     if(id<min_id)//��ջ����»���������С����id�Ͷ�Ӧ�Ļ������� 
		     { 
		      min_id=id;
		      min_k_id=Best_k_id;
		     }
		     
	       }
	   }
   }
   return 1; 
}

int main()
{   //int train[9]={5,8,1,7,4,2,9,6,3};
    int train[9]={3,6,9,2,4,7,1,8,5};
    int number=9;//������ 
    int k;//���������� 
    cout<<"�����뻺��������"<<endl;
    cin>>k;
    cout<<endl;
    getchar();//�Ե��س��� 
    
	if(solution(train,number,k)==1)
	{
		cout<<endl<<"���ȳɹ�"; 
	}
	else
	{
		cout<<endl<<"����ʧ��";
	}
	cout<<endl;
    system("pause");
	return 0;
}
