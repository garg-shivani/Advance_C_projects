#include <stdlib.h>
#include <string.h>
#include "id3_utils.h"
#include "main.h"
/**
 * @brief Creates a new TagData structure.
 * 
 * @return Pointer to the newly created TagData structure.
 */
TagData* create_tag_data() {
    TagData *data = (TagData *)malloc(sizeof(TagData));
    if (data) {
        data->version = NULL;
        data->title = NULL;
        data->artist = NULL;
        data->album = NULL;
        data->year = NULL;
        data->comment = NULL;
        data->genre = NULL;
        // Initialize other fields as needed
    }
    return data;
}

/**
 * @brief frees the TagData Structure
 * 
 * @param pointer to the TagData that is to be freed.
 */
void free_tag_data(TagData *data) {
    if (data) {
        free(data->version);
        free(data->title);
        free(data->artist);
        free(data->album);
        free(data->year);
        free(data->comment);
        free(data->genre);
        // Free other fields as needed
        free(data);
    }
}

int get_sync_safe_int(unsigned char bytes[4])
{
    return (bytes[0] << 21) | (bytes[1] << 14)   | (bytes[2] << 7)| bytes[3];
}
/*
* @brief adding fptr inside the tag_dat->fptr;
* @return SUCCESS or FAILURE 
*/

int open_files(TagData* tag_data)
{
    
    tag_data->fptr= fopen(tag_data->file_name, "rb+");
    if(tag_data->fptr == NULL)
    {
        return FAILURE;
    }
    return SUCCESS;
}

int read_validate_id3_version_tag_size(TagData* tag_data)
{
    char buffer[10];
    if(fread(buffer, 1, 10 , tag_data->fptr))
    {
        if(strncmp("ID3", buffer,3 ) == 0)
        {
            if(buffer[3] == 03 && buffer[4] == 00)
            {
                tag_data->tag_size = ((buffer[6] & 0x7F)<<21) | ((buffer[7] & 0x7F) <<14)|((buffer[8] & 0x7F) << 7) | (buffer[9] & 0x7F);
                return 0;
            }
        }
    }
    else{
        return - 1;
    }
}

int copy_frame_content(FILE *src, FILE* dest, int size)
{
    char ch;
    while(size--)
    {
        if(fread(&ch, 1, 1, src) != 1)
        {
            return 1;
        }
        if(fwrite(&ch, 1, 1, dest) != 1)
        {
            return 1;
        }
    }
    return 0;
}
int get_frame_size(char* frame_size)
{
    return ((frame_size[0] << 24) | (frame_size[1] << 16) | (frame_size[2] << 8 ) | frame_size[3]);
}
/*
* converts the integer value from little endian to big endian
* and storing that vallue to the char buffer that is provided as paramater
*/
int convert_big_endian(unsigned int little, char* big)
{
    big[0] = (little & 0xFF000000) >>24;
    big[1] = (little & 0x00FF0000) >>16;
    big[2] = (little & 0x0000FF00) >> 8;
    big[3] = (little & 0x000000FF) >> 0;
    return 0;
}
void size_to_string(char *updated_size, int size)
{
    for (int i = 0; i < 4; i++) {
        updated_size[i] = (size >> (3 - i) * 7) & 0x7F;
    }
}

int copy_remainng_data(FILE* src, FILE* dest)
{
    char ch;
    while(fread(&ch, sizeof(char), 1, src) == 1)
    {
        fwrite(&ch, sizeof(char), 1, dest);
    }
    ch = EOF;
    fwrite(&ch, sizeof(char), 1,dest);
    return 0;
}
