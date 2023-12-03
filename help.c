#include"tag.h"

/* 
 * This function just prints the user how to use this
 * program in correct way and its limitations
 * This is for only ID3 V2.3 and V2.4
 */

void help(){

    printf("--------------------------------------------------\n");

    printf("This works only for only ID3 V2.3 and V2.4\n");

    printf("--------------------------------------------------\n");

    printf("\t\t\tTo edit\n--------------------------------------------------\n");

    printf("Usage : a.out -e -[tTaAycgh] 'Value' file.mp3\n");
    
    printf("--------------------------------------------------\n");
    
    printf("\t\t\tTo view\n--------------------------------------------------\nUsage : a.out -v file.mp3\n");
    
    printf("--------------------------------------------------\n");
    
    printf("\tEx  : \t\t./a.out -v sample.mp3\n");
    
    printf("--------------------------------------------------\n");
    
    printf("\t-t ->\t\tModifies Title tag\n");
    
    printf("\t-T ->\t\tModifies Track tag\n");
    
    printf("\t-a ->\t\tModifies Artist tag\n");
    
    printf("\t-A ->\t\tModifies Album tag\n");
    
    printf("\t-y ->\t\tModifies Year tag\n");
    
    printf("\t-c ->\t\tModifies Comments tag\n");
    
    printf("\t-g ->\t\tModifies Genre tag\n");
    
    printf("\t-h(or)--help -> Displays this help info\n");
    
    printf("\t-v ->\t\tPrints version info\n");
    
    printf("--------------------------------------------------\n");
}