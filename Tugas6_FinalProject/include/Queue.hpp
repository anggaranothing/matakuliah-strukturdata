#pragma once

#ifndef AN_QUEUE_H
#define AN_QUEUE_H

#include "Debug.hpp"

namespace AN
{

    const int QUEUE_CAPACITY_MAXIMUM_DEFAULT = 512;

    template <typename T>
    class Queue
    {
        private:
            int kapasitas;
            int jumlah;
            int kepala;
            int ekor;
            T* data;
        
        protected:
            // Sets a value into the given index.
            virtual void SetData( int position , const T& value ) final
            {
                this->data[position] = value;
            }

        public:
            // Constructor.
            Queue( int capacity = QUEUE_CAPACITY_MAXIMUM_DEFAULT )
                : kapasitas { capacity }
                , jumlah { 0 }
                , kepala { 0 }
                , ekor { -1 }
                , data { new T[ kapasitas ] }
            {
                for( int i = 0; i < kapasitas; i++ )
                {
                    this->data[i] = NULL;
                }
            }

            // Destructor.
            ~Queue()
            {
                delete[] this->data;
            }

            // Returns the queue capacity.
            virtual int Capacity() const final
            {
                return this->kapasitas;
            }

            // Returns the queue element counts.
            virtual int Count() const final
            {
                return this->jumlah;
            }

            // Checks whether the queue is full.
            virtual bool IsFull() final 
            {
                return this->Count() >= this->Capacity();
            }

            // Checks whether the queue is empty.
            virtual bool IsEmpty() final
            {
                return this->Count() <= 0;
            }

            // Returns the head index.
            virtual int Head() final
            {
                return this->kepala;
            }

            // Returns the tail index.
            virtual int Tail() final
            {
                return this->ekor;
            }

            // Returns the value at front index.
            virtual T& GetData() const final
            {
                return this->GetData( this->kepala );
            }

            // Returns the value at the given index.
            virtual T& GetData( int position ) const final
            {
                return this->data[position];
            }

            bool InQueue( T& value )
            {
                if( this->IsFull() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Queue: InQueue(): Antrian penuh.\n" );
                    
                    return false;
                }

                ++this->jumlah;
                ++this->ekor;
                if ( this->Tail() >= this->Capacity() )
                {
                    this->ekor = 0;
                }
                this->SetData( this->Tail() , value );

                if( DEBUG_ENABLED )
                    std::printf( "Queue: InQueue(): count = %i ; head = %i ; tail = %i.\n" , this->Count() , this->Head() , this->Tail() );
                
                return true;
            }

            bool DeQueue()
            {
                if( this->IsEmpty() )
                {
                    if( DEBUG_ENABLED )
                        std::printf( "Queue: DeQueue(): Antrian kosong.\n" );

                    return false;
                }

                --this->jumlah;
                ++this->kepala;
                if ( this->Head() >= this->Capacity() )
                {
                    this->kepala = 0;
                }

                if( DEBUG_ENABLED )
                    std::printf( "Queue: DeQueue(): count = %i ; head = %i ; tail = %i.\n" , this->Count() , this->Head() , this->Tail() );
                
                return true;
            }
    };

}
#endif
