//////////////////////////////  nodedata.h  //////////////////////////////////
// Simple object containing one integer and one character
//#pragma once
#ifndef NODEDATA_H
#define NODEDATA_H

#include <iostream>
#include <fstream>
using namespace std;

//---------------------------  class NodeData  ------------------------------
class NodeData {                                 // incomplete class
	friend ostream& operator<<(ostream &, const NodeData &);

	public:
	NodeData(int n = 0, char c = 'z');       // default constructor
	bool setData();                          // sets data by prompting user
	bool setData(ifstream&);                 // reads data from file

											 // <, > are defined by order of num; if nums are equal, ch is compared
	bool operator<(const NodeData& N) const;
	bool operator>(const NodeData& N) const;
	bool operator==(const NodeData& N) const;
	bool operator!=(const NodeData& N) const;

	// other operators: >=, <= are left to the reader

	private:
	int num;
	char ch;
};

#endif
//////////////////////////////  nodedata.cpp  ////////////////////////////////


//--------------------------  constructor  -----------------------------------
NodeData::NodeData(int n, char c) { num = n; ch = c; }

//-----------------------------  setData  ------------------------------------
// set data by prompting user
bool NodeData::setData() {
	cout << "Please enter an integer: ";   cin >> num;
	cout << "Please enter a character: ";  cin >> ch;
	return true;
}

//-----------------------------  setData  ------------------------------------
// set data from file
bool NodeData::setData(ifstream& infile) {
	infile >> num >> ch;
	return true;
}

//-------------------------------  <  ----------------------------------------
// < defined by value of num; if nums equal, ch is used
bool NodeData::operator<(const NodeData& obj) const {
	if (num < obj.num) return true;
	if (num == obj.num) return ch < obj.ch;
	return false;
}

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator>(const NodeData& obj) const {
	if (num > obj.num) return true;
	if (num == obj.num) return ch > obj.ch;
	return false;
}

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator==(const NodeData& obj) const {
	return num == obj.num && ch == obj.ch;
}

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator!=(const NodeData& obj) const {
	return !(*this == obj);
}

//-------------------------------  <<  ---------------------------------------
// display NodeData object
ostream& operator<<(ostream& output, const NodeData& obj) {
	output << obj.num << ' ' << obj.ch << endl;
	return output;
}