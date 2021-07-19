#ifndef __CLASS_H_
#define __CLASS_H_

#include"systemData.h"

class Book {
private:
	char* bookTitle;
	char* bookAuthor;
	char* bookCode;
	int remainBook;
	int borrowedBook;
	int reservedBook;
public:
	Book* next;
	Book* prev;
	~Book()
	{
		delete[] bookTitle;
		delete[] bookAuthor;
		delete[] bookCode;
	}
	int BookRegist(char* bookTitle, char* bookAuthor, char* bookCode, int remainBook, int borrowedBook, int reservedBook);
	void ShowBookInfo(void);
	char* GetTitle(void);
	char* GetAuthor(void);
	char* GetCode(void);
	void DeleteBookInfo(void);
	void EnterBookInfo(char* bookTitle, char* bookAuthor, char* bookCode);
	int GetRemainBook(void);
	int GetBorrowedBook(void);
	int GetReservedBook(void);
	void BorrowBook(void);
	void ReturnBook(void);
	void ReserveBook(void);
	void BorrowReservedBook(void);
	void InitRemainBook(int remain);
	void InitBorrowedBook(void);
	void InitReservedBook(void);
};

#endif