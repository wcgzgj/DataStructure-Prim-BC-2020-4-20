#include "GraphMenu.h"
#include <Windows.h>
#include <string>
#include<fstream>
#include<iostream>


GraphMenu::GraphMenu(void)
{
}


GraphMenu::~GraphMenu(void)
{
}

std::string UTF8ToGB(const char* str)//��Ϊʹ��getline��������룬����ֻ���������
{
	std::string result;
	WCHAR *strSrc;
	LPSTR szRes;

	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

void GraphMenu::printMenu(std::string fname)
{
	std::ifstream fin(fname);
	std::string lineCnt;
	while(getline(fin,lineCnt))
	{
		std::string str;
		str= UTF8ToGB(lineCnt.c_str()).c_str();
		std::cout<<str<<std::endl;
	}

}

int GraphMenu::getAnswer()
{
	int x;
	std::cin>>x;
	return x;
}

void GraphMenu::helpBook()
{
	printMenu("�˵�\\�����ֲ�.txt");
	printEndl(3);
	printBlock(20);
	std::cout<<"�밴 0 �ص����˵�"<<std::endl;
	int answer;
	while(1)
	{
		std::cin>>answer;
		if(answer==0) break;
		system("cls");
		printEndl(10);
		printBlock(20);
		std::cout<<"����������������룺�밴 0 �ص����˵�";
		pleaseInput();
	}
	return;
}

void GraphMenu::pleaseInput()
{
	printEndl(7);
	std::cout<<"��������������س���";
}

void GraphMenu::printEndl(int n)
{
	for(int i=0;i<n;i++) std::cout<<std::endl;
	return;
}

void GraphMenu::printBlock(int n)
{
	for(int i=0;i<n;i++) std::cout<<" ";
	return;
}

void GraphMenu::remainTime(int t,std::string fname)
{
	system("cls");
	for(int i=t;i>=1;i--)
	{
		printMenu(fname);
		printEndl(7);
		std::cout<<"����"<<i<<"�����������"<<std::endl;
		Sleep(1000);
		system("cls");
	}
}
