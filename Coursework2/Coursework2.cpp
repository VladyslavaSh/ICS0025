#include "DataStructure.h"


int main() {

	// Task 1
	DataStructure* pStruct1 = new DataStructure();

	// Task 2
	// GetItem from DLL
	const int length = 10;
	//const char* pItemID[length] = { "Z A", "Z Z", "Z K", "A Z", "A A", "A K", "G Z", "G A", "G K", "M A"};
	for (int i = 0; i < length; i++) {
		try {
			ITEM9* p = (ITEM9*)GetItem(9);//, const_cast <char*> (pItemID[i]));
			*pStruct1 += p;
			cout << "Item " << p->pID << " was inserted. " << endl;
		}
		catch (string error) {
			cout << error << endl;
		}
	}
	cout << endl;

	// Task 3
	cout << *pStruct1 << endl;
	/*
	Data->TestPrintDataStructure();
	int n = TestStruct->GetItemsNumber();
	ITEM9** ItemArray = TestStruct->GetItemsArray();
	cout << endl;
	for (int i = 0; i < n; i++) {
		//cout << ItemArray[i]->pID << endl;
	}
	*/


	// Task 4
	cout << "Count: " << pStruct1->GetItemsNumber() << endl;

	// Task 5
	char arr[] = "Light Cyan";
	ITEM9* p = pStruct1->GetItem(arr);
	if (p != NULL) {
		cout << "Received item: " << p->pID << endl;
	}
	else {
		cout << "There is no such ID " << arr << endl;
	}

	// Task 6
	char arr2[] = "X X";
	ITEM9* p2 = pStruct1->GetItem(arr2);
	if (p2 != NULL) {
		cout << "Received item: " << p2->pID << endl;
	}
	else {
		cout << "There is no such ID " << arr2 << endl;
	}

	// Task 7: Using the copy constructor creates the copy of current structure
	DataStructure *pStruct2 = new DataStructure(*pStruct1);
	cout << *pStruct2;

	// Task 8
	const int length2 = 3;
	const char* toRemove[length2] = { "Banana Mania", "Persian Green", "Vegas Gold" };
	for (int i = 0; i < length2; i++) {
		try {
			*pStruct1 -= (char*) const_cast <char*> (toRemove[i]); // const_cast from const makes char*
			cout << "Item " << toRemove[i] << " was deleted. " << endl;
		}
		catch (string error) {
			cout << error << endl;
		}
	}
	cout << endl;

	// Task 9: Compares the initial structure (now with 7 items) with the copy structure.
	//cout << *pStruct1 << endl; 
	//cout << *pStruct2 << endl;

	if (*pStruct1 == *pStruct2) {
		cout << "Structures are same." << endl;
	}
	else {
		cout << "Structures are different." << endl;
	}

	// Task 10: Writes the initial structure (now 7 items) into a data file.
	char filename[] = "a.txt";
	pStruct1->Write(filename);

	// Task 11: Creates a new structure from this data file and compares it with initial stucture.
	DataStructure *pStruct3 = new DataStructure(filename);
	if (*pStruct1 == *pStruct3) {
		cout << "Structures are same." << endl;
	}
	else {
		cout << "Structures are different." << endl;
	}

	// Task 12: . Asssigns to the structure just created (7 items) the copy created in step 7 (10 items) and prints the result.
	*pStruct3 = *pStruct2;
	cout << *pStruct3;

	delete(pStruct1);
	delete(pStruct2);
	delete(pStruct3);

	return 0;
}

