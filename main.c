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
	        printf("            TELEFON REHBER� v1.0\n");
	        printf("          ************************\n\n");
	        printf("��LEMLER\n");
	        printf("1.Kay�t Ekle\n2.Telefonlar� Listele\n3.Kayd� D�zenle\n4.Numara ile Kay�t Bul\n5.�sim ile Kay�t Bul\n6.Kay�t Sil\n0.��k��\n");

	        printf("Se�im:");
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
	                    printf("MEN�YE D�NMEK ���N B�R TU�A BASINIZ\n");
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
	                    printf("Uygulamadan ��k�l�yor\n");
	                    fclose(fp);
	                    exit(1);
	                default:
	                    printf("Hatal� se�im\n");
	                break;
	        	}
	    }
}

int KayitEkle()
{
        fseek(fp,0,SEEK_END);
        telefon.kayitnumarasi=kayitlimusterisayisi+1;
        printf("M��terinin ismini giriniz: ");
        scanf("%s",telefon.isim);
        printf("M��terinin numaras�n� giriniz: ");
        scanf("%ld",&telefon.numara);
        printf("M��terinin kodunu giriniz: ");
        scanf("%ld",&telefon.kod);
            if(fwrite(&telefon,sizeof(telefon),1,fp)==1)
            {
                printf("\nKAYIT BA�ARIYLA EKLENM��T�R.\n\n");
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
				printf("\nM��terinin Numaras�:  %ld\n",telefonlist.numara);
	            printf("M��terinin Ad�:  %s\n",telefonlist.isim);
	            printf("M��terinin Kodu:  %ld\n",telefonlist.kod);
			}
	    }
	    if(yazdi==0)
            printf("Kay�t bulunamad�.\n");

}

void KayitDuzenle()
{
    char musteriadi[100];
    char evet_hayir;
    int konumasistan=0;

 	rewind(fp);

        printf("D�zenlemek istedi�iniz m��terinin ismini giriniz: ");
        scanf("%s",musteriadi);
            while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
            {
            	konumasistan++;

            	if(strcmp(telefonlist.isim,musteriadi)==0)
            	{
            		bayrak++;
            		printf("M��terinin yeni ismini giriniz: ");
            		scanf("%s",telefonlist.isim);
            		printf("M��terinin yeni numaras�n� giriniz: ");
            		scanf("%ld",&telefonlist.numara);
            		printf("M��terinin yeni kodunu giriniz: ");
            		scanf("%ld",&telefonlist.kod);
            		fseek(fp,(konumasistan-1)*sizeof(telefonlist),SEEK_SET);

	            		if(fwrite(&telefonlist,sizeof(telefonlist),1,fp)==1)
	            		{
	            			printf("D�zenleme Ba�ar�l�..");
	            			break;
						}

	            		else
	            		{
	            			printf("D�zenleme Ba�ar�s�z..");
	            			break;
						}

				}
            }
			if(bayrak==0)
			{
				printf("M��teri bulunamad�. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    KayitDuzenle();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamen�ye y�nlendiriliyorsunuz.. ");
	                    AnaMenu();
	               	}
			}

}

void NumaraIleKayitBul()
{
	int musterinumarasi;
	char evet_hayir;
	fseek(fp,0,SEEK_SET);
		printf("Bilgilerini ��renmek istedi�iniz m��terinin numaras�n� giriniz: ");
		scanf("%ld",&musterinumarasi);
			while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
			{
				if(musterinumarasi==telefonlist.numara)
				{
					printf("M��teri bulundu bilgileri listeleniyor: \n\n");

						printf("\nM��terinin Numaras�:  %ld\n",telefonlist.numara);
			            printf("M��terinin Ad�:  %s\n",telefonlist.isim);
			            printf("M��terinin Kodu:  %ld\n",telefonlist.kod);
				}
			}
			if(bayrak==0)
			{
				printf("M��teri bulunamad�. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    NumaraIleKayitBul();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamen�ye y�nlendiriliyorsunuz.. ");
	                    AnaMenu();
	               	}
			}

}

void IsimIleKayitBul()
{
	rewind(fp);
	char evet_hayir,musteriara[100];
		printf("Bulmak istedi�iniz m��terinin ad�n� giriniz: ");
		scanf("%s",musteriara);
			while(fread(&telefonlist,sizeof(telefonlist),1,fp)==1)
		    {
		    	if(strcmp(musteriara,telefonlist.isim)==0)
		    	{
				        printf("\nM��terinin Numaras�:  %ld\n",telefonlist.numara);
				        printf("M��terinin Ad�:  %s\n",telefonlist.isim);
				        printf("M��terinin Kodu:  %ld\n",telefonlist.kod);
				        break;
				}
		    }
			if(bayrak==0)
			{
				printf("M��teri bulunamad�. Tekrar arama yapmak ister misiniz? (E/H)");
	            scanf(" %s",&evet_hayir);

	                if(evet_hayir=='E' || evet_hayir=='e')
	                    IsimIleKayitBul();
	                else if(evet_hayir=='H' || evet_hayir=='h')
	                {
	                    printf("Anamen�ye y�nlendiriliyorsunuz.. ");
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
		printf("Silmek istedi�iniz m��terinin kodunu giriniz: ");
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
						printf("Silme i�lemi ba�ar�l�.!\n");
						return(1);
						break;
					}
				}
			}
			if(bayrak==0)
			{
				printf("M��teri bulunamad�. Tekrar arama yapmak ister misiniz? (E/H)");
		        scanf("%s",&evet_hayir);

		            if(evet_hayir=='E' || evet_hayir=='e')
		                KayitSil();
		            else if(evet_hayir=='H' || evet_hayir=='h')
		            {
		                printf("Anamen�ye y�nlendiriliyorsunuz.. ");
		                AnaMenu();
		            }
			}
}
