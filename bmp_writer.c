// Bitmap file reader
// Designer: Deng LiWei
// Date: 2021/03
// Description: A writer for Windows Bitmap image file

#include "bmp_writer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>

BitmapWriteError WriteBitmap(Bitmap* bitmap, const char* fileName)
{
    if (bitmap == NULL)
    {
        return BMPW_ERR_NULL_POINTER;
    }

    char* fName;
    if (strcmp(fileName, "") == 0)
    {
        fName = bitmap->fileName;
    }
    else
    {
        fName = (char*)malloc(strlen(fileName));
        strcpy(fName, fileName);
    }

    // Create binary bitmap file
    FILE *fpBitmap;

    fpBitmap = fopen(fName, "wb+");

    if (fpBitmap == NULL)
    {
        // Error when open a file to write
        return BMPW_ERR_FILE;
    }

    // Write the bitmap head
    uint8_t *headBuffer = (uint8_t*)malloc(54);
    uint32_t p32;
    uint16_t p16;
    p16 = DEFAULT_BMP_HEADER;
    memcpy(headBuffer + 0, &p16, 2);    // Identify
    p32 = bitmap->head->biSizeImage + 54;
    memcpy(headBuffer + 2, &p32, 4);    // Size of file
    p32 = 0;
    memcpy(headBuffer + 6, &p32, 4);    // Reserved
    p32 = 54;
    memcpy(headBuffer + 10, &p32, 4);   // Data offset
    memcpy(headBuffer + 14, bitmap->head, 40); // Information head
    fwrite(headBuffer, 54, 1, fpBitmap);

    // Write bitmap data
    for (int y = bitmap->image->height - 1; y >= 0; y--)
    {
        fwrite(bitmap->image->pData + y * bitmap->image->width * 4, 4, bitmap->image->width, fpBitmap);
    }    

    // Close to write the bitmap
    fclose(fpBitmap);

    return BMPW_ERR_OK;
}
