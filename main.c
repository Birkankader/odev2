#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
void AnaMenu();
int KayitEkle();
void KayitListele();
void KayitDuzenle();
void NumaraIleKayitBul();
void IsimIleKayitBul();
int KayitSil();

struct telephone{
 char isim[100];
 long int kayitnumarasi;
 long int kod;
 long int numara;
 }telefon,telefonlist;

FILE *fp;
int kayitlimusterisayisi=0,bayrak=0;
int i;

int main()
{
    fp=fopen("TelefonRehber.txt","wb+");
    setlocale(LC_ALL, "Turkish");
    AnaMenu();
  return 0;
}

void AnaMenu()
{
    char secim;
	    while ( 1 )
	    {
	        printf("            TELEFON REHBERÝ v1.0\n");
	        printf("          ************************\n\n");
	        printf("ÝÞLEMLER\n");
	        printf("1.Kayýt Ekle\n2.Telefonlarý Listele\n3.Kaydý Düzenle\n4.Numara ile Kayýt Bul\n5.Ýsim ile Kayýt Bul\n6.Kayýt Sil\n0.Çýkýþ\n");

	        printf("Seçim:");
	        scanf("%s",&secim);
	            switch(secim)
	            {
	                case '1':
	                   if(KayitEkle()==1)
	                    {
	                        kayitlimusterisayisi++;
	                    }
	                        break;
	                case '2':
	                    KayitListele();
	                    printf("MENÜYE DÖNMEK ÝÇÝN BÝR TUÞA BASINIZ\n");
	                    getch();
	                        break;
	                case '3':
	                    KayitDuzenle();
	                    break;
	                case '4':
	                	NumaraIleKayitBul();
	                    break;
	                case '5':
	                	IsimIleKayitBul();
	                    break;
	                case '6':
	                	if(KayitSil()==1)
	                	{
	                		kayitlimusterisayisi--;
						}
	                    break;
	                case '0':
	                    printf("Uygulamadan çýkýlýyor\n");
	                    fclose(fp);
	                    exit(1);
	                default:
	                    printf("Hatalý seçim\n");
	                break;
	        	}
	    }
}

int KayitEkle()
{
        fseek(fp,0,SEEK_END);
        telefon.kayitnumarasi=kayitlimusterisayisi+1;
        printf("Müþterinin ismini giriniz: ");
        scanf("%s",telefon.isim);
        printf("Müþterinin numarasýný giriniz: ");
        scanf("%ld",&telefon.numara);
        printf("Müþterinin kodunu giriniz: ");
        scanf("%ld",&telefon.kod);
            if(fwrite(&telefon,sizeof(telefon),1,fp)==1)
            {
                printf("\nKAYIT BAÞARIYLA EKLENMÝÞTÝR.\n\n");
                return(1);
            }
            else
            {
                printf("\nDOSYAYA YAZMA HATASI.!!\n");
                return(0);
            }
}

void KayitListele()
{
    int yazdi=0;
    fseek(fp,0,SEEK_SET);
	    while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
	    {
			if(telefonlist.kayitnumarasi!=0)
			{
			    yazdi++;
				printf("\nMüþterinin Numarasý:  %ld\n",telefonlist.numara);
	            printf("Müþterinin Adý:  %s\n",telefonlist.isim);
	            printf("Müþterinin Kodu:  %ld\n",telefonlist.kod);
			}
	    }
	    if(yazdi==0)
            printf("Kayýt bulunamadý.\n");

}

void KayitDuzenle()
{
    char musteriadi[100];
    char evet_hayir;
    int konumasistan=0;

 	rewind(fp);

        printf("Düzenlemek istediðiniz müþterinin ismini giriniz: ");
        scanf("%s",musteriadi);
            while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
            {
            	konumasistan++;

            	if(strcmp(telefonlist.isim,musteriadi)==0)
            	{
            		bayrak++;
            		printf("Müþterinin yeni ismini giriniz: ");
            		scanf("%s",telefonlist.isim);
            		printf("Müþterinin yeni numarasýný giriniz: ");
            		scanf("%ld",&telefonlist.numara);
            		printf("Müþterinin yeni kodunu giriniz: ");
            		scanf("%ld",&telefonlist.kod);
            		fseek(fp,(konumasistan-1)*sizeof(telefonlist),SEEK_SET);

	            		if(fwrite(&telefonlist,sizeof(telefonlist),1,fp)==1)
	            		{
	            			printf("Düzenleme Baþarýlý..");
	            			break;
						}

	            		else
	            		{
	            			printf("Düzenleme Baþarýsýz..");
	            			break;
						}

				}
            }
			if(bayrak==0)
			{
				printf("Müþteri bulunamadý. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    KayitDuzenle();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamenüye yönlendiriliyorsunuz.. ");
	                    AnaMenu();
	               	}
			}

}

void NumaraIleKayitBul()
{
	int musterinumarasi;
	char evet_hayir;
	fseek(fp,0,SEEK_SET);
		printf("Bilgilerini öðrenmek istediðiniz müþterinin numarasýný giriniz: ");
		scanf("%ld",&musterinumarasi);
			while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
			{
				if(musterinumarasi==telefonlist.numara)
				{
					printf("Müþteri bulundu bilgileri listeleniyor: \n\n");

						printf("\nMüþterinin Numarasý:  %ld\n",telefonlist.numara);
			            printf("Müþterinin Adý:  %s\n",telefonlist.isim);
			            printf("Müþterinin Kodu:  %ld\n",telefonlist.kod);
				}
			}
			if(bayrak==0)
			{
				printf("Müþteri bulunamadý. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    NumaraIleKayitBul();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamenüye yönlendiriliyorsunuz.. ");
	                    AnaMenu();
	               	}
			}

}

void IsimIleKayitBul()
{
	rewind(fp);
	char evet_hayir,musteriara[100];
		printf("Bulmak istediðiniz müþterinin adýný giriniz: ");
		scanf("%s",musteriara);
			while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
		    {
		    	if(strcmp(musteriara,telefonlist.isim)==0)
		    	{
				        printf("\nMüþterinin Numarasý:  %ld\n",telefonlist.numara);
				        printf("Müþterinin Adý:  %s\n",telefonlist.isim);
				        printf("Müþterinin Kodu:  %ld\n",telefonlist.kod);
				        break;
				}
		    }
			if(bayrak==0)
			{
				printf("Müþteri bulunamadý. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    IsimIleKayitBul();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamenüye yönlendiriliyorsunuz.. ");
	                    AnaMenu();
	               	}
			}
}

int KayitSil()
{
	rewind(fp);
	int konumasistan=0;
	long int musterikodu;
	char evet_hayir;
		printf("Silmek istediðiniz müþterinin kodunu giriniz: ");
		scanf("%ld",&musterikodu);

			while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
			{
				konumasistan++;
				if(musterikodu==telefonlist.kod)
				{
					bayrak++;
					telefonlist.kod=0;
					telefonlist.numara=0;
					telefonlist.kayitnumarasi=0;
					strcpy(telefonlist.isim," ");
					fseek(fp,(konumasistan-1)*sizeof(telefonlist),SEEK_SET);
					if(fwrite(&telefonlist,sizeof(telefonlist),1,fp)==1)
					{
						printf("Silme iþlemi baþarýlý.!\n");
						return(1);
						break;
					}
				}
			}
			if(bayrak==0)
			{
				printf("Müþteri bulunamadý. Tekrar arama yapmak ister misiniz? (E/H)");
		        scanf("%s",&evet_hayir);

		            if(evet_hayir=='E' || evet_hayir=='e')
		                KayitSil();
		            else if(evet_hayir=='H' || evet_hayir=='h')
		            {
		                printf("Anamenüye yönlendiriliyorsunuz.. ");
		                AnaMenu();
		            }
			}
}
