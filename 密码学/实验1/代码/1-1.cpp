#include<stdio.h>
#include<map>
#include<string.h>
using namespace std;
int key[100]={0};//����(143)(56),����getkey���õ�421365 
int decodekey[100]={0};//������Կ 
void getkey(char* pointerK){
	
	int* ktemp=key;
	int i;
	int t=0;
	for(i=0;i<100;i++)
		key[i]=i;
 
    
	do{
		if(*pointerK=='(')
			continue;
		else{
			t=*pointerK-'0';
			while(*(pointerK+1)!=')'){
			ktemp[*pointerK-'0']=*(pointerK+1)-'0';
			pointerK++;
			}
			ktemp[*pointerK-'0']=t;
			pointerK++;
		}
	}	while(*(++pointerK)!='\0');	
	
}


int main()
{
    char plaintext[9999]="inseveraldistributedsystemsausershouldonlybeabletoaccessdataifauserpossesacertainsetofcredentialsorattributescurrentlytheonlymethodforenforcingsuchpoliciesistoemployatrustedservertostorethedataandmediateaccesscontrolhoweverifanyserverstoringthedataiscompromisedthentheconfidentialityofthedatawillbecompromisedinthispaperwepresentasystemforrealizingcomplexaccesscontrolonencrypteddatathatwecallciphertextpolicyattributebasedencryptionbyusingourtechniquesencrypteddatacanbekeptconfidentialevenifthestorageserverisuntrustedmoreoverourmethodsaresecureagainstcollusionattacks",cipher[9999],decodetext[9999];//���ģ����ģ������Ľ��ܵõ������� 
    char K[100];//K=(143)(56)
    
    int cyclelen,len;
    //printf("��������Ҫ��������ģ�");
    //scanf("%s",plaintext);
    len=strlen(plaintext);
    
	printf("����Ϊ��\n");
    for(int i=0; i<len; i++)
        printf("%c",plaintext[i]);
	printf("\n");
 
    printf("�������ڳ��ȣ�");
    scanf("%d",&cyclelen);
    getchar();
    
    printf("\n");
    

    //����ĩβ��ȱ 
	for(int i=len; i<len+cyclelen-(len%cyclelen); i++)
        {plaintext[i]='#';
		}
	plaintext[len+cyclelen-len%cyclelen]='\0';
 
    
	printf("�������û���ʽ������(143)(56) \n");
    gets(K);//K=(143)(56)
    
	
     printf("������Կ���£�\n");
	//(143)(56),����getkey���õ�421365 
	getkey(K);
	//��ӡ������Կ 
	for(int i=1;i<=cyclelen;i++)
    {printf("%d ", key[i]) ;
	   
    }
    
    //���ܹ��� 
	int flag=1;
    for(int i=0; i<len+cyclelen-len%cyclelen; i++)//plaintext[len+cyclelen-len%cyclelen]='\0'
    {  if(flag==cyclelen+1){flag=1;}
	
        
        cipher[i]=plaintext[i-(flag-key[flag])];
        flag++;
    }
    //��ӡ���� 
    printf("\n\n");
    printf("�������£�\n");
    for(int i=0; i<len+cyclelen-len%cyclelen; i++)
        printf("%c",cipher[i]);
    printf("\n\n");
    
    
	printf("ͨ��������Կ�����������Կ��\n");
	//ͨ��������Կ�����������Կ 
    for(int i=1;i<=cyclelen;i++)
    {
	   decodekey[key[i]]=i;
    }
    //��ӡ������Կ
    for(int i=1;i<=cyclelen;i++)
    {printf("%d ", decodekey[i]) ;
	   
    }
    
    //���ܹ��� 
	flag=1;
    for(int i=0; i<len; i++)
    {  if(flag==cyclelen+1){flag=1;}
	
       
        decodetext[i]=cipher [i-(flag-decodekey[flag])];
        flag++;
    }
    //��ӡ���ܺ����� 
	printf("\n\n");
    printf("���ľ������ܽ�����£�\n");
    for(int i=0; i<len; i++)
        printf("%c",decodetext[i]);
    printf("\n");
    
    printf("����ͳ�ƣ�\n");
    map<char,int>statistics;
    for(int i=0; i<26; i++)
        statistics.insert(pair<int, int>(i+97, 0));
    for(int i=0; i<len; i++)
        {
		statistics[cipher[i]]++;
        
    }
    for(int i=0; i<26; i++)
        printf("%c��%d��",i+97,statistics[i+97]);
    return 0;
}
