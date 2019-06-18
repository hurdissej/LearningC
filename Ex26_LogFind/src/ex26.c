#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "dbg.h"

char* concat(char *str1, char *str2)
{
    char *result = malloc(strlen(str1) + strlen(str2) +1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

void parseFile(FILE *file, char *fileName, int argCount, char *searchParams[], char method)
{
    int matchCount = 0;
    char line [ 128 ]; 
    while ( fgets ( line, sizeof line, file ) != NULL ) 
    {
        line[strlen(line) - 1] = '\0'; 
        for(int i = 0; i < argCount; i++)
        {
            if(!strcmp(searchParams[i], line))
            {
                matchCount++;
            }
        }
    }
    if(method == 'O' && matchCount > 0){
        printf("Match in file: %s\n", fileName);
    } else if(matchCount == argCount) {
        printf("Match in file: %s\n", fileName);
    } else {
        printf("No match\n");
    }
}

int parseFiles(char *searchParams[], char *directory, char method, int argCount)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("./logs");
    check(d, "Could not open directory");

    while ((dir = readdir(d)) != NULL)
    {
        char* fileName =  concat(directory, dir->d_name);
        FILE *file = fopen(fileName, "r+");
        if(file != NULL)
        {
           parseFile(file, fileName, argCount, searchParams, method);
        }
        fclose(file);  
        free(fileName);
    }
    
    closedir(d);
    return 1;
    error: return -1;
}

int main(int argc, char *argv[])
{
    char method = 'A';
    int argCount = 0;
    char *searchParams[argc];
    
    check(argc > 1, "Specify a search parameter");

    for (int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-o")){
            method = 'O';
            break;
        }
        argCount++;
    }

    for(int i = 0; i < argCount; i++)
    {
        searchParams[i] = argv[i+1];
    }
    
    return parseFiles(searchParams, "./logs/", method, argCount);

    error: printf("Usage - ./ex16 ...search params -o(optional) \n");
}