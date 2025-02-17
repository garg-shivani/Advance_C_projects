#include "id3_writer.h"
#include "main.h"
#include "id3_utils.h"




int edit_tag(TagData tag_data, char ch, char* data)
{

    switch(ch)
    {
        case 't':
            update(&tag_data, "TIT2", data);
            break;
        case 'a':
            update(&tag_data,"TPE1" , data);
            break;
        case 'A':
            update(&tag_data,"TALB", data);
            break;
        case 'y':
            update(&tag_data, "TYER", data);
            break;
        case 'm':
            update(&tag_data, "TCON", data);
            break;
        case 'c':
            update(&tag_data, "COMM", data);
            break;
        default:
            display_help();
            return -1;
    }

}
int update(TagData* tag_data, char* frame,   char* data)
{
    FILE* temp = fopen("sample.mp3", "wb+");
    char header[10];
    int frame_found = 0;
    if(temp == NULL)
    {
        printf("Error while creating temp file\n");
    }
    open_files(tag_data);
    fread(header,1, 10, tag_data->fptr);
    fwrite(header, 1, 10, temp);
    while (!frame_found)
    {
        char frame_details[11];
        if(fread(frame_details, 1, 11, tag_data->fptr) == 0)
            return 1;
        int prev_frame_size = get_frame_size(&frame_details[4]); 
        int new_frame_size= 0;
        if(strncmp(frame , frame_details, 4) == 0 )
        {

            if(frame == "COMM")
            {
                new_frame_size = strlen(data) +5 ;// + 5 for lang descriptor , encoding bit;

                if(convert_big_endian(new_frame_size, &frame_details[4])== 1)
                {
                    printf("Error while converting the frmae_size\n");
                }
                fwrite(frame_details, 1, 11, temp);
                char buffer[4];
                fread(buffer, 1, 4, tag_data->fptr);
                fwrite(buffer, 1, 4, temp);
                tag_data->tag_size = tag_data->tag_size - prev_frame_size + new_frame_size;
                fseek(tag_data->fptr, prev_frame_size-5, SEEK_CUR);
                fwrite(data, 1, new_frame_size- 5, temp);
            }
            else{  
                new_frame_size = strlen(data) +1 ;
                if(convert_big_endian(new_frame_size, &frame_details[4])== 1)
                {
                    printf("Error while converting the frmae_size\n");
                }
                fwrite(frame_details, 1, 11, temp);
                tag_data->tag_size = tag_data->tag_size - prev_frame_size + new_frame_size;
                fseek(tag_data->fptr, prev_frame_size-1, SEEK_CUR);
                fwrite(data, 1, new_frame_size - 1, temp);
            }          
            frame_found = 1;
        }
        else{
            //in the case when we didn't get the frame, we have to copy the 
            // the 11 bytes as it is to the sample file 
            // and also we have to copy the the frame content as well to the sample file
            fwrite(frame_details, 1, 11, temp);
            if(copy_frame_content(tag_data->fptr, temp, prev_frame_size -1)== FAILURE)
            {
                printf("Error while copying the frame_content");
            }
        }
    }
    if(copy_remainng_data(tag_data->fptr, temp)== 1)
    {
        printf("Error while copying remaining file data\n");
    }
        // Update frame size in sync-safe format
    char updated_size[4];   
    size_to_string(updated_size, tag_data->tag_size);    
    fseek(temp, 6, SEEK_SET);
    fwrite(updated_size, 4, 1, temp);
    rewind(tag_data->fptr);
    rewind(temp);
    if (copy_remainng_data(temp, tag_data->fptr) != SUCCESS)
    {
       return FAILURE;
    }
    return 0;
}