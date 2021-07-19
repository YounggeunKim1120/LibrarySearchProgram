#include "personalDataClass.h"
#include "common.h"

int UserLogIn(User* (&LoggedID));
int ManagerLogIn(void);
int SignUp(void);
void LoadUserData(FILE* fp);
void SaveUserData(FILE* fp);
void LoadManagerData(FILE* fp);
void SaveManagerData(FILE* fp);
void DeletePersonalData(void);