#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Çalışan bilgilerini tutan struct
typedef struct {
    char soyad[50]; // Çalışanın soyadı
    char ad[50];    // Çalışanın adı
    double satis;   // Çalışanın aylık satış değeri
    double spd;     // Çalışanın satış performans değeri
} personel;

// Fonksiyonlar
double enBuyukSatis(personel p[], int n); // En büyük satış değerini bulur
void alfabetikSiralaAd(personel p[], int n); // Çalışanları adına göre sıralar
void dosyayaYaz(personel p[], int n, const char *dosyaAdi); // Çalışan bilgilerini bir dosyaya yazar

int main() {
    FILE *dosya; // Dosya işaretçisi tanımlanır
    personel calisanlar[12]; // Maksimum 12 çalışan bilgisi tutacak dizi
    int i = 0, n = 0; // Sayaç değişkenleri ve çalışan sayısı
    double ENB; // En büyük satış değeri için değişken
    const char *dosyaYolu = "C:\\Users\\ataca\\OneDrive\\satis.txt"; // Giriş dosyasının yolu
    const char *prfrmsDosyaYolu = "C:\\Users\\ataca\\OneDrive\\prfrms.txt"; // Çıkış dosyasının yolu

    // satis.txt dosyasını aç
    dosya = fopen(dosyaYolu, "r");
    if (dosya == NULL) {
        printf("Hata: satis.txt dosyasi bulunamadi! Lutfen dosyayi manuel olarak olusturup calistirin.\n");
        return 1; // Program sonlandırılır
    }

    // satis.txt dosyasındaki veriyi oku
    while (fscanf(dosya, "%s %s %lf", calisanlar[i].soyad, calisanlar[i].ad, &calisanlar[i].satis) == 3) {
        i++; // Okunan çalışan sayısını artır
    }
    n = i; // Toplam çalışan sayısını kaydet
    fclose(dosya); // Dosyayı kapat

    // En büyük satış değerini bul
    ENB = enBuyukSatis(calisanlar, n);

    // Satış performans değerlerini hesapla
    for (i = 0; i < n; i++) {
        calisanlar[i].spd = ENB - calisanlar[i].satis; // Performans değerini hesapla
    }

    // Çalışanları adına göre alfabetik sırala
    alfabetikSiralaAd(calisanlar, n);

    // Sonuçları prfrms.txt dosyasına yaz
    dosyayaYaz(calisanlar, n, prfrmsDosyaYolu);

    // prfrms.txt dosyasını ekrana bastır
    dosya = fopen(prfrmsDosyaYolu, "r");
    if (dosya == NULL) {
        printf("Hata: prfrms.txt dosyasi acilamadi!\n");
        return 1; // Program sonlandırılır
    }

    printf("\nprfrms.txt dosyasinin icerigi:\n");
    char satir[100]; // Satır okuma a
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        printf("%s", satir); // Her bir satırı ekrana yazdır
    }
    fclose(dosya); // Dosyayı kapat

    printf("\nIslem tamamlandi. Sonuclar yukarida ekrana bastirildi ve prfrms.txt dosyasina yazildi.\n");
    return 0; // Program başarıyla sonlandı
}

// En büyük satış değerini bulan fonksiyon
double enBuyukSatis(personel p[], int n) {
    double max = p[0].satis;
    for (int i = 1; i < n; i++) {
        if (p[i].satis > max) {
            max = p[i].satis;
        }
    }
    return max;
}

// Adına göre alfabetik sıralama yapan fonksiyon (Bubble Sort kullanıldı)
void alfabetikSiralaAd(personel p[], int n) {
    personel temp; // Geçici değişken
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(p[j].ad, p[j + 1].ad) > 0) { // Alfabetik sırayı kontrol et (Adına göre)
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp; // Yer değiştir
            }
        }
    }
}

// Sonuçları dosyaya yazan fonksiyon
void dosyayaYaz(personel p[], int n, const char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "w");
    if (dosya == NULL) {
        printf("Dosya yazma hatasi!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(dosya, "%s %s %.2lf\n", p[i].ad, p[i].soyad, p[i].spd); // Önce ad, sonra soyad yazdır
    }
    fclose(dosya);
    printf("Sonuclar %s dosyasina yazildi.\n", dosyaAdi);
}
