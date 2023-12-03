
#include"tag.h"

/*Main function routes to the correct file to edit view or help files
 * 
 * take a look at line 23 , 37, 53
 */

int main(int argc, char *argv[]){

    //Create a required variables in user defined structure
    Name aud_info;

    //check for required arguments
    if(argc == 1 ){

        //if argument count dosent meet the requirment then go to print error statement 
        goto l1;
    }

    //help section 
    else if(check_opr_type(argv)==HELP){

        //help section for user.For further reference look at view.c 
        help();
        return SUCCESS;
    }

    //edit section 
    else if(check_opr_type(argv)==EDIT){

        //If the argument is above or below 5 then go to print error section
        if(argc == 5){

            //Acknoledge user that s(he) selected edit option
            printf("----------------------------------------\n");
            printf(" \t  Selected edit option  \t \n");

            //go to function in do_mods.c 
            if(do_mods(argv,&aud_info)==SUCCESS){

                if(remove(aud_info.f_name)== 0){

                    if(rename(aud_info.copy_fname,aud_info.f_name)==0){
                        
                        printf("Done\n");
                
                        printf("----------------------------------------\n");

                        return SUCCESS;
                    }
                
                }
                
            }

            remove(aud_info.copy_fname);

            return FAILURE;
        }
        goto l1;
    }

    //if argc is above or below 3 then give error to the user
    else if(check_opr_type(argv)==VIEW){
        
        if(argc == 3){

            //Acknoledge user that s(he) selected view option
            printf("+---------------------------------------+\n");

            printf("|\t  Selected view option  \t|\n");

            //go to the view_info function in view.c
            version_info(argv,&aud_info);

            return SUCCESS;
        }
        goto l1;
    }
    
    //The l1: unconditional jump for any errors happened above cases
    else{
        l1:
        printf("--------------------------------------------------\n");
        printf("\t\tINVALID ARGUMENTS\n--------------------------------------------------\n");
        printf("Usage : ./a.out -v filename.mp3\nFor more information try using --help or -h\n");
        printf("--------------------------------------------------\n");
        return FAILURE;
    }
}
/*
 * This function checks the operation type HELP , EDIT , or VIEW
 * It takes the input from argv[1] i.e char*
 * It gives output enum described as HELP , EDIT , VIEW anf FAILURE
 */

Status check_opr_type(char *argv[]){

    //Compares the argv[1] and const literals and returns to the particular function
    if(!strcmp(argv[1],"-h")||!strcmp(argv[1],"--help")){

        return HELP;
    }
    if(!strcmp(argv[1],"-e")){
        
        return EDIT;
    }
    if(!strcmp(argv[1],"-v")){
        
        return VIEW;
    }
    return FAILURE;
}