#ifndef LIST_H
#define LIST_H
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include "Node.h"
#include <time.h>

using std::ifstream;
using std::ofstream;
using std::cin;

class List
{
private:
	Node *pHead;
	void trashList(Node *pMem);
public:
	List(void);
	List(List &copyMe);
	List & operator = (List &rhs);
	~List(void);
	void insertAtFront(Node *pNode);
	void printAllInfo();//for testing purposes
	void importList(string fileName);
	void markAbsences();
	bool isEmpty();
	void store();
	void loadFromTextFile(string fileName);
	void genReportAll(string fileName);
	void genReportThreshold(string fileName);
	void genReportDate(string fileName);
	void trashList();
};

#endif