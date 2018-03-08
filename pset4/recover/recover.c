/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    unsigned char buffer[512];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int jpeg_count = 0;
    int jpeg_found = 0;
    FILE* outptr;
    char outfile[8];

    while (fread(buffer, 512, 1, inptr)) { //read 512 bytes until eof
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0
            )
        {
            if (jpeg_found == 1){
                fclose(outptr);
            } else {
                jpeg_found = 1;
            }

            sprintf(outfile, "%03d.jpg", jpeg_count);
            outptr = fopen(outfile, "a");
            jpeg_count ++;
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 3;
            }
        }
        if (jpeg_found == 1)
        {
            // write 512 bytes to file once we start finding jpgs
            fwrite(&buffer, 512, 1, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
