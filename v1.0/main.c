#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000

char *removeLeadingSpaces(char *str)
{
    static char str1[1000];
    int count = 0, j, k;

    // Iterate String until last
    // leading space character
    while (str[count] == ' ')
    {
        count++;
    }

    // Putting string into another
    // string variable after
    // removing leading white spaces
    for (j = count, k = 0;
         str[j] != '\0'; j++, k++)
    {
        str1[k] = str[j];
    }
    str1[k] = '\0';

    return str1;
}

void removeChar(char *s, char c)
{

    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

int main()
{

    const char *filename = ".kilit";
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        perror(filename), exit(1);

    int bufferLength = MAX_SIZE;
    char buffer[bufferLength];
    char *file[MAX_SIZE];
    int i = 0;
    for (i = 0; i < MAX_SIZE; i++)
        file[i] = (char *)malloc(MAX_SIZE * sizeof(char));

    i = 0;
    while (fgets(buffer, bufferLength, fp))
    {
        strcpy(file[i++], buffer);
    }

    int j;
    for (j = 1; j < i - 1; j++)
    {
        file[j] = removeLeadingSpaces(file[j]);
        removeChar(file[j], ',');

        char *token = strtok(file[j], ":");

        // Keep printing tokens while one of the
        // delimiters present in str[].

        char *key = strdup(token);
        
        
        token = strtok(NULL, ":");

        char *value = strdup(token);
        //printf("%s\n", token);
        token = strtok(NULL, ":");

        value = removeLeadingSpaces(value);

        printf("%s\n", key);
        printf("%s\n",value);
    }

    fclose(fp);

    return 0;
}
