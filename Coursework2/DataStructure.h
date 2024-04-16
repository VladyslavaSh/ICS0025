#pragma once
#include <iostream>
#include <fstream>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
using namespace std;

class DataStructure {
private:
	ITEM9** GetItemsArray();
	void DeleteItem(ITEM9* p);
	void Delete();
	HEADER_D* pHeaderD;
	bool CorrectID(char* pItemID);
	char GetLetter1(char* pItemID);
	char GetLetter2(char* pItemID);
	HEADER_A* CreatepHeaderA(char* pNewItemID);

public:
	DataStructure();
	DataStructure(char* pFilename);
	DataStructure(const DataStructure& Original);
	~DataStructure();

	void TestPrintDataStructure();

	int GetItemsNumber();
	ITEM9* GetItem(char* pID);

	void operator+=(ITEM9* p);
	void operator-=(char* pID);

	DataStructure& operator=(const DataStructure& Right);

	int operator==(DataStructure& Other);
	void Write(char* pFilename);
	friend ostream& operator<<(ostream& ostr, const DataStructure& str);

};

