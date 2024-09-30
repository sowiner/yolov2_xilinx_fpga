#include <stdio.h>
#include <stdlib.h>

void bin_to_c_array(const char *bin_filename, const char *c_filename, const char *array_name)
{
    FILE *bin_file = fopen(bin_filename, "rb");
    if (!bin_file)
    {
        perror("Cannot open binary file");
        exit(EXIT_FAILURE);
    }

    // Get the size of the binary file
    fseek(bin_file, 0, SEEK_END);
    long file_size = ftell(bin_file);
    fseek(bin_file, 0, SEEK_SET);

    // Read the binary file into a buffer
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer)
    {
        perror("Memory allocation failed");
        fclose(bin_file);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, file_size, bin_file);
    fclose(bin_file);

    // Open the C file for writing
    FILE *c_file = fopen(c_filename, "w");
    if (!c_file)
    {
        perror("Cannot open C file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    // Write the array declaration
    fprintf(c_file, "unsigned char %s[%ld] = {", array_name, file_size);
    for (long i = 0; i < file_size; ++i)
    {
        if (i % 12 == 0)
        {
            fprintf(c_file, "\n    ");
        }
        fprintf(c_file, "0x%02X", buffer[i]);
        if (i < file_size - 1)
        {
            fprintf(c_file, ", ");
        }
    }
    fprintf(c_file, "\n};\n");

    // Clean up
    free(buffer);
    fclose(c_file);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <binary file> <C file> <array name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    bin_to_c_array(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}