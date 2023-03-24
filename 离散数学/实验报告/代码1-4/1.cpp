#include <iostream>
#include <string>
#include<cstring>
#include <set>
#include <map>
using namespace std;
 
string org;       //ԭʽ�����潫�����ɺ�׺���ʽ 
string pcnf;    //����ȡ��ʽ
string pdnf;    //����ȡ��ʽ

int a, b, res;  //a��b�����ջ������Ԫ�ص�ֵ��res���������

int choose;
 
class SeqStack 
{
public:
    SeqStack(int mSize);
    ~SeqStack();
    bool Push(char x);  
    bool Pop(); 
    char Top(); 
private:
    int top;
    char *st;
    int maxtop;
};
 
SeqStack::SeqStack(int mSize)
{
    maxtop = mSize - 1;
    st = new char[mSize];
    top = -1;
}
 
SeqStack::~SeqStack()
{
    delete[]st;
}
 
bool SeqStack::Push(char x) 
{
    if(top == maxtop)
        return false;
    st[++top] = x;
    return true;
}
 
bool SeqStack::Pop()     
{
    if(top == -1)
        return false;
    top--;
    return true;
}
 
char SeqStack::Top()        
{
    return st[top];
}
 
void And();     //��ȡ
void Or();      //��ȡ
void Not();     //��
void If();      //����
void Iif(); //˫����
bool CanIn(char out);       //�ж��ܷ��ջ
void Suffix();              //���׺���ʽ
void Calculate();           //���㹫ʽ��ֵ
void Print();               //�����ֵ��ͷ�ʽ
void Calculate1();
 
SeqStack stack(200);        
  
map<char,int>map1; //�������Ԫ����٣� 

//dfsö��t��2^t�η��� 01��� 
void dfs(map<char,int>::iterator n)//n=begin;
{
if(n==map1.end())
{Calculate1();//���� 
return;
}
else
{
n->second=1;
n++;
dfs(n);
n--;
n->second=0;
n++;
dfs(n);
}
}




int main()
{
    cout << "! ��" << endl << "| ��ȡ" << endl <<"& ��ȡ" << endl << "-> ����" << endl << "<-> ˫����" << endl << endl;
    cout<<"����������" <<endl; 
    
    
    
   
    char str[100];//��ʼ���� 
    char ch[100];//�򻯳�ʼʽ 
    cin >> str;
    int cnt = 0;
    for(int i = 0; i < strlen(str);)
    {
        if(str[i] == '-')
        {
            ch[cnt++] = '>';
            i += 2;
        }
        else if(str[i] == '<')
        {
            ch[cnt++] = '~';
            i += 3;
        }
        else
        {
            ch[cnt++] = str[i];
            if((65<=str[i]&&str[i]<=90)||(97<=str[i]&&str[i]<=122)){map1.insert(pair<char, int>(str[i],1));}
            i++;
        
    }
}
    ch[cnt++] = '\0';
    org = ch;
    Suffix();  //ת��׺ 
    map<char,int>::iterator iter = map1.begin();
    
	for (iter = map1.begin();iter != map1.end(); iter++){
         cout << iter->first<<"\t";//��ӡ����С�����Ԫ 
    }
    cout<<str; //��ӡ����ʽ 
    cout<<endl;
    
	iter = map1.begin();
	dfs(iter) ; 
    
	
    if(pdnf.length() != 0)  
        pdnf.erase(pdnf.length() - 2); //ȥ��ʽ��ĩβ�Ķ������ӷ� 
    if(pcnf.length() != 0)  
        pcnf.erase(pcnf.length() - 2);
    
    cout << "����ȡ��ʽ��" << pdnf << endl << endl;
    cout << "����ȡ��ʽ��" << pcnf << endl << endl;
	
    return 0;
}
 








void And()      //��ȡ
{
    res = a * b;
    stack.Push(res);
}
 
void Or()       //��ȡ
{
    res = a + b;
    res = res > 1 ? 1 : res;
    stack.Push(res);
}
 
void Not()      //��
{
    a = stack.Top();
    stack.Pop();
    res = a == 1 ? 0 : 1;
    stack.Push(res);
}
 
void If()       //����,b->a
{
    res = (b == 1 && a == 0) ? 0 : 1;
    stack.Push(res);
}
 
void Iif()  //˫����
{
    res = (b == a) ? 1 : 0;
    stack.Push(res);
}
 
bool CanIn(char out)        //�ȼ������ȼ���Ȼ���ж��ܷ��ջ
{
    char in = stack.Top();  
    int i, o;   //�ֱ��ʾջ��������������ȼ�
    switch(in)
    {
        case '#':i = 0; break;
        case '(':i = 1; break;
        case '~':i = 3; break;
        case '>':i = 5; break;
        case '|':i = 7; break;
        case '&':i = 9; break;
        case '!':i = 11; break;
        case ')':i = 12; break;
    }
    switch(out)
    {
        case '#':o = 0; break;
        case '(':o = 12; break;
        case '~':o = 2; break;
        case '>':o = 4; break;
        case '|':o = 6; break;
        case '&':o = 8; break;
        case '!':o = 10; break;
        case ')':o = 1; break;
    }
 
    if(i < o)      //���ջ������ȼ���ջ�ڵĸߣ��Ϳ��Խ�ջ����Ϊ��ջ��Խ������Խ�ȳ�ջ
        return true;
    else
        return false;
}
 
void Suffix()   //ת��Ϊ��׺���ʽ
{
    string tmp = "";                //�����׺���ʽ
    stack.Push('#');                //ջ��
    for(int i = 0; (unsigned)i < org.length(); i++)
    {
        //if(org[i] == 'P' || org[i] == 'Q' || org[i] == 'R' || org[i] == 'S' || org[i] == 'T' || org[i] == 'U')      //�����P��Q��R �ͱ��浽�ַ���tmp��
        if((65<=org[i]&&org[i]<=90)||(97<=org[i]&&org[i]<=122))
        {
            tmp = tmp + org[i];
            continue;           
        }
        if(CanIn(org[i]))           
            stack.Push(org[i]);
        else if(org[i] == ')')       
        {
            while(stack.Top() != '(')
            {
                tmp = tmp + stack.Top();          
                stack.Pop();
            }
            stack.Pop();     
        }
        else                    
        {
            do
            {
                tmp = tmp + stack.Top();            
                stack.Pop();
            } while(!CanIn(org[i]));        
            stack.Push(org[i]);  
        }
    }
    while(stack.Top() != '#') 
    {
        tmp = tmp + stack.Top();   
        stack.Pop();
    }
    stack.Pop();                // '#' ��ջ
    org = tmp;                      
}

void Calculate1()
{ 

 
    for(int i = 0; (unsigned)i < org.length(); i++)//org�Ǻ�׺���ʽ 
    {if((65<=org[i]&&org[i]<=90)||(97<=org[i]&&org[i]<=122))//��׺���ʽ�����������Ԫ ����ջ��01ֵ 
            { stack.Push(map1[org[i]]);
              continue;          
            }
    	
    	 if(org[i] != '!')         // ��׺���ʽ�еĵ�Ԫ���Ӵ�!
            {
                a = stack.Top();    
                stack.Pop();       
                b = stack.Top();
                stack.Pop();
            }
            switch(org[i])//��׺���ʽ������˫Ԫ���Ӵ� ��ջ����Ԫ��ջ �������㣬����res��� 
            {
                case '~':Iif(); break;
                case '>':If(); break;
                case '|':Or(); break;
                case '&':And(); break;
                case '!':Not(); break;
            } 
	}
	map<char,int>::iterator iter = map1.begin();
	 
	if(res == 1)  //res�������������� 
	{
	pdnf = pdnf + "(";//pdnfΪ����ȡ��ʽ 
	for (iter = map1.begin();iter != map1.end(); iter++){
		string t1(1,iter->first);char t3[3]={'!',iter->first,'\0'}; string t2(t3);//��char���͵�iter->first,!iter->first���string�����۵�c++�ַ��� 
         pdnf = pdnf + (iter->second == 1? t1 : t2)  ;
         if(iter != --map1.end()){pdnf=pdnf+"&" ;}
    }
    pdnf = pdnf + ")"+" | ";
    
	}
    else
	{pcnf = pcnf + "(";//pncfΪ����ȡ��ʽ 
	
	for (iter = map1.begin();iter != map1.end(); iter++){
		string t1(1,iter->first);  char t3[3]={'!',iter->first,'\0'};   string t2(t3);//��char���͵�iter->first,!iter->first���string�����۵�c++�ַ��� 
         pcnf = pcnf + (iter->second == 0 ? t1 : t2);
         if(iter != --map1.end()){pcnf=pcnf+"|" ;}
    }
    pcnf = pcnf + ")"+" & ";
	}  
	
	for (iter = map1.begin();iter != map1.end(); iter++){//��ӡÿ����������Ԫ��01ֵ 
         cout << iter->second << "\t";
         
    }
    cout<<res<<endl;
    res=0;     //�Ǳ��� 
    }
 
