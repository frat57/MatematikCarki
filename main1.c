#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ogrenciler
{
	int numara;
	char ad[20];
	char soyad[20];
	//short yerine int gelebiliir
	short kayitSirasi;
	char* ogretim;
	struct ogrenciler* next;
};

typedef struct ogrenciler ogrenciler;

void dosyaYazdir(ogrenciler* root, const char* p)
{
	ogrenciler* ileri = root;
	FILE* kayit;

	kayit = fopen(p, "w");
	while(ileri->next != NULL) {
		fprintf(kayit, "%d\t%s\t%s\t%d\t%s\n", (ileri->next->numara), &(ileri->next->ad), &(ileri->next->soyad), (ileri->next->kayitSirasi), &(ileri->next->ogretim));
		ileri = ileri->next;
	}
	fclose(kayit);

}

ogrenciler* olustur()
{
	char ch;//char ch
	char numara[10] ;
	FILE* ogrenci_kayit;
	ogrenci_kayit = fopen("ogrenci_kayit.txt", "r");

	ogrenciler* root = (ogrenciler*) malloc(sizeof(ogrenciler));
	root->next = NULL;
	ogrenciler* ileri = root;

	//ilk satiri gec
	for(ch = fgetc(ogrenci_kayit); ch!='\n'; ch = fgetc(ogrenci_kayit));

	//Dosyanin sonuna gelinceye kadar dondur
	while(!feof(ogrenci_kayit)) {

		while(ileri->next != NULL) {
			ileri = ileri->next;
		}

		ileri->next =  malloc(sizeof(ogrenciler));

		//ogrenci numaralrını alma
		fscanf(ogrenci_kayit, "%s", &(numara));
		char tire[2]= "-";
		if(strstr(numara, tire)) {
			ileri->next->numara = -1;
		}
		else {
			ileri->next->numara = atoi(&numara);
		}
		//diger bilgileri alma
		fscanf(ogrenci_kayit, "%d", &(ileri->next->numara));
		fscanf(ogrenci_kayit, "%s %s", &(ileri->next->ad),  &(ileri->next->soyad));
		fscanf(ogrenci_kayit, "%d", &(ileri->next->kayitSirasi));
		fscanf(ogrenci_kayit, "%s", &(ileri->next->ogretim));

		//bilgileri konsola yazdir
		/*printf("Ad: %s\n", &(ileri->next->ad));
		printf("Soyad: %s\n", &(ileri->next->soyad));
		printf("Numara: %d\n", (ileri->next->numara));
		printf("Kayit Sirasi: %d\n", (ileri->next->kayitSirasi));
		printf("Ogretim: %s\n", &(ileri->next->ogretim));
		printf("\n");*/

		ileri->next->next = NULL;
	}

	fclose(ogrenci_kayit);

	return root;
}

void kayitKontrol(ogrenciler* root)
{

	ogrenciler* ileri = root->next;
	ogrenciler* ileriN = ileri->next;
//Hata
//Hata son ogrencinin adini karşılaştırmıyor
	printf("Ismi silinen ogrencilerin listesi: \n");
	while(ileri->next != NULL){

		while(ileriN->next != NULL) {
			if(strcmp(ileri->ad, ileriN->ad) != 0)
				break;
			if(strcmp(ileri->soyad, ileriN->soyad) == 0) {
				printf("%s %s\n", &(ileri->ad), &(ileri->soyad));
				ileri->next = ileriN->next;
				/*free(ileriN);
				ileriN = ileri->next;*/
			}
			ileriN = ileriN->next;
		}
		ileri= ileri->next;
		ileriN = ileri->next;
	}

	dosyaYazdir(root, "kayitKontrol.txt");

}

void numaraAtama(ogrenciler* root)
{
	int i, numara;
	int yil = 	1700000;
	int ogretim;
	short var;
	ogrenciler* ileri = root;
	ogrenciler* gecis;

	while(ileri->next !=NULL) {
		ileri = ileri->next;
		//ogrencinin numarasi yoksa bu if e gir
		if(ileri->numara == -1) {
				//ogretim 1 e ayarlı
				ogretim = 1000;
				if(strstr( &(ileri->ogretim), "II"))
					ogretim = 2000;
				//001 den başlayacak
				for(i=1; i<=999;i++) {
					numara = yil+ ogretim +i;
					gecis= root;
					var = 0;
					//diger sayilarla cakisiyor mu diye bak
					while(gecis->next != NULL) {
						gecis = gecis->next;
						if(gecis->numara == numara) {
							var=1;
							break;
						}
					}
					//eger cakısma yoksa numarayı esitle
					if(var== 0) {
						ileri->numara = numara;
						break;
					}
				}
		}
	}

	dosyaYazdir(root, "numaraAtama.txt");
}

void numaraSiralama(ogrenciler* root)
{
	ogrenciler* ileri = root;
	ogrenciler* gecis;

	while(ileri->next !=NULL) {
		ileri = ileri->next;

		gecis=ileri->next;

	}

	dosyaYazdir(root, "numaraSiralama.txt");
}

void esitDagilim(ogrenciler* root)
{

	dosyaYazdir(root, "esitDagilim.txt");
}

void enAzDagilim(ogrenciler* root)
{

	dosyaYazdir(root, "enAzDagilim.txt");
}

void ogrenciEkle(ogrenciler* root, char* ad, char* soyad, char* ogretim, int kayitNo, int numara)
{
	ogrenciler* son = root;
	//Sona git
	while(son->next != NULL) {
		son = son->next;
	}

	son->next = (ogrenciler*) malloc(sizeof(ogrenciler));
	son = son->next;

	strcpy(son->ad, ad);
	strcpy(son->soyad, soyad);
	//son->ogretim i boyle yazmazsak program hata veriyor
	//ogretim dizi değil pointer oldugu icin boyle olabilir
	strcpy(&(son->ogretim), ogretim);
	son->kayitSirasi = kayitNo;
	son->numara = numara;

	son->next = NULL;

	dosyaYazdir(root, "ogrenciEkle.txt");

}

int main(){
	char ad[20];
	char soyad[15];
	int ogretim;
	char ogrt[3];
	int kayitNo;
	int numara;
	//ogrenci listesni baglı listeye atma
	ogrenciler* root = olustur();

	//sirayla diger fonksiyonlar
	//kayitKontrol(root);
	//numaraAtama(root);
	//numaraSırala(root);
	//esitDagilim(root);
	//enAzDagilim(root);
	printf("Adi: ");
	scanf("%s", ad);
	printf("Soyadi: ");
	scanf("%s", soyad);
	printf("Ogretimi(1,2):  ");
	scanf("%s", &ogretim);
	if(ogretim == 1) {
		strcpy(ogrt, "I");
	}
	else{
		strcpy(ogrt, "II");
	}

	printf("Kayit no: ");
	scanf("%d", &kayitNo);
	printf("Numara: ");
	scanf("%d", &numara);

	ogrenciEkle(root, ad, soyad, ogrt, kayitNo, numara);

	printf("En guncel dosyanin adi \"final.txt\" dedir.\n");
	dosyaYazdir(root, "final.txt");

    return 0;
}


/// timer eksik

///uygulama zamani calisma süresi gösterilmeli

///     Olasi Fonksiyonlar(Siralamayla)
/// kayit kontrol
/// numara ataması
/// numaraya gore sirala
/// yeni listenin txt ye yazdır
/// sinif sayisi ve kapasitesini main icinde sorma

/// esit dagilim fonk
    /// text e yaz
/// en az sinif dagilimi fonk
    /// text e yaz
