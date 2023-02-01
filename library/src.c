#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>


typedef struct Ogrenci{
    char ogrID[9];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
}Ogrenci;

typedef struct Yazar{
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar *next;
}Yazar;

typedef struct KitapOrnek{
    char etiketNo[20];
    char durum[9];
    struct KitapOrnek *next;
}KitapOrnek;

typedef struct Kitap{
    char kitapAdi[30];
    char ISBN[14];
    int adet;
    struct Kitap *next;
    struct KitapOrnek *head;
}Kitap;

typedef struct KitapYazar{
    char ISBN[14];
    int YazarID;
    struct KitapYazar *next;
}KitapYazar;

typedef struct Tarih{
    unsigned int gun:5;
    unsigned int ay:4;
    unsigned int yil:12;
}Tarih;

typedef struct KitapOdunc{
    char EtiketNo[20];
    char ogrID[9];
    unsigned int islemTipi:1;
    Tarih islemTarihi;
    struct KitapOdunc *next;
}KitapOdunc;

int getDifference(Tarih dt1, Tarih dt2);

Ogrenci *ogrenciEkle(Ogrenci *header);
Ogrenci * ogrenciOku(Ogrenci *header);
void ogrenciYazdir(Ogrenci *header);
Ogrenci * ogrenciSil(Ogrenci *header);
Ogrenci *ogrenciGuncelle(Ogrenci *header, KitapOdunc **islemler);
void ogrenciListele(Ogrenci *header);

void ogrenciGoruntule(Ogrenci *header, KitapOdunc *islemler);

int * ogrenciBul(Ogrenci *head, char input[40]);
Ogrenci *ogrenciSec(Ogrenci *header, char input[40]);
int kendisi();
int birOnceki();
void kitapOduncYazdir(KitapOdunc *header);
void yazarSil(Yazar **header, KitapYazar **h, char input[40]);
void yazarEkle(Yazar **header, char yazarAd[30], char yazarSoyad[30], int ID);
void yazarYazdir(Yazar *header);
void yazarOku(Yazar **header);
int * yazarBul(Yazar *head, char input[40]);
void yazarGuncelle(Yazar **header, char yazarAd[30], char yazarSoyad[30], char input[40]);
Yazar *yazarSec(Yazar *header, char input[40], int (*fptr)());
void yazarListele(Yazar *header);
void yazarGoruntule(Yazar *header, KitapYazar *iliski, Kitap *ktpHeader);

int kitapOrnekSil(KitapOrnek **header, int adet1, int adet2);
void kitapOrnekEkle(KitapOrnek **header, char kitapID[13], char durum[8]);
void kitapEkle(Kitap **header, char kitapAd[30], char kitapID[13], int adet, char durum[8]);
void kitapOku(Kitap **header);
void kitapYazdir(Kitap *header);
int *kitapBul(Kitap *header, char input[40]);
void kitapSil(Kitap **header, char input[40], int adet);
void kitapGoruntule(Kitap *header);
void timeKitapListele(Kitap *header, KitapOdunc *islemler, Ogrenci *ogrHead);
Kitap* kitapGuncelle(Kitap *header);
KitapYazar *kitapYazariGuncelle(Kitap *ktpHead, Yazar *yzrHead, KitapYazar *esler);

Kitap *kitapSec(Kitap *header, char input[40], int count);
KitapYazar * kitapYazarOku(KitapYazar *iliski);
KitapYazar *kitapYazarIliskisiEkle(KitapYazar *iliski, Yazar *yzrHead, Kitap *ktpHead);
KitapOdunc *siraliEkle(KitapOdunc *islemler, KitapOdunc *islem);
KitapOdunc *
islemEkle(KitapOdunc *islemler, char ogrID[9], char etiket[20], int islemTipi, Tarih tarih, Kitap **ktpHead);
KitapOdunc *kitapOduncTeslim(KitapOdunc *islemler, Ogrenci *header, Kitap **ktpHeader);
void kitapListele(Kitap *header);

void nonTeslimListele(Ogrenci *header, KitapOdunc *islemler);
void cezaliListele(Ogrenci *header);


void ogrenciMenusu(Ogrenci **ogrHead, KitapOdunc *islemler, Kitap **ktpHeader);
void kitapMenusu(Kitap **ktpHead, KitapOdunc *islemler, Ogrenci **ogrHead, KitapYazar *iliski, Yazar **yzrHead);
void yazarMenusu(Kitap **ktpHead, KitapOdunc *islemler, Ogrenci **ogrHead, KitapYazar **iliski, Yazar **yzrHead);
void kitapYazarYazdir(KitapYazar *header);

int * ogrenciBul(Ogrenci *head, char input[40]){
    Ogrenci *current = head;
    int *arr = calloc(10,sizeof(int));
    if(arr == NULL){
        perror("\n\t\t\t\t      Hafiza Yok");
        exit(EXIT_FAILURE);

    }
    char *v1 = strtok(input, " ");
    char *v2 = strtok(NULL, " ");

    int i  = 1, j = 0;
    while(current != NULL) {
        if(v2 == NULL){
            if (strstr(current->ogrID, v1) == NULL && strstr(current->ad, v1) == NULL &&
                strstr(current->soyad, v1) == NULL){
                current = current->next;
                i++;
            }
            else {
                arr[j] = i;
                current = current->next;
                i++;
                j++;
            }
        }
        else{
            if(strstr(current->ad, v1) == NULL && strstr(current->soyad, v2) == NULL){
                current = current->next;
                i++;
            }
            else {
                arr[j] = i;
                current = current->next;
                j++;
                i++;
            }
        }
    }
    if(j > 0)
        return arr;
    else
        return NULL;
}


void main_menu(Kitap **ktpHead, KitapOdunc **islemler, Ogrenci **ogrHead, KitapYazar **iliski, Yazar **yzrHead){
    int choice;
    do{
        printf("\n\n");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      ANA MENU: ");
        printf("\n\t\t\t\t     1. OGRENCI ISLEMLERI ");
        printf("\n\t\t\t\t     2. KITAP ISLEMLERI ");
        printf("\n\t\t\t\t     3. YAZAR ISLEMLERI ");
        printf("\n\t\t\t\t     4. CIKIS\n ");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      Seciminizi giriniz: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                ogrenciMenusu(ogrHead, *islemler, ktpHead);
                break;
            }
            case 2:{
                kitapMenusu(ktpHead, *islemler, ogrHead, *iliski, yzrHead);
                break;
            }
            case 3:{
                yazarMenusu(ktpHead, *islemler, ogrHead, iliski, yzrHead);
                break;
            }
            case 4:{
                exit(1);
            }
            default:{
                printf("\n\t\t\t\t      ...Invalid Option!...\n");
                printf("\n\t\t\t\t      Press any key to try again: ");
                getch();
            }
        }
    }while(choice!=4);
}

void ogrenciMenusu(Ogrenci **ogrHead, KitapOdunc *islemler, Kitap **ktpHeader) {
    int choice;

    do{
        printf("\n\n");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      OGRENCI ISLEMLERI: ");
        printf("\n\t\t\t\t     1. OGRENCI EKLE");
        printf("\n\t\t\t\t     2. OGRENCI SIL ");
        printf("\n\t\t\t\t     3. OGRENCI GUNCELLE ");
        printf("\n\t\t\t\t     4. OGRENCI BILGILERINI GORUNTULE ");
        printf("\n\t\t\t\t     5. KITAP TESLIM ETMEMIS OGRENCILERI LISTELE ");
        printf("\n\t\t\t\t     6. CEZALI OGRENCILERI LISTELE ");
        printf("\n\t\t\t\t     7. TUM OGRENCILERI LISTELE ");
        printf("\n\t\t\t\t     8. KITAP ODUNC AL VEYA TESLIM ET");
        printf("\n\t\t\t\t     9. ANA MENUYE DON");

        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      Secimini gir: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                (*ogrHead) = ogrenciEkle(*ogrHead);
                ogrenciYazdir(*ogrHead);
                break;
            }
            case 2:{
                (*ogrHead) = ogrenciSil(*ogrHead);
                break;
            }
            case 3:{
                (*ogrHead) = ogrenciGuncelle(*ogrHead, &islemler);
                break;
            }
            case 4:{
                ogrenciGoruntule(*ogrHead, islemler);
                break;

            }
            case 5:{
                nonTeslimListele(*ogrHead, islemler);
                break;
            }
            case 6:{
                cezaliListele(*ogrHead);
                break;
            }
            case 7:{
                ogrenciListele(*ogrHead);
                break;
            }
            case 8:{
                islemler = kitapOduncTeslim(islemler, *ogrHead, ktpHeader);
                break;
            }
            case 9:{
                break;
            }
            default:{
                printf("\n\t\t\t\t      ...Gecersiz giris!...\n");
                printf("\n\t\t\t\t      Tekrar denemek icin herhangi bir tusa basin: ");
                getch();
            }
        }
    }while(choice!=9);
}
void kitapMenusu(Kitap **ktpHead, KitapOdunc *islemler, Ogrenci **ogrHead, KitapYazar *iliski, Yazar **yzrHead){
    int choice;
    char ISBN[13];
    char kitapAd[30];
    int adet;
    do{
        printf("\n\n");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      KITAP ISLEMLERI: ");
        printf("\n\t\t\t\t     1. KITAP EKLE");
        printf("\n\t\t\t\t     2. KITAP SIL ");
        printf("\n\t\t\t\t     3. KITAP GUNCELLE ");
        printf("\n\t\t\t\t     4. KITAP BILGILERINI GORUNTULE ");
        printf("\n\t\t\t\t     5. RAFTAKI KITAP BILGILERINI GORUNTULE ");
        printf("\n\t\t\t\t     6. ZAMANINDA TESLIM EDILMEMIS KITAPLARI LISTELE ");
        printf("\n\t\t\t\t     7. KITAP YAZAR ESLESTIR");
        printf("\n\t\t\t\t     8. KITAP YAZARINI GUNCELLE ");
        printf("\n\t\t\t\t     9. ANA MENUYE DON");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      Secimini gir: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("\n\t\t\t\t      Sirasiyla kitabin adini, ISBN numarasini ve adetini giriniz: ");
                scanf("%s %s %d", kitapAd, ISBN, &adet);
                kitapEkle(ktpHead, kitapAd, ISBN, adet, "Rafta");
                kitapYazdir(*ktpHead);
                break;
            }
            case 2:{
                printf("\n\t\t\t\t      Silmek istediginiz kitabin adini veya ISBN numarasini giriniz: ");
                scanf("%s", kitapAd);
                printf("\n\t\t\t\t      Adetini giriniz: ");
                scanf("%d", &adet);
                kitapSil(ktpHead, kitapAd, adet);
                break;
            }
            case 3:{
                (*ktpHead) = kitapGuncelle(*ktpHead);
                break;
            }
            case 4:{
                kitapGoruntule(*ktpHead);
                break;
            }
            case 5:{
                kitapListele(*ktpHead);
                break;
            }
            case 6:{
                timeKitapListele(*ktpHead, islemler, *ogrHead);
                break;
            }
            case 7:{
                iliski = kitapYazarIliskisiEkle(iliski, *yzrHead, *ktpHead);
                kitapYazarYazdir(iliski);
                break;
            }
            case 8:{
                iliski = kitapYazariGuncelle( *ktpHead, *yzrHead, iliski);
                kitapYazarYazdir(iliski);
                break;
            }
            case 9:{
                break;
            }
            default:{
                printf("\n\t\t\t\t      ...Gecersiz giris!...\n");
                printf("\n\t\t\t\t      Tekrar denemek icin herhangi bir tusa basin: ");
                getch();
            }
        }
    }while(choice!=9);
}
void yazarMenusu(Kitap **ktpHead, KitapOdunc *islemler, Ogrenci **ogrHead, KitapYazar **iliski, Yazar **yzrHead){
    int choice;
    char input[40];
    char yazarAd[30];
    char yazarSoyad[30];
    do{
        printf("\n\n");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      OGRENCI ISLEMLERI: ");
        printf("\n\t\t\t\t     1. YAZAR EKLE");
        printf("\n\t\t\t\t     2. YAZAR SIL ");
        printf("\n\t\t\t\t     3. YAZAR GUNCELLE ");
        printf("\n\t\t\t\t     4. YAZAR BILGILERINI GORUNTULE ");
        printf("\n\t\t\t\t     5. ANA MENUYE DON");
        printf("\n\t\t\t*************************************************\n");
        printf("\n\t\t\t\t      Secimini gir: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("\n\t\t\t Sirasiyla yazarin adini ve soyadini giriniz: ");
                scanf("%s %s", yazarAd, yazarSoyad);
                Yazar *tmp = *yzrHead;
                while (tmp->next != NULL){
                    tmp = tmp->next;
                }
                yazarEkle(yzrHead, yazarAd, yazarSoyad, tmp->yazarID+1);
                yazarYazdir(*yzrHead);
                break;
            }
            case 2:{
                printf("\n\t\t\t Silmek istedi?iniz yazarin ad?n? soyadini giriniz: ");
                scanf("%s", input);
                yazarSil(yzrHead, iliski, input);
                kitapYazarYazdir(*iliski);
                break;
            }
            case 3:{
                printf("Guncellemek istedi?iniz yazarin ad?n? soyadini giriniz: ");
                scanf("%s", input);
                printf("Yazarin yeni adini ve soyadini giriniz: ");
                scanf("%s %s", yazarAd, yazarSoyad);
                yazarGuncelle(yzrHead, yazarAd, yazarSoyad, input);
                break;
            }
            case 4:{
                yazarGoruntule(*yzrHead, *iliski, *ktpHead);
                break;
            }
            case 5:{
                break;
            }
            default:{
                printf("\n\t\t\t ...Gecersiz giris!...\n");
                printf("\n\t\t\t Tekrar denemek icin herhangi bir tusa basin: ");
                getch();
            }
        }
    }while(choice!=5);
}


Ogrenci *ogrenciEkle(Ogrenci *header){

    Ogrenci *tmp = header;

    char ogrID[9];
    char ad[30];
    char soyad[30];

    printf("\n\t\t\t Eklemek istediginiz ogrencinin sirasiyle adini soyadini ve ID degerini giriniz: ");
    scanf("%s %s %s", ad, soyad, ogrID);
    if(ogrenciBul(header, ogrID) != NULL){
        printf("\n\t\t\t Bu ID degerine sahip bir ogrenci zaten kayitli.");
        return header;
    }
    Ogrenci *newOgrenci = (Ogrenci*)malloc(sizeof(Ogrenci));
    if (newOgrenci == NULL) {
        perror("\n\t\t\t Hafizada Yer Acilamadi");
        exit(EXIT_FAILURE);
    }
    strcpy(newOgrenci->ad,ad);
    strcpy(newOgrenci->soyad,soyad);
    strcpy(newOgrenci->ogrID,ogrID);
    newOgrenci->puan = 100;
    newOgrenci->next = NULL;

    if (header == NULL){
        header = newOgrenci;
    }
    else{
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = newOgrenci;
        newOgrenci->prev = tmp;
    }
    return header;
}

Ogrenci * ogrenciOku(Ogrenci *header){

    FILE *fp;
    fp = fopen("Ogrenciler.csv", "r+");

    if (!fp){
        perror("Can't open file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    char ogrID[8], ad[30], soyad[30];
    int puan;

    while (fgets(buffer,1024, fp)) {
        Ogrenci *newOgrenci = (Ogrenci *) malloc(sizeof(Ogrenci));
        char *value = strtok(buffer, ",");
        strcpy(newOgrenci->ogrID, value);
        value = strtok(NULL, ",");
        strcpy(newOgrenci->ad, value);
        value = strtok(NULL, ",");
        strcpy(newOgrenci->soyad, value);
        value = strtok(NULL, ",\n");
        int a = atoi(value);
        newOgrenci->puan = a;
        newOgrenci->next = NULL;
        if (header == NULL){
            header = newOgrenci;
        }
        else{
            Ogrenci *current = header;
            while (current->next != NULL)
                current = current->next;

            current->next = newOgrenci;
            newOgrenci->prev = current;
        }
    }
    fclose(fp);
    return header;
}

void ogrenciYazdir(Ogrenci *header){
    FILE *fp;
    fp = fopen("Ogrenciler.csv", "w");

    if (!fp){
        perror("\n\t\t\t Dosya Acilamadi");
        exit(EXIT_FAILURE);
    }

    while(header != NULL){
        fprintf(fp,"%s,%s,%s,%d\n", header->ogrID, header->ad, header->soyad, header->puan);
        header = header->next;
    }
    fclose(fp);
}
Ogrenci * ogrenciSil(Ogrenci *header) {
    int i = 0;
    int j = 0;
    if(header == NULL){
        printf("\n\t\t\t Sistemde hic ogrenci yok!");
        return header;
    }
    char input[40];
    printf("\n\t\t\t Silmek istediginiz ogrencinin adini soyadini veya ID degerini giriniz: ");
    scanf("%s", input);

    Ogrenci *temp;
    Ogrenci *current = header;
    current = ogrenciSec(header, input);
    if(header == current)
    {
        temp = header;    
        header = header->next;
        free(temp);
    }
    else
    {
        if(current == NULL)
        {
            printf("\n\t\t\t Ogrenci Bulunamadi!!");
            return header;
        } else {
            temp = current;
            if(current->next != NULL)
                current->next->prev = current->prev;
            if(current->prev != NULL){
                current->prev->next = current->next;
            }

            free(temp);
        }
    }
    ogrenciYazdir(header);
    return header;
}
void ogrenciGoruntule(Ogrenci *header, KitapOdunc *islemler) {
    char input[40];
    int i;
    int flag = 0;
    printf("\n\t\t\t Goruntulemek istediginiz ogrencinin adini, soyadini veya ID degerini giriniz: ");
    scanf("%s", input);
    Ogrenci *current = header;
    current = ogrenciSec(header, input);
    if(current == NULL){
        printf("\n\t\t\t Goruntulemek istediginiz ogrenci bulunamadi");
        return;
    }
    printf("\n\t\t\t %-20s", current->ad);
    printf("%-20s", current->soyad);
    printf("%-10s", current->ogrID);
    while (islemler != NULL){
        //printf("%s ", islemler[4].ogrID);
        if(strcmp(islemler->ogrID, current->ogrID) == 0){
            printf("\n\t\t\t %s,%s,%d,%d.%d.%d", islemler->EtiketNo, islemler->ogrID, islemler->islemTipi, islemler->islemTarihi.gun, islemler->islemTarihi.ay, islemler->islemTarihi.yil);
            flag = 1;
        }
        islemler = islemler->next;
    }
    if (flag != 1){
        printf("\n\t\t\t Ogrenci herhangi bir islem yapmamistir");
    }
}



Ogrenci *ogrenciSec(Ogrenci *header, char input[40]){
    Ogrenci *current = header;
    int i = 0, j = 1;
    int *arr  = ogrenciBul(header, input);
    if(arr != NULL && arr[1] != 0){
        while (arr[i] != 0){
            if(arr[i] == j){
                printf("\n%-5d", i+1);
                printf("%-20s", current->ad);
                printf("%-20s", current->soyad);
                printf("%-10s", current->ogrID);
                i++;
            }
            current = current->next;
            j++;
        }
        printf("\n\t\t\t Girdiginiz degere sahip birden fazla ogrenci bulundu. Lutfen degistirmek istediginiz ogrencinin satir numarasini giriniz: ");
        scanf("%d", &i);
    }
    else if(arr == NULL) {
        return NULL;
    }
    else
        i = 1;
    current = header;
    int count = 1;
    while (count < arr[i-1]) {
        current = current->next;
        count++;
    }
    return current;
}
Kitap *kitapSec(Kitap *header, char input[40], int count) {
    Kitap *current = header;
    int i = 0, j = 1;
    int *arr  = kitapBul(header, input);
    if(arr != NULL && arr[1] != 0){
        while (arr[i] != 0){
            if(arr[i] == j){
                printf("\n%-5d", i+1);
                printf("%-20s", current->kitapAdi);
                printf("%-20s", current->ISBN);
                i++;
            }
            current = current->next;
            j++;
        }
        printf("\n\t\t\t Girdiginiz degere sahip birden fazla kitap bulundu. Lutfen degistirmek istediginiz ogrencinin sat?r numaras?n? giriniz: ");
        scanf("%d", &i);
    }
    else if(arr == NULL) {
        return NULL;
    }
    else
        i = 1;
    current = header;
    while (count < arr[i-1]) {
        current = current->next;
        count++;
    }
    return current;
}

int * yazarBul(Yazar *head, char input[40]){
    Yazar *current = head;
    int *arr = calloc(10,sizeof(int));
    if(arr == NULL){
        perror("Hafiza Yok");
        exit(EXIT_FAILURE);

    }
    char *v1 = strtok(input, " ");
    char *v2 = strtok(NULL, " ");

    int i  = 1, j = 0;
    while(current != NULL) {
        if(v2 == NULL){
            if (strstr(current->yazarAd, v1) == NULL && strstr(current->yazarSoyad, v1) == NULL){
                current = current->next;
                i++;
            }
            else {
                arr[j] = i;
                current = current->next;
                i++;
                j++;
            }
        }
        else{
            if(strstr(current->yazarAd, v1) == NULL && strstr(current->yazarSoyad, v2) == NULL){
                current = current->next;
                i++;
            }
            else {
                arr[j] = i;
                current = current->next;
                j++;
                i++;
            }
        }
    }
    if(j > 0)
        return arr;
    else
        return NULL;
}
Yazar *yazarSec(Yazar *header, char input[40], int (*fptr)()) {
    Yazar *current = header;
    int i = 0, j = 1;
    int *arr  = yazarBul(header, input);
    if(arr != NULL && arr[1] != 0){
        while (arr[i] != 0){
            if(arr[i] == j){
                printf("\n%-5d", i);
                printf("%-20s", current->yazarAd);
                printf("%-20s", current->yazarSoyad);
                i++;
            }
            current = current->next;
            j++;
        }
        printf("\nGirdiginiz degere sahip birden fazla yazar bulundu. Lutfen istediginiz yazarin sat?r numaras?n? giriniz: ");
        scanf("%d", &i);
    }
    else if(arr == NULL) {
        return NULL;
    }
    else
        i = 1;
    current = header;
    int count = fptr();
    while (count < arr[i-1]) {
        current = current->next;
        count++;
    }
    return current;
}
int birOnceki(){
    return 2;
}
int kendisi(){
    return 1;
}

Ogrenci *ogrenciGuncelle(Ogrenci *header, KitapOdunc **islemler) {
    int i = 0;
    int j = 0;
    int cho;
    int flag = 0;
    char ogrID[9];
    char ad[30];
    char soyad[30];
    if(header == NULL){
        printf("\n\t\t\t Sistemde hic ogrenci yok!");
        return header;
    }
    char input[40];
    printf("\n\t\t\t Guncellemek istediginiz ogrencinin adini soyadini veya ID degerini giriniz: ");
    scanf("%s", input);
    Ogrenci *current = header;
    current = ogrenciSec(header, input);
    if(current == NULL){
        printf("\n\t\t\t Ogrenci bulunamadi!!");
        return header;
    }
    do{
        printf("\n\t\t\t Ogrencinin degistirmek istediginiz bilgisini seciniz: ");
        printf("\n\t\t\t 1. Ad ve Soyad");
        printf("\n\t\t\t 2. ID");
        printf("\n\t\t\t Secim: ");
        scanf("%d",&cho);
        switch (cho) {
            case 1:
                printf("\n\t\t\t Yeni ad ve soyad: ");
                scanf("%s %s", ad, soyad);
                strcpy(current->ad, ad);
                strcpy(current->soyad, soyad);

                flag = 1;
                break;
            case 2:
                printf("\n\t\t\t Yeni ID: ");
                scanf("%s", ogrID);
                if(ogrenciBul(header, ogrID) != NULL){
                    printf("\n\t\t\t Bu ID degerine sahip bir ogrenci zaten var. Tekrar denemek icin 0'a cikis icin 1' basiniz");
                    scanf("%d", &flag);
                    break;
                }
                KitapOdunc *tmp = *islemler;
                while (tmp != NULL){
                    if(strcmp(tmp->ogrID, current->ogrID) == 0){
                        strcpy(tmp->ogrID, ogrID);
                    }
                    tmp = tmp->next;
                }
                kitapOduncYazdir(*islemler);
                strcpy(current->ogrID, ogrID);
                flag = 1;
                break;
            default:{
                printf("\n\t\t\t ...Gecersiz Giris...\n");
                printf("\n\t\t\t Tekrar denemek için herhangi bir tusa basiniz: ");
                getch();
            }
        }

    } while (flag == 0);
    ogrenciYazdir(header);
    return header;
}
void nonTeslimListele(Ogrenci *header, KitapOdunc *islemler) {
    int i = 0, j = 0, flag;
    KitapOdunc *x = islemler;
    KitapOdunc *y;

    while (x != NULL){
        if(x->islemTipi == 0){
            flag = 0;
            y = x;
            while (flag == 0 && y != NULL){
                if(strcmp(x->ogrID, y->ogrID) == 0 && strcmp(x->EtiketNo, y->EtiketNo) == 0 && y->islemTipi == 1){
                    flag=1;
                }
                y = y->next;
            }
            Ogrenci *current;
            current = ogrenciSec(header, x->ogrID);
            if(flag == 0 && current != NULL){
                printf("\n\t\t\t %-20s", current->ad);
                printf("%-20s", current->soyad);
                printf("%-10s", current->ogrID);
            }
        }
        x = x->next;
    }
}
void cezaliListele(Ogrenci *header) {
    int i = 0, j = 0, flag;
    Ogrenci *current;
    current = header;
    while (current != NULL){
        if(current->puan < 100){
            printf("\n\t\t\t %-20s", header->ad);
            printf("%-20s", header->soyad);
            printf("%-10s", header->ogrID);
        }
        current = current->next;
    }
}


void ogrenciListele(Ogrenci *header){
    int i = 1;
    printf("\n\t\t\t %-5s%-20s%-20s%-10s","", "Ad", "Soyad", "ID");
    printf("\n\t\t\t %-5s%-20s%-20s%-10s","", "--------", "--------", "--------");


    while (header != NULL){
        printf("\n\t\t\t %-5d", i);
        printf("%-20s", header->ad);
        printf("%-20s", header->soyad);
        printf("%-10s", header->ogrID);
        header = header->next;
        i++;
    }
}

void yazarSil(Yazar **header, KitapYazar **h, char input[40]){
    if(header == NULL){
        perror("Sistemde hiç yazar yok!");
    }
    //temp is used to freeing the memory
    Yazar *temp;
    KitapYazar *x = *h;
    Yazar *current  = yazarSec(*header, input, kendisi);
    if(current == NULL){
        printf("\n\t\t\t Yazar Bulunamadi!!");
    }
    if(current == (*header))
    {
        temp = *header;    //backup to free the memory
        *header = (*header)->next;
        while (x != NULL){
            if(x->YazarID == temp->yazarID){
                x->YazarID = -1;
            }
            x = x->next;
        }
        free(temp);

    }
    else
    {
        current = yazarSec(*header, input, birOnceki);
        if(current == NULL)
        {
            printf("\n\t\t\t Yazar Bulunamadi!!");
            return;

        } else {
            temp = current->next;
            current->next = current->next->next;
            while (x != NULL){
                if(x->YazarID == temp->yazarID){
                    x->YazarID = -1;
                }
                x = x->next;
            }
            free(temp);
        }
    }
    yazarYazdir( *header);
}
void yazarEkle(Yazar **header, char yazarAd[30], char yazarSoyad[30], int ID){
    Yazar *newYazar;
    Yazar *tmp = *header;

    newYazar = (Yazar*)malloc(sizeof(Yazar));
    if (newYazar == NULL) {
        perror("\n\t\t\t Hafizada Yer Acilamadi");
        exit(EXIT_FAILURE);
    }

    strcpy(newYazar->yazarAd, yazarAd);
    strcpy(newYazar->yazarSoyad, yazarSoyad);
    newYazar->yazarID = ID;
    newYazar->next = NULL;

    if (*header == NULL){
        *header = newYazar;
    }
    else{
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newYazar;
    }

}

void yazarOku(Yazar **header){

    FILE *fp;
    fp = fopen("Yazarlar.csv", "r");
    if (!fp){
        perror("\n\t\t\t Hafizada yer acilamadi");
        exit(EXIT_FAILURE);
    }
    char buffer[1024], yazarAd[30], yazarSoyad[30];
    int yazarID;


    while (fgets(buffer,1024, fp)) {


        char *value = strtok(buffer, ",\n");
        int a = atoi(value);
        yazarID = a;
        value = strtok(NULL, ",\n");
        strcpy(yazarAd, value);
        value = strtok(NULL, ",\n");
        strcpy(yazarSoyad, value);
        yazarEkle(header, yazarAd, yazarSoyad, yazarID);
    }
    fclose(fp);
}
void yazarYazdir(Yazar *header){
    FILE *fp;
    fp = fopen("Yazarlar.csv", "w");

    if (!fp){
        perror("\n\t\t\t Dosya Acilamadi");
        exit(EXIT_FAILURE);
    }
    while(header != NULL){
        fprintf(fp,"%d,%s,%s\n", header->yazarID, header->yazarAd, header->yazarSoyad);
        header = header->next;
    }
    fclose(fp);
}

void yazarGuncelle(Yazar **header, char yazarAd[30], char yazarSoyad[30], char input[40]) {
    Yazar *tmp = yazarSec(*header, input, kendisi);
    if((*header) == tmp){
        strcpy(tmp->yazarAd, yazarAd);
        strcpy(tmp->yazarSoyad, yazarSoyad);
    }
    else {
        tmp = yazarSec(*header, input, birOnceki);

        if (tmp->next == NULL) {
            printf("\n\t\t\t Yazar bulunamadi!");
            return;
        } else {
            strcpy(tmp->next->yazarAd, yazarAd);
            strcpy(tmp->next->yazarSoyad, yazarSoyad);
        }
    }
    yazarYazdir(*header);
}

void yazarListele(Yazar *header){
    printf("\n\t\t\t %-20s%-20s%-5s", "Ad", "Soyad", "ID");
    printf("\n\t\t\t %-20s%-20s%-10s", "--------", "--------", "--------");
    while (header != NULL){
        printf("\n\t\t\t %-20s", header->yazarAd);
        printf("%-20s", header->yazarSoyad);
        printf("%-10d", header->yazarID);
        header = header->next;
    }
}
void yazarGoruntule(Yazar *header, KitapYazar *iliski, Kitap *ktpHeader) {
    char input[40];
    int i;
    int flag = 0;
    printf("\n\t\t\t Goruntulemek istediginiz yazarin adini soyadini giriniz: ");
    scanf("%s", input);
    Yazar *current = header;
    current = yazarSec(header, input, kendisi);
    if(current == NULL){
        printf("\n\t\t\t Goruntulemek istediginiz ogrencini bulunamadi");
        return;
    }
    printf("\n\t\t\t %-20s", current->yazarAd);
    printf("%-20s", current->yazarSoyad);
    while (iliski != NULL){
        if(iliski->YazarID == current->yazarID){
            Kitap *tmp = kitapSec(ktpHeader, iliski->ISBN, 1);
            printf("\n\t\t\t %s,%s,%d", tmp->kitapAdi, tmp->ISBN, tmp->adet);

            flag = 1;
        }
        iliski = iliski->next;
    }
    if (flag != 1){
        printf("\n\t\t\t Yazarin herhangi bir kitabi yoktur");
    }
}


void kitapOrnekEkle(KitapOrnek **header, char kitapID[13], char durum[8]){
    KitapOrnek *newOrnek;
    KitapOrnek *tmp = *header;

    int counter = 1;

    newOrnek = (KitapOrnek*) malloc(sizeof(KitapOrnek));
    if(newOrnek == NULL){
        perror("\n\t\t\t Hafizada Yer Acilamadi");
        exit(EXIT_FAILURE);
    }

    strcpy(newOrnek->durum, durum);
    newOrnek->next = NULL;

    if (*header == NULL){
        *header = newOrnek;
        sprintf(newOrnek->etiketNo, "%s_%d",kitapID, counter);
    }
    else{
        while (tmp->next != NULL) {
            tmp = tmp->next;
            counter++;
        }
        counter++;
        sprintf(newOrnek->etiketNo, "%s_%d",kitapID, counter);
        tmp->next = newOrnek;
    }
}

void kitapEkle(Kitap **header, char kitapAd[30], char kitapID[13], int adet, char durum[8]) {
    Kitap *newKitap;
    int i;

    newKitap = (Kitap *) malloc(sizeof(Kitap));
    if (newKitap == NULL) {
        perror("\n\t\t\t Hafizada Yer Acilamadi");
        exit(EXIT_FAILURE);
    }

    strcpy(newKitap->ISBN, kitapID);
    strcpy(newKitap->kitapAdi, kitapAd);
    newKitap->adet = adet;
    newKitap->next = NULL;
    newKitap->head = NULL;
    for (i= 0; i<adet; i++){
        kitapOrnekEkle(&(newKitap->head), kitapID, durum);
    }

    if (*header == NULL || strcmp((*header)->kitapAdi, kitapAd) > 0) {
        newKitap->next = *header;
        *header = newKitap;
    }
    else {
        Kitap *tmp = *header;
        while (tmp->next != NULL &&  strcmp(tmp->next->kitapAdi, kitapAd) < 0)
            tmp = tmp->next;
        if(tmp->next != NULL && strcmp(tmp->next->kitapAdi, kitapAd) == 0){
            while(tmp->next != NULL && strcmp(tmp->next->ISBN, kitapID) < 0)
                tmp = tmp->next;
        }
        newKitap->next = tmp->next;
        tmp->next = newKitap;
    }
}




void kitapOku(Kitap **header){
    FILE *fp;
    fp = fopen("Kitaplar.csv", "r");

    if (!fp){
        perror("\n\t\t\t Dosya okunamadi");
        exit(EXIT_FAILURE);
    }

    char buffer[1024], kitapAd[30], kitapID[14];
    int adet;


    while (fgets(buffer,1024, fp)) {

        char *value = strtok(buffer, ",");
        strcpy(kitapAd, value);
        value = strtok(NULL, ",");
        strcpy(kitapID, value);
        value = strtok(NULL, ",\n");
        int a = atoi(value);
        adet = a;
        kitapEkle(header, kitapAd, kitapID, adet , "Rafta");
    }
    fclose(fp);
}

void kitapYazdir(Kitap *header){
    FILE *fp;
    fp = fopen("Kitaplar.csv", "w+");

    if (!fp){
        perror("\n\t\t\t Dosya Acilamadi");
        exit(EXIT_FAILURE);
    }

    while(header != NULL){
        fprintf(fp,"%s,%s,%d\n", header->kitapAdi, header->ISBN, header->adet);
        header = header->next;
    }
    fclose(fp);
}

void kitapSil(Kitap **header, char input[40], int adet){

    if(header == NULL){
        printf("Sistemde hic yazar yok!");
        return;
    }
    Kitap *temp;

    Kitap *current;

    if(kitapBul(*header, input)[0] == 1)
    {
        current = kitapSec(*header, input, 1);
        if((*header)->adet == adet){
            temp = *header;
            *header = (*header)->next;
            free(temp);
        } else{
            (*header)->adet = kitapOrnekSil(&((*header)->head), (*header)->adet, adet);
        }

    }
    else
    {
        current = kitapSec(*header, input, 2);
        if(current->next == NULL)
        {
            printf("\n\t\t\t Kitap Bulunamadi!!");

        } else if(current->next->adet == adet) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else{
            current->next->adet = kitapOrnekSil(&(current->next->head), current->next->adet, adet);
        }
    }
    kitapYazdir(*header);
}
int kitapOrnekSil(KitapOrnek **header, int adet1, int adet2){
    int i;
    KitapOrnek *tmp;
    KitapOrnek *iter;
    if(adet2 < adet1){
        for(i = 0; i<adet2; i++){
            if(strcmp((*header)->durum, "Rafta") == 0){
                tmp = *header;
                *header = (*header)->next;
                free(tmp);
                adet1--;
            }else {
                iter = *header;
                while (strcmp(iter->next->durum, "Rafta") != 0 && iter->next != NULL)
                    iter = iter->next;
                if (iter->next != NULL) {
                    tmp = iter->next;
                    iter->next = iter->next->next;
                    free(tmp);
                    adet1--;
                } else if (i <= adet2 - 1) {
                    printf("\n\t\t\t Girdiginiz Adet Kadar Bosta Kitap Yok");
                    return adet1;
                }
            }
        }
        return adet1;
    }
    else{
        printf("\n\t\t\t Girdiginiz Adet Kadar Kitap Yok!!");
        return adet1;
    }
}

int *kitapBul(Kitap *header, char input[40]){
    Kitap *current = header;
    int *arr = calloc(10,sizeof(int));
    if(arr == NULL){
        perror("\n\t\t\t Hafiza Yok");
        exit(EXIT_FAILURE);

    }
    int i  = 1, j = 0;
    while(current != NULL) {
        if (strstr(current->kitapAdi, input) == NULL && strstr(current->ISBN, input) == NULL){
            current = current->next;
            i++;
        }
        else {
            arr[j] = i;
            current = current->next;
            i++;
            j++;
        }
    }
    if(j > 0)
        return arr;
    else
        return NULL;
}


KitapYazar * kitapYazarOku(KitapYazar *iliski) {

    FILE *fp;
    fp = fopen("KitapYazar.csv", "r+");

    char buffer[1024];

    while (fgets(buffer,1024, fp)){
        KitapYazar *newiliski = (KitapYazar*) malloc(sizeof(KitapYazar));
        if (newiliski == NULL) {
            perror("\n\t\t\t Hafizada Yer Acilamadi");
            exit(EXIT_FAILURE);
        }
        char *value = strtok(buffer, ",");
        strcpy((newiliski)->ISBN,value);
        value = strtok(NULL, ",\n");
        int a = atoi(value);
        (newiliski)->YazarID = a;
        (newiliski)->next = NULL;

        if (iliski == NULL) {
            iliski = newiliski;
        }
        else {
            KitapYazar *tmp = iliski;

            while (tmp->next != NULL)
                tmp = tmp->next;

            tmp->next = newiliski;
        }
    }
    return iliski;
    fclose(fp);
}
Kitap* kitapGuncelle(Kitap *header) {
    char ISBN[9];
    char kitapAd[30];
    if(header == NULL){
        printf("\n\t\t\t Sistemde hic ogrenci yok!");
        return header;
    }
    char input[40];
    printf("\n\t\t\t Guncellemek istediginiz kitabin adini veya ISBN degerini giriniz: ");
    scanf("%s", input);
    Kitap *current = header;
    current = kitapSec(header, input, 1);
    if(current == NULL){
        printf("\n\t\t\t Kitap Bulunamadi.");
        return header;
    }
    printf("\n\t\t\t Yeni ad: ");
    scanf("%s", kitapAd);
    strcpy(current->kitapAdi, kitapAd);
    kitapYazdir(header);
    return header;
}

void kitapGoruntule(Kitap *header){
    char input[40];
    int i;
    int flag = 0;
    printf("\n\t\t\t Goruntulemek istediginiz kitab?n ad?n? veya ISBN degerini giriniz: ");
    scanf("%s", input);
    Kitap *current = header;
    current = kitapSec(header, input, 1);
    if(current == NULL){
        printf("\n\t\t\t Goruntulemek istediginiz kitap bulunamadi");
        return;
    }
    printf("\n\t\t\t %-20s", current->kitapAdi);
    printf("%-20s", current->ISBN);
    KitapOrnek *x = current->head;
    while (x != NULL){
        printf("\n\t\t\t %s, %s", x->etiketNo, x->durum);
        x = x->next;
    }
}

void kitapListele(Kitap *header){
    while (header != NULL){
        printf("\n\t\t\t %-20s", header->kitapAdi);
        printf("\t\t\t %-5d", header->adet);
        printf("%-10s", header->ISBN);
        while (header->head != NULL){
            if(strcmp(header->head->durum, "Rafta") == 0) {
                printf("\n\t\t\t %-30s", header->head->etiketNo);
            }
            header->head = header->head->next;
        }
        header = header->next;
    }
}

void timeKitapListele(Kitap *header, KitapOdunc *islemler, Ogrenci *ogrHead){
    int i = 0, j = 0, flag;
    KitapOdunc *x = islemler;
    KitapOdunc *y;

    while (x != NULL){
        if(x->islemTipi == 0){
            flag = 0;
            y = x;
            while (y != NULL){
                if(strcmp(x->ogrID, y->ogrID) == 0 && strcmp(x->EtiketNo, y->EtiketNo) == 0 && y->islemTipi == 1 &&
                   getDifference(x->islemTarihi,y->islemTarihi) < 15){
                    Kitap *current = kitapSec(header, strtok(x->EtiketNo, "_"), 1);
                    while (current->head != NULL){
                        if(strcmp(current->head->etiketNo, x->EtiketNo) == 0) {
                            printf("\n\t\t\t %-30s", current->head->etiketNo);
                        }
                        current->head = current->head->next;
                    }
                }
                y = y->next;
            }
        }
        x = x->next;
    }
}


int countLeapYears(Tarih d)
{
    int years = d.yil;


    if (d.ay <= 2)
        years--;

    return years / 4
           - years / 100
           + years / 400;
}
int getDifference(Tarih dt1, Tarih dt2)
{
    int i= 0;
    const int monthDays[12]
            = { 31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31 };
    long int n1 = dt1.yil * 365 + dt1.gun;

    for (i = 0; i < dt1.ay - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);

    long int n2 = dt2.yil * 365 + dt2.gun;

    for (i = 0; i < dt2.ay - 1; i++)
        n2 += monthDays[i];

    n2 += countLeapYears(dt2);


    return (n2 - n1);
}
KitapOrnek *kitapOrnekBul(Kitap *header, char input[40]){
    Kitap *tmp = header;
    char no[2];
    char ISBN[13];
    char copy[40];
    strcpy(copy, input);
    char *value = strtok(input, "_");
    strcpy(ISBN, value);
    strcpy(input, copy);
    tmp = kitapSec(header, ISBN, 1);
    KitapOrnek *temp = tmp->head;
    if(temp == NULL){
        return NULL;
    }
    while (temp != NULL){
        if(strcmp(temp->etiketNo, copy) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
KitapOdunc *kitapOduncTeslim(KitapOdunc *islemler, Ogrenci *header, Kitap **ktpHeader) {
    char ogrID[9], ISBN[13], t[10];
    int islemTipi, gun, ay, yil;
    Tarih tarih;
    int run = 1;
    printf("\n\t\t\t Ogrencinin ad soyadini veya ID'sini giriniz: ");
    scanf("%s", ogrID);
    Ogrenci *current = ogrenciSec(header, ogrID);
    if(current == NULL){
        printf("\n\t\t\t Ogrenci bulunamadi");
        return islemler;
    }
    printf("\n\t\t\t Kitabin adini veya ISBN numarasini giriniz: ");
    scanf("%s", ISBN);
    Kitap *ktp = kitapSec(*ktpHeader, ISBN, 1);
    KitapOrnek *ktpOrnek = ktp->head;
    if(ktp == NULL){
        printf("\n\t\t\t Eklemek istediginiz kitap bulunamadi");
        return islemler;
    }
    printf("\n\t\t\t Islem tipi: ");
    scanf("%d", &islemTipi);
    printf("\n\t\t\t Tarih(gg.aa.yyyy): ");
    scanf("%d.%d.%d", &gun, &ay, &yil);
    tarih.gun = gun;
    tarih.ay = ay;
    tarih.yil = yil;
    KitapOdunc *tmp = islemler;
    if(islemTipi == 1){
        int i = 0, j = 0, flag = 0;
        while (flag == 0 && tmp != NULL){
            if(tmp->islemTipi == 0 && strcmp(tmp->ogrID, current->ogrID) == 0){
                if(getDifference(tmp->islemTarihi, tarih) > 15){
                    current->puan -= 10;
                }
                flag = 1;
                while (ktpOrnek != NULL && run == 1){
                    if(strcmp(ktpOrnek->durum, current->ogrID) == 0){
                        strcpy(ktpOrnek->durum,"Rafta");
                        run = 0;
                    } else
                        ktpOrnek = ktpOrnek->next;
                }
            }
            tmp = tmp->next;
        }
        if(flag == 0){
            printf("\n\t\t\t Odunc alinmamis kitap teslim edilemez.");
            return islemler;
        }
    }
    else{
        if(current->puan < 0){
            printf("\n\t\t\t Ogrencinin puani negatif oldugu icin kitap verilemiyor.");
            return islemler;
        }
        while (strcmp(ktpOrnek->durum, current->ogrID) != 0 && strcmp(ktpOrnek->durum, "Rafta") != 0 && ktpOrnek != NULL){
            ktpOrnek = ktpOrnek->next;
        }
        if(strcmp(ktpOrnek->durum, current->ogrID) == 0){
            printf("\n\t\t\t Bu ogrenci bu kitabi zaten odunc almis. Islem Basarisiz!");
            return islemler;
        }
        else if(ktpOrnek == NULL){
            printf("\n\t\t\t Bu kitab?n butun ornekleri odunc alinmis. Islem Basarisiz!");
            return islemler;
        }
        strcpy(ktpOrnek->durum,current->ogrID);
    }
    islemler = islemEkle(islemler, current->ogrID, ktpOrnek->etiketNo, islemTipi, tarih, ktpHeader);
    kitapOduncYazdir(islemler);
    return islemler;
}

void kitapOduncYazdir(KitapOdunc *header){
    FILE *fp;
    fp = fopen("KitapOdunc.csv", "w+");
    int i = 0;

    if (!fp){
        perror("\n\t\t\t Dosya Acilamadi");
        exit(EXIT_FAILURE);
    }

    while(header != NULL){
        fprintf(fp, "%s,%s,%d,%d.%d.%d\n", header->EtiketNo, header->ogrID, header->islemTipi, header->islemTarihi.gun, header->islemTarihi.ay, header->islemTarihi.yil);
        header = header->next;
    }
    fclose(fp);
}
void kitapYazarYazdir(KitapYazar *header){
    FILE *fp;
    fp = fopen("KitapYazar.csv", "w+");
    int i = 0;

    if (!fp){
        perror("\n\t\t\t Dosya Acilamadi");
        exit(EXIT_FAILURE);
    }

    while(header != NULL){
        fprintf(fp, "%s,%d\n", header->ISBN, header->YazarID);
        header = header->next;
    }
    fclose(fp);
}

KitapOdunc *islemEkle(KitapOdunc *islemler, char ogrID[9], char etiket[20], int islemTipi, Tarih tarih, Kitap **ktpHead) {

    KitapOdunc *yeniIslem = malloc(sizeof (KitapOdunc));
    strcpy(yeniIslem->EtiketNo,etiket);
    strcpy(yeniIslem->ogrID, ogrID);
    yeniIslem->islemTarihi = tarih;
    yeniIslem->islemTipi = islemTipi;
    yeniIslem->next = NULL;
    if(islemTipi == 0){
        KitapOrnek *tmp = kitapOrnekBul(*ktpHead, etiket);
        strcpy(tmp->durum, ogrID);
        printf("");
    }
    else{
        KitapOrnek *tmp = kitapOrnekBul(*ktpHead, etiket);
        strcpy(tmp->durum, "Rafta");
    }
    islemler = siraliEkle(islemler, yeniIslem);
    return islemler;
}
KitapOdunc *kitapOduncOku(KitapOdunc *islem, Kitap **ktpHead) {

    FILE *fp;
    fp = fopen("KitapOdunc.csv", "r+");

    char buffer[1024];

    int i = 0;
    char etiketNo[20];
    char ogrID[9];
    int islemTipi;
    Tarih islemTarihi;
    while (fgets(buffer,1024, fp)){
        char *value = strtok(buffer, ",");
        strcpy(etiketNo, value);
        value = strtok(NULL, ",");
        strcpy(ogrID, value);
        value = strtok(NULL, ",");
        islemTipi = atoi(value);
        value = strtok(NULL, ",");
        value = strtok(value, ".");
        int a = atoi(value);
        islemTarihi.gun = a;
        value = strtok(NULL, ".");
        a = atoi(value);
        islemTarihi.ay = a;
        value = strtok(NULL, ". \n");
        a = atoi(value);
        islemTarihi.yil = a;
        islem = islemEkle(islem, ogrID, etiketNo, islemTipi, islemTarihi, ktpHead);
    }
    fclose(fp);

    return islem;
}

KitapYazar *kitapYazarIliskisiEkle(KitapYazar *iliski, Yazar *yzrHead, Kitap *ktpHead){
    KitapYazar *yeniIliski = malloc(sizeof (KitapYazar));
    char input1[40];
    char input2[40];
    printf("\n\t\t\t Yazarin adini veya ID'sini giriniz");
    scanf("%s", input1);
    Yazar *current = yazarSec(yzrHead, input1, kendisi);
    if(current == NULL){
        return iliski;
    }
    printf("\n\t\t\t Kitabin adini veya ISBN degerini giriniz");
    scanf("%s", input2);
    Kitap *x = kitapSec(ktpHead, input2, 1);
    if(x == NULL){
        return iliski;
    }
    strcpy(yeniIliski->ISBN, x->ISBN);
    yeniIliski->YazarID = current->yazarID;
    if (iliski == NULL) {
        iliski = yeniIliski;
    }
    else {
        KitapYazar *tmp = iliski;

        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = yeniIliski;
    }
    kitapYazarYazdir(iliski);
    return iliski;
}

KitapYazar *kitapYazariGuncelle(Kitap *ktpHead, Yazar *yzrHead, KitapYazar *esler){
    char yzrAd[30];
    char input[40];
    printf("\n\t\t\t Kitap adini veya ISBN numarasini giriniz: ");
    scanf("%s", input);
    Kitap *tmp = kitapSec(ktpHead, input, 1);
    if(tmp == NULL){
        return esler;
    }
    KitapYazar *x = esler;

    printf("\n\t\t\t Kitabin yeni yazarinin adini giriniz: ");
    scanf("%s", yzrAd);
    Yazar *yemp = yazarSec(yzrHead, yzrAd, kendisi);
    if(yemp == NULL){
        return esler;
    }
    while (x != NULL){
        if(strcmp(x->ISBN,tmp->ISBN) == 0){
            x->YazarID = yemp->yazarID;
        }
        x = x->next;
    }
    return esler;
}

KitapOdunc *siraliEkle(KitapOdunc *islemler, KitapOdunc *islem)
{
    KitapOdunc *current = islemler;
    if (islemler == NULL) {
        islem->next = islemler;
        islemler = islem;
    }
    else {
        if(islem == islemler){

        }
        KitapOdunc *tmp = islemler;

        while (tmp->next != NULL && getDifference(tmp->next->islemTarihi, islem->islemTarihi) > 0)
            tmp = tmp->next;

        islem->next = tmp->next;
        tmp->next = islem;

    }
    return islemler;
}

int main(){

    setlocale(LC_ALL, "Turkish");  //türkçe karakter

    int sec;

    KitapYazar *iliski = NULL;
    KitapOdunc *islemler = NULL;

    islemler = NULL;


    FILE *fp;
    fp = fopen("KitapOdunc.csv", "r+");

    fclose(fp);

    Ogrenci *ogrHead = NULL;
    Yazar *yzrHead = NULL;
    Kitap *ktpHead = NULL;


    int n = 0;


    ogrHead = ogrenciOku(ogrHead);
    yazarOku(&yzrHead);
    kitapOku(&ktpHead);
    islemler = kitapOduncOku(islemler, &ktpHead);
    iliski = kitapYazarOku(iliski);
    main_menu(&ktpHead, &islemler, &ogrHead, &iliski, &yzrHead);
    return(0);

}

