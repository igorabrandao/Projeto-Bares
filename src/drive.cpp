/*! \file */ 
/*! \brief Class main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bares.h"

using namespace std;

//#define DEBUG

int main(int argc, char const *argv[])
{
	/*! Create an instance from Bares class */
	Bares obj;

	/*! If the user has passed the input file as a parameter */
	if ( argc == 2 )
	{
		vector<string> myExpressions; 	/*!< Vector that stores all the expressions*/
		string filename = argv[ 1 ]; 	/*!< Gets its name from the input file*/

		myExpressions = obj.readExpressions( filename );

		string postfix;

		#ifdef DEBUG

			// DEGUG
			cout << "printing input file "<< endl;

			/*! Print the vector */
			for ( size_t i(0); i < myExpressions.size(); ++i )
			{
				cout << myExpressions[i] << endl;
			}

			cout << "####End of input file" << endl;

		#endif

		for ( size_t i(0); i < myExpressions.size(); ++i )
		{
			cout << "-------------------------------------------------------" << endl;
			cout << ">>> Expression: " << obj.trim(myExpressions[i]) << endl;

			/*! Se não tiver erros de sintaxe */
			if ( !obj.hasSyntaxError( obj.stringToQueue( myExpressions[ i ] ) ) )
			{
				int result = obj.calculatesExpression( obj.infixToPostfix( myExpressions[i]) );
				cout << ">>> Result: " << result << endl;
			}
			cout << "-------------------------------------------------------" << endl << endl;
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

		/*! Se não tiver erros de sintaxe */
		if ( !obj.hasSyntaxError( obj.stringToQueue( expression ) ) )
		{
			cout << "-------------------------------------------------------" << endl;
			int result = obj.calculatesExpression( obj.infixToPostfix( expression )  );
			cout << ">>> Result: " << result << endl;
			cout << "-------------------------------------------------------" << endl << endl;
		}
	}

	/*! Main return */
	return 0;
}