#include <iostream>
#include "tugas2_1.hpp"
#include "an_search_linear.hpp"

using std::cin;
using std::printf;
using std::scanf;
using std::system;

namespace Tugas2_1
{

const unsigned int PANJANG_KARAKTER = 32;

void Run()
{
    char nama[PANJANG_KARAKTER];
    char dicari[2];
    int hasil;

    printf( "Masukkan nama\t\t= " );
    cin.getline( nama , PANJANG_KARAKTER );

    printf( "\nMasukkan karakter yang dicari\t= " );
    scanf( " %1s" , dicari ); cin.ignore();
    hasil = linearSearch( nama , dicari , PANJANG_KARAKTER );

    if( hasil == -1 )
    {
        printf( "\nKarakter tidak di temukan." );
    }
    else
    {
        printf( "\nKarakter di temukan pada posisi %d." , hasil+1 );
    }
}

}

