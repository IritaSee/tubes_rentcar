#include <stdio.h>
#include <string.h>

// Deklarasi
void regis_user();
void login_user();
void login_admin();
void menu_user();
void menu_admin();
void pause();
void cls();

int i, pil, pil2, ubah, mob, mot, dur1, dur2, dur3, durtot, durtot2, durtot3, tambahdurasi;
char nama[100], pass[100];
struct{ int jadwal, stok_mobil, stok_motor; } add;
struct{ int tanggal, bulan, tahun; } tgl;
struct
	{	
		char nama[100], pass[100], sewaan[100]; 
  		int mobil, motor, status, jadwal, tanggal, bulan, tahun; 
	} akun;

FILE *dataread; FILE *dataread2; FILE *dataread3; FILE *datadel;

// Program
main() 
{
    system("cls");
    printf("\t==============================\n");
    printf("\t  Selamat datang di D'Rent!\n");
    printf("\t==============================\n");
    printf("\n1. Registrasi\n2. Login\n3. Login sebagai Admin\n4. Exit\nPilhan: ");
    scanf("%d",&pil); getchar();
    switch(pil)
    {
        case 1: regis_user();break;
        case 2: login_user();break;
        case 3: login_admin();break;
        case 4: system("exit");break;
        default:
		{ printf("\nPilihan Salah, silahkan pilih lagi!!!\n");pause();main();break; }
    }
}

void pause(){ system("pause"); }
void cls(){ system("cls"); }

void regis_user()
{
	cls();
	dataread=fopen("data.dat","ab");
	printf("\t===================\n");
    printf("\t  Registrasi Akun\n");
    printf("\t===================\n");
	printf("\nUsername\t: ");gets(akun.nama);
	printf("Password\t: ");gets(akun.pass);
	fwrite(&akun,sizeof(akun),1,dataread);
	printf("\nAkun Berhasil dibuat !!!\n"); pause();
	fclose(dataread);
	main();
	
}

void login_user()
{
	cls();
	dataread=fopen("data.dat","rb+");
	printf("\t================\n");
	printf("\t   Login User\n");
	printf("\t================\n");
	printf("\nUsername\t: ");gets(nama);
	printf("Password\t: ");gets(pass);
	while(fread(&akun,sizeof(akun),1,dataread)==1){
		if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
		{
			printf("welcome\n");pause();
			fseek(dataread,-sizeof(akun),SEEK_CUR);
			menu_user();break;
		}
	}
	printf("login gagal\n");fclose(dataread);pause();main();
}

void menu_user()
{
	cls();
	dataread3=fopen("tanggal.dat","rb");
	while(fread(&tgl,sizeof(tgl),1,dataread3)==1);
	fclose(dataread3);
	printf("MENU USER:\n1. Sewa Kendaraan\n2. Cek Status Sewa\n3. Perpanjang Durasi Sewa\n4. Pengembalian Barang\n5. Kembali\nPilihan = ");
	scanf("%d",&pil);getchar();
	switch(pil)
	{
		case 1 : 
		{
			cls();
			printf("\t===============\n");
			printf("\t   Menu Sewa\n");
			printf("\t===============\n\n");
			dataread2=fopen("stok.dat","rb+");
			if (akun.status!=0) { printf("Maaf anda harus mengembalikan sewaan dahulu untuk menyewa kembali, cek kembali status sewa anda\n"); pause();menu_user(); }
			printf("1. Senin\n2. Rabu\n3. Sabtu\n4. Minggu\nPilihan : ");scanf("%d",&pil);
			while(fread(&add,sizeof(add),1,dataread2)==1)
				{
					if(pil==add.jadwal)
					{ 
					  printf("\nJumlah Stok Pertanggal %d - %d - %d :\n1. Mobil : %d\n", tgl.tanggal, tgl.bulan, tgl.tahun, add.stok_mobil); 
					  printf("2. Motor : %d\n", add.stok_motor); 
					  fseek(dataread2,-sizeof(add),SEEK_CUR); break;
					}
				}	
			printf("\nPilih Jenis Kendaraan untuk 2 Hari Anda\n1. Mobil\n2. Motor\n3. Kembali\nPilihan : ");scanf("%d",&pil2);
			switch(pil2)
			{
				case 1 :
				{
					akun.mobil=1; akun.status=1; akun.jadwal==pil; strcpy(akun.sewaan, "Mobil");
					akun.tanggal=tgl.tanggal+2; akun.bulan=tgl.bulan; akun.tahun=tgl.tahun;
					add.stok_mobil=add.stok_mobil-1;
					fwrite(&add, sizeof(add), 1, dataread2);
					fwrite(&akun, sizeof(akun), 1, dataread);
					fclose(dataread); fclose(dataread2);
					printf("Anda berhasil menyewa mobil selama 2 hari !!!)");
					menu_user(); break;
				}
				case 2 :
				{
					akun.motor=1; akun.status=1; akun.jadwal==pil; strcpy(akun.sewaan, "Motor");
					akun.tanggal=tgl.tanggal+2; akun.bulan=tgl.bulan; akun.tahun=tgl.tahun;
					add.stok_motor=add.stok_motor-1;
					fwrite(&add, sizeof(add), 1, dataread2);
					fwrite(&akun, sizeof(akun), 1, dataread);
					fclose(dataread); fclose(dataread2);
					printf("Anda berhasil menyewa motor selama 2 hari !!!)");
					menu_user(); break;
				}
				case 3 : menu_user(); break;
				default: printf("\nPilihan salah!!!, silahkan coba lagi\n");pause();menu_user();break;
			}
		case 2 :
		{
			cls();
			printf("\t=================\n");
			printf("\t   Status Sewa\n");
			printf("\t=================\n\n");
			printf("== Tanggal Saat ini %d - %d - %d ==\n", tgl.tanggal, tgl.bulan, tgl.tahun);
			
			dur1=tgl.tanggal;
			dur2=tgl.bulan * 30;
			dur3=tgl.tahun * 365;
			durtot=dur1 + dur2 + dur3;
			
			dur1=akun.tanggal;
			dur2=akun.bulan * 30;
			dur3=akun.tahun * 365;
			durtot2=dur1 + dur2 + dur3;
			
			durtot3=durtot2 - durtot;
			printf("Sisa Durasi Sewa mu %d hari lagi!!\n", durtot3); pause();
			menu_user(); break;
		}
		case 3 :
		{
			system("cls");
			printf("\t======================\n");
			printf("\t  Tambah Durasi Sewa \n");
			printf("\t======================\n\n");
			// Memposisikan Indikator File
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1){
			if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
			{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }}
			
			printf("Berapa Lama ingin diperpanjang? "); scanf("%d", &tambahdurasi);
			akun.tanggal=akun.tanggal+tambahdurasi;
			fwrite(&akun, sizeof(akun), 1, dataread);fclose(dataread);
			pause(); menu_user(); break;
		}
		case 4 :
		case 5 : main(); break;
		default: printf("\nPilihan salah!!!, silahkan coba lagi\n"); pause(); menu_user(); break;
		}
	}
}

void login_admin()
{
	system("cls");
	printf("\t============================\n");
	printf("\t      Menu Login Admin\n");
	printf("\t============================\n");
	printf("\nUsername  : ");gets(nama);
    printf("Password  : ");gets(pass);
    if(strcmp(nama,"admin")==0 && strcmp(pass,"admin")==0)
	{
		printf("\nLogin berhasil, selamat datang Admin !!!\n");
		pause();
		menu_admin();
	}
	else printf("\nNama atau Password tidak sesuai !!!\n");
	pause();
	main();
}

void menu_admin()
{
	system("cls");
    printf("\t========================\n");
	printf("\t     D'Rent' Admin\n");
	printf("\t========================\n");
	printf("\n1. Update Tanggal\n2. Ubah Stok Kendaraan\n3. Tampilkan List Tersewa\n4. Exit\nPilihan: ");
	scanf("%d",&pil);getchar();
	switch(pil)
	    {
	        case 1: 
	        {
	        	system("cls");
				printf("\t========================\n");
				printf("\t     Update Tanggal\n");
				printf("\t========================\n");
				
				dataread = fopen("tanggal.dat","rb");
				while(fread(&tgl,sizeof(tgl),1,dataread)==1)
				{ 
					printf("\nTanggal saat ini   : %d ", tgl.tanggal);
					printf("- %d ", tgl.bulan);
					printf("- %d", tgl.tahun);
				}
				fclose(dataread);rewind(dataread);
				
				dataread = fopen("tanggal.dat","wb");
				printf("\n\n== Update ==\n");
				printf("Tanggal  : "); scanf("%d", &tgl.tanggal);
				printf("Bulan    : "); scanf("%d", &tgl.bulan);
				printf("Tahun    : "); scanf("%d", &tgl.tahun);
				fwrite(&tgl,sizeof(tgl),1,dataread);
					
				printf("\n\n");
				printf(">>>> Tanggal Berhasil diubah !!! <<<<\n\n\n");
				fclose(dataread);
				pause();
				menu_admin();
				break;
	   		}
			case 2:
			{
				system("cls");
				printf("\t===========================\n");
				printf("\t     Ubah Stok Kendaraan\n");
				printf("\t===========================\n");
				add.stok_mobil=0; add.stok_motor=0;
				printf("1. Senin\n2. Rabu\n3. Sabtu\n4. Minggu\nPilih Jadwal : "); scanf("%d",&pil);
				dataread = fopen("stok.dat","rb");
				
				// Baca Stok
				while(fread(&add,sizeof(add),1,dataread)==1)
				{
					if(pil==add.jadwal)
					{ 
					  printf("\nJumlah Stok Saat ini : \n1. Mobil : %d\n", add.stok_mobil); 
					  printf("2. Motor : %d\n", add.stok_motor); 
					}
				}
				
				
				// Tambah Stok
				printf("\nPilih Stok yang ingin diubah\n1. Mobil\n2. Motor\n3. Kembali\nPilihan : ");scanf("%d",&pil2);
				switch(pil2)
				{
					case 1 : 
					{
						printf("Ubah jumlah stok mobil menjadi : ");
						scanf("%d",&mob); mot=add.stok_motor;
						datadel = fopen("stok2.dat", "wb");
						fseek(dataread, 0, SEEK_SET);  
						while (fread(&add,sizeof(add),1, dataread)==1)
						{ 
							if (add.jadwal!=pil)
							{ fwrite(&add, sizeof(add), 1, datadel); } 
						} 
						fclose(dataread); fclose(datadel); 
						remove("stok.dat"); rename("stok2.dat","stok.dat"); 
						
						add.jadwal=pil; add.stok_mobil=mob; add.stok_motor=mot;
						dataread = fopen("stok.dat","ab");
						fwrite(&add,sizeof(add),1,dataread);
						fclose(dataread);
						menu_admin(); break;
					}
					case 2 : 
					{
						printf("Ubah jumlah stok motor menjadi : ");
						scanf("%d",&mot); mob=add.stok_mobil;
						datadel = fopen("stok2.dat", "wb");
						fseek(dataread, 0, SEEK_SET);  
						while (fread(&add,sizeof(add),1, dataread)==1)
						{ 
							if (add.jadwal!=pil)
							{ fwrite(&add, sizeof(add), 1, datadel); } 
						} 
						fclose(dataread); fclose(datadel); 
						remove("stok.dat"); rename("stok2.dat","stok.dat"); 
						
						add.jadwal=pil; add.stok_mobil=mob; add.stok_motor=mot;
						dataread = fopen("stok.dat","ab");
						fwrite(&add,sizeof(add),1,dataread);
						fclose(dataread);
						menu_admin(); break;
					}
					case 3 :
					{
						fclose(dataread);
						menu_admin(); break;
					}
					default: printf("\nPilihan salah!!!, silahkan coba lagi\n");pause();menu_admin();break;
				}
			}
			case 3:
			{
				system("cls");
				printf("\t==================\n");
				printf("\t   List Tersewa\n");
				printf("\t===================\n\n");
				dataread = fopen("data.dat", "rb");
				i=0;
				while(fread(&akun,sizeof(akun),1,dataread)==1)
				{
					if(akun.status!=0)
					{ printf("%d. Username '%s' menyewa %s sampai tanggal %d - %d - %d\n", i+1, akun.nama, akun.sewaan, akun.tanggal, akun.bulan, akun.tahun ); }
					i++;
				}
				pause(); menu_admin(); break;
			}
			case 4: main();break;
			default: printf("\nPilihan salah!!!, silahkan coba lagi\n");pause();menu_admin();break;
		}
}


