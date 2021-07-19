#ifndef __FUNC_H_
#define __FUNC_H_

#include "class.h"
#include "personalDataClass.h"

void RegisterBook(void);
void AmendBookInfo(void);
void DeleteBook(void);

void ShowAllBookInfo(void);
int SearchBookByTitle(void);
int SearchBookByAuthor(void);
int SearchBookByCode(void);

void DeleteAllMem(void);
void QuestDeleteOrAmend(void);

void LoadData(FILE* fp);
void SaveData(FILE* fp);

void GotoXY(int x, int y);

void QuestBorrowReserve(User* CurrentUser);
void QuestReturn(User* CurrentUser);
#endif