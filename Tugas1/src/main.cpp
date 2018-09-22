/*
*   Tugas 1.
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>

using std::cin;
using std::scanf;
using std::printf;
using std::system;

/* Global Consts. */
#define MAXIMUM_DATA 10

/* Global Functions. */
void TampilkanMenuUtama();
void TampilkanInfoBuku();
void TampilkanDaftarBuku();
void TambahBuku();
void PauseSebelumKeMenuUtama();

/* Data Containers. */
struct buku
{
    char judul[32];
    char pengarang[32];
    char penerbit[32];
    unsigned int tahun;
};

/* Global Variables */
unsigned int g_uiDataTerkumpul = 0;
buku g_daftarBuku[MAXIMUM_DATA];

int main()
{
    TampilkanMenuUtama();

    //system("PAUSE");
}

void TampilkanMenuUtama()
{
    system("cls");
    printf( "Menu yang tersedia: \n" );
    printf( "1. Info buku \n" );
    printf( "2. Daftar buku \n" );
    printf( "3. Tambah buku \n"  );
    printf( "\nSelain itu, matikan program." );
    printf( "\nPilihan anda: " );

    unsigned int choice;
    scanf( " %u" , &choice );
    switch(choice)
    {
        case 1 : TampilkanInfoBuku(); break;
        case 2 : TampilkanDaftarBuku(); break;
        case 3 : TambahBuku(); break;
        default: break;
    }
}

void TampilkanInfoBuku()
{
    system("cls");
    printf( "Maksimal buku yang bisa di inputkan: %i\n" , MAXIMUM_DATA );
    printf( "Buku yang telah terkumpul: %u\n" , g_uiDataTerkumpul );

    PauseSebelumKeMenuUtama();
}

void TampilkanDaftarBuku()
{
    system("cls");

    if( g_uiDataTerkumpul > 0 )
    {
        buku currentBook;
        for( unsigned int i = 0; i < g_uiDataTerkumpul; i++ )
        {
            currentBook = g_daftarBuku[i];

            printf( "=== Buku ke-%u ===" , i+1 );
            printf( "\nJudul: %s" , currentBook.judul );
            printf( "\nPengarang: %s" , currentBook.pengarang );
            printf( "\nTahun: %u" , currentBook.tahun );
            printf( "\nPenerbit: %s" , currentBook.penerbit );
            printf( "\n================\n\n\n" );
        }
    }
    else
    {
        printf( "Daftar buku masih kosong." );
    }

    PauseSebelumKeMenuUtama();
}

void TambahBuku()
{
    system("cls");

    if( g_uiDataTerkumpul < MAXIMUM_DATA )
    {
        printf( "Sisa ruang array: %u\n" , MAXIMUM_DATA - g_uiDataTerkumpul );

        buku newBook;

        cin.ignore();
        printf( "\nJudul: " ); cin.getline( newBook.judul , 32 );
        printf( "\nPengarang: " ); scanf( " %31s" , newBook.pengarang );
        printf( "\nTahun: " ); scanf( " %u" , &newBook.tahun );
        printf( "\nPenerbit: " ); scanf( " %31s" , newBook.penerbit );

        g_daftarBuku[g_uiDataTerkumpul] = newBook;
        g_uiDataTerkumpul++;
    }
    else
    {
        printf( "Daftar buku sudah memenuhi batas maksimum." );
    }

    PauseSebelumKeMenuUtama();
}

void PauseSebelumKeMenuUtama()
{
    printf( "\n" );
    system("PAUSE");
    TampilkanMenuUtama();
}
