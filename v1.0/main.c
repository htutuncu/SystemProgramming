#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    const char *filename = ".kilit";
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        perror(filename), exit(1);

    
    int bufferLength = 20;
    char buffer[bufferLength];
    char* file[20];
    int  i=0;
    for(i=0; i<20; i++)
        file[i] = (char*)malloc(20*sizeof(char));

    i=0;
    while (fgets(buffer, bufferLength, fp))
    {
        //printf("%s", buffer);
        strcpy(file[i++],buffer);
    }

    int j;
    for(j=0; j<i; j++)
        printf("%s",file[j]);
    
    fclose(fp);

    return 0;
}
