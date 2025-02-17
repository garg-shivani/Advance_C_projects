#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width of bmp image= %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height of bmp image= %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo )
{
	char* ptr;
	if(argv[2] != NULL)
	{	if(strcmp(strchr(argv[2], (int)'.' ), ".bmp") == 0)//checking if the third argumemt is bmp file or not 
		{
			encInfo->src_image_fname = argv[2];
		}
		else
		{
			return e_failure;
		}
	}
	else
	{
		return e_failure;
	}
	if(argv[3] != NULL )
	{
		if(ptr = strchr(argv[3], '.'))
		{	
			strcpy(encInfo->extn_secret_file, ptr);//assigning extension to the structure member
			encInfo->secret_fname = argv[3];
			FILE *file = fopen(argv[3], "r");
			fseek(file, 0, SEEK_END);
			long file_size = ftell(file);
			fclose(file);
			if(file_size == 0)
			{
				printf("Secret file is empty\n");
				return e_failure;
			}
		}
		else{
			return e_failure;
		}
	}
	if(argv[4] != NULL)
	{
		if(strcmp(strchr(argv[4], (int)'.'), ".bmp") == 0)
		{
			encInfo->stego_image_fname = argv[4];
		}
		else{
			return e_failure;
		}
	}
	else
	{
		encInfo->stego_image_fname = "Stego.bmp";
	}
	return e_success;
}
Status do_encoding(EncodeInfo *encInfo)
{
	if(open_files(encInfo) == e_success)
	{
		printf("INFO: opening  required files for encoding\n");
		printf("INFO: Done\n");
		if(check_capacity(encInfo) == e_success)
		{
			printf("INFO: Capacity Check of beautiful.bmp to handel secret.txt\n");
			printf("INFO: Done\n");
			if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
			{
				printf("INFO: Copying Image Header\n");
				printf("INFO: Done\n");
				if(encode_magic_string(MAGIC_STRING, encInfo) == e_success)
				{
					printf("INFO: Encoding magic string\n");
					printf("INFO: Done\n");
					printf("the encoded file extension is %s\n", encInfo->extn_secret_file);
					if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file), encInfo) == e_success)
					{
						printf("INFO: Encoding extn size\n");
						printf("INFO: Done\n");
						if(encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_success)
						{
							printf("INFO: Encoding extn data \n");
							printf("INFO: Done\n");
							if(encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success)
							{
								printf("INFO: Encoding secret file size\n");
								printf("INFO: Done\n");
								if(encode_secret_file_data(encInfo) == e_success)
								{
									printf("INFO: Encoding secret file data\n");
									printf("INFO: Done\n");
									if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
									{
											printf("INFO: Copy remainig data\n");
											printf("INFO: Done");
											return e_success;
									}
									else
									{
										printf("Failed to copy remaining data\n");
										return e_failure;
									}
								}
								else
								{
									printf("Encode secret file data failure\n");
									return e_failure;
								}
							}
							else
							{
								printf("Secret file size encoding failed\n");
								return e_failure;
							}
						}
						else
						{
							printf("Encode extn data failure\n");
							return e_failure;
						}
					}
					else
					{
						printf("Encode extn size failure\n");
						return e_failure;
					}

				}
				else
				{
					printf("Encode magic string failure\n");
					return e_failure;
				}
			}
			else
			{
				printf("BMP header copy failure\n");
				return e_failure;
			}
		}
		else
		{
			printf("Capacity checking failure\n");
			return e_failure;
		}
	}
	else
	{
		printf("opening files for encoding failure\n");
		return e_failure;
	}

}
Status check_capacity(EncodeInfo *encInfo)
{
	encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);//height * width * 3
	encInfo->size_secret_file = get_file_size(encInfo->fptr_secret); // find sizeof secret file
	//printf("size secret file = %lu\n", encInfo->size_secret_file);
if(encInfo->image_capacity>(54+(strlen(MAGIC_STRING)*8)+(sizeof(int) * 8)+(strlen(encInfo->extn_secret_file)*8)+(sizeof(int) * 8)+encInfo->size_secret_file*8)) //check if size of image is gr
		return e_success;
	else
	{
		return e_failure;
	}
}
uint get_file_size(FILE *fptr)
{
	fseek(fptr, 0, SEEK_END);
	return ftell(fptr);

}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{

	//copy first 54 bytes from source to destination;
	char buffer[54];
	rewind(fptr_src_image);
	fread(buffer, 54, 1, fptr_src_image);
	fwrite(buffer,1, 54,fptr_stego_image);
	return e_success;

}
Status encode_magic_string(const char* magic_string, EncodeInfo *encInfo )
{
	fseek(encInfo->fptr_src_image, 54, SEEK_SET);
	if(encode_data_to_image(magic_string,strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image ) == e_success)
		return e_success;
	else
	{
		return e_failure;
	}
}

Status encode_secret_file_extn_size(int  extn_size, EncodeInfo *encInfo)
{
	char buffer[32];
	fread(buffer, 32, 1, encInfo->fptr_src_image);
	encode_size_to_lsb(extn_size, buffer);
	fwrite(buffer, 32,1, encInfo->fptr_stego_image);
	//printf("the encoded size of file is %s", buffer);
	return e_success;
}

Status encode_data_to_image( const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
	char buffer[8];
	for(int i =0;i < size;i++)
	{
		fread(buffer, 8, 1, fptr_src_image);
		encode_byte_to_lsb(data[i], buffer);
		fwrite(buffer, 1, 8, fptr_stego_image);
	}
	return e_success;
	

}
Status encode_byte_to_lsb(char data, char* image_buffer)
{
	for(int i =0;i<8;i++)
		image_buffer[i] = (image_buffer[i] & 0xfe) | ((data & (1<<i)) >> i);


}
Status encode_size_to_lsb(int size, char* image_buffer)
{
	for(int i =0;i<32;i++)
	{
		image_buffer[i] = (image_buffer[i] & 0xfe) |( (size & (1<<i)) >> i);
	}

}
Status encode_secret_file_extn(char* file_extn, EncodeInfo *encInfo)
{
	if(encode_data_to_image(file_extn, strlen(file_extn), encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
		return e_success;
	else
	{
		return e_failure;
	}
}
Status encode_secret_file_size(int file_size, EncodeInfo *encInfo)
{
	char buffer[32];
	fread(buffer, 32, 1, encInfo->fptr_src_image);
	encode_size_to_lsb(file_size, buffer);
	fwrite(buffer, 32, 1, encInfo->fptr_stego_image);
	return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
	fseek(encInfo->fptr_secret, 0, SEEK_SET);
	char buffer[encInfo->size_secret_file];
	fread(buffer, encInfo->size_secret_file, 1, encInfo->fptr_secret);
	if(encode_data_to_image(buffer, encInfo->size_secret_file, encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
	{
	 	return e_success;

	}
	else
		return e_failure;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
	char ch;
	while(fread(&ch,1,1, fptr_src) != 0){
		fwrite(&ch,1,1, fptr_dest);
	}
	return e_success;
}
