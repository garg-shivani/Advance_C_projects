#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/**

 */
int read_data(TagData*  , char* , char** );

/**
 * @brief displays the id3 tag to the console
 * 
 * @param TagData struct that contains the id3 tag values
 */
void display_metadata(const TagData *data);

/**
 * @brief view tags from main function
 * 
 * @param constant character pointer to the mp3 file
 */
int view_data(TagData* ) ;

#endif // ID3_READER_H
