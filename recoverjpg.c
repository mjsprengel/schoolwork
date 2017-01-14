/**
 *  This code will read in raw bits from a damaged file, look for the file signature of a jpeg image, 
 *  and if it detects a jpeg file format, will start reading in the file and outputting the jpeg image to
 *  the current directory, creating a new jpeg image if it runs into another file signature
 *  All .jpeg files start with 0xff, 0xd8, 0xff
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(void)
{
    uint8_t buf[512];
    int picture = 0;
    char title[10];
    
    FILE* inptr = fopen("card.raw", "r");
    
    if (inptr == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    while(fread(&buf, sizeof(buf), 1, inptr) == 1)
    {
        if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && ((buf[3] & 0xf0) == 0xe0)) // if jpeg sig detected
        {
            if(picture<10)
                sprintf(title, "00%i.jpg", picture);
            else if (picture>=10)
                sprintf(title, "0%i.jpg", picture);
            
            FILE* outptr = fopen(title, "w");
            
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", title);
                return 2;
            }
            
            fwrite(&buf, sizeof(buf), 1, outptr);
            
            // read and write all of the bytes in the current jpeg until the next jpeg sig is detected
            while(fread(&buf, sizeof(buf), 1, inptr) == 1 && !(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && ((buf[3] & 0xf0) == 0xe0)))
            { 
                fwrite(&buf, sizeof(buf), 1, outptr);
            }
            
            fclose(outptr);
            picture++;
            fseek(inptr, -512, SEEK_CUR);
        }
    }
    
    fclose(inptr);
    return 0;
}
