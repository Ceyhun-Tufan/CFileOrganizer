# CFileOrganizer

Program, belirtilen dizinde resimler, metin belgeleri, exeler ve rar dosyaları için ayrı ayrı yeni yeni dizin oluşturur ve dosyaları gerekli yerlerine taşır.

![image](https://github.com/Ceyhun-Tufan/CFileOrganizer/assets/69029757/9bb8a517-a9e5-4658-a4fb-519594e3357e)

Programın çalışmasını istediğiniz dizinin adresini, aşağıda belirttiğim sabite atayınız. 


```c
const char *sourceDir = "C:/Users/ASUS/Downloads";
```

Özel olarak yazdığım basit bat dosyası ile terminalde
```
.\run.bat .\main.c Organizer
```
yazarak hızlıca compile ettikten sonra çalışmasını sağlayabilirsiniz.

~~Burada belirtildiği gibi organize edilecek dosyaları gideceği dizilerin önceden tanımlanması gerekir. Tanımlanan dizilerin de aşağıda belirtilen yerlere girilmesi gerekir.~~

```c
if (strstr(entry->d_name, ".txt") != NULL) { // dosya uzantısını kontrol eder
  snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/MetinBelgeleri/%s", entry->d_name);
  moveFile(sourcePath, destinationPath);
```

