#include"tag.h"

/*
 * do_mods function exactly routes to the sub functions
 * Takes input as argv and gives output as done and error
 */


Status do_mods(char *argv[],Name *aud_info){
    
    //reads the argv's and verifies weather these are correct for edit or not
    if(read_and_validate_args(argv) == SUCCESS){

        // Opens all the required files 
        if(open_files(argv,aud_info)==SUCCESS){

            //goes to the title function in mods.c file
            if(do_opr(argv)==TITLE){

                aud_info->aud_title=argv[3];
                
                if(title(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }
            
             //goes to the track function in mods.c file
            else if(do_opr(argv)==TRACK){
              
                aud_info->aud_track=argv[3];
              
                if(track(aud_info)==SUCCESS){
                    
                    return SUCCESS;
                }
                return FAILURE;
            }

             //goes to the artist function in mods.c file
            else if(do_opr(argv)==ARTIST){

                aud_info->aud_artist=argv[3];
                
                if(artist(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }

             //goes to the album function in mods.c file
            else if(do_opr(argv)==ALBUM){

                aud_info->aud_album=argv[3];
                
                if(album(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }

             //goes to the year function in mods.c file
            else if(do_opr(argv)==YEAR){

                aud_info->aud_year=argv[3];
                
                if(year(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }

            // //goes to the comment function in mods.c file
            else if(do_opr(argv)==COMMENT){
       
                aud_info->aud_comments=argv[3];
                
                if(comments(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }

             //goes to the genere function in mods.c file
            else if(do_opr(argv)==GENERE){
          
                aud_info->aud_genere=argv[3];
                
                if(gerne(aud_info)==SUCCESS){

                    return SUCCESS;
                }
                return FAILURE;
            }

            //returns failure
            else{
                
                return FAILURE;
            }
        }

        //open files failure case
        else{
            return FAILURE; 
        }
    }

    //read and validate failure case
    else{

        printf("----------------------------------------\n");


        printf("Please pass the correct arguments\nFor more info try -h or --help\n");
        
        printf("----------------------------------------\n");

        return FAILURE;
    }
}

/* 
 * This function verifies that all the CLA's are correct
 * Input : argv
 * Output : enum SUCCESS and FAILURE
 */

Status read_and_validate_args(char *argv[]){

    // compares and that is mp3 file or not
    if(!strcmp(strstr(argv[4],"."),".mp3")){

        // compares for other arguments
        if(!strcmp(argv[2],"-t")||!strcmp(argv[2],"-T")||!strcmp(argv[2],"-a")||!strcmp(argv[2],"-A")||!strcmp(argv[2],"-y")||!strcmp(argv[2],"-c")||!strcmp(argv[2],"-g")){
            
            return SUCCESS;
        }
        printf("----------------------------------------\n");

        printf("Please pass mp3 files only\n");

        printf("----------------------------------------\n");
        
        return FAILURE;
    }
    
    return FAILURE;
}

/* 
 * Opens the required files for doing operations
 * Input : argv and structure
 * Output : enum SUCCESS / FAILURE
 */

Status open_files(char *argv[],Name *aud_info){

    //store the name from CLA
    aud_info->f_name=argv[4];

    //open the file by file pointer
    aud_info->fptr=fopen(aud_info->f_name,"r");
    
    //if file open failed show error
    if(!aud_info->fptr){
        
        perror("fopen");
        
        fprintf(stderr,"ERROR : Unable to open the file %s\n",aud_info->f_name);
        
        return FAILURE;
    }
    
    //create a new file named copy.mp3
    aud_info->copy_fname="copy.mp3";

    //open the file
    aud_info->copy_fptr=fopen(aud_info->copy_fname,"w");
    
    //ERROR handling for that file
    if(!aud_info->copy_fptr){

        perror("fopen");
        
        fprintf(stderr,"ERROR : Unable to open the file %s\n",aud_info->copy_fname);
        
        return FAILURE;
    }
    
    return SUCCESS;
}

/*
 * This function erturns the exact enum to do the sub function
 * Input : argv
 *  Output : enum for particular function
 */

Status do_opr(char *argv[]){
    
    // returns to title function
    if(!strcmp(argv[2],"-t")){
    
        return TITLE;
    }
    
    //returns to track function
    else if(!strcmp(argv[2],"-T")){
    
        return TRACK;
    }
    
    //returns to artist function
    else if(!strcmp(argv[2],"-a")){
    
        return ARTIST;
    }
    
    //returns to album function
    else if(!strcmp(argv[2],"-A")){
    
        return ALBUM;
    }
    
    //returns to year
    else if(!strcmp(argv[2],"-y")){
    
        return YEAR;
    }
    
    //returns to comment
    else if(!strcmp(argv[2],"-c")){
    
        return COMMENT;
    }
    
    //returns to gerene function
    else if(!strcmp(argv[2],"-g")){
    
        return GENERE;
    }
    
    //error if no option is above
    else{
        
        printf("----------------------------------------\n");

        printf("Please pass the correct arguments\nFor more info try -h or --help\n");
        
        printf("----------------------------------------\n");
        
        return FAILURE;
    }
}