/*
*   Tugas 5.
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>

using std::cin;
using std::cout;
using std::printf;

#define DEBUG_MODE true
const int MAXIMUM_ANTRIAN = 5;

class Queue
{
    private:
        int awal = -1, akhir = -1;
        int data[MAXIMUM_ANTRIAN];

    protected:
        int GetHead()
        {
            return this->awal;
        }

        int GetTail()
        {
            return this->akhir;
        }

        void SetData( int position , int value )
        {
            this->data[position] = value;

            #ifdef DEBUG_MODE
                printf( "SetData(): position = %i ; value = %i.\n" , position , value );
            #endif
        }
    
    public:
        Queue()
        {
            this->awal = -1;
            this->akhir = -1;
        }

        int Capacity()
        {
            return MAXIMUM_ANTRIAN;
        }

        int Count()
        {
            return this->GetTail()+1;
        }

        bool IsFull()
        {
            return this->GetTail() >= (this->Capacity()-1);
        }

        bool IsEmpty()
        {
            return this->GetTail() <= -1;
        }

        int GetData()
        {
            return this->GetData( this->GetTail() );
        }

        int GetData( int position )
        {
            return this->data[position];
        }

        bool InQueue( int value )
        {
            if( this->IsFull() )
            {
                #ifdef DEBUG_MODE
                printf( "InQueue(): Antrian penuh.\n" );
                #endif
                
                return false;
            }

            if( this->IsEmpty() )
            {
                this->awal = 0;
                this->akhir = -1;
            }
            
            ++this->akhir;
            this->SetData( this->akhir , value );

            #ifdef DEBUG_MODE
                printf( "InQueue(): head = %i ; tail = %i.\n" , this->GetHead() , this->GetTail() );
            #endif

            return true;
        }

        bool DeQueue()
        {
            if( this->IsEmpty() )
            {
                #ifdef DEBUG_MODE
                printf( "DeQueue(): Antrian kosong.\n" );
                #endif

                return false;
            }

            --this->akhir;

            if( this->IsEmpty() )
            {
                this->awal = -1;
                this->akhir = -1;
            }

            #ifdef DEBUG_MODE
                printf( "DeQueue(): head = %i ; tail = %i.\n" , this->GetHead() , this->GetTail() );
            #endif

            return true;
        }

        int GetSmallest()
        {
            if( this->IsEmpty() ) return INT32_MAX;

            int result = INT32_MAX;
            for( int i = 0; i < this->Count(); i++ )
            {
                if( this->GetData(i) < result ) result = this->GetData(i);
            }
            return result;
        }

        int GetBiggest()
        {
            if( this->IsEmpty() ) return INT32_MIN;

            int result = INT32_MIN;
            for( int i = 0; i < this->Count(); i++ )
            {
                if( this->GetData(i) > result ) result = this->GetData(i);
            }
            return result;
        }

        int Sum()
        {
            if( this->IsEmpty() ) return INT32_MIN;

            int result = 0;
            for( int i = 0; i < this->Count(); i++ )
            {
                result += this->GetData(i);
            }
            return result;
        }

        double Average()
        {
            if( this->IsEmpty() ) return INT32_MIN;

            return ((double) this->Sum()) / ((double) this->Count());
        }

        int Search( int value )
        {
            if( this->IsEmpty() ) return -1;
            for( int i = 0; i < this->Count(); i++ )
            {
                if( this->GetData(i) == value )
                    return i;
            }

            return -1;
        }

        void PrintAll()
        {
            if( this->IsEmpty() )
            {
                printf( "PrintAll(): Antrian kosong.\n" );
                return;
            }

            printf( "Data statistik antrian: \n" );
            printf( "Kapasitas => %i/%i\n" , this->Count() , this->Capacity() );
            printf( "Nilai terkecil => %i\n" , this->GetSmallest() );
            printf( "Nilai terbesar => %i\n" , this->GetBiggest() );
            printf( "Total => %i\n" , this->Sum() );
            printf( "Rata-rata => %f\n\n" , this->Average() );

            printf( "Isi antrian: \n" );
            for( int i = 0; i < this->Count(); i++ )
            {
                printf( "Antrian ke-%i => %i\n" , i+1 , this->GetData(i) );
            }
        }
};

int main()
{
    Queue antrian = Queue();

    int pilihan, input, output;

    do
    {
        cin.clear();
        cout.clear();
        system( "cls" );
        printf( "== Menu Queue ==\n\n" );
        printf( "1. Print All.\n" );
        printf( "2. Search.\n" );
        printf( "3. In queue.\n" );
        printf( "4. De queue.\n" );
        printf( "5. Exit.\n" );
        printf( "Pilihan: " );
        cin >> pilihan; cin.ignore();

        system( "cls" );
        switch( pilihan )
        {
            case 1:
                antrian.PrintAll();
                getchar();
                break;
            
            case 2:
                if( antrian.IsEmpty() )
                {
                    printf( "Antrian kosong." );
                    getchar();
                    break;
                }
                printf( "Masukkan bilangan yg di cari: " );
                cin >> input; cin.ignore();
                output = antrian.Search( input );
                if( output > -1 )
                    printf( "Ketemu! Berada pada posisi %i." , output+1 );
                else
                    printf( "Tidak ketemu!" );
                getchar();
                break;
            
            case 3:
                if( antrian.IsFull() )
                {
                    printf( "Antrian penuh." );
                    getchar();
                    break;
                }
                printf( "Masukkan bilangan yg akan dimasukkan: " );
                cin >> input; cin.ignore();
                if( antrian.InQueue( input ) )
                    printf( "Berhasil!." );
                else
                    printf( "Gagal!." );
                getchar();
                break;
            
            case 4:
                if( antrian.DeQueue() )
                    printf( "Berhasil!." );
                else
                    printf( "Gagal!." );
                getchar();
                break;
            
            case 5:
                printf( "Bye!" );
                break;
            
            default:
                printf( "Pilihan tidak valid." );
                getchar();
                break;
        }
    } while( pilihan != 5 );

    return 0; 
}