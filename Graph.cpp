#include "Graph.h"
#include "Draw.h"
#include "GraphMenu.h"
#include <fstream>
#include <iostream>
#include<Windows.h>
//using namespace std;

Graph::Graph(void)
{
}


Graph::~Graph(void)
{
}

void Graph::iniGraph(std::string fname)
{
	std::ifstream fin(fname);
	fin>>graphSize;
	visit=new bool[graphSize];
	vex=new int[graphSize];
	graph=new int*[graphSize];
	for(int i=0;i<graphSize;i++) graph[i]=new int[graphSize];
	for(int i=0;i<graphSize;i++) visit[i]=false;//��ʼ����������
	for(int i=0;i<graphSize;i++) vex[i]=i;//��ö�������
	for(int i=0;i<graphSize;i++)
	{
		for(int j=0;j<graphSize;j++)
		{
			if(i==j) graph[i][j]=0;
			else graph[i][j]=infienty;
		}
	}                                                                                                                                                                                                                                                                                                   
	while(fin)
	{
		int x,y,w;
		fin>>x>>y>>w;
		graph[x][y]=graph[y][x]=w;
	}
}

primResult * Graph::prim()
{
	primResult *pr=new primResult[graphSize-1];//�������õ���С��������·��,·�������ȵ�����1
	whoChange *dis=new whoChange[graphSize];//���һ�㵽�������е��Ȩֵ
	for(int i=0;i<graphSize;i++) 
	{
		dis[i].dis=graph[0][i]; 
		dis[i].index=0;//��ȡ0�Ŷ��㵽���ж����Ȩֵ
	}
	visit[0]=true;//0�Ŷ������ȷ���
	int count=1;//0�Ŷ����Ѿ���¼������

	while(count<graphSize)//·������Ҫ�ȶ��������һ��
	{
		int min=infienty;
		int j=0;
		for(int i=0;i<graphSize;i++)//�ҳ���С
		{
			if(visit[i]==false && dis[i].dis<min)
			{
				min=dis[i].dis;
				j=i;
			}
		}
		pr[count-1].start=dis[j].index;//��ʼΪ��СȨֵ�ߵ���ʼ��
		pr[count-1].end=j;//��ֹΪ��СȨֵ�ߵ��յ�
		pr[count-1].weight=dis[j].dis;//<======���·����Ȩֵ�����ں��滭ͼ
		visit[j]=true;//��һ���㱻����
		count++;
		for(int i=0;i<graphSize;i++)
		{
			if(visit[i]==false && graph[j][i]<dis[i].dis) 
			{
				dis[i].dis=graph[j][i]; 
				dis[i].index=j;//��������i
			}
		}

	}
	return pr;
}

primResult * Graph::getOrigin(std::string fname, int &len)
{
	std::ifstream fin(fname);
	int n;//�����nû�ã���Ϊ��������һ�еĵ��������
	fin>>n;
	primResult *origin=new primResult[graphSize*(graphSize-1)/2];//<====�����˾���ô���
	n=0;
	while(fin)
	{
		int x,y,w;
		fin>>x>>y>>w;
		origin[n].start=x;
		origin[n].end=y;
		origin[n].weight=w;
		n++;
	}
	len=n;//��ó���
	return origin;//���ԭʼ�㡢�߼���
}

int ** Graph::getGraph()
{
	return graph;
}

int Graph::getSize()
{
	return graphSize;
}

void Graph::resetVisit()
{
	for(int i=0;i<graphSize;i++) visit[i]=false;
	return;
}

int Graph::DFSTranverse()
{
	int len=0;
	for(int v=0;v<graphSize;v++)
	{
		if(!visit[v])
		{
			DFS(v);
			len++;
		}
	}
	resetVisit();//��reset�Ļ�prim�㷨��ͬһ��visit�����
	return len;
}

void Graph::doTest()
{
	for(int i=1;i<=6;i++)
	{
		Graph gh;

		char tmp[10];
		sprintf(tmp,"%d",i);
		std::string str(tmp,tmp+strlen(tmp));//Ϊ�˻��ÿ�ε��ļ���

		std::string name="��������\\"+str+".txt";
		std::string num="�˵�\\"+str+".txt";


		gh.iniGraph(name);
		int len=0;
		primResult *origin=gh.getOrigin(name,len);//<=====�������ȡ��С������֮ǰ��ͼ

		GraphMenu gm;
		Draw dw;
		system("cls");
		gm.printEndl(10);
		gm.printMenu(num);
		Sleep(900);

		system("cls");
		gm.printEndl(10);
		gm.printBlock(20);
		std::cout<<"������С������֮ǰ��·��Ϊ"<<std::endl;
		Sleep(1000);
		system("cls");
		dw.iniPanel();
		dw.drawCircle(gh);
		dw.drawInstant(origin,gh.getSize(), len);
		Sleep(2000);
		dw.clearPanel();
		dw.closePanel();

	
		primResult *pr=gh.prim();//��������С������
		gh.resetVisit();
		int k=gh.DFSTranverse();
		//std::cout<<k<<std::endl;
		if(k!=1)
		{
			system("cls");
			gm.printMenu("��������\\����ͨͼ.txt");
			gm.remainTime(3,"��������\\����ͨͼ.txt");
			system("cls");
			continue;
		}//<===============�ж��ǲ�����ͨͼ

		gm.printEndl(10);
		gm.printBlock(20);
		std::cout<<"���ɵ���С������Ϊ"<<std::endl;
		Sleep(1000);
		system("cls");

		dw.iniPanel();
		dw.drawCircle(gh);
		dw.drawSlow(pr,gh.getSize());

		Sleep(2000);	
		dw.closePanel();
	}
	Draw dw;
	dw.closePanel();
}

void Graph::doUserTest()
{	
	int flag=1;
	while(flag)
	{
		system("cls");
		GraphMenu gm;
		gm.printMenu("�˵�\\ѡ��.txt");
		gm.pleaseInput();

		while(1)
		{


			int answer=gm.getAnswer();
			switch(answer)
			{
			case 1:
				inputNewData();
				break;
			case 2:
				useOldData();
				break;
			case 3://������ѡ��<==============================================����ͺ���
				flag=0;
				break;
			default:
				gm.remainTime(3,"��������\\�������.txt");
			}
			break;
		}
	}
	return;

}

void Graph::inputNewData()
{
	std::ifstream finTimes("�û�����\\����\\��������.txt");
	//std::ofstream foutTimes("�û�����\\����\\��������.txt");

	int opTime;
	int n;//�û���Ĳ�������
	int flag=0;
	int edgeN=0;

	finTimes>>opTime;//��ȡ֮ǰ�Ĳ�������<=======================================����Ҫ��1�ģ������ٸ��²����������ļ�
	finTimes.close();

	system("cls");
	GraphMenu gm;

	gm.printEndl(10);
	gm.printBlock(10);
	std::cout<<"�����붥��ĸ�����";
	std::cin>>n;

	gm.printEndl(10);
	gm.printBlock(10);
	std::cout<<"������ߵĸ�����";
	std::cin>>edgeN;

	opTime+=1;
	char tmp[10];
	sprintf(tmp,"%d",opTime);
	std::string str(tmp,tmp+strlen(tmp));//Ϊ�˻��ÿ�ε��ļ���

	std::string name="�û�����\\����\\"+str+".txt";
	std::ofstream foutData(name);
	foutData<<n<<"\n";//�������ļ����������ݵĸ���

	while(flag<edgeN)
	{
		system("cls");
		//gm.printMenu("�û�����\\�˵�\\��������.txt");
		gm.printEndl(10);
		gm.printBlock(10);
		std::cout<<"�������"<<flag+1<<"������";
		gm.printBlock(10);
		std::cout<<"�밴�� ��ʼ�� ��ֹ�� Ȩֵ �ĸ�ʽ��������"<<std::endl;
		gm.printEndl(1);
		std::cout<<"���������ݣ�";

		int s,e,weight;
		std::cin>>s>>e>>weight;
		if(s>=n || e>=n)//��ı�Ų���ȵ�ĸ����󣬲�Ȼ�޷�����prim
		{
			system("cls");
			gm.remainTime(2,"�˵�\\�������.txt");
			continue;
		}
		flag++;
		foutData<<s<<" "<<e<<" "<<weight<<"\n";
	}
	foutData.close();

	std::ofstream foutTimes("�û�����\\����\\��������.txt");
	foutTimes<<opTime;//���²�������
	foutTimes.close();




	//std::string num="�˵�\\"+str+".txt";
	Graph gh;
	gh.iniGraph(name);
	int len=0;
	primResult *origin=gh.getOrigin(name,len);//<=====�������ȡ��С������֮ǰ��ͼ

	//GraphMenu gm;
	Draw dw;
	
	system("cls");
	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"������С������֮ǰ��·��Ϊ"<<std::endl;
	Sleep(1000);
	system("cls");
	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawInstant(origin,gh.getSize(), len);
	Sleep(2000);
	dw.clearPanel();
	dw.closePanel();


	primResult *pr=gh.prim();//��������С������
	gh.resetVisit();
	int k=gh.DFSTranverse();
	//std::cout<<k<<std::endl;
	if(k!=1)
	{
		system("cls");
		gm.printMenu("��������\\����ͨͼ���ز˵�.txt");
		gm.remainTime(3,"��������\\����ͨͼ���ز˵�.txt");
		system("cls");
		return;
	}//<===============�ж��ǲ�����ͨͼ

	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"���ɵ���С������Ϊ"<<std::endl;
	Sleep(1000);
	system("cls");

	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawSlow(pr,gh.getSize());

	Sleep(2000);	
	dw.closePanel();
}

void Graph::useOldData()
{
	std::ifstream finNum("�û�����\\����\\��������.txt");
	int num;
	finNum>>num;//����������ļ�����
	finNum.close();
	GraphMenu gm;
	int answer;
	while(1)
	{
		system("cls");
		gm.printEndl(10);
		gm.printBlock(10);
		std::cout<<"һ����"<<num<<"�ļ�����ѡ��";
		gm.printEndl(3);
		std::cout<<"��������Ҫѡ��ڼ����ļ���";
		answer=gm.getAnswer();
		if(answer>num)
		{
			system("cls");
			gm.remainTime(3,"�˵�\\�������.txt");
		}
		else break;
	}

	char tmp[10];
	sprintf(tmp,"%d",answer);
	std::string str(tmp,tmp+strlen(tmp));//Ϊ�˻��ÿ�ε��ļ���

	std::string name="�û�����\\����\\"+str+".txt";
	Graph gh;
	gh.iniGraph(name);
	int len=0;
	primResult *origin=gh.getOrigin(name,len);//<=====�������ȡ��С������֮ǰ��ͼ

	//GraphMenu gm;
	Draw dw;

	system("cls");
	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"������С������֮ǰ��·��Ϊ"<<std::endl;
	Sleep(1000);
	system("cls");
	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawInstant(origin,gh.getSize(), len);
	Sleep(2000);
	dw.clearPanel();
	dw.closePanel();


	primResult *pr=gh.prim();//��������С������
	gh.resetVisit();
	int k=gh.DFSTranverse();
	//std::cout<<k<<std::endl;
	if(k!=1)
	{
		system("cls");
		gm.printMenu("��������\\����ͨͼ���ز˵�.txt");
		gm.remainTime(3,"��������\\����ͨͼ���ز˵�.txt");
		system("cls");
		return;
	}//<===============�ж��ǲ�����ͨͼ

	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"���ɵ���С������Ϊ"<<std::endl;
	Sleep(1000);
	system("cls");

	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawSlow(pr,gh.getSize());

	Sleep(2000);	
	dw.closePanel();


}

void Graph::DFS(int v)
{
	//std::cout<<vex[v]<<" ";
	visit[v]=true;
	for(int i=0;i<graphSize;i++)
		if(graph[v][i]!=0 && graph[v][i]!=infienty && visit[i]==false) DFS(i);
	return;
}
