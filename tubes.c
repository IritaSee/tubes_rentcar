//Pastikan Admin telah setup tanggal saat ini dan stok awal kendaraan
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

int i, j, o, pil, pil2, ubah, mob, mot, dur1, dur2, dur3, durtot, durtot2, durtot3, tambahdurasi;
char nama[100], pass[100];
struct{ int jadwal, stok_mobil, stok_motor; } add, add2[100], add3[100];
struct{ int tanggal, bulan, tahun; } tgl;
struct
	{	
		char nama[100], pass[100], sewaan[100]; 
  		int mobil, motor, status, jadwal, tanggal, bulan, tahun, durasi; 
	} akun;
struct
	{	
		char nama[100], pass[100], sewaan[100]; 
		int mobil, motor, status, jadwal, tanggal, bulan, tahun, durasi; 
	} data2[100], temp;

FILE *dataread; FILE *dataread2; FILE *dataread3; FILE *datadel;

// Program
main() 
{
    system("cls");
    printf("\t==============================\n");
    printf("\t  Selamat datang di D'Rent!\n");
    printf("\t==============================\n");
    printf("\n1. Registrasi\n2. Login\n3. Login sebagai Admin\n4. Exit\nPilhan : ");
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
	printf("\nUsername   : ");gets(akun.nama);
	printf("Password   : ");gets(akun.pass);
	akun.status=0;
	fwrite(&akun,sizeof(akun),1,dataread);
	printf("\n\nAkun Berhasil dibuat !!!\n"); pause();
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
	printf("\nUsername   : ");gets(nama);
	printf("Password   : ");gets(pass);
	while(fread(&akun,sizeof(akun),1,dataread)==1){
		if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
		{
			printf("\nSelamat Datang %s !!!\n\n", akun.nama);pause();
			fclose(dataread);
			menu_user();break;
		}
	}
	printf("\nLogin gagal, Username atau Password tidak sesuai !!!\n\n");fclose(dataread);pause();main();
}

void menu_user()
{
	i=0; o=0;
	cls();
	//Cek Tanggal Saat Ini
	dataread3=fopen("tanggal.dat","rb");
	while(fread(&tgl,sizeof(tgl),1,dataread3)==1);
	fclose(dataread3);
	
	//Pengembalian Otomatis
	dur1=tgl.tanggal;
	dur2=tgl.bulan * 30;
	dur3=tgl.tahun * 365;
	durtot=dur1 + dur2 + dur3;
	dataread=fopen("data.dat","rb+");
	while(fread(&akun,sizeof(akun),1,dataread)==1)
	{
		if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
		{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }
	}
	if ((akun.durasi<durtot) && (akun.status!=0))
	{
		printf("\t====================\n");
		printf("\t   Peringatan !!!\n");
		printf("\t====================\n\n");
		dataread2=fopen("stok.dat","rb");
		while(fread(&add,sizeof(add),1,dataread2)==1)
		{
			if(add.jadwal==akun.jadwal)
			{ break; }
		}
		datadel=fopen("stok2.dat","wb+");
		fseek(dataread2, 0, SEEK_SET);
		while (fread(&add3[o],sizeof(add3[o]),1, dataread2)==1)
		{ 
			if (add3[o].jadwal!=akun.jadwal)
			{ fwrite(&add3[o], sizeof(add3[o]), 1, datadel); } 
			o++;
		} 
		fclose(dataread2); fclose(datadel); 
		remove("stok.dat"); rename("stok2.dat","stok.dat"); 
		if (akun.mobil==1)
			{ 
				akun.mobil=akun.mobil-1;
				add.stok_mobil=add.stok_mobil+1;
				printf("Durasi Mobil yang Anda sewa telah habis, Mobil yang Anda pinjam berhasil dikembalikan\n\n");
			}
		if (akun.motor==1)
			{ 
				akun.motor=akun.motor-1; 
				add.stok_motor=add.stok_motor+1;
				printf("Durasi Motor yang Anda sewa telah habis, Motor yang Anda pinjam berhasil dikembalikan\n\n");
			}
		akun.status=0; 
		add.jadwal=akun.jadwal;
		akun.jadwal=0;
		dataread2=fopen("stok.dat","ab");
		fwrite(&add, sizeof(add), 1, dataread2);fclose(dataread2);
		fwrite(&akun, sizeof(akun), 1, dataread);
		pause();
	}
	fclose(dataread);
	
	//Menu User
	cls();
	printf("\t===============\n");
	printf("\t   Menu User\n");
	printf("\t===============\n");
	printf("\n1. Sewa Kendaraan\n2. Cek Status Sewa\n3. Perpanjang Durasi Sewa\n4. Pengembalian Kendaraan\n5. Kembali\nPilihan : ");
	scanf("%d",&pil);getchar();
	switch(pil)
	{
		case 1 : 
		{
			cls();
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1)
			{
				if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
				{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }
			}
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
					akun.mobil=1; akun.status=1; akun.jadwal=pil; strcpy(akun.sewaan, "Mobil");
					akun.tanggal=tgl.tanggal+2; akun.bulan=tgl.bulan; akun.tahun=tgl.tahun;
					add.stok_mobil=add.stok_mobil-1;
					dur1=tgl.tanggal;
					dur2=tgl.bulan * 30;
					dur3=tgl.tahun * 365;
					akun.durasi=dur1+dur2+dur3;
					fwrite(&add, sizeof(add), 1, dataread2);
					fwrite(&akun, sizeof(akun), 1, dataread);
					fclose(dataread); fclose(dataread2);
					printf("Anda berhasil menyewa mobil selama 2 hari !!!\n\n"); pause();
					menu_user(); break;
				}
				case 2 :
				{
					akun.motor=1; akun.status=1; akun.jadwal=pil; strcpy(akun.sewaan, "Motor");
					akun.tanggal=tgl.tanggal+2; akun.bulan=tgl.bulan; akun.tahun=tgl.tahun;
					add.stok_motor=add.stok_motor-1;
					dur1=tgl.tanggal;
					dur2=tgl.bulan * 30;
					dur3=tgl.tahun * 365;
					akun.durasi=dur1+dur2+dur3;
					fwrite(&add, sizeof(add), 1, dataread2);
					fwrite(&akun, sizeof(akun), 1, dataread);
					fclose(dataread); fclose(dataread2);
					printf("Anda berhasil menyewa motor selama 2 hari !!!\n\n"); pause();
					menu_user(); break;
				}
				case 3 : menu_user(); break;
				default: printf("\nPilihan salah!!!, silahkan coba lagi\n\n");pause();menu_user();break;
			}
		}
		case 2 :
		{
			cls();
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1)
			{
				if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
				{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }
			}
			printf("\t=================\n");
			printf("\t   Status Sewa\n");
			printf("\t=================\n\n");
			printf("== Tanggal Saat ini %d - %d - %d ==\n", tgl.tanggal, tgl.bulan, tgl.tahun);
			if (akun.status==0) { printf("\nSaat ini Anda belum menyewa kendaraan\n\n"); pause();menu_user(); }
			dur1=tgl.tanggal;
			dur2=tgl.bulan * 30;
			dur3=tgl.tahun * 365;
			durtot=dur1 + dur2 + dur3;
			
			dur1=akun.tanggal;
			dur2=akun.bulan * 30;
			dur3=akun.tahun * 365;
			durtot2=dur1 + dur2 + dur3;
			
			durtot3=durtot2 - durtot;
			printf("\nSisa Durasi Sewa mu %d hari lagi!!\n\n", durtot3); pause();
			fclose(dataread);
			menu_user(); break;
		}
		case 3 :
		{
			system("cls");
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1)
			{
				if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
				{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }
			}
			printf("\t======================\n");
			printf("\t  Tambah Durasi Sewa \n");
			printf("\t======================\n\n");
			if (akun.status==0) { printf("\nSaat ini Anda belum menyewa kendaraan\n"); pause();menu_user(); }
			// Memposisikan Indikator File
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1){
			if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
			{ fseek(dataread,-sizeof(akun),SEEK_CUR); break; }}
			
			printf("Berapa lama Anda ingin perpanjang kendaraan Anda? ( Dalam Hari ) \n=> "); scanf("%d", &tambahdurasi);
			akun.tanggal=akun.tanggal+tambahdurasi;
			fwrite(&akun, sizeof(akun), 1, dataread);fclose(dataread);
			pause(); menu_user(); break;
		}
		case 4 :
		{
			i=0, o=0;
			system("cls");
			dataread=fopen("data.dat","rb+");
			while(fread(&akun,sizeof(akun),1,dataread)==1)
			{
				if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0)
				{ fseek(dataread,-sizeof(akun), SEEK_CUR); break; }
			}
			dataread2=fopen("stok.dat","rb");
			while(fread(&add,sizeof(add),1,dataread2)==1)
			{
				if(add.jadwal==akun.jadwal)
				{ break; }
			}
			fseek(dataread2, 0, SEEK_SET);
			datadel=fopen("stok2.dat","wb+");
			while (fread(&add3[o],sizeof(add3[o]),1, dataread2)==1)
			{ 
				if (add3[o].jadwal!=akun.jadwal)
				{ fwrite(&add3[o], sizeof(add3[o]), 1, datadel); } 
				o++;
			} 
			fclose(dataread2); fclose(datadel); 
			remove("stok.dat"); rename("stok2.dat","stok.dat"); 
			
			printf("\t=======================\n");
			printf("\t  Pengembalian Manual \n");
			printf("\t=======================\n\n");
			if (akun.status==0) { printf("Saat ini Anda belum menyewa kendaraan\n\n"); pause();menu_user(); }
			
			if (akun.mobil==1)
			{ 
				akun.mobil=akun.mobil-1;
				add.stok_mobil=add.stok_mobil+1;
				printf("Mobil yang telah Anda pinjam berhasil dikembalikan\n\n");
			}
			if (akun.motor==1)
			{ 
				akun.motor=akun.motor-1; 
				add.stok_motor=add.stok_motor+1;
				printf("Motor yang telah Anda pinjam berhasil dikembalikan\n\n");
			}
			akun.status=0; 
			add.jadwal=akun.jadwal;
			akun.jadwal=0;
			dataread2=fopen("stok.dat","ab");
			fwrite(&add, sizeof(add), 1, dataread2);fclose(dataread2);
			fwrite(&akun, sizeof(akun), 1, dataread);fclose(dataread);
			pause(); menu_user(); break;
		}
		case 5 : main(); break;
		default: printf("\nPilihan salah !!!, silahkan coba lagi\n\n"); pause(); menu_user(); break;
	}
}

void login_admin()
{
	system("cls");
	printf("\t============================\n");
	printf("\t      Menu Login Admin\n");
	printf("\t============================\n");
	printf("\nUsername   : ");gets(nama);
    printf("Password   : ");gets(pass);
    if(strcmp(nama,"admin")==0 && strcmp(pass,"admin")==0)
	{
		printf("\nLogin berhasil, Selamat datang Admin !!!\n\n");
		pause();
		menu_admin();
	}
	else printf("\nLogin gagal, Username atau Password tidak sesuai !!!\n\n");
	pause();
	main();
}

void menu_admin()
{
	system("cls");
    printf("\t========================\n");
	printf("\t     D'Rent' Admin\n");
	printf("\t========================\n");
	printf("\n1. Update Tanggal\n2. Cek dan Ubah Stok Kendaraan\n3. Tampilkan List Tersewa\n4. Kembali\nPilihan : ");
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
				printf(" === Tanggal Berhasil diubah !!! === \n\n");
				fclose(dataread);
				pause();
				menu_admin();
				break;
	   		}
			case 2:
			{
				i=0;
				system("cls");
				printf("\t==================================\n");
				printf("\t     Cen dan Ubah Stok Kendaraan\n");
				printf("\t==================================\n\n");
				printf("1. Senin\n2. Rabu\n3. Sabtu\n4. Minggu\nPilih Jadwal : "); scanf("%d",&pil);
				dataread = fopen("stok.dat","rb");
				
				//Baca Stok
				while(fread(&add2[i],sizeof(add2[i]),1,dataread)==1)
				{
					if(pil==add2[i].jadwal)
					{ 
					  printf("\nJumlah Stok Saat ini : \n1. Mobil : %d\n", add2[i].stok_mobil); 
					  printf("2. Motor : %d\n", add2[i].stok_motor); break;
					}
					i++;
				}
				
				//Ubah Stok
				printf("\nPilih Stok yang ingin diubah\n1. Mobil\n2. Motor\n3. Kembali\nPilihan : ");scanf("%d",&pil2);
				switch(pil2)
				{
					case 1 : 
					{
						printf("\nUbah jumlah stok Mobil menjadi : ");
						scanf("%d",&add2[i].stok_mobil);
						
						datadel = fopen("stok2.dat", "wb");
						fseek(dataread, 0, SEEK_SET); 
						int o=0; 
						while (fread(&add3[o],sizeof(add3[o]),1, dataread)==1)
						{ 
							if (add3[o].jadwal!=pil)
							{ fwrite(&add3[o], sizeof(add3[o]), 1, datadel); } 
						} 
						fclose(dataread); fclose(datadel); 
						remove("stok.dat"); rename("stok2.dat","stok.dat"); 
						
						add2[i].jadwal=pil;
						dataread = fopen("stok.dat","ab");
						fwrite(&add2[i],sizeof(add2[i]),1,dataread);
						fclose(dataread);
						printf("\n === Stok Mobil berhasil diubah !!! ===\n\n "); pause();
						menu_admin(); break;
					}
					case 2 : 
					{
						printf("\nUbah jumlah stok motor menjadi : ");
						scanf("%d",&add2[i].stok_motor);
						
						datadel = fopen("stok2.dat", "wb");
						fseek(dataread, 0, SEEK_SET); 
						int o=0; 
						while (fread(&add3[o],sizeof(add3[o]),1, dataread)==1)
						{ 
							if (add3[o].jadwal!=pil)
							{ fwrite(&add3[o], sizeof(add3[o]), 1, datadel); } 
							o++;
						} 
						fclose(dataread); fclose(datadel); 
						remove("stok.dat"); rename("stok2.dat","stok.dat"); 
						
						add2[i].jadwal=pil;
						dataread = fopen("stok.dat","ab");
						fwrite(&add2[i],sizeof(add2[i]),1,dataread);
						fclose(dataread);
						printf("\n === Stok Motor berhasil diubah !!! ===\n\n "); pause();
						menu_admin(); break;
					}
					case 3 :
					{
						fclose(dataread);
						menu_admin(); break;
					}
					default: printf("\nPilihan salah !!!, silahkan coba lagi\n\n");pause();menu_admin();break;
				}
			}
			case 3:
			{
				int o=0;
				system("cls");
				printf("\t==================\n");
				printf("\t   List Tersewa\n");
				printf("\t===================\n\n");
				dataread = fopen("data.dat", "rb");
				while (fread(&data2[o],sizeof(data2[o]),1,dataread)==1)
				{ o++; }
				//Bubble Sort
				for (i=o-1;i>=1;i--)
				for (j=1;j<=i;j++)
				{ 
					if (data2[j-1].durasi>data2[j].durasi)
					{
						temp=data2[j-1];
						data2[j-1]=data2[j];
						data2[j]=temp;
					} 
				}
				//Output Sorting
				for(i=0;i<o;i++)
				{
					if(data2[i].status!=0)
					{ printf("%d. Username '%s' menyewa %s sampai tanggal %d - %d - %d\n", i+1, data2[i].nama, data2[i].sewaan, data2[i].tanggal, data2[i].bulan, data2[i].tahun ); }
				}
				printf("\n"); pause(); menu_admin(); break;
			}
			case 4: main();break;
			default: printf("\n\nPilihan salah !!!, silahkan coba lagi\n\n");pause();menu_admin();break;
		}
}

