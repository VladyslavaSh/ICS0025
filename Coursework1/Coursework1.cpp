#include "Library.h"


int main()
{
	HEADER_D* pHeaderD = GetStruct4(9, 30);

	cout << "--------------- Task 1 ---------------" << endl;
	PrintDataStructure(pHeaderD);
	cout << endl;

	cout << "--------------- Task 2 ---------------" << endl;
	const int length = 15;
	const char* pItemID[length] = { "Z A", "Z Z", "Z K", "A Z", "A A", "A K", "G Z", "G A", "G K", "M A", "M Ba", "M Bb", "M Z", "M Ba", "Mba"};
	for (int i = 0; i < length; i++) {
		if (i == 13) {
			cout << endl << "--------------- Task 3 ---------------" << endl;
		}
		try {
			pHeaderD = InsertItem(pHeaderD, const_cast <char*> (pItemID[i])); //take const char*, but return just char* (get rid of const)
			cout << "Item " << pItemID[i] << " was inserted. " << endl;
		}
		catch (string error) {
			cout << error << endl;
		}
	}
	cout << endl;

	cout << "--------------- Task 4 ---------------" << endl;
	PrintDataStructure(pHeaderD);
	cout << endl;

	cout << "--------------- Task 5 ---------------" << endl;
	for (int i = 0; i < length; i++) {
		if (i == 13) {
			cout << endl << "--------------- Task 6 ---------------" << endl;
		}
		try {
			pHeaderD = RemoveItem(pHeaderD, const_cast <char*> (pItemID[i])); //take const char*, but return char*
			cout << "Item " << pItemID[i] << " was deleted. " << endl;
		}
		catch (string error) {
			cout << error << endl;
		}
	}
	cout << endl;

	cout << "--------------- Task 7 ---------------" << endl;
	PrintDataStructure(pHeaderD);
	cout << endl;
	
	return 0;
}

