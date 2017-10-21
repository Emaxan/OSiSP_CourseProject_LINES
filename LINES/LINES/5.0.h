#pragma once

#include "resource.h"
#define FILE_PATH _T("data.dat")


HBITMAP hBitmapBKG = (HBITMAP)LoadImage(nullptr, _T("data//BKG.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hBitmapNum1 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS1.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum2 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS2.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum3 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS3.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum4 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS4.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum5 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS5.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum6 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS6.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum7 = (HBITMAP)LoadImage(nullptr, _T("data//BALLS7.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum8 = (HBITMAP)LoadImage(nullptr, _T("data//TIME.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum9 = (HBITMAP)LoadImage(nullptr, _T("data//NEXT.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum10 = (HBITMAP)LoadImage(nullptr, _T("data//DIGITS.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum11 = (HBITMAP)LoadImage(nullptr, _T("data//DIGTR.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum12 = (HBITMAP)LoadImage(nullptr, _T("data//TIMTR.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum13 = (HBITMAP)LoadImage(nullptr, _T("data//NEXTTR.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


TCHAR MY_SOUND_MOVE[] = _T("data//move.wav");
TCHAR MY_SOUND_DESTROY[] = _T("data//destroy.wav");
TCHAR MY_SOUND_FETUS[] = _T("data//fetus.wav");
TCHAR MY_SOUND_CANT_MOVE[] = _T("data//cantmove.wav");
