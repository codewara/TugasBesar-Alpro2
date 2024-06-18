#include "library.h"

char str[256], tablename[128], columnname[128];
table ide[3], kategori[2];
mainFile _main[256];
subFile _sub[256];

void checkInput (char str[]) {
    START (str);
    if (strequal (READ (), "jangan")) quit(str);
    else if (strequal (READ (), "SHOW")) {
        INC(str); SHOW (READ ());
    } else if (strequal (READ (), "INSERT")) {
        INC(str); INSERT (READ ());
    } else if (strequal (READ (), "UPDATE")) {
        INC(str); UPDATE (READ ());
    } else if (strequal (READ (), "DELETE")) {
        INC(str); DELETE (READ ());
    }// else if (strequal (READ (), "JOIN")) {
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
    if (strequal(table, "ide")) {
        maxstr(ide, 3, _main, m);

        int id_width = ide[0].length;
        int name_width = ide[1].length;
        int subid_width = ide[2].length;

        // Header
        printf("+");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width + 2; i++) printf("-");
        printf("+\n");
        
        printf("| ID ");
        for (int i = 0; i < id_width - 2; i++) printf(" ");
        printf("| Deskripsi_Ide ");
        for (int i = 0; i < name_width - 13; i++) printf(" ");
        printf("| Kategori ");
        for (int i = 0; i < subid_width - 8; i++) printf(" ");
        printf("|\n");

        // Separator
        printf("|");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width + 2; i++) printf("-");
        printf("|\n");

        // Data
        for (int i = 0; i < m; i++) {
            printf("| %-*s | %-*s | %-*s |\n", id_width, _main[i].ID, name_width, _main[i].name, subid_width, _main[i].subID);
        }

        // Footer
        printf("+");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < subid_width + 2; i++) printf("-");
        printf("+\n");

    } else if (strequal(table, "kategori")) {
        maxstr_sub(kategori, 2, _sub, s);

        int id_width = kategori[0].length;
        int name_width = kategori[1].length;

        // Header
        printf("+");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+\n");
        
        printf("| ID ");
        for (int i = 0; i < id_width - 2; i++) printf(" ");
        printf("| Nama_Kategori ");
        for (int i = 0; i < name_width - 13; i++) printf(" ");
        printf("|\n");

        // Separator
        printf("+");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+\n");

        // Data
        for (int i = 0; i < s; i++) {
            printf("| %-*s | %-*s |\n", id_width, _sub[i].ID, name_width, _sub[i].name);
        }

        // Footer
        printf("+");
        for (int i = 0; i < id_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < name_width + 2; i++) printf("-");
        printf("+\n");

    } else if (strequal (table, "IJOIN")) {
        maxstr(ide, 3, _main, m);
        maxstr_sub(kategori, 2, _sub, s);

        int Mid_width = ide[0].length;
        int Mname_width = ide[1].length;
        int Sname_width = kategori[1].length;

        // Header
        printf("+");
        for (int i = 0; i < Mid_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Mname_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Sname_width + 2; i++) printf("-");
        printf("+\n");
        
        printf("| ID ");
        for (int i = 0; i < Mid_width - 2; i++) printf(" ");
        printf("| Deskripsi_Ide ");
        for (int i = 0; i < Mname_width - 13; i++) printf(" ");
        printf("| Nama_Kategori ");
        for (int i = 0; i < Sname_width - 13; i++) printf(" ");
        printf("|\n");

        // Separator
        printf("|");
        for (int i = 0; i < Mid_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Mname_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Sname_width + 2; i++) printf("-");
        printf("|\n");

        // Data
        for (int i = 0; i < m; i++) {
            printf("| %-*s | %-*s | %-*s |\n", Mid_width, _main[i].ID,
                                               Mname_width, _main[i].name,
                                               Sname_width, _sub[_getID (_main[i].subID)].name);
        }

        // Footer
        printf("+");
        for (int i = 0; i < Mid_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Mname_width + 2; i++) printf("-");
        printf("+");
        for (int i = 0; i < Sname_width + 2; i++) printf("-");
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
            break;
            
        case 106:
            strcpy (errmsg, "ERROR 106 : Jenis join tidak ditemukan.");
            break;
    }
    printf ("%s\n", errmsg);
    return;
}

void SHOW (char table[]) {
    strcpy (tablename, table);
    if (strequal(tablename, "ide") || strequal(tablename, "kategori")) {
        printf ("\nTabel %s\n", tablename);
        getTable(tablename);
    } else { ALERT (104); return; }
}

void INSERT (char table[]) {
    strcpy (tablename, table);
    if (strequal(tablename, "ide")) {
        addMain (str);
    } else if (strequal(tablename, "kategori")) {
        addSub (str);
    } else { ALERT (104); return; }
}

void UPDATE (char table[]) {
    strcpy(tablename, READ());
    if (strequal(tablename, "ide")) {
        updateMain (str);
    } else if (strequal(tablename, "kategori")) {
        updateSub (str);
    } else { ALERT(104); return; }
}

void DELETE (char table[]) {
    char id[16];
    strcpy(tablename, READ());
    
    INC (str);
    strcpy (id, READ ());

    if (strequal(tablename, "ide")) {
        delMain (id);
    } else if (strequal(tablename, "kategori")) {
        delSub (id);
    } else { ALERT(104); return; }
}

void JOIN (char type[]) {
    if (strequal (type, "INNER")) {
        getTable ("IJOIN");
    } else if (strequal (type, "RIGHT")) {
        getTable ("RJOIN");
    } else if (strequal (type, "LEFT")) {
        getTable ("LJOIN");
    }
}