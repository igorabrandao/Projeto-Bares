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
	/*! Create an instance from Bares class */
	Bares obj;

	/*! Store the input expression */
	string expression; 

	/*! Message to user */
	cout << "Enter Infix Expression \n";

	/*! Read the input */
	getline(cin, expression);

	/*! Convert the infix exp to postfix */
	string postfix = obj.infix2Postfix(expression);

	/*! Print the result */
	cout << "Output = " << postfix << "\n";

	/*! Main return */
	return 0;
}