/*++++++++++++++++++++++++++++++++++++++++++
This code demostrates array templates 
+++++++++++++++++++++++++++++++++++++++++++*/
//This is a basic 1D array class 

#ifndef ARRAY_H
#define ARRAY_H

template<class Datatype>
class Array
{

public :
	//------------------------------
	//name: Array::Array
	//description:This constructs the array
	//arguments: p_size thesize of the array 
	//-----------------------------
	Array(int p_size){
		//allocate enough memory for the array
		m_array = new Datatype[p_size];
		//set size variable
		m_size = p_size;

	}
	//------------------------------
	//name: Array::~Array
	//description:This deconstructs the array
	//-----------------------------
	~Array(){
		//if the array is not null, delete it
		if(m_array !=0){
			delete[]m_array;
		
		}
		m_array =0;
	}
		//------------------------------
	//name: Array::Resize
	//description:This resizes the array
	//Arguments: p_size the new size of the array
	//-----------------------------
	void Resize(int p_size){
		//create a new array with the new size
		Datatype* newarray = new Datatype[p_size];
		//if the new array wasnt allocated
		//then just return and dont do anything
		if(newarray == 0){
			return;
		}
		//determine which size is smaller the new one or the old one
		int min;
		if(p_size < m_size){
			min = p_size;
		}else{
			min = m_size;
		}
		//loop through and copy everything
		//this complexity O(n) caused by the lopp
		for(int index =0;index < min;index++){
			newarray[index] = m_array[index];
		}
		//set the size of the new array
		m-size = p_size;
		//delete the old array
		if(m_array != 0){
			delete[] m_array;
			//copy the pointer 
			m_array = newarray;
			newarray =0;
		}
	}

	//------------------------------
	//name: Array::opertaor[]
	//description:get a reference to the item at the given index
	//Arguments: p_index the index you want
	//Return: Reference to the item
	//-----------------------------
	Datatype& operator[](int p_index){
		return m_array[p_index];
	}
	//------------------------------
	//name: Array::Insert
	//description:insert an item between two cells
	//Arguments: p_item the item to insert
	//			p_index index to insert at
	//-----------------------------
	void insert(Datatype p_item,int p_index){
		int index;
		//move everything after p_index up one cell
		for(index = m_size-1;index> p_index;index--)
		{
			m_array[index]=m_array[index-1];
		}
		//insert the item
		m_array[p_index]=p_item;
	}
	//------------------------------
	//name: Array::Remove
	//description:remove a cell
	//Arguments: p_index the index to remove
	//-----------------------------
	void remove(int p_index){
		int index;
		//move everything after p_index down one
		for(index = p_index+1;index < m_size;index++){
			m_array[index-1]=m_array[index];
		}
	}
	//------------------------------
	//name: Array::size
	//description:return the size of the array
	//return: the size of the array
	//-----------------------------
	int size(){
		return m_size;
	}
	//------------------------------
	//name: Array::operator Datatype*
	//description:conversion operator,converts the array to a pointer so we pass it to a function
	//Arguments: none
	//returns: a pointer to the array
	//-----------------------------
	operator Datatype*(){
		return m_array;
	}
	//------------------------------
	//name: Array::WriteFile
	//description:write an array to disc
	//Arguments: the filename
	//returns: true on succes or false if fail
	//-----------------------------
	bool writeFile(const char* p_filename){
		ofstream outfile (p_filename);

		if (outfile.is_open()) //if the file is open
		{
			for(int i = 0; i < m_numelements; i++)
			{
				outfile << m_array[i] << endl;
			}

			outfile.close(); //closing the file
			return true;
		}
		//else couldn't open
		return false;
	}
	//------------------------------
	//name: Array::readFile
	//description:reads an array from disc
	//Arguments: the filename
	//returns: true on succes or false if fail
	//-----------------------------
	bool readFile(const char* p_filename){
		Datatype input; //this will contain the data read from the file

		ifstream myfile (p_filename); //opening the file.
		if (myfile.is_open()) //if the file is open
		{
			while (! myfile.eof() ) //while the end of file is NOT reached
			{
				myfile >> input; //get one line from the file
				Push(input); //Use the push function to add it to the array
			}
			myfile.close(); //closing the file
			return true;
		}
		//else couldnt open file
		return false;
	}
	//------------------------------
	//name: Array::m_array
	//description:this is the pointer to the array
	//-----------------------------
	Datatype* m_array;
	//------------------------------
	//name: Array::m_size
	//description:this is the size to the array
	//-----------------------------
	int m_size;

};
#endif
