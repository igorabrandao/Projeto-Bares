/*!
	<PRE>
	SOURCE FILE : Stack.h
	DESCRIPTION.: Stack class - with implementation.
	AUTHOR......: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: October/2015
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	tail UPDATE.: Octuber 16th, 2015.
	</pre>
*/
	
#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

/*! Stack template class */
template <class T>
class Stack
{
	/*!
     * Private section
    */
	private:

		/*! Template node */
		struct Node
		{
			T data;  		/*!< Data field */
			Node * prev;	/*!< Previous pointer */
			Node * next;	/*!< Next pointer */

			Node( const T & d = T(), Node* p = nullptr, Node* n = nullptr )
			: data( d )
			, prev( p )
			, next( n )
			{ /* Empty */ };
		};

	/*!
     * Public section
    */
	public:

		/*! Iterator class */
		class const_iterator
		{
			/*!
		     * Public section
		    */
			public:

				/*! Public constructor */
				const_iterator() : current( nullptr ) { /* Empty */ };

				/*!	Return the storaged object to actual position.
				 *	@brief to const_iterator, thi method is an accessor that returns
				 *	a constant reference. So it can aapears on the right side
				 *	from an atribution or in comparators.
				*/
				const T & operator*() const
				{
					return ( current->data );
				}

				/*! Pre-increment */
				const_iterator & operator++()
				{
					current = current->next;	/*!< This node receives the next node */
					return ( *this );			/*!< Return the next node */
				}

				/*! Pos-increment */
				const_iterator & operator++( int )
				{
					const_iterator old = *this;
					++(*this);
					return old;
				}

				// Pre-decrement : --it
				const_iterator & operator--()
				{
					current = current->mp_Prev;	/*!< This node receives the previus node */
					return ( *this ); 			/*!< Return this node */
				}

				// Pos-decrement : it--
				const_iterator operator--( int )
				{
					const_iterator old = *this;	/*!< This node receives the previus node */
					--( *this ); 				/*!< Updates the previus node */
					return old; 				/*!< Return this node */
				}

				/*! @return true if the atual node is equal to right hand side node */
				bool operator==( const const_iterator & rhs ) const
				{
					return current == rhs.current;
				}

				/*! @return true if the atual node is diferent to right hand side node */
				bool operator!=( const const_iterator & rhs ) const
				{
					return !( *this == rhs );
				}

			/*!
			 *	Protect section
			*/
			protected:

				/*! Node current pointer */
				Node * current;

				const_iterator( Node * p )
				{
					current = p;
				}

				friend class Stack<T>;
		};

		class iterator : public const_iterator
		{
			/*!
			 *	Public section
			*/
			public :

				// Construtor publico do iterator que invoca construtor da classe base .
				iterator( ) : const_iterator::current( nullptr ) { /* Empty */ }
				
				/*!
				 *	Retorna objeto armazenado na posicao apontada por ‘current’.
				 * 	For iterator , tem duas versoes , uma accessor que permite sua
				 * 	utilizacao do apenas do lado direito de uma atribuicao ou em
				 * 	comparacoes.
				 */
				const T & operator*() const
				{
					/*! Retorna os dados do noh */
					return ( *this );
				}

				/*! Esta Mutator version eh usada do lado esquerdo de atribuicoes */
				T & operator*()
				{
					/*! Retorna os dados do noh */
					return ( this->current->data );
				}
				
				// prefixo
				iterator & operator++()
				{
					this->current = this->current->next;
					return ( *this );
				}

				// posfix
				iterator operator++( int )
				{
					iterator old = *this;	// este noh recebe o proximo noh
					++( *this ); 			// Atualiza o proximo noh (next node)
					return old; 			// retorna this noh
				}
				
				// prefixo
				iterator & operator--()
				{
					this->current = this->current->prev;	/*!< This node receive the previus node */
					return ( *this );			/*!< Return the previus nodde */
				}

				// posfix
				iterator operator--( int )
				{
					iterator old = *this;
					--( *this );
					return old;
				}

			/*!
			 *	Protect section
			*/
			protected :
				
				/*!
				 *	Construtor protegido que espera uma posi¸c~ao para apontar .
				 *	E invocado principalmente dentro da classe ‘Stack ’, mas
				 * 	nao pelo cliente ( que nao tem acesso a este metodo ).
				*/
				iterator( Node *p )
				{
					this->current = p; /*! Atribui o noh atual */
				}

				// Necessario p/ permitir acesso de ‘Stack’ aos campos desta classe.
				friend class Stack<T>;
		};

		/*! Defaut Constructor */
		Stack();

		/*! Constructor copy */
		Stack( const Stack & rhs );

		/*! Destructor */
		~Stack();

		/**
		 *	Stack clone. 
		 * 	@param rhs The stack to be cloned.
		*/
		const Stack & operator=( const Stack & rhs )
		{	
			clear(); 			/*!< Desaloca todos os itens da Stack */
			new Stack( rhs ); 	/*!< Clone the stack */
		}

		/********************************************//**
		* Specific methods from class.
		***********************************************/

		/*! @return the first node (with stored value) of the Stack */
		iterator begin() /*!< Mutator version */
		{
			return iterator( head->next ); 
		}

		/*! @return the first node (with stored value) of the Stack */
		const_iterator begin() const /*!< Accessor version */
		{
			return iterator( head->next ); 
		}

		/*! @return the last node of the Stack */
		iterator end() 	/*!< Mutator version */
		{ 
			return iterator( tail ); 
		}

		/*! @return the last node of the Stack */
		const_iterator end() const /*!< Accessor version */
		{
			return iterator( tail ); 
		}

		/*! Return number of elements currently in the Stack */
		int size() const 
		{	
			return theSize; 
		}

		/*! @return true if the Stack is empty */
		bool empty() const 
		{
			return ( size() == 0 ); 
		}

		void print()
		{
			iterator itr = begin();
			cout << "Stack = "<< endl;
			while( itr != end() )
			{
				cout <<"[ "<< itr.current->data << " ]" << endl;
				itr++;
			}
			cout << "====" << endl;
		}

		/*! Clear all stack nodes, making it empty */
		void clear()
		{
			erase( begin(), end() );
		}

		T & top()	/*!< Mutator version */
		{ 
			return *begin(); 
		}

		/*! @return the value of the first node of the Stack */
		const T & top() const /*!< Accessor version  */
		{ 
			return *begin(); 
		}

		/*! @return the value of the last node of the Stack */
		//T & back() /*!< Mutator version */
		//{
		//	return ( *( --end() ) );
		//}

		/*! @return the value of the last node of the Stack */
		//const T & back() const /*!< Accessor version  */
		//{
		//	return ( *( --end() ) );
		//}

		/*! Adiciona um novo noh no topo da stack */
		void push( const T & obj )
		{
			insert( begin(), obj );
		}

		/*! Remove o noh do topo da stack */
		void pop()
		{
			erase( begin() );
		}

		/*!
		 *	Insere um novo noh na Stack.
		 *	@param itr um noh da stack
		 * 	@param obj Valor no novo noh
		 * 	@return the new node
		 */
		iterator insert( iterator itr , const T & obj )
		{
			Node *newNode = new Node( obj, itr.current->prev, itr.current );
			itr.current->prev->next = newNode;
			itr.current->prev = newNode;
			theSize++;
			
			return newNode;
		}

		/**
		 * 	Remove  o noh itr da Stacka
		 * 	@param itr Um noh da Stacka
		 * 	@return O noh removido.
		*/
		iterator erase( iterator itr )	
		{
			Node* pAuxNode = itr.current->next;	// Aloca um noh auxiliar
			itr.current->prev->next = itr.current->next;	// Atribui o proximo noh para o proximo noh do noh anterior.
			itr.current->next->prev = itr.current->prev; 	// Atribui o noh anterior ao noh anterior do proximo noh.
			delete itr.current;	// Desaloca o noh
			--theSize; 			// Decrementa o tamanho da Stacka.
			return pAuxNode; 	// Retorna o noh removido
		}

		/**
		 * Remove os nohs entre o range passado como parametro
		 * @param start O primeiro noh a ser removido
		 * @param end O último noh a ser removido
		 * @return O proximo noh do ultimo noh removido
		 */
		iterator erase( iterator start , iterator end )
		{
			iterator itr = start; 	/*!< Iterador auxiliar para percorrer o range da Stacka */
			while ( itr != end ) 	/*!< Percorre o range da Stacka */
			{
				itr = erase( itr );	/*!< Atribui o proximo noh retornado da funcao e remove o noh */
			}
			return itr; 			/*!< Retorna o proximo noh do ultimo noh removido */
		}


		/*!
		 *	Retorna o noh encontrado na Stacka
		 * 	@param obj O valor do noh a ser procurado
		 * 	@return O noh encontrado.
		 */
		const_iterator find( const T & obj ) const
		{
			const_iterator citr = find(obj);
			return citr;
		}

		/*!
		 *	Retorna o noh encontrado na Stacka
		 * 	@param obj O valor do noh a ser procurado
		 * 	@return O noh encontrado.
		 */
		iterator find( const T & obj )
		{
			iterator itr = begin(); // atribui o noh inicial da Stacka ao iterador auxiliar
			while ( itr != end() ) // Percorre o intervalo da Stacka
			{
				if ( *( itr ) == obj )  // Se o valor no noh eh igual ao objeto obj.
					break; // Finaliza a busca
			
				++( itr ); // Atribui o noh next ao iterador auxiliar
			}
			return itr; // Retorna o noh encontrado na Stacka
		}

	private:
		Node * head;
		Node * tail;
		int theSize;

		void init();
};

#include "Stack.inl"
#endif // STACK_H