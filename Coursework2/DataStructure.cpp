#include "DataStructure.h"


// Task 1
DataStructure::DataStructure() {
	pHeaderD = NULL;
}

// Task 2
DataStructure::DataStructure(char* pFilename) {
	pHeaderD = NULL;

	ifstream fin(pFilename, ios::binary);
	if (!fin) {
		string err = "File was not found.";
		throw err;
	}
	int n;
	fin.read((char*)&n, sizeof n); // &n - address where to write n in memory

	int lengthpID;
	int lengthpMonth;

	for (int i = 0; i < n; i++) {
		ITEM9* pItem = new ITEM9;
		pItem->pDate = new DATE3;

		fin.read((char*)&lengthpID, sizeof lengthpID);
		pItem->pID = new char[lengthpID]; // allocate memory for pID exactly as measured above
		fin.read(pItem->pID, lengthpID); // read lengthpID bytes

		fin.read((char*)&pItem->Code, sizeof pItem->Code); // where to read; bytes to read
		fin.read((char*)&pItem->pDate->Day, sizeof pItem->pDate->Day); // int* p = &pItem->pDate->Day - address

		fin.read((char*)&lengthpMonth, sizeof lengthpMonth);
		pItem->pDate->pMonth = new char[lengthpMonth];
		fin.read(pItem->pDate->pMonth, lengthpMonth); // read as much as needed for each pMonth

		fin.read((char*)&pItem->pDate->Year, sizeof pItem->pDate->Year);

		*this += pItem; // *this - DataStructure object
	}
	fin.close();
}

// Task 3
void DataStructure::DeleteItem(ITEM9* p) {
	delete(p->pDate->pMonth);
	delete(p->pDate);
	delete(p->pID);
	delete(p);
	p = NULL;
}

void DataStructure::Delete() {
	HEADER_D* pHeaderD0 = pHeaderD;
	HEADER_D* pHeaderD0_delete;
	while (pHeaderD0 != NULL) { // pNext
		HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
		HEADER_A* pHeaderA_delete;
		while (pHeaderA != NULL) {
			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems; // (ITEM9*) - data type
			ITEM9* pItem9_delete;
			while (pItem9 != NULL) {
				pItem9_delete = pItem9;
				pItem9 = pItem9->pNext;
				DeleteItem(pItem9_delete);
			}
			pHeaderA_delete = pHeaderA;
			pHeaderA = pHeaderA->pNext;
			delete(pHeaderA_delete);
		}
		pHeaderD0_delete = pHeaderD0;
		pHeaderD0 = pHeaderD0->pNext; //next struct HEADER_D
		delete(pHeaderD0_delete); // release memory for pHeaderD (pointer to the first pHeaderD)
	}
	pHeaderD = NULL; // pointer to empty list, address is NULL
}

// destructor
DataStructure :: ~DataStructure() {
	Delete();
}


ITEM9** DataStructure::GetItemsArray() {
	if (pHeaderD == NULL) {
		return NULL;
	}
	else {
		int n = GetItemsNumber();
		ITEM9** ItemsArray = new ITEM9* [n]; // array of pointers to Items (Items addresses)
		HEADER_D* pHeaderD0 = pHeaderD;
		int i = 0;
		while (pHeaderD0 != NULL) { // pNext
			HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
			while (pHeaderA != NULL) {
				ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems; // (ITEM9*) - data type
				while (pItem9 != NULL && i < n) {
					ItemsArray[i] = pItem9; // ITEM9* type, ItemsArray[i] and pItem9 are pointers
					i++;
					pItem9 = pItem9->pNext;
				}
				pHeaderA = pHeaderA->pNext;
			}
			pHeaderD0 = pHeaderD0->pNext;
		}
		return ItemsArray;
	}
}


// Test print 
void DataStructure::TestPrintDataStructure() {

	if (pHeaderD == NULL) {
		cout << "Error: Data struct pHeaderD is empty.";
		return;
	}

	HEADER_D* pHeaderD0 = pHeaderD;
	while (pHeaderD0 != NULL) { // pNext
		cout << pHeaderD0->cBegin << "+" << endl;

		HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
		while (pHeaderA != NULL) {
			cout << " " << pHeaderA->cBegin << endl;

			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems; // (ITEM9*) - data type
			while (pItem9 != NULL) {
				cout << "  " << pItem9->pID << " " << pItem9->Code << " " << pItem9->pDate->Day << " " << pItem9->pDate->pMonth << " " << pItem9->pDate->Year << endl;
				pItem9 = pItem9->pNext;
			}
			pHeaderA = pHeaderA->pNext;
		}
		cout << endl;
		pHeaderD0 = pHeaderD0->pNext;
	}
}

// Task 4 (copy constructor)
DataStructure::DataStructure(const DataStructure& Original) {
	*this = Original;
}


// Task 5
int DataStructure::GetItemsNumber() {
	int i = 0;
	HEADER_D* pHeaderD0 = pHeaderD;
	while (pHeaderD0 != NULL) { // pNext
		HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
		while (pHeaderA != NULL) {
			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems;
			while (pItem9 != NULL) {
				pItem9 = pItem9->pNext;
				i++;
			}
			pHeaderA = pHeaderA->pNext;
		}
		pHeaderD0 = pHeaderD0->pNext;
	}
	return i;
}


// Task 6
ITEM9* DataStructure::GetItem(char* pItemID) {
	HEADER_D* pHeaderD_current = pHeaderD;
	if (CorrectID(pItemID)) {
		while (pHeaderD_current != NULL) { // pNext
			HEADER_A* pHeaderA_current = pHeaderD_current->pHeaderA; // get struct pHeaderA from pHeaderD

			while (pHeaderA_current != NULL) {
				ITEM9* pItem9_current = (ITEM9*)pHeaderA_current->pItems;

				while (pItem9_current != NULL) {
					if (strcmp(pItem9_current->pID, pItemID) == 0) //Item found
					{
						return pItem9_current;
					}
					pItem9_current = pItem9_current->pNext;
				}
				pHeaderA_current = pHeaderA_current->pNext;
			}
			pHeaderD_current = pHeaderD_current->pNext; //next struct HEADER_D
		}
		return NULL;
	}
	else {
		string err = "The ID ";
		err += pItemID;
		err += " presented by user does not follow the formatting rules.";
		throw err;
	}
}


// Task 7
void DataStructure :: operator+=(ITEM9* p) {
	HEADER_D* pHeaderD_current = pHeaderD;
	ITEM9* pItem9_previous = NULL;
	bool find = false;
	if (pHeaderD == NULL) {
		pHeaderD = new HEADER_D;
		pHeaderD->cBegin = GetLetter1(p->pID);
		pHeaderD->pPrior = NULL; // first pHeaderD, no previous
		pHeaderD->pNext = NULL;

		HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
		pHeaderD->pHeaderA = pHeaderA_new;
		pHeaderA_new->pItems = p; // assign new item
		p->pNext = NULL; // only one item, no following item
		return;
	}
	while (pHeaderD_current != NULL) { // pNext

		if (pHeaderD_current->cBegin > GetLetter1(p->pID)) { // "D" > "A", no need to iterate further, put "A" before "D"

			if (pHeaderD_current->pPrior == NULL) { // pHeaderD_current was the first HEADER_D
				HEADER_D* pHeaderD_new = new HEADER_D;
				pHeaderD_new->cBegin = GetLetter1(p->pID);
				pHeaderD_new->pPrior = NULL; // first pHeaderD, no previous
				pHeaderD_new->pNext = pHeaderD_current;
				pHeaderD_current->pPrior = pHeaderD_new;

				HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
				pHeaderD_new->pHeaderA = pHeaderA_new;
				pHeaderD = pHeaderD_new;
				// Add item
				pHeaderA_new->pItems = p; // assign new item
				p->pNext = NULL; // only one item, no following item
				return;
			}
			else { // between pHeaderD_current->pPrior and pHeaderD_current
				HEADER_D* pHeaderD_new = new HEADER_D; // pHeader in the middle
				pHeaderD_new->cBegin = GetLetter1(p->pID);
				pHeaderD_new->pNext = pHeaderD_current;
				pHeaderD_new->pPrior = pHeaderD_current->pPrior;
				pHeaderD_current->pPrior->pNext = pHeaderD_new;
				pHeaderD_current->pPrior = pHeaderD_new;

				HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
				pHeaderD_new->pHeaderA = pHeaderA_new;
				// Add item
				pHeaderA_new->pItems = p; // assign new item
				p->pNext = NULL; // only one item, no following item
				return;
			}
		}
		if (pHeaderD_current->cBegin == GetLetter1(p->pID)) {

			HEADER_A* pHeaderA_current = pHeaderD_current->pHeaderA; // get struct pHeaderA from pHeaderD
			HEADER_A* pHeaderA_previous = NULL;

			while (pHeaderA_current != NULL) {

				if (pHeaderA_current->cBegin > GetLetter2(p->pID)) { // put our pHeaderA before 
					if (pHeaderA_previous == NULL) { //create pHeaderA at the beginning of pHeaderD array
						HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
						pHeaderA_new->pNext = pHeaderA_current;
						pHeaderD_current->pHeaderA = pHeaderA_new;
						// Add item
						pHeaderA_new->pItems = p; // assign new item
						p->pNext = NULL; // only one item, no following item
						return;
					}
					else {
						HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID); //create pHeader in the middle
						pHeaderA_new->pNext = pHeaderA_current;
						pHeaderA_previous->pNext = pHeaderA_new;
						//Add item
						pHeaderA_new->pItems = p; // assign new item
						p->pNext = NULL; // only one item, no following item
						return;
					}
				}

				else if (pHeaderA_current->cBegin == GetLetter2(p->pID)) { //first letter of second word

					ITEM9* pItem9_current = (ITEM9*)pHeaderA_current->pItems; // (ITEM9*) - data type

					while (pItem9_current != NULL) {
						if (strcmp(pItem9_current->pID, p->pID) == 0) //Item found
						{
							find = true;
							string err = "An item with same ID ";
							err += p->pID;
							err += " is already in the data structure.";
							throw err;
						}
						pItem9_previous = pItem9_current;
						pItem9_current = pItem9_current->pNext;
					}

					if (!find) {
						p->pNext = NULL; // the last item points to null
						if (pItem9_previous != NULL) { // use pItem9_previous, because pItem9_current is NULL
							pItem9_previous->pNext = p; // put pNewItem as the last item
						}
						return;
					}
				} // A, B, C and we want to put D     pHeaderA_current->cBegin < GetLetter2(p->pID) & the last pHeaderA
				else if (pHeaderA_current->pNext == NULL) {
					HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
					pHeaderA_current->pNext = pHeaderA_new;
					// Add item
					pHeaderA_new->pItems = p; // assign new item
					p->pNext = NULL; // only one item, no following item
					return;
				}
				pHeaderA_previous = pHeaderA_current;
				pHeaderA_current = pHeaderA_current->pNext;
			}
		}
		else if (pHeaderD_current->pNext == NULL) { // the last pHeaderD
			HEADER_D* pHeaderD_new = new HEADER_D; // pHeader in the middle
			pHeaderD_new->cBegin = GetLetter1(p->pID);
			pHeaderD_new->pNext = NULL; //no further pHeaderD
			pHeaderD_new->pPrior = pHeaderD_current;
			pHeaderD_current->pNext = pHeaderD_new;

			HEADER_A* pHeaderA_new = CreatepHeaderA(p->pID);
			pHeaderD_new->pHeaderA = pHeaderA_new;
			// Add item
			pHeaderA_new->pItems = p; // assign new item
			p->pNext = NULL; // only one item, no following item
			return;
		}

		pHeaderD_current = pHeaderD_current->pNext; //next struct HEADER_D
	}
}


// Task 8
void DataStructure :: operator-=(char* pItemID) {
	HEADER_D* pHeaderD_current = pHeaderD, * pHeaderDNew = pHeaderD;
	if (CorrectID(pItemID)) {
		bool find = false;
		while (pHeaderD_current != NULL) { // pNext

			HEADER_A* pHeaderA_current = pHeaderD_current->pHeaderA; // get struct pHeaderA from pHeaderD
			HEADER_A* pHeaderA_previous = NULL;

			while (pHeaderA_current != NULL) {

				ITEM9* pItem9_current = (ITEM9*)pHeaderA_current->pItems; // (ITEM9*) - data type
				ITEM9* pItem9_previous = NULL;
				while (pItem9_current != NULL) {
					//Item found
					if (strcmp(pItem9_current->pID, pItemID) == 0)
					{
						find = true;

						if (pItem9_current->pNext == NULL) { // check the last item

							DeleteItem(pItem9_current);

							if (pItem9_previous == NULL) { // deleted item was the only item

								if (pHeaderA_previous != NULL) { // there are previous pHeaderA
									pHeaderA_previous->pNext = pHeaderA_current->pNext;
									delete(pHeaderA_current);
								}
								else { // pHeaderA_current is first 
									if (pHeaderA_current->pNext != NULL) { // there are further pHeaderA
										pHeaderD_current->pHeaderA = pHeaderA_current->pNext;
										delete(pHeaderA_current);
									}
									else { // the only pHeaderA -> delete pHeaderD
										delete(pHeaderA_current);
										if (pHeaderD_current->pNext == NULL) { // the last pHeaderD
											if (pHeaderD_current->pPrior != NULL) { // not the first pHeaderD, then pPrior exists
												pHeaderD_current->pPrior->pNext = NULL; // previous pHeaderD become the last
												delete(pHeaderD_current);
											}
											else { // the only pHeaderD
												delete(pHeaderD);
												pHeaderDNew = NULL;
											}
										}
										else { // not the last pHeaderD: first / middle
											if (pHeaderD_current->pPrior == NULL) { // first pHeaderD
												pHeaderDNew = pHeaderD_current->pNext; // point to the second pHeader as first will be deleted
												pHeaderDNew->pPrior = NULL; // set no previous elements for the first element
												delete(pHeaderD_current);
											}
											else { // pHeader in the middle, not the last
												pHeaderD_current->pNext->pPrior = pHeaderD_current->pPrior; // set new next element
												pHeaderD_current->pPrior->pNext = pHeaderD_current->pNext; // set new previous element
												delete(pHeaderD_current);
											}
										}
									}
								}
							}
							else { // the last item, BUT not the only one in struct, at least 2
								pItem9_previous->pNext = NULL; // set previous element pNext to NULL as element was deleted
							}
						}
						else { // not the last Item9 (first / middle)
							if (pItem9_previous == NULL) { // the first item in struct
								pHeaderA_current->pItems = pItem9_current->pNext; // move pointer to the next item
								DeleteItem(pItem9_current);
							}
							else { // item in the middle
								pItem9_previous->pNext = pItem9_current->pNext;
								DeleteItem(pItem9_current);
							}
						}
						pHeaderD = pHeaderDNew;
						return;
					}
					pItem9_previous = pItem9_current;
					pItem9_current = pItem9_current->pNext;
				}
				pHeaderA_previous = pHeaderA_current;
				pHeaderA_current = pHeaderA_current->pNext;
			}
			pHeaderD_current = pHeaderD_current->pNext; //next struct HEADER_D
		}
		if (!find) {
			string err = "Item with the specified ID ";
			err += pItemID;
			err += " does not exist.";
			throw err;
		}
	}
	else {
		string err = "The ID ";
		err += pItemID;
		err += " presented by user does not follow the formatting rules.";
		throw err;
	}
}


// Task 9
DataStructure& DataStructure :: operator=(const DataStructure& Right) { // get and return reference to data struct
	Delete(); // make sure that the data struct is empty
	if (Right.pHeaderD == NULL) {
		pHeaderD = NULL;
		return *this; // data struct object returns through reference
	}

	HEADER_D* Right_pHeaderD = Right.pHeaderD;
	while (Right_pHeaderD != NULL) { // pNext

		HEADER_A* pHeaderA = Right_pHeaderD->pHeaderA; // get struct pHeaderA from pHeaderD
		while (pHeaderA != NULL) {

			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems;
			while (pItem9 != NULL) {
				ITEM9* pItem = new ITEM9;
				pItem->pDate = new DATE3;

				int lengthpID = strlen(pItem9->pID) + 1;
				pItem->pID = new char[lengthpID]; // array of chars of lengthpID
				strcpy_s(pItem->pID, lengthpID, pItem9->pID);

				pItem->Code = pItem9->Code;
				pItem->pDate->Day = pItem9->pDate->Day;
				pItem->pDate->Year = pItem9->pDate->Year;

				int lengthpMonth = strlen(pItem9->pDate->pMonth) + 1;
				pItem->pDate->pMonth = new char[lengthpMonth];
				strcpy_s(pItem->pDate->pMonth, lengthpMonth, pItem9->pDate->pMonth);

				*this += pItem;
				pItem9 = pItem9->pNext;
			}
			pHeaderA = pHeaderA->pNext;
		}
		Right_pHeaderD = Right_pHeaderD->pNext; //next struct HEADER_D
	}
	return *this;
}

// Task 10
int DataStructure :: operator==(DataStructure& Other) {
	int n1 = GetItemsNumber(); // our struct, same as this->GetItemsNumber()
	int n2 = Other.GetItemsNumber(); // other struct
	if (n1 == n2) {
		ITEM9** ItemArray1 = GetItemsArray();
		ITEM9** ItemArray2 = Other.GetItemsArray();
		for (int i = 0; i < n1; i++) {
			bool find = false;
			for (int j = 0; j < n2; j++) {
				if (strcmp(ItemArray1[i]->pID, ItemArray2[j]->pID) == 0 &&
					ItemArray1[i]->Code == ItemArray2[j]->Code &&
					ItemArray1[i]->pDate->Day == ItemArray2[j]->pDate->Day &&
					strcmp(ItemArray1[i]->pDate->pMonth, ItemArray2[j]->pDate->pMonth) == 0 &&
					ItemArray1[i]->pDate->Year == ItemArray2[j]->pDate->Year) {
					find = true;
					break;
				}
			}
			if (!find) {
				delete []ItemArray1; // delete array of items
				delete []ItemArray2;
				return 0;
			}
		}
		delete []ItemArray1;
		delete []ItemArray2;
		return 1;
	}
	else {
		return 0;
	}
}


// Task 11
void DataStructure::Write(char* pFilename) {
	if (pHeaderD == NULL) {
		string err = "Cannot save structure into file as it is empty.";
		throw err;
	}
	ofstream fout(pFilename, ios::binary); // ofstream - output file stream, open file to write there
	int n = GetItemsNumber(); // first we will write the number of items, so get it
	fout.write((char*)&n, sizeof n); // address from where to read in memory - &n; number of bytes to read in memory

	ITEM9** ItemArray = GetItemsArray();
	for (int i = 0; i < n; i++) {
		int lengthpID = strlen(ItemArray[i]->pID) + 1; // + 1 -> /0 - indicator of the line end
		fout.write((char*)&lengthpID, sizeof lengthpID); // read from address &lengthpID and write the lengthpID itself
		fout.write(ItemArray[i]->pID, lengthpID); // write the pID that has length of lengthpID

		fout.write((char*)&ItemArray[i]->Code, sizeof ItemArray[i]->Code);
		fout.write((char*)&ItemArray[i]->pDate->Day, sizeof ItemArray[i]->pDate->Day);

		int lengthpMonth = strlen(ItemArray[i]->pDate->pMonth) + 1; // to know how many bytes to read
		fout.write((char*)&lengthpMonth, sizeof lengthpMonth); //sizeof counts just length of char
		fout.write(ItemArray[i]->pDate->pMonth, lengthpMonth); // ItemArray[i]->pDate->pMonth is a line alreday

		fout.write((char*)&ItemArray[i]->pDate->Year, sizeof ItemArray[i]->pDate->Year);
	}
	delete []ItemArray; // delete array of items
	fout.close();
}


// Task 12 
ostream& operator<<(ostream& ostr, const DataStructure& str) { // cout - variable of class ostream, ostr will be cout: cout << *pStruct3
	if (str.pHeaderD == NULL) {
		ostr << "Error: Data struct pHeaderD is empty.";
		return ostr;
	}

	int i = 1;
	HEADER_D* pHeaderD0 = str.pHeaderD;
	while (pHeaderD0 != NULL) { // pNext

		HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
		while (pHeaderA != NULL) {

			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems; // (ITEM9*) - data type
			while (pItem9 != NULL) {
				ostr << i << ")" << pItem9->pID << " " << pItem9->Code << " " << pItem9->pDate->Day << " " << pItem9->pDate->pMonth << " " << pItem9->pDate->Year << endl;
				pItem9 = pItem9->pNext;
				i++;
			}
			pHeaderA = pHeaderA->pNext;
		}
		pHeaderD0 = pHeaderD0->pNext; //next struct HEADER_D
	}
	if (i == 1) {
		ostr << "Error: No items in data struct pItem9.";
	}
	return ostr;
}




bool DataStructure::CorrectID(char* pItemID)
{
	if (pItemID == NULL || strlen(pItemID) < 3 || (!isupper(pItemID[0]))) {
		return false;
	}
	bool state = false;
	bool second_upper = false;
	for (int i = 0; i < strlen(pItemID); i++) {
		if (!isalpha(pItemID[i]) && pItemID[i] != '-' && pItemID[i] != ' ') {
			return false;
		}
		if (pItemID[i] == ' ') {
			if (state) {
				return false;
			}
			state = true;
			i++;
			if (i < strlen(pItemID) && isupper(pItemID[i])) { //check if not the last symbol
				second_upper = true;
			}
			else {
				return false;
			}
		}
	}
	return second_upper;
}

char DataStructure::GetLetter1(char* pItemID) {
	return pItemID[0];
}

char DataStructure::GetLetter2(char* pItemID) {
	char* f = strchr(pItemID, ' '); // pointer to space
	int n = f - pItemID + 1;
	return pItemID[n];
}

HEADER_A* DataStructure::CreatepHeaderA(char* pNewItemID) {
	HEADER_A* pHeaderA_new = new HEADER_A;
	pHeaderA_new->pItems = NULL;
	pHeaderA_new->cBegin = GetLetter2(pNewItemID);
	pHeaderA_new->pNext = NULL;

	//ITEM9* pNewItem = (ITEM9*)::GetItem(9, pNewItemID); // create new item
	//pNewItem->pNext = NULL; // the last item points to null
	//pHeaderA_new->pItems = pNewItem; // put pNewItem as the last item

	return pHeaderA_new;
}
