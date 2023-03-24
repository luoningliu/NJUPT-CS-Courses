
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
int count = 0;  //�� 0 ��ʼ����
int n;  //������
int elements[100];  //������
int matrixs[100][100] = {0};  //��ʼ��Ϊ 0 

void element()//�ֽ�n������ 
{
    cout << "���� " << n << " ������: ";
    for(int i = 1; i <= n/2; i++){ 
        if(n % i == 0){
            elements[count++] = i; 
            cout << i << ", ";
        }
    }
    elements[count] = n;  
    cout << n << endl << endl;
}



//��ס��ϵ
void cover(){
	//��ϵ�����ʼ��
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			if(elements[j] % elements[i] == 0){  //�������������ϵ������Ϊ 1
				matrixs[i][j] = 1;
			}
		}
	}
	//��ʼ�ж�
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			for(int k = 0; k < count+1; ++k){
				matrixs[k][k] = 0;  //��ȥ���Է���
				if(matrixs[i][j] && matrixs[j][k]){
					matrixs[i][k] = 0;  //��ȥ��������
				}
			}
		}
	}
	cout << "��ס��ϵ��: {";
	for(int i = 0; i < count+1; ++i){
		for(int j = 0; j < count+1; ++j){
			if(matrixs[i][j]){  //��ȥǰ��ȥ���ģ������������ס��ϵ��
				cout << " <" << elements[i] << "," << elements[j] << ">";
			}
		}
	}
	cout << " }" << endl;
}

//�����Լ��
int gcd(int x, int y){
	int m;
	//շת�����
	while(m != 0){
		m = x % y;
		x = y;
		y = m;
	}
	return x;
}

//�ж��в���
void IFcomplemented_lattice(){
    bool flag;
    int Gcd, Lcm;
    for(int i = 1; i < count-1; i++){  //�ж��в���ʱ����Ҫ�������Ԫ����СԪ 
        flag = false; // ��ʼ�� flag = false 
        for(int j = 1; j < count-1; j++){
            if(i == j)
                continue;
            Gcd = gcd(elements[i], elements[j]); // ���Լ����������½�
            Lcm = elements[i]*elements[j] / Gcd; // ��С������������С�Ͻ�
            if(Gcd == 1 && Lcm == n){ // ���ǲ�Ԫ��flag = true 
                flag = true;
                break;
            }
            if(!flag){ // ������Ԫ��û�в�Ԫ����˸����в���
                cout << "�ⲻ���в���" << endl;
                return;
            } 
        }
    }
    // ������Ԫ�ؾ��в�Ԫ����˸����в���
    cout << "�����в���" << endl;
    return;
}


int main(){
	cout << "������һ��������: ";
	cin >> n;
	cout << endl;
    element();
	cover();
	cout << endl;
	IFcomplemented_lattice();
	cout << endl;
	return 0;
}




