#include "main.h"
#include "id3_utils.h"

/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */
void display_help() {
    printf("Usage: mp3tagreader [options] filename\n");
    printf("Options:\n");
    printf("  -h               Display help\n");
    printf("  -v               View tags\n");
    printf("  -e -t/-T/-a/-A/-y/-c/-g <value>  Edit tags\n");
}

void display_error(char* str)
{
    printf("%s", str);
    return;
}

/**
 * @brief Main function to handle command-line arguments and execute appropriate actions.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        display_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        display_help();
        return 0;
    } else if (strcmp(argv[1], "-v") == 0 && argc == 3) {
        TagData tag_data;
        tag_data.file_name = argv[2];
        if(open_files(&tag_data) == FAILURE) // adding the 
        {
            printf("Error while opening file\n");
        }
        if(read_validate_id3_version_tag_size(&tag_data)== SUCCESS)
        {
            if(view_data(&tag_data) == SUCCESS)
            {
                printf("Raeding and viewing of tags done successfully\n");
                fclose(tag_data.fptr);
            }
            else{
                printf("Error while viewing the id3 tags\n");
            }
        }
        else
        {
            printf("%s is not a valid ID3 file. Enter valid ID3 file\n", tag_data.file_name);
        }

    } else if (strcmp(argv[1], "-e") == 0 && argc == 5) {
        TagData tag_data;
        tag_data.file_name = argv[4];
        if(open_files(&tag_data) == FAILURE)
        {
            printf("Error while opening files\n");
        }
        if(read_validate_id3_version_tag_size(&tag_data) == SUCCESS)
        {
            if (edit_tag(tag_data, argv[2][1], argv[3]) == SUCCESS) {
                remove("sample.mp3");
                printf("File written successfully\n");
            }
            else{
                printf("Error while writing in file\n");
            }
        }
        else
        {
            printf("%s is not a valid ID3 file. Enter valid ID3 file\n", tag_data.file_name);
        }    
    } else {
        display_help();
        return 1;
    }

    return 0;
}
