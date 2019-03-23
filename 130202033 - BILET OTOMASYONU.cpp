#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

void sefer_islemleri();
void sefer_ekle();
void sefer_sil();
void kaptan_degis();
void gelir_hesapla();
void sefer_listele();
void sefer_sayisi();
void bilet_islemleri();
void sefer_sec();
void ara();

typedef struct sefer_bilgileri{
	char sefer_no[2];
	char nereden[20];
	char nereye[20];
	char tarihi[15];
	char saati[10];
	int kapasite;
	char plaka[15];
	char kaptan[30];
	float bilet_fiyati;
	
    struct sefer_bilgileri *sonraki, *onceki;
}*sefer;
sefer_bilgileri *ilk,*son,*gecici;

struct kisi_bilgileri{
	char ad[10];
 	char soyad[10];
 	char cinsiyet[5];
    char koltuk_durumu;
}kisi;

typedef struct koltuklar{
    int koltuk_no;
 	struct kisi_bilgileri k1;
 	
	struct koltuklar *sonraki, *onceki;
 }*koltuk;
koltuklar *ilk1,*son1,*temp;

int main()
{
	int secim;
	printf("-------------------------------BILET OTOMASYONU-------------------------------");
	menu:
	printf("\nSefer islemleri icin... [1]'e \nBilet islemleri icin... [2]'ye \nCikmak icin...          [0]'a basiniz.\n");
	
	//tarih ve saat uygulamasý
	time_t timer;
    char zaman[250];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(zaman,250,"\t\t\t\t\t\t\t--------Guncel------- \n\t\t\t\t\t\t\tSaat : %H:%M \n   \t\t\t\t\t\t\tTarih: %d.%m.%Y", tm_info);      
    puts(zaman);
    //tarih ve saat uygulamasý
    
   	printf("Secim: ");
	scanf("%d",&secim);
	
	switch(secim)
	{
		case 1: sefer_islemleri(); 	break;
		case 2: bilet_islemleri();	break;
		case 0: printf("\nProgram sonlaniyor..."); exit(0);
		default : printf("\nHATALI GIRIS, LUTFEN [1],[2] VEYA [0]'A BASINIZ !\n"); goto menu; break;
	}
	
	goto menu;
}

void sefer_islemleri()
{
	int secim1;
	while((secim1=getchar())!=EOF)
	{
		printf("\n-------------------------------SEFER ISLEMLERI-------------------------------\n");
		sefer_menu:
		printf("\nSefer eklemek icin...         [1]'e \nSefer silmek icin...          [2]'ye \nKaptani degistirmek icin...   [3]'e \nGelir hesaplamak icin...      [4]'e ");
		printf("\nSefer listelemek icin...      [5]'e \nSefer sayisini gormek icin... [6]'ya");
		printf("\nUst menuye gitmek icin...     [9]'a \nCikmak icin...                [0]'a basiniz.\n\n");
		printf("Secim: ");
		scanf("%d",&secim1);
		
		switch(secim1)
		{
			case 1: sefer_ekle();		break;
			case 2: sefer_sil(); 		break;
			case 3: kaptan_degis();		break;
			case 4: gelir_hesapla(); 	break;
			case 5: sefer_listele(); 	break;
			case 6: sefer_sayisi(); 	break;
			case 9: goto ust_menu;
			case 0: printf("\nProgram kapatiliyor..."); exit(0);
			default : printf("\nHATALI GIRIS, LUTFEN BELIRTILEN SAYILARDAN BIRINI GIRINIZ !\n"); goto sefer_menu; break;
		}
	}
	
	ust_menu:
	printf("\nUst menuye gidiliyor...\n");
}

void bilet_islemleri()
{
	int secim2;
	while((secim2=getchar())!=EOF)
	{
	
		printf("\n-------------------------------BILET ISLEMLERI-------------------------------\n");
		bilet_menu:
		printf("\nMevcut seferleri listelemek icin...   [1]'e \nSefer secmek icin...                  [2]'ye");
		printf("\nUst menuye gitmek icin...             [9]'a \nCikmak icin...                        [0]'a basiniz.\n");
		printf("Secim: ");
		scanf("%d",&secim2);
	
		switch(secim2)
		{
			case 1: sefer_listele();	break;
			case 2: sefer_sec(); 		break;
			case 9: goto ust_menu2;
			case 0: printf("\nProgram kapatiliyor..."); exit(0);
			default : printf("\nHATALI GIRIS, LUTFEN [1],[2] VEYA [0]'A BASINIZ !\n"); goto bilet_menu; break;
		}
	}
	
	ust_menu2:
	printf("\nUst menuye gidiliyor...\n");
}

void sefer_ekle()
{
	int kapasite=5;
	
	if(ilk==NULL)
	{
		ilk=(sefer_bilgileri*) malloc(sizeof(sefer_bilgileri));

		printf("Sefer numarasini giriniz: ");
		fflush(stdin); gets(ilk->sefer_no);
			
		printf("Kalkis yerini giriniz: ");
		fflush(stdin); gets(ilk->nereden);
	
		printf("Inis yerini giriniz: ");
		fflush(stdin); gets(ilk->nereye);
	
		printf("Sefer tarihini giriniz(gg.aa.yyyy): ");
		fflush(stdin); gets(ilk->tarihi);
	
		printf("Sefer saatini giriniz(ss:dd): ");
		fflush(stdin); gets(ilk->saati);
	
		printf("Otobusun kapasitesi: %d\n",kapasite);
			
		printf("Otobus plakasini giriniz: ");
		fflush(stdin); gets(ilk->plaka);
		
		printf("Kaptani giriniz(ad soyad): ");
		fflush(stdin); gets(ilk->kaptan);
		
		printf("Bilet fiyatini giriniz: ");
		fflush(stdin); scanf("%f",&ilk->bilet_fiyati);
		
		FILE *tut;
		char tutucu[20];
		
		tut=fopen("gecici.txt","w+");
		fprintf(tut,"%s",ilk->tarihi);
		fprintf(tut,".txt");
		fclose(tut);
		
		tut=fopen("gecici.txt","r+");
		fgets(tutucu,20,tut);
		fclose(tut);
		remove("gecici.txt");
		
		FILE *dosya;
		dosya=fopen(tutucu,"a+");
		
		fprintf(dosya,"Sefer No: %s\n",ilk->sefer_no);
		fprintf(dosya,"%s\n",ilk->nereden);
		fprintf(dosya,"%s\n",ilk->tarihi);
		fprintf(dosya,"%s\n",ilk->nereye);
		fprintf(dosya,"%s\n",ilk->saati);
		fprintf(dosya,"%d\n",kapasite);
		fprintf(dosya,"%s\n",ilk->plaka);
		fprintf(dosya,"%s\n",ilk->kaptan);
		fprintf(dosya,"%.2f\n",ilk->bilet_fiyati);
		
		fclose(dosya);
		
		ilk->sonraki=NULL;
		ilk->onceki=NULL;
		son=ilk;
	}
	
	else if(son==ilk)
	{
		son=(sefer_bilgileri*) malloc(sizeof(sefer_bilgileri));
		
		printf("Sefer numarasini giriniz: ");
		fflush(stdin); gets(son->sefer_no);
	
		printf("Kalkis yerini giriniz: ");
		fflush(stdin); gets(son->nereden);
	
		printf("Inis yerini giriniz: ");
		fflush(stdin); gets(son->nereye);
	
		printf("Sefer tarihini giriniz(gg.aa.yyyy): ");
		fflush(stdin); gets(son->tarihi);
	
		printf("Sefer saatini giriniz(ss:dd): ");
		fflush(stdin); gets(son->saati);
	
		printf("Otobusun kapasitesi: %d\n",kapasite);
		
		printf("Otobus plakasini giriniz: ");
		fflush(stdin); gets(son->plaka);
	
		printf("Kaptani giriniz(ad soyad): ");
		fflush(stdin); gets(son->kaptan);
	
		printf("Bilet fiyatini giriniz: ");
		fflush(stdin); scanf("%f",&son->bilet_fiyati);
		
		FILE *tut;
		char tutucu[20];
		
		tut=fopen("gecici.txt","w");
		fprintf(tut,"%s",son->tarihi);
		fprintf(tut,".txt");
		fclose(tut);
		
		tut=fopen("gecici.txt","r");
		fgets(tutucu,20,tut);
		fclose(tut);		
		remove("gecici.txt");
		
		FILE *dosya;
		dosya=fopen(tutucu,"a+");
		
		fprintf(dosya,"Sefer No: %s\n",son->sefer_no);
		fprintf(dosya,"%s\n",son->nereden);
		fprintf(dosya,"%s\n",son->tarihi);
		fprintf(dosya,"%s\n",son->nereye);
		fprintf(dosya,"%s\n",son->saati);
		fprintf(dosya,"%d\n",kapasite);
		fprintf(dosya,"%s\n",son->plaka);
		fprintf(dosya,"%s\n",son->kaptan);
		fprintf(dosya,"%.2f\n",son->bilet_fiyati);
		
		fclose(dosya);
		
		ilk->sonraki=son;
		son->sonraki=NULL;
		son->onceki = ilk;
	}
	
	else
	{
		gecici=(sefer_bilgileri*) malloc(sizeof(sefer_bilgileri));
		
		printf("Sefer numarasini giriniz: ");
		fflush(stdin); gets(gecici->sefer_no);
	
		printf("Kalkis yerini giriniz: ");
		fflush(stdin); gets(gecici->nereden);
	
		printf("Inis yerini giriniz: ");
		fflush(stdin); gets(gecici->nereye);
	
		printf("Sefer tarihini giriniz(gg.aa.yyyy): ");
		fflush(stdin); gets(gecici->tarihi);
	
		printf("Sefer saatini giriniz(ss:dd): ");
		fflush(stdin); gets(gecici->saati);
	
		printf("Otobusun kapasitesi: %d\n",kapasite);
			
		printf("Otobus plakasini giriniz: ");
		fflush(stdin); gets(gecici->plaka);
	
		printf("Kaptani giriniz(ad soyad): ");
		fflush(stdin); gets(gecici->kaptan);
	
		printf("Bilet fiyatini giriniz: ");
		fflush(stdin); scanf("%f",&gecici->bilet_fiyati);
		
		FILE *tut;
		char tutucu[20];
		
		tut=fopen("gecici.txt","w");
		fprintf(tut,"%s",gecici->tarihi);
		fprintf(tut,".txt");
		fclose(tut);
		
		tut=fopen("gecici.txt","r");
		fgets(tutucu,20,tut);
		fclose(tut);
		remove("gecici.txt");
		
		FILE *dosya;
		dosya=fopen(tutucu,"a+");
		
		fprintf(dosya,"Sefer No: %s\n",gecici->sefer_no);
		fprintf(dosya,"%s\n",gecici->nereden);
		fprintf(dosya,"%s\n",gecici->tarihi);
		fprintf(dosya,"%s\n",gecici->nereye);
		fprintf(dosya,"%s\n",gecici->saati);
		fprintf(dosya,"%d\n",kapasite);
		fprintf(dosya,"%s\n",gecici->plaka);
		fprintf(dosya,"%s\n",gecici->kaptan);
		fprintf(dosya,"%.2f\n",gecici->bilet_fiyati);
		
		fclose(dosya);
		
		son->sonraki=gecici;
		gecici->onceki=son;
		son=gecici;
		son->sonraki=NULL;
	}
  	
	
	printf("\nSEFER BASARIYLA OLUSTURULDU...\n");
	

}

void ara()
{
	char sefer_ara[2];
	
	printf("\nAranacak, Duzenlenecek, Listelenecek ya da Silinecek Seferin Numarasi: ");
	fflush(stdin); gets(sefer_ara);
	
	if(ilk==NULL)
	{
		printf("\nMEVCUT SEFER BULUNAMADI !\n");
	}
	
	else
	{
		gecici=ilk;
	
		while(strcmp(gecici->sefer_no,sefer_ara))
		{
			gecici=gecici->sonraki;
			
			if(gecici==son->sonraki)
			{
				printf("Sefer bulunamadi...");
				break;
			}
		}
	}
}

void sefer_sil()
{
	ara();
	
	if(gecici->sonraki==NULL) //son kayit silinecekse
	{
		son=son->onceki;
		son->sonraki=NULL;
		
		printf("\n%s NUMARALI SEFER SILINDI...",gecici->sefer_no);
		
		free(gecici);	
	}	
	
	else if(gecici->onceki==NULL) //ilk kayit silinecekse
	{
		ilk=ilk->sonraki;
		ilk->onceki=NULL;
		
		printf("\n%s NUMARALI SEFER SILINDI...",gecici->sefer_no);
		
		free(gecici);
	}
	
	else
	{
		struct sefer_bilgileri *gecici1, *gecici2;
		
		gecici1 = gecici; //silinen adresi bosaltmak icin.
		gecici2 = gecici1->onceki; //silinecek kaydin oncesini tutar.
		gecici1 = gecici1->sonraki; //silinecek kaydin sonrasini tutar.
		
		//gecici1'de silinecek kayittan sonraki, gecici2'de onceki var.
		
		gecici2->sonraki=gecici1; //tutulanlarý baglama bölümü.
		gecici1->onceki=gecici2;
		
		printf("\n%s NUMARALI SEFER SILINDI...",gecici->sefer_no);
		
		free(gecici); //koparýlan bað silindi.
	}
}

void kaptan_degis()
{
	int kapasite=5;
	ara();
	
	printf("\nYeni kaptanin adini girin: ");
	fflush(stdin); gets(gecici->kaptan);
	
	printf("\n-------------------------%s Numarali Sefer Guncellendi-------------------------\n",gecici->sefer_no);
	printf("\nSefer No: %s \nKalkis: %s \nInis: %s \nTarihi: %s \nSaati: %s \nKapasitesi: %d \nPlaka: %s \nKaptan: %s \nBilet Fiyati: %.2f\n\n",gecici->sefer_no
			,gecici->nereden,gecici->nereye,gecici->tarihi,gecici->saati,kapasite,gecici->plaka,gecici->kaptan,gecici->bilet_fiyati);
	
	
}

void gelir_hesapla()
{
	ara();
	
	printf("\n%s numarali seferden elde edilecek gelir: %.2f",gecici->sefer_no,gecici->bilet_fiyati*5);
}

void sefer_listele()
{
	int kapasite=5;
	if(ilk==NULL)
	{
		printf("\nMEVCUT SEFER BULUNAMADI !\n");
	}
	
	else
	{
		gecici=ilk;
	
		printf("\n-------------------------------MEVCUT SEFERLER-------------------------------\n");
	
		while(gecici!=NULL)
		{
			printf("Sefer No: %s \nKalkis: %s \nInis: %s \nTarihi: %s \nSaati: %s \nKapasitesi: %d \nPlaka: %s \nKaptan: %s \nBilet Fiyati: %.2f\n\n",gecici->sefer_no
			,gecici->nereden,gecici->nereye,gecici->tarihi,gecici->saati,kapasite,gecici->plaka,gecici->kaptan,gecici->bilet_fiyati);
		
			gecici=gecici->sonraki;
		}
	}
}

void sefer_sayisi()
{
	printf("\nToplam sefer sayisi: %s",son->sefer_no);
}

void sefer_sec()
{
	int kapasite=5;
	ara();
	
	if(gecici==NULL)
	{
		printf("Menuye donuluyor...");
	}
	else
	{
		printf("\n%s. sefer getiriliyor...\n",gecici->sefer_no);
		printf("Sefer No: %s \nKalkis: %s \nInis: %s \nTarihi: %s \nSaati: %s \nKapasitesi: %d \nPlaka: %s \nKaptan: %s \nBilet Fiyati: %.2f\n\n",gecici->sefer_no
			,gecici->nereden,gecici->nereye,gecici->tarihi,gecici->saati,kapasite,gecici->plaka,gecici->kaptan,gecici->bilet_fiyati);
			
		int koltuk_durumu[5],koltuk;
		char durum[]={"DOLU"};
		FILE *dosya1;
		
		temp=(koltuklar*) malloc(sizeof(koltuklar));
	
		printf("\nKoltuk Seciniz: [1] [2] [3] [4] [5] \n");
		printf("\nSecim:");
		scanf("%d",&koltuk);
		
		dosya1=fopen("kisibilgileri.txt","w");

		fprintf(dosya1,"[%d]",koltuk);
		fprintf(dosya1,"  %s",durum);
			
		printf("\nAdiniz: ");
		scanf("%s",&kisi.ad);
		fprintf(dosya1,"\n%s",kisi.ad);
			
		printf("Soyadiniz: ");
		scanf("%s",&kisi.soyad);
		fprintf(dosya1,"\n%s",kisi.soyad);
			
		printf("Cinsiyet: ");
		scanf("%s",&kisi.cinsiyet);
		fprintf(dosya1,"\n%s",kisi.cinsiyet);
			
		fclose(dosya1);	
		
		printf("\nBilgiler kaydedildi...\n");
	}	
}
