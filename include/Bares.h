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
	LAST UPDATE.: October 8th, 2015.
	LAST UPDATE.: October 10th, 2015.
	</pre>
*/

#ifndef Bares_H_
#define Bares_H_

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream> /*!< ifstream */
#include <queue>
#include <stdexcept>
#include <cmath>

/*! Custom classes */
#include "Stack.h"
#include "Queue.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// string infix2Postfix( _exp )					--> Convert infix to postfix expressions
// int hasPriority( _exp1, _exp2 )				--> Check wich operator has a higher precedence
// int isRightAssociative( _operator )			--> Check whether an operator is right associative
// int getOperatorPrecedence( _operator )		--> Get the operator precedence
// bool isOperator( _char )						--> Check whether a character is operator symbol
// bool isOperand( _char )						--> Check whether a character is alphanumeric chanaracter
// int performOperation( _operator, _operand1, _operand2 )	--> Perform an operation 
// vector<string> readExpressions( _filename )	--> Read Expression from file
// queue<string> stringToQueue( _exp )			--> Convert the expression to queue
// int calculatesExpression( _fila )			--> Calculate the expression
// void printQueue( _queue )					--> Print the queue
// void hasSyntaxError( _infixQueue )			--> Check if the sintax has errors
// string trim( _str )							--> Remove white spaces from expression

// ***********************ERRORS****************************
// std::underflow_error thrown if needed.

/*! Bares template class */
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
		queue<string> infixToPostfix( const string _exp );
		int hasPriority( const char _exp1, const char _exp2 );
		int isRightAssociative( const char _operator );
		int getOperatorPrecedence( const char _operator );

		bool isOperator( const char _char );
		bool isOperator( const string _str );
		bool isInvalidOperator( const string _str );
		bool isOperand( const char _char );
		bool isOperand( const string _str );

		int performOperation( const char _operator, const int _operand1, const int _operand2 );

		vector<string> readExpressions( const string _filename );
		queue<string> stringToQueue( const string _exp );
		int calculatesExpression( queue<string> _fila );
		void printQueue( queue<string> _queue );
		bool hasSyntaxError( queue<string> _infixQueue );

		string trim( const string & _str );
	
	/*!
     * Private section
    */
	private:

		/*! Attributes */
		string expression;	/*!< Expression to be evaluated */
		char operators[8] = { '+', '-', '/', '*', '^', '%', '(', ')' };
		char invalidOperators[2] = { '=', '.'};

		/*! Disable copy constructor */
		Bares( const Bares & ){ /* empty */ }
};

#endif

/* --------------------- [ End of the Bares.h header ] ------------------- */
/* ========================================================================= */