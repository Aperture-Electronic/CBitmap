// Bitmap file reader
// Designer: Deng LiWei
// Date: 2021/03
// Description: A writer for Windows Bitmap image file
#pragma once
#include <stdint.h>

#include "bmp.h"

typedef enum
{
    BMPW_ERR_OK,
    BMPW_ERR_NULL_POINTER,
    BMPW_ERR_FILE
}BitmapWriteError;

BitmapWriteError WriteBitmap(Bitmap* bitmap, const char* fileName);


