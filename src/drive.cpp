/*! \brief Class main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bares.h"

using namespace std;

int main()
{
	Bares obj;
	string expression; 
	cout << "Enter Infix Expression \n";
	getline(cin, expression);
	string postfix = obj.infix2Postfix(expression);
	cout << "Output = " << postfix << "\n";

	/*! Main return */
	return 0;
}