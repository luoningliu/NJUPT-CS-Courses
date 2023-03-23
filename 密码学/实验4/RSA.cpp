#include<cstring>
#include<iostream>
 
using namespace std;
typedef long long LL;
int p=11, q=23, e=7;
bool Is_prime(int n)//��ͨ�ж�����
{
    for(int i=1;i*i<=n;++i)
    {
        if(n%i==0) return false;
    }
    return true;
}

LL exgcd(LL a,LL b,LL &x,LL &y)//��չŷ������㷨  ax+by=gcd(a,b)  ��������ֵretΪgcd(a,b) 
 {
	   if(b==0)
    {
        x=1,y=0;
        return a;
    }
    LL ret=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return ret;
}




LL qkpow(LL a,LL p,LL mod) //��a^p %mod ˼·�ǰ�p���ɳɶ�������ʽ ��(a^b) mod c = (a mod c)^b mod c 
{
    LL ans=1,base=a%mod; 
    while(p)
    {
        if(p&1) ans=ans*base%mod;//��� p���һλ��1 
        base=(base*base)%mod; //ÿһ����λ��Ҫƽ�� 
        p>>=1;
    }
    return ans;
}

LL getInv(int a,int mod)//��a��mod�µ���Ԫ����������Ԫ����-1 
{   if(Is_prime(mod))  //���modΪ�������÷���С����+����ģָ���㷨����Ԫ 
    {return qkpow(a,mod-2,mod);
	}
    LL x,y;
    LL d=exgcd(a,mod,x,y);
    return d==1?(x%mod+mod)%mod:-1;
}
int main(){
    
    // ���� n = p��q����(n) = (p-1)��(q-1)
    // ���� d������ d*e �� 1mod ��(n) 
    // �õ�����ԿΪ {e,n}, ˽ԿΪ {d,n}    
    // ���ģ�C = M^e (mod n)
    //���ģ�M = C^d (mod n) 
    int n = p*q;
    
    int d =getInv(e,(p-1)*(q-1));
    

    
    int plaintext=30;// plaintext < n 
    cout<<"����Ϊ"<<plaintext<<endl; 
    
    int cipher=qkpow(plaintext,e,n);
    cout<<"����Ϊ"<<cipher<<endl; 
    
    
    int decode_cipher=qkpow(cipher,d,n);
    cout<<"����Ϊ"<<decode_cipher<<endl; 
    return 0;
}
