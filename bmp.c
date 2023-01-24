// Bitmap
// Designer: Deng LiWei
// Date: 2021/03
// Description: A struct for Windows Bitmap image file

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "bmp.h"

static void NewBitmap(Bitmap** pBitmap, int width, int height, const char* fileName)
{
    Bitmap* bitmap = (Bitmap*)malloc(sizeof(bitmap));

    bitmap->fileName = (char*)malloc(strlen(fileName));
    strcpy(bitmap->fileName, fileName);
    
    bitmap->head = (BitmapHead*)malloc(sizeof(BitmapHead));
    bitmap->image = NewImageMat(width, height);

    bitmap->head->biClrImportant = 0;
    bitmap->head->biClrUsed = 0;
    bitmap->head->biCompression = 0x00;
    bitmap->head->biHeight = height;
    bitmap->head->biPlanes = 1;
    bitmap->head->biSize = 40;
    bitmap->head->biSizeImage = width * height * sizeof(uint32_t);
    bitmap->head->biWidth = width;
    bitmap->head->biXPelsPerMeter = 0;
    bitmap->head->biYPelsPerMeter = 0;

    *pBitmap = bitmap;
}

void NewBitmap32bpp(Bitmap** pBitmap, int width, int height, const char* fileName)
{
    NewBitmap(pBitmap, width, height, fileName);
    (*pBitmap)->head->biBitCount = 32;
}

void NewBitmap24bpp(Bitmap** pBitmap, int width, int height, const char* fileName)
{
    NewBitmap(pBitmap, width, height, fileName);
    (*pBitmap)->head->biBitCount = 24;
}

void DestoryBitmap(Bitmap* bitmap)
{
    if (bitmap != NULL)
    {
        if (bitmap->image != NULL)
        {
            DestoryImageMat(bitmap->image);
        }
        
        if (bitmap->head != NULL)
        {
            free(bitmap->head);
        }

        free(bitmap);
    }
}

