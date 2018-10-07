// wes males berurusan dengan c++, khusus nya pointer.
// java pls.
#include <cstring>

/*
*   Cari sebuah karakter dari himpunan karakter (array) dengan linear/sequential search.
*   Return -1 jika tidak ketemu.
*/
int linearSearch( const char * list , const char * yangDicari , unsigned int size )
{
    for( unsigned int i = 0; i < size; i++ )
    {
        // ini nih yang bikin jengkel.
        char perHuruf[2];
        strncpy( perHuruf, &list[i], 1 );
        perHuruf[1] = '\0';

        if( strcmp( &perHuruf[0] , &yangDicari[0] ) == 0 )
            return i;
    }

    // Jika tidak ketemu...
    return -1;
};


/*
*   Cari sebuah kata dari kumpulan kata (array) dengan linear/sequential search.
*   Return -1 jika tidak ketemu.
*/
int linearSearch( char ** list , const char * yangDicari , unsigned int size )
{
    for( unsigned int i = 0; i < size; i++ )
    {
        if( strcmp( list[i] , yangDicari ) == 0 )
            return i;
    }

    // Jika tidak ketemu...
    return -1;
};

