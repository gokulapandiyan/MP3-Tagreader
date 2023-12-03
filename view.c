#include"tag.h"

/* 
 * This function is responsible for printing the entire song information 
 * It takes input argv and structure that we have defined
 * Output just prints the informations
 */
Status version_info(char *argv[],Name *aud_info){

    //open files and read arguments 
    if(!strcmp(strstr(argv[2],"."),".mp3")){

        //get the file name from command line and stores in aud_info->f_name
        aud_info->f_name=argv[2];

        //Oprn the file using file pointer
        aud_info->fptr=fopen(aud_info->f_name,"r");

        //error handling for openning required files for view
        if(!aud_info->fptr){

            perror("fopen");
            
            fprintf(stderr,"ERROR : Unable to open the file %s",aud_info->f_name);
            
            return FAILURE;
        }
    }

    //create a flag of size 4 to get the version ID of the mp3 file
    char ad_name[4];

    //rewind the file ftell to initial position 
    rewind(aud_info->fptr);

    //read 3 characters from the file and store it in the flag
    fread(ad_name,3,1,aud_info->fptr);

    //add NULL at last position 
    ad_name[3]='\0';

    aud_info->version=ad_name;
    printf("+---------------------------------------+\n");

    printf("%c\t     Version %s V",'|',aud_info->version);

    //create another flag to store the subversion v2 or v3 and print it
    int x=0;

    //read 2 char and stores in flag 
    fread(&x,2,1,aud_info->fptr);
    
    printf("%d  %12c\n",x,'|');
    
    printf("+-----------+---------------------------+\n");
    //Get move the ftell to 6th position as first 3 bytes are version next 2 is sub version
    // next one is extended header version and then 4 bytes are size of the mp3 from 6 to 10
    fseek(aud_info->fptr,6,SEEK_SET);

    //store the size in the variable 
    aud_info->aud_size=get_size(aud_info->fptr);

    //print for user accknooledgement
    printf("|%-11.11s| %d\n"," Size ",aud_info->aud_size);

    printf("+-----------+----------------------------\n");

    /*
     * The tags are basically in order like TITLE,ARTIST,TRACK,ALBUM
     * Here we are checking and printing just 8 tags in total 
     * If the tag present in the song then it is displayed
     */

    //create a flag for checking the tags 
    char tit[5];

    //read the four bytes
    fread(tit,4,1,aud_info->fptr);

    tit[4]='\0';

    // TIT2 refers to the title of the song it starts from the 11th byte 
    // followed by size of the title 3 flag bytes and actual title contents
    if(!strcmp(tit,"TIT2")){

        printf("|%-11.11s| "," Title ");
        
        // Refer the last function in this file which gets the data 
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
   
    // The 2nd tag contains artist information like his name
    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    if(!strcmp(tit,"TPE1")){
    
        printf("|%-11.11s| "," Artist ");
    
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
   
   //The 3rd tag contains TRACK info as TRCK 
   fread(tit,4,1,aud_info->fptr);

    tit[4]='\0';
   
    if(!strcmp(tit,"TRCK")){
   
        printf("|%-11.11s| "," Track ");
   
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
   
   //This case where the song dosent have TRCK tag then the ftell moves backwards to 4 bytes
    else{

        fseek(aud_info->fptr,-4,SEEK_CUR);
    }
    
    // TALB contains the album tag
    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    if(!strcmp(tit,"TALB")){
        
        printf("|%-11.11s| "," Album ");
        
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
    
    else{
    
        fseek(aud_info->fptr,-4,SEEK_CUR);
    }
    
    // TYER or TDRC  Both refers to the year tag i.e the song published year
    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    if(!strcmp(tit,"TYER")||!strcmp(tit,"TDRC")){
    
        printf("|%-11.11s| "," Year ");
    
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
    
    else{
    
        fseek(aud_info->fptr,-4,SEEK_CUR);
    }
    
    // TCON refers to the Genere of the song
    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    if(!strcmp(tit,"TCON")){
    
        printf("|%-11.11s| "," Genere ");
        
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
    
    else{
    
        fseek(aud_info->fptr,-4,SEEK_CUR);
    }
    
    // COMM refers to the comments of the song
    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    if(!strcmp(tit,"COMM")){
    
        printf("|%-11.11s| "," Comment ");
    
        get_data(aud_info);

        printf("+-----------+----------------------------\n");
    }
    
    fclose(aud_info->fptr);
    
}

/* 
 * This function is used to get the size of the string after getting the tags
 * Input : file pointer
 * output : returns the size
 */

int get_size(FILE *fptr){
    
    //flag variable
    int size;
        
    // Read the 4 bytes and stores in size 
    fread(&size,4,1,fptr);

    //this function reverse the bytes.Refer mods.c for this function
    rev_size(&size);

    return size;
}

/*
 * This function gets the actual data and prints it
 * Input : structure
 * Output : prints char by char
 */

void get_data(Name *aud_info){

    //The size is got by get size function
    int size=get_size(aud_info->fptr);

    //Dynamically allocates the memory for the read bytes to store here
    char *txt=malloc(size);

    //skips the 3 flag bytes
    fseek(aud_info->fptr,3,SEEK_CUR);
    
    //Reads the bytes upto size
    fread(txt,size-1,1,aud_info->fptr);
    txt[size-1]='\0';
    
    //prints the characters up to size
    for(int i=0;i < size;i++){

        printf("%c",txt[i]);
    }
    
    printf("\n");
    
    //free the heap used by malloc
    free(txt);
}

