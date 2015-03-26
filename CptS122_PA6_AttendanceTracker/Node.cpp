#include "Node.h"


Node::Node(void)
{
	this->recordNum = 0;
	this->idNum = 0;
	this->numAbsences = 0;
	//TODO: Dates of absence initialization.
	this->datesOfAbsence[0] = "";
	this->name = "";
	this->email = "";
	this->units = "";
	this->major = "";
	this->level = "";
	this->pNext = NULL;
}

Node::Node(int recordNum, int idNum, string name, string email,
		string units, string major, string level)
{
	this->recordNum = recordNum;
	this->idNum = idNum;
	this->numAbsences = 0;
	//TODO: Dates of absence initialization.
	this->datesOfAbsence[0] = "";
	this->name = name;
	this->email = email;
	this->units = units;
	this->major = major;
	this->level = level;
	this->pNext = NULL;
}


Node::Node(Node &copyMe)
{
	this->recordNum = copyMe.recordNum;
	this->idNum = copyMe.idNum;
	this->numAbsences = copyMe.numAbsences;
	//TODO: copy dates of absence to destination...
	for (int i = 0; i < 20 && copyMe.datesOfAbsence[i].empty(); i++)
	{
		this->datesOfAbsence[i] = copyMe.datesOfAbsence[i];
	}
	this->name = copyMe.name;
	this->email = copyMe.email;
	this->units = copyMe.units;
	this->major = copyMe.major;
	this->level = copyMe.level;
	this->pNext = copyMe.pNext;
}

Node & Node::operator = (Node &rhs)
{
	this->recordNum = rhs.recordNum;
	this->idNum = rhs.idNum;
	this->numAbsences = rhs.numAbsences;
	//TODO: copy dates of absence to destination...
	for (int i = 0; i < 20 && rhs.datesOfAbsence[i].empty(); i++)
	{
		this->datesOfAbsence[i] = rhs.datesOfAbsence[i];
	}
	this->name = rhs.name;
	this->email = rhs.email;
	this->units = rhs.units;
	this->major = rhs.major;
	this->level = rhs.level;
	this->pNext = rhs.pNext;

	return *this;
}


Node::~Node(void)
{
}

void Node::print()
{
	int i = 0;
	cout << this->recordNum << endl;
	cout << this->idNum << endl;
	cout << this->numAbsences << endl;
	cout << "Dates of absence:" << endl;
	for (i = 0; i < 20 && this->datesOfAbsence[i] != ""; i++)
	{
		cout << '\t' << this->datesOfAbsence[i] << endl;
	}
	if (i == 0)
		cout << "\tNone." << endl;
	cout << this->name << endl;
	cout << this->email << endl;
	cout << this->units << endl;
	cout << this->major << endl;
	cout << this->level << endl;

}
