#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <winnt.h>
#include <imagehlp.h>
#pragma comment(lib,"IMAGEHLP")

using namespace std;

PIMAGE_DOS_HEADER pDH = NULL;
PIMAGE_NT_HEADERS pNtH = NULL;
PIMAGE_FILE_HEADER pFH = NULL;
PIMAGE_OPTIONAL_HEADER pOH= NULL;
PIMAGE_SECTION_HEADER pSH = NULL;
PIMAGE_IMPORT_DESCRIPTOR pIMT = NULL;
LPVOID  imageBase = NULL;

//E://Hill.exe
//�����ļ�
BOOL loadPE(LPSTR fileName)
{
    HANDLE hFile;
    HANDLE hMapping;

    //���ļ������ؾ��
    hFile=CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (!hFile)
    {
        cout << "�ļ����ش���..." << endl;
        return FALSE;
    }
    //�����ڴ�ӳ����󣬽�PE�ļ�װ�ص��ڴ�
    hMapping = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,GetFileSize(hFile,NULL),NULL);
    if(!hMapping)
    {
        cout << "�ļ����ش���..." << endl;
        CloseHandle(hFile);
        return FALSE;
    }
    imageBase = MapViewOfFile(hMapping,FILE_MAP_READ,0,0,0);
    if(!imageBase)
    {
        CloseHandle(hMapping);
        CloseHandle(hFile);
        cout << "�ļ����ش���..." << endl;
        return FALSE;
    }
    //printf("ImageBase : %x\n",imageBase);
    return TRUE;
}

//�ж��Ƿ�PE�ļ�
BOOL isPE()
{
    pDH=(PIMAGE_DOS_HEADER)imageBase;
    pNtH=(PIMAGE_NT_HEADERS32)((DWORD)pDH+pDH->e_lfanew);//pNtH PE�ļ�ͷ��־

    //�ж��ļ���һ���ֶ��Ƿ���MZ����5A4D
    printf("e_magic : %x\n",pDH->e_magic);
    if(pDH->e_magic!=IMAGE_DOS_SIGNATURE)
    {
        cout << "��ʽ������ѡ��PE��ʽ���ļ�..." << endl;
        return FALSE;
    }
    //��ʹ��MZ��Ϊ��ֹ���жϣ��Ƚ�Signature��IMAGE_NT_SIGNATURE��Ӧ�������Ϊ4550
    printf("Signature : %x\n",pNtH->Signature);
    printf("IMAGE_NT_SIGNATURE : %x\n",IMAGE_NT_SIGNATURE);
    if (pNtH->Signature != IMAGE_NT_SIGNATURE)
    {
        cout << "��ʽ������ѡ��PE��ʽ���ļ�..." << endl;
        return FALSE;
    }
    cout << "��ȷ��PE�ļ���ʽ��ȷ..." << endl;

    return TRUE;
}

//��IMAGE_FILE_HEADER�ṹ��������
void getFileHeader()
{
    pFH=&(pNtH->FileHeader);
    printf("����CPU���� : ");
    if(pFH->Machine == 0x014c)
        printf("Intel i386");
    else if(pFH->Machine == 0x0162)
        printf("MIPS R3000");
    else if(pFH->Machine == 0x0166)
        printf("MIPS R4000");
    else if(pFH->Machine == 0x0184)
        printf("Alpha AXP");
    else printf("Power PC");
    printf("( %x )\n",pFH->Machine);
    printf("����ʱ�� : ");
    //printf(ctime((time_t*)&pFH->TimeDateStamp));
    printf("(%x)\n",(time_t*)&pFH->TimeDateStamp);

    printf("���� : ");
    if(pFH->Characteristics == 0x010f)
        printf("��ͨEXE�ļ�");
    if(pFH->Characteristics == 0x0210)
        printf("DLL�ļ�");
	else printf("����");
    printf("( %x )\n",pFH->Characteristics);

    //�ж��ļ�32λ����64��size�������ļ�����
    printf("����(32 or 64) : ");
    if(pFH->SizeOfOptionalHeader == 0x00E0)
        printf("32λ");
    if(pFH->SizeOfOptionalHeader == 0x00F0)
        printf("64λ");
    printf("( %x )\n",pFH->SizeOfOptionalHeader);

    printf("Section��Ŀ : %x\n", pFH->NumberOfSections);
    //�Ƿ����COFF���ű�ƫ��λ��
	printf("�Ƿ����COFF���ű� : ");
	if(pFH->PointerToSymbolTable == 0)
        printf("COFF������");
    else
        printf("COFF����");
    printf("( %x )\n",pFH->PointerToSymbolTable);
	printf("���ű��С : %x\n", pFH->NumberOfSymbols);
}

//��IMAGE_OPTIONAL_HEADER�ṹ��������
void getOptionalHeader()
{
    pOH = &(pNtH ->OptionalHeader);
    //
    printf("ROM or EXECUTABLE : ");
    if(pOH->Magic == 0x0107)
        printf("ROM");
    if(pOH->Magic == 0x010B)
        printf("EXECUTABLE");
	if(pOH->Magic == 0x020b)
        printf("PE32+");
    printf("( %x )\n",pOH->Magic);
    printf("�û��������� ��");
    if(pOH->Subsystem == 0)printf("δ֪\n");
    if(pOH->Subsystem == 1)printf("����Ҫ��ϵͳ��������������\n");
    if(pOH->Subsystem == 2)printf("GUIͼ�ν���\n");
    if(pOH->Subsystem == 3)printf("CUI�����н���\n");
    if(pOH->Subsystem == 5)printf("OS/2�ַ���ϵͳ\n");
    if(pOH->Subsystem == 7)printf("POSIX�ַ���ϵͳ\n");
    if(pOH->Subsystem == 8)printf("����\n");
    if(pOH->Subsystem == 9)printf("WINDOWS CE����\n");

    printf("���ӳ������汾�� : %x\n",pOH->MajorLinkerVersion);
    //�ѳ�ʼ�����ݿ��С������ʱ�����ɵĿ�Ĵ�С������������Σ�
    printf("�ѳ�ʼ�����ݿ��С : %x\n",pOH->SizeOfInitializedData);
    //δ��ʼ�����ݿ飬��������ʱû��ָ��ֵ
    printf("δ��ʼ�����ݿ� : %x\n",pOH->SizeOfUninitializedData);
    printf("ӳ��У��� ��%x\n",pOH->CheckSum);

    printf("ӳ��װ���ڴ���ܳߴ� : %x\n",pOH->SizeOfImage);
    printf("MSͷ��PEͷ��SECTION���С �� %x\n",pOH->SizeOfHeaders);
    printf(".text��С : %x\n",pOH->SizeOfCode);

    printf("�������ʼRVA : %x\n",pOH->BaseOfCode);
    printf("���ݶ���ʼRVA : %x\n",pOH->BaseOfData);
    //����ִ�����RVA��ָ������ʱ����룬������ָ��main
    printf("����ִ�����RVA : %x\n",pOH->AddressOfEntryPoint);
    printf("��ַ : %x\n\n",pOH->ImageBase);
    //װ���ڴ����������С,����Ӵ���������ʼ
    printf("װ���ڴ����������С �� %x\n",pOH->FileAlignment);
    printf("��������������С�� %x\n",pOH->SectionAlignment);
    printf("һ��ʼ��ί�ɸ���ջ���ڴ��С : %x\n",pOH->SizeOfStackCommit);
    printf("һ��ʼ��ί�ɸ��ѵ��ڴ��С : %x\n",pOH->SizeOfHeapCommit);
    printf("Ϊ�̶߳�ջ������ : %x\n",pOH->SizeOfHeapReserve);
    printf("Ϊ�̶߳ѱ����� : %x\n",pOH->SizeOfHeapReserve);
}

//������Ŀ¼��
void getDataDirectory()
{
    for(int i = 0;i < 16;i++)//����Ŀ¼��16�����
    {
        char* item = "";
        if(pOH->DataDirectory[i].VirtualAddress == 0&&pOH->DataDirectory[i].Size == 0)
            continue;
        if(i == 0)item = "Export Table";
        if(i == 1)item = "Import Table";
        if(i == 2)item = "Resource Table";
        if(i == 3)item = "Exception Table";
        if(i == 4)item = "Security Table";
        if(i == 5)item = "Base Relocation";
        if(i == 6)item = "Debug Table";
        if(i == 7)item = "Copy Right";
        if(i == 8)item = "Global ptr";
        if(i == 9)item = "TLS";
        if(i == 10)item = "Load configuration";
        if(i == 11)item = "Bound Import";
        if(i == 12)item = "Import Address Table";
        if(i == 13)item = "Delay Import";
        if(i == 14)item = "COM Descriptor";
        if(i == 15)item = "����";

        printf("%s(����Ŀ¼���%d��)\n",item,i+1);
        printf("VirtualAddress��%x\n",pOH->DataDirectory[i].VirtualAddress);
        printf("Size��%x\n",pOH->DataDirectory[i].Size);
    }
}

//��������Ϣ
void getSectionTable()
{
    pSH = IMAGE_FIRST_SECTION(pNtH);
    for(int i = 0;i < pFH->NumberOfSections;i++)
    {
        printf("%s ",pSH->Name);
		//Characteristics��ͨ�����õ�����λ��ɵ�֪�Ƿ��������
        if(IMAGE_SCN_CNT_CODE&pSH->Characteristics)cout<<"������ִ�д���,";
		if(IMAGE_SCN_MEM_EXECUTE&pSH->Characteristics)cout<<"��ִ��,";
		if(IMAGE_SCN_CNT_INITIALIZED_DATA&pSH->Characteristics)cout<<"�����ѳ�ʼ������,";
		if(IMAGE_SCN_CNT_UNINITIALIZED_DATA&pSH->Characteristics)cout<<"����δ��ʼ������,";
		if(IMAGE_SCN_MEM_DISCARDABLE&pSH->Characteristics)cout<<"�ɱ�����,";
		if(IMAGE_SCN_MEM_SHARED&pSH->Characteristics)cout<<"�����,";
		if(IMAGE_SCN_MEM_READ&pSH->Characteristics)cout<<"�ɶ�,";
        if(IMAGE_SCN_MEM_WRITE&pSH->Characteristics)cout<<"��д,";
		printf("(%x)\n",pSH->Characteristics);
		//����SIZEû������
		printf("�ÿ�װ�ص��ڴ��е�RVA %x\n",pSH->VirtualAddress);
        printf("�ÿ��ڴ����д�С %x\n",pSH->SizeOfRawData);
        printf("�ÿ��ڴ�����ƫ�� %x\n",pSH->PointerToRawData);
        ++pSH;
    }
}
//������չPEͷ��DataDirectory����Ŀ¼����ʵ��ַ
LPVOID getDirectoryEntryToData(USHORT DirectoryEntry)
{

	LPVOID pDirData=NULL;
	DWORD dwDataStartRVA = 0;

	//����Ŀ¼��1�ǵ��룬ָ��IID��0�ǵ�����ָ��IED
    dwDataStartRVA=pOH->DataDirectory[DirectoryEntry].VirtualAddress;
	//printf("%x %x\n",imageBase,dwDataStartRVA);
    if(!dwDataStartRVA)
        return NULL;
	//��֪RVA���õ�VA
	pDirData = ImageRvaToVa(pNtH,imageBase,dwDataStartRVA,NULL);//pNtH=(PIMAGE_NT_HEADERS32)((DWORD)pDH+pDH->e_lfanew);
    if(!pDirData)
		return NULL;
   	return  pDirData;
}

//��DLL��Ӧ���뺯��
void getImportFuction(int index)
{
    DWORD dwThunk,*pdwThunk=NULL,*pdwRVA=NULL;
	PIMAGE_IMPORT_DESCRIPTOR pIFT = NULL;
	PIMAGE_IMPORT_BY_NAME pIBN = NULL;
	//��ǰIID����
    pIFT=&pIMT[index];
	//ָ��INT����������ڣ���ôָ��IAT
    dwThunk=((DWORD)((PIMAGE_IMPORT_DESCRIPTOR)pIMT->OriginalFirstThunk?                      \
         (PIMAGE_IMPORT_DESCRIPTOR)pIMT->OriginalFirstThunk:(PIMAGE_IMPORT_DESCRIPTOR)pIMT->FirstThunk \
          ));

	//RVA
	pdwRVA=(DWORD *)dwThunk;
	//VA
	pdwThunk=(DWORD*)ImageRvaToVa(pNtH,imageBase,dwThunk,NULL);
   	if(!pdwThunk)
		    return;
    while(*pdwThunk)
    {
		printf("%x ",(DWORD)pdwRVA);
		printf("%x ", (DWORD)(*pdwThunk));
		//�����λΪ1����������ŷ�ʽ����
		if (HIWORD(*pdwThunk) == 0x8000)
		{
			printf("%x ",IMAGE_ORDINAL32(*pdwThunk));
		}
		//�����ַ����������룬��ʱ��ָ��IMAGE_IMPORT_BY_NAME��RVA
		else
		{
			pIBN =(PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(pNtH,imageBase,(DWORD)(*pdwThunk),NULL);
			if(pIBN)
			{
				//������������פ��DLL�е���ţ����ܱ���0
				printf("%x ",pIBN->Hint);
				string temp = (char*)pIBN->Name;
				printf("%s\n",temp.c_str());
			}
			else
			{
				printf("%x ",(DWORD)(*pdwThunk));
			}
		}
		++pdwRVA;
		++pdwThunk;
	}
	cout << "--------------------------------" << endl;
}

//������DLL
void getImportTable()
{
    int i = 0;
	//�õ�IID���飨����DLL�ļ�����VA
    pIMT = (PIMAGE_IMPORT_DESCRIPTOR)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IMPORT);
	if(!pIMT)
	{
		printf("�����Ϊ��\n");
	}
	else
	{
		while(pIMT->FirstThunk)//û�������ֶΣ������һ����ԪΪNULL
		{
			//NAME��DLL���ֵ�ָ��
			printf("%s %x\n",ImageRvaToVa(pNtH,imageBase,pIMT->Name,NULL),pIMT->Name);
			cout << "------------getImportFuction--------------------" << endl;
			//�õ���DLL���뺯��
			getImportFuction(i);
			//ָ����һ��DLL
			++pIMT;
			i++;
		}
	}
}

//����������
void getExportTable()
{
	PDWORD pdwRva, pdwName;
	PWORD pMap;
	string funcName;
	PIMAGE_EXPORT_DIRECTORY pEXT = NULL;
	//�õ�IED
	pEXT = (PIMAGE_EXPORT_DIRECTORY)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXPORT);

	if(!pEXT)
	{
		printf("������Ϊ��\n");
	}
	else
	{
		//EAT������
		pdwRva = (PDWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfFunctions,NULL);
		//ENT���Ʊ�
		pdwName = (PDWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfNames,NULL);
		//��Ӧ��ű�
		pMap = (PWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfNameOrdinals,NULL);
		printf("��%d��������\n",pEXT->NumberOfFunctions);

		if(!pdwRva)
			return;
		//ѭ������������ַ
		for(int i = 0;i < pEXT->NumberOfFunctions;i++)
		{
			for(int j = 0;j < pEXT->NumberOfNames;j++)
			{
				if(i == pMap[j])
				{
					//���Ʊ����ű��Ƕ�Ӧ��
					funcName = (char*)ImageRvaToVa(pNtH,imageBase,pdwName[j],NULL);
					break;
				}
			}
			//��ַ��ȷ��Ӧ����
			printf("%x ", pEXT->Base+i);
			printf("%x ", (*pdwRva));
			printf("%s\n",funcName.c_str());
			++pdwRva;
		}
	}
}

void getResource()
{
    PIMAGE_RESOURCE_DIRECTORY pRD = NULL;
    pRD = (PIMAGE_RESOURCE_DIRECTORY)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_RESOURCE);
    if(!pRD)
	{
		printf("��ԴΪ��\n");
		return;
	}
    printf("�û��Զ�����Դ�� %x\n������Դ������Ի���%x \n",pRD->NumberOfIdEntries,pRD->NumberOfNamedEntries);
}



int main()
{
	char fileName[30];
	cout << "\n������exe�ļ��ľ���·�� : ";
	cin.getline(fileName,50);
    cout << "\n���������Ϊ : "<< fileName << endl;

	//�����ļ�
    int a = loadPE(fileName);
    if(!a)
        return 1;
    cout << "�ļ� " << fileName << " ��ȡ�ɹ�...\n" << endl;
    cout << "--------------------------------" << endl;

   

    //�Ƿ�PE�����ļ�
    int flag = isPE();
    if(!flag)
    {
        return 1;
    }
   
	
	cout << fileName <<"�������������PE�ļ�ͷ(IMAGE_FILE_HEADER��IMAGE_OPTIONAL_HEADER������Ŀ¼��)��" <<
		"������Ϣ�Լ����뵼������Ϣ\n" << endl;

    //��IMAGE_FILE_HEADER�ṹ��������
    cout << "-------IMAGE_FILE_HEADER--------" << endl;
    getFileHeader();
    cout << "" << endl;

    //��IMAGE_OPTIONAL_HEADER�ṹ��������
    cout << "-------IMAGE_OPTIONAL_HEADER--------" << endl;
    getOptionalHeader();
    cout << "" << endl;

    //������Ŀ¼��
    cout << "DATA_DIRECTORY����0�" << endl;
    getDataDirectory();
    cout << "" << endl;

    //���������Ϣ
    cout << "-------IMAGE_SECTION_HEADER---------" << endl;
    getSectionTable();
    cout << "" << endl;

    //����Դ
    cout << "--------------RESOURCE--------------" << endl;
    getResource();
    cout << "" << endl;

    //�������
    cout << "------------IMPORT_TABLE------------" << endl;
    getImportTable();
    cout << "" << endl;

	//��������
    cout << "------------EXPORT_TABLE------------" << endl;
    getExportTable();
    cout << "------------------------------------\n" << endl;

	//�������
	freopen( "CON", "w", stdout ); //�ض������������̨
	cout << ""<<fileName<<"�������..." << endl;
	system("pause"); 
    return 0;
}