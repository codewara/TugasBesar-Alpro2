/* Saya Datuk Daneswara Raditya Samsura mengerjakan evaluasi Tugas Masa Depan
dalam mata kuliah Algoritma dan Pemrograman II untuk keberkahan-Nya. Maka,
saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.*/

#include "library.h"

int main () {
    // welcome();

    table ide[3], kategori[2];
    
    // Mengisi elemen-elemen struct ide
    strcpy(ide[0].name, "ID");
    strcpy(ide[1].name, "Deskripsi_Ide");
    strcpy(ide[2].name, "Kategori");

    // Mengisi elemen-elemen struct kategori
    strcpy(kategori[0].name, "ID");
    strcpy(kategori[1].name, "Nama_Kategori");
    
    // Mengambil data dari sequential files
    _mainRead(&m, main, "seqfiles/ide.txt");
    _subRead(&s, sub, "seqfiles/kategori.txt");
    
    char input[256];
    do {
        printf ("\nDBMS Daneswara> "); RESET(input);
        scanf("%255[^\n]s", input); getchar();

        checkInput(input);
    } while (1);
    
    return 0;
}