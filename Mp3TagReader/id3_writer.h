#ifndef ID3_WRITER_H
#define ID3_WRITER_H

#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */


/**
TODO: Add documention as sample given above
 */
int edit_tag(TagData , char , char* );
int update(TagData* , char* ,   char* );

#endif // ID3_WRITER_H
