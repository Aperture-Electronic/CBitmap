// Bitmap file reader
// Designer: Deng LiWei
// Date: 2021/03
// Description: A reader for Windows Bitmap image file
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>

#include "../image/image_mat.h"
#include "bmp_reader.h"

static BitmapHead* ReadBitmapInfoHead(FILE* file);

BitmapReadError ReadBitmap(const char* fileName, Bitmap** pBitmap)
{
    // Open the bitmap file using 
    // binary reading mode
    FILE *fpBitmap;

    fpBitmap = fopen(fileName, "rb");

    if (fpBitmap == NULL)
    {
        // Error when open the file
        return BMPR_ERR_FILE;
    }

    // Check the bitmap head
    uint16_t bitmapIdentify;
    uint32_t bitmapFileSize;
    uint32_t bitmapDataOffset;

    fread(&bitmapIdentify, sizeof(uint16_t), 1, fpBitmap);

    if (bitmapIdentify != DEFAULT_BMP_HEADER)
    {
        // Error, the bitmap identify field is not "BM"
        return BMPR_ERR_FILE_FORMAT;
    }

    fread(&bitmapFileSize, sizeof(uint32_t), 1, fpBitmap);
    fseek(fpBitmap, 4, SEEK_CUR);
    fread(&bitmapDataOffset, sizeof(uint32_t), 1, fpBitmap);

    BitmapHead* head = ReadBitmapInfoHead(fpBitmap);

    // We do not want to decode 8bpp or 16bpp images,
    // compatible format is 24bpp or 32bpp, no compression
    if ((head->biBitCount != 24) && (head->biBitCount != 32))
    {
        return BMPR_ERR_BPP_FORMAT;
    }

    if (head->biCompression != 0x00) // 0x00: BI_RGB, no compression
    {
        return BMPR_ERR_BMP_COMPRESSED;
    }

    // All conditions are matched, create the bitmap object
    Bitmap* bitmap = (Bitmap*)malloc(sizeof(Bitmap));
    *pBitmap = bitmap;
    bitmap->head = head;

    // Create the image matrix object
    bitmap->image = NewImageMat(head->biWidth, head->biHeight);

    // Seek to the start of image
    fseek(fpBitmap, bitmapDataOffset, SEEK_SET);

    // Read the data from last line of image (Normal BMP mode)

    for (int y = head->biHeight - 1; y >= 0; y--)
    {
        if (head->biBitCount == 32) // 32 bpp (BGRA)
        {          
            uint32_t addrOffset = (y * head->biWidth) * sizeof(uint32_t);
            fread(bitmap->image->pData + addrOffset, sizeof(uint32_t), head->biWidth, fpBitmap);
        }
        else // 24 bpp (BGR, A = 0xFF)
        {
            // Create the line buffer
            uint8_t *lineBuffer = (uint8_t*)malloc(head->biWidth * 3);
            int bufferOffset = 0;

            // Read a line to line buffer
            fread(lineBuffer, 3, head->biWidth, fpBitmap);

            for (int x = 0; x < head->biWidth; x++, bufferOffset += 3)
            {
                memcpy(bitmap->image->pData + ((y * head->biWidth + x) << 2), lineBuffer + bufferOffset, 3);
                *(uint8_t *)(bitmap->image->pData + ((y * head->biWidth + x) << 2) + 3) = 0xFF; // Set alpha
            }

            // Dispose the line buffer
            free(lineBuffer);
        }
    }

    fclose(fpBitmap);

    return BMPR_ERR_OK;    
}

static BitmapHead* ReadBitmapInfoHead(FILE* fpBitmap)
{
    // Create the new head information struct
    BitmapHead* head = (BitmapHead*)malloc(sizeof(BitmapHead));

    // Seek to the infomation head
    fseek(fpBitmap, 14, SEEK_SET);

    // Read fields
    fread(head, 40, 1, fpBitmap);

    // Return
    return head;
}
