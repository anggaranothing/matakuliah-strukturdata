/*
*   Tugas 3.
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>
#include <string>
#include "an_sorting.hpp"

using std::cin;
using std::getline;
using std::printf;
using std::scanf;
using std::system;
using std::string;

#define MAXIMUM_INPUT 5

int sortType = -1;
bool isAscending = true;

string szData[MAXIMUM_INPUT];

int main()
{
    unsigned int choice;

    // Pilih tipe pengurutan.
    system("cls");
    printf( "Menu yang tersedia: \n" );
    printf( "1. Bubble Sort \n" );
    printf( "2. Selection Sort \n" );
    printf( "3. Insertion Sort \n" );
    printf( "\nSelain itu, matikan program." );
    printf( "\nPilihan anda: " );

    scanf( " %u" , &choice ); cin.ignore();
    system("cls");
    switch(choice)
    {
        case 1 : sortType = SORT_TYPE_BUBBLE; break;
        case 2 : sortType = SORT_TYPE_SELECTION; break;
        case 3 : sortType = SORT_TYPE_INSERTION; break;
        default: break;
    }

    // Pilih mode pengurutan.
    printf( "Menu yang tersedia: \n" );
    printf( "1. Ascending \n" );
    printf( "2. Descending \n" );
    printf( "\nPilihan anda: " );

    scanf( " %u" , &choice ); cin.ignore();
    system("cls");

    isAscending = ( choice != 2 );

    printf( "Tipe sorting: %s\nMode sorting: %s\n" , sorttype_name[sortType].c_str() , ( isAscending ? "Ascending" : "Descending" ) );

    // Input.
    printf( "\nData SEBELUM di urutkan:\n");
    for( int i = 0; i < MAXIMUM_INPUT; i++ )
    {
        printf( "Data ke-%i: " , i+1 );
        getline( cin , szData[i] );
    }

    // Proses.
    switch( sortType )
    {
        case SORT_TYPE_SELECTION:
            selectionSort( szData , MAXIMUM_INPUT , isAscending );
            break;
        
        case SORT_TYPE_INSERTION:
            insertionSort( szData , MAXIMUM_INPUT , isAscending );
            break;

        case SORT_TYPE_BUBBLE:
        default:
            bubbleSort( szData , MAXIMUM_INPUT , isAscending );
            break;
    }

    // Output.
    printf( "\nData SETELAH di urutkan:");
    for( int i = 0; i < MAXIMUM_INPUT; i++ )
    {
        printf( "\nData ke-%i: %s" , i+1 , szData[i].c_str() );
    }

    return 0;
}

