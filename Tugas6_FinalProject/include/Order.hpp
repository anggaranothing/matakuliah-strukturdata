#pragma once

#ifndef AN_ORDER_H
#define AN_ORDER_H

#include <string>
#include <array>
#include <algorithm>
#include "Debug.hpp"
#include "Table.hpp"
#include "Menu.hpp"
#include "Queue.hpp"

namespace AN
{
    class OrderItem
    {
        private:
            MenuItem* item;
            int jumlah;
        
        public:
            OrderItem( MenuItem* item_obj , int quantity )
                : item { item_obj }
                , jumlah { ( quantity < 0 ? 0 : quantity ) }
            {}

            virtual bool IsEmpty() final
            {
                return this->jumlah == 0;
            }

            virtual MenuItem* Item() const final
            {
                return this->item;
            }

            virtual int Quantity() const final
            {
                return this->jumlah;
            }

            virtual void SetQuantity( int value ) final
            {
                if( value < 0 ) value = 0;
                this->jumlah = value;
            }

            virtual float Cost() const final
            {
                return ( !this->Item() ? -1 : this->Item()->Price() );
            }
    };

    class Order final
    {
        private:
            int kapasitas;
            int noPesanan;
            bool sudahDilayani = false;
            bool sudahDibayar = false;
            Table* meja;
            std::array<OrderItem* , ORDER_ITEM_MAXIMUM> daftar;
        
        public:
            Order( Table* table_obj , int order_id = -1 )
                : kapasitas { ORDER_ITEM_MAXIMUM }
                , noPesanan { order_id }
                , sudahDilayani { false }
                , sudahDibayar { false }
                , meja { table_obj }
            {
                daftar.fill( NULL );
            }

            ~Order()
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

            int Index() const
            {
                return this->noPesanan;
            }

            bool IsEmpty()
            {
                return this->Count() <= 0;
            }

            bool IsFull()
            {
                return this->Count() >= kapasitas;
            }

            bool IsServed()
            {
                return this->sudahDilayani;
            }

            bool IsPaidOff()
            {
                return this->sudahDibayar;
            }

            Table* GetTable() const
            {
                return this->meja;
            }

            OrderItem* GetItem( int index ) const
            {
                if( index < 0 || index >= this->Size() ) return NULL;

                return this->daftar[ index ];
            }

            void SetIndex( int value )
            {
                if( noPesanan > -1 )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Order: SetIndex(): Sudah memiliki nomor.\n" );
                    
                    return;
                }

                this->noPesanan = value;
            }

            void SetServingStatus( bool value )
            {
                this->sudahDilayani = value;
            }

            void SetPaymentStatus( bool value )
            {
                this->sudahDibayar = value;
            }

            bool Insert( OrderItem* value )
            {
                if( this->IsFull() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Order: Insert(): Daftar penuh.\n" );

                    return false;
                }

                if( !value )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Order: Insert(): Pointer null.\n" );

                    return false;
                }

                if( value->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Order: Insert(): Kuantitas kosong.\n" );

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
                        std::printf( "Order: Remove(): Daftar kosong.\n" );
                    
                    return;
                }

                if( !daftar[ index ] )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Order: Remove(): Indeks kosong.\n" );
                    
                    return;
                }

                // Hapus pointer.
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

            float TotalCost() const
            {
                float hasil = 0;
                for( int i = 0; i < kapasitas; i++ )
                {
                    OrderItem* item = daftar[ i ];
                    if( item )
                    {
                        float biaya = item->Cost() * item->Quantity();
                        if( biaya > 0 )
                            hasil += biaya;
                    }
                }

                return hasil;
            }
    };

    class Orders final
    {
        private:
            int kapasitas;
            int noPesanan;
            std::array<Order* , ORDER_MAXIMUM> daftar;
            Queue<Order*>* antrian;
        
        public:
            Orders(  Queue<Order*>* antrian_obj )
                : kapasitas { ORDER_MAXIMUM }
                , noPesanan { 1 }
                , antrian{ antrian_obj }
            {
                daftar.fill( NULL );
            }

            ~Orders()
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

            int UnservedCount() const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) && !this->GetItem(i)->IsServed() )
                        ++jumlah;

                return jumlah;
            }

            int UnservedCount( int table_index ) const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) 
                        && this->GetItem(i)->GetTable() 
                        && this->GetItem(i)->GetTable()->Number() == table_index 
                        && !this->GetItem(i)->IsServed()
                    )
                        ++jumlah;

                return jumlah;
            }

            int UnpaidCount() const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) && !this->GetItem(i)->IsPaidOff() )
                        ++jumlah;

                return jumlah;
            }

            int UnpaidCount( int table_index ) const
            {
                int jumlah = 0;
                for( int i = 0; i < this->Size(); i++ )
                    if( this->GetItem(i) 
                        && this->GetItem(i)->GetTable() 
                        && this->GetItem(i)->GetTable()->Number() == table_index 
                        && !this->GetItem(i)->IsPaidOff()
                    )
                        ++jumlah;

                return jumlah;
            }

            int NextOrderIndex() const
            {
                return this->noPesanan;
            }

            bool IsEmpty()
            {
                return this->Count() <= 0;
            }

            bool IsFull()
            {
                return this->Count() >= kapasitas;
            }

            Order* GetItem( int index ) const
            {
                if( index < 0 || index >= this->Size() ) return NULL;
                
                return this->daftar[ index ];
            }

            Order* GetItemByOrderIndex( int index ) const
            {
                for( int i = 0; i < this->Size(); i++ )
                {
                    Order* pesanan = this->GetItem(i);
                    if( pesanan && pesanan->Index() == index )
                        return pesanan;
                }
                
                return NULL;
            }

            bool Insert( Order* value )
            {
                if( this->IsFull() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: Insert(): Daftar penuh.\n" );

                    return false;
                }

                if( !value )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: Insert(): Pointer null.\n" );

                    return false;
                }

                if( value->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: Insert(): Isi pesanan kosong.\n" );

                    return false;
                }

                // Isi pada elemen yang NULL.
                for( int i = 0; i < kapasitas; i++ )
                {
                    if( !daftar[ i ] )
                    {
                        daftar[ i ] = value;

                        value->SetIndex( noPesanan );
                        ++noPesanan;

                        if( value->GetTable() )
                            value->GetTable()->SetAvailability( false );
                        
                        if( antrian )
                            antrian->InQueue( value );
                        
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
                        std::printf( "Orders: Remove(): Daftar kosong.\n" );
                    
                    return;
                }

                if( !daftar[ index ] )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: Remove(): Indeks kosong.\n" );
                    
                    return;
                }

                // Hapus pointer.
                delete daftar[ index ];
                daftar[ index ] = NULL;
            }

            void PayOff( Order* pesanan )
            {
                if( this->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: PayOff(): Daftar kosong.\n" );
                    
                    return;
                }

                if( !pesanan )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: PayOff(): Pointer null.\n" );
                    
                    return;
                }

                for( int i = 0; i < this->Size(); i++ )
                {
                    if( this->GetItem( i ) == pesanan )
                    {
                        this->PayOff( i );
                        return;
                    }
                }
            }

            void PayOff( int index )
            {
                if( this->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: PayOff(): Daftar kosong.\n" );
                    
                    return;
                }

                Order* pesanan = this->GetItem( index );
                if( !pesanan )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Orders: PayOff(): Indeks kosong.\n" );
                    
                    return;
                }

                pesanan->SetPaymentStatus( true );

                Table* meja = pesanan->GetTable();
                if( meja )
                    if( this->UnpaidCount( meja->Number() ) <= 0 )
                        meja->SetAvailability( true );
            }
    };

}
#endif
