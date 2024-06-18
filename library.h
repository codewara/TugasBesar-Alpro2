#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int idx, length, err;
extern char cw[128], tablename[128], columnname[128];

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
} subFile

/*=============== GENERAL ===============*/

void concat (char*, char*);
void delay (int);
void welcome();
void quit(char*);
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

/*=========== SEQUENTIAL FILE ===========*/

void _mainCreate (int, mainFile*, char*);
void _subCreate (int, subFile*, char*);
void _mainRead (int*, mainFile*, char*);
void _subRead (int*, subFile*, char*);
void _mainDelete (int, char*, mainFile*);
void _subDelete (int, char*, subFile*);
int _getID (char*, subFile*);
int _cekFK (char*);

void addMain (char*);
void addSub (char*);
void updateMain (char*);
void updateSub (char*);
void delMain (char*);
void delSub (char*);



