#include <stdio.h>
#include <stdlib.h>
#define BSIZE 512 // Defines a macro

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s image\n", argv[0]);
        return 1;
    }
    // Open the image for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s for reading\n", argv[1]);
        return 1;
    }
    // Initialize variables
    unsigned char buffer[BSIZE];
    int file_count = 0;
    FILE *jpeg = NULL;
    // Read the forensic image block by block
    while (fread(buffer, BSIZE, 1, file) == 1)
    {
        // Check if the block starts a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous file
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            // Create a new file, filename of the form ###.jpg
            char filename[8];
            sprintf(filename, "%03d.jpg", file_count);
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                fprintf(stderr, "Could not create %s\n", filename);
                fclose(file);
                return 1;
            }
            // Increment the file counter
            file_count++;
        }
        // Write the block to the current file
        if (jpeg != NULL)
        {
            fwrite(buffer, BSIZE, 1, jpeg);
        }
    }
    // Close the last file
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    // Close the image file
    fclose(file);
    return 0;
}