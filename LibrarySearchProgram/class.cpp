#include "common.h"
#include "class.h"
#include "systemData.h"

int Book::BookRegist(char* bookTitle, char* bookAuthor, char* bookCode, int remainBook, int borrowedBook, int reservedBook)
{
	if (this->bookTitle = new char[strlen(bookTitle) + 1])
	{
		if (this->bookAuthor = new char[strlen(bookAuthor) + 1])
		{
			if (this->bookCode = new char[strlen(bookCode) + 1])
			{
				strcpy(this->bookTitle, bookTitle);
				strcpy(this->bookAuthor, bookAuthor);
				strcpy(this->bookCode, bookCode);
				this->remainBook = remainBook;
				this->borrowedBook = borrowedBook;
				this->reservedBook = reservedBook;
				return 1;
			}
		}
	}
	cout << "ERROR : LACK OF HEAP MEMORY" << endl;
	return 0;
}

char* Book::GetTitle(void)
{
	if (!strlen(bookTitle))
		return NULL;
	return bookTitle;
}

char* Book::GetAuthor(void)
{
	if (!strlen(bookAuthor))
		return NULL;
	return bookAuthor;
}

char* Book::GetCode(void)
{
	if (!strlen(bookCode))
		return NULL;
	return bookCode;
}

void Book::DeleteBookInfo(void)
{
	strset(bookTitle, NULL);
	strset(bookAuthor, NULL);
	strset(bookCode, NULL);
	return;
}

void Book::EnterBookInfo(char* bookTitle, char* bookAuthor, char* bookCode)
{
	if(strlen(bookTitle)<=MAX_STR_LEN)
		if (strlen(bookAuthor) <= MAX_STR_LEN)
			if (strlen(bookCode) <= MAX_STR_LEN)
			{
				strcpy(this->bookTitle, bookTitle);
				strcpy(this->bookAuthor, bookAuthor);
				strcpy(this->bookCode, bookCode);
			}
			else
			{
				cout << "Excess String Length";
				return;
			}
}

void Book::ShowBookInfo(void)
{
	cout << "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收" << endl;
	cout << "早 Book Title : " << bookTitle << endl;
	cout << "早 Book Author : " << bookAuthor << endl;
	cout << "早 Book Code : " << bookCode << endl; 
	cout << "早 Remain : " << remainBook << endl;
	cout << "早 Borrowed : " << borrowedBook << endl;
	cout << "早 Reserved : " << reservedBook << endl;
	cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收" << endl;
}

int Book::GetRemainBook(void)
{
	return remainBook;
}

int Book::GetBorrowedBook(void)
{
	return borrowedBook;
}

int Book::GetReservedBook(void)
{
	return reservedBook;
}

void Book::BorrowBook(void)
{
	if (remainBook > 0)
	{
		remainBook--;
		borrowedBook++;
		cout << bookTitle << " is borrowed";
	}
}

void Book::ReturnBook(void)
{
	if (borrowedBook > 0)
	{
		borrowedBook--;
		remainBook++;
		cout << bookTitle << " is returned";
	}
}

void Book::ReserveBook(void)
{
	if (remainBook == 0)
	{
		reservedBook++;
		cout << bookTitle << " is reserved";
	}
}

void Book::BorrowReservedBook(void)
{
	if (reservedBook > 0)
	{
		reservedBook--;
	}
	return;
}

void Book::InitRemainBook(int remain)
{
	remainBook = remain;
	return;
}

void Book::InitBorrowedBook(void)
{
	borrowedBook = 0;
	return;
}

void Book::InitReservedBook(void)
{
	reservedBook = 0;
	return;
}