#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "decode.h"
#include <string.h>

int main(int argc,char*  argv[])
{ 
    if(argc < 2)
	{
		printf("Encoding:./a.out -e <.bmp file> <.txt file> [output file]\n");
		printf("Decoding:./a.out -d <.bmp file> [output file]\n");
		return e_failure;
	}
	int ret = check_operation_type(argv[1]);
    if(ret == e_encode )
    {
    	printf("Encoding is selected\n");
		EncodeInfo encInfo;
		if(read_and_validate_encode_args(argv, &encInfo)== e_success)
		{
			printf("## Encoding Procedure Started ##\n");
			printf("Read and validate arguments for encoding success\n");
			if(do_encoding(&encInfo) == e_success)
			{
				printf("## Encoding Done Successfully ##\n");
				return e_success;
			}
			else
			{
				printf("## Encoding failure ##\n"); 
				return e_failure;
			}
		}
		else
		{
			printf("Encoding:./a.out -e <.bmp file> <.txt file> [output file]\n");
			return e_failure;
		}
    }
    else if(ret == e_decode)
    {
    	DecodeInfo decInfo;
		if(read_and_validate_decode_args(argv, &decInfo) == e_success)
		{
			printf("## Decoding Procedure Started ##\n");
			printf("Read and validate arguments for decoding success\n");
			if(do_decoding(&decInfo) == e_success)
			{
				printf("## Decoding Done Successfully ##\n");
			}
			else
			{
				printf("## Decoding secret data failure ##\n");
			}
		}
		else
		{
			printf("Decoding:/a.out -d <.bmp file> [output file]\n");
		}
		
    }
    else
    {
    	printf("Invalid operation\n");
		return e_failure;
    }

    return 0;
}

OperationType check_operation_type(char argv[])
{
	if(strcmp(argv, "-e") == 0)
	{
		return e_encode;
	}
	else if(strcmp(argv, "-d") == 0 )
	{
		return e_decode;
	
	}
	else
	{
		return e_unsupported;
	}


}
