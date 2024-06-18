#include "library.h"

int err;
char tablename[128], columnname[128];

void checkInput (char str[]) {
    START (str); err = 101;
    if (strequal (READ (), "jangan")) quit(str);
    else if (strequal (READ (), "SHOW")) {
        INC(str); SHOW (READ ());
    } else if (strequal (READ (), "INSERT")) {
        INC(str); INSERT (READ ());
    } else if (strequal (READ (), "UPDATE")) {
        INC(str); UPDATE (READ ());
    } //else if (strequal (READ (), "DELETE")) {
    //     INC(str); DELETE (READ ());
    // } else if (strequal (READ (), "JOIN")) {
    //     INC(str); JOIN (READ ());
    // } 
    else { ALERT(101); return; }
}

void still (char str[]) {
    char newstr[256];
    int length = strlen (str);
    str[length] = ' '; str[length + 1] = '\0';
    length++;
    printf ("    -> ");
    scanf ("%256[^\n]s", newstr); getchar();
    concat (str, newstr);
}

void getTable(char* table) {
    if (!EOP (str)) { ALERT (103); return; }
    
    if (strequal(table, "ide")) {
        maxstr(ide, 3, main, m);

        int id_width = ide[0].length;
        int name_width = ide[1].length;
        int subid_width = ide[2].length;

        // Header
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width; i++) printf("-");
        printf("+\n");
        
        printf("| ID");
        for (int i = 0; i < id_width - 2; i++) printf(" ");
        printf("| Deskripsi_Ide");
        for (int i = 0; i < name_width - 14; i++) printf(" ");
        printf("| Kategori");
        for (int i = 0; i < subid_width - 8; i++) printf(" ");
        printf("|\n");

        // Separator
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width; i++) printf("-");
        printf("+\n");

        // Data
        for (int i = 0; i < m; i++) {
            printf("| %-*s | %-*s | %-*s |\n", id_width, main[i].ID, name_width, main[i].name, subid_width, main[i].subID);
        }

        // Footer
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width; i++) printf("-");
        printf("+\n");
    } else if (strequal(table, "kategori")) {
        maxstr_sub(kategori, 2, sub, s);

        int id_width = kategori[0].length;
        int name_width = kategori[1].length;

        // Header
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+\n");
        
        printf("| ID");
        for (int i = 0; i < id_width - 2; i++) printf(" ");
        printf("| Nama_Kategori");
        for (int i = 0; i < name_width - 14; i++) printf(" ");
        printf("|\n");

        // Separator
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+\n");

        // Data
        for (int i = 0; i < s; i++) {
            printf("| %-*s | %-*s |\n", id_width, sub[i].ID, name_width, sub[i].name);
        }

        // Footer
        printf("+");
        for (int i = 0; i < id_width; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width; i++) printf("-");
        printf("+\n");
    }
}

void ALERT (int code) {
    char errmsg[256];
    switch (code) {
        case 101:
            strcpy (errmsg, "ERROR 101 : Perintah '");
            concat (errmsg, READ ());
            concat (errmsg, "' tidak ditemukan.");
            break;
        
        case 102:
            strcpy (errmsg, "ERROR 102 : Perintah tidak lengkap.");
            break;
            
        case 103:
            strcpy (errmsg, "ERROR 103 : Jumlah input pada tabel '");
            concat (errmsg, tablename);
            concat (errmsg, "' tidak sesuai.");
            break;
        
        case 104:
            strcpy (errmsg, "ERROR 104 : Tabel '");
            concat (errmsg, tablename);
            concat (errmsg, "' tidak ditemukan.");
            break;
            
        case 105:
            strcpy (errmsg, "ERROR 105 : Kolom '");
            concat (errmsg, columnname);
            concat (errmsg, "' pada tabel '");
            concat (errmsg, tablename);
            concat (errmsg, "' tidak ditemukan.");
            
    }
    printf ("%s\n", errmsg);
    return;
}

void SHOW (char table[]) {
    strcpy (tablename, table);
    if (strequal(table, "ide") || strequal(table, "kategori")) {
        printf ("\nTabel %s\n", table);
        getTable(table);
    } else { ALERT (104); return; }
}

void INSERT (char table[]) {
    if (strequal(tablename, "ide")) {
        addMain (str);
    } else if (strequal(tablename, "kategori")) {
        addSub (str);
    } else { ALERT (104); return; }
}

void UPDATE(char str[]) {
    strcpy(tablename, READ());
    if (strequal(tablename, "ide")) {
        updateMain (str);
    } else if (strequal(tablename, "kategori")) {
        updateSub (str);
    } else { ALERT(104); return; }
}
