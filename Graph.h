#pragma once
#include <string>
#define infienty 99999

struct primResult
{
	int start;
	int end;
	int weight;
	primResult(int start,int end,int weight)
	{
		this->start=start;
		this->end=end;
		this->weight=weight;
	}
	primResult()
	{}
};

struct whoChange
{
	int dis;
	int index;//记录改变了距离的点的下标
};




class Graph
{
private:
	bool *visit;
	int *vex;
	int **graph;
	int graphSize;
public:
	Graph(void);
	~Graph(void);
	void iniGraph(std::string fname);


	//************************************
	// Method:    prim
	// FullName:  Graph::prim
	// Access:    public 
	// Returns:   primResult *
	// Qualifier: 当最小生成树生成后，返回一个装有前后链接步骤的结构体数组
	//************************************
	primResult *prim();


	primResult *getOrigin(std::string fname, int &len);


	//************************************
	// Method:    getGraph
	// FullName:  Graph::getGraph
	// Access:    public 
	// Returns:   int **
	// Qualifier: 便于接下来进行图像的绘制
	//************************************
	int **getGraph();


	//************************************
	// Method:    getSize
	// FullName:  Graph::getSize
	// Access:    public 
	// Returns:   int
	// Qualifier: 获得顶点的个数，便于图的绘制
	//************************************
	int getSize();

	void resetVisit();
	int DFSTranverse();


	//************************************
	// Method:    doTest
	// FullName:  Graph::doTest
	// Access:    public 
	// Returns:   void
	// Qualifier: 运行所有6个测试数据
	//************************************
	void doTest();


	//************************************
	// Method:    doUserTest
	// FullName:  Graph::doUserTest
	// Access:    public 
	// Returns:   void
	// Qualifier: 反应用户的操作
	//************************************
	void doUserTest();


	//************************************
	// Method:    inputNewData
	// FullName:  Graph::inputNewData
	// Access:    public 
	// Returns:   void
	// Qualifier: 用户输入新的数据进行使用，并会存储用户之前输入的数据
	//************************************
	void inputNewData();


	//************************************
	// Method:    useOldData
	// FullName:  Graph::useOldData
	// Access:    public 
	// Returns:   void
	// Qualifier: 使用之前用户输入的数据
	//************************************
	void useOldData();

private:
	void DFS(int v);

};

