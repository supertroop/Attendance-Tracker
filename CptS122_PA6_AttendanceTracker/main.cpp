//Nick Anderssohn
//PA6
#include "Menu.h"

int main (void)
{
	Menu *mainMenu = new Menu(); //needs to be dynamically allocated pointer otherwise there is an error when exiting the application

	mainMenu->runMenu();
	return 0;
}
