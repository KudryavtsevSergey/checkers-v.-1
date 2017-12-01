#define ID_prog		1
#define ID_cancel	2
#define ID_lose		3
#define ID_exit		4
#define ID_new1		5
#define ID_new2		6
#define ID_save		7
#define ID_load		8

#define BL 1
#define WH 0

const int visOkna = 578;
HBITMAP hBitmapNum1 = (HBITMAP) LoadImage (NULL, L"data//checkers1.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum2 = (HBITMAP) LoadImage (NULL, L"data//checkers2.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hBitmapNum3 = (HBITMAP) LoadImage (NULL, L"data//checkers3.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#define FILE_PATH L"data//data.dat"
#define FILE_FOR_CANCEL L"data//dataForCancel.dat"


#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name