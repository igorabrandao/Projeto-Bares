/*! \brief Bares.inl.
 *
 *  Implements the functions from Bares class.
*/
#include "Bares.h"

/********************************************//**
* constructor
***********************************************/
Bares::Bares()
{
    /* Empty */
}

/********************************************//**
* destructor
***********************************************/
Bares::~Bares()
{
	/* Empty */
}

/********************************************//**
* Convert infix to postfix exp_s.
***********************************************/
string
Bares::infix2Postfix( const string exp_ )
{
	/*! Declare a stack from our custom class */
	Stack<char> S;

	/*! Initialize postfix as empty string */
	string postfix = "";

	for ( unsigned int i = 0; i < exp_.length(); ++i )
	{
		/*! Scanning each character from left. 
		 * If character is a delimitter, move on.
		*/
		if ( exp_[i] == ' ' || exp_[i] == ',' ) continue; 

		/*! If character is operator, pop two elements from stack, 
		 * perform operation and push the result back. 
		*/
		else if ( isOperator(exp_[i]) )
		{
			while( !S.isEmpty() && S.top() != '(' && hasPriority(S.top(), exp_[i]) )
			{
				postfix+= S.top();
				S.pop();
			}

			S.push(exp_[i]);
		}
		/*! If character is an operand */
		else if ( isOperand(exp_[i]) )
		{
			postfix += exp_[i];
		}
		/*! If character is an parentheses opener */
		else if (exp_[i] == '(') 
		{
			S.push(exp_[i]);
		}
		/*! If character is an parentheses closer */
		else if ( exp_[i] == ')' )
		{
			while( !S.isEmpty() && S.top() !=  '(' )
			{
				postfix += S.top();
				S.pop();
			}

			S.pop();
		}
	}

	while( !S.isEmpty() )
	{
		postfix += S.top();
		S.pop();
	}

	return postfix;
}

/********************************************//**
* Check wich operator has a higher precedence.
***********************************************/
int
Bares::hasPriority( const char exp1_, const char exp2_ )
{
	int exp1Precedence = getOperatorPrecedence(exp1_);
	int exp2Precedence = getOperatorPrecedence(exp2_);

	/*! If operators have equal precedence, return true if they are left associative. 
	 * return false, if right associative. 
	 * if operator is left-associative, left one should be given priority.
	*/
	if ( exp1Precedence == exp2Precedence )
	{
		if ( isRightAssociative(exp1_) ) return false;
		else return true;
	}

	/*! Return the higher precedence */
	return exp1Precedence > exp2Precedence ? true: false;
}

/********************************************//**
* Check whether an operator is right associative.
***********************************************/
int
Bares::isRightAssociative( const char operator_ )
{
	if ( operator_ == '^' ) return true;
	return false;
}

/********************************************//**
* Get the operator precedence.
***********************************************/
int
Bares::getOperatorPrecedence( const char operator_ )
{
	/*! Define the precedence */
	int precedence = -1;

	/*! Check the operator */
	switch ( operator_ )
	{
		case '+':
		case '-':
			precedence = 1;
		case '*':
		case '/':
		case '%':
			precedence = 2;
		case '^':
			precedence = 3;
		case '(':
		case ')':
			precedence = 4;
	}

	return precedence;
}

/********************************************//**
* Check whether a character is operator symbol.
***********************************************/
bool
Bares::isOperator( const char char_ )
{
	/*! Check all possible operators */	
	for ( unsigned int i = 0; i < sizeof(operators); ++i )
	{
		if ( char_ == operators[i] )
			return true;
	}

	return false;
}

/********************************************//**
* Check whether a character is alphanumeric 
* chanaracter.
***********************************************/
bool
Bares::isOperand( const char char_ )
{
	/*! Compare the char with possible operands */
	if ( char_ >= '0' && char_ <= '9' ) return true;
	if ( char_ >= 'a' && char_ <= 'z' ) return true;
	if ( char_ >= 'A' && char_ <= 'Z' ) return true;

	/*! It's not an operand */
	return false;
}