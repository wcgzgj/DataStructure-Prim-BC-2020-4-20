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
	for(int i=0;i<graphSize;i++) visit[i]=false;//初始化访问数组
	for(int i=0;i<graphSize;i++) vex[i]=i;//获得顶点数组
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
	primResult *pr=new primResult[graphSize-1];//存放最后获得的最小生成树的路径,路径个数比点数少1
	whoChange *dis=new whoChange[graphSize];//存放一点到其它所有点的权值
	for(int i=0;i<graphSize;i++) 
	{
		dis[i].dis=graph[0][i]; 
		dis[i].index=0;//获取0号顶点到所有顶点的权值
	}
	visit[0]=true;//0号顶点率先访问
	int count=1;//0号顶点已经记录在内了

	while(count<graphSize)//路径条数要比顶点个数少一个
	{
		int min=infienty;
		int j=0;
		for(int i=0;i<graphSize;i++)//找出最小
		{
			if(visit[i]==false && dis[i].dis<min)
			{
				min=dis[i].dis;
				j=i;
			}
		}
		pr[count-1].start=dis[j].index;//起始为最小权值边的起始点
		pr[count-1].end=j;//终止为最小权值边的终点
		pr[count-1].weight=dis[j].dis;//<======存放路径的权值，便于后面画图
		visit[j]=true;//又一个点被访问
		count++;
		for(int i=0;i<graphSize;i++)
		{
			if(visit[i]==false && graph[j][i]<dis[i].dis) 
			{
				dis[i].dis=graph[j][i]; 
				dis[i].index=j;//更改者是i
			}
		}

	}
	return pr;
}

primResult * Graph::getOrigin(std::string fname, int &len)
{
	std::ifstream fin(fname);
	int n;//这里的n没用，是为了消掉第一行的点个数数据
	fin>>n;
	primResult *origin=new primResult[graphSize*(graphSize-1)/2];//<====撑死了就这么多边
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
	len=n;//获得长度
	return origin;//获得原始点、边集合
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
	resetVisit();//不reset的话prim算法用同一个visit会出错
	return len;
}

void Graph::doTest()
{
	for(int i=1;i<=6;i++)
	{
		Graph gh;

		char tmp[10];
		sprintf(tmp,"%d",i);
		std::string str(tmp,tmp+strlen(tmp));//为了获得每次的文件名

		std::string name="测试数据\\"+str+".txt";
		std::string num="菜单\\"+str+".txt";


		gh.iniGraph(name);
		int len=0;
		primResult *origin=gh.getOrigin(name,len);//<=====用来获得取最小生成树之前的图

		GraphMenu gm;
		Draw dw;
		system("cls");
		gm.printEndl(10);
		gm.printMenu(num);
		Sleep(900);

		system("cls");
		gm.printEndl(10);
		gm.printBlock(20);
		std::cout<<"生成最小生成树之前的路径为"<<std::endl;
		Sleep(1000);
		system("cls");
		dw.iniPanel();
		dw.drawCircle(gh);
		dw.drawInstant(origin,gh.getSize(), len);
		Sleep(2000);
		dw.clearPanel();
		dw.closePanel();

	
		primResult *pr=gh.prim();//用来画最小生成树
		gh.resetVisit();
		int k=gh.DFSTranverse();
		//std::cout<<k<<std::endl;
		if(k!=1)
		{
			system("cls");
			gm.printMenu("错误提醒\\非连通图.txt");
			gm.remainTime(3,"错误提醒\\非连通图.txt");
			system("cls");
			continue;
		}//<===============判断是不是连通图

		gm.printEndl(10);
		gm.printBlock(20);
		std::cout<<"生成的最小生成树为"<<std::endl;
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
		gm.printMenu("菜单\\选择.txt");
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
			case 3://返回主选单<==============================================补完就好了
				flag=0;
				break;
			default:
				gm.remainTime(3,"错误提醒\\输入错误.txt");
			}
			break;
		}
	}
	return;

}

void Graph::inputNewData()
{
	std::ifstream finTimes("用户操作\\数据\\操作次数.txt");
	//std::ofstream foutTimes("用户操作\\数据\\操作次数.txt");

	int opTime;
	int n;//用户输的操作个数
	int flag=0;
	int edgeN=0;

	finTimes>>opTime;//读取之前的操作次数<=======================================后面要加1的，还有再更新操作次数的文件
	finTimes.close();

	system("cls");
	GraphMenu gm;

	gm.printEndl(10);
	gm.printBlock(10);
	std::cout<<"请输入顶点的个数：";
	std::cin>>n;

	gm.printEndl(10);
	gm.printBlock(10);
	std::cout<<"请输入边的个数：";
	std::cin>>edgeN;

	opTime+=1;
	char tmp[10];
	sprintf(tmp,"%d",opTime);
	std::string str(tmp,tmp+strlen(tmp));//为了获得每次的文件名

	std::string name="用户操作\\数据\\"+str+".txt";
	std::ofstream foutData(name);
	foutData<<n<<"\n";//在数据文件中输入数据的个数

	while(flag<edgeN)
	{
		system("cls");
		//gm.printMenu("用户操作\\菜单\\输入数据.txt");
		gm.printEndl(10);
		gm.printBlock(10);
		std::cout<<"请输入第"<<flag+1<<"个数据";
		gm.printBlock(10);
		std::cout<<"请按照 起始点 终止点 权值 的格式进行输入"<<std::endl;
		gm.printEndl(1);
		std::cout<<"请输入数据：";

		int s,e,weight;
		std::cin>>s>>e>>weight;
		if(s>=n || e>=n)//点的标号不许比点的个数大，不然无法进行prim
		{
			system("cls");
			gm.remainTime(2,"菜单\\输入错误.txt");
			continue;
		}
		flag++;
		foutData<<s<<" "<<e<<" "<<weight<<"\n";
	}
	foutData.close();

	std::ofstream foutTimes("用户操作\\数据\\操作次数.txt");
	foutTimes<<opTime;//更新操作次数
	foutTimes.close();




	//std::string num="菜单\\"+str+".txt";
	Graph gh;
	gh.iniGraph(name);
	int len=0;
	primResult *origin=gh.getOrigin(name,len);//<=====用来获得取最小生成树之前的图

	//GraphMenu gm;
	Draw dw;
	
	system("cls");
	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"生成最小生成树之前的路径为"<<std::endl;
	Sleep(1000);
	system("cls");
	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawInstant(origin,gh.getSize(), len);
	Sleep(2000);
	dw.clearPanel();
	dw.closePanel();


	primResult *pr=gh.prim();//用来画最小生成树
	gh.resetVisit();
	int k=gh.DFSTranverse();
	//std::cout<<k<<std::endl;
	if(k!=1)
	{
		system("cls");
		gm.printMenu("错误提醒\\非连通图返回菜单.txt");
		gm.remainTime(3,"错误提醒\\非连通图返回菜单.txt");
		system("cls");
		return;
	}//<===============判断是不是连通图

	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"生成的最小生成树为"<<std::endl;
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
	std::ifstream finNum("用户操作\\数据\\操作次数.txt");
	int num;
	finNum>>num;//获得曾经的文件个数
	finNum.close();
	GraphMenu gm;
	int answer;
	while(1)
	{
		system("cls");
		gm.printEndl(10);
		gm.printBlock(10);
		std::cout<<"一共有"<<num<<"文件可以选择";
		gm.printEndl(3);
		std::cout<<"请输入想要选择第几个文件：";
		answer=gm.getAnswer();
		if(answer>num)
		{
			system("cls");
			gm.remainTime(3,"菜单\\输入错误.txt");
		}
		else break;
	}

	char tmp[10];
	sprintf(tmp,"%d",answer);
	std::string str(tmp,tmp+strlen(tmp));//为了获得每次的文件名

	std::string name="用户操作\\数据\\"+str+".txt";
	Graph gh;
	gh.iniGraph(name);
	int len=0;
	primResult *origin=gh.getOrigin(name,len);//<=====用来获得取最小生成树之前的图

	//GraphMenu gm;
	Draw dw;

	system("cls");
	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"生成最小生成树之前的路径为"<<std::endl;
	Sleep(1000);
	system("cls");
	dw.iniPanel();
	dw.drawCircle(gh);
	dw.drawInstant(origin,gh.getSize(), len);
	Sleep(2000);
	dw.clearPanel();
	dw.closePanel();


	primResult *pr=gh.prim();//用来画最小生成树
	gh.resetVisit();
	int k=gh.DFSTranverse();
	//std::cout<<k<<std::endl;
	if(k!=1)
	{
		system("cls");
		gm.printMenu("错误提醒\\非连通图返回菜单.txt");
		gm.remainTime(3,"错误提醒\\非连通图返回菜单.txt");
		system("cls");
		return;
	}//<===============判断是不是连通图

	gm.printEndl(10);
	gm.printBlock(20);
	std::cout<<"生成的最小生成树为"<<std::endl;
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
