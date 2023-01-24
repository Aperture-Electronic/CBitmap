// Bitmap
// Designer: Deng LiWei
// Date: 2021/03
// Description: A struct for Windows Bitmap image file
#pragma once
#include <stdint.h>
#include "../image/image_mat.h"

#define DEFAULT_BMP_HEADER 19778
#define DEFAULT_BMP_HEAD_LEN 14

typedef struct 
{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}BitmapHead;

typedef struct 
{
    char* fileName;
    BitmapHead *head;
    ImageMat *image;
}Bitmap;

void NewBitmap32bpp(Bitmap** pBitmap, int width, int height, const char* fileName);
void NewBitmap24bpp(Bitmap** pBitmap, int width, int height, const char* fileName);
void DestoryBitmap(Bitmap* bitmap);
