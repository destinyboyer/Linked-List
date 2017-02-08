/*----------------------------------------------------------------------------------------------------------

	Author:			Destiny Boyer
	Date:			11/3/2016
	Version:		1.0

	Templated linked list will take an object of any type and create a dynamically allocated sorted list.
	Class can insert and remove objects from any point in the list. Each node in the list contains a
	pointer to an object, and a pointer to the next node in the list. Relies on a private Node class in
	order to create the links. Users can also retrieve nodes from the list, list will return
	the first instance in the list that is equal to the first parameter passed through the 
	function, will set the second parameter equal to this value. Class also provides overloaded operators
	to evaluate lists for equality and inequality, as well as create a deep copy. Two lists can be merged,
	or a list can be created that has only the elements shared in common by the two parameters.

----------------------------------------------------------------------------------------------------------*/

#ifndef List_h
#define List_h

#include <iostream>
#include <fstream>


using namespace std;


template <typename T>
class List {

	// output operator for class List, print data,
	// responsibility for output is left to object stored in the list
	friend ostream& operator<<(ostream& output, const List<T>& thelist) {
		typename List<T>::Node* current = thelist.head;
		while (current != NULL) {
			output << *current->data;
			current = current->next;
		}
		return output;
	}




	public:
	List();                           		// default constructor
	~List();                       			// destructor
	List(const List&);						// copy constructor
	bool insert(T*);                  		// insert one Node into list
	bool isEmpty() const;             		// is list empty?
	void buildList(ifstream&);        		// build a list from datafile
	bool retrieve(T* target, T& retrieved);	//retrieves a node from the list, sets it equal to the second parameter
	bool remove(T* target, T& removed);		//removes a node from the list
	void makeEmpty();						//deallocates memory for all nodes and sets head to NULL
	int size() const;						//returns size of the list
	void intersect(List<T>& listOne, List<T>& listTwo);	//sets calling object to the commone elements of the two parameters
	void merge(List<T>& toMerge, List<T>& toMergeTwo);	//takes two parameters and sets calling object equal to the two lists combines


	bool operator!=(const List<T>& toCompare) const;
	bool operator==(const List<T>& toCompare) const;
	List<T>& operator=(const List<T>& toCopy);			// needs many more member functions to become a complete ADT




	private:

	//struct for storing the nodes in the list. Each node has a
	//pointer to a data object and a pointer to the next node in the list

	struct Node {       
		T* data;          
		Node* next;
	};
	
	//pointer to the first Node in the list
	Node* head;
};

/*-------------------------------------------------------------------------------------------------

	Copy constructor. Uses the overloaded = operator to make a deep copy of the parameter
	and set it equal to the calling object. Parameter is passed by reference to save on memory
	but is const.

	POSTCONDITIONS:
		- makes a deep copy of the parameter and sets it equal to the calling object

-------------------------------------------------------------------------------------------------*/

template<typename T>
List<T>::List(const List<T>& toCopy) {
	*this = toCopy;
};


/*-------------------------------------------------------------------------------------------------

	Default no-args constructor. Creates a List object and sets head = NULL

	POSTCONDITIONS:
		- instantiates a new List object
		- sets head to NULL

-------------------------------------------------------------------------------------------------*/

template <typename T>
List<T>::List() {
	//sets head to NULL
	head = NULL;
};

/*-------------------------------------------------------------------------------------------------

	Deconstructor. Uses makeEmpty as a helper function to delete all Nodes in the list and
	set their pointers equal to NULL

	POSTCONDITIONS:
		- deletes all nodes in a list and sets head equal to NULL

-------------------------------------------------------------------------------------------------*/

template<typename T>
List<T>::~List() {
	this->makeEmpty();	//calls makeEmpty to delete all the nodes in the list
	delete head;		//deletes head
	head = NULL;		//sets head equal to NULL
};

/*-------------------------------------------------------------------------------------------------

	Returns if the head of the calling object is equal to NULL. If head is NULL then the 
	List is empty.

	POSTCONDITIONS:
		- returns true if head is NULL, false otherwise

-------------------------------------------------------------------------------------------------*/

template <typename T>
bool List<T>::isEmpty() const {
	return head == NULL;	//returns true if head is NULL, false otherwise
}

/*-------------------------------------------------------------------------------------------------

	Removes the first instance in the list that is equal to the first parameter. Sets the second
	parameter equal to the removed instance. If the first object is not found in the list then
	the second parameter is unchanged.

	PRECONDITIONS:
		- target should not be NULL

	POSTCONDITIONS:
		- removes a Node from the list. Sets the second argument equal to the removed
		  object

-------------------------------------------------------------------------------------------------*/

template<typename T>
bool List<T>::remove(T* target, T& removed) {
	bool ableToRemove;	//bool object

	//checks to make sure that head is not equal to NULL
	//and that target is not equal to NULL
	if (target == NULL || head == NULL) {
		//if either condition is true then we cannot remove from the list
		//sets ableToRemove to false
		ableToRemove = false;
	} else {
		//else ableToRemove is true
		ableToRemove = true;
	}

	if (ableToRemove) {
		Node* previous = head;	//Node to track previous Node
		Node* current = head;	//Node to track current Node

		while (current != NULL) {

			//checks to see if target is equal to the current Node
			if (*target == *current->data) {
				//checks to see if the target is equal to the current
				//node, and if this node is equal to head (special remove case)
				if (*target == *head->data) {
					//increments the current node
					current = current->next;
					//sets the second parameter equal to the data of head
					removed = *head->data;
					//increments head to the next node, effectively removing the 
					//node from the list
					head->next = current->next;
				} else {
					//sets second parameter equal to the removed object
					removed = *current->data;
					//sets previous nodes pointer to the node after the
					//one that target is equal to.
					previous->next = current->next;
					//deletes the current node
					delete current;
					//sets the current pointer equal to NULL
					current = NULL;
				}
				//returns true indicating that we were able to remove a node
				//equal to targer
				return true;
			}
			//increments the nodes that we are using to iterate through
			//the list
			previous = current;
			current = current->next;
		}
		//returns false indicating that we were not able to remove a node
		//equal to the target
		return false;
	}
};

/*-------------------------------------------------------------------------------------------------

	Overloads the != operator. Uses the overloaded == operator and returns the opposite value
	of that operator. Declared const as it should not change the calling object.

	POSTCONDITIONS:
		- returns bool value. True if the two lists are not equal to one another,
		  false otherwise.

-------------------------------------------------------------------------------------------------*/

template<typename T>
bool List<T>::operator!=(const List<T>& toCompare) const {
	return !(*this == toCompare);
};

/*-------------------------------------------------------------------------------------------------

	Retrieves the first instance in the list that is equal to the first parameter. Sets the second
	parameter equal this instance. If the first object is not found in the list then
	the second parameter is unchanged.

	PRECONDITIONS:
		- target should not be NULL

	POSTCONDITIONS:
		- retrieves an object from the list. Sets the second argument equal to this
		  object

-------------------------------------------------------------------------------------------------*/

template<typename T>
bool List<T>::retrieve(T* target, T& retrieved) {
	bool ableToRetrieve;	//creates bool object

	//checks to see if head or the target object are
	//equal to NULL, if so sets ableToRetrieve indicating
	//that we are not able to retrieve from the list either
	//because the list is empty or the target is not a valid value
	if (head == NULL || target == NULL) {
		ableToRetrieve = false;
	} else {
		ableToRetrieve = true;
	}

	if (ableToRetrieve) {
		Node* previous = head;	//node equal to previous node in the list
		Node* current = head;	//node equal to the current node in the list

		while (current != NULL) {
			//checks to see if target is equal to the current node in the list
			if (*target == *current->data) {
				//checks to see if this node is the head node
				if (*target == *head->data) {
					//sets the second parameter (retrieved) equal to
					//head
					retrieved = *head->data;
					//returns true
					return true;
				}
				//sets retrieved to the data of the current node
				retrieved = *current->data;
				//returns true
				return true;
			}
			//increments the current and previous nodes through the list
			previous = current;
			current = current->next;
		}
		//returns false indicating that we were not able to 
		//find the target object in the list
		return false;
	}
};

/*-------------------------------------------------------------------------------------------------

	Inserts the parameter into the appropriate spot in the linked list.

	PRECONDITIONS:
		- parameter cannot be NULL

	POSTCONDITIONS:
		- iterates through the list and finds the appropriate sorted spot for the node.
		  inserts the dataptr, linking it to the next element in the list, and linking the
		  previous element in the list to the new element.

-------------------------------------------------------------------------------------------------*/

template <typename T>
bool List<T>::insert(T* dataptr) {
	//checks to see if the computer is out of memory
	//if so returns false
	Node* ptr = new Node;
	if (ptr == NULL) {
		return false;
	}
	//checks to see if the pointer to the object to insert
	//is set to NULL, if so, returns false
	if (dataptr == NULL) {
		return false;
	}

	ptr->data = dataptr;	//sets ptr equal to the parameter

	//checks to see if the list is empty (head == NULL) or if the 
	//object to insert is less than head, if so inserts the object at
	//the beginning of the list
	if (isEmpty() || *ptr->data < *head->data) {
		//sets the next pointer equal to head
		ptr->next = head;
		//sets head equal to the new object
		head = ptr;
	} else {								//case if the new object is greater than head
		Node* current = head->next;      	//node to walk over the list
		Node* previous = head;           	//node to walk over the list, kee

		//iterates over the list until we find a spot where the new object it less than or
		//equal to the current node, or if we reach the end of the list
		while (current != NULL && *current->data < *ptr->data) {
			previous = current;              	//increases the node
			current = current->next;			//increases the node
		}

		//inserts the new node, links it the current
		ptr->next = current;
		//links the previous node to the new node
		previous->next = ptr;
	}
	//returns true indicating that we have been able to
	//insert the new node in to the list
	return true;
};

/*-------------------------------------------------------------------------------------------------

	Returns an int value equal to the number of nodes in the list

	POSTCONDITIONS:
	- returns an int value equal to the number of nodes in the list

-------------------------------------------------------------------------------------------------*/

template<typename T>
int List<T>::size() const {
	//instantiates node pointer to iterator over the list. sets it equal to the head
	//of the calling object
	Node* currentPtr = this->head;
	//creates retVal = 0. will return 0 if the list is empty.
	int retVal = 1;
	//iterates over list while current is not equal to NULL
	while (currentPtr != NULL) {
		//increments node
		currentPtr = currentPtr->next;
		//increments retVal
		retVal++;
	}
	//returns retVal
	return retVal;
};

/*-------------------------------------------------------------------------------------------------

	Overloaded operator to evaluate whether two lists are equal. Iterates over each of the lists
	and returns false at the first instance that the value of objects in each node are not
	equal to each other. Relies on any object in the node being set up for equality evaluation.
	Does not change either of the lists.

-------------------------------------------------------------------------------------------------*/

template<typename T>
bool List<T>::operator==(const List<T>& toCompare) const {
	//checks to see if both of the lists are empty, if so
	//returns true;
	if (this->isEmpty() && toCompare.isEmpty()) {
		return true;
	} 
	//checks to see if the lists are not equal in size
	//if so returns false
	else if (this->size() != toCompare.size()) {
		return false;
	} 
	//iterates over the list, check each of their node
	//pairs for equality, returns false the first time an
	//inequality happens
	else {
		Node* thisPtr = this->head;
		Node* thatPtr = toCompare.head;
		while (thisPtr != NULL) {
			if (*thisPtr->data != *thatPtr->data) {
				return false;
			}
			thisPtr = thisPtr->next;
			thatPtr = thatPtr->next;
		}
		return true;
	}
};

/*-------------------------------------------------------------------------------------------------

	Function iterates over a list and deallocates memory for each node. Sets head to null;

	POSTCONDITIONS:
		- deallocates all memory in the nodes of a linked list

-------------------------------------------------------------------------------------------------*/

template<typename T>
void List<T>::makeEmpty() {
	//checks to see if head is equal to null, if so we do not need to empty the list
	//exits the function
	if (head == NULL) {
		return;
	} else {
		Node* previous = head;			//node to track the previous node in the list
		Node* current = head->next;		//node to track the current node in the list

		//iterates over the list while current is not equal to null
		while (current != NULL) {
			//delete previous->data (deallocates memory)
			delete previous;
			//sets previous to current
			previous = current;
			//sets current to the next node in the list
			current = current->next;
		}

		//delete previous->data;
		delete previous;
		//deletes current's data
		delete current;
		//sets head to NULL
		head = NULL;
	}
};

/*-------------------------------------------------------------------------------------------------

	Takes two Linked Lists as parameters and creates a third list that is filled with all the 
	elements that the two parameters share in common.

	POSTCONDITIONS:
		- sets the calling object equal to a linked list that is set to the elements that the
		  two parameters show in common

-------------------------------------------------------------------------------------------------*/

template<typename T>
void List<T>::intersect(List<T>& listOne, List<T>& listTwo) {
	//checks to see if the calling object is equal to both of the
	//parameters, if so we return 
	if (*this == listOne && *this == listTwo) {
		return;
	}
	List<T> intersection;			//list to store the intersecting values

	Node* currentPtr = listOne.head;		//node to track our progress in the list

	T retrieved;		//object to set to retrieved value

	while (currentPtr != NULL) {
		//checks to see if the value found in listOne is also found in listTwo
		if (listTwo.retrieve(currentPtr->data, retrieved) == true) {
			//checks to see if the value is already in the intersection list
			//if not we insert it in to the list
			if (intersection.retrieve(currentPtr->data, retrieved) == false) {
				//adds the datapoint to the intersection list
				intersection.insert(currentPtr->data);
			}
		}
		//increments the node that is iterating over the list
		currentPtr = currentPtr->next;

	}
	//makes the calling object empty
	this->makeEmpty();

	//sets the current object equal to the head of intersection
	//and the head of intersection equal to NULL
	head = intersection.head;
	intersection.head = NULL;

};

/*-------------------------------------------------------------------------------------------------

	Merges two lists together (in order) and sets the calling object to this sorted list.
	No new memory is allocated, rather pointers are just rearranged.

	PRECONDITIONS:
		- both parameters cannot be equal to the calling object

	POSTCONDITIONS:
		- sets calling object equal to the merged nodes of the two parameters 

-------------------------------------------------------------------------------------------------*/

template<typename T>
void List<T>::merge(List<T>& listOne, List<T>& listTwo) {
	//checks to see if the calling object is equal to the two
	//parameters, if so bails.
	if (*this == listOne && *this == listTwo) {
		return;
	//else makes the calling object empty, so that we do not
	//leak memory
	} else if (*this != listOne && *this != listTwo) {
		makeEmpty();
	}


	Node* listOnePtr = listOne.head;		//pointer to the head of listOne
	Node* listTwoPtr = listTwo.head;		//pointer to the head of listTwo

	Node* newListHead;						//static pointer to the head of what will be the new list
	Node* current;							//node as the current iterator

	//checks to see if the node from list one is less than
	//the node data from list two
	if (*listOnePtr->data < *listTwoPtr->data) {
		//if the listOne node is the least than we set the current
		//node equal to this (next in the ordered list)
		current = listOne.head;
		//sets the head of the new list equal to current
		newListHead = current;
		//increments the listOne pointer since we have already
		//included it in the newly ordered list
		listOnePtr = listOnePtr->next;
	//else we know that the node data from lsitTwoPtr is less than
	//or equal to the listOnePtr
	} else {
		//sets the current node to listTwo's head
		current = listTwo.head;
		//sets the newListHead equal to current
		newListHead = current;
		//increments the listTwoPtr to the next node in the list
		listTwoPtr = listTwoPtr->next;
	}

	//while loop iterates over listOne and listTwo, while both
	//of them still have data
	while (listOnePtr != NULL && listTwoPtr != NULL) {
		//if the data that listOne is pointing two
		//is less than the data that listTwo is pointing to
		if (*listOnePtr->data < *listTwoPtr->data) {
			//we set the next node from current equal to
			//the listOnePtr
			current->next = listOnePtr;
			//increment the listOnePtr
			listOnePtr = listOnePtr->next;
			//increments the current node ptr
			current = current->next;
		} else {
			//else we know that the listTwoPointer is less than
			//or equal to listOnePtr
			//set current's next node to listTwoPtr
			current->next = listTwoPtr;
			//increments the listTwoPointer
			listTwoPtr = listTwoPtr->next;
			//increments the current pointer
			current = current->next;
		}
	}

	//checks to see if the listTwoPtr still has more nodes
	//if so we append this to the current->next list
	if (listOnePtr == NULL && listTwoPtr != NULL) {
		current->next = listTwoPtr;
		current = current->next;
	//otherwise we check to see if listOnePtr still has information
	//if so we append this to the end of our newly ordered list
	} else if (listOnePtr != NULL && listTwoPtr == NULL) {
		current->next = listOnePtr;
		current = current->next;
	}
	//set head of the calling object equal to our newly ordered lsit
	head = newListHead;
	//set both heads of our parameters equal to NULL to avoid memory leaks
    listOne.head = NULL;
	listTwo.head = NULL;
};

/*-------------------------------------------------------------------------------------------------

	Overloaded operator for =. Creates a deep copy of the parameter. Uses insert() as a
	helper function.

	POSTCONDITIONS:
		- makes a deep copy of the parameter

-------------------------------------------------------------------------------------------------*/

template<typename T>
List<T>& List<T>::operator=(const List<T>& toCopy) {
	//checks if the calling object is equal to 
	//the parameter. If so we cannot make a deep
	//copy and then set it equal to itself.
	if (*this == toCopy) {
		//return the calling object
		return *this;
	} else {
		//checks if head is not equal to NULL
		//if so, clears the list
		if (head != NULL) {
			makeEmpty();
		}
		Node* currentPtr = toCopy.head;		//current pointer equal to the head of parameter
		while (currentPtr != NULL) {
			this->insert(currentPtr->data);		//calls insert to create a deep copy of the node
			currentPtr = currentPtr->next;		//increments the iterator node
		}
	}
	//return this
	return *this;
}

/*-------------------------------------------------------------------------------------------------

	Takes and infile stream and builds an ordered list with this input. Relies on object's
	being able to handle the ifstream in order to populate an object.

	POSTCONDITIONS:
		- builds an ordered list from a file

-------------------------------------------------------------------------------------------------*/
template <typename T>
void List<T>::buildList(ifstream& infile) {
	T* ptr;
	bool successfulRead;                            // read good data
	bool success;                                   // successfully insert
	for (;;) {
		ptr = new T;
		successfulRead = ptr->setData(infile);       // fill the T object
		if (infile.eof()) {
			delete ptr;
			break;
		}

		// insert good data into the list, otherwise ignore it
		if (successfulRead) {
			success = insert(ptr);
		} else {
			delete ptr;
		}
		if (!success) break;
	}
}


#endif




