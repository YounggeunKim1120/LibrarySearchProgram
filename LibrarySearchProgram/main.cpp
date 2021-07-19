#include "common.h"
#include "systemData.h"
#include "func.h"
#include "personalDataFunc.h"
#include "personalDataClass.h"

int main(void)
{
	User* CurrentUser;
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	LoadData(fp);
	LoadUserData(fp1);
	LoadManagerData(fp2);

	int logInType = 0;
	int signUpType = 0;
	char choice;
	
	while (1)
	{
		cout << "-----Log In-----" << endl;
		cout << "1. User Log In" << endl;
		cout << "2. Manager Log In" << endl;
		cout << "3. Sign Up" << endl;
		cout << "4. Quit Program" << endl;
		while (1)
		{
			cout << "Enter num from 1 to 4 for choice: "; cin >> choice;
			if (choice <= '4' && choice >= '1')
				break;
		}
		switch (choice)
		{
		case '1':
			while (1)
			{
				if (UserLogIn(CurrentUser))
				{
					logInType = 1;
					break;
				}
			}
			break;
		case '2':
			while (1)
			{
				if (ManagerLogIn())
				{
					logInType = 2;
					break;
				}
			}
			break;
		case '3':
			signUpType = SignUp();
			if (signUpType == 1)
				SaveUserData(fp1);
			else if (signUpType == 2)
				SaveManagerData(fp2);
			system("cls");
			continue;
		case '4':
			DeletePersonalData();
			DeleteAllMem();
			return 0;
		}
		if (logInType)
			break;
	}

	while (logInType == 2)
	{
		system("cls");
		cout << "-----Menu-----" << endl;
		cout << "1. Register Book Information" << endl;
		cout << "2. Search Data For Manage" << endl;
		cout << "3. Quit Program And Save Data" << endl;
	
		while (1)
		{
			cout << "Enter num from 1 to 3 for choice: "; cin >> choice;
			if (choice <= '3' && choice >= '1')
				break;
		}
		
		switch (choice)
		{
		case '1':
			system("cls");
			cout << "-----Register-----" << endl;
			cout << "1. Register Book" << endl;
			cout << "2. Back To Menu" << endl;
			while (1)
			{
				cout << "Enter num from 1 to 2 for choice: "; cin >> choice;
				if (choice <= '2' && choice >= '1')
					break;
				while (getchar() != '\n');
			}
			switch (choice)
			{
			case '1':
				RegisterBook();
				continue;
			case '2':
				break;
			}
		case '2':
			system("cls");
			cout << "-----SEARCH-----" << endl;
			cout << "1. Show All Book Information" << endl;
			cout << "2. Search Book By Title" << endl;
			cout << "3. Search Book By Author" << endl;
			cout << "4. Search Book By Code" << endl;
			cout << "5. Back To Menu" << endl;
			while (1)
			{
				cout << "Enter num from 1 to 5 for choice: "; cin >> choice;
				if (choice <= '5' && choice >= '1')
					break;
			}
			switch (choice)
			{
			case '1':
				ShowAllBookInfo();
				continue;
			case '2':
				SearchBookByTitle();
				QuestDeleteOrAmend();
				continue;
			case '3':
				SearchBookByAuthor();
				QuestDeleteOrAmend();
				continue;
			case '4':
				SearchBookByCode();
				QuestDeleteOrAmend();
				continue;
			case '5':
				break;
			}
		}
		if (choice == '3')
		{
			SaveData(fp);
			SaveUserData(fp1);
			SaveManagerData(fp2);
			DeletePersonalData();
			DeleteAllMem();
			return 0;
		}
	}

	while (logInType == 1)
	{
		system("cls");
		cout << "-----Menu-----" << endl;
		cout << "1. Show All Book Information" << endl;
		cout << "2. ReturnBook" << endl;
		cout << "3. Search Book For Borrowing Or Reserving" << endl;
		cout << "4. Quit Program And Save Data" << endl;

		while (1)
		{
			cout << "Enter num from 1 to 3 for choice: "; cin >> choice;
			if (choice <= '4' && choice >= '1')
				break;
		}

		switch (choice)
		{
		case '1':
			ShowAllBookInfo();
			continue;
		case '2':
			QuestReturn(CurrentUser);
			SaveData(fp);
			SaveUserData(fp1);
			continue;
		case '3':
			system("cls");
			cout << "-----Search-----" << endl;
			cout << "1. Search Book By Title" << endl;
			cout << "2. Search Book By Author" << endl;
			cout << "3. Search Book By Code" << endl;
			cout << "4. Back To Menu" << endl;
			while (1)
			{
				cout << "Enter num from 1 to 3 for choice: "; cin >> choice;
				if (choice <= '4' && choice >= '1')
					break;
			}
			switch (choice)
			{
			case '1':
				if(SearchBookByTitle())
				QuestBorrowReserve(CurrentUser);
				SaveData(fp);
				SaveUserData(fp1);
				break;
			case '2':
				if(SearchBookByAuthor())
				QuestBorrowReserve(CurrentUser);
				SaveData(fp);
				SaveUserData(fp1);
				break;
			case '3':
				if (SearchBookByCode())
					QuestBorrowReserve(CurrentUser);
				SaveData(fp);
				SaveUserData(fp1);
				break;
			case '4':
				break;
			}	
			break;
		case '4':
			SaveData(fp);
			SaveUserData(fp1);
			SaveManagerData(fp2);
			DeletePersonalData();
			DeleteAllMem();
			return 0;
		}
	}
}