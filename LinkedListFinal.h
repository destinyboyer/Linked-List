//#pragma once
#ifndef LinkedListFinal_h
#define LinkedListFinal_h

#include "employee.h"
#include "nodedata.h"
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
	List();                           	// default constructor
	~List();                       	// destructor
	List(const List&);             	// copy constructor
	bool insert(T*);                  	// insert one Node into list
	bool isEmpty() const;             	// is list empty?
	void buildList(ifstream&);        	// build a list from datafile
	bool retrieve(T* target, T& retrieved);
	bool remove(T* target, T& removed);
	void makeEmpty();
	int size();
	void intersect(List<T>& listOne, List<T>& listTwo);
	void merge(List<T>& toMerge, List<T>& toMergeTwo);


	bool operator!=(List<T>& toCompare);
	bool operator==(List<T>& toCompare);
	List<T>& operator=(List<T>& toCopy);			// needs many more member functions to become a complete ADT




	private:
	struct Node {        	// the node in a linked list
		T* data;          	// pointer to actual data, operations in T
		Node* next;
	};




	Node* head;          	// pointer to first node in list
};






/*
template<typename F>
ostream<F>& operator<<(ostream<F>& output, const LinkedListFinal<T>& thelist) {




LinkedListFinal<T>::Node* current = thelist.head;
while (current != NULL) {
output << *current->data;
current = current->next;
}
return output;                  	// enables output << x << y;
};
*/


//----------------------------------------------------------------------------
// Constructor
template <typename T>
List<T>::List() {
	head = NULL;
};
template<typename T>
List<T>::~List() {
	this->makeEmpty();
	delete head;
	head = NULL;
};




// isEmpty
// check to see if List is empty as defined by a NULL head
template <typename T>
bool List<T>::isEmpty() const {
	return head == NULL;
}


//remove
template<typename T>
bool List<T>::remove(T* target, T& removed) {
	bool ableToRemove = head != NULL;

	if (ableToRemove) {
		Node* previous = head;
		Node* current = head;

		while (current != NULL) {


			if (*target == *current->data) {
				if (*target == *head->data) {
					current = current->next;
					removed = *head->data;
					head->next = current->next;


				} else {
					removed = *current->data;
					previous->next = current->next;
					delete current;
					current = NULL;
				}
				return true;
			}
			previous = current;
			current = current->next;
		}
		//removed = 0;
		return false;
	}
};


template<typename T>
bool List<T>::operator!=(List<T>& toCompare) {
	return !(*this == toCompare);
};


template<typename T>
bool List<T>::retrieve(T* target, T& retrieved) {
	bool ableToRetrieve = head != NULL;

	if (ableToRetrieve) {
		Node* previous = head;
		Node* current = head;




		while (current != NULL) {


			if (*target == *current->data) {
				if (*target == *head->data) {
					current = current->next;
					retrieved = *head->data;
					head->next = current->next;
					return true;
				}
				retrieved = *current->data;
				previous->next = current->next;
				return true;
			}
			previous = current;
			current = current->next;
		}
		retrieved = 0;
		return false;
	}




};




//----------------------------------------------------------------------------
// insert
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insert(T* dataptr) {


	Node* ptr = new Node;
	if (ptr == NULL) {
		return false;
	}            	// out of memory, bail
	ptr->data = dataptr;                       	// link the node to data




												// if the list is empty or if the node should be inserted before
												// the first node of the list
	if (isEmpty() || *ptr->data < *head->data) {
		ptr->next = head;
		head = ptr;
	}


	// then check the rest of the list until we find where it belongs
	else {
		Node* current = head->next;      	// to walk list
		Node* previous = head;           	// to walk list, lags behind

											// walk until end of the list or found position to insert
		while (current != NULL && *current->data < *ptr->data) {
			previous = current;              	// walk to next node
			current = current->next;
		}

		// insert new node, link it in
		ptr->next = current;
		previous->next = ptr;
	}
	return true;
};


template<typename T>
int List<T>::size() {
	Node* currentPtr = this->head;
	int retVal = 0;
	while (currentPtr != NULL) {
		currentPtr = currentPtr->next;
		retVal++;
	}
	return retVal;


};


template<typename T>
bool List<T>::operator==(List<T>& toCompare) {
	if (this->isEmpty() || toCompare.isEmpty()) {
		return false;
	} else if (this->size() != toCompare.size()) {
		return false;
	} else {
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


template<typename T>
void List<T>::makeEmpty() {
	if (head == NULL) {
		return;
	} else {

		Node* previous = head;
		Node* current = head->next;

		while (current != NULL) {
			//delete previous->data;
			delete previous;
			previous = current;
			current = current->next;
		}

		//delete previous->data;
		delete previous;
		delete current;
		head = NULL;
	}
};


template<typename T>
void List<T>::intersect(List<T>& listOne, List<T>& listTwo) {
	List<T> intersection;

	Node* currentPtr = listOne.head;

	T retrieved;

	while (currentPtr != NULL) {
		if (listTwo.retrieve(currentPtr->data, retrieved) == true) {
			if (intersection.retrieve(currentPtr->data, retrieved) == false) {
				intersection.insert(currentPtr->data);
			}
			//cout << *currentPtr->data;
		}
		currentPtr = currentPtr->next;

	}

	this->makeEmpty();


	Node* intersectPtr = intersection.head;


	while (intersectPtr != NULL) {
		insert(intersectPtr->data);
		intersectPtr = intersectPtr->next;
	}
	intersection.makeEmpty();


};


template<typename T>
void List<T>::merge(List<T>& toMerge, List<T>& toMergeTwo) {
	Node* currentPtr;
	Node* previousPtr;
	Node* thisPtr = NULL;
	Node* temp;

	int toNULL = -1;

	if (head != NULL) {
		return;
	}

	if (*this == toMerge && *this == toMerge) {
		return;
	}

	if (*this == toMerge) {
		//head = toMerge.head;
		Node* thisPtr = toMergeTwo.head;
		toNULL = 1;

	} else if (*this == toMergeTwo) {
		//head = toMergeTwo.head;
		Node* thisPtr = toMerge.head;
		toNULL = 2;

	} else if (toMerge.head == NULL) {
		head = toMergeTwo.head;
		toMergeTwo.head = NULL;
		return;
	} else if (toMergeTwo.head == NULL) {
		head = toMerge.head;
		toMerge.head == NULL;
		return;
	} else {
		Node* data1 = toMerge.head;
		Node* data2 = toMergeTwo.head;
		if (*data1->data < *data2->data) {
			head = toMerge.head;
			thisPtr = toMergeTwo.head;
		} else {
			head = toMergeTwo.head;
			thisPtr = toMerge.head;
		}

		toNULL = 3;
	}

	previousPtr = head;
	currentPtr = head;

	while (currentPtr != NULL && thisPtr != NULL) {
		if (*currentPtr->data >= *thisPtr->data) {
			temp = thisPtr;
			previousPtr->next = temp;
			temp->next = currentPtr;
			thisPtr = thisPtr->next;
		} else if (*currentPtr->data < *thisPtr->data) {
			currentPtr = currentPtr->next;
		}
		if (thisPtr == NULL) {
			break;
		}
		if (currentPtr != NULL) {
			previousPtr = currentPtr;
		}
	}

	if (currentPtr == NULL && thisPtr != NULL) {
		previousPtr->next = thisPtr;
	}

	if (toNULL == 1) {
		toMergeTwo.head = NULL;
		return;
	} else if (toNULL == 2) {
		toMerge.head = NULL;
		return;
	} else {
		toMerge.head = NULL;
		toMergeTwo.head = NULL;
		return;
	}

};



template<typename T>
List<T>& List<T>::operator=(List<T>& toCopy) {
	if (*this == toCopy) {
		return *this;
	} else {
		if (head != NULL) {
			makeEmpty();
		}
		Node* currentPtr = toCopy.head;
		while (currentPtr != NULL) {
			this->insert(currentPtr->data);
			currentPtr = currentPtr->next;
		}
	}
	return *this;
}






//----------------------------------------------------------------------------
// buildList 
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
	T* ptr = new T;
	bool successfulRead;                            // read good data
	bool success;        // successfully insert

						 
						 /*
	while (!infile.eof()) {
		ptr = new T;
		successfulRead = ptr->setData(infile);

		if (successfulRead) {
			success = insert(ptr);
		} else {
			delete ptr;
		}
		if (!success) {
			break;
		}
	}

	delete ptr;
	*/
	for (;;) {

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




