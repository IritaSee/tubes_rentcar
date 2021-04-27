#include <stdio.h>

// Deklarasi variabel
void regis_user();
void login_user();
void login_admin();
void menu_user();
void menu_admin();
void pause();
void cls();

int pil;
char nama[100], pass[100];
FILE *dataread;

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

main(){
    system("cls");
    printf("\t================================\n");
    printf("\t\t Selamat datang!\n");
    printf("\t================================\n");
    printf("\n1. Registrasi\n2. Login\n3. Login sebagai Admin\n4. Exit\nPilhan: ");
    scanf("%d",&pil); getchar();
    switch(pil){
    	case 1: regis_user();break;
    	case 2: login_user();break;
    	case 3: login_admin();break;
    	case 4: system("exit");break;
	}
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

void login_admin(){
	cls();
	printf("login admin\n");
	printf("Username\t: ");gets(nama);
	printf("Password\t: ");gets(pass);
	if(strcmp(nama,"admin")==0 && strcmp(pass,"admin")==0){
		printf("selamat datang admin\n");pause();
		menu_admin();
	}
	else printf("Username atau pass salah !!\n");pause();
	main();
	
}
void menu_user(){
	//ini menu user
	cls();
	printf("MENU USER:\n1. \n2. \n3. \n");
}

void menu_admin(){
	//ini menu admin
	cls();
	printf("MENU ADMIN:\n1. \n2. \n3. \n");
}

//your code goes here... semangaat!!!
// SIAAPP BANGGG!!!
