#pragma once

#ifndef AN_TABLE_H
#define AN_TABLE_H

#include <array>
#include <algorithm>
#include "Debug.hpp"

namespace AN
{

    class Table final
    {
        private:
            int nomor;
            bool isKosong;
        
        public:
            Table( int nomor_meja )
                : nomor { nomor_meja }
                , isKosong { true }
            {}

            int Number() const
            {
                return this->nomor;
            }

            bool IsEmpty() const
            {
                return this->isKosong;
            }

            void SetAvailability( const bool value ) 
            {
                this->isKosong = value;

                if( DEBUG_ENABLED )
                    std::printf( "Table(%i): SetAvailability(): Meja %s di pakai.\n" , this->Number() , (this->IsEmpty() ? "tidak" : "") );
            }
    };

    class Tables final
    {
        private:
            int kapasitas;
            std::array<Table* , CUSTOMER_TABLE_COUNT> daftar;
        
        public:
            Tables()
                : kapasitas { CUSTOMER_TABLE_COUNT }
            {
                daftar.fill( NULL );
            }

            ~Tables()
            {
            }

            int Size() const
            {
                return this->kapasitas;
            }

            int Count() const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) )
                        ++jumlah;

                return jumlah;
            }

            int FullCount() const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) && !this->GetItem(i)->IsEmpty() )
                        ++jumlah;

                return jumlah;
            }

            int EmptyCount() const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) && this->GetItem(i)->IsEmpty() )
                        ++jumlah;

                return jumlah;
            }

            bool IsEmpty()
            {
                return this->Count() <= 0;
            }

            bool IsFull()
            {
                return this->Count() >= kapasitas;
            }

            Table* GetItem( int index ) const
            {
                if( index < 0 || index >= this->Size() ) return NULL;
                
                return this->daftar[ index ];
            }

            bool Insert( Table* value )
            {
                if( this->IsFull() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Tables: Insert(): Daftar penuh.\n" );

                    return false;
                }

                if( !value )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Tables: Insert(): Pointer null.\n" );

                    return false;
                }

                int index = value->Number()-1;
                if( index < 0 || index >= this->Size() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Tables: Insert(): Nomor meja tidak sesuai dengan jarak min-max.\n" );

                    return false;
                }

                // Isi pada nomor meja.
                daftar[ index ] = value;

                return false;
            }

            void Remove( int index )
            {
                if( this->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Tables: Remove(): Daftar kosong.\n" );
                    
                    return;
                }

                if( !daftar[ index ] )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Tables: Remove(): Indeks kosong.\n" );
                    
                    return;
                }

                // Hapus pointer.
                delete daftar[ index ];
                daftar[ index ] = NULL;
            }
    };

}
#endif
