#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
using namespace std;

FILE *DataKaryawan;
FILE *DataBarangn;

char yn;

	
struct karyawan{
    int id_karyawan;
    char nama[30];
}kry[100];

struct barang{
	char nama[30];
    int harga;
    int stok;
}brg[100];

void YN();
void sequentialsearch(int banyakbarang, int &index, char cari[]);

void login();

void admin();
void menuadmin();
void admin_inputdata();
void admin_tampildata();
void admin_searching();

void karyawan();
void menukaryawan();
void tambahbarang();
void lihatbarang();
void editbarang();
void caribarang();

void keluar();


//tambahan
void YN(){
	do{
		cout << "ingin melanjutkan program (y/n) : ";
		cin >> yn;
		yn=tolower(yn);
		if (yn != 'y' and yn != 'n' ){
			cout << "Input tidak valid " << endl;
			}
	}while(yn != 'y' and yn != 'n');
}

void hitungbarang(int &banyakbarang){
	int i =0;
	DataBarangn = fopen("DataBarang.txt","r");
	while(fscanf(DataBarangn,"%s %d %d",
		brg[i].nama,
		&brg[i].harga,	
		&brg[i].stok) != EOF){
		i++;
		}

	banyakbarang=i;
	fclose(DataBarangn);
}
	
//menu utama

void login(){
	
	int Opsilogin;
	
	cout << "========== WELCME TO COCOA HEAVEN ==========" << endl;
	cout << "1. Login Admin " << endl;
	cout << "2. Login Karyawan" << endl;
	cout << "3. Keluar" << endl;
	cout << "============================================" << endl;
	cout << "Masukan pilihan menu : ";
	cin >> Opsilogin;
	if (Opsilogin == 1){
		admin();
	}else if(Opsilogin == 2){
		karyawan();
	}else if(Opsilogin == 3){
		keluar();
	}else{
		cout << "Input yang anda masukan tidak sesuai" << endl;
		login();
		}
}

// menu admin

void menuadmin(){
	int opsimenuadmin;
		cout << "Berhasil login " << endl;
		cout << "========== Halo Admin ==========" << endl;
		cout << "1. Tambah data karyawan" << endl;
		cout << "2. Lihat data Karyawan" << endl;
		cout << "3. Searchin data karyawan" << endl;
		cout << "4. Logout" << endl;
		cout << "============================================" << endl;
		cout << "Masukan pilihan menu : ";
		cin >> opsimenuadmin;
		switch(opsimenuadmin){

            case 1 : admin_inputdata();
            break;

            case 2 : admin_tampildata();
            break;

            case 3 : admin_searching();
            break;

            case 4 : login();
            break;

            default : {
				cout << "Input tidak valid masukan y atau n " << endl;
				YN();
				(yn == 'y') ? menuadmin() : login();
				
				}
		}
	}
	
void admin(){
	
	string useradmin,pwadmin;
	cout << "Masukan Username Anda : ";
	cin >> useradmin;
	cout << "Masukan Password Anda : ";
	cin >> pwadmin;
	
	if (pwadmin != "qwert123" or useradmin != "nabil"){
		cout << "Username atau Pw anda salah anda bukan admin" << endl;
		YN();
		if(yn == 'y'){
			admin();
		}else {
			login();
		}
	
	}else{
		menuadmin();
	}
}

void admin_inputdata(){
	int jumlahkaryawan;
	cout << "Masukan jumlah karyawan : ";
	cin >> jumlahkaryawan;
	
	DataKaryawan = fopen("DataKaryawan.txt","a");
	for (int i=0; i < jumlahkaryawan; i++){
		cout << "Data karyawan ke-" << i+1 << endl;
		cout << "Id karyawan : ";
		cin >> kry[i].id_karyawan;
		cout << "Nama karyawan : ";
		cin >> kry[i].nama;
		cout << endl << endl;
		// nama pointer, type datanya, nama datanya
		fprintf(DataKaryawan,"%d %s\n",
	        kry[i].id_karyawan,
	        kry[i].nama);
		
		}
	fclose(DataKaryawan);

	YN();
	(yn == 'y') ? admin_inputdata() : menuadmin();

}
void admin_tampildata(){
	int i=0;
	DataKaryawan= fopen("DataKaryawan.txt","r");
	if (DataKaryawan==NULL){
		cout << "Data karyawan belum ada " << endl;
	}else {
		cout << "================ Data Karyawan ================" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "| NO |ID       | Nama                         |" << endl;
		cout << "-----------------------------------------------" << endl;
		
		while(fscanf(DataKaryawan,"%d %s",
			&kry[i].id_karyawan,
			kry[i].nama) != EOF){
			cout << left << "|" << setw(4) << i + 1
				 << "|" << setw(9) << kry[i].id_karyawan
				 << "|" << setw(30) << kry[i].nama
				 << "|" << endl;
			cout << "-----------------------------------------------" << endl;
			i++;
		
		}
	}
	fclose(DataKaryawan);
	YN();
	(yn == 'y') ? admin_tampildata() : menuadmin();
	
}
void admin_searching(){
	int i=0;
	DataKaryawan= fopen("DataKaryawan.txt","r");
	int cariid;
	bool data=false;
	cout << "========== Searching Data ==========" << endl;
	cout << "Masukan id dari data yang ingin di cari : ";
	cin >> cariid;
	
	while(fscanf(DataKaryawan,"%d %s",
			&kry[i].id_karyawan,
			kry[i].nama) != EOF){
				
			if (kry[i].id_karyawan== cariid){
			cout <<  "data ditemukan " << endl;
			data=true;
			cout << "-----------------------------------------------" << endl;
			cout << "| NO |ID       | Nama                         |" << endl;
			cout << "-----------------------------------------------" << endl;
			cout << left << "|" << setw(4) << i+1
             << "|" << setw(9) << kry[i].id_karyawan
             << "|" << setw(30) << kry[i].nama
             << "|" << endl;
			cout << "-----------------------------------------------" << endl;
			break;
			}
			
			i++;
		
		}
		
	if (data == false ) {
			 cout <<  " data tidak ditemukan " << endl;
			}
	
	fclose(DataKaryawan);
	YN();
	(yn == 'y') ? admin_searching() : menuadmin();
}
	
//menu karyawan

void menukaryawan(){
	cout << "=====================================" << endl;
	cout << "            Halo Karyawan!           " << endl;
	cout << "=====================================" << endl;
	cout << "1. Tambah data barang" << endl;
	cout << "2. Lihat data barang" << endl;
	cout << "3. edit data barang" << endl;
	cout << "4. cari data barang" << endl;
	cout << "5. Logout" << endl;
	cout << "=====================================" << endl;
	
	}
	
void karyawan(){
	int opsimenukaryawan;
	menukaryawan();
	do{
		cout << "Pilih menu: ";
		cin >> opsimenukaryawan;
		
		switch(opsimenukaryawan){

				case 1 : tambahbarang();
				break;

				case 2 : lihatbarang();
				break;

				case 3 : editbarang();
				break;

				case 4 : caribarang();
				break;
				
				case 5 : login();
				break;

				default : {
					yn ='y';
					cout << "Pilihan Tidak Valid" << endl; 
					YN();
					if (yn == 'n')login();
					}
				
			}
	
	}while (yn != 'n');
}

void tambahbarang(){
	cout << "========== Tambah Barang ==========" << endl;
	int jumlahbarang=0;
	cout << "Masukan jumlah Barang : ";
	cin >> jumlahbarang;
	
	DataBarangn = fopen("DataBarang.txt","a");
	for (int i=0; i < jumlahbarang; i++){
		cout << "Data barang ke-" << i+1 << endl;
		cout << "Nama barang : ";
		cin >> brg[i].nama;
		cout << "Harga "<< brg[i].nama << " : ";
		cin >> brg[i].harga;
		cout << "Stok "<< brg[i].nama << " : ";
		cin >> brg[i].stok;
		cout << endl << endl;
		// nama pointer, type datanya, nama datanya
		fprintf(DataBarangn,"%s %d %d \n",
	        brg[i].nama,
	        brg[i].harga,
	        brg[i].stok);
		
		}
	fclose(DataBarangn);

	YN();
	(yn == 'y') ? tambahbarang() : karyawan();

}
void TampilAscending(int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(brg[j].harga > brg[j+1].harga){
                
                barang temp = brg[j];
                brg[j] = brg[j+1];
                brg[j+1] = temp;

            }
        }
    }
}

void TampilDescending(int awal, int akhir){
	int i = awal;
	int j = akhir;
	int pivot = brg[(awal + akhir) / 2].harga;

	while(i <= j){

		while(brg[i].harga > pivot){
			i++;}
		while(brg[j].harga < pivot){
			j--;}
		if(i <= j){
			barang temp = brg[i];
			brg[i] = brg[j];
			brg[j] = temp;

			i++;
			j--;
		}
	}

	if(awal < j){
		TampilDescending(awal, j);
	}

	if(i < akhir){
		TampilDescending(i, akhir);
	}
}
void lihatbarang(){
	int pilih;
	int banyakbarang=0;
	hitungbarang(banyakbarang);
	cout << "========== Lihat Barang ==========" << endl;
	cout << "Banyak data yang ada sejumlah : " << banyakbarang << endl;
	if (banyakbarang >=1){
		do{
		cout << "========== Lihat Barang ==========" << endl;
		cout << "1. Harga  Kecil ke Terbesar " << endl;
		cout << "2. Harga Besar ke kecil " << endl;
		cout << "Pilih : ";
		cin >> pilih;
		}while(pilih !=1 and pilih !=2);
	
	(pilih == 1) ? TampilAscending(banyakbarang) : TampilDescending(0,banyakbarang-1);
	cout << "------------------------------------------------------" << endl;
	cout << "| NO |Nama                          | Harga   | Stok |" << endl;
	cout << "------------------------------------------------------" << endl;
	for (int i =0 ; i<banyakbarang; i++){
		cout << left << "|" << setw(4) << i+1
        << "|" << setw(30) << brg[i].nama
        << "|" << setw(9) << brg[i].harga
        << "|" << setw(6) << brg[i].stok
        << "|" << endl;
		cout << "------------------------------------------------------" << endl;
		}
		
	}else {
		cout << "Data baramg tidak tersedia " << endl;
		}
		
	YN();
	(yn == 'y') ? lihatbarang() : karyawan();
	
	}
void editbarang(){
	int index;
	int banyakbarang;
	char cari[30];
	hitungbarang(banyakbarang);
	cout << "========== Edit Barang ==========" << endl;
	cout << "Nama barang yang ingin diedit : ";
	cin >> cari;
	sequentialsearch(banyakbarang, index, cari);
	
	if (index<0){
		cout << "===== Barang Tidak Ditemukan =====" << endl;
		}else{
			cout << "========== Barang Ditemukan ==========" << endl;
			cout << "Nama  : " << brg[index].nama << endl;
			cout << "Harga : " << brg[index].harga << endl;
			cout << "Stok  : " << brg[index].stok << endl;
			cout << "========== Edit Barang ==========" << endl;
			cout << "Data barang ke-" << index+1 << endl;
			cout << "Nama  : " ;
			cin >> brg[index].nama;
			cout << "Harga : ";
			cin >> brg[index].harga;
			cout << "Stok  : ";
			cin >> brg[index].stok;
			DataBarangn = fopen("DataBarang.txt","w");

			for(int i = 0; i < banyakbarang; i++){
				fprintf(DataBarangn,"%s %d %d\n",
				brg[i].nama,
				brg[i].harga,
				brg[i].stok);
			}
			
			
		}
	fclose(DataBarangn);
	
	
	YN();
	(yn == 'y') ? editbarang() : karyawan();
}


void sequentialsearch(int banyakbarang, int &index, char cari[]){
	bool ditemukan = false;

	for(int i=0; i<banyakbarang; i++){

		if(strcmp(brg[i].nama, cari) == 0){
			index = i;
			ditemukan = true;
			break;
		}
	}

	if(!ditemukan){
		index = -1;
	}
}

int binarySearch(int n, char cari[]){

    int kiri = 0;
    int kanan = n - 1;

    while(kiri <= kanan){

        int tengah = (kiri + kanan) / 2;

        int hasil = strcmp(brg[tengah].nama, cari);

        if(hasil == 0){
            return tengah;
        }

        else if(hasil > 0){
            kanan = tengah - 1;
        }

        else{
            kiri = tengah + 1;
        }
    }

    return -1;
}

void caribarang(){
	int banyakbarang;
	int index;
	char cari[30];
	int pilih;
	hitungbarang(banyakbarang);
	do{
		cout << "========== Cari Barang ==========" << endl;
		cout << "1. Metode Binery " << endl;
		cout << "2. Sequential " << endl;
		cout << "Pilih : ";
		cin >> pilih;
		}while(pilih !=1 and pilih !=2);
	cout << "Masukan nama barang yang dicari : ";
	cin >> cari;
	if(pilih==1){
		index = binarySearch(banyakbarang, cari);
		}else{
			sequentialsearch(banyakbarang, index, cari);
			}
	if (index>=0){
		
		cout << "========== Cari Barang ==========" << endl;
		cout << "Nama  : " << brg[index].nama << endl;
		cout << "Harga : " << brg[index].harga << endl;
		cout << "Stok  : " << brg[index].stok << endl;
		}else{
		cout << "===== Barang Tidak Ditemukan =====" << endl;
			}
		
		YN();
		(yn == 'y') ? caribarang() : karyawan();
	}
	
// keluar

void keluar(){
	cout << "========== Selamat Tinggal ==========" << endl;
	}

// main 

int main(){
	login();
	}

