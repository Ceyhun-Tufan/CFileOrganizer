# CFileOrganizer

Programın çalışmasını istediğiniz dizinin adresini, aşağıda belirttiğim sabite atayınız. 

```c
const char *sourceDir = "C:/Users/ASUS/Downloads";
```

Burada belirtildiği gibi organize edilecek dosyaları gideceği dizilerin önceden tanımlanması gerekir. Tanımlanan dizilerin de aşağıda belirtilen yerlere girilmesi gerekir.

```c
if (strstr(entry->d_name, ".txt") != NULL) { // dosya uzantısını kontrol eder
  snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/MetinBelgeleri/%s", entry->d_name);
  moveFile(sourcePath, destinationPath);
```

Özel olarak yazdığım basit bat dosyası ile terminalde
```
.\run.bat .\main.c Organizer
```
yazarak hızlıca compile ettikten sonra çalışmasını sağlayabilirsiniz.
