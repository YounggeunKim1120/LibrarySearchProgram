#include "common.h"
#include "personalDataClass.h"
#include "systemData.h"

char* User::GetID(void)
{
	return ID;
}

char* User::GetPW(void)
{
	return PW;
}

void User::EnterID(char* ID)
{
	strcpy(this->ID, ID);
	return;
}

void User::EnterPW(char* PW)
{
	strcpy(this->PW, PW);
	return;
}

void User::BorrowBook(Book* BookPtr)
{
	if (borrowBookNum < MAX_BORROW_NUM)
	{
		if (borrowBanDate <= 0)
		{
			if (BookPtr->GetRemainBook() > 0)
			{
				if (BookPtr->GetRemainBook() - BookPtr->GetReservedBook() > 0)
				{
					borrowBookNum++;
					BorrowBookPtr[borrowBookNum - 1] = BookPtr;
					time(&borrowBookDate[borrowBookNum - 1]);
				}
				else
				{
					for (int i = 0; i < reserveBookNum; i++)
					{
						if (BookPtr == ReserveBookPtr[i])
						{
							borrowBookNum++;
							BorrowBookPtr[borrowBookNum - 1] = BookPtr;
							time(&borrowBookDate[borrowBookNum - 1]);
							ReserveBookPtr[i] = NULL;
							reserveBookNum--;
							BookPtr->BorrowReservedBook();
							break;
						}
					}
				}
				cout << "Borrowing Complete" << endl;
			}
		}
	}
}

void User::ReturnBook(Book* BookPtr)
{
	time_t tempBanDate;

	for (int i = 0; i < borrowBookNum; i++)
	{
		if (BookPtr == BorrowBookPtr[i])
		{
			time_t now;
			time(&now);
			BookPtr->ReturnBook();
			tempBanDate = 7 * SEC_PER_DATE - (now - borrowBookDate[i]);
			if (tempBanDate <= borrowBanDate)
				borrowBanDate = tempBanDate;
			BorrowBookPtr[i] = NULL;
			borrowBookDate[i] = NULL;
			borrowBookNum--;
			cout << "Returning Complete" << endl;
			system("pause");
			if (borrowBanDate > 0)
				cout << "Borrowing Is Banned For " << borrowBanDate / SEC_PER_DATE << " Day" << endl;
			return;
		} 
	}
}

void User::ReserveBook(Book* BookPtr)
{
	if (BookPtr->GetRemainBook() == 0)
	{
		if (borrowBanDate <= 0)
		{
			if (reserveBookNum < MAX_RESERVE_NUM)
			{
				reserveBookNum++;
				ReserveBookPtr[reserveBookNum - 1] = BookPtr;
				BookPtr->ReserveBook();
			}
		}
		else
			cout << "Can`t reserve when borrowing is banned" << endl;
	}
	else
		cout << "Can`t reserve when books are remain" << endl;
}


char* Manager::GetID(void)
{
	return ID;
}

char* Manager::GetPW(void)
{
	return PW;
}

void Manager::EnterID(char* ID)
{
	strcpy(this->ID, ID);
	return;
}

void Manager::EnterPW(char* PW)
{
	strcpy(this->PW, PW);
	return;
}

int User::GetBorrowBookNum(void)
{
	return borrowBookNum;
}

int User::GetReserveBookNum(void)
{
	return reserveBookNum;
}

void User::ShowBorrowBook(void)
{
	struct tm t;
	time_t returnDueDate;

	for (int i = 0; i < borrowBookNum; i++)
	{
		returnDueDate = borrowBookDate[i] + 7 * SEC_PER_DATE;
		t = *localtime(&returnDueDate);
		cout << "No." << i + 1 << endl;
		BorrowBookPtr[i]->ShowBookInfo();
		cout << "Return Due Date : " << 1900 + t.tm_year << '-' << t.tm_mon + 1 << '-' << t.tm_mday << endl;
	}
}

void User::ChoiceBookToReturn(void)
{
	char choiceChar;
	char buff[2];
	int choiceInt;

	if (borrowBookNum == 0)
		return;
	itoa(borrowBookNum, buff, 10);
	while (1)
	{
		cout << "Choice Number To Return : "; cin >> choiceChar;
		if (choiceChar > '0' && choiceChar <= buff[0])
			break;
	}
	choiceInt = atoi(&choiceChar);
	BorrowBookPtr[choiceInt - 1]->ReturnBook();
	ReturnBook(BorrowBookPtr[choiceInt - 1]);
}

time_t User::GetBorrowBookDate(int idx)
{
	return borrowBookDate[idx];
}

time_t User::GetBorrowBanDate(void)
{
	return borrowBanDate;
}

Book* User::GetBorrowBookPtr(int idx)
{
	return BorrowBookPtr[idx];
}

Book* User::GetReserveBookPtr(int idx)
{
	return ReserveBookPtr[idx];
}

void User::InitBorrowBookNum(int borrowBookNum)
{
	this->borrowBookNum = borrowBookNum;
	return;
}

void User::InitReservedBookNum(int reservedBookNum)
{
	this->reserveBookNum = reservedBookNum;
	return;
}

void User::InitBorrowBookDate(int idx, time_t borrowBookDate)
{
	this->borrowBookDate[idx] = borrowBookDate;
	return;
}

void User::InitBorrowBanDate(time_t borrowBanDate)
{
	this->borrowBanDate = borrowBanDate;
	return;
}

void User::InitBorrowBookPtr(int idx, Book* BorrowBookPtr)
{
	this->BorrowBookPtr[idx] = BorrowBookPtr;
	return;
}

void User::InitReserveBookPtr(int idx, Book* ReserveBookPtr)
{
	this->ReserveBookPtr[idx] = ReserveBookPtr;
	return;
}