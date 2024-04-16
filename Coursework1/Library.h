#pragma once
#include <iostream>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
using namespace std;
void PrintDataStructure(HEADER_D* pHeaderD);
void TestPrintDataStructure(HEADER_D* pHeaderD);
HEADER_D* RemoveItem(HEADER_D* pHeaderD, char* pItemID);
bool CorrectID(char* pItemID);
HEADER_D* InsertItem(HEADER_D* pHeaderD, char* pNewItemID = 0);
char GetLetter1(char* pItemID);
char GetLetter2(char* pItemID);
HEADER_A* CreatepHeaderA(char* pNewItemID);
void DeleteItem(ITEM9* p);

