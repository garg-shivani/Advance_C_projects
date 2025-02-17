#ifndef ID3_UTILS_H
#define ID3_UTILS_H
#include <stdio.h>
/**
 * @brief Structure to hold ID3 tag data.
 */
typedef struct {
    FILE *fptr;
    char* file_name;
    int tag_size;
    char *version; /**< Version of the ID3 tag */
    char *title;   /**< Title of the song */
    char *artist;  /**< Artist of the song */
    char *album;   /**< Album name */
    char *year;    /**< Year of release */
    char *comment; /**< Comment */
    char *genre;   /**< Genre */
    // Add other fields as needed
} TagData;

/**
 * @brief Creates a new TagData structure.
 * 
 * @return Pointer to the newly created TagData structure.
 */
TagData* create_tag_data();

/**
 * @brief frees the TagData Structure
 * 
 * @param pointer to the TagData that is to be freed.
 */
void free_tag_data(TagData *data);

int get_sync_safe_int(unsigned char bytes[]);
int open_files(TagData*);
int copy_frame_content(FILE *src, FILE* dest, int);
int get_frame_size(char* frame_size);
int convert_big_endian(unsigned int, char*);
int copy_remainng_data(FILE*, FILE*);
void size_to_string(char *, int );
#endif // ID3_UTILS_H
