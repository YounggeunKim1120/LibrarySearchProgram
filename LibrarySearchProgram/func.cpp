#include "common.h"
#include "systemData.h"
#include "class.h"
#include "personalDataClass.h"
#include "personalDataFunc.h"

Book* head = NULL;
Book* SearchedBook = NULL;

int numOfData = 0;

Book* CreateNode(void)
{
	Book* horse = head;
	Book* newNode = NULL;
	if (!(newNode = new Book))
	{
		cout << "ERROR : LACK OF HEAP MEMORY" << endl;
		return NULL;
	}

	if (head == NULL)
	{
		head = newNode;
		head->next = NULL;
	}
	else
	{
		while (horse->next != NULL)
		{
			horse = horse->next;
		}
		horse->next = newNode;
		newNode->prev = horse;
		newNode->next = NULL;
	}

	numOfData++;
	return newNode;
}

void DeleteNode(Book* remove)
{
	if (remove == NULL)
	{
		cout << "NO DATA" << endl;
		return;
	}
	
	if (remove == head)
	{
		head = remove->next;
	}
	if (remove->next != NULL)
	{
		remove->next->prev = remove->prev;
	}
	if (remove->prev != NULL)
	{
		remove->prev->next = remove->next;
	}

	delete remove;
	numOfData--;
	return;
}

int InsertNode(Book* prevNode, Book* Node)
{
	if (Node == NULL)
	{
		cout << "NO DATA" << endl;
		return 0;
	}

	if (Node == head)
	{
		head = Node->next;
	}
	if (Node->next != NULL)
	{
		Node->next->prev = Node->prev;
	}
	if (Node->prev != NULL)
	{
		Node->prev->next = Node->next;
	}

	if (prevNode->next != NULL)
	{
		prevNode->next->prev = Node;
		Node->next = prevNode->next;
		prevNode->next = Node;
		Node->prev = prevNode;
	}
}

int SearchSameBookCode(char* bookCode)
{
	Book* cur = head;
	while (cur != NULL)
	{
		if (!strcmp(bookCode, cur->GetCode()))
			return 1;
		cur = cur->next;
	}
	return 0;
}

void RegisterBook(void)
{
	Book* newNode;
	char tempTitleArr[MAX_STR_LEN];
	char tempAuthorArr[MAX_STR_LEN];
	char tempCodeArr[MAX_STR_LEN];
	int tempRemainBook;

	system("cls");

	cout << "Book Register" << endl;
	cout << "Book Title: "; cin >> tempTitleArr;
	cout << "Book Author: "; cin >> tempAuthorArr;
	cout << "Book Code: "; cin >> tempCodeArr;
	cout << "Remain : "; cin >> tempRemainBook;

	if (SearchSameBookCode(tempCodeArr))
	{
		cout << "Same Code Exist" << endl;
		return;
	}

	newNode = CreateNode();
	newNode->BookRegist(tempTitleArr, tempAuthorArr, tempCodeArr, tempRemainBook, 0, 0);

	cout << "Register Complete" << endl;
	system("pause");
}

int SearchBookByTitle(void)
{
	Book* cur = head;
	char tempTitleArr[MAX_STR_LEN];
	char* ptr;
	int maxSearchIdx = 0;
	int searchIdx = 0;

	cout << "Book Title: "; cin >> tempTitleArr;
	system("cls");
	while (cur != NULL)
	{
		ptr = strstr(cur->GetTitle(), tempTitleArr);
		if (ptr != NULL)
		{
			cout << "No." << maxSearchIdx + 1 << endl;
			cur->ShowBookInfo();
			maxSearchIdx++;
		}
		cur = cur->next;
	}
	if (!maxSearchIdx)
	{
		cout << "No Result Found" << endl;
		system("pause");
		return 0;
	}
	while (1)
	{
		cout << "Number You Looking for : "; cin >> searchIdx;
		if (searchIdx > 0 && searchIdx <= maxSearchIdx)
			break;
	}
	cur = head;
	while (cur != NULL)
	{
		ptr = strstr(cur->GetTitle(), tempTitleArr);
		if (ptr != NULL)
		{
			--searchIdx;
			if (searchIdx == 0)
			{
				system("cls");
				cur->ShowBookInfo();
				SearchedBook = cur;
				return 1;
			}
		}
		cur = cur->next;
	}
}


int SearchBookByAuthor(void)
{
	Book* cur = head;
	char tempAuthorArr[MAX_STR_LEN];
	char* ptr;
	int maxSearchIdx = 0;
	int searchIdx = 0;

	cout << "Book Author: "; cin >> tempAuthorArr;
	system("cls");
	while (cur != NULL)
	{
		ptr = strstr(cur->GetAuthor(), tempAuthorArr);
		if (ptr != NULL)
		{
			cout << "No." << ++maxSearchIdx << endl;
			cur->ShowBookInfo();
		}
		cur = cur->next;
	}
	if (!maxSearchIdx)
	{
		cout << "No Result Found" << endl;
		system("pause");
		return 0;
	}
	while (1)
	{
		cout << "Number You Looking for : "; cin >> searchIdx;
		if (searchIdx > 0 && searchIdx <= maxSearchIdx)
			break;
	}
	cur = head;
	while (cur != NULL)
	{
		ptr = strstr(cur->GetAuthor(), tempAuthorArr);
		if (ptr != NULL)
		{
			--searchIdx;
			if (searchIdx == 0)
			{
				system("cls");
				cur->ShowBookInfo();
				SearchedBook = cur;
				return 1;
			}
		}
		cur = cur->next;
	}
}


int SearchBookByCode(void)
{
	Book* cur = head;
	char tempCodeArr[MAX_STR_LEN];
	char* ptr;
	int maxSearchIdx = 0;
	int searchIdx = 0;

	cout << "Book Code: "; cin >> tempCodeArr;
	system("cls");
	while (cur != NULL)
	{
		ptr = strstr(cur->GetCode(), tempCodeArr);
		if (ptr != NULL)
		{
			cout << "No." << ++maxSearchIdx << endl;
			cur->ShowBookInfo();
		}
		cur = cur->next;
	}
	if (!maxSearchIdx)
	{
		cout << "No Result Found" << endl;
		system("pause");
		return 0;
	}
	while (1)
	{
		cout << "Number You Looking for : "; cin >> searchIdx;
		if (searchIdx > 0 && searchIdx <= maxSearchIdx)
			break;
	}
	cur = head;
	while (cur != NULL)
	{
		ptr = strstr(cur->GetCode(), tempCodeArr);
		if (ptr != NULL)
		{
			--searchIdx;
			if (searchIdx == 0)
			{
				system("cls");
				cur->ShowBookInfo();
				SearchedBook = cur;
				return 1;
			}
		}
		cur = cur->next;
	}
}

void ShowAllBookInfo(void)
{
	Book* cur = head;

	while (cur != NULL)
	{
		cur->ShowBookInfo();
		cur = cur->next;
	}
	system("pause");
	return;
}

void DeleteBook(void)
{
	DeleteNode(SearchedBook);
	SearchedBook = NULL;
	cout << "The Book`s Information Is Deleted" << endl;
	return;
}

void AmendBookInfo(void)
{
	char tempTitleArr[MAX_STR_LEN];
	char tempAuthorArr[MAX_STR_LEN];
	char tempCodeArr[MAX_STR_LEN];

	SearchedBook->DeleteBookInfo();

	system("cls");
	cout << "Book Amend" << endl;
	cout << "Book Title: "; cin >> tempTitleArr;
	cout << "Book Author: "; cin >> tempAuthorArr;
	cout << "Book Code: "; cin >> tempCodeArr;

	SearchedBook->EnterBookInfo(tempTitleArr, tempAuthorArr, tempCodeArr);
	SearchedBook = NULL;
	return;
}

void DeleteAllMem(void)
{
	Book* remove;
	while(head!=NULL)
	{
		remove = head;
		head = head->next;
		delete remove;
	}
}

void QuestDeleteOrAmend(void)
{
	char choice;

	cout << "1. Delete" << endl;
	cout << "2. Amend" << endl;
	cout << "3. InitRemainBookNum" << endl;
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
		DeleteBook();
		break;
	case '2':
		AmendBookInfo();
		break;
	case '3':
		int remainNum;
		system("cls");
		cout << "Enter Remain Book Number : "; cin >> remainNum;
		SearchedBook->InitRemainBook(remainNum);
	case '4':
		SearchedBook = NULL;
		return;
	}
}

void LoadData(FILE* fp)
{
	char loadedTitle[MAX_STR_LEN] = { NULL };
	char loadedAuthor[MAX_STR_LEN] = { NULL };
	char loadedCode[MAX_STR_LEN] = { NULL };
	int tempRemainBook;
	int tempBorrowedBook;
	int tempReservedBook;

	Book* cur;

	fp = fopen("BookFile.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	while (1)
	{
		fgets(loadedTitle, MAX_STR_LEN, fp);
		if (feof(fp))
			break;
		loadedTitle[strlen(loadedTitle) - 1] = NULL;
		fgets(loadedAuthor, MAX_STR_LEN, fp);
		loadedAuthor[strlen(loadedAuthor) - 1] = NULL;
		fgets(loadedCode, MAX_STR_LEN, fp);
		loadedCode[strlen(loadedCode) - 1] = NULL;
		fread(&tempRemainBook, sizeof(int), 1, fp);
		fread(&tempBorrowedBook, sizeof(int), 1, fp);
		fread(&tempReservedBook, sizeof(int), 1, fp);

		cur = CreateNode();
		cur->BookRegist(loadedTitle, loadedAuthor, loadedCode, tempRemainBook, tempBorrowedBook, tempReservedBook);
		cur = cur->next;
	}
	
	fclose(fp);
}

void SaveData(FILE* fp)
{
	Book* cur = head;

	fp = fopen("BookFile.txt", "w");

	while (cur != NULL)
	{
		int remainBook = cur->GetRemainBook();
		int borrowedBook = cur->GetBorrowedBook();
		int reservedBook = cur->GetReservedBook();

		fputs(cur->GetTitle(), fp);
		fputc('\n', fp);
		fputs(cur->GetAuthor(), fp);
		fputc('\n', fp);
		fputs(cur->GetCode(), fp);
		fputc('\n', fp);
		fwrite(&remainBook, sizeof(int), 1, fp);
		fwrite(&borrowedBook, sizeof(int), 1, fp);
		fwrite(&reservedBook, sizeof(int), 1, fp);
		cur = cur->next;
	}
	fclose(fp);
	return;
}


void QuestBorrowReserve(User* CurrentUser)
{
	char choice;
	puts("");
	cout << "1. Borrowing Book" << endl;
	cout << "2. Reserve Book" << endl;
	while (1)
	{
		cout << "ENTER NUMBER: "; cin >> choice;
		if (choice == '1' || choice == '2')
			break;
	}
	
	if (choice == '1')
	{
		CurrentUser->BorrowBook(SearchedBook);
		SearchedBook->BorrowBook();
	}

	if (choice == '2')
	{
		CurrentUser->ReserveBook(SearchedBook);
		SearchedBook->ReserveBook();
	}

	return;
}

void QuestReturn(User* CurrentUser)
{
	CurrentUser->ShowBorrowBook();
	CurrentUser->ChoiceBookToReturn();
}