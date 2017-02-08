#include "nodedata.h"
#include <iostream>
#include <fstream>
//#include "nodedata.h"


using namespace std;

template <typename T>
class List {


	// output operator for class List, print data,
	// responsibility for output is left to object stored in the list
	template<typename T>
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
										// ~List();                       	// destructor
										// List(const List&);             	// copy constructor
	bool insert(T*);                  	// insert one Node into list
	bool isEmpty() const;             	// is list empty?
	void buildList(ifstream&);        	// build a list from datafile
	bool retrieve(T* target, T*& retrieved);
	bool remove(T* target, T*& removed);
	void makeEmpty();
	void intersect(List<T>& listOne, List<T>& listTwo);
	void merge(List<T>& toMerge, List<T>& toMergeTwo);

	bool operator==(List<T>& toCompare);
	List<T>& operator=(List<T>& toCopy);

										// needs many more member functions to become a complete ADT


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
}
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
bool List<T>::remove(T* target, T*& removed) {
	bool ableToRemove = head != NULL;


	if (ableToRemove) {
		Node* previous = head;
		Node* current = head;


		while (current != NULL) {

			if (*target == *current->data) {
				if (*target == *head->data) {
					current = current->next;
					removed = head->data;
					head->next = current->next;
				} else {
					removed = current->data;
					previous->next = current->next;
					delete current;
					current = NULL;
				}
				return true;
			}
			previous = current;
			current = current->next;
		}
		removed = NULL;
		return false;
	}
};

template<typename T>
bool List<T>::retrieve(T* target, T*& retrieved) {
	bool ableToRetrieve = head != NULL;


	if (ableToRetrieve) {
		Node* previous = head;
		Node* current = head;


		while (current != NULL) {

			if (*target == *current->data) {
				if (*target == *head->data) {
					current = current->next;
					retrieved = head->data;
					head->next = current->next;
					return true;
				}
				retrieved = current->data;
				previous->next = current->next;
				return true;
			}
			previous = current;
			current = current->next;
		}
		retrieved = NULL;
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
	p
		tr->data = dataptr;                       	// link the node to data


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
}

template <typename T>
bool List<T>::operator==(List<T>& toCompare) {
	if (head == NULL || toCompare.head == NULL || size() != toCompare.size()) {
		return false;
	}

	Node* current = head;
	Node* toCompareCurrent = toCompare.head;


	while (current->next != NULL) {
		if (current->data != toCompareCurrent->data) {
			return false;
		} else {
			current = current->next;
			toCompareCurrent = toCompareCurrent->next;
		}

	}

	return true;
};

template<typename T>
void List<T>::makeEmpty() {

	if (head == NULL) {
		return;
	} else {


		Node* previous = head;
		Node* current = head->next;


		while (current != NULL) {
			delete previous;
			previous = current;
			current = current->next;
		}


		delete previous;
		delete current;
		head = NULL;
	}
};

template<typename T>
void List<T>::intersect(List<T>& listOne, List<T>& listTwo) {
	List intersection;


	Node* currentPtr = listOne.head;

	NodeData* retrieved = NULL;


	while (currentPtr != NULL) {
		if (listTwo.retrieve(currentPtr->data, retrieved) == true) {
			intersection.insert(currentPtr->data);
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
	if (toMerge == toMergeTwo) {
		return;
	}
	Node* currentPtr;
	Node* currentPtrTwo;

	toMerge.size() > toMergeTwo.size() ? *currentPtr = *toMerge.head : *currentPtr = *toMergeTwo.head;
	toMerge.size() < toMergeTwo.size() ? *currentPtrTwo = *toMerge.head : *currentPtrTwo = *toMergeTwo.head;


	while (currentPtr->data != NULL) {

		if (*currentPtr->data < *currentPtrTwo->data) {
			currentPtr = currentPtr->next;
		} else if (*currentPtr->data == *currentPtrTwo->data) {
			currentPtr->next = currentPtrTwo;
			currentPtr = currentPtr->next;
		} else {
			currentPtrTwo->next = currentPtr;
			currentPtrTwo = currentPtrTwo->next;
		}
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


// buildList
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
	T* ptr;
	bool successfulRead;                        	// read good data
	bool success;                               	// successfully insert
	for (;;) {
		ptr = new T;
		successfulRead = ptr->setData(infile);   	// fill the T object
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

