#include "List.h"

List::List(void)
{
	this->pHead = NULL;
}

List::List(List &copyMe)
{
	this->pHead = copyMe.pHead;
}

List & List::operator = (List &rhs)
{
	this->pHead = rhs.pHead;
	return *this;
}

List::~List(void)
{
	delete [] this->pHead;
}

void List::insertAtFront(Node *pNode)
{
	Node *pCur = this->pHead;
	if (pHead == NULL)
		pHead = pNode;
	else//list not empty
	{
		pNode->pNext = pHead;
		pHead = pNode;
	}
}

void List::printAllInfo()
{
	Node *pCur = this->pHead;
	//loop through and print each node
	while (pCur != NULL)
	{
		pCur->print();
		cout << endl;
		pCur = pCur->pNext;
	}
}

//this must be a new, empty list before calling this fun.
void List::importList(string fileName)
{
	ifstream input;
	int recordNum = 0, idNum = 0;
	string name = "", email = "", units = "", major = "", level = "";
	input.open(fileName);
	char buffer[100];

	this->trashList(this->pHead);//in case user imports multiple times
	this->pHead = NULL;

	input.getline(buffer, 100, '\n');//skip first line
	while (!input.eof())
	{
		//recordNum,ID,Name,Email,Units,Program,Level
		input.getline(buffer, 100, ','); //reads til ','
		if (strcmp(buffer, "") != 0)
		{
			recordNum = atoi(buffer); //converts to int
			input.getline(buffer, 100, ',');
			idNum = atoi(buffer);
			input.getline(buffer, 100, '\"');//read first quotation
			input.getline(buffer, 100, '\"');
			name = buffer;
			input.getline(buffer, 100, ',');//read next comma
			input.getline(buffer, 100, ',');
			email = buffer;
			input.getline(buffer, 100, ',');
			units = buffer;
			input.getline(buffer, 100, ',');
			major = buffer;
			input.getline(buffer, 100, '\n');
			level = buffer;
			Node *pMem = new Node(recordNum, idNum, name, email,
				units, major, level);
			this->insertAtFront(pMem);
		}
	}
	input.close();

}

void List::markAbsences()
{
	Node *pMem = this->pHead;
	time_t t = time(0);
	struct tm *now = localtime(&t);//current date and time
	char answer = '\0';
	string date = std::to_string(now->tm_year + 1900) + "-" + std::to_string(now->tm_mon + 1) + "-"
		+ std::to_string(now->tm_mday);

	while (pMem != NULL && answer != 'y' && answer != 'n')
	{
		cout << "Is " << pMem->name << " absent? (y/n):" << endl;
		cin >> answer;
		if (answer == 'y')
		{
			pMem->datesOfAbsence[pMem->numAbsences++] = date;
			cout << "Student marked absent." << endl;
			system("pause");
		}
		if (answer != 'y' && answer !='n')
		{
			cout << "Invalid response. Enter y for yes or n for no." << endl;
			system("pause");
		}
		else
		{	
			pMem = pMem->pNext;
		}
		system("cls");
		answer = '\0';
	}
	cout << "Attendance poll complete." << endl;

}

void List::store()
{

	ofstream output;
	output.open("masterSave.txt");

	Node *pCur = this->pHead;
	while (pCur != NULL)
	{
		output << pCur->recordNum << '\n';
		output << pCur->idNum << '\n';
		output << pCur->numAbsences << '\n';
		for (int i = 0; i < pCur->numAbsences; i++)
		{
			output << pCur->datesOfAbsence[i] << '\n';
		}
		output << pCur->name << '\n';
		output << pCur->email << '\n';
		output << pCur->units << '\n';
		output << pCur->major << '\n';
		output << pCur->level << '\n';
		pCur = pCur->pNext;
	}

}

void List::loadFromTextFile(string fileName)
{
	//each item is separated by a newline char
	//use numAbsences to determine how many lines to read for dates

	ifstream input;
	input.open(fileName);

	char temp[100];

	this->trashList(this->pHead); //in case user imports or loads multiple times
	this->pHead = NULL;

	while (!input.eof())
	{
		Node *pMem = new Node();

		input.getline(temp, 100);
		if (strcmp(temp, "") != 0)
		{
			pMem->recordNum = atoi(temp);
			input.getline(temp, 100);
			pMem->idNum = atoi(temp);
			input.getline(temp, 100);
			pMem->numAbsences = atoi(temp);
			for (int i = 0; i < pMem->numAbsences; i++)
			{
				input.getline(temp, 100);
				pMem->datesOfAbsence[i] = temp;
			}
			input.getline(temp, 100);
			pMem->name = temp;
			input.getline(temp, 100);
			pMem->email = temp;
			input.getline(temp, 100);
			pMem->units = temp;
			input.getline(temp, 100);
			pMem->major = temp;
			input.getline(temp, 100);
			pMem->level = temp;

			this->insertAtFront(pMem);
		}
	}
	input.close();
}

//reports include name, email, and absences info
void List::genReportAll(string fileName)
{
	ofstream output;
	output.open(fileName);

	Node *pCur = this->pHead;
	while (pCur != NULL)
	{
		output << "Name: " << pCur->name << endl;
		output << "Email: " << pCur->email << endl;
		output << "Number of absences: " << pCur->numAbsences << endl;
		output << "Dates of absence:" << endl;
		if (pCur->numAbsences == 0)
			output << "\tNone." << endl;
		else
			for (int i = 0; i < pCur->numAbsences; i++)
			{
				output << '\t' << pCur->datesOfAbsence[i] << endl;	
			}
		pCur = pCur->pNext;
	}
	output.close();
	cout << "Report generated in " << fileName << endl;
}

void List::genReportThreshold(string fileName)
{
	ofstream output;
	output.open(fileName);

	int threshold = 0;
	cout << "Generate report for students who have more than x absences." << endl;
	cout << "x = ";
	cin >> threshold;

	Node *pCur = this->pHead;
	while (pCur != NULL)
	{
		if (pCur->numAbsences > threshold)
		{
			output << "Name: " << pCur->name << endl;
			output << "Email: " << pCur->email << endl;
			output << "Number of absences: " << pCur->numAbsences << endl;
			output << "Dates of absence:" << endl;
			if (pCur->numAbsences == 0)
				output << "\tNone." << endl;
			else
				for (int i = 0; i < pCur->numAbsences; i++)
				{
					output << '\t' << pCur->datesOfAbsence[i] << endl;	
				}
		}
		pCur = pCur->pNext;
	}
	output.close();
	cout << "Report generated in " << fileName << endl;
}

void List::genReportDate(string fileName)
{
	string day, month, year;
	ofstream output;
	output.open(fileName);

	cout << "Generate report for certain date:" << endl;
	cout << "Month (1-12): ";
	cin >> month;
	cout << "Day: ";
	cin >> day;
	cout << "Year: ";
	cin >> year;
	string date = year + "-" + month + "-" + day;

	Node *pCur = this->pHead;
	bool dateFound = false;
	while (pCur != NULL)
	{
		for (int i = 0; i < pCur->numAbsences; i++)
		{
			if (pCur->datesOfAbsence[i] == date)
				dateFound = true;
		}
		if (dateFound)
		{
			output << "Name: " << pCur->name << endl;
			output << "Email: " << pCur->email << endl;
			output << "Number of absences: " << pCur->numAbsences << endl;
			output << "Dates of absence:" << endl;
			if (pCur->numAbsences == 0)
				output << "\tNone." << endl;	
			else
				for (int i = 0; i < pCur->numAbsences; i++)
				{
					output << '\t' << pCur->datesOfAbsence[i] << endl;	
				}
		}
		dateFound = false;
		pCur = pCur->pNext;
	}
	output.close();
	cout << "Report generated in " << fileName << endl;
}

//emptys the list...deletes everything inside
//be sure to set pHead to NULL after using this function
void List::trashList(Node *pMem)
{
	if (pMem != NULL)//in case list is empty
	{
		if (pMem->pNext != NULL)
			this->trashList(pMem->pNext);

			delete pMem;
	}
}

void List::trashList()
{
	this->trashList(this->pHead);
}



bool List::isEmpty()
{
	return this->pHead == NULL;
}

