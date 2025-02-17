#ifndef MAIN_H
#define MAIN_H
#define SUCCESS 0
#define FAILURE 1
#include "id3_reader.h"
#include "id3_writer.h"
#include "id3_utils.h"
#include <stdio.h>
#include <string.h>
/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */

void display_help();
int read_validate_id3_version_tag_size(TagData*);
#endif // MAIN_H
