#include "common.h"
#include "systemData.h"
#include "personalDataClass.h"

User* head1 = NULL;
Manager* head2 = NULL;
extern FILE* fp1;
extern FILE* fp2;
extern Book* head;

void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int UserLogIn(User* (&LoggedID))
{
	char ch;
	char ID[MAX_ID_LEN] = { NULL };
	char PW[MAX_ID_LEN] = { NULL };
	int IDLen = 0;
	int PWLen = 0;
	User* cur = head1;

	system("cls");
	cout << "-----User Log In-----" << endl;
	cout << "ID : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (IDLen >= 15)
				continue;
			ID[IDLen] = ch;
			GotoXY(5 + IDLen, 1);
			cout << ID[IDLen];
			IDLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (IDLen == 0)
				continue;
			IDLen--;
			ID[IDLen] = NULL;
			GotoXY(5 + IDLen, 1);
			cout << ' ';
		}
		if (ch == '\r')
		{
			cout << endl;
			break;
		}
	}
	cout << "PW : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (PWLen >= 15)
				continue;
			PW[PWLen] = ch;
			GotoXY(5 + PWLen, 2);
			cout << '*';
			PWLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (PWLen == 0)
				continue;
			PWLen--;
			PW[PWLen] = NULL;
			GotoXY(5 + PWLen, 2);
			cout << ' ';
		}
		if (ch == '\r')
			break;
	}

	while (cur != NULL)
	{
		if (!strcmp(ID, cur->GetID()))
		{
			if (!strcmp(PW, cur->GetPW()))
			{
				LoggedID = cur;
				return 1;
			}
		}
		cur = cur->next;
	}
	system("cls");
	cout << "Fail To Log In" << endl;
	system("pause");
	return 0;
}

int ManagerLogIn(void)
{
	char ch;
	char ID[MAX_ID_LEN] = { NULL };
	char PW[MAX_ID_LEN] = { NULL };
	int IDLen = 0;
	int PWLen = 0;
	Manager* cur = head2;

	system("cls");
	cout << "-----Manager Log In-----" << endl;
	cout << "ID : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (IDLen >= 15)
				continue;
			ID[IDLen] = ch;
			GotoXY(5 + IDLen, 1);
			cout << ID[IDLen];
			IDLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (IDLen == 0)
				continue;
			IDLen--;
			ID[IDLen] = NULL;
			GotoXY(5 + IDLen, 1);
			cout << ' ';
		}
		if (ch == '\r')
		{
			cout << endl;
			break;
		}
	}
	cout << "PW : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (PWLen >= 15)
				continue;
			PW[PWLen] = ch;
			GotoXY(5 + PWLen, 2);
			cout << '*';
			PWLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (PWLen == 0)
				continue;
			PWLen--;
			PW[PWLen] = NULL;
			GotoXY(5 + PWLen, 2);
			cout << ' ';
		}
		if (ch == '\r')
		{
			break;
		}
	}

	while (cur != NULL)
	{
		if (strcmp(ID, cur->GetID())==0)
		{
			if (strcmp(PW, cur->GetPW())==0)
			{
				return 1;
			}
		}
		cur = cur->next;
	}
	system("cls");
	cout << "Fail To Log In" << endl;
	system("pause");
	return 0;
}


void LoadUserData(FILE* fp)
{
	char loadedID[MAX_ID_LEN] = { NULL };
	char loadedPW[MAX_ID_LEN] = { NULL };
	int borrowedNum;
	int reservedNum;
	time_t borrowBookDate[MAX_BORROW_NUM] = { NULL };
	time_t borrowBanDate;
	char borrowBookCode[MAX_STR_LEN] = { NULL };
	char reserveBookCode[MAX_STR_LEN] = { NULL };

	fp = fopen("UserIDFile.txt", "r");
	if (fp == NULL)
		return;

	while (1)
	{
		fgets(loadedID, MAX_ID_LEN, fp);
		if (feof(fp))
			break;
		loadedID[strlen(loadedID) - 1] = NULL;
		fgets(loadedPW, MAX_ID_LEN, fp);
		loadedPW[strlen(loadedPW) - 1] = NULL;
		fread(&borrowedNum, sizeof(int), 1, fp);
		fread(&reservedNum, sizeof(int), 1, fp);
		for (int i = 0; i < borrowedNum; i++)
			fread(&borrowBookDate[i], sizeof(time_t), 1, fp);
		fread(&borrowBanDate, sizeof(time_t), 1, fp);
		for (int i = 0; i < borrowedNum; i++)
		{
			fgets(borrowBookCode, MAX_STR_LEN, fp);
			borrowBookCode[strlen(borrowBookCode) - 1] = NULL;
		}
		for (int i = 0; i < reservedNum; i++)
		{
			fgets(reserveBookCode, MAX_STR_LEN, fp);
			reserveBookCode[strlen(reserveBookCode) - 1] = NULL;
		}

		User* cur1 = head1;
		User* newNode = new User;
		Book* cur = head;

		if (head1 == NULL)
		{
			head1 = newNode;
			head1->EnterID(loadedID);
			head1->EnterPW(loadedPW);
			head1->InitBorrowBookNum(borrowedNum);
			head1->InitReservedBookNum(reservedNum);
			for (int i = 0; i < borrowedNum; i++)
				head1->InitBorrowBookDate(i, borrowBookDate[i]);
			head1->InitBorrowBanDate(borrowBanDate);
			for (int i = 0; i < borrowedNum; i++)
			{
				while (cur != NULL)
				{
					if (!strcmp(borrowBookCode, cur->GetCode()))
					{
						head1->InitBorrowBookPtr(i, cur);
					}
					cur = cur->next;
				}
			}
			for (int i = 0; i < reservedNum; i++)
			{
				while (cur != NULL)
				{
					if (!strcmp(reserveBookCode, cur->GetCode()))
					{
						head1->InitReserveBookPtr(i, cur);
					}
					cur = cur->next;
				}
			}
			head1->next = NULL;
		}
		else
		{
			while (cur1->next != NULL)
			{
				cur1 = cur1->next;
			}
			cur1->next = newNode;
			cur1 = cur1->next;
			cur1->EnterID(loadedID);
			cur1->EnterPW(loadedPW);
			cur1->InitBorrowBookNum(borrowedNum);
			cur1->InitReservedBookNum(reservedNum);
			for (int i = 0; i < borrowedNum; i++)
				cur1->InitBorrowBookDate(i, borrowBookDate[i]);
			cur1->InitBorrowBanDate(borrowBanDate);
			for (int i = 0; i < borrowedNum; i++)
			{
				while (cur != NULL)
				{
					if (!strcmp(borrowBookCode, cur->GetCode()))
					{
						cur1->InitBorrowBookPtr(i, cur);
					}
					cur = cur->next;
				}
			}
			for (int i = 0; i < reservedNum; i++)
			{
				while (cur != NULL)
				{
					if (!strcmp(reserveBookCode, cur->GetCode()))
					{
						cur1->InitReserveBookPtr(i, cur);
					}
					cur = cur->next;
				}
			}
			cur1->next = NULL;
		}
	}
	fclose(fp);
}

void SaveUserData(FILE* fp)
{
	User* cur = head1;

	fp = fopen("UserIDFile.txt", "w");

	while (cur != NULL)
	{
		int borrowedNum = cur->GetBorrowBookNum();
		int reservedNum = cur->GetReserveBookNum();
		time_t borrowBookDate[MAX_BORROW_NUM] = { NULL };
		time_t borrowBanDate;
		char borrowBookCode[MAX_STR_LEN] = { NULL };
		char reserveBookCode[MAX_STR_LEN] = { NULL };

		fputs(cur->GetID(), fp);
		fputc('\n', fp);
		fputs(cur->GetPW(), fp);
		fputc('\n', fp);
		fwrite(&borrowedNum, sizeof(int), 1, fp);
		fwrite(&reservedNum, sizeof(int), 1, fp);
		for (int i = 0; i < borrowedNum; i++)
		{
			borrowBookDate[i] = cur->GetBorrowBookDate(i);
			fwrite(&borrowBookDate[i], sizeof(time_t), 1, fp);
		}
		fwrite(&borrowBanDate, sizeof(time_t), 1, fp);
		for (int i = 0; i < borrowedNum; i++) 
		{
			fputs(cur->GetBorrowBookPtr(i)->GetCode(), fp);
			fputc('\n', fp);
		}
		for (int i = 0; i < reservedNum; i++)
		{
			fputs(cur->GetReserveBookPtr(i)->GetCode(), fp);
			fputc('\n', fp);
		}
		cur = cur->next;
	}
	fclose(fp);
	return;
}


void LoadManagerData(FILE* fp)
{
	char loadedID[MAX_ID_LEN] = { NULL };
	char loadedPW[MAX_ID_LEN] = { NULL };

	fp = fopen("ManagerIDFile.txt", "r");
	if (fp == NULL)
		return;

	while (1)
	{
		fgets(loadedID, MAX_ID_LEN, fp);
		if (feof(fp))
			break;
		loadedID[strlen(loadedID) - 1] = NULL;
		fgets(loadedPW, MAX_ID_LEN, fp);
		loadedPW[strlen(loadedPW) - 1] = NULL;

		Manager* cur = head2;
		Manager* newNode = new Manager;

		if (head2 == NULL)
		{
			head2 = newNode;
			head2->EnterID(loadedID);
			head2->EnterPW(loadedPW);
			head2->next = NULL;
		}
		else
		{
			while (cur->next != NULL)
			{
				cur = cur->next;
			}
			cur->next = newNode;
			cur = cur->next;
			cur->EnterID(loadedID);
			cur->EnterPW(loadedPW);
			cur->next = NULL;
		}
	}
	fclose(fp);
}

void SaveManagerData(FILE* fp)
{
	Manager* cur = head2;

	fp = fopen("ManagerIDFile.txt", "w");

	while (cur != NULL)
	{
		fputs(cur->GetID(), fp);
		fputc('\n', fp);
		fputs(cur->GetPW(), fp);
		fputc('\n', fp);
		cur = cur->next;
	}
	fclose(fp);
}

int SignUp(void)
{
	char ch;
	char ID[MAX_ID_LEN] = { NULL };
	char PW[MAX_ID_LEN] = { NULL };
	int IDLen = 0;
	int PWLen = 0;
	int choice=0;

	while (1)
	{
		system("cls");
		cout << "User Sign Up: 1" << endl;
		cout << "Manager Sign Up: 2" << endl;
		scanf("%d", &choice);
		if (choice == 1 || choice == 2)
			break;
	}

	system("cls");
	if (choice == 1)
		cout << "-----User Sign Up-----" << endl;
	if (choice == 2)
		cout << "-----Manager Sign Up-----" << endl;
	cout << "ID : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (IDLen >= 15)
				continue;
			ID[IDLen] = ch;
			GotoXY(5 + IDLen, 1);
			cout << ID[IDLen];
			IDLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (IDLen == 0)
				continue;
			IDLen--;
			ID[IDLen] = NULL;
			GotoXY(5 + IDLen, 1);
			cout << ' ';
		}
		if (ch == '\r')
		{
			cout << endl;
			break;
		}
	}
	cout << "PW : ";
	while (1)
	{
		ch = getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			if (PWLen >= 15)
				continue;
			PW[PWLen] = ch;
			GotoXY(5 + PWLen, 2);
			cout << '*';
			PWLen++;
		}
		if (ch == BACK_SPACE)
		{
			if (PWLen == 0)
				continue;
			PWLen--;
			PW[PWLen] = NULL;
			GotoXY(5 + PWLen, 2);
			cout << ' ';
		}
		if (ch == '\r')
			break;
	}

	if (choice == 1)
	{
		User* cur = head1;
		User* newNode = new User;
		while (cur != NULL)
		{
			if (!strcmp(cur->GetID(), ID))
			{
				system("cls");
				cout << "Overlapped ID Exist" << endl;
				system("pause");
				return 0;
			}
			cur = cur->next;
		}
		cur = head1;
		if (head1 == NULL)
		{
			head1 = newNode;
			head1->EnterID(ID);
			head1->EnterPW(PW);
			head1->InitBorrowBookNum(0);
			head1->InitReservedBookNum(0);
			head1->next = NULL;
		}
		else
		{
			while (cur->next != NULL)
			{
				cur = cur->next;
			}
			cur->next = newNode;
			cur->next->EnterID(ID);
			cur->next->EnterPW(PW);
			cur->next->InitBorrowBookNum(0);
			cur->next->InitReservedBookNum(0);
			cur = cur->next;
			cur->next = NULL;
		}
	}
	else if (choice == 2)
	{
		Manager* cur = head2;
		Manager* newNode = new Manager;

		while (cur != NULL)
		{
			if (!strcmp(cur->GetID(), ID))
			{
				system("cls");
				cout << "Overlapped ID Exist" << endl;
				system("pause");
				return 0;
			}
			cur = cur->next;
		}
		cur = head2;

		if (head2 == NULL)
		{
			head2 = newNode;
			head2->EnterID(ID);
			head2->EnterPW(PW);
			head2->next = NULL;
		}
		else
		{
			while (cur->next != NULL)
			{
				cur = cur->next;
			}
			cur->next = newNode;
			cur->next->EnterID(ID);
			cur->next->EnterPW(PW);
			cur = cur->next;
			cur->next = NULL;
		}
	}

	return choice;
}

void DeletePersonalData(void) 
{
	User* remove1 = NULL;
	Manager* remove2 = NULL;

	while (head1 != NULL)
	{
		remove1 = head1->next;
		delete head1;
		head1 = remove1;
	}
	while (head2 != NULL)
	{
		remove2 = head2->next;
		delete head2;
		head2 = remove2;
	}
	return;
}
