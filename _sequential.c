#include "library.h"

int m = 0, s = 0;

void _mainRead (int *n, mainFile src[], char dest[]) {
    FILE *file = fopen(dest, "r");

    fscanf(file, "%s %s %s",
           src[*n].ID, src[*n].name, src[*n].subID);

    if (!strequal (src[*n].ID, "####")) {
        while (!strequal (src[*n].ID, "####")) {
            (*n)++;
            fscanf(file, "%s %s %s",
                   src[*n].ID, src[*n].name, src[*n].subID);
        }
    } fclose(file);
}

void _subRead (int *n, subFile src[], char dest[]) {
    FILE *file = fopen(dest, "r");

    fscanf(file, "%s %s", src[*n].ID, src[*n].name);

    if (!strequal (src[*n].ID, "####")) {
        while (!strequal (src[*n].ID, "####")) {
            (*n)++;
            fscanf(file, "%s %s", src[*n].ID, src[*n].name);
        }
    } fclose(file);
}

void _mainCreate (int n, mainFile src[], char dest[]) {
    FILE *file = fopen(dest, "w");

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %s %s\n", src[i].ID, src[i].name, src[i].subID);
    }
    fprintf(file, "#### #### ####");
    fclose(file);
}

void _subCreate (int n, subFile src[], char dest[]) {
    FILE *file = fopen(dest, "w");

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %s\n", src[i].ID, src[i].name);
    }
    fprintf(file, "#### ####");
    fclose(file);
}

int _getID (char ID[], subFile src[]) {
    int i = -1;
    while (!strequal (ID, src[i].ID) && i < 256) i++;
    return i;
}

int _isTaken (char ID[], char src[]) {
    int i = 0;
    if (strequal (src, "main")) {
        while (!strequal (ID, _main[i].ID)  && i < m) i++;
        return (i < m) ? 1 : 0;
    } else if (strequal (src, "sub")) {
        while (!strequal (ID, _sub[i].ID)  && i < s) i++;
        return (i < s) ? 1 : 0;
    } else if (strequal (src, "FK")) {
        while (!strequal (ID, _main[i].subID)  && i < m) i++;
        return (i < m) ? 1 : 0;
    }
}

void addMain (char str[]) {
    mainFile newRecord;

    // Masukkan data ID
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.ID, READ ());

    // Masukkan data Deskripsi Ide
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.name, READ ());

    // Masukkan data Kategori
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.subID, READ ());

    if (_isTaken(newRecord.ID, "main")) {
        printf ("ID '%s' telah digunakan!\n", newRecord.ID);
        return;
    } else if (!_isTaken(newRecord.subID, "sub")) {
        printf ("kategori '%s' tidak ditemukan!\n", newRecord.subID);
        return;
    }

    // Simpan data ke array
    _main[m] = newRecord;
    m++;

    // Perbarui data ke file
    _mainCreate (m, _main, "seqfiles/ide.txt");

    printf ("Data ide berhasil ditambahkan!\n");
}

void addSub (char str[]) {
    subFile newRecord;

    // Masukkan data ID
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.ID, READ ());

    // Masukkan data Nama Kategori
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.name, READ ());

    if (_isTaken(newRecord.ID, "sub")) {
        printf ("ID '%s' telah digunakan!\n", newRecord.ID);
        return;
    }

    // Simpan data ke array
    _sub[s] = newRecord;
    s++;

    // Perbarui data ke file
    _subCreate (s, _sub, "seqfiles/kategori.txt");

    printf ("Data kategori berhasil ditambahkan!\n");
}

void updateMain (char str[]) {
    char id[16], column[128], newValue[128];

    // Ambil ID
    INC (str);
    if (EOP (str)) { ALERT(102); return; }
    strcpy(id, READ ());

    // Ambil kolom yang akan diperbarui
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (column, READ ());
    strcpy (columnname, column);

    // Ambil nilai baru
    INC (str);
    if (EOP(str)) { ALERT (102); return; }
    strcpy (newValue, READ ());
    
    // Cari record dengan ID yang sesuai dan update
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (strequal (_main[i].ID, id)) {
            if (strequal (column, "Deskripsi_Ide")) {
                strcpy (_main[i].name, newValue);
            } else if (strequal (column, "Kategori")) {
                strcpy (_main[i].subID, newValue);
            } else { ALERT (105); return; }
            found = 1; break;
        }
    }

    if (found) {
        _mainCreate (m, _main, "seqfiles/ide.txt");
        printf ("Data ide dengan ID '%s' berhasil diperbarui!\n", id);
    } else {
        printf ("Data ide dengan ID '%s' tidak ditemukan!\n", id);
    }
}

void updateSub (char str[]) {
    char id[16], column[128], newValue[128];
    // Ambil ID
    INC (str);
    if (EOP (str)) { ALERT(102); return; }
    strcpy(id, READ ());

    // Ambil kolom yang akan diperbarui
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (column, READ ());
    strcpy (columnname, column);

    // Ambil nilai baru
    INC (str);
    if (EOP(str)) { ALERT (102); return; }
    strcpy (newValue, READ ());

    // Cari record dengan ID yang sesuai dan update
    int found = 0;
    for (int i = 0; i < s; i++) {
        if (strequal (_sub[i].ID, id)) {
            if (strequal (column, "Nama_Kategori")) {
                strcpy(_sub[i].name, newValue);
            } else { ALERT (105); return; }
            found = 1; break;
        }
    }

    if (found) {
        _subCreate (m, _sub, "seqfiles/kategori.txt");
        printf ("Data kategori dengan ID '%s' berhasil diperbarui!\n", id);
    } else {
        printf ("Data kategori dengan ID '%s' tidak ditemukan!\n", id);
    }
}

void delMain (char id[]) {
    int found = 0;

    // Cari record dengan id yang sesuai
    for (int i = 0; i < m; i++) {
        if (strequal (_main[i].ID, id) == 0) {
            found = 1;
            for (int j = i; j < m - 1; j++) {
                _main[j] = _main[j + 1];
            } m--; break;
        }
    }

    if (found) {
        _mainCreate (m, _main, "seqfiles/ide.txt");
        printf ("Data ide dengan ID '%s' berhasil dihapus!\n", id);
    } else {
        printf ("Data ide dengan ID '%s' tidak ditemukan!\n", id);
    }
}

void delSub (char id[]) {
    int found = 0;

    // Cari record dengan id yang sesuai
    for (int i = 0; i < s; i++) {
        if (strequal (_sub[i].ID, id)) {
            if (!_isTaken (id, "FK")) {
                found = 1;
                for (int j = i; j < s - 1; j++) {
                    _sub[j] = _sub[j + 1];
                } s--; break;
            } else {
                printf ("Data kategori dengan ID '%s' merupakan foreign key!\n", id);
                return;
            }
        }
    }

    if (found) {
        _subCreate (s, _sub, "seqfiles/kategori.txt");
        printf ("\033[0;32Data kategori dengan ID '%s' berhasil dihapus!\033[0m\n", id);
    } else {
        printf ("\033[0;31mData kategori dengan ID '%s' tidak ditemukan!\033[0m\n", id);
    }
}