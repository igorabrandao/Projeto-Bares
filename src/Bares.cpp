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
queue<string>
Bares::infixToPostfix( const string _exp )
{
	string symbol;					/*!< The current symbol to be classified */
	string topSymbol;				/*!< Top symbom from top queue */
	queue<string> _inputQueue;		/*!< The queue with the input expression */
	queue<string> outputQueue; 		/*!< Output list with postfix format */
	stack<string> stackOfOperators;	/*!< stack of operators */

	_inputQueue = stringToQueue( _exp );

	/*! Run until the queue end */
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
			stackOfOperators.push( symbol );
		}
		else 	/* Se symbol nao for operando nem abre parenteses */
		{	
			/*! 
			 *	Se a pilha de operadores nao esta vazia 
			 *	topSymbol recebe pela primeira vez o elemento do topo para poder
			 * 	entrar no proximo while
			 */
			if ( !stackOfOperators.empty() )
			{
				/*! topSymbol recebe o simbolo do topo da pilha de operadores */
				topSymbol = stackOfOperators.top();
			}

			auto itrA = topSymbol.begin();
			auto itrB = symbol.begin();

			char _topSymbol = *itrA;
			char _symbol 	= *itrB;
			/*!
			 * 	Enquanto a pilha de operadores nao estiver vazia 
			 *	e o simbolo do topo (topSymbol) ≥ symb faca... 
			 */
			while( !stackOfOperators.empty() && hasPriority( _topSymbol, _symbol ) )
			{
				/*! topSymbol recebe o simbolo do topo da pilha de operadores */
				topSymbol = stackOfOperators.top();

				/* Se o simbolo do topo da pilha nao for parentesis */
				if ( topSymbol != "(" && topSymbol != ")" )
				{
					outputQueue.push( topSymbol );	/*!< Insere o simbolo do topo da pilha na fila de saida */
					stackOfOperators.pop(); 		/*!< Remove o operador ja utilizado da pilha */
				}
				else /*!< Se for um parentesis, apenas o retira da pilha */
				{
					stackOfOperators.pop();
				}	
			}

			/*! Empilhar symbol depois que retirar operadores de precedencia ≥ */
			stackOfOperators.push( symbol );
		}
	}

	/*! Descarregar operadores remanescentes da pilha e manda-los para a fila de saida */
	while ( !stackOfOperators.empty() )
	{
		/*! Remover simbolo da pilha e enviar para fila de saida */
		topSymbol = stackOfOperators.top();
		stackOfOperators.pop();

		/*! Os simbolos parenteses nao entram para a fila de saida */
		if ( topSymbol != "(" && topSymbol != ")" )
		{
			outputQueue.push( topSymbol ); /*! Se nao for parentesis, vai para a fila de saida */
		}
	}

	/*! Print the output queue */
	printQueue(outputQueue);

	/*! Returns the queue in a posfix format */
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
queue<string>
Bares::stringToQueue( const string _exp )
{
	queue<string> expression;
	//stack<string> expression;
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
Bares::calculatesExpression( queue<string> _fila ) 
{
 	string symbol;	/*!< Receives one member of the expression for be checked. */
 	stack<double> stk;	/*!< Auxiliary stack to calculate the expression */

 	/*! Operands. */
 	int firstOperand;
 	int secondOperand;

 	int result;	/*!< Store the result of the expression */

 	/*! If the queue isn't empty, calculate the expression */
 	while ( !_fila.empty() ) 
 	{
 		symbol = _fila.front(); 	/*!< Receives the first member of the queue */

 		/*! Since symb is the first element, we remove it from the queue. */
 		_fila.pop();

 		/*! If the member is operand. */
 		if ( isOperand( symbol ) ) 
 		{
			try
			{
				/* Adds the operand in the stack. */
				stk.push( std::stod( symbol ) );

			/* If occur an error. */
			} 
			catch ( std::exception& e ) 
			{
				/* ERROR. */
				throw std::out_of_range(" ERROR Value out of bounds. ");
			}
 		}

 		/* If the stack size is greater than one, and symb is an operator. */
		if ( stk.size() > 1 && isOperator( symbol ) ) 
		{
 			/* Receives the second operand of the top stack. */
 			secondOperand = stk.top();

 			/* Removes the operand of the top stack. */
 			stk.pop();

 			/* Receives the first operand of the top stack */
 			firstOperand = stk.top();
 			/* Removes the operand of the top stack. */
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
			stk.push( result );	/*!< Adds the result in the stack */
		}
 	}

 	/* Receives the result, top stack. */
 	result = stk.top();

 	/* Removes the result of the stack. */
 	stk.pop();
 	
 	/* Return the result. */
 	return result;
}

/********************************************//**
* Print the queue.
***********************************************/
void
Bares::printQueue( queue<string> _queue )
{
	string str;
	cout << "[ ";
	while( !_queue.empty() )
	{
		str = _queue.front();
		cout << str << " ";
		_queue.pop();
	}
	cout << "]" << endl;
}

/********************************************//**
* Check if the expression has sintax error.
***********************************************/
bool
Bares::hasSyntaxError( queue<string> _infixQueue )
{
	/*! Auxiliary variables */
	bool bResult = false;

	/*!< Auxiliary queues to test erros */
	queue<string> queueTest1(_infixQueue);
	queue<string> queueTest2(_infixQueue);
	queue<string> queueTest3(_infixQueue);
	queue<string> queueTest4(_infixQueue);
	queue<string> queueTest5(_infixQueue);
	queue<string> queueTest6(_infixQueue);
	queue<string> queueTest7(_infixQueue);
	queue<string> queueTest8(_infixQueue);

	/********************************************//**
	* ERROR 01: Invalid numeric constant
	***********************************************/
	/*while ( !queueTest1.empty() )
	{*/
		/*! Check the interval */
		/*if ( !(queueTest1.front() > (-32767) && queueTest1.front() < 32767) )
		{
			cout << ">>> Invalid Operator..." << endl;
			return true;
		}

		queueTest1.pop();
	}*/

	/********************************************//**
	* ERROR 02: Missing operand
	***********************************************/
	int operandsInSeq 	= 0;
	int operatorsInSeq = 0;

	while ( !queueTest2.empty() )
	{
		if ( isOperand(queueTest2.front()) )
		{	
			operandsInSeq += 1;
			if ( operatorsInSeq == 1 )
				operatorsInSeq--;
		}
		else if ( isOperator( queueTest2.front() ) )
		{
			if ( queueTest2.front() != "(" && queueTest2.front() != ")")
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
		queueTest2.pop();
	}
	if ( operatorsInSeq == 1 )
	{
		cout << ">>> Missing operand..." << endl;
		return true;
	}

	/********************************************//**
	* ERROR 03: Invalid operand
	***********************************************/
	while ( !queueTest3.empty() )
	{
		if ( !isOperand( queueTest3.front() ) && !isOperator( queueTest3.front() ) )
		{
			cout << ">>> Operand " << queueTest3.front() << " is invalid..." << endl;
			return true;
		}

		queueTest3.pop();
	}

	/********************************************//**
	* ERROR 04: Invalid operator
	***********************************************/
	// Handle invalid operands
	while ( !queueTest4.empty() )
	{
		if ( isInvalidOperator( queueTest4.front() ) )
		{
			cout << ">>> Invalid Operator..." << endl;
			return true;
		}
		queueTest4.pop();
	}

	/********************************************//**
	* ERROR 06: Invalid escope closer
	***********************************************/
	int inParentesis = 0;

	while ( !queueTest6.empty() )
	{
		if( queueTest6.front() == "(" )
			inParentesis++;
		
		/*! Se fechou um parentesis sem antes abri-lo dá erro*/
		if ( queueTest6.front() == ")" && inParentesis == 0 )
		{
			cout << ">>> Invalid escope closer..." << endl;
			return true;
		}

		if ( queueTest6.front() == ")" && inParentesis == 1 )
			inParentesis--;

		queueTest6.pop();
	}

	/********************************************//**
	* ERROR 07: Open escope
	***********************************************/
	inParentesis = 0;

	while ( !queueTest4.empty() )
	{
		if ( queueTest4.front() == "(" )
			inParentesis++;
		if ( queueTest4.front() == ")" && inParentesis == 1 )
		{
			inParentesis--; 
		}

		queueTest4.pop();
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