#ifndef __PERSONAL_DATA_CLASS_H_
#define __PERSONAL_DATA_CLASS_H_

#include "systemData.h"
#include "class.h"
#include <time.h>

class User {
private:
	char ID[MAX_ID_LEN];
	char PW[MAX_ID_LEN];
	int borrowBookNum;
	int reserveBookNum;
	time_t borrowBookDate[MAX_BORROW_NUM];
	time_t borrowBanDate;
	Book* BorrowBookPtr[MAX_BORROW_NUM];
	Book* ReserveBookPtr[MAX_BORROW_NUM];
public:
	User* next;
	char* GetID(void);
	char* GetPW(void);
	void EnterID(char* ID);
	void EnterPW(char* PW);
	void BorrowBook(Book* BookPtr);
	void ReturnBook(Book* BookPtr);
	void ReserveBook(Book* BookPtr);
	int GetBorrowBookNum(void);
	int GetReserveBookNum(void);
	time_t GetBorrowBookDate(int idx);
	time_t GetBorrowBanDate(void);
	Book* GetBorrowBookPtr(int idx);
	Book* GetReserveBookPtr(int idx);
	void InitBorrowBookNum(int borrowBookNum);
	void InitReservedBookNum(int reservedBookNum);
	void InitBorrowBookDate(int idx, time_t borrowBookDate);
	void InitBorrowBanDate(time_t borrowBanDate);
	void InitBorrowBookPtr(int idx, Book* BorrowBookPtr);
	void InitReserveBookPtr(int idx, Book* ReserveBookPtr);
	void ShowBorrowBook(void);
	void ChoiceBookToReturn(void);
};

class Manager {
private:
	char ID[MAX_ID_LEN];
	char PW[MAX_ID_LEN];
public:
	Manager* next;
	char* GetID(void);
	char* GetPW(void);
	void EnterID(char* ID);
	void EnterPW(char* PW);
};

#endif