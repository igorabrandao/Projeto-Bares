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
Queue<string>
Bares::infixToPostfix( const string _exp )
{
	string symbol;					/*!< The current symbol to be classified */
	string topSymbol;				/*!< Top symbom from top Queue */
	Queue<string> _inputQueue;		/*!< The Queue with the input expression */
	Queue<string> outputQueue; 		/*!< Output list with postfix format */
	Stack<string> StackOfOperators;	/*!< Stack of operators */

	_inputQueue = stringToQueue( _exp );

	/*! Run until the Queue end */
	while ( !_inputQueue.empty() )
	{
		/** Remover o simbolo da lista de entrada e armazenar em symbol */
		symbol = _inputQueue.front();
		_inputQueue.pop();

		/*! Se symbol for operando... entao */
		if ( isOperand( symbol ) )
		{
			/* Enviar symbol direto para a fila de saida */
			outputQueue.push( symbol );
		}
		else if ( symbol == "(" ) /*!< Caso o symbol seja um abre parenteses */
		{
			/*! Joga o symbol na pilha */
			StackOfOperators.push( symbol );
		}
		else 	/* Se symbol nao for operando nem abre parenteses */
		{	
			/*! 
			 *	Se a pilha de operadores nao esta vazia 
			 *	topSymbol recebe pela primeira vez o elemento do topo para poder
			 * 	entrar no proximo while
			 */
			if ( !StackOfOperators.empty() )
			{
				/*! topSymbol recebe o simbolo do topo da pilha de operadores */
				topSymbol = StackOfOperators.top();
			}

			auto itrA = topSymbol.begin();
			auto itrB = symbol.begin();

			char _topSymbol = *itrA;
			char _symbol 	= *itrB;
			/*!
			 * 	Enquanto a pilha de operadores nao estiver vazia 
			 *	e o simbolo do topo (topSymbol) ≥ symb faca... 
			 */
			while( !StackOfOperators.empty() && hasPriority( _topSymbol, _symbol ) )
			{
				/*! topSymbol recebe o simbolo do topo da pilha de operadores */
				topSymbol = StackOfOperators.top();

				/* Se o simbolo do topo da pilha nao for parentesis */
				if ( topSymbol != "(" && topSymbol != ")" )
				{
					outputQueue.push( topSymbol );	/*!< Insere o simbolo do topo da pilha na fila de saida */
					StackOfOperators.pop(); 		/*!< Remove o operador ja utilizado da pilha */
				}
				else /*!< Se for um parentesis, apenas o retira da pilha */
				{
					StackOfOperators.pop();
				}	
			}

			/*! Empilhar symbol depois que retirar operadores de precedencia ≥ */
			StackOfOperators.push( symbol );
		}
	}

	/*! Descarregar operadores remanescentes da pilha e manda-los para a fila de saida */
	while ( !StackOfOperators.empty() )
	{
		/*! Remover simbolo da pilha e enviar para fila de saida */
		topSymbol = StackOfOperators.top();
		StackOfOperators.pop();

		/*! Os simbolos parenteses nao entram para a fila de saida */
		if ( topSymbol != "(" && topSymbol != ")" )
		{
			outputQueue.push( topSymbol ); /*! Se nao for parentesis, vai para a fila de saida */
		}
	}

	/*! Print the output Queue */
	printQueue(outputQueue);

	/*! Returns the Queue in a posfix format */
	return outputQueue;
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
			break;
		case '*':
		case '/':
		case '%':
			precedence = 2;
			break;
		case '^':
			precedence = 3;
			break;
		case '(':
		case ')':
			precedence = 0;
			break;
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
* Check whether a character is operator symbol.
***********************************************/
bool
Bares::isOperator( const string _str )
{
	auto itr = _str.begin();
	char char_ = *itr;
	/*! Check all possible operators */	
	for ( unsigned int i = 0; i < sizeof(operators); ++i )
	{
		if ( char_ == operators[i] )
			return true;
	}

	return false;
}

/********************************************//**
* Check whether a character is operator symbol.
***********************************************/
bool
Bares::isInvalidOperator( const string _str )
{
	auto itr = _str.begin();
	char char_ = *itr;

	/*! Check all possible operators */	
	for ( unsigned int i = 0; i < sizeof(invalidOperators); ++i )
	{
		if ( char_ == invalidOperators[i] )
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

/********************************************//**
* Check whether a character is alphanumeric 
* chanaracter.
***********************************************/
bool
Bares::isOperand( const string _str )
{
	auto itr = _str.begin();
	char char_ = *itr;

	/*! Compare the char with possible operands */
	if ( char_ >= '0' && char_ <= '9' ) return true;
	
	/*! It's not an operand */
	return false;
}

/********************************************//**
* Check whether a character is alphanumeric 
* chanaracter.
***********************************************/
int
Bares::performOperation( const char operator_, const int operand1_, const int operand2_ )
{
	/*! Sum */
	if ( operator_ == '+' ) return operand1_ + operand2_;

	/*! Subtraction */
	else if ( operator_ == '-' ) return operand1_ - operand2_;

	/*! Multiplication */
	else if ( operator_ == '*' ) return operand1_ * operand2_;

	/*! Division */
	else if ( operator_ == '/' ) return operand1_ / operand2_;

	/*! Division (int) */
	else if ( operator_ == '%' ) return operand1_ % operand2_;

	/*! Potentiation */
	else if ( operator_ == '^' ) return pow(operand1_, operand2_);

	/*! Cannot calculate */
	else cout << "<< Unexpected Error >>\n";
	return -1; 
}

/********************************************//**
* @brief Read the expressions of an input file
* @param filename the name of the input file
* @returns an array with all the expressions 
***********************************************/
vector<string> 
Bares::readExpressions( const string _filename )
{
	/*! Vector that stores all the expressions.*/
	vector<string> tempVector;

	/*! Opens the input file */
	ifstream file( "assets/data/" + _filename);

	/*! if the input file does not open */
	if ( !file.is_open() )
	{
		/*! Show a error message */
		cout << "Error!!! [ " << _filename << " ], does not open " << endl;
	}
	else /*!< Opened the file with success */
	{
		/*! Temporary auxiliar string to helps to read expression by expression */
		string str;

		/*! While there are expressions*/
        while ( getline( file, str ) )
        {
        	/*! Insert the expression in the vector */
        	if ( trim(str) != "" )
        		tempVector.push_back(str);
        	else
        	{
        		cout << "-------------------------------------------------------" << endl;
        		cout << ">>> Null expression..." << endl;
        		cout << "-------------------------------------------------------" << endl << endl;
        	}
        }
	}

	/*! returns the vector containing all expressions */
	return tempVector;
}

/*****************************************************************//**
* @brief transforms an infix expression in an array	
* where each position is an operator or an operand.
* @param _exp one infix expression 		
* @returns an array where each position is an operator or an operand. 		
*********************************************************************/
Queue<string>
Bares::stringToQueue( const string _exp )
{
	Queue<string> expression;
	//Stack<string> expression;
	//vector<string> expression;

	string strItr; /*! Usado apenas para fins de teste */
	string str;
	string opr;

	for ( auto itr( _exp.begin() ); itr < _exp.end(); ++itr )
	{
		strItr = *itr;

		if ( isOperand( *itr ) )
		{
			/*! if not a blank space */
			if ( strItr != " " )
				str = str + *itr;
		}
		else
		{

			if ( str != "" )
				expression.push(str);
			
			opr = *itr;
			if ( opr != " " )
				expression.push(opr);
			str = "";
		}
	}

	if ( str != "" )
	{	
		if ( str != " " )
			expression.push(str);
	}

	return expression;
}

/********************************************//**
* Calculates and evaluates the expression.
***********************************************/
int 
Bares::calculatesExpression( Queue<string> _fila ) 
{
 	string symbol;	/*!< Receives one member of the expression for be checked. */
 	Stack<double> stk;	/*!< Auxiliary Stack to calculate the expression */

 	/*! Operands. */
 	int firstOperand;
 	int secondOperand;

 	int result;	/*!< Store the result of the expression */

 	/*! If the Queue isn't empty, calculate the expression */
 	while ( !_fila.empty() ) 
 	{
 		symbol = _fila.front(); 	/*!< Receives the first member of the Queue */

 		/*! Since symb is the first element, we remove it from the Queue. */
 		_fila.pop();

 		/*! If the member is operand. */
 		if ( isOperand( symbol ) ) 
 		{
			try
			{
				/* Adds the operand in the Stack. */
				stk.push( std::stod( symbol ) );

			/* If occur an error. */
			} 
			catch ( std::exception& e ) 
			{
				/* ERROR. */
				throw std::out_of_range(" ERROR Value out of bounds. ");
			}
 		}

 		/* If the Stack size is greater than one, and symb is an operator. */
		if ( stk.size() > 1 && isOperator( symbol ) ) 
		{
 			/* Receives the second operand of the top Stack. */
 			secondOperand = stk.top();

 			/* Removes the operand of the top Stack. */
 			stk.pop();

 			/* Receives the first operand of the top Stack */
 			firstOperand = stk.top();
 			/* Removes the operand of the top Stack. */
	 		stk.pop();

	 		char symb = symbol[0];
			/* Receives the result of the operation. */
			if ( secondOperand == 0 && symb == '/' )
			{	
				cout << ">>> Zero division..." << endl;
				result = 0;
				return result; 
			}
			else
			{
				result = performOperation( symb, firstOperand, secondOperand );
			}
			stk.push( result );	/*!< Adds the result in the Stack */
		}
 	}

 	/* Receives the result, top Stack. */
 	result = stk.top();

 	/* Removes the result of the Stack. */
 	stk.pop();
 	
 	/* Return the result. */
 	return result;
}

/********************************************//**
* Print the Queue.
***********************************************/
void
Bares::printQueue( Queue<string> _Queue )
{
	string str;
	cout << "[ ";
	while( !_Queue.empty() )
	{
		str = _Queue.front();
		cout << str << " ";
		_Queue.pop();
	}
	cout << "]" << endl;
}

/********************************************//**
* Check if the expression has sintax error.
***********************************************/
bool
Bares::hasSyntaxError( Queue<string> _infixQueue )
{
	/*! Auxiliary variables */
	bool bResult = false;

	/*!< Auxiliary Queues to test erros */
	Queue<string> QueueTest1(_infixQueue);
	Queue<string> QueueTest2(_infixQueue);
	Queue<string> QueueTest3(_infixQueue);
	Queue<string> QueueTest4(_infixQueue);
	Queue<string> QueueTest5(_infixQueue);
	Queue<string> QueueTest6(_infixQueue);
	Queue<string> QueueTest7(_infixQueue);
	Queue<string> QueueTest8(_infixQueue);

	/********************************************//**
	* ERROR 01: Invalid numeric constant
	***********************************************/
	/*while ( !QueueTest1.empty() )
	{*/
		/*! Check the interval */
		/*if ( !(QueueTest1.front() > (-32767) && QueueTest1.front() < 32767) )
		{
			cout << ">>> Invalid Operator..." << endl;
			return true;
		}

		QueueTest1.pop();
	}*/

	/********************************************//**
	* ERROR 02: Missing operand
	***********************************************/
	int operandsInSeq 	= 0;
	int operatorsInSeq = 0;

	while ( !QueueTest2.empty() )
	{
		if ( isOperand(QueueTest2.front()) )
		{	
			operandsInSeq += 1;
			if ( operatorsInSeq == 1 )
				operatorsInSeq--;
		}
		else if ( isOperator( QueueTest2.front() ) )
		{
			if ( QueueTest2.front() != "(" && QueueTest2.front() != ")")
			{
				operatorsInSeq += 1; 	/*!< Increase the num of operators in sequence */  
				if ( operandsInSeq == 1 )
					operandsInSeq--;
			}
		}

		/* Testa se existem dois operadores ou dois operandos em sequencia */
		if ( operandsInSeq > 1 || operatorsInSeq > 1)
		{
			cout << ">>> Missing operand..." << endl;
			return true;
		}
		QueueTest2.pop();
	}
	if ( operatorsInSeq == 1 )
	{
		cout << ">>> Missing operand..." << endl;
		return true;
	}

	/********************************************//**
	* ERROR 03: Invalid operand
	***********************************************/
	while ( !QueueTest3.empty() )
	{
		if ( !isOperand( QueueTest3.front() ) && !isOperator( QueueTest3.front() ) )
		{
			cout << ">>> Operand " << QueueTest3.front() << " is invalid..." << endl;
			return true;
		}

		QueueTest3.pop();
	}

	/********************************************//**
	* ERROR 04: Invalid operator
	***********************************************/
	// Handle invalid operands
	while ( !QueueTest4.empty() )
	{
		if ( isInvalidOperator( QueueTest4.front() ) )
		{
			cout << ">>> Invalid Operator..." << endl;
			return true;
		}
		QueueTest4.pop();
	}

	/********************************************//**
	* ERROR 06: Invalid escope closer
	***********************************************/
	int inParentesis = 0;

	while ( !QueueTest6.empty() )
	{
		if( QueueTest6.front() == "(" )
			inParentesis++;
		
		/*! Se fechou um parentesis sem antes abri-lo dá erro*/
		if ( QueueTest6.front() == ")" && inParentesis == 0 )
		{
			cout << ">>> Invalid escope closer..." << endl;
			return true;
		}

		if ( QueueTest6.front() == ")" && inParentesis == 1 )
			inParentesis--;

		QueueTest6.pop();
	}

	/********************************************//**
	* ERROR 07: Open escope
	***********************************************/
	inParentesis = 0;

	while ( !QueueTest4.empty() )
	{
		if ( QueueTest4.front() == "(" )
			inParentesis++;
		if ( QueueTest4.front() == ")" && inParentesis == 1 )
		{
			inParentesis--; 
		}

		QueueTest4.pop();
	}

	if (inParentesis != 0 )
	{
		cout << ">>> Escope opened [ \'(\' without \')\' ] " << endl;
		return true;
	}

	//*********************************************[ end ]*********************************************//
	return bResult;
}

/********************************************//**
* Check if the expression has sintax error.
***********************************************/
string
Bares::trim( const string & str_  )
{
	if(str_.empty())
        return str_;

    std::size_t firstScan = str_.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str_.length() : firstScan;
    std::size_t last      = str_.find_last_not_of(' ');
    return str_.substr(first, last-first+1);
}