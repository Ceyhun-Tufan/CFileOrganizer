#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <locale.h>

void moveFile(const char *sourcePath, const char *destinationPath)
{
   if (rename(sourcePath, destinationPath) != 0)
   {
      printf("\033[0;31mDosya tasima hatasi\033[0m \n");
   }
   else
   {
      printf("\033[0;33m%s isimli dosya <  %s \033[0m noktasina tasindi \n", sourcePath, destinationPath);
   }
}

void createFolders(const char *sourcePath)
{

   const char arr[6][21] = {"MetinBelgeleri", "Exeler", "Resimler", "RarDosyalari", "PdfDosyalari", "FarkliDosyalar"};
   char checkerPath[256];
   int check;

   for (int i = 0; i < 6; i++)
   { // i<6 yazan kısmı arr 'ın boyutuna göre değiştirmelisin
      snprintf(checkerPath, sizeof(checkerPath), "%s/%s", sourcePath, arr[i]);
      DIR *checker = opendir(checkerPath);
      if (checker)
      {
         printf("%s acilip kapandi\n", arr[i]);
         closedir(checker);
      }
      else
      {
         check = mkdir(checkerPath);
         if (!check)
         {
            printf("%s olusturuldu.\n", arr[i]);
         }
         else
         {
            printf("Hata");
         }
      }
   }
}

void FileOrganizer(const char *sourceDir)
{
   DIR *dir;
   struct dirent *entry;
   if ((dir = opendir(sourceDir)) != NULL)
   {
      while ((entry = readdir(dir)) != NULL)
      {
         if (entry->d_type == DT_REG) // DT_REG herhangi bir dosya demektir
         {
            char sourcePath[256];
            char destinationPath[256];
            snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceDir, entry->d_name);
            // bu fonskiyon sourcePath'e sığabileceği kadar miktarda güvenli
            // şekilde istenilen karakterleri yükler
            if (strstr(entry->d_name, ".txt") != NULL)
            { // dosya uzantısını kontrol eder
               snprintf(destinationPath, sizeof(destinationPath), "%s/MetinBelgeleri/%s", sourceDir, entry->d_name);
               printf("%s", destinationPath);
               moveFile(sourcePath, destinationPath);
            }
            else if (strstr(entry->d_name, ".exe") != NULL )
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Exeler/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".jpg") != NULL) || (strstr(entry->d_name, ".png") != NULL) || (strstr(entry->d_name, ".jpeg") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Resimler/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".zip") != NULL) || (strstr(entry->d_name, ".rar") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/RarDosyalari/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if (strstr(entry->d_name, ".pdf") != NULL)
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/PdfDosyalari/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/FarkliDosyalar/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
         }
      }
      closedir(dir);
   }
   else
   {
      printf("\033[0;31mDosyayi acarken bir sorun yasandi!\033[0m \n");
   }
}

int main()
{
   const char *sourceDir = "C:/Users/ASUS/Downloads";
   // signal(SIGINT,cleaner);
   printf("\033[0;36mOrganizer started!\033[0m \n");
   createFolders(sourceDir);
   FileOrganizer(sourceDir);
   return 0;
}