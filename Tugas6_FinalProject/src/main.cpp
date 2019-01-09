/*
*   Tugas 6 (Final Project).
*   Anggara Yama Putra
*   14.12.8078
*
*   Uploaded at https://github.com/anggaranothing/matakuliah-strukturdata
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "Language.hpp"
#include "Config.hpp"
#include "Queue.hpp"
#include "Table.hpp"
#include "Menu.hpp"
#include "Order.hpp"
#include "InputParser.hpp"

using std::cin;
using std::cout;
using std::printf;
using std::string;
using std::transform;

namespace AN
{
    Queue<Order*> antrianMasak( ORDER_MAXIMUM );
    Tables* daftarMeja = new Tables();
    Menu* daftarMenu = new Menu();
    Orders* daftarPesanan = new Orders( &antrianMasak );

    void Init()
    {
        // Buat daftar meja makan.
        for( int i = 0; i < daftarMeja->Size(); i++ )
        {
            daftarMeja->Insert( new Table( i+1 ) );
        }

        // Buat daftar menu.
        if( DEMO_ENABLED )
        {
            daftarMenu->Insert( new MenuItem( "Nasi Goreng" , 8000 ) );
            daftarMenu->Insert( new MenuItem( "Roti Bakar" , 5000 ) );
            daftarMenu->Insert( new MenuItem( "Kentang Goreng" , 12000 ) );
            daftarMenu->Insert( new MenuItem( "Air Mineral" , 1000 ) );
            daftarMenu->Insert( new MenuItem( "Es Teh" , 3000 ) );
        }
    }


    void CetakSemuaMeja()
    {
        printf( "Daftar meja:\n\n" );

        if( daftarMeja->IsEmpty() )
        {
            printf( "Tidak memiliki meja.\n\n" );
            return;
        }

        for( int i = 0; i < daftarMeja->Size(); i++ )
        {
            Table* meja = daftarMeja->GetItem(i);

            if( meja )
            {
                printf( "%i. (%s)\t" , meja->Number() , LANG_TABLE_AVAILABILITY[ meja->IsEmpty() ].c_str() );

                if( meja->Number() % 3 == 0 || i == daftarMeja->Size()-1 )
                    printf( "\n" );
            }
            else
                if( i == daftarMeja->Size()-1 )
                    printf( "\n" );
        }
        printf( "\n" );
    }
    Table* PilihMeja()
    {
        if( daftarMeja->IsEmpty() )
        {
            printf( "Tidak memiliki meja.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return NULL;
        }

        Table* meja = NULL;

        CetakSemuaMeja();

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        do
        {
            printf( "Masukkan nomor meja: " );
            int index = -1;
            getInput(index);
            if( index < 0 ) return NULL;

            meja = daftarMeja->GetItem( --index );
            if( !meja )
            {
                printf( "Meja tidak valid!\n\n" );
                continue;
            }
        } while( !meja );

        return meja;
    }
    void EditMeja()
    {
        Table* meja = PilihMeja();

        if( !meja ) return;

        string yesno;
        printf( "Ubah menjadi '%s' (Tidak Input = Ya)(Y/T): " , LANG_TABLE_AVAILABILITY[ !meja->IsEmpty() ].c_str() );
        getInput( yesno );
        if( !yesno.empty() )
        {
            transform( yesno.begin(), yesno.end(), yesno.begin(), ::tolower ) ;
            if( yesno != "y" && yesno != "ya" && yesno != "yes" )
                return;
        }

        meja->SetAvailability( !meja->IsEmpty() );
    }
    void TampilSubmenuMeja()
    {
        int pilihan;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Meja ==\n\n" );
            printf( "Kapasitas: %i/%i.\n\n" , daftarMeja->FullCount() , daftarMeja->Size() );
            printf( "(1) Daftar Meja.\n" );
            printf( "(2) Ubah Ketersediaan Meja.\n" );
            printf( "\n(0) Kembali.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    system( "cls" );
                    printf( "== Menu Utama -> Meja -> Daftar Meja ==\n\n" );
                    CetakSemuaMeja();
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 2:
                    system( "cls" );
                    printf( "== Menu Utama -> Meja -> Ubah Ketersediaan Meja ==\n\n" );
                    EditMeja();
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }


    void CetakSemuaAntrianMasak()
    {
        printf( "Daftar antrian masak:\n\n" );

        if( antrianMasak.IsEmpty() )
        {
            printf( "Antrian kosong.\n\n" );
            return;
        }

        int counter = 1;
        for( int i = antrianMasak.Head(); i <= antrianMasak.Tail(); i++ )
        {
            Order* pesanan = antrianMasak.GetData(i);

            if( pesanan )
            {
                printf( "Antrian ke-%i.\tNo. Nota (#%i)\tNo. Meja (%i).\n" , counter , pesanan->Index() , pesanan->GetTable()->Number() );
                ++counter;
            }
        }
        printf( "\n" );
    }
    void CetakAntrianMasakTerdepan()
    {
        if( antrianMasak.IsEmpty() )
        {
            printf( "Antrian kosong.\n\n" );
            return;
        }

        Order* pesanan = antrianMasak.GetData();
        if( !pesanan )
        {
            printf( "(null)\n\n" );
            return;
        }

        printf( "No. Pesanan:\t#%i.\n" , pesanan->Index() );
        printf( "No. Meja:\t%i.\n\n" , pesanan->GetTable()->Number() );
        printf( "Isi pesanan:\n\n" );
        
        for( int i = 0; i < pesanan->Size(); i++ )
        {
            OrderItem* itemOrder = pesanan->GetItem(i);

            if( itemOrder )
            {
                MenuItem* itemMenu = itemOrder->Item();

                if( itemMenu )
                    printf( "%i. %s (qty. %i).\n" , i+1 , itemMenu->Name().c_str(), itemOrder->Quantity() );
            }
        }

        printf( "\n" );
    }
    void KonfirmasiPelayananAntrianTerdepan()
    {
        if( antrianMasak.IsEmpty() )
        {
            printf( "Antrian kosong.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return;
        }

        CetakAntrianMasakTerdepan();

        Order* pesanan = antrianMasak.GetData();
        if( !pesanan )
        {
            cin.get();
            return;
        }

        string yesno;
        printf( "Apakah semua pesanan sudah sampai ke meja? (Tidak Input = Ya)(Y/T): " );
        getInput( yesno );
        if( !yesno.empty() )
        {
            transform( yesno.begin(), yesno.end(), yesno.begin(), ::tolower ) ;
            if( yesno != "y" && yesno != "ya" && yesno != "yes" )
                return;
        }

        antrianMasak.DeQueue();
        pesanan->SetServingStatus( true );
    }
    void TampilSubmenuAntrianMasak()
    {
        int pilihan;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Antrian Masak ==\n\n" );
            printf( "(1) Daftar Antrian Masak.\n" );
            printf( "(2) Antrian Terdepan.\n" );
            printf( "(3) Konfirmasi Pelayanan pada Antrian Terdepan.\n" );
            printf( "\n(0) Kembali.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    system( "cls" );
                    printf( "== Menu Utama -> Antrian Masak -> Daftar Antrian Masak ==\n\n" );
                    CetakSemuaAntrianMasak();
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 2:
                    system( "cls" );
                    printf( "== Menu Utama -> Antrian Masak -> Antrian Terdepan ==\n\n" );
                    CetakAntrianMasakTerdepan();
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 3:
                    system( "cls" );
                    printf( "== Menu Utama -> Antrian Masak -> Konfirmasi Pelayanan pada Antrian Terdepan ==\n\n" );
                    KonfirmasiPelayananAntrianTerdepan();
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }


    void CetakSemuaMenuMakanan()
    {
        if( daftarMenu->IsEmpty() )
        {
            printf( "Isi menu kosong.\n\n" );
            return;
        }

        printf( "Daftar menu:\n\n" );
        for( int i = 0; i < daftarMenu->Size(); i++ )
        {
            MenuItem* item = daftarMenu->GetItem(i);

            if( item )
            {
                printf( "%i. %s (Rp. %.2f).\n" , i+1, item->Name().c_str(), item->Price() );
            }
        }
        printf( "\n" );
    }
    void TambahMenuMakanan()
    {
        string nama;
        float harga = -1;

        CetakSemuaMenuMakanan();

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        printf( "Masukkan nama: " );
        getInput( nama );
        if( nama.empty() ) return;
        nama += '\0';

        printf( "Masukkan harga: " );
        getInput( harga );
        if( harga < 0 ) return;

        daftarMenu->Insert( new MenuItem( nama , harga ) );
    }
    void EditMenuMakanan()
    {
        if( daftarMenu->IsEmpty() )
        {
            printf( "Isi menu kosong.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return;
        }

        string nama;
        float harga = -1;
        MenuItem* item = NULL;

        CetakSemuaMenuMakanan();

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        do
        {
            printf( "Masukkan nomor menu: " );
            int index = -1;
            getInput( index );
            if( index < 0 ) return;

            item = daftarMenu->GetItem( --index );
            if( !item )
            {
                printf( "Menu tidak valid!\n\n" );
                continue;
            }
        } while( !item );

        printf( "Masukkan nama: " );
        getInput( nama );
        nama = ( !nama.empty() ? nama + '\0' : item->Name() );

        printf( "Masukkan harga: " );
        getInput( harga );
        harga = ( harga >= 0 ? harga : item->Price() );

        item->SetName( nama );
        item->SetPrice( harga );
    }
    void HapusMenuMakanan()
    {
        if( daftarMenu->IsEmpty() )
        {
            printf( "Isi menu kosong.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return;
        }

        int index;
        MenuItem* item = NULL;

        CetakSemuaMenuMakanan();

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        do
        {
            printf( "Masukkan nomor menu: " );
            index = -1;
            getInput( index );
            if( index < 0 ) return;

            item = daftarMenu->GetItem( --index );
            if( !item )
            {
                printf( "Menu tidak valid!\n\n" );
                continue;
            }
        } while( !item );

        daftarMenu->Remove( index );
    }
    void TampilSubmenuMenuMakanan()
    {
        int pilihan;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Menu Makanan dan Minuman ==\n\n" );
            printf( "(1) Daftar Menu.\n" );
            printf( "(2) Tambah Menu.\n" );
            printf( "(3) Ubah Menu.\n" );
            printf( "(4) Hapus Menu.\n" );
            printf( "\n(0) Kembali.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    system( "cls" );
                    printf( "== Menu Utama -> Menu Makanan dan Minuman -> Daftar Menu ==\n\n" );
                    CetakSemuaMenuMakanan();
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 2:
                    system( "cls" );
                    printf( "== Menu Utama -> Menu Makanan dan Minuman -> Tambah Menu ==\n\n" );
                    TambahMenuMakanan();
                    break;
                
                case 3:
                    system( "cls" );
                    printf( "== Menu Utama -> Menu Makanan dan Minuman -> Ubah Menu ==\n\n" );
                    EditMenuMakanan();
                    break;
                
                case 4:
                    system( "cls" );
                    printf( "== Menu Utama -> Menu Makanan dan Minuman -> Hapus Menu ==\n\n" );
                    HapusMenuMakanan();
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }


    void CetakSemuaPesanan( bool hanyaBelumLunas )
    {
        printf( "Daftar pesanan:\n\n" );

        if( daftarPesanan->IsEmpty() )
        {
            printf( "Daftar pesanan kosong.\n\n" );
            return;
        }

        for( int i = 0; i < daftarPesanan->Size(); i++ )
        {
            Order* pesanan = daftarPesanan->GetItem(i);

            if( !pesanan )
                continue;
            
            if( hanyaBelumLunas && pesanan->IsPaidOff() )
                continue;
            
            printf( "No. Meja:\t%i\n" , pesanan->GetTable()->Number() );
            printf( "No. Pesanan:\t#%i\n" , pesanan->Index() );
            printf( "\tSudah di layani:\t%s\n" , LANG_STATUS_YESNO[ pesanan->IsServed() ].c_str() );
            printf( "\tSudah di bayar:\t\t%s\n" , LANG_STATUS_YESNO[ pesanan->IsPaidOff() ].c_str() );
            printf( "\tTotal bayar:\t\tRp. %.2f\n\n" , pesanan->TotalCost() );
        }
        printf( "\n" );
    }
    void CetakSemuaItemPesanan( Order* pesanan )
    {
        if( !pesanan )
        {
            printf( "(null)\n\n" );
            return;
        }

        printf( "Daftar isi pesanan:\n\n" );

        if( pesanan->IsEmpty() )
        {
            printf( "Isi pesanan kosong.\n\n" );
            return;
        }
        
        for( int i = 0; i < pesanan->Size(); i++ )
        {
            OrderItem* itemOrder = pesanan->GetItem(i);

            if( itemOrder )
            {
                MenuItem* itemMenu = itemOrder->Item();

                if( itemMenu )
                {
                    int qty = itemOrder->Quantity();
                    float price = itemOrder->Cost();
                    float subtotal = price * qty;
                    printf( "%i. %s (qty. %i) x (Rp. %.2f) =\tRp. %.2f.\n" , i+1 , itemMenu->Name().c_str() , qty , price , subtotal  );
                }
            }
        }
        printf( "\n" );
    }
    void TambahItemPesanan( Order* pesanan )
    {
        if( daftarMenu->IsEmpty() )
        {
            printf( "Isi menu kosong.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return;
        }

        if( !pesanan ) return;

        int kuantitas = 0;
        MenuItem* item = NULL;

        CetakSemuaMenuMakanan();

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        do
        {
            printf( "Masukkan nomor menu: " );
            int index = -1;
            getInput( index );
            if( index < 0 ) return;

            item = daftarMenu->GetItem( --index );
            if( !item )
            {
                printf( "Menu tidak valid!\n\n" );
                continue;
            }
        } while( !item );

        printf( "Masukkan kuantitas: " );
        getInput( kuantitas );
        if( kuantitas == 0 ) return;
        
        pesanan->Insert( new OrderItem( item , kuantitas ) );
    }
    void HapusItemPesanan( Order* pesanan )
    {
        if( !pesanan ) return;

        if( pesanan->IsEmpty() )
        {
            printf( "Isi pesanan kosong.\n\n" );
            printf( "Tekan tombol apapun untuk lanjut." );
            cin.get();
            return;
        }

        int index;
        OrderItem* item = NULL;

        CetakSemuaItemPesanan( pesanan );

        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        do
        {
            printf( "Masukkan nomor item: " );
            index = -1;
            getInput( index );
            if( index < 0 ) return;

            item = pesanan->GetItem( --index );
            if( !item )
            {
                printf( "Item tidak valid!\n\n" );
                continue;
            }
        } while( !item );

        pesanan->Remove( index );
    }
    Order* PilihMejaUntukPesananBaru()
    {
        Table* meja = NULL;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Pesanan -> Buat Pesanan Baru -> Pilih Meja ==\n\n" );
            
            meja = PilihMeja();
            if( !meja ) return NULL;

            if( !meja->IsEmpty() )
            {
                string yesno;
                printf( "Meja ini tidak kosong, lanjut? (Tidak Input = Ya)(Y/T): " );
                getInput( yesno );
                transform( yesno.begin(), yesno.end(), yesno.begin(), ::tolower ) ;
                if( !yesno.empty() && yesno != "y" && yesno != "ya" && yesno != "yes" )
                {
                    meja = NULL;
                    continue;
                }
            }
        } while( !meja );

        return new Order( meja );
    }
    void EditIsiPesanan( Order* pesanan , bool isBaru )
    {
        if( !pesanan ) return;

        int pilihan;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Pesanan %s-> Edit Pesanan ==\n\n" , ( isBaru ? "-> Buat Pesanan Baru " : "" ) );
            printf( "Total Biaya:\tRp. %.2f.\n\n" , pesanan->TotalCost() );
            printf( "No. Nota:\t#%i.\n" , ( isBaru ? daftarPesanan->NextOrderIndex() : pesanan->Index() ) );
            printf( "No. Meja:\t%i.\n\n" , pesanan->GetTable()->Number() );
            CetakSemuaItemPesanan( pesanan );
            printf( "(1) Tambah Item.\n" );
            printf( "(2) Hapus Item.\n" );
            printf( "\n(9) Simpan.\n" );
            printf( "(0) Batal.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    system( "cls" );
                    printf( "== Menu Utama -> Pesanan -> Buat Pesanan Baru -> Tambah Item ==\n\n" );
                    TambahItemPesanan( pesanan );
                    break;
                
                case 2:
                    system( "cls" );
                    printf( "== Menu Utama -> Pesanan -> Buat Pesanan Baru -> Hapus Item ==\n\n" );
                    HapusItemPesanan( pesanan );
                    break;
                
                case 9:
                    daftarPesanan->Insert( pesanan );
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 && pilihan != 9 );
    }
    void BuatPesananBaru()
    {
        Order* pesanan = NULL;

        cin.clear();
        cout.clear();
        system( "cls" );
        printf( "== Menu Utama -> Pesanan -> Buat Pesanan Baru ==\n\n" );

        do
        {
            if( !pesanan )
            {
                if( !(pesanan = PilihMejaUntukPesananBaru()) )
                    break;
            }
            else
            {
                EditIsiPesanan( pesanan , true );
                break;
            }
        } while( true );
    }
    void CetakDaftarPesananBelumLunas( Table* meja = NULL )
    {
        printf( "Daftar nomor nota yang belum lunas:\n\n" );

        if( daftarPesanan->IsEmpty() )
        {
            printf( "Daftar pesanan kosong.\n\n" );
            return;
        }

        if( daftarPesanan->UnpaidCount() <= 0 || ( meja && daftarPesanan->UnpaidCount( meja->Number() ) <= 0 ) )
        {
            printf( "Tidak ada pesanan yang belum dibayar.\n\n" );
            return;
        }

        for( int i = 0; i < daftarPesanan->Size(); i++ )
        {
            Order* pesanan = daftarPesanan->GetItem(i);
            if( !pesanan || pesanan->IsPaidOff() || (meja && pesanan->GetTable() != meja) )
            {
                if( i == daftarPesanan->Size()-1 ) printf( "\n" );
                continue;
            }

            printf( "(%i)\t" , pesanan->Index() );

            if( (i+1) % 10 == 0 || i == daftarPesanan->Size()-1 )
                printf( "\n" );
        }
        printf( "\n" );
    }
    void BayarPesanan( Order* pesanan )
    {
        if( !pesanan ) return;

        float uangBayar;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Pesanan -> Bayar Pesanan ==\n\n" );
            printf( "No. Nota:\t#%i.\n" , pesanan->Index() );
            printf( "No. Meja:\t%i.\n\n" , pesanan->GetTable()->Number() );
            CetakSemuaItemPesanan( pesanan );

            if( pesanan->IsEmpty() )
            {
                printf( "Isi pesanan kosong.\n\n" );
                cin.get();
                return;
            }

            if( pesanan->IsPaidOff() )
            {
                printf( "Pesanan ini sudah di bayar.\n\n" );
                cin.get();
                return;
            }

            if( !pesanan->IsServed() )
            {
                string yesno;
                printf( "Pesanan ini belum di layani! Lanjut? (Tidak Input = Ya)(Y/T): " );
                getInput( yesno );
                if( !yesno.empty() && yesno != "y" && yesno != "ya" && yesno != "yes" )
                    return;
            }
            
            printf( "\nKosongkan input untuk membatalkan perintah.\n\n" );
            printf( "Total Biaya:\t\tRp. %.2f.\n" , pesanan->TotalCost() );
            do
            {
                printf( "Masukkan Jumlah Uang:\tRp. " );
                uangBayar = -1;
                getInput( uangBayar );
                if( uangBayar < 0 ) return;
                else
                if( uangBayar < pesanan->TotalCost() )
                {
                    printf( "Nominal kurang!\n\n" ); continue;
                }
                else
                    break;
            } while( true );

            daftarPesanan->PayOff( pesanan );

            printf( "Kembalian:\t\tRp. %.2f.\n\n" , uangBayar - pesanan->TotalCost() );
            printf( "Terima Kasih!\n" );
            cin.get();
            break;
        } while( true );
    }
    Order* PilihPesananBelumLunas( Table* meja )
    {
        system( "cls" );
        printf( "== Menu Utama -> Pesanan -> Bayar Pesanan -> Pilih Nomor Nota ==\n\n" );

        CetakDaftarPesananBelumLunas( meja );

        if( daftarPesanan->IsEmpty() || daftarPesanan->UnpaidCount() <= 0 || ( meja && daftarPesanan->UnpaidCount( meja->Number() ) <= 0 ) )
        {
            cin.get();
            return NULL;
        }
        
        printf( "Kosongkan input untuk membatalkan perintah.\n\n" );

        Order* pesanan = NULL;
        do
        {
            printf( "Masukkan nomor nota: " );
            int index = -1;
            getInput( index );
            if( index < 0 ) return NULL;

            pesanan = daftarPesanan->GetItemByOrderIndex( index );
            if( !pesanan )
            {
                printf( "Pesanan tidak valid!\n\n" );
                continue;
            }
        } while( !pesanan );

        return pesanan;
    }
    void BayarPesananDenganNomorMeja()
    {
        system( "cls" );
        printf( "== Menu Utama -> Pesanan -> Bayar Pesanan -> Pilih Nomor Meja ==\n\n" );

        if( daftarPesanan->UnpaidCount() <= 0 )
        {
            printf( "Tidak ada pesanan yang belum dibayar.\n\n" );
            return;
        }
        
        Table* meja = PilihMeja();

        if( !meja ) return;

        BayarPesanan( PilihPesananBelumLunas( meja ) );
    }
    void TampilSubmenuBayarPesanan()
    {
        int pilihan;
        
        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Pesanan -> Bayar Pesanan ==\n\n" );
            printf( "(1) Pilih Nomor Meja.\n" );
            printf( "(2) Pilih Nomor Nota.\n" );
            printf( "\n(0) Kembali.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    BayarPesananDenganNomorMeja();
                    break;
                
                case 2:
                    BayarPesanan( PilihPesananBelumLunas( NULL ) );    
                    break;
                
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }


    void TampilSubmenuPesanan()
    {
        int pilihan;
        
        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama -> Pesanan ==\n\n" );
            printf( "Total:\t\t\t%i.\n" , daftarPesanan->Count() );
            printf( "Belum Lunas:\t\t%i.\n" , daftarPesanan->UnpaidCount() );
            printf( "Belum di Layani:\t%i.\n\n" , daftarPesanan->UnservedCount() );
            printf( "(1) Daftar Semua Pesanan.\n" );
            printf( "(2) Daftar Pesanan Belum Lunas.\n" );
            printf( "(3) Buat Pesanan Baru.\n" );
            printf( "(4) Bayar Pesanan.\n" );
            printf( "\n(0) Kembali.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    system( "cls" );
                    printf( "== Menu Utama -> Pesanan -> Daftar Semua Pesanan ==\n\n" );
                    CetakSemuaPesanan( false );
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 2:
                    system( "cls" );
                    printf( "== Menu Utama -> Pesanan -> Daftar Pesanan Belum Lunas ==\n\n" );
                    CetakSemuaPesanan( true );
                    printf( "Tekan tombol apapun untuk lanjut." );
                    cin.get();
                    break;
                
                case 3:
                    BuatPesananBaru();
                    break;
                
                case 4:
                    TampilSubmenuBayarPesanan();
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }


    void TampilMenuUtama()
    {
        int pilihan;

        do
        {
            cin.clear();
            cout.clear();
            system( "cls" );
            printf( "== Menu Utama ==\n\n" );
            printf( "(1) Meja.\n" );
            printf( "(2) Pesanan.\n" );
            printf( "(3) Antrian Masak.\n" );
            printf( "(4) Menu Makanan dan Minuman.\n" );
            printf( "\n(0) Matikan Program.\n" );
            printf( "\nPilihan: " );
            cin >> pilihan; cin.ignore();

            switch( pilihan )
            {
                case 1:
                    TampilSubmenuMeja();
                    break;
                
                case 2:
                    TampilSubmenuPesanan();
                    break;
                
                case 3:
                    TampilSubmenuAntrianMasak();
                    break;
                
                case 4:
                    TampilSubmenuMenuMakanan();
                    break;
                
                case 0:
                    break;
                
                default:
                    printf( "Pilihan tidak valid." );
                    cin.get();
                    break;
            }
        } while( pilihan != 0 );
    }
}


int main()
{
    AN::Init();
    AN::TampilMenuUtama();

    return 0;
}
