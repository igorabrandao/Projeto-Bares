/*! \brief Class main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bares.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*! Create an instance from Bares class */
	Bares obj;

	/*! If the user has passed the input file as a parameter */
	if( argc == 2 )
	{
		vector<string> myExpressions; 	/*!< Vector that stores all the expressions*/
		string filename = argv[ 1 ]; 	/*!< Gets its name from the input file*/

		myExpressions = obj.readExpressions( filename );

		// DEGUG
		/*! Print the vector */
		for( size_t i(0); i < myExpressions.size(); ++i )
		{
			cout << myExpressions[i] << endl;
		}
	}
	else
	{
		/*! Store the input expression */
		string expression; 

		/*! Message to user */
		cout << "Enter Infix Expression \n";

		/*! Read the input */
		getline(cin, expression);

		/*! Convert the infix exp to postfix */
		string postfix = obj.infix2Postfix(expression);

		/*! Print the result */
		cout << "Postfix = " << postfix << "\n";
		cout << "Result = " << obj.parsePostfix(postfix) << "\n";
	}
	/*! Main return */
	return 0;
}