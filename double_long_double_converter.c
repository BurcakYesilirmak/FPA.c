// This code convertes a file content: conversion "double" words to "long double"
// Burcak Yesilirmak

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char* replaceWord(const char* s, const char* old_word, 
                  const char* new_word) 
{ 
    char* result; 
    int i, cnt = 0; 
    int new_wordlen = strlen(new_word); 
    int old_wordlen = strlen(old_word); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], old_word) == &s[i]) { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += old_wordlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char*)malloc(i + cnt * (new_wordlen - old_wordlen) + 1); 
  
    i = 0; 
    while (*s) { 
        // compare the substring with the result 
        if (strstr(s, old_word) == s) { 
            strcpy(&result[i], new_word); 
            i += new_wordlen; 
            s += old_wordlen; 
        } 
        else
            result[i++] = *s++; 
    } 
    result[i] = '\0'; 
    return result; 
} 

int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[500];
    char ch_long[] = "long double"; 
    char* result = NULL; 
    FILE *temporary = tmpfile();

	if((fp = fopen(fname, "r")) == NULL) {  //  open a file, get the content of the file
		return(-1);
	}  

	while(fgets(temp, 500, fp) != NULL) {   // get the content of the file, line by line        
        if((strstr(temp, str)) == NULL)     //start to create temporary file and copy if there is no word "double"
          fprintf(temporary, "%s" ,temp); 
		   if((strstr(temp, str)) != NULL) {    // search for our string in the content we took from the file
            result = replaceWord(temp, str, ch_long); // function that changes double word with long double 
            printf("%s", temp);
            printf("%s\n", result);
            fprintf(temporary, "%s" , result);   // copy line if there is word "double"
         //   printf("line: %d\n", line_num);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, could not find a match.\n");
	}
		fclose(fp);
        fclose(temporary);
   	return(0);
}

int main(int argc, char *argv[]) {
	int result, error;
	result = Search_in_File("DOUBLE_LONGDOUBLE.txt", "double");
	if(result == -1) {
//		perror("Error");
		printf("Error number = %d\n", error);
		exit(1);
	}
	return(0);
}














