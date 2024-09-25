/*
 * Kevin Nguyen
 * A00955925
 */

#include "../include/process.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int         opt;
    int         fdin;
    int         fdout;
    ssize_t     bytes_read;
    char        buffer;
    char        output;
    const char *input_file     = NULL;
    const char *output_file    = NULL;
    const char *filter_opt     = NULL;
    const char *OUTPUT_DEFAULT = "output.txt";
    char (*filter_func)(char)  = NULL;

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
                filter_opt = optarg;
                if(strcmp(optarg, "upper") == 0)
                {
                    filter_func = upper_filter;
                }
                else if(strcmp(optarg, "lower") == 0)
                {
                    filter_func = lower_filter;
                }
                else if(strcmp(optarg, "null") == 0)
                {
                    filter_func = null_filter;
                }
                else
                {
                    fprintf(stderr, "Unknown filter: %s\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-i input_file] [-o output_file] [-f filter]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    // Check for unexpected arguments
    if(optind < argc)
    {
        fprintf(stderr, "Error: Unexpected arguments\n");
        fprintf(stderr, "Usage: %s [-i input_file] [-o output_file] [-f filter]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Check for input file
    if(input_file == NULL)
    {
        fprintf(stderr, "Error: input file is required\n");
        fprintf(stderr, "Usage: %s [-i input_file] [-o output_file] [-f filter]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Reading from file %s\n", input_file);

    // Default filter
    if(filter_opt == NULL)
    {
        printf("No filter specified, applying null filter\n");
        filter_func = null_filter;
    }
    else
    {
        printf("Applying %s filter\n", filter_opt);
    }

    // Default output file
    if(output_file == NULL)
    {
        printf("No output file specified, writing result to file %s\n", OUTPUT_DEFAULT);
    }
    else
    {
        printf("Writing result to file %s\n", output_file);
    }

    // ----- Opening Files -----
    fdin = open(input_file, O_RDONLY | O_CLOEXEC);
    if(fdin == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    // Check for null flag and create output file.
    fdout = (output_file == NULL) ? open(OUTPUT_DEFAULT, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IWUSR) : open(output_file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IWUSR);
    if(fdout == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    // ----- Processing Data -----
    while((bytes_read = read(fdin, &buffer, 1)) > 0)
    {
        output = process(buffer, filter_func);
        if(write(fdout, &output, 1) != 1)
        {
            perror("write");
            close(fdin);
            close(fdout);
            exit(EXIT_FAILURE);
        }
    }
    if(bytes_read == -1)
    {
        perror("read");
    }

    // ----- Closing Files -----
    if(close(fdin) == -1 || close(fdout) == -1)
    {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
