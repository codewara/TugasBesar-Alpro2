/* Saya Datuk Daneswara Raditya Samsura mengerjakan evaluasi Tugas Masa Depan
dalam mata kuliah Algoritma dan Pemrograman II untuk keberkahan-Nya. Maka,
saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.*/

#include "library.h"

int main () {
    // welcome();
    
    // Mengisi elemen-elemen struct ide
    strcpy(ide[0].name, "ID");
    strcpy(ide[1].name, "Deskripsi_Ide");
    strcpy(ide[2].name, "Kategori");

    // Mengisi elemen-elemen struct kategori
    strcpy(kategori[0].name, "ID");
    strcpy(kategori[1].name, "Nama_Kategori");
    
    // Mengambil data dari sequential files
    _mainRead(&m, _main, "seqfiles/ide.txt");
    _subRead(&s, _sub, "seqfiles/kategori.txt");
    
    do {
        printf ("\nDBMS Daneswara> "); RESET(str);
        scanf("%255[^\n]s", str); getchar();

        checkInput(str);
    } while (1);
    
    return 0;
}
