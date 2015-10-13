/*!
	<PRE>
	SOURCE FILE : Bares.h
	DESCRIPTION.: Bares class - with implementation.
	AUTHORS.....: Igor A. Brandão and Leandro F. Silva
	CONTRIBUTORS: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: SEPT/2005
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	LAST UPDATE.: October 6th, 2015.
	LAST UPDATE.: October 6th, 2015.
	</pre>
*/

#ifndef Bares_H_
#define Bares_H_

#include <iostream>
#include <string>
//#include "Stack.h"
#include <stack>
#include <vector>
#include <fstream> // ifstream
#include <queue>
#include <stdexcept>

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// string infix2Postfix( _exp )				--> Convert infix to postfix expressions
// int hasPriority( _exp1, _exp2 )			--> Check wich operator has a higher precedence
// int isRightAssociative( _operator )		--> Check whether an operator is right associative
// int getOperatorPrecedence( _operator )	--> Get the operator precedence
// bool isOperator( _char )					--> Check whether a character is operator symbol
// bool isOperand( _char )					--> Check whether a character is alphanumeric chanaracter
// int performOperation( _operator, _operand1, _operand2 )	--> Perform an operation 
// int parsePostfix( _exp )					--> Parse the postfix expression and return the output

// ***********************ERRORS****************************
// std::underflow_error thrown if needed.

/*! LifeScreen template class */
class Bares
{
	/*!
     * Public section
    */
	public:

		/*! Functions */
        Bares();   			/*!< Constructor */
        ~Bares();  			/*!< Destructor */

		/*! Basic members */
		string infix2Postfix( const string _exp );
		int hasPriority( const char _exp1, const char _exp2 );
		int isRightAssociative( const char _operator );
		int getOperatorPrecedence( const char _operator );

		bool isOperator( const char _char );
		bool isOperator( const string _str );
		bool isOperand( const char _char );
		bool isOperand( const string _str );

		int performOperation( const char _operator, const int _operand1, const int _operand2 );
		int parsePostfix( const string _exp );
		void loadFile( const string _filename );
		vector<string> readExpressions( const string _filename );
		queue<string> transformaEmVetor( const string _exp );
		int calculatesExpression( queue<string> _fila );

	/*!
     * Private section
    */
	private:

		/*! Attributes */
		string expression;	/*!< Expression to be evaluated */
		char operators[8] = { '+', '-', '/', '*', '^', '%' };

		/*! Disable copy constructor */
		Bares( const Bares & ){ /* empty */ }
};

#endif

/* --------------------- [ End of the Bares.h header ] ------------------- */
/* ========================================================================= */