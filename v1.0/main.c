#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jval.h"
#include "jrb.h"
#include "dllist.h"
#include "fields.h"

#define MAX_SIZE 1000

char *removeLeadingSpaces(char *str);

void removeChar(char *s, char c);

int compareJval(Jval j1, Jval j2);

int main(int argc, char** argv)
{

    if(argc != 4){  /* Checking if program called properly */
        fprintf(stderr, "Incorrect parameter count\n");
        exit(EXIT_FAILURE);
    } 

    JRB jrb = make_jrb();

    const char *filename = ".kilit";
    FILE *fp = fopen(filename, "rb");
    //FILE * input = fopen(argv[2], "r"); 

    IS is;      /* Fields struct for reading input */
    is = new_inputstruct(argv[2]);
    if (is == NULL) {
        perror(argv[2]);
        exit(1);
    }

    FILE * output = fopen(argv[3], "w+");

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
        strcpy(file[i++], buffer);
    

    int j;
    
    for (j = 1; j < i - 1; j++)
    {
        file[j] = removeLeadingSpaces(file[j]);
        removeChar(file[j], ',');

        char *token = strtok(file[j], ":");

        /* Keep printing tokens while one of the
           delimiters present in str[]. */

        char *key = strdup(token);
        int k;
        char *newKey = (char*)malloc(strlen(key)*sizeof(char));
        for(k=0; k<strlen(key)-2; k++){
            newKey[k] = key[k+1];
        }
        
        
        
        token = strtok(NULL, ":");

        char *value = strdup(token);
        value = removeLeadingSpaces(value);
        char *newValue = (char*)malloc(strlen(value)*sizeof(char));
        for(k=0; k<strlen(value)-3; k++){
            newValue[k] = value[k+1];
        }
        
        token = strtok(NULL, ":");

        
    

        Jval myJval = (Jval)malloc(sizeof(Jval));
        myJval = new_jval_v(strdup(newValue));

        Jval myJval2 = (Jval)malloc(sizeof(Jval));
        myJval2 = new_jval_s(strdup(newKey));

        if(strcmp(argv[1], "-e")==0){
            (void) jrb_insert_gen(jrb, myJval2, myJval, compareJval);
        }

        else if(strcmp(argv[1], "-d")== 0){

            (void) jrb_insert_gen(jrb, myJval, myJval2, compareJval);
        }

        else{
            fprintf(stderr, "Wrong parameter/n");
            exit(EXIT_FAILURE);
        }

        free(newKey);
        free(newValue);
    }
    

    if(strcmp(argv[1], "-e")==0){
        while(get_line(is) >= 0) {
            for (i = 0; i < is->NF; i++) {
                //printf("%s\n",is->fields[i]);
                fprintf(output,"%s ",jrb_find_str(jrb, is->fields[i])->val);
            }
        }
    }else{
        while(get_line(is) >= 0) {
            for (i = 0; i < is->NF; i++) {
                //printf("%s\n",is->fields[i]);
                fprintf(output,"%s ",jrb_find_str(jrb, is->fields[i])->val);
                
            }
        }
    }


    fclose(fp);
    jettison_inputstruct(is);
    fclose(output);

    return 0;
}


char *removeLeadingSpaces(char *str)
{
    static char str1[1000];
    int count = 0, j, k;

    /* Iterate String until last
       leading space character  */
    while (str[count] == ' ')
    {
        count++;
    }

    /* Putting string into another
       string variable after
       removing leading white spaces */
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

int compareJval(Jval j1, Jval j2){

    return strcmp(j1.s, j2.s);
}
