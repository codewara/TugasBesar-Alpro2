#include "library.h"

void delay (int ms) {
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock());
}

int strequal (char str[], char check[]) {
    int i = 0, found = 0;
    while (str[i] != '\0' && check[i] != '\0' && found < strlen (str)) {
        if (str[i] == check[i] || str[i] == check[i] + 32 || str[i] == check[i] - 32) {
            i++; found++;
        } else return 0;
    }
    if (found == strlen (str) && check[i] == '\0') return 1;
    else return 0;
}

int maxstr(char column_name[],int maxstr(char column_name[], mainFile main[], int m) {
    int max_length = strlen(column_name);
    for (int i = 0; i < m; i++) {
        if (strequal(column_name, "ID")) {
            if (strlen(main[i].ID) > max_length) {
                max_length = strlen(main[i].ID);
            }
        } else if (strequal(column_name, "Deskripsi Ide")) {
            if (strlen(main[i].name) > max_length) {
                max_length = strlen(main[i].name);
            }
        } else if (strequal(column_name, "Kategori")) {
            if (strlen(main[i].subID) > max_length) {
                max_length = strlen(main[i].subID);
            }
        }
    }
    return max_length;
}

int maxstr_sub(char column_name[], subFile sub[], int s) {
    int max_length = strlen(column_name);
    for (int i = 0; i < s; i++) {
        if (strequal(column_name, "ID")) {
            if (strlen(sub[i].ID) > max_length) {
                max_length = strlen(sub[i].ID);
            }
        } else if (strequal(column_name, "Nama Kategori")) {
            if (strlen(sub[i].name) > max_length) {
                max_length = strlen(sub[i].name);
            }
        }
    }
    return max_length;
}

void concat (char str1[], char str2[]) {
    int L1 = strlen (str1), L2 = strlen (str2);
    for (int i = 0; i < L2; i++) {
        str1[L1 + i] = str2[i];
    } str1[L1 + L2] = '\0';
}

void welcome () {
    system("cls");
    printf ("Dieksekusi pada %s - %s\n\n", __DATE__, __TIME__);

    char string[256] = "Wilujeng Sumping di DBMS Bermanfaat bagi Negeri Daneswara!";
    for (int i = 0; i < strlen (string); i++) {
        printf ("%c", string[i]);
        delay (100);
    } printf ("\n"); delay (500);
    printf ("Developed by Daneswara\n"); delay (500);
    printf ("Versi 1.0\n\n"); delay (500);

    printf("00000000000000000000000000000000000000000000000000000000\n"); delay (1000);
    printf("   0000000000000000000000000000000000000000000000000\n"); delay (1000);
    printf("                    Semangat Pagi\n"); delay (1000);
    printf("   0000000000000000000000000000000000000000000000000\n"); delay (1000);
    printf("00000000000000000000000000000000000000000000000000000000\n"); delay (1000);
}

void quit (char str[]) {
    INC (str); if (EOP (str)) { ALERT (102); return; }
    if (strequal (READ (), "lupa")) {
        INC (str); if (EOP (str)) { ALERT (102); return; }
        if (strequal (READ (), "bahagia")) {
            INC (str); if (EOP (str)) { ALERT (102); return; }
            if (strequal (READ (), "hari")) {
                INC (str); if (EOP (str)) { ALERT (102); return; }
                if (strequal (READ (), "ini")) {
                    printf ("\nTerima kasih telah menggunakan DBMS Daneswara!\n");
                    exit(0);
                }
            }
        }
    }
}