
#include <iostream>
#include<vector>
#include<list>
using namespace std;

//--------------------------------------------- Class definition---------------------------------------------
template <class dt>
class HashingTable
{
	friend  ostream& ::operator<< (ostream& s, HashingTable<dt>* h);

private:
	vector<list <dt>*> *hash;
	
public:
	HashingTable();
	HashingTable(int i);
	HashingTable(HashingTable<dt> &h);
	virtual ~HashingTable();
	bool find(dt s);
	void split(int i, int p);
	void remove(const dt s);
	void insert(dt s);
	void insert(int i, dt s);
	void  copy(HashingTable<dt> &h);                //Bonus
	void operator= (HashingTable<dt> &h);
	int size();
	list<dt>* getElements(int i);
	
};

//----------------------- empty constructor--------------------------------------------------------------------------------------------
template <class dt>
HashingTable<dt>::HashingTable()
{
	hash = new vector<list<dt>*>(0, NULL);
}

//------------------------ non empty constructor--------// creates vector of size i with NULL pointers
template<class dt>
HashingTable<dt>::HashingTable(int i)
{
	hash = new vector<list<dt>*>(i, NULL);
}

//------------------------ copy constructor------------------// 
template<class dt>
HashingTable<dt>::HashingTable(HashingTable<dt> &h)
{
	hash = new vector<list<dt>*>(h.size(), NULL);
	copy(h);
}

//------------------------ Destructor ----------------------------------------------------------------------------------------------------------
template<class dt>
HashingTable<dt>::~HashingTable()
{
	for (int i = 0; i < (*hash).size(); i++)     // Each element in vector
	{
		if ((*hash)[i] != NULL)
		{
			for (list<dt> ::iterator  it =  (*(*hash)[i]).begin() ; it !=(*(*hash)[i]).end() ; )    // Each element in list
			{
				
				//cout << *it << "  deleted" << endl;
				(*(*hash)[i]).remove(*(it++));                                 // Deletes each element in list
				 
			}	
		}
		
	}
	(*hash).erase((*hash).begin(), (*hash).end());               // Deletes elements in vector
	 delete hash;																		  // Deletes vector

	 cout << "Hash Table Deleted" << endl;

}  

//----------------------- Find ---------------------------------//  Finds an element in the Hashing Table
template<class dt>
bool HashingTable<dt>::find(dt s)
{
	int index = (s[0] - 'A');                         // hash value of given word

	for (int i = index; i < (*hash).size(); i++)      //starts from index = hash value n goes to end of hash table
	{
		for (list<dt> ::iterator j = (*(*hash)[i]).begin(); j != (*(*hash)[i]).end(); j++)    // Iterates on linked list at each index
		{

			if (*j == s) return true;

		}

	}

	return false;
}

//------------------------ Remove -------------------------// Removes an element from HashingTable
template<class dt>
void HashingTable<dt>::remove(const dt s)
{
	int index = (s[0] - 'A');               // hash index of given word
	bool found = false;					//  index for found

	for (int i = index; i < (*hash).size(); i++)    // index to end of hash table
	{
		if ((*hash)[i] != NULL)  {  (*((*hash)[i])).remove(s);   }
	}

	cout << "\n" << s << "  Removed \n" << endl;
}

//------------------------- insert method ----------------// Inserts an element as per hash value
template<class dt>
void HashingTable<dt>::insert(dt s)
{
	int index = s[0] - 'A';   // Hash index
	
	if ((*hash).size() <= index)      // Resizes hash table if size less than index
	{

		(*hash).resize(index + 1, NULL);

		(*hash)[index] = new list<dt>(1, s);

	}
	else													 // Inserts element at hash index
	{
		if ((*hash)[index] == NULL)    // Creates new list if hash index has null
		{
			(*hash)[index] = new list<dt>(1, s);
		}
		else                                            // Adds to list at hash index
		{
			(*(*hash)[index]).push_front(s);

		}

	}
}

//------------------------- split method ------------------// Splits hashtable as given in the project
template<class dt>
void HashingTable<dt>::split(int i, int p)
{
	bool inserted = false;

	if ((((*hash)[i]) != NULL)  && ( (*(*hash)[i]).size() > p ) )  // Checks the length of list at given index
	{

		list<dt> ::iterator j = (*(*hash)[i]).begin();					// Iterator to that list												
		advance(j, p);													// Advances iterator by p to leave first p elements

		for ( ; j != (*(*hash)[i]).end(); )				// iterates from p+1 to end
		{	
			inserted = false;
			if (i == ((*hash).size() - 1)) { insert((*hash).size(), NULL); }  // Expands hash table if end is reached

			for (int ii = i + 1; ii < (*hash).size(); ii++)			// iterates through lists from i+1 index to check
			{
				

				if ( (((*hash)[ii]) == NULL))							  // creates new list and inserts the element there if NULL
				{
					insert(ii, *j);
					inserted = true;
					(*(*hash)[i]).remove(*(j++));
					break;
					
				}
				else if ((*(*hash)[ii]).size() < p)					// inserts if any list below i+1 has less than p elements
				{
					insert(ii, *j);
					inserted = true;
					(*(*hash)[i]).remove(*(j++));
					break;		
				}

			}

			if (inserted == false)									// Expands hash table if element couldnt be inserted 
			{
				insert((*hash).size(), *j);
				(*(*hash)[i]).remove(*(j++));
				inserted = true;
			}

		}

	}

}

//------------------------- Ostream operator -------// Prints structure of the hash table
template <class dt>
ostream& operator<< (ostream& s, HashingTable<dt>* h)
{	
	

	for (int i = 0; i < (*h).hash->size(); i++) {             // Each list in hash table

		if ((*(*h).hash)[i] != NULL)								// Checks NULL values
		{
			for (list<dt> ::iterator j = (*(*(*h).hash)[i]).begin(); j != (*(*(*h).hash)[i]).end(); j++)   //Each element in list
			{

				cout << *j << "   ";

			}
			cout << "  " << endl;
		}

	}

	cout << "" << endl;
	return s;
}

//------------------------- Insert with index ---------// Inserts an element in the list at specific index of hashtable ( additional method)
template <class dt>
void HashingTable<dt>::insert(int i, dt s)   // Additional method to insert an element at specifit index. 
{
	int index = i;										// index value

	if ((*hash).size() <= index)				// Expands table if size is less than index
	{

		(*hash).resize(index + 1, NULL);

		(*hash)[index] = new list<dt>(1, s);

	}
	else														// Inserts at give index value
	{
		if ((*hash)[index] == NULL)			// Creates new list if required at given index
		{
			(*hash)[index] = new list<dt>(1, s);
		}
		else
		{
			(*(*hash)[index]).push_back(s);

		}

	}
}

//--------------------------  Copy -----------------------// copies whole HashingTable
template <class dt>
void HashingTable<dt>::copy(HashingTable<dt> &h)
{
	// Deleting the present items                 
	for (int i = 0; i < (*hash).size(); i++)     // iterates over hash table
	{
		if ((*hash)[i] != NULL)
		{
			for (list<dt> ::iterator it = (*(*hash)[i]).begin(); it != (*(*hash)[i]).end(); )     // traverses each list 
			{

				//cout << *it << "  deleted" << endl; 
				(*(*hash)[i]).remove(*(it++));    // Deletes each element

			}
		}

	}
	(*hash).erase((*hash).begin(), (*hash).end());

	// Adding elements of h
	hash = new vector<list<dt>*>(h.size(), NULL);     // Creates new table with the length of given table

	for (int j = 0; j < h.size(); j++)    // Goes to each index
	{
		list<dt>* k;
		k = h.getElements(j);

		if (k != NULL)
		{
			for (list<dt>::iterator l = (*k).begin(); l != (*k).end(); l++)      // traverses list and inserts elements 
			{
					insert(j, *l);

			}

		}

	}

}

//--------------------------- Size --------------------------// returns size of hashtable
template <class dt>
int HashingTable<dt>::size()
{
	return (*hash).size();      
}

//----------------------------getElements ----------// returns pointer to list at specific index in hash table
template <class dt>
list<dt>* HashingTable<dt>::getElements(int i)
{
	return ((*hash)[i]);
}

//--------------------------- = Operator ------------// Uses copy method
template<class dt>
void HashingTable<dt>:: operator= (HashingTable<dt> &h)
{
	copy(h);

}


void main() /* A sample main program */
{
	HashingTable<char*>* myHashTable;

	char* Names[25] = { "Andy B", "Amy Dean", "Antonio G", "Andy Roberts",
		"Brian W","Bob Macy", "Brent James", "Buck Muck",
		"Cannon James", "Cart Wright", "Catherine Zeta", "Carl Lewis",
		"David Johnson", "Dowd Peter", "Daniel Fauchier", "Dawn Smith",
		"Yarda Varda", "Yami Jacob", "Yester Louis", "Yukon Oklahoma",
		"Zandi Rich", "Zea John", "Zelby Leon", "Ziert Paul", "Zanola Helen" };

	int i;

	myHashTable = new HashingTable<char*>(26);


	for (i = 0; i < 25; i++)
		(*myHashTable).insert(Names[i]);


	cout << "Printing the hash table after inserting...." << endl;
	cout << myHashTable << endl;


	if ((*myHashTable).find("Zandi Rich"))
		cout << "Zandi Rich is in the list" << endl;
	else
		cout << "Zandi Rich is not in the list" << endl;


	(*myHashTable).remove("Zea John");

	if ((*myHashTable).find("Zea John"))
		cout << "Zea John is in the list" << endl;
	else
		cout << "Zea John is not in the list" << endl;



	for (i = 0; i <26; i++)
		(*myHashTable).split(i, 2);


	cout << "Printing the hash table after splitting...." << endl;
	cout << myHashTable << endl;


	if ((*myHashTable).find("Ziert Paul"))
		cout << "Ziert Paul is in the list" << endl;
	else
		cout << "Ziert Paul is not in the list" << endl;


	(*myHashTable).insert("Zea John");


	if ((*myHashTable).find("Zea John"))
		cout << "Zea John is in the list" << endl;
	else
		cout << "Zea John is not in the list" << endl;


	// Additional lines for copy and = -------------------------------------
	HashingTable<char*>* myNewHashTable1 = new HashingTable<char*>();
	(*myNewHashTable1)=(*myHashTable);

	cout << "\n Printing myNewHashTable1 \n" << endl;
	cout << myNewHashTable1 << endl;


	// Copy constructor-------------------------------------------------
	HashingTable<char*>* myNewHashTable2 = new HashingTable<char*>((*myHashTable));
	
	cout << "\n Printing myNewHashTable2 \n" << endl;
	cout << myNewHashTable2 << endl;
	

	delete myHashTable;
	delete myNewHashTable1;
	delete myNewHashTable2;

	cin >> i;
}


