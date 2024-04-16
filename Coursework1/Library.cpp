#include "Library.h"


// Task 1
void PrintDataStructure(HEADER_D* pHeaderD)
{
	if (pHeaderD == NULL) {
		cout << "Error: Data struct pHeaderD is empty.";
		return;
	}

	int i = 1;
	HEADER_D* pHeaderD0 = pHeaderD;
	while (pHeaderD0 != NULL) { // pNext

		HEADER_A* pHeaderA = pHeaderD0->pHeaderA; // get struct pHeaderA from pHeaderD
		while (pHeaderA != NULL) {

			ITEM9* pItem9 = (ITEM9*)pHeaderA->pItems; // (ITEM9*) - data type
			while (pItem9 != NULL) {
				cout << i << ")" << pItem9->pID << " " << pItem9->Code << " " << pItem9->pDate->Day << " " << pItem9->pDate->pMonth << " " << pItem9->pDate->Year << endl;
				pItem9 = pItem9->pNext;
				i++;
			}
			pHeaderA = pHeaderA->pNext;
		}
		pHeaderD0 = pHeaderD0->pNext; //next struct HEADER_D
	}
	if (i == 1) {
		cout << "Error: No items in data struct pItem9.";
	}
}
// Test function
void TestPrintDataStructure(HEADER_D* pHeaderD) {

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
		pHeaderD0 = pHeaderD0->pNext; //next struct HEADER_D
	}
}


// Task 3
HEADER_D* RemoveItem(HEADER_D* pHeaderD, char* pItemID)
{
	HEADER_D *pHeaderD_current = pHeaderD, *pHeaderDNew = pHeaderD;
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

							if (pItem9_previous == NULL) { // p_current was the only item

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
						return pHeaderDNew;
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
	return pHeaderDNew;
}


bool CorrectID(char* pItemID)
{
	if (pItemID == NULL || strlen(pItemID) < 3 || (!isupper(pItemID[0]))) {
		return false;
	}
	bool space = false;
	bool second_upper = false;
	for (int i = 0; i < strlen(pItemID); i++) {
		if (!isalpha(pItemID[i]) && pItemID[i] != '-' && pItemID[i] != ' ') {
			return false;
		}
		if (pItemID[i] == ' ') {
			if (space) { // only one space is allowed
				return false;
			}
			space = true;
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


// Task 2
HEADER_D* InsertItem(HEADER_D* pHeaderD, char* pNewItemID) {
	HEADER_D* pHeaderD_current = pHeaderD, * pHeaderDNew = pHeaderD;
	if (CorrectID(pNewItemID)) {
		ITEM9* pItem9_previous = NULL;
		bool find = false;
		while (pHeaderD_current != NULL) { // pNext
			if (pHeaderD_current->cBegin > GetLetter1(pNewItemID)) { // there always letters before first letter of new item
				if (pHeaderD_current->pPrior == NULL) { // first pHeaderD
					HEADER_D* pHeaderD_new = new HEADER_D;
					pHeaderD_new->cBegin = GetLetter1(pNewItemID);
					pHeaderD_new->pPrior = NULL; // first pHeaderD, no previous
					pHeaderD_new->pNext = pHeaderD_current;
					pHeaderD_current->pPrior = pHeaderD_new;

					HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID);
					pHeaderD_new->pHeaderA = pHeaderA_new;

					return pHeaderD_new;
				}
				else { // pHeader in the middle
					HEADER_D* pHeaderD_new = new HEADER_D; 
					pHeaderD_new->cBegin = GetLetter1(pNewItemID);
					pHeaderD_new->pNext = pHeaderD_current;
					pHeaderD_new->pPrior = pHeaderD_current->pPrior;
					pHeaderD_current->pPrior->pNext = pHeaderD_new;
					pHeaderD_current->pPrior = pHeaderD_new;

					HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID);
					pHeaderD_new->pHeaderA = pHeaderA_new;

					return pHeaderD;
				}
			}
			if (pHeaderD_current->cBegin == GetLetter1(pNewItemID)) {

				HEADER_A* pHeaderA_current = pHeaderD_current->pHeaderA; // get struct pHeaderA from pHeaderD
				HEADER_A* pHeaderA_previous = NULL;

				while (pHeaderA_current != NULL) {
					if (pHeaderA_current->cBegin > GetLetter2(pNewItemID)) {
						if (pHeaderA_previous == NULL) { //create pHeaderA at the beginning of pHeaderD
							HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID);
							pHeaderA_new->pNext = pHeaderA_current;
							pHeaderD_current->pHeaderA = pHeaderA_new;
							return pHeaderD;
						}
						else {
							HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID); //create pHeader in the middle
							pHeaderA_new->pNext = pHeaderA_current;
							pHeaderA_previous->pNext = pHeaderA_new;
							return pHeaderD;
						}
					}
					else if (pHeaderA_current->cBegin == GetLetter2(pNewItemID)) { //first letter of second word
						ITEM9* pItem9_current = (ITEM9*)pHeaderA_current->pItems; // (ITEM9*) - data type
						while (pItem9_current != NULL) {
							if (strcmp(pItem9_current->pID, pNewItemID) == 0) //Item found
							{
								find = true;
								string err = "An item with same ID ";
								err += pNewItemID;
								err += " is already in the data structure.";
								throw err;
							}
							pItem9_previous = pItem9_current;
							pItem9_current = pItem9_current->pNext;
						}
						if (!find) {
							ITEM9* pNewItem = (ITEM9*)GetItem(9, pNewItemID); // create new item
							pNewItem->pNext = NULL; // the last item points to null
							if (pItem9_previous != NULL) {
								pItem9_previous->pNext = pNewItem; // put pNewItem as the last item
							}
							return pHeaderD;
						}
					}
					else if (pHeaderA_current->pNext == NULL) { // the last pHeaderA
						HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID);
						pHeaderA_current->pNext = pHeaderA_new;
						return pHeaderD;
					}
					pHeaderA_previous = pHeaderA_current;
					pHeaderA_current = pHeaderA_current->pNext;
				}
			}
			else if (pHeaderD_current->pNext == NULL) { // pHeaderD is the last pHeaderD
				HEADER_D* pHeaderD_new = new HEADER_D;
				pHeaderD_new->cBegin = GetLetter1(pNewItemID);
				pHeaderD_new->pNext = NULL; // no further pHeaderD
				pHeaderD_new->pPrior = pHeaderD_current;
				pHeaderD_current->pNext = pHeaderD_new;

				HEADER_A* pHeaderA_new = CreatepHeaderA(pNewItemID);
				pHeaderD_new->pHeaderA = pHeaderA_new;

				return pHeaderD;
			}

			pHeaderD_current = pHeaderD_current->pNext; //next struct HEADER_D
		}
	}
	else {
		string err = "The ID ";
		err += pNewItemID;
		err += " presented by user does not follow the formatting rules.";
		throw err;
	}
	return pHeaderDNew;
}

// LOOK AT THIS
char GetLetter1(char* pItemID) {
	return pItemID[0];
}

char GetLetter2(char* pItemID) {
	char* f = strchr(pItemID, ' '); // find space and return pointer to space (address)
	int n = f - pItemID + 1; // number of the next element after space in the array
	return pItemID[n];
}

HEADER_A* CreatepHeaderA(char* pNewItemID) {
	ITEM9* pNewItem = (ITEM9*)GetItem(9, pNewItemID); // create new item
	pNewItem->pNext = NULL; // the last item points to null

	HEADER_A* pHeaderA_new = new HEADER_A; // create new HeaderA
	pHeaderA_new->cBegin = GetLetter2(pNewItemID);
	pHeaderA_new->pNext = NULL;
	pHeaderA_new->pItems = pNewItem; // put pNewItem as the last item

	return pHeaderA_new;
}

void DeleteItem(ITEM9* p) {
	// use delete on following (others cam empty themselfs):
	delete(p->pDate->pMonth);
	delete(p->pDate);
	delete(p->pID);
	delete(p);
	p = NULL;
}
