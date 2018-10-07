#include <iostream>
#include "tugas2_2.hpp"
#include <an_search_linear.hpp>

using std::cin;
using std::printf;
using std::scanf;
using std::system;

namespace Tugas2_2
{

const unsigned int UKURAN_ARRAY = 16;
const unsigned int PANJANG_KARAKTER = 32;

void Run()
{
    char nama[UKURAN_ARRAY][PANJANG_KARAKTER];
    char dicari[PANJANG_KARAKTER];
    unsigned int jml;
    int hasil;

    printf( "Masukkan jumlah nama\t= " );
    scanf( " %u" , &jml ); cin.ignore();

    printf( "\n" );
    for( unsigned int i = 0; i < jml; i++ )
    {
        printf( "%d. " , i+1 );
        cin.getline( nama[i] , PANJANG_KARAKTER );
    }

    printf( "\nMasukkan nama yang dicari\t= " );
    cin.getline( dicari , PANJANG_KARAKTER );

    // wes kapok nganggo c++.
    char *b[UKURAN_ARRAY];  // surrogate
    for( unsigned int i = 0; i < UKURAN_ARRAY; ++i )
    {
        b[i] = nama[i];
    }
    hasil = linearSearch( b , dicari , UKURAN_ARRAY );

    if( hasil == -1 )
    {
        printf( "\nNama tidak di temukan." );
    }
    else
    {
        printf( "\nNama di temukan pada posisi %d." , hasil+1 );
    }
}

}

