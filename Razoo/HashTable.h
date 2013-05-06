//HashTable.h
//this is the Linked hash table implementation

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "SLinkedList.h"
#include "Array.h"



//=======================================================
//Name:				HashEntry
//Description:		This class key, data pairs
//=======================================================

template<class KeyType, class Datatype>
class HashEntry
{
public:
	KeyType m_key;
	Datatype m_data;
};

//=======================================================
//Name:				HashTable
//Description:		This is the implementation of the 
//					hash table 
//=======================================================
template<class KeyType, class Datatype>
class HashTable
{
public:
	typedef HashEntry<KeyType, Datatype> Entry;
	int m_size;
	int m_count;
	Array<SLinkedList<Entry>> m_table;
	unsigned long int (*m_hash)(KeyType);


	//=======================================================
	//Name:				HashTable
	//Description:		construct a table with a size, and
	//					a hash function. the constructor will 
	//					construct the array with the correct 
	//					size
	//Arguments:		p_size: the size of the array
	//					p_hash: the hash function
	//=======================================================

	HashTable(int p_size, unsigned long int 
		(*p_hash)(KeyType) ): m_table( p_size )
	{
		// set the size, hash function, and count.
		m_size = p_size;
		m_hash = p_hash;
		m_count = 0;
	}

	//=======================================================
	//Name:				Insert
	//Description:		Insert a new key, data pair
	//Arguments:		p_key: the key
	//					p_data: the data
	//=======================================================
	
	void Insert(KeyType p_key, Datatype p_data)
	{
		//create an entry object
		Entry entry;
		entry.m_data = p_data;
		entry.m_key = p_key;

		//get the hash value for the key, and modulo
		//it so that it fits ion the table
		int index = m_hash( p_key ) % m_size;

		//add the entry to the correct index, and 
		//incremate count
		m_table[index].Append( entry );
		m_count++;
	}
	//=======================================================
	//Name:				Find
	//Description:		Find a key in the table
	//Arguments:		p_key: the key
	//Returns:			a pointer the entry that has the 
	//					key/data or 0
	//=======================================================
	Entry* Find( KeyType p_key )
	{
		//find out which index the key is in
		int index = m_hash( p_key ) % m_size;

		//get an iterator to the list at the index
		SListIterator<Entry> itr = m_table[index].GetIterator();
		while(itr.Valid())
		{
			//if the two keys match return pointer to the entry
			if( itr.Item().m_key == p_key )
			return &(itr.Item());
			itr.Forth();
		}
		//no match found
		return 0;
	}
	
	//=======================================================
	//Name:				Remove 
	//Description:		remove an entry based on key
	//Arguments:		p_key: the key
	//Returns:			true if removed, otherwise false
	//=======================================================

	bool Remove( KeyType p_key )
	{
		int index = m_hash( p_key ) % m_size;

		SListIterator<Entry> itr = m_table[index].GetIterator();
		//search the item
		while( itr.Valid() )
		{
			if( itr.Item().m_key == p_key )
			{		
				m_table[index].Remove(itr);
				m_count--;
				return true;
			}
			itr.Forth();
		}
		return false;
	}

	//=======================================================
	//Name:				Count 
	//Description:		returns the number
	//Arguments:		none
	//Returns:			m_count
	//=======================================================
	int Count()
	{
		return m_count;
	}
};
#endif