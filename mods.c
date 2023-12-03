#include"tag.h"

/*
 * This function edits the title that user inputs
 * INPUT : struct that has CLA stored in title
 * OUTPUT : prints the name and done
 */

Status title(Name *aud_info){

    int old_size; // flag for already have txt size
    
    // condition for head
    if(frame_header_cmpr(aud_info,"TIT2",&old_size)==SUCCESS){
    
        //length of the title
        int size=strlen(aud_info->aud_title)+1;

        //This function copies the data upto before the title tag
        copy_before_data(aud_info,size);

        //writes the user txt to copy.mp3
        fwrite(aud_info->aud_title,size-1,1,aud_info->copy_fptr);

        //copies remaining data
        copy_rem_data(aud_info,old_size);

        //prints for user acknoledgement
        printf("----------------------------------------\n");

        printf("Title successfully edited to %s\n",aud_info->aud_title);
        
        printf("----------------------------------------\n");
        
        return SUCCESS;
    }
    else{

        printf("----------------------------------------\n");

        printf("ERROR : Title tag not found\n");

        printf("----------------------------------------\n");
        
        return FAILURE;
    }
}

/*
 * This function edits the track that user inputs
 * INPUT : struct that has CLA stored in track
 * OUTPUT : prints the name and done
 */


Status track(Name *aud_info){

    int old_size;
    
    if(frame_header_cmpr(aud_info,"TRCK",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_track)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_track,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Track successfully edited to %s\n",aud_info->aud_track);

        printf("----------------------------------------\n");
        return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR :Track tag not found\n");

        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function edits the artist that user inputs
 * INPUT : struct that has CLA stored in artist
 * OUTPUT : prints the name and done
 */

Status artist(Name *aud_info){
    
    int old_size;
    
    if(frame_header_cmpr(aud_info,"TPE1",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_artist)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_artist,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Artist successfully edited to %s\n",aud_info->aud_artist);

        printf("----------------------------------------\n");
        
        return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR : Artist tag not found\n");
    
        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function edits the album that user inputs
 * INPUT : struct that has CLA stored in album
 * OUTPUT : prints the name and done
 */

Status album(Name *aud_info){
    
    int old_size;
    
    if(frame_header_cmpr(aud_info,"TALB",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_album)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_album,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Album successfully edited to %s\n",aud_info->aud_album);

        return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR : Album tag not found\n");
    
        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function edits the year that user inputs
 * INPUT : struct that has CLA stored in year
 * OUTPUT : prints the name and done
 */

Status year(Name *aud_info){
    
    int old_size;
    
    if(frame_header_cmpr(aud_info,"TYER",&old_size)==SUCCESS ||frame_header_cmpr(aud_info,"TDRC",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_year)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_year,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Year successfully edited to %s\n",aud_info->aud_year);

        printf("----------------------------------------\n");
        return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR : Year tag not found\n");
    
        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function edits the comment that user inputs
 * INPUT : struct that has CLA stored in comment
 * OUTPUT : prints the name and done
 */

Status comments(Name *aud_info){
    
    int old_size;
    
    if(frame_header_cmpr(aud_info,"COMM",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_comments)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_comments,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Comments successfully edited to %s\n",aud_info->aud_comments);

        printf("----------------------------------------\n");

        return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR : Comments tag not found\n");

        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function edits the gerne that user inputs
 * INPUT : struct that has CLA stored in gerne
 * OUTPUT : prints the name and done
 */

Status gerne(Name *aud_info){
    
    int old_size;
    
    if(frame_header_cmpr(aud_info,"TCON",&old_size)==SUCCESS){
    
        int size=strlen(aud_info->aud_genere)+1;

        copy_before_data(aud_info,size);

        fwrite(aud_info->aud_genere,size-1,1,aud_info->copy_fptr);

        copy_rem_data(aud_info,old_size);

        printf("----------------------------------------\n");

        printf("Genere successfully edited to %s\n",aud_info->aud_genere);

         printf("----------------------------------------\n");

         return SUCCESS;
    }
    else{
        
        printf("----------------------------------------\n");

        printf("ERROR : Genere tag not found\n");

        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/*
 * This function is used to copy the contents till above the required tag
 * INPUT : struct , char *(from argv) and the int pointer
 * OUTPUT : returns the enum SUCCESS and FAILURE
 */

Status frame_header_cmpr(Name *aud_info, char str[],int *old_size){

    //move the ftell to initial position
    rewind(aud_info->fptr);
    
    //write upto 10 bytes
    fseek(aud_info->fptr,10,SEEK_SET);

    // flag for getting the tag
    char tit[5];

    fread(tit,4,1,aud_info->fptr);
    
    tit[4]='\0';
    
    int size;

    //compares the tags and str from start to till getting TEXT (actual content of the tag)or APIC(logo image) tag
    while(strcmp(tit,str) && (strcmp(tit,"TEXT") && strcmp(tit,"APIC"))){

        //get the size
        size=get_size(aud_info->fptr); // call from view.c file

        // move the ftell to thae size and + 2 is for skipping frame tag
        fseek(aud_info->fptr,size+2,SEEK_CUR);

        //reads and writes 4 tag bytes in tit variable
        fread(tit,4,1,aud_info->fptr);

        fwrite(tit,4,1,aud_info->fptr);
        
        tit[4]='\0';
    }

    //compares weather the tit has req. tag or not 
    if(!strcmp(tit,str)){
        
        //gets the size of already existed size
        *old_size=get_size(aud_info->fptr);

        //move ftell 4 bytes backwards as it is used to rewrite the size too
        fseek(aud_info->fptr,-4,SEEK_CUR);

        return SUCCESS;
    }
    return FAILURE;
}

/* 
 * This function is used to copy the data upto before the size byte of the tag
 * Input : struct and size of current str
 */
Status copy_before_data(Name *aud_info,int size){

    //flag for position of ftell
    int f_tell=ftell(aud_info->fptr);
    
    //reset the ftell
    rewind(aud_info->fptr);
    
    //var for copying the data byte by byte
    char c;

    //copies the data up to old ftell position
    while(ftell(aud_info->copy_fptr) < f_tell){

        fread(&c,1,1,aud_info->fptr);
        
        fwrite(&c,1,1,aud_info->copy_fptr);
    }

    //reverse the size using pointer (Refer this function in below)
    rev_size(&size);

    //writes the size to the copy.mp3 using file pointer
    fwrite(&size,4,1,aud_info->copy_fptr);

    //var used to copy and write frame flag
    char ch[3];
    
    fread(ch,3,1,aud_info->fptr);
    
    fwrite(ch,3,1,aud_info->copy_fptr);
}

/* 
 * This function copies the remaining data to the copy.mp3
 * Input struct containing file pointer and old sizeof str
 */

Status copy_rem_data(Name *aud_info,int old_size){

    //skips the old size and frame flag 3 bytes
    fseek(aud_info->fptr,old_size+3,SEEK_CUR);

    //variable used to copy all the data byte by byte to the copy.mp3 file
    char ch;

    //terminate at 0 because EOF is -1
    while(fread(&ch,1,1,aud_info->fptr) > 0){
        
        //write the entire data byte by byte
        fwrite(&ch,1,1,aud_info->copy_fptr);
    }
}

/* 
 * This function swaps the value of int using int pointer
 * input int pointer
 */

void rev_size(int *size){

    char *ptr=(char *)size;

    char temp = *ptr;
    
    *ptr = *(ptr+3);
    
    *(ptr+3)=temp;
    
    temp=*(ptr+1);
    
    *(ptr+1)=*(ptr+2);
    
    *(ptr+2)=temp;
}