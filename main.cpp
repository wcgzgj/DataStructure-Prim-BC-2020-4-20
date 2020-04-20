#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include "Graph.h"
#include "Draw.h"
#include "GraphMenu.h"
using namespace std;

int main()
{
	GraphMenu gm;

	Graph gh;//<<======��case 2:��ʹ��,switch���޷�����ʵ����
	int flag=1;
	while(flag)
	{
		system("cls");
		gm.printMenu("�˵�\\���˵�.txt");
		gm.pleaseInput();
		int answer=gm.getAnswer(); 

		switch (answer)
		{
		case 1:
			while (1)
			{
				system("cls");
				gm.printMenu("�˵�\\������Ϣ.txt");
				int infoFlag;
				gm.pleaseInput();
				cin>>infoFlag;
				if(infoFlag==0) break;
			}
			break;
		case 2:
			system("cls");
			gh.doTest();
			break;	
		case 3:
			system("cls");
			gh.doUserTest();//<=============�Ͳ����һ����
			break;
		case 4:
			system("cls");
			gm.helpBook();
			break;
		case 5:
			system("cls");
			gm.printMenu("�˵�\\�ټ�.txt");
			Sleep(1000);
			return 0;
		default:
			system("cls");
			gm.printMenu("�˵�\\�������.txt");
			gm.remainTime(3,"�˵�\\�������.txt");
			break;
		}
	}
	system("pause");
	return 0;
}