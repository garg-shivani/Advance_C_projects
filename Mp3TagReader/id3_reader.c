/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "id3_reader.h"
#include <string.h>



int read_data(TagData* tag_data , char* frame_name, char** dest)
{
    int frame_found = 0;
    fseek(tag_data->fptr, 10, SEEK_SET);
    while(!frame_found)
    {
        char frame_details[11];
        if(fread(frame_details, 1, 11, tag_data->fptr) == 0)
            return -1;
        int frame_size = get_frame_size(&frame_details[4]); 
        if(strncmp(frame_details, frame_name, 4)== 0)
        {
            if(frame_name == "COMM")
            {
                fseek(tag_data->fptr, 4, SEEK_CUR);
                *dest = malloc(frame_size - 4);
                if(*dest == NULL)
                {
                    //Memory Allocation Failed
                    return -1;
                }
                if(fread(*dest, 1, frame_size- 5, tag_data->fptr)!= frame_size -5)
                {
                    free(*dest);
                    *dest = NULL;
                    return -1;
                }
                (*dest)[frame_size-5] = '\0';// Null terminate the string\\ here its important because its a pointer to an array if we dont use 
                // bracket here then it will be treated as array of pointers 
                frame_found = 1;
                return 0;
            }
            else{
                *dest = malloc(frame_size);
                if(*dest == NULL)
                {
                    //Memory Allocation Failed
                    return -1;
                }

                if(fread(*dest, 1, frame_size- 1, tag_data->fptr)!= frame_size -1)
                {
                    free(*dest);
                    *dest = NULL;
                    return -1;
                }
                (*dest)[frame_size-1] = '\0';// Null terminate the string\\ here its important because its a pointer to an array if we dont use 
                // bracket here then it will be treated as array of pointers 
                frame_found = 1;
                return 0;
            }
        }
        else
        {
            if(fseek(tag_data->fptr, frame_size - 1, SEEK_CUR)!= 0)
            {
                return 1;// Error moving the file pointer
            }
        }
    }
    *dest = NULL;
    return 1;
}

/**
 * @brief displays the id3 tag to the console
 * 
 * @param TagData struct that contains the id3 tag values
 */
void display_metadata(const TagData *data) {
    // Implementation for displaying metadata
    // printf("title is %s \n", data->title);
    // printf("artist is %s \n",data->artist);
    // printf("album is %s \n", data->album);
    // printf("year is %s \n",  data->year);
    // printf("content is %s \n", data->genre);
    // printf("comment is %s \n", data->comment);
    printf("----------------------------SELECTED VIEW DETAILS------------------------------\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("-----------------------MP3 TAG READER AND EDITOR FOR ID3V2-----------------------\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-20.20s : \t\t%-50.50s\n", "TITLE", data->title);
    printf("%-20.20s : \t\t%-50.50s\n", "ARTIST", data->artist);
    printf("%-20.20s : \t\t%-50.50s\n", "ALBUM", data->album);
    printf("%-20.20s : \t\t%-50.50s\n", "YEAR", data->year);
    printf("%-20.20s : \t\t%-50.50s\n", "MUSIC", data->genre);
    printf("%-20.20s : \t\t%-50.50s\n", "COMMENT", data->comment);
    printf("--------------------------------------------------------------------------------\n\n");
    printf("---------------------------DETAILS DISPLAYED SUCCESSFULLY------------------------\n");
}    

/**
 * @brief view tags from main function
 * 
 * @param constant character pointer to the mp3 file
 */
int view_data(TagData* tag_data) {
    if(read_data(tag_data, "TIT2", &(tag_data->title)) == -1)
        return -1;
    if(read_data(tag_data, "TPE1", &(tag_data->artist)) == -1)
        return -1;
    if(read_data(tag_data, "TALB", &(tag_data->album)) == -1)
        return -1;
    if(read_data(tag_data, "TYER", &(tag_data->year)) == -1)
        return -1;
    if(read_data(tag_data, "TCON", &(tag_data->genre)) == -1)
        return -1;
    if(read_data(tag_data, "COMM", &(tag_data->comment)) == -1)
        return -1;
    display_metadata(tag_data);
    free(tag_data->title);
    free(tag_data->artist);
    free(tag_data->album);
    free(tag_data->year);
    free(tag_data->genre);
    free(tag_data->comment);
    return 0;
}