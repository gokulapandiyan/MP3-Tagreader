#ifndef _TAG_H_
#define _TAG_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef enum{
    SUCCESS,
    FAILURE,

    HELP,
    EDIT,
    VIEW,

    TITLE,
    TRACK,
    ARTIST,
    ALBUM,
    YEAR,
    COMMENT,
    GENERE
}Status;


typedef struct filename{
    char *f_name;
    FILE *fptr;
    char *copy_fname;
    FILE *copy_fptr;

    int aud_size;
    char *version;

    char *aud_title;
    char *aud_track;
    char *aud_artist;
    char *aud_album;
    char *aud_year;
    char *aud_comments;
    char *aud_genere;
}Name;


/*Functions*/


/*checks the operation type*/
Status check_opr_type(char *argv[]);
/*reads and validate the CLA*/
Status read_and_validate_args(char *argv[]);
/*Opens the required files*/
Status open_files(char *argv[] ,Name *aud_info);
/*prints the details of the song*/
Status version_info(char *argv[],Name *aud_info);
/*gets the size of the str in metadata*/
int get_size(FILE *fptr);
/*gets the str in metadata*/
void get_data(Name *aud_info);


/*Returns to the exact modification function*/
Status do_mods(char *argv[],Name *aud_info);
/*do the operation */
Status do_opr(char *argv[]);
/*compares the frame header*/
Status frame_header_cmpr(Name *aud_info, char str[],int *old_size);
/*copies data up to particular tag*/
Status copy_before_data(Name *aud_info,int size);
/*continues copying after that tag*/
Status copy_rem_data(Name *aud_info,int old_size);
/*swaps the nibble of the int*/
void rev_size(int *size);



/*used to modify title*/
Status title(Name *aud_info);
/*used to modify the track*/
Status track(Name *aud_info);
/*used to modify the artist tag*/
Status artist(Name *aud_info);
/*used to modify the album tag*/
Status album(Name *aud_info);
/*used to modify the year tag*/
Status year(Name *aud_info);
/*used to modify the comments*/
Status comments(Name *aud_info);
/*used to modify the gerene tag*/
Status gerne(Name *aud_info);

/*used to display help section*/
void help();

#endif