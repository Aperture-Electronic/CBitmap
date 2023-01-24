// Bitmap file reader
// Designer: Deng LiWei
// Date: 2021/03
// Description: A reader for Windows Bitmap image file
#pragma once
#include <stdint.h>

#include "bmp.h"

typedef enum
{
    BMPR_ERR_OK,
    BMPR_ERR_FILE,
    BMPR_ERR_FILE_FORMAT,
    BMPR_ERR_BPP_FORMAT,
    BMPR_ERR_BMP_COMPRESSED
}BitmapReadError;

BitmapReadError ReadBitmap(const char* fileName, Bitmap** bitmap);

