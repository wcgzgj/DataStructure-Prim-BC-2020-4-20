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
	int index;//��¼�ı��˾���ĵ���±�
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
	// Qualifier: ����С���������ɺ󣬷���һ��װ��ǰ�����Ӳ���Ľṹ������
	//************************************
	primResult *prim();


	primResult *getOrigin(std::string fname, int &len);


	//************************************
	// Method:    getGraph
	// FullName:  Graph::getGraph
	// Access:    public 
	// Returns:   int **
	// Qualifier: ���ڽ���������ͼ��Ļ���
	//************************************
	int **getGraph();


	//************************************
	// Method:    getSize
	// FullName:  Graph::getSize
	// Access:    public 
	// Returns:   int
	// Qualifier: ��ö���ĸ���������ͼ�Ļ���
	//************************************
	int getSize();

	void resetVisit();
	int DFSTranverse();


	//************************************
	// Method:    doTest
	// FullName:  Graph::doTest
	// Access:    public 
	// Returns:   void
	// Qualifier: ��������6����������
	//************************************
	void doTest();


	//************************************
	// Method:    doUserTest
	// FullName:  Graph::doUserTest
	// Access:    public 
	// Returns:   void
	// Qualifier: ��Ӧ�û��Ĳ���
	//************************************
	void doUserTest();


	//************************************
	// Method:    inputNewData
	// FullName:  Graph::inputNewData
	// Access:    public 
	// Returns:   void
	// Qualifier: �û������µ����ݽ���ʹ�ã�����洢�û�֮ǰ���������
	//************************************
	void inputNewData();


	//************************************
	// Method:    useOldData
	// FullName:  Graph::useOldData
	// Access:    public 
	// Returns:   void
	// Qualifier: ʹ��֮ǰ�û����������
	//************************************
	void useOldData();

private:
	void DFS(int v);

};

