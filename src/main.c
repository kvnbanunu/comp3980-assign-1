#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int         opt;
    const char *input_file  = NULL;
    const char *output_file = NULL;
    const char *filter      = NULL;

    while((opt = getopt(argc, argv, "i:o:f:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'f':
                filter = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -f input_file [-o output_file] [-v]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Check for unexpected arguments
    if(optind < argc)
    {
        fprintf(stderr, "Error: Unexpected arguments\n");
        fprintf(stderr, "Usage: %s -f input_file [-o output_file] [-v]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Check for required arguments
    if(input_file == NULL)
    {
        fprintf(stderr, "Error: Input file is required\n");
        fprintf(stderr, "Usage: %s -f input_file [-o output_file] [-v]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Reading from file %s\n", input_file);

    // Default filter
    if(filter == NULL)
    {
        printf("No filter specified, filter set to null\n");
    }
    else
    {
        printf("Applying %s filter\n", filter);
    }

    // Default output file
    if(output_file == NULL)
    {
        printf("No output file specified, output file set to output.txt\n");
    }
    else
    {
        printf("Writing result to file %s\n", output_file);
    }

    return EXIT_SUCCESS;
}
