// This is the basic 

#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

//forward class definitions needed because we use
//classes before they are defined
template <class Datatype> class SListNode;
template <class Datatype> class SLinkedList;
template <class Datatype> class SListIterator;


//-------------------------------------------
// Name: SListNode
// Description: Node class - each element looks like this


template<class Datatype>
class SListNode
{
public:
	// data in node
	Datatype m_data;
	// pointer to next node
	SListNode<Datatype>* m_next;

	//constructor
	SListNode()
	{
		m_next = 0;
	}

	void InsertAfter(Datatype p_data)
	{
		// create new node
		SListNode<Datatype>* newnode = new SListNode<Datatype>;
		newnode->m_data=p_data;
		//make the new node point to next node
		newnode->m_next = m_next;

		//make the previous node point to new node
		m_next = newnode;
	}
};

//----------------------------------------------------
//Name:           SLinkedList
//Description:    This is the list
//----------------------------------------------------

template<class Datatype>
class SLinkedList
{

public:
	SListNode<Datatype>*m_head;
	SListNode<Datatype>*m_tail;
	int m_count;

	
	//contructor creates an empty list
	SLinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}

	// destructor deletes the dynamically allocated memory
	~SLinkedList()
	{
		//Temporary node pointer
		SListNode<Datatype>* itr = m_head;
		SListNode<Datatype>* next = 0;

		while(itr != 0)
		{
			//save the pointer to next node 
			next = itr->m_next;
			
			//delete the current node
			delete itr;

			//make the next node the current node
			itr = next;
		}
	}

	//append, add data to the end of the list
	void Append(Datatype p_data)
	{
		//check if list is empty
		if(m_head == 0)
		{
			//the list is empty
			//creat a new node and make the head and tail point there

			m_head=m_tail=new SListNode<Datatype>;
			m_head->m_data = p_data;
			
		}
		else
		{
			//insert new node after the tail and update the tail
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_next;
		}
		m_count++;
	}

	//Prepend, adds a node at the start of the list
	void Prepend(Datatype p_data)
	{
		//create a new node
		SListNode<Datatype>* newnode = new SListNode<Datatype>;
		newnode->m_data = p_data;
		newnode->m_next = m_head;

		//set the head node and the tail node if necessary
		m_head = newnode;
		if(m_tail == 0)
		{
			m_tail = m_head;
		}

		m_count++;
	}

	//RemoveHead removes the first element from the list O(c)
	void RemoveHead()
	{
		SListNode<Datatype>* node = 0;

		if (m_head != 0)
		{
			//make the node point to the next node
			node = m_head->m_next;

			//now delete the head and make head point to node
			delete m_head;
			m_head = node;


			//if the head is null , we have just deleted the only
			//element in the list, set the tail to 0

			if(m_head == 0)
			{
				m_tail == 0;
			}

			m_count--;
		}
	}

	void RemoveTail()
	{
		SListNode<Datatype>*node = m_head;

		//if the list is empty there is no work to do

		if(m_head != 0)
		{
			//now if the head=tail then there is only oe element
			delete m_head;
			m_head = m_tail = 0;
		}

		else
		{
			//skip ahead and find the node right before the
			//last node
			while(node->m_next != m_tail)
			{
				node = node->m_next;
			}

			//make the tail point to the node before the last node
			//and delete the old tail

			m_tail = node;
			delete node->m_next;
			node->m_next = 0;
		}
		m_count --;
	}

	//GetIterator, get an iterator pointing to the start of the 
	//current list

	SListIterator<Datatype> GetIterator()
	{
		return SListIterator<Datatype>(this, m_head);
	}

	//--------------------------------------
	//Name:Insert
	//Description: insert new data after the given iterator
	//				or append if the iterator is not valid
	//arguments : p_iterator: iterator to insert after
	//			  p_data: data to insert
	//Return value: none
	//--------------------------------------
	void Insert( SListIterator<Datatype>& 
		p_iterator, Datatype p_data )
	{
		// if the iterator doesn’t belong to this 
		//list, do nothing.
			if( p_iterator.m_list != this )
				return;
		if( p_iterator.m_node != 0 )
		{
			// if the iterator is valid, then insert the node
				p_iterator.m_node->InsertAfter( p_data);
			// if the iterator is the tail node, then
			// update the tail pointer to point to the
			// new node.
			if( p_iterator.m_node == m_tail )
			{
				m_tail = p_iterator.m_node->m_next;

			}
			m_count++;
		}
		else
		{
			// if the iterator is invalid, just append the data
				Append( p_data );
		}
	}
	//--------------------------------------
	//Name:Remove
	//Description: Remove node that the iterator points to
	//arguments : p_iterator: pointer to node to remove
	//			  p_data: data to insert
	//Return value: none
	//--------------------------------------
	void Remove(SListIterator<Datatype>& p_iterator)
	{
		SListNode<Datatype>* node = m_head;
		// if the iterator doesn’t belong to this list, do nothing.
			if( p_iterator.m_list != this )
				return;
		// if node is invalid, then do nothing.
		if( p_iterator.m_node == 0 )
			return;
		if( p_iterator.m_node == m_head )
		{
			// move the iterator forward and delete the head.
			p_iterator.Forth();
			RemoveHead();
		}
		else
		{
			// scan forward through the list until you find
			// the node prior to the node that you want to remove
			while( node->m_next != p_iterator.m_node )
				node = node->m_next;
			// move the iterator forward.
			p_iterator.Forth();
			// if the node you are deleting is the tail,
			// update the tail node.
			if( node->m_next == m_tail )
			{
				m_tail = node;
			}
			// delete the node.
			delete node->m_next;
			// re-link the list.
			node->m_next = p_iterator.m_node;
		}
		m_count--;
	}
	

};

//---------------------------------------------------
//Name:           SListIterator
//Description:    Iterator for a singly linked list
//---------------------------------------------------


template <class Datatype>
class SListIterator
{
public:
	SListNode <Datatype>*m_node;
	SLinkedList<Datatype>* m_list;

	//Constructor
	SListIterator(SLinkedList<Datatype>* p_list=0, 
		SListNode<Datatype>* p_node=0)
	{
		m_list = p_list;
		m_node = p_node;
	}

	//Start
	void Start()
	{
		if(m_list !=0)
		{
			m_node =m_list->m_head;
		}
	}

	//Forth - steps forward through the list
	void Forth()
	{
		if(m_node !=0)
		{
			m_node = m_node->m_next;
		}
	}

	//Item - gets the item that the iterator points to
	Datatype& Item()
	{
		return m_node->m_data;
	}


	//Valid - an iterator is valid if it is not null
	bool Valid()
	{
		return(m_node != 0);
	}
};

#endif


