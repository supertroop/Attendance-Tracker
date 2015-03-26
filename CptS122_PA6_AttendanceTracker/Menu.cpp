#include "Menu.h"


Menu::Menu(void)
{
	this->master = List();
}


Menu::~Menu(void)
{

}

void Menu::runMenu()
{
	int selection = 0;
	while (selection != 6)
	{
		selection = displayMenu();
		switch (selection)
		{
		case 1://import course list	
			this->master.importList(CSVFILE);
			if (!this->master.isEmpty())
				cout << "Successfully imported list." << endl;
			else
				cout << "Error. List not imported." << endl;
			break;
		case 2://load master list
			this->master.loadFromTextFile("masterSave.txt");
			cout << "Loaded from masterSave.txt" << endl;
			break;
		case 3://store master list
			this->master.store();
			cout << "Saved in masterSave.txt" << endl;
			break;
		case 4://mark absences
			this->master.markAbsences();
			break;
		case 5://generate report
			system("cls");
			runReportMenu();
			break;
		case 6://exit
			break;
		case 69://for testing purposes
			this->master.printAllInfo();
			break;
		default:
			cout << "Invalid selection. Try again." << endl;
			break;
		}
		system("pause");
		system("cls");
	}

}

int Menu::displayMenu()
{
	cout << "1. Import course list" << endl;
	cout << "2. Load master list" << endl;
	cout << "3. Store master list" << endl;
	cout << "4. Mark absences" << endl;
	cout << "5. Generate report" << endl;
	cout << "6. Exit" << endl;
	cout << "Enter the corresponding number: ";
	int selection;
	cin >> selection;
	return selection;
}
void Menu::runReportMenu()
{
	cout << "1. Generate report for all students." << endl;
	cout << "2. Generate report based off of threshold." << endl;
	cout << "3. Generate report for a specific date." << endl;
	cout << "Enter corresponding number: ";
	int selection = 0;
	cin >> selection;

	switch (selection)
	{
	case 1:
		this->master.genReportAll("report1.txt");
		break;
	case 2:
		this->master.genReportThreshold("report2.txt");
		break;
	case 3:
		this->master.genReportDate("report3.txt");
		break;
	default:
		break;
	}
}
