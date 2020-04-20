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

	Graph gh;//<<======给case 2:中使用,switch中无法进行实例化
	int flag=1;
	while(flag)
	{
		system("cls");
		gm.printMenu("菜单\\主菜单.txt");
		gm.pleaseInput();
		int answer=gm.getAnswer(); 

		switch (answer)
		{
		case 1:
			while (1)
			{
				system("cls");
				gm.printMenu("菜单\\个人信息.txt");
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
			gh.doUserTest();//<=============就差最后一个了
			break;
		case 4:
			system("cls");
			gm.helpBook();
			break;
		case 5:
			system("cls");
			gm.printMenu("菜单\\再见.txt");
			Sleep(1000);
			return 0;
		default:
			system("cls");
			gm.printMenu("菜单\\输入错误.txt");
			gm.remainTime(3,"菜单\\输入错误.txt");
			break;
		}
	}
	system("pause");
	return 0;
}