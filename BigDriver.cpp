
#include "NodeData.h"
#include "Employee.h"
#include "LinkedListFinal.h"

//extern class Employee;
using namespace std;

int main() {
	std::cout << "Hello, World!" << std::endl;


	List<int> list1;
	int one = 1;
	int three = 3;
	list1.insert(&one);
	list1.insert(&three);
	cout << "list1: " << list1 << endl; //13

	List<int> list2;
	int five = 5;
	int fifteen = 15;
	list2.insert(&five);
	list2.insert(&fifteen);

	List<int> list4;
	int two = 2;
	int four = 4;
	list4.insert(&five);
	list4.insert(&fifteen);

	int find = 0;

	cout << "retrieving three from list1. List1: " << list1 << ", the number to find: " << three << endl;
	list1.retrieve(&three, find);

	cout << "found: " << find << endl << endl; //3

	cout << "list1: " << list1 << endl;
	cout << "list2: " << list2 << endl;
	cout << "list4: " << list4 << endl << endl;

	cout << "list1 == list2: " << ((list1 == list2) ? "true" : "false") << endl; //false
	cout << "list2 == list4: " << ((list2 == list4) ? "true" : "false") << endl << endl; //true

	list4.insert(&two);
	list4.insert(&four);

	cout << "list2: " << list2 << endl;

	cout << "made new list, list3. merging list1, list2, into list3." << endl;
	List<int> list3;
	list3.merge(list1, list2);
	cout << list3.size() << endl << endl;

	cout << "list3: " << list3 << endl; //13515
	cout << "list1: " << list1 << endl; //null
	cout << "list2: " << list2 << endl << endl; //null

	cout << "recreating list1, list2. merging list1, list2, into list1." << endl;
	list1.insert(&one);
	list1.insert(&three);
	list2.insert(&five);
	list2.insert(&fifteen);

	cout << "list1: " << list1 << endl; //13
	cout << "list2: " << list2 << endl << endl; //515

	list1.merge(list3, list2);

	cout << "list1: " << list1 << endl; //13515
	cout << "list2: " << list2 << endl; //null
	cout << "list3: " << list3 << endl << endl; //13515 (unaffected)

	cout << "list1.merge(list1, list1)" << endl;
	//list1.merge(list1, list1);

	cout << "list1: " << list1 << endl; //13515 (unaffected)

	cout << "list2.merge(list1, list1)" << endl;
	//ist2.merge(list1, list1); // this is broken...

	cout << "list1: " << list1 << endl; //null
	cout << "list2: " << list2 << endl << endl; //13515

	cout << "list1: " << list1 << endl; //null
	cout << "list4: " << list4 << endl; //24515
	cout << "doing list1 = list4, assignment operator." << endl;
	list1 = list4; //list1 now equals 24515
	cout << "list1: " << list1 << endl; //24515
	cout << "list4: " << list4 << endl << endl; //24515
	cout << "list1 == list4: " << ((list1 == list4) ? "true" : "false") << endl << endl; //true

	int eight = 8;
	int six = 6;
	list1.insert(&one);
	list1.insert(&eight);
	list1.insert(&six);
	cout << "inserted one, six, eight into list1." << endl;



	bool success;
	cout << "list1: " << list1 << endl; //12456815
	cout << "trying to remove four" << endl;
	success = list1.remove(&four, find);
	if (success) cout << "removed from list1: " << find << endl;         //should remove four
	else cout << "didn't find " << four << " in the list" << endl;
	cout << "list1: " << list1 << endl << endl;
	cout << "trying to remove five" << endl;
	success = list1.remove(&five, find);
	if (success) cout << "removed from list1: " << find << endl;         //should remove five the first time
	else cout << "didn't find " << five << " in the list" << endl;
	cout << "list1: " << list1 << endl << endl;
	success = list1.remove(&five, find);
	if (success) cout << "removed from list1: " << find << endl;         //should not remove five the second time
	else cout << "didn't find " << five << " in the list" << endl;
	cout << "list1: " << list1 << endl << endl;
	
	cout << "list1: " << list1 << endl;
	cout << "list2: " << list2 << endl; // breaks here 
	list3.intersect(list1, list2);
	cout << "list3.intersect(list1, list2): " << endl;
	cout << "list1: " << list1 << endl; //126815
	cout << "list2: " << list2 << endl; //13515
	cout << "list3: " << list3 << endl << endl; //115
	list1.intersect(list1, list2);
	cout << "list1.intersect(list1, list2): " << endl;
	cout << "list1: " << list1 << endl; //115
	cout << "list2: " << list2 << endl; //13515
	
	//system("pause");
	cout << "building company 1 of employees" << endl;
	List<Employee> company1;
	ifstream file;
	file.open("data.txt");
	if (!file) {

		cout << "File could not be opened";
		return 1;
	}
	company1.buildList(file);
	cout << "company1: " << endl << company1 << endl << endl; //look at data.txt, should be ordered by last name

	Employee store;
	Employee* e = new Employee("egal", "ali", 1563, 150000);
	cout << "about to remove: " << *e << "from company1." << endl;
	company1.remove(e, store);
	cout << company1 << endl; //should now lack egal ali
	cout << "removed: " << store << endl << endl; //the object we removed
	delete e;

	cout << "building company2 of NodeData" << endl;
	List<NodeData> company2;
	ifstream file2("data2.txt");
	company2.buildList(file2);
	cout << "company2:" << endl << company2 << endl; //look at data2.txt, should be in order by first number

	cout << "list1.makeEmpty() twice, see if it is a bad idea" << endl; //just trying to makeEmpty twice, see if our program crashes
	list1.makeEmpty();
	list1.makeEmpty();
	cout << "nah we gucci" << endl << endl; //if we got here the program didn't crash, look for errors associated with doing this though

	List<Employee> companyCopy(company1);

	cout << companyCopy << endl << endl << endl;

	cout << "************SILENT TESTING SUITE OF EMPTY THINGS**************" << endl;
	List<int> list5;
	List<int> list6;
	List<int> list7;

	//    int blankInsert;
	//    list5.insert(blankInsert); //this is stupid don't do this
	cout << "removing" << endl;
	list5.remove(&five, find); // breaks here 
	cout << "list5: " << list5 << endl << endl;
	cout << "retrieving" << endl;
	list5.retrieve(&five, find);
	cout << "list5: " << list5 << endl << endl;
	cout << "merge" << endl;
	list5.merge(list6, list7);
	cout << "list5: " << list5 << endl;
	cout << "list6: " << list6 << endl;
	cout << "list7: " << list7 << endl << endl;
	cout << "intersect" << endl;
	list5.intersect(list6, list7);
	cout << "list5: " << list5 << endl;
	cout << "list6: " << list6 << endl;
	cout << "list7: " << list7 << endl << endl;
	cout << "isEmpty" << endl;
	cout << (list5.isEmpty() ? "true" : "false") << endl;
	cout << "makeEmpty" << endl;
	list5.makeEmpty();
	cout << endl << "list2: " << list2 << "    list5: " << list5 << endl;
	cout << "list5==list2" << endl;
	cout << ((list5 == list2) ? "true - equal to" : "false - not equal to") << endl;
	cout << "list5==list6" << endl;
	cout << ((list5 == list6) ? "true - equal to" : "false - not equal to") << endl;
	cout << "list5!=list2" << endl;
	cout << ((list5 != list2) ? "true - not equal to" : "false - equal to") << endl;
	cout << "list5!=list6" << endl;
	cout << ((list5 != list6) ? "true - not equal to" : "false - equal to") << endl;

	cout << "made it to the end, no runtime errors, no infinite loops!" << endl;

	system("Pause");
	
	return 0;
}
