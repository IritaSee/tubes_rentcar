#include <stdio.h>
#include <string.h>

void login_admin();
void menu_admin();
void pause();

char nama[100], pass[100];
int pil;

struct
{ int tanggal, bulan, tahun; }tgl;

FILE *dataread;

main()
{
    system("cls");
    printf("\t==============================\n");
    printf("\t Selamat datang di D'Rent'!\n");
    printf("\t==============================\n");
    printf("\n1. Registrasi\n2. Login\n3. Login sebagai Admin\n4. Exit\nPilhan: ");
    scanf("%d",&pil); getchar();
    switch(pil)
    {
        case 1: ;break;
        case 2: ;break;
        case 3: login_admin();break;
        case 4: exit(1);break;
        default:
		{printf("\nPilihan Salah, silahkan pilih lagi!!!\n");pause();main();break;}
    }
    
}

void pause()
{ system("pause"); }

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
void menu_admin()
{
	system("cls");
    printf("\t========================\n");
	printf("\t     D'Rent' Admin\n");
	printf("\t========================\n");
	printf("\n1. Update Tanggal\n2. Exit\nPilhan: ");
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
	   		}
	   		
			case 2: main();
			default: {printf("\nPilihan salah!!!, silahkan coba lagi\n");pause();menu_admin();break;}
	}
}


