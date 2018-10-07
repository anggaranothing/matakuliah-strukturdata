/*
*   Tugas 2.
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>
#include "tugas2_1.hpp"
#include "tugas2_2.hpp"

using std::cin;
using std::printf;
using std::scanf;
using std::system;

int main()
{
    system("cls");
    printf( "Menu yang tersedia: \n" );
    printf( "1. Jalankan Tugas_2_1 \n" );
    printf( "2. Jalankan Tugas_2_2 \n" );
    printf( "\nSelain itu, matikan program." );
    printf( "\nPilihan anda: " );

    unsigned int choice;
    scanf( " %u" , &choice ); cin.ignore();
    system("cls");

    switch(choice)
    {
        case 1 : Tugas2_1::Run(); break;
        case 2 : Tugas2_2::Run(); break;
        default: break;
    }

    return 0;
}

