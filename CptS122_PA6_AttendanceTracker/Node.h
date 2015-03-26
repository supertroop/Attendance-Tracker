#ifndef NODE_H
#define	NODE_H
#include <iostream>
#include <string>

using std::string;
using std::endl;
using std::ostream;
using std::cout;

class List; //forward declaration

class Node
{
	friend class List;
private:
	int recordNum;
	int idNum;
	int numAbsences;
	string datesOfAbsence[20];
	string name;
	string email;
	string units;//string instead of int...needs to be able to store "AU" for audit
	string major;
	string level; //freshman, sophomore, junior, senior, graduate
	Node *pNext;

public:
	Node(void);
	Node(Node &copyMe);
	Node(int recordNum, int idNum, string name, string email,
		string units, string major, string level);
	Node & operator = (Node &rhs);
	~Node(void);

	void print();
};

#endif