#include "library.h"

int m = 0, s = 0;

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

void _mainRead (int *n, mainFile src[], char dest[]) {
    FILE *file = fopen(dest, "r");

    fscanf(file, "%s %s %s",
           src[*n].ID, src[*n].name, src[*n].subID);

    if (strcmp (src[*n].ID, "####") == 0) {
        printf ("File ini kosong!\n");
    } else while (strcmp (src[*n].ID, "####") != 0) {
        (*n)++;
        fscanf(file, "%s %s %s",
               src[*n].ID, src[*n].name, src[*n].subID);
    }
    fclose(file);
}

void _subRead (int *n, subFile src[], char dest[]) {
    FILE *file = fopen(dest, "r");

    fscanf(file, "%s %s", src[*n].ID, src[*n].name);

    if (strcmp (src[*n].ID, "####") == 0) {
        printf ("File ini kosong!\n");
    } else while (strcmp (src[*n].ID, "####") != 0) {
        (*n)++;
        fscanf(file, "%s %s", src[*n].ID, src[*n].name);
    }
    fclose(file);
}

void _mainDelete (int n, char ID[], mainFile src[]) {
    FILE *file = fopen("seqfiles/ide.txt", "w");

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp (src[i].ID, ID) != 0) {
            fprintf(file, "%s %s %s %s %s %d\n",
                    src[i].ID, src[i].name, src[i].subID);
        } else found = 1;
    } fprintf(file, "#### #### ####");
    
    printf ("----------------------------------------\n");
    if (!found) printf ("Data ide dengan ID %s tidak ditemukan!\n", ID);
    else {
        printf ("Data ide dengan ID %s telah dihapus!\n", ID);
        n--;
    }
    m = 0;
    _mainRead (&m, src, "seqfiles/ide.txt");
    fclose(file);
}

void _subDelete (int n, char ID[], subFile src[]) {
    FILE *file = fopen("seqfiles/kategori.txt", "w");

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp (src[i].ID, ID) != 0) {
            fprintf(file, "%s %s\n", src[i].ID, src[i].name);
        } else {
            if (_cekFK (ID)) {
                fprintf(file, "%s %s\n", src[i].ID, src[i].name);
                found = 2;
            } else found = 1;
        }
    } fprintf(file, "#### ####");

    printf ("----------------------------------------\n");
    if (found == 1) printf ("Data kategori dengan ID %s tidak ditemukan!\n", ID);
    else if (found == 2) printf ("Data kategori dengan ID %s digunakan pada tabel ide!\n", ID);
    else {
        printf ("Data kategori dengan ID %s telah dihapus!\n", ID);
        n--;
    }
    
    s = 0;
    _subRead (&s, src, "seqfiles/kategori.txt");
    fclose(file);
}

int _getID (char ID[], subFile src[]) {
    int i = -1;
    while (strcmp (ID, src[i].ID) != 0 && i < 256) i++;
    return i;
}

int _cekFK (char ID[]) {
    int i = 0;
    while (strcmp (ID, _main[i].subID) != 0  && i < m) i++;
    return (i < m) ? 1 : 0;
}

void addMain (char str[]) {
    mainFile newRecord;

    // Masukkan data ID
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.ID, READ ());;

    // Masukkan data Deskripsi Ide
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.name, READ ());

    // Masukkan data Kategori
    INC (str);
    if (EOP (str)) { ALERT (102); return; }
    strcpy (newRecord.subID, READ ());

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

    // Ambil nilai baru
    INC (str);
    if (EOP(str)) { ALERT (102); return; }
    strcpy (newValue, READ ());
    
    INC (str);
    if (!EOP (str)) { ALERT (103); return; }

    // Cari record dengan ID yang sesuai dan update
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (strcmp(_main[i].ID, id) == 0) {
            if (strequal(column, "Deskripsi_Ide")) {
                strcpy(_main[i].name, newValue);
            } else if (strequal(column, "Kategori")) {
                strcpy(_main[i].subID, newValue);
            } else { ALERT (105); return; }
            found = 1; break;
        }
    }

    if (found) {
        _mainCreate (m, _main, "seqfiles/ide.txt");
        printf ("Data ide berhasil diperbarui!\n");
    } else {
        printf ("Data ide dengan ID %s tidak ditemukan!\n", id);
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
    
    INC (str);
    if (!EOP (str)) { ALERT (103); return; }

    // Cari record dengan ID yang sesuai dan update
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (strcmp(_main[i].ID, id) == 0) {
            if (strequal(column, "Nama_Kategori")) {
                strcpy(_main[i].name, newValue);
            } else { ALERT (105); return; }
            found = 1; break;
        }
    }

    if (found) {
        _mainCreate (m, _main, "seqfiles/kategori.txt");
        printf ("Data ide berhasil diperbarui!\n");
    } else {
        printf ("Data ide dengan ID %s tidak ditemukan!\n", id);
    }
}
