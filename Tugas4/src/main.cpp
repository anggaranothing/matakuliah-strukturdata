/*
*   Tugas 4.
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>
#include <string.h>

using std::cin;
using std::printf;

const int MAKSIMUM_JUMLAH_KATA = 64;
const int MAKSIMUM_JUMLAH_KARAKTER = 32;

class Stack
{
    private:
        int indeks_terakhir = -1;
    
    public:
        char kata[MAKSIMUM_JUMLAH_KATA][MAKSIMUM_JUMLAH_KARAKTER];

        int GetCurrentIndex()
        {
            return this->indeks_terakhir;
        }

        bool IsEmpty()
        {
            return indeks_terakhir == -1;
        }

        bool IsFull()
        {
            return indeks_terakhir >= MAKSIMUM_JUMLAH_KATA-1;
        }

        bool Push( char *nilai )
        {
            if( this->IsFull() )
                return false;
            
            ++indeks_terakhir;
            strcpy( kata[indeks_terakhir], nilai );

            return true;
        }

        bool Pop()
        {
            if( this->IsEmpty() )
                return false;
            
            --indeks_terakhir;
            return true;
        }

        void Clear()
        {
            while( !this->IsEmpty() )
            {
                this->Pop();
            }
        }

        void PrintAll()
        {
            if( this->IsEmpty() )
            {
                printf( "Stack is empty!" );
                return;
            }

            for( int i = 0; i <= indeks_terakhir; i++ )
            {
                printf( "[%s]", kata[i] );

                if( i != indeks_terakhir )
                    printf( " ");
            }

            //printf( "\n");
        }

        void Reverse()
        {
            if( this->IsEmpty() )
            {
                printf( "Stack is empty!" );
                return;
            }

            int finalIndex = indeks_terakhir;
            char temporer[MAKSIMUM_JUMLAH_KATA][MAKSIMUM_JUMLAH_KARAKTER];
            for( int i = 0; i <= finalIndex; i++ )
            {
                strcpy( temporer[i] , kata[i] );
            }

            this->Clear();

            for( int j = finalIndex; j >= 0; j-- )
            {
                this->Push( temporer[j] );
            }
        }
};

int main()
{
    Stack tumpukan = Stack();
    int size = MAKSIMUM_JUMLAH_KATA * MAKSIMUM_JUMLAH_KARAKTER;
    char input[size];

    printf( "Masukkan kalimat yang ingin di balik:\n" );
    cin.getline( input , size );

    char buffer[MAKSIMUM_JUMLAH_KARAKTER];
    unsigned int jmlKarakterInput = strlen(input);
    for( unsigned int i = 0; i < jmlKarakterInput; i++ )
    {
        // Ambil 1 karakter.
        char karakter[2];
        strncpy( karakter, &input[i], 1 );

        // Karakter delimiter terdeteksi.
        if( !isalnum( karakter[0] ) )
        {
            if( strlen( buffer ) > 0 )
            {
                strcat( buffer , "\0" );
                tumpukan.Push( buffer );
            }
            
            // Bersihkan buffer.
            strcpy( buffer , "" );
            continue;
        }

        // Susun karakter ke dalam buffer.
        strcat( buffer , karakter );

        // Kata terakhir yg tanpa spasi.
        if( i == jmlKarakterInput-1 )
        {
            if( strlen( buffer ) > 0 )
            {
                strcat( buffer , "\0" );
                tumpukan.Push( buffer );
            }
        }
    }

    printf( "\nDaftar kata:\n" );
    tumpukan.PrintAll();

    printf( "\n\nHasil kata di balikkan susunan nya:\n" );
    tumpukan.Reverse();
    tumpukan.PrintAll();

    return 0;
}

