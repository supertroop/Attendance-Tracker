#ifndef MENU_H
#define MENU_H
#define CSVFILE "classList.csv"

#include "List.h"
class Menu
{
private:
	List master;
	int displayMenu();//returns users selection
	void runReportMenu();
public:
	Menu(void);
	~Menu(void);

	void runMenu();
};

#endif