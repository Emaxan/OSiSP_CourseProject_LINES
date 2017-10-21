#include "stdafx.h"
#include "5.0.h"
#include "PathFinder.h"
#include <commctrl.h>
#include <mmsystem.h>
#include <ctime>

#define MAX_LOADSTRING 100
#define TEMER_TIME 2

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HIMAGELIST himl, himl2, himl3, himl4;
DWORD T1, T2;
TIME my_time = {0};
int startX, startY;
POINT fetus[3];
BOOL START = FALSE;
int SCORE = 0, COUNT_BUBBLES = 0;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


void Paint(HDC hdc, HDC hdcMem)
{
    BITMAP bm;
    HDC hDC = CreateCompatibleDC(hdc);
    SelectObject(hDC, (HBITMAP)hBitmapBKG);
    GetObject(hBitmapBKG, sizeof(bm), &bm);
    BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0,SRCCOPY);
    if (START)
        for (int i = 0; i < 3; i++)
        {
            ImageList_Draw(himl3,LOWORD(walkability[fetus[i].x][fetus[i].y]) / 22
                           , hdcMem, 163 + i * 25, 5,ILD_TRANSPARENT);
        }
    int mul = 10000;
    for (int i = 0; i < 5; i++)
    {
        ImageList_Draw(himl4, (SCORE / mul) % 10, hdcMem, 290 + i * 20, 8,ILD_TRANSPARENT);
        mul /= 10;
    }


    ImageList_Draw(himl2, my_time.hour / 10, hdcMem, 174, 34,ILD_TRANSPARENT);
    ImageList_Draw(himl2, my_time.hour % 10, hdcMem, 183, 34,ILD_TRANSPARENT);

    ImageList_Draw(himl2, my_time.min / 10, hdcMem, 193, 34,ILD_TRANSPARENT);
    ImageList_Draw(himl2, my_time.min % 10, hdcMem, 202, 34,ILD_TRANSPARENT);

    ImageList_Draw(himl2, my_time.sec / 10, hdcMem, 212, 34,ILD_TRANSPARENT);
    ImageList_Draw(himl2, my_time.sec % 10, hdcMem, 220, 34,ILD_TRANSPARENT);


    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (walkability[i][j])
                ImageList_Draw(himl,LOWORD(walkability[i][j]) + HIWORD(walkability[i][j]) - 1, hdcMem, 45 * i + 5, 45 * j + 56,ILD_NORMAL);
    DeleteDC(hDC);
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR lpCmdLine,
                       int nCmdShow)
{
    MSG msg;

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_MY50, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY50));

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_MY50),
                                  IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);

    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY50);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_MY50),
                                    IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, 0, 416, 512, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void CreateBubbles(HWND hWnd)
{
    int x, y;

    srand((unsigned)time(nullptr));
    if (!START)
        for (int i = 0; i < 5; i++)
        {
            do
            {
                x = rand() % 9;
                y = rand() % 9;
            }
            while (walkability[x][y]);
            walkability[x][y] = (rand() % 7) * 22 + 1;
            COUNT_BUBBLES++;
        }
    else
        for (int i = 0; i < 3; i++)
            walkability[fetus[i].x][fetus[i].y] &= zero;
    for (int i = 0; i < 3; i++)
    {
        do
        {
            x = rand() % 9;
            y = rand() % 9;
        }
        while (walkability[x][y]);
        fetus[i].x = x;
        fetus[i].y = y;
        walkability[x][y] = walkability_fetus;
        walkability[x][y] += (rand() % 7) * 22 + 1;
        COUNT_BUBBLES++;


        if (COUNT_BUBBLES == mapWidth * mapHeight)
        {
            COUNT_BUBBLES = 0;
            PlaySound(MY_SOUND_CANT_MOVE, nullptr, SND_FILENAME | SND_ASYNC);
            START = FALSE;
            if (MessageBox(nullptr, _T("GAME OVER"),_T(""),MB_OK))
            PostMessage(hWnd,WM_COMMAND,ID_GAME_NEW, 0);
            break;
        }
        PlaySound(MY_SOUND_FETUS, nullptr, SND_FILENAME | SND_ASYNC);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    static HANDLE hFile = nullptr;
    static int x, y;
    static BITMAP bm;
    static bool ANIMATE_RUN = false;

    DWORD NumberOfBytesRead;
    static HDC hdc;
    static HDC hdcMem;
    static HBITMAP hBmpFrame;
    static int COUNT_RUN = 0;
    static int COUNT_FETUS = 0;
    static int COUNT_DESTROY = 0;
    static int LENGTH_DESTROY = 0;
    static POINT* PatchDestroy;
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (HIWORD(lParam) <= 56 || COUNT_RUN || COUNT_FETUS || COUNT_DESTROY || !START)
            break;
        if (ANIMATE_RUN)
            walkability[x][y] &= zero;
        startX = x;
        startY = y;

        x = (LOWORD(lParam) - 5) / 45;
        y = (HIWORD(lParam) - 56) / 45;
        if (HIWORD(walkability[x][y]) ^ HIWORD(walkability_fetus) && walkability[x][y])
        {
            ANIMATE_RUN = true;
            PlaySound(MY_SOUND_MOVE, nullptr, SND_FILENAME | SND_ASYNC);
        }
        else if (ANIMATE_RUN)
        {
            ANIMATE_RUN = false;
            path = FindPath(startX, startY, x, y);
            if (path == found)
                COUNT_RUN = pathLength;
        }
        break;
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_FILE_32771: //save
            walkability[x][y] &= zero;
            hFile = CreateFile(FILE_PATH, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS,
                                        FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile)
            {
                WriteFile(hFile, walkability, sizeof(walkability), &NumberOfBytesRead, nullptr);
                WriteFile(hFile, &SCORE, sizeof(int), &NumberOfBytesRead, nullptr);
                WriteFile(hFile, &my_time, sizeof(TIME), &NumberOfBytesRead, nullptr);

                CloseHandle(hFile);
            }
            else
            MessageBox(hWnd,_T("Невозможно открыть файл"),_T("Ошибка"), MB_ICONWARNING | MB_OK);

            break;


        case ID_FILE_32772: //load
            ANIMATE_RUN = false;
            hFile = CreateFile(FILE_PATH,GENERIC_READ,FILE_SHARE_READ, nullptr,OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile)
            {
                ReadFile(hFile, walkability, sizeof(walkability), &NumberOfBytesRead, nullptr);
                ReadFile(hFile, &SCORE, sizeof(int), &NumberOfBytesRead, nullptr);
                ReadFile(hFile, &my_time, sizeof(TIME), &NumberOfBytesRead, nullptr);
                CloseHandle(hFile);
                COUNT_BUBBLES = 0;
                int k = 0;
                for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                        if (walkability[i][j])
                        {
                            COUNT_BUBBLES++;
                            if (!(HIWORD(walkability[i][j]) ^ HIWORD(walkability_fetus)))
                            {
                                fetus[k].x = i;
                                fetus[k++].y = j;
                            }
                        }
                START = TRUE;
                T1 = GetTickCount() - (my_time.hour * 3600 + my_time.min * 60 + my_time.sec) * 1000;
            }
            else
            MessageBox(hWnd,_T("Невозможно открыть файл"),_T("Ошибка"), MB_ICONWARNING | MB_OK);

            break;

        case ID_GAME_NEW: //new
            ANIMATE_RUN = false;
            START = FALSE;
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    walkability[i][j] = 0;
            COUNT_BUBBLES = 0;
            SCORE = 0;
            CreateBubbles(hWnd);
            START = TRUE;

            T1 = GetTickCount();
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_CREATE:

        himl = ImageList_Create(40, 40,ILC_COLOR24, 154, 0);
        himl2 = ImageList_Create(7, 13,ILC_COLOR32 | ILC_MASK, 10, 0);
        himl3 = ImageList_Create(25, 25,ILC_COLOR24 | ILC_MASK, 7, 0);
        himl4 = ImageList_Create(18, 35,ILC_COLOR32 | ILC_MASK, 10, 0);
        ImageList_Add(himl, hBitmapNum1, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum2, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum3, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum4, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum5, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum6, (HBITMAP)nullptr);
        ImageList_Add(himl, hBitmapNum7, (HBITMAP)nullptr);
        ImageList_Add(himl2, hBitmapNum8, hBitmapNum12);
        ImageList_Add(himl3, hBitmapNum9, hBitmapNum13);
        ImageList_Add(himl4, hBitmapNum10, hBitmapNum11);
        SetTimer(hWnd,TEMER_TIME, 100, nullptr);
        hdc = GetDC(hWnd);
        hdcMem = CreateCompatibleDC(hdc);
        GetObject(hBitmapBKG, sizeof(bm), &bm);

        hBmpFrame = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
        SelectObject(hdcMem, (HBITMAP)hBmpFrame);
        break;
    case WM_ERASEBKGND:
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case TEMER_TIME:
            if (START)
            {
                T2 = GetTickCount();
                my_time.hour = (T2 - T1) / (1000 * 3600);
                my_time.min = (T2 - T1) / (1000 * 60) - my_time.hour * 60;
                my_time.sec = (T2 - T1) / 1000 - my_time.hour * 3600 - my_time.min * 60;
            }
            if (ANIMATE_RUN)
                walkability[x][y] = ((((walkability[x][y] >> 16) + 1) % 7) << 16) + (walkability[x][y] & 0x0000ffff);

            if (COUNT_FETUS)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (!(HIWORD(walkability[fetus[i].x][fetus[i].y])))
                    {
                        do
                        {
                            x = rand() % 9;
                            y = rand() % 9;
                        }
                        while (walkability[x][y]);
                        walkability[x][y] = walkability_fetus;
                        walkability[x][y] += (rand() % 7) * 22 + 1;
                        fetus[i].x = x;
                        fetus[i].y = y;
                    }
                    walkability[fetus[i].x][fetus[i].y] = ((((walkability[fetus[i].x][fetus[i].y] >> 16) - 1)) << 16) +
                        (walkability[fetus[i].x][fetus[i].y] & zero);
                }
                COUNT_FETUS--;

                if (!COUNT_FETUS)
                    CreateBubbles(hWnd);
            }

            if (COUNT_DESTROY)
            {
                for (int i = 0; i < LENGTH_DESTROY; i++)
                    walkability[PatchDestroy[i].x][PatchDestroy[i].y] = ((17 - COUNT_DESTROY) << 16) +
                        (walkability[PatchDestroy[i].x][PatchDestroy[i].y] & 0x0000ffff);
                COUNT_DESTROY--;
                if (!COUNT_DESTROY)
                {
                    for (int i = 0; i < LENGTH_DESTROY; i++)
                        walkability[PatchDestroy[i].x][PatchDestroy[i].y] = 0;
                    dest_len(PatchDestroy);
                    SCORE += LENGTH_DESTROY;
                }
            }


            if (COUNT_RUN)
            {
                if (COUNT_RUN == pathLength)
                {
                    if (!walkability[pathBank[0].x][pathBank[0].y] ||
                        !(HIWORD(walkability[x][y]) ^ HIWORD(walkability_fetus)))
                    {
                        walkability[pathBank[0].x][pathBank[0].y] =
                            walkability[startX][startY] & zero;
                    }
                    else
                    {
                        walkability[pathBank[1].x][pathBank[1].y] =
                            walkability[startX][startY] & zero;
                        COUNT_RUN--;
                    }
                    walkability[startX][startY] = 0;
                }
                else
                {
                    if (!walkability[pathBank[pathLength - COUNT_RUN].x][pathBank[pathLength - COUNT_RUN].y] ||
                        !(HIWORD(walkability[x][y]) ^ HIWORD(walkability_fetus)))
                    {
                        walkability[pathBank[pathLength - COUNT_RUN].x][pathBank[pathLength - COUNT_RUN].y] =
                            walkability[pathBank[pathLength - COUNT_RUN - 1].x][pathBank[pathLength - COUNT_RUN - 1].y];
                        walkability[pathBank[pathLength - COUNT_RUN - 1].x][pathBank[pathLength - COUNT_RUN - 1].y] = 0;
                    }
                    else
                    {
                        walkability[pathBank[pathLength - COUNT_RUN + 1].x][pathBank[pathLength - COUNT_RUN + 1].y] =
                            walkability[pathBank[pathLength - COUNT_RUN - 1].x][pathBank[pathLength - COUNT_RUN - 1].y];
                        walkability[pathBank[pathLength - COUNT_RUN - 1].x][pathBank[pathLength - COUNT_RUN - 1].y] = 0;
                        COUNT_RUN--;
                    }
                }
                COUNT_RUN--;
                if (COUNT_RUN <= 0)
                {
                    if (PatchDestroy = len(x, y, LENGTH_DESTROY))
                    {
                        COUNT_DESTROY = 10;
                        COUNT_BUBBLES -= LENGTH_DESTROY;
                        PlaySound(MY_SOUND_DESTROY, nullptr, SND_FILENAME | SND_ASYNC);
                    }
                    COUNT_FETUS = 4;
                    path = 0;

                    EndPathfinder();
                }
            }
            break;
        }
        Paint(hdc, hdcMem);
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        break;

    case WM_DESTROY:
        ImageList_Destroy(himl);
        ImageList_Destroy(himl2);
        ImageList_Destroy(himl3);
        ImageList_Destroy(himl4);
        ReleaseDC(hWnd, hdc);
        DeleteDC(hdcMem);
        KillTimer(hWnd,TEMER_TIME);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
