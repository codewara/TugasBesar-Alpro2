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

void maxstr(table tbl[], int n, mainFile main[], int m) {
    for (int i = 0; i < n; i++) {
        int max_length = strlen(tbl[i].name);
        for (int j = 0; j < m; j++) {
            if (strequal(tbl[i].name, "ID")) {
                if (strlen(main[j].ID) > max_length) {
                    max_length = strlen(main[j].ID);
                }
            } else if (strequal(tbl[i].name, "Deskripsi_Ide")) {
                if (strlen(main[j].name) > max_length) {
                    max_length = strlen(main[j].name);
                }
            } else if (strequal(tbl[i].name, "Kategori")) {
                if (strlen(main[j].subID) > max_length) {
                    max_length = strlen(main[j].subID);
                }
            }
        }
        tbl[i].length = max_length;
    }
}

void maxstr_sub(table tbl[], int n, subFile sub[], int s) {
    for (int i = 0; i < n; i++) {
        int max_length = strlen(tbl[i].name);
        for (int j = 0; j < s; j++) {
            if (strequal(tbl[i].name, "ID")) {
                if (strlen(sub[j].ID) > max_length) {
                    max_length = strlen(sub[j].ID);
                }
            } else if (strequal(tbl[i].name, "Nama_Kategori")) {
                if (strlen(sub[j].name) > max_length) {
                    max_length = strlen(sub[j].name);
                }
            }
        }
        tbl[i].length = max_length;
    }
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
