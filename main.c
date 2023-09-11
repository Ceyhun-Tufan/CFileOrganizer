#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <locale.h>


void moveFile(const char *sourcePath, const char *destinationPath) {
    if (rename(sourcePath, destinationPath) != 0) {
        printf("\033[0;31mDosya taşıma hatası\033[0m \n");
    } else {
        printf("\033[0;33m%s named file transferred to :  %s \033[0m \n", sourcePath, destinationPath);
    }
}


void createFolders(const char *sourcePath){
   
   const char arr[4][21] = {"MetinBelgeleri","Exeler","Resimler","RarDosyalari"};
   char checkerPath[256];
   int check;

   for(int i = 0;i<4;i++){
      snprintf(checkerPath, sizeof(checkerPath), "%s/%s", sourcePath,arr[i]);
      DIR *checker = opendir(checkerPath);
      if(checker){
         printf("%s acilip kapandi\n",arr[i]);
         closedir(checker);
      }else{
         check = mkdir(checkerPath);
         if(!check){
            printf("%s created.\n",arr[i]);
         }else{
            printf("Error");
         }
      }
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
                     snprintf(destinationPath, sizeof(destinationPath), "%s/MetinBelgeleri/%s", sourceDir,entry->d_name);
                     printf("%s",destinationPath);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".exe") != NULL){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/Exeler/%s", sourceDir,entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".jpg") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/Resimler/%s",sourceDir, entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".png") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/Resimler/%s",sourceDir, entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".jpeg") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/Resimler/%s",sourceDir, entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".zip") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/RarDosyalari/%s",sourceDir, entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }else if(strstr(entry->d_name, ".rar") != NULL ){
                     snprintf(destinationPath, sizeof(destinationPath), "%s/RarDosyalari/%s",sourceDir, entry->d_name);
                     moveFile(sourcePath, destinationPath);
            }
         }
      }
      closedir(dir);
      printf("File closed.");
   }else{
      printf("\033[0;31mThere is an error while opening the directory!\033[0m \n");
   }
   
}

int main() {
   struct FolderNames
      {
         char metin[21];
         char exe[13];
         char resim[15];
         char rar[19];
      }foldernames;

   const char *sourceDir = "C:/Users/ASUS/Downloads";
   //signal(SIGINT,cleaner);
   printf("\033[0;36mOrganizer started!\033[0m \n");
   createFolders(sourceDir);
   FileOrganizer(sourceDir);
   return 0;
}