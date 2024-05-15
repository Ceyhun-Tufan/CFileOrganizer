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
      printf("\033[0;31m Transferring error\033[0m \n");
   }
   else
   {
      printf("\033[0;33m%s named file > moved to %s \033[0m\n", sourcePath, destinationPath);
   }
}

void createFolders(const char *sourcePath)
{


   const char arr[6][30] = {"Music", "Programs", "Video", "Compressed", "Documents", "OtherFiles"};
   char checkerPath[256];
   int check;

   for (int i = 0; i < 6; i++)
   {
      snprintf(checkerPath, sizeof(checkerPath), "%s/%s", sourcePath, arr[i]);
      DIR *checker = opendir(checkerPath);
      if (checker)
      {
         closedir(checker);
      }
      else
      {
         check = mkdir(checkerPath);
         if (!check)
         {
            printf("%s created.\n", arr[i]);
         }
         else
         {
            printf("Error\n");
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
            if ((strstr(entry->d_name, ".txt") != NULL) || (strstr(entry->d_name, ".pdf") != NULL) || (strstr(entry->d_name, ".pptx") != NULL))
            { // dosya uzantısını kontrol eder
               snprintf(destinationPath, sizeof(destinationPath), "%s/Documents/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".exe") != NULL) || (strstr(entry->d_name, ".bat") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Programs/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".jpg") != NULL) || (strstr(entry->d_name, ".png") != NULL) || (strstr(entry->d_name, ".jpeg") != NULL) || (strstr(entry->d_name, ".mp4") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Video/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".zip") != NULL) || (strstr(entry->d_name, ".rar") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Compressed/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else if ((strstr(entry->d_name, ".mp3") != NULL) || (strstr(entry->d_name, ".wav") != NULL))
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/Music/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
            else
            {
               snprintf(destinationPath, sizeof(destinationPath), "%s/OtherFiles/%s", sourceDir, entry->d_name);
               moveFile(sourcePath, destinationPath);
            }
         }
      }
      closedir(dir);
   }
   else
   {
      printf("\033[0;31mThere was a problem while opening a folder!\033[0m \n");
   }
}

int main()
{
   const char *sourceDir = "C:/Users/Ceyhun/Downloads"; // TODO: find a way to fix this shit
   // signal(SIGINT,cleaner);
   printf("\033[0;36mOrganizer started!\033[0m \n");
   createFolders(sourceDir);
   FileOrganizer(sourceDir);
   printf("\033[0;36mDone!\033[0m \n");

   return 0;
}