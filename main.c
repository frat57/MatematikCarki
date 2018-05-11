#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/// n1 kodu

void cark();
void ozdegerbul(int n, float matris[][n], double ozdeger[]);
void schur(int n, float matris[][n], double ozdeger[]);
void ozvektorbul(int n, float matris[][n], double ozdeger[]);
void nilpotent(int n);

int main()
{
    ///Her seferinde rastgele sayi uretmesi icin
    srand(time(NULL));

    cark();

    return 0;
}

void cark()
{
    int rastgele, donus_sayisi;
    int i, j, n;
    char* islemler[] = {"Oz Deger Bul", "Shur Teoremi", "Oz Vektor Bul", "Nilpotent Matris"};

    printf("Cark kac defa donsun: ");
    scanf("%d", &donus_sayisi);

    for(i = 0; i<donus_sayisi; i++) {
        printf("Cark donuyor");
        rastgele = rand() % 242;
        printf("Rastgele sayiniz: %d\n", rastgele);
    }

    ///rastgele burada islem numarasina donusur
    rastgele = rastgele %4;
    printf("Secilen sayi:%d \n", rastgele);
    printf("Secilen islem:\"%s\" \n", islemler[rastgele]);

    printf("Matris boyutu icin bir n sayisi giriniz: ");
    scanf("%d", &n);

    float matris[n][n];
    double ozdeger[n];

    if(rastgele == 3)
    {
        nilpotent(n);
        return ;
    }

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("[%d][%d]: ", i, j);
            scanf("%f", &matris[i][j]);
        }
    }

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%2d ", (int)matris[i][j]);
        }
        printf("\n");
    }


    ///Fonksiyonlari kullanma
    ozdegerbul(n, matris, ozdeger);

    if(rastgele == 1) {
        schur(n, matris, ozdeger);
    }
    else if(rastgele == 2)
    {
        ozvektorbul(n, matris, ozdeger);
    }

}

void ozdegerbul(int n, float matris[][n], double ozdeger[])
{
    int i, j, k;

    if(n==1) {
        ozdeger[0] = matris[0][0];
    }

    if(n==2) {
//                        kok  b2                               - (4ac) (a=1)
        float kok_delta = sqrt((pow(matris[0][0]+matris[1][1],2)) - (4*(matris[0][0]*matris[1][1] - matris[0][1]*matris[1][0])));
     //   if (kok_delta < 0 ) printf("Uyari kokler irrasyonel sayilardir\n");
        ozdeger[0] = ((matris[0][0] +matris[1][1]) -kok_delta) / 2;
        ozdeger[1] = ((matris[0][0] +matris[1][1]) +kok_delta) / 2;
    }

    else if(n==3) {
        float a, b, matris_det;
		float trA=0, trX=0;
        int toplam = 0;

        float kare_matris[n][n];

        /// Matrisini Tr si
        ///Kosegenler toplamı
        trA = 0;
        for(i=0; i<n; i++) {
            trA += matris[i][i];
        }

        matris_det = ((matris[0][0] * matris[1][1] * matris[2][1]) + (matris[1][0] * matris[2][1] * matris[0][2]) + (matris[2][0] * matris[0][1] * matris[1][2]) - (matris[0][2] * matris[1][1] * matris[2][0]) - (matris[1][2] * matris[2][1] * matris[0][0]) - (matris[2][2] * matris[0][1] * matris[1][0]) );

        a = -1 * trA;

        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                toplam = 0;
                for (k=0; k<n; k++) {
                    toplam  += matris[i][k]*matris[k][j];
                }

            kare_matris[i][j] = toplam;
            }
        }

        trX = 0;
        for(i=0; i<n; i++) {
            trX += kare_matris[i][i];
        }

        b = ((trA * trA) - trX) / (float)2;

        double s, q, r, t, x1, x2, x3;

        q = (3 * b - ( a * a )) / 9;
        r = ((9 * a * b) - (27 * (-1 * matris_det)) - (2 * a * a * a)) / 54;
        s = pow(fabs(r + sqrt(fabs((pow(q,3)) + (pow(r,2))))), 0.33334);
        t = pow(fabs(r - sqrt(fabs((pow(q,3)) + (r * r)))),    0.33334);

        x1 = s + t - ( a / 3 );
        x2 = -1 * ( (s + t) / 2 ) - ( a / 3  ) + (float)0.8660 * (s - t);
        x3 = -1 * ( (s + t) / 2 ) - ( a / 3 ) - (float)0.8660 * (s - t);

        ozdeger[0] = x1;
        ozdeger[1] = x2;
        ozdeger[2] = x3;

    }


    for(i=0; i<n; i++)
    {
        printf("ozdeger %d: %f\n",i+1,  ozdeger[i]);
    }
    ///txt ye yazdir
    FILE* ozdegertxt;
    ozdegertxt = fopen("ozdeger.txt", "w");
    fputs("Matris: \n", ozdegertxt);
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
        {
            fprintf(ozdegertxt, "%2d ", (int)matris[i][j]);
        }
        fputs("\n", ozdegertxt);
    }
    //fputs("Delta: %d" + kok_delta, ozdegertxt);
    fputs("Ozdegerler: ", ozdegertxt);
    for(i=0; i<n; i++) {
        fprintf(ozdegertxt, "%f ", ozdeger[i]);
    }
    fclose(ozdegertxt);
}

void schur(int n, float matris[][n], double ozdeger[])
{
    int oz_toplam=0, kose_toplam=0, i, j;
    FILE* schurtxt;

    for(i=0; i<n; i++) {
        for(j=0;j<n;j++) {
            kose_toplam += pow(matris[i][i], 2);
        }
    }

    for(i=0; i<n; i++) {
        oz_toplam += pow(ozdeger[i], 2);
    }

    schurtxt = fopen("schur.txt", "w");
    printf("Ozdeger karelerinin toplami: %d\nKosegen kareleri toplami: %d\n", oz_toplam, kose_toplam);
    fprintf(schurtxt, "Ozdeger karelerinin toplamı: %d\nKosegen kareleri toplamı: %d\n", oz_toplam, kose_toplam);

    if(kose_toplam>oz_toplam) {
        printf("Kosegen karelerinin toplami daha fazladir");
        fputs("Kosegen karelerinin toplamı daha fazladır", schurtxt);
    }
    else if(kose_toplam<oz_toplam){
        printf("Ozdeger karelerinin toplami daha fazladir");
        fputs("Ozdeger karelerinin toplamı daha fazladır", schurtxt);
    }
    else {
        printf("Her iki toplam da esittir");
        fputs("Her iki toplam da esittir", schurtxt);
    }

    fclose(schurtxt);
}

void ozvektorbul(int n, float matris[][n], double ozdeger[])
{
    ///txt ye yazdır
}

void nilpotent(int n)
{

    int i,j,k, h;
    int var= 0, nilpotent_sayi = 1;
    int nil_matris[n][n], yeni_matris[n][n], sonuc[n][n];
    FILE* nilpotenttxt;

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            nil_matris[i][j] = rand()%31-15;
        }
    }

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            yeni_matris[i][j] = nil_matris[i][j];
        }
    }

    nilpotenttxt = fopen("nilpotent.txt", "w");


    ///Yazdir
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%7d ", nil_matris[i][j]);
            fprintf(nilpotenttxt, "%7d ", nil_matris[i][j]);
        }
        printf("\n");
        fprintf(nilpotenttxt, "\n");
    }
    printf("\n");
    fprintf(nilpotenttxt, "\n");

    for(h=0;h<n;h++) {
        ///kontrol et
        int sifir = 0;
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(sonuc[i][j]==0)
                    sifir++;
            }
        }

        if(sifir==n*n) {
            var = 1;
            break;
        }

        ///matrisi kendisiyle carp
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                int eleman = 0;
                for(k=0; k<n; k++) {
                    eleman += yeni_matris[i][k]*nil_matris[k][j];
                }
                sonuc[i][j] = eleman;
            }
        }

        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                yeni_matris[i][j] = sonuc[i][j];
            }
        }
        nilpotent_sayi++;
        printf("DENIYOR\n");

        ///Yazdir
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                printf("%7d ", sonuc[i][j]);
                fprintf(nilpotenttxt, "%7d ", sonuc[i][j]);
            }
            printf("\n");
            fprintf(nilpotenttxt, "\n");
        }
        printf("\n");
        fprintf(nilpotenttxt, "\n");
    }

    if(var==0) {
        printf("Nilpotent Yoktur");
        fputs("Nilpotent Yoktur", nilpotenttxt);
    }
    else {
        printf("Nilpotent Vardır\nDegeri: %d", nilpotent_sayi);
        fprintf(nilpotenttxt, "Nilpotent Vardır\nDegeri: %d", nilpotent_sayi);
    }

    fclose(nilpotenttxt);
}

/*void nilpotent(int n, float matris[][n], float ozdeger[])
{
    ///n3 kodu

    int i,j;

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            matris[i][j] = rand()%31-15;
            printf("%2d ", matris[i][j]);
        }
        printf("\n");
    }


    ozdegerbul(n, matris, ozdeger);

    int var=1;
    for(i=0;i<n;i++) {
        if(ozdeger[i] != 0)
            var=0;
    }

    FILE* nilpotenttxt;
    nilpotenttxt = fopen("nilpotent.txt", "w");

    if(var==0) {
        printf("Nilpotent Yoktur");
        fputs("Nilpotent Yoktur", nilpotenttxt);
    }
    else {
        printf("Nilpotent Vardır");
        fputs("Nilpotent Yoktur", nilpotenttxt);
    }

    fclose(nilpotenttxt);

}*/
