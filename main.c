#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>
#include <locale.h>

void moveFile(const char *sourcePath, const char *destinationPath) {
    if (rename(sourcePath, destinationPath) != 0) {
        printf("\033[0;31mDosya taşıma hatası\033[0m \n");
    } else {
        printf("\033[0;33m%s named file transferred to :  %s \033[0m \n", sourcePath, destinationPath);
    }
}

void FileOrganizer(const char *sourceDir){
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
            if (strstr(entry->d_name, ".txt") != NULL) { // dosya uzantısını kontrol eder
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/MetinBelgeleri/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".exe") != NULL){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/Exeler/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".jpg") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/Resimler/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".png") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/Resimler/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".jpeg") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/Resimler/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".zip") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/RarDosyalari/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".rar") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "C:/Users/ASUS/Downloads/RarDosyalari/%s", entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }
         }
      }
      closedir(dir);
   }else{
      printf("\033[0;31mThere is an error while opening the directory!\033[0m \n");
   }
   
}

int main() {
   const char *sourceDir = "C:/Users/ASUS/Downloads";
   //signal(SIGINT,cleaner);
   printf("\033[0;36mOrganizer started!\033[0m \n");
   FileOrganizer(sourceDir);
   return 0;
}