#pragma once

#ifndef AN_MENU_H
#define AN_MENU_H

#include <string>
#include <array>
#include <algorithm>
#include "Debug.hpp"

namespace AN
{
    class MenuItem
    {
        private:
            std::string nama;
            float harga;
        
        public:
            MenuItem( std::string nama_item , float harga_item )
                : nama { nama_item }
                , harga { ( harga_item < 0 ? 0 : harga_item ) }
            {}

            virtual std::string Name() const final
            {
                return this->nama;
            }

            virtual float Price() const final
            {
                return this->harga;
            }

            virtual void SetName( std::string value ) final
            {
                this->nama = value;
            }

            virtual void SetPrice( float value ) final
            {
                if( value < 0 ) value = 0;
                this->harga = value;
            }
    };

    class Menu final
    {
        private:
            int kapasitas;
            std::array<MenuItem* , MENU_ITEM_MAXIMUM> daftar;
        
        public:
            Menu()
                : kapasitas { MENU_ITEM_MAXIMUM }
            {
                daftar.fill( NULL );
            }

            ~Menu()
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

            bool IsEmpty()
            {
                return this->Count() <= 0;
            }

            bool IsFull()
            {
                return this->Count() >= kapasitas;
            }

            MenuItem* GetItem( int index ) const
            {
                if( index < 0 || index >= this->Size() ) return NULL;
                
                return this->daftar[ index ];
            }

            bool Insert( MenuItem* value )
            {
                if( this->IsFull() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Menu: Insert(): Daftar penuh.\n" );

                    return false;
                }

                if( !value )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Menu: Insert(): Pointer null.\n" );

                    return false;
                }

                // Isi pada elemen yang NULL.
                for( int i = 0; i < kapasitas; i++ )
                {
                    if( !daftar[ i ] )
                    {
                        daftar[ i ] = value;
                        return true;
                    }
                }

                return false;
            }

            void Remove( int index )
            {
                if( this->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Menu: Remove(): Daftar kosong.\n" );
                    
                    return;
                }

                if( !daftar[ index ] )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Menu: Remove(): Indeks kosong.\n" );
                    
                    return;
                }

                // Hapus pointer.
                //delete daftar[ index ];
                daftar[ index ] = NULL;

                // Urutkan. Posisi pointer NULL berada paling depan.
                std::sort( daftar.begin(), daftar.end() );

                // Urutkan lagi. Posisi pointer NULL berada paling belakang.
                int pos = 0;
                for( int i = 0; i < kapasitas; i++ )
                {
                    if( daftar[i] )
                    {
                        std::swap( daftar[pos] , daftar[i] );
                        ++pos;
                    }
                }
            }
    };

}
#endif
