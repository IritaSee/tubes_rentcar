#include <stdio.h>
#include <string.h>


// Deklarasi variabel (ikut PRI)
void regis_user();
void login_user();
void login_admin();
void menu_user();
void menu_admin();
void pause();
void cls();
void add_motor();
void add_mobil();

int pil;
char nama[100], pass[100];
FILE *dataread;
struct
{
	int stok_mobil, stok_motor;
}add;

struct
{ int tanggal, bulan, tahun; 
}tgl;

main() // dari sini ke bawah ada conflict, aku gabung punya FER sama PRI, soalnya FER frontendnya lebih bagus dan PRI backend nya mulai keliatan
{
    system("cls");
    printf("\t==============================\n");
    printf("\t Selamat datang di D'Rent'!\n");
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
		{printf("\nPilihan Salah, silahkan pilih lagi!!!\n");pause();main();break;}
    }
}

struct
{
	char nama[100], pass[100];
}akun;

void pause(){
	system("pause");
}

void cls(){
	system("cls");
}

void regis_user(){
	cls();
	dataread=fopen("akunuser.dat","ab");
	printf("REGISTRASI AKUN\n");
	printf("Username\t: ");gets(akun.nama);
	printf("Password\t: ");gets(akun.pass);
	fwrite(&akun,sizeof(akun),1,dataread);
	fclose(dataread);
	main();
	
}

void login_user(){
	cls();
	dataread=fopen("akunuser.dat","rb");
	printf("\t=========================\n");
	printf("\t      Menu Login User\n");
	printf("\t=========================\n");
	printf("Username\t: ");gets(nama);
	printf("Password\t: ");gets(pass);
	while(fread(&akun,sizeof(akun),1,dataread)==1){
		if(strcmp(nama,akun.nama)==0 && strcmp(pass,akun.pass)==0){
			printf("welcome\n");fclose(dataread);pause();
			menu_user();
		}
		else printf("login gagal\n");fclose(dataread);pause();main();
	}
}

void menu_user(){
	//ini menu user
	cls();
	printf("MENU USER:\n1. Tampilkan dan Pilih Jadwal\n2. \n3. \nPilihan = ");
	scanf("%d",&pil);getchar();
	switch(pil)
	{
		case 1 : 
		{
			printf("Pilih Jenis Kendaraan\n 1.Mobil\n2.Motor\nPilihan : ");scanf("%d",&pil);
			switch(pil)
			{
				case 1 :
				{
					dataread = fopen("data.dat","rb");
					while((fread(&add,sizeof(add),1,dataread))==1)
					{
					}
					printf("Jumlah Stok Mobil : %d",add.stok_mobil);
					fclose(dataread);rewind(dataread);
					break;
				}
				case 2 :
				{
					dataread = fopen("data.dat","rb");
					while((fread(&add,sizeof(add),1,dataread))==1)
					{
					}
					printf("Jumlah Stok Motor : %d",add.stok_motor);
					fclose(dataread);rewind(dataread);
					break;	
				}
			}
			
		}
	}
}

void login_admin()
{
	system("cls");
	printf("\t============================\n");
	printf("\t      Menu Login Admin\n");
	printf("\t============================\n");
	printf("\nNama	 : ");gets(nama);
    printf("Password : ");gets(pass);
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
//your code goes here... semangaat!!!
// SIAAPP BANGGG!!!

void menu_admin()
{
	system("cls");
    printf("\t========================\n");
	printf("\t     D'Rent' Admin\n");
	printf("\t========================\n");
	printf("\n1. Update Tanggal\n2. Tambah Kendaraan\n3.Exit\nPilihan: ");
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
				printf("Tanggal  : "); scanf("%d", &tgl.tahun);
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
				printf("\t========================\n");
				printf("\t     Pilih Kendaraan\n");
				printf("\t========================\n");
				printf("1. Mobil\n2. Motor\nPilihan : ");scanf("%d",&pil);getchar();
				switch(pil)
				{
					case 1 : add_mobil();break;
					case 2 : add_motor();break;
				}
				break;
			}
			case 3: main();break;
			default: printf("\nPilihan salah!!!, silahkan coba lagi\n");pause();menu_admin();break;
		}
}



void add_mobil()
{
	dataread = fopen("data.dat","ab");
	printf("Masukan Jumlah Stok Mobil : ");
	scanf("%d",&add.stok_mobil);
	fwrite(&add,sizeof(add),1,dataread);
	fclose(dataread);rewind(dataread);
	menu_admin();
}

void add_motor()
{
	dataread = fopen("data.dat","ab");
	printf("Masukan Jumlah Stok Motor : ");
	scanf("%d",&add.stok_motor);
	fwrite(&add,sizeof(add),1,dataread);
	fclose(dataread);rewind(dataread);
	menu_admin();
}
