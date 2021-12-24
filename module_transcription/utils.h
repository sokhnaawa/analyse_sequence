#include <string.h>
#include "sequence.h"
#include "fileregex.h"
#include<sys/time.h>

int sequenceFileType(char *filename)
{
    regex_t r;
    const char * regex_text;
    regex_text = "[^\\s]+(.*?)\\.(txt|sec)$";
    compile_regex (& r, regex_text);
    int file_valid = match_regex (& r, filename);
    return file_valid;
}

int checkIfFileExists(char * filePath)
{
    int is_valid;
    if( access( filePath, F_OK ) == 0 ) {
        printf("Ok file %s exists \n", filePath);
        is_valid = 1;

        int is_valid_file_type = sequenceFileType(filePath);
        if(is_valid_file_type == 0) {
            printf("File type is invalid please enter txt or sec file. \n");
            is_valid = 0;
        }
    } else {
        printf("File %s not found . \n", filePath);
        is_valid =  0;
    }
    return is_valid;
}

int get_path_from_user(char ** filePath)
{
    char *v = (char*) malloc(128 * sizeof(char));
    printf("Please enter a sequence file Path: ");
    scanf("%s", v);

    while (checkIfFileExists(v) == 0)
    {
        printf("Please enter a sequence file Path: ");
        scanf("%s",v);
    }
    *filePath = v;

    return 1;

}

void extract_sequence(char * filename, char ** sequence) {
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler)
    {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size)
        {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
        fclose(handler);
    }
    *sequence = buffer;

}

int save_sequence(char * data, char * filePath) {
    char *filename = filePath;
    // open the file for writing

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file %s", filename);
        return -1;
    }

    int i,n;
    for(i = 0; i < strlen(data); ++i)
    {
        if(i%80 != 0 && i >= 0)
        {
            fprintf(fp, "%c", data[i]);
        }
        else
        {
            if( i> 0)
            {
                fputs("\n", fp);

            }
        }
    }

    // close the file
    fclose(fp);
    /* Success message */
    printf("File created and saved successfully. :) \n");
    return 1;
}

char * replaceWord(const char* s, const char* oldW, const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

long long timeInMilliseconds() {
    struct tm xmas = { 0, 0, 0, 24, 11, 116 };
    time_t rawtime = mktime(&xmas);

    if (rawtime == -1) {

        puts("The mktime() function failed");
        return 1;
    }

   return rawtime;
}


