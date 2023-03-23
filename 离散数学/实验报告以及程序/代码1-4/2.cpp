#include <iostream>
using namespace std;

#define MAX 1000
bool flag_ref, flag_irr, flag_sym, flag_dis, flag_tra;  //�ж��Է��ԡ����Է��ԡ��Գ��ԡ����Գ��ԡ������Ե� flag
int matrix[MAX][MAX];
int n;


//�Է���
void Reflexive(){
	flag_ref = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] != 1){  //ֻҪ��һ���Խ���Ԫ��Ϊ 0����������
			flag_ref = false;
			break;
		}
	}
}


//���Է���
void Irreflexive(){
	flag_irr = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] == 1){  //ֻҪ��һ���Խ���Ԫ��Ϊ 1����������
			flag_irr = false;
			break;
		}
	}
}


//�Գ���
void Symmetrical(){
	flag_sym = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] != matrix[j][i]){  //ֻҪ��һ�ԶԳ�Ԫ�ز���ȣ���������Գ���
				flag_sym = false;
				break;
			}
		}
	}
}


//���Գ���
void Dissymmetrical(){
	flag_dis = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] == matrix[j][i]&&matrix[j][i]==1&&i!=j){  //ֻҪ��һ�ԶԳ�Ԫ������ҵ���1���������㷴�Գ���
				flag_dis = false;
				break;
			}
		}
	}
}


//������
void Transitive(){
	
	flag_tra = true;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				if(matrix[i][j] && matrix[j][k] && !matrix[i][k]){  //ǰ����Ϊ 1��������Ϊ 0
					flag_tra = false;
					break;
				}
			}
		}
	}
}


//��հ� warshall
void Closure(){
	for(int i = 0; i < n; ++i){  //��
		for(int j = 0; j < n; ++j){  //��
			if(matrix[j][i] == 1){
				for(int k = 0 ; k < n; ++k){
					matrix[j][k]=matrix[j][k]|matrix[i][k];
					 /* if(matrix[j][k] == 0 && matrix[i][k] == 0){
						matrix[j][k] = 0;
					}
					else if(matrix[j][k] == 0 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 0){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}*/
					
				}
			}
		}
	}
}
int bb1[MAX][MAX];
void zfbb( int (*a)[1000])
{    
        for(int i=0;i<n;i++)
		  {for(int j=0;j<n;j++)
		{ bb1[i][j]=a[i][j];}}
	
	for(int i=0;i<n;i++)
	{
		if(!bb1[i][i])
		{
			bb1[i][i]=1;
		}
	}
	cout<<"�Է��հ�Ϊ��"<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<bb1[i][j]<<"  ";
		cout<<endl;
	}
}

int bb2[MAX][MAX];
void dcbb( int (*a)[1000])
{   
        for(int i=0;i<n;i++)
		  {for(int j=0;j<n;j++)
		{ bb2[i][j]=a[i][j];}}
	
		for(int i=0;i<n;i++)
		  for(int j=0;j<n;j++)
			if(bb2[i][j]!=bb2[j][i])
			{
				bb2[i][j]=1;
				bb2[j][i]=1;
			}
	cout<<"�ԳƱհ�Ϊ��"<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<bb2[i][j]<<"  ";
		cout<<endl;
	}
}

int main(){

	cout << "�����뼯��Ԫ�ظ���:" << endl;
	cin >> n;
	
	cout << "�������ϵ����:" << endl;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> matrix[i][j];
		}
	}
	cout << endl;
	Reflexive();
	Irreflexive();
	Symmetrical();
	Dissymmetrical();
	Transitive();
	cout << "���ϵ�����:" << endl; 
	if(flag_ref == true){
		cout << "�Է���" << endl;
	}
	if(flag_irr == true){
		cout << "���Է���" << endl;
	}
	if(flag_sym == true){
		cout << "�Գ���" << endl;
	}
	if(flag_dis == true){
		cout << "���Գ���" << endl;
	}
	if(flag_tra == true){
		cout << "������" << endl;
	}
	cout << endl;
	zfbb(matrix);
	dcbb(matrix); 
	cout << "���ݱհ�Ϊ:" << endl;
	Closure();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
