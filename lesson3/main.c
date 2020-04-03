#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>

size_t deep = 0;
#ifdef CONSIDER
size_t count = 0;
#endif

void display_directory(char *path)
{
    
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
        printf("opendir failure for %s --> %s\n", path, strerror(errno));
        exit(1);
    }
    chdir(path);

    struct dirent *dirent;
    struct stat stat_info;

    while ((dirent = readdir(directory)) != NULL)
    {
        if (!strcmp(dirent->d_name, ".") || !strcmp(dirent->d_name, ".."))
            continue;
      
        if(stat(dirent->d_name, &stat_info))
        {
            printf("stat failure for %s --> %s\n", dirent->d_name, strerror(errno));
            continue;
        }
             
        if (S_ISREG(stat_info.st_mode))
        {
            for (size_t i = 0; i <= deep; i++)
            {
                printf("\t");
            }
            printf("File : %s \n", dirent->d_name);
#ifdef CONSIDER
++count;
#endif 
            continue;
        }

        if (S_ISDIR(stat_info.st_mode))
        {
            for (size_t i = 0; i < deep; i++)
            {
                printf("\t");
            }
            printf("Directory : %s\n", dirent->d_name);
            
            deep++;
            display_directory(dirent->d_name);
            --deep;
            chdir("..");
        }
    }

    closedir(directory);
}

int main(int argc, char *argv[])
{

    if(argc < 2) return 1;
    
    if(argv[2] != NULL && !strcmp(argv[2],"-c"))
            return 1;
    
    
    display_directory(argv[1]);

#ifdef CONSIDER
    printf("\n\nCount files: %lu\n", count);
#endif

    return EXIT_SUCCESS;
}