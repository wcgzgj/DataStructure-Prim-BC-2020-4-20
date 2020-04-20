#pragma once
#include <string>
class GraphMenu
{
public:
	GraphMenu(void);
	~GraphMenu(void);
	void printMenu(std::string fname);
	int getAnswer();
	void helpBook();
	void pleaseInput();
	void printEndl(int n);
	void printBlock(int n);
	void remainTime(int t,std::string fname);
};

