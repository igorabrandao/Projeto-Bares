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
	if( argc == 2 )
	{
		vector<string> myExpressions; 	/*!< Vector that stores all the expressions*/
		string filename = argv[ 1 ]; 	/*!< Gets its name from the input file*/

		myExpressions = obj.readExpressions( filename );

		string postfix;
		

		#ifdef DEBUG
		// DEGUG
		cout << "imprimindo arquivo de entrada "<< endl;
		/*! Print the vector */
		for( size_t i(0); i < myExpressions.size(); ++i )
		{
			cout << myExpressions[i] << endl;
		}
		cout << "####Fim do arquivo de entrada" << endl;
		#endif

		for ( size_t i(0); i < myExpressions.size(); ++i )
		{
			cout << ">>> Expressao: " << myExpressions[ i ] << endl;
			/*! Se não tiver erros de sintaxe */
			if (!obj.hasSyntaxError( obj.stringToQueue( myExpressions[ i ] ) ) )
			{
				int result = obj.calculatesExpression( obj.infixToPostfix( myExpressions[ i ] ) );
				cout << ">>> Resultado: " << result << endl;
			}
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
			int result = obj.calculatesExpression( obj.infixToPostfix( expression )  );
			cout << ">>> Resultado: " << result << endl;
		}
	}
	/*! Main return */
	return 0;
}