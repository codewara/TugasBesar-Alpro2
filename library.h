#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*=============== STRUCTS ===============*/

typedef struct {
    char name[128];
    char type[64];
    int length;
} table;

typedef struct {
    char ID[16];
    char name[128];
    char subID[16];
} mainFile;

typedef struct {
    char ID[16];
    char name[128];
} subFile;

/*=============== EXTERNS ===============*/

extern table ide[3], kategori[2];
extern mainFile _main[256];
extern subFile _sub[256];

extern int m, s, idx, length, err;
extern char str[256], cw[128], tablename[128], columnname[128];

/*=============== GENERAL ===============*/

void concat (char*, char*);
void delay (int);
void welcome();
void quit(char*);
void maxstr (table*, int, mainFile*, int);
void maxstr_sub (table*, int, subFile*, int);
int strequal (char*, char*);

/*=============== MACHINE ===============*/

char* READ ();
void START (char*);
void RESET (char*);
void INC (char*);
int EOP (char*);

/*================ QUERY ================*/

void ALERT (int);
void checkInput (char*);
void still (char*);
void SHOW (char*);
void INSERT (char*);
void UPDATE (char*);
void DELETE (char*);

/*=========== SEQUENTIAL FILE ===========*/

void _mainRead (int*, mainFile*, char*);
void _subRead (int*, subFile*, char*);
void _mainCreate (int, mainFile*, char*);
void _subCreate (int, subFile*, char*);
int _getID (char*, subFile*);
int _isTaken (char*, char*);

void addMain (char*);
void addSub (char*);
void updateMain (char*);
void updateSub (char*);
void delMain (char*);
void delSub (char*);
