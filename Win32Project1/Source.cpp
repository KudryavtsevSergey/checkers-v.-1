#include <windows.h> // заголовочный файл, содержащий WINAPI
#include "Konstn.h"
#include "resource.h"
#include "zapisi.h"
#include "AIcomp.h"

// Прототип функции обработки сообщений с пользовательским названием:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);
BOOL myprover(HWND hWnd, clChess::myChessStruct raspChess[8][8]);
BOOL START, gameWithComp;
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
void mySaveGame(HWND hWnd, HANDLE hFile);
void myLoadGame(HWND hWnd, HANDLE hFile);
HINSTANCE hInst;
clChess cl;
aiComp II;
int movChess;
aiComp::myList iznSost;
clChess::myChessStruct raspChess[8][8];

// Управляющая функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
	HINSTANCE hPrevInst, // не используем
	LPSTR lpCmdLine, // не используем
	int nCmdShow) // режим отображения окошка
{
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_MY50, szWindowClass, MAX_LOADSTRING);
	//	HWND hMainWnd; // создаём дескриптор будущего окошка
	MSG msg; // создём экземпляр структуры MSG для обработки сообщений
	MyRegisterClass(hInst);
	if (!InitInstance(hInst, nCmdShow)) {
		return FALSE;
	}


	while (GetMessage(&msg, NULL, NULL, NULL)) { // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
		TranslateMessage(&msg); // интерпретируем сообщения
		DispatchMessage(&msg); // передаём сообщения обратно ОС
	}
	return msg.wParam; // возвращаем код выхода из приложения
}


ATOM MyRegisterClass(HINSTANCE hInst) {
	WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
	wc.cbSize = sizeof(wc); // размер структуры (в байтах)
	wc.style = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
	wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
	wc.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
	wc.lpszClassName = szWindowClass; // указатель на имя класса
	wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
	wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // декриптор пиктограммы
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)); // дескриптор маленькой пиктограммы (в трэе)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(253, 253, 200)); // дескриптор кисти для закраски фона окна
	wc.hInstance = hInst; // указатель на строку, содержащую имя меню, применяемого для класса
	if (!RegisterClassEx(&wc)) {
		// в случае отсутствия регистрации класса:
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}
	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	HWND hMainWnd;
	// Функция, создающая окошко:
	hMainWnd = CreateWindow(szWindowClass, // имя класса
		szTitle,  // имя окошка (то что сверху)
		WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // режимы отображения окошка
		CW_USEDEFAULT, // позиция окошка по оси х
		NULL, // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
		visOkna - 42,//    (CW_USEDEFAULT для автоматич) ширина окошка
		visOkna,// высота окошка (раз дефолт в ширине, то писать не нужно) - NULL
		(HWND)NULL, // дескриптор родительского окна
		NULL, // дескриптор меню
		HINSTANCE(hInst), // дескриптор экземпляра приложения
		NULL); // ничего не передаём из WndProc
	if (!hMainWnd) {
		// в случае некорректного создания окошка (неверные параметры и тп):
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return FALSE;
	}
	ShowWindow(hMainWnd, nCmdShow); // отображаем окошко
	UpdateWindow(hMainWnd); // обновляем окошко
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC, hDCmem; // создаём дескриптор ориентации текста на экране
	static HANDLE hFile = NULL;
	PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
	RECT rect; // стр-ра, определяющая размер клиентской области
	HPEN hPen;
	HBRUSH hBrush;
	HANDLE hOldBitmap;
	HBITMAP Bitmap;
	static int i, j, k;
	switch (uMsg) {
	case WM_CREATE: {
		HMENU hMenubar = CreateMenu();
		HMENU hFile = CreateMenu();
		HMENU hGame = CreateMenu();

		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hGame, L"Игра");
		AppendMenu(hMenubar, MF_POPUP, ID_prog, L"О программе");

		AppendMenu(hGame, MF_POPUP, (UINT_PTR)hFile, L"Новая");
		AppendMenu(hGame, MF_POPUP, ID_save, L"Сохранить");
		AppendMenu(hGame, MF_STRING, ID_load, L"Загрузить");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_cancel, L"Отменить");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_lose, L"Сдаться");
		AppendMenu(hGame, MF_STRING, ID_exit, L"Выход");

		AppendMenu(hFile, MF_STRING, ID_new1, L"Один игрок");
		AppendMenu(hFile, MF_STRING, ID_new2, L"Два игрока");
		SetMenu(hWnd, hMenubar);
	}
					break;
	case WM_LBUTTONDOWN: {
		cl.y = LOWORD(lParam) / 65;
		cl.x = HIWORD(lParam) / 65;
		if (!START) {
			if (cl.isCheckStrike(raspChess)) {
				if (raspChess[cl.x][cl.y].necesStrike) {
					raspChess[cl.x][cl.y].shine = TRUE;
					cl.nShashka = raspChess[cl.x][cl.y];
					cl.xG = cl.x;
					cl.yG = cl.y;
					START = TRUE;
					rect.left = 65 * cl.y;
					rect.top = 65 * cl.x;
					rect.right = 65 * (cl.y + 1);
					rect.bottom = 65 * (cl.x + 1);
					InvalidateRect(hWnd, &rect, FALSE);
				}
			}
			else if (cl.isSelect(raspChess)) {
				raspChess[cl.x][cl.y].shine = TRUE;
				cl.nShashka = raspChess[cl.x][cl.y];
				cl.xG = cl.x;
				cl.yG = cl.y;
				START = TRUE;
				rect.left = 65 * cl.y;
				rect.top = 65 * cl.x;
				rect.right = 65 * (cl.y + 1);
				rect.bottom = 65 * (cl.x + 1);
				InvalidateRect(hWnd, &rect, FALSE);
			}
		}
		else {
			cl.y = LOWORD(lParam) / 65;
			cl.x = HIWORD(lParam) / 65;
			if (cl.x < 8 && cl.y < 8 && ((cl.y % 2) ^ (cl.x % 2))) {
				if (raspChess[cl.x][cl.y].chess) {
					if (cl.isCheckStrike(raspChess)) {
						if (raspChess[cl.x][cl.y].necesStrike) {
							raspChess[cl.xG][cl.yG].shine = FALSE;
							rect.left = 65 * cl.yG;
							rect.top = 65 * cl.xG;
							rect.right = 65 * (cl.yG + 1);
							rect.bottom = 65 * (cl.xG + 1);
							InvalidateRect(hWnd, &rect, FALSE);

							raspChess[cl.x][cl.y].shine = TRUE;
							cl.nShashka = raspChess[cl.x][cl.y];
							cl.xG = cl.x;
							cl.yG = cl.y;
							rect.left = 65 * cl.y;
							rect.top = 65 * cl.x;
							rect.right = 65 * (cl.y + 1);
							rect.bottom = 65 * (cl.x + 1);
							InvalidateRect(hWnd, &rect, FALSE);
						}
					}
					else if (cl.isSelectOne(raspChess)) {
						raspChess[cl.xG][cl.yG].shine = FALSE;
						rect.left = 65 * cl.yG;
						rect.top = 65 * cl.xG;
						rect.right = 65 * (cl.yG + 1);
						rect.bottom = 65 * (cl.xG + 1);
						InvalidateRect(hWnd, &rect, FALSE);

						raspChess[cl.x][cl.y].shine = TRUE;
						cl.nShashka = raspChess[cl.x][cl.y];
						cl.xG = cl.x;
						cl.yG = cl.y;
						rect.left = 65 * cl.y;
						rect.top = 65 * cl.x;
						rect.right = 65 * (cl.y + 1);
						rect.bottom = 65 * (cl.x + 1);
						InvalidateRect(hWnd, &rect, FALSE);
					}
				}
				else {
					hFile = CreateFile(FILE_FOR_CANCEL, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL, NULL);
					if (hFile) {
						mySaveGame(hWnd, hFile);
					}
					if (raspChess[cl.xG][cl.yG].queen) {
						cl.downing = FALSE;
						if (cl.isStrikeQueen(raspChess)) {
							k = abs(cl.x - cl.xG);
							for (signed int i = 0; i < k; i++) {
								raspChess[cl.xG + i*cl.xG1][cl.yG + i*cl.yG1].chess = FALSE;
								raspChess[cl.xG + i*cl.xG1][cl.yG + i*cl.yG1].shine = FALSE;
								raspChess[cl.xG + i*cl.xG1][cl.yG + i*cl.yG1].queen = FALSE;
								raspChess[cl.xG + i*cl.xG1][cl.yG + i*cl.yG1].color = 2;
								rect.left = 65 * (cl.yG + i*cl.yG1);
								rect.top = 65 * (cl.xG + i*cl.xG1);
								rect.right = 65 * (cl.yG + i*cl.yG1 + 1);
								rect.bottom = 65 * (cl.xG + i*cl.xG1 + 1);
								InvalidateRect(hWnd, &rect, FALSE);
							}
							if (cl.isDoubleStrikeQueen(raspChess)) {
								START = FALSE;
								raspChess[cl.x][cl.y].shine = FALSE;
								movChess = !movChess;
								cl.downing = FALSE;
							}
							else {
								cl.nShashka = raspChess[cl.x][cl.y];
								cl.xG = cl.x;
								cl.yG = cl.y;
							}
							rect.left = 65 * cl.y;
							rect.top = 65 * cl.x;
							rect.right = 65 * (cl.y + 1);
							rect.bottom = 65 * (cl.x + 1);
							InvalidateRect(hWnd, &rect, FALSE);
						}
					}
					else {
						if (cl.isStrikeChess(raspChess)) {
							cl.downing = FALSE;
							cl.xG1 = (cl.x - cl.xG) / abs(cl.x - cl.xG);
							cl.yG1 = (cl.y - cl.yG) / abs(cl.y - cl.yG);

							rect.left = 65 * cl.yG;
							rect.top = 65 * cl.xG;
							rect.right = 65 * (cl.yG + 1);
							rect.bottom = 65 * (cl.xG + 1);
							InvalidateRect(hWnd, &rect, FALSE);
							if ((cl.x - 2 * cl.xG1 == cl.xG) && (cl.y - 2 * cl.yG1 == cl.yG)) {
								raspChess[cl.x - cl.xG1][cl.y - cl.yG1].chess = FALSE;
								raspChess[cl.x - cl.xG1][cl.y - cl.yG1].shine = FALSE;
								raspChess[cl.x - cl.xG1][cl.y - cl.yG1].queen = FALSE;
								raspChess[cl.x - cl.xG1][cl.y - cl.yG1].color = 2;
								cl.downing = TRUE;
								rect.left = 65 * (cl.y - cl.yG1);
								rect.top = 65 * (cl.x - cl.xG1);
								rect.right = 65 * (cl.y - cl.yG1 + 1);
								rect.bottom = 65 * (cl.x - cl.xG1 + 1);
								InvalidateRect(hWnd, &rect, FALSE);
							}
							if (raspChess[cl.x][cl.y].queen) {
								if (cl.isDoubleStrikeQueen(raspChess)) {
									START = FALSE;
									raspChess[cl.x][cl.y].shine = FALSE;
									movChess = !movChess;
									cl.downing = FALSE;
								}
								else {
									cl.nShashka = raspChess[cl.x][cl.y];
									cl.xG = cl.x;
									cl.yG = cl.y;
								}
							}
							else {
								if (cl.isDoubleStrikeChess(raspChess)) {
									START = FALSE;
									raspChess[cl.x][cl.y].shine = FALSE;
									movChess = !movChess;
									cl.downing = FALSE;
								}
								else {
									cl.nShashka = raspChess[cl.x][cl.y];
									cl.xG = cl.x;
									cl.yG = cl.y;
								}
							}
							rect.left = 65 * cl.y;
							rect.top = 65 * cl.x;
							rect.right = 65 * (cl.y + 1);
							rect.bottom = 65 * (cl.x + 1);
							InvalidateRect(hWnd, &rect, FALSE);
						}
					}
				}
			}
		}
		if (myprover(hWnd, raspChess)) {
			if (gameWithComp && !START && (movChess == BL)) {
				II.Initial(&iznSost);
				iznSost = *II.podborHodov(&iznSost, raspChess, movChess, 5);
				II.maxSum = -1000;
				II.poiskHoda(&iznSost, raspChess, 0, TRUE);
				movChess = !movChess;
				rect.left = 0;
				rect.top = 0;
				rect.right = 520;
				rect.bottom = 520;
				InvalidateRect(hWnd, &rect, FALSE);
				II.Del(&iznSost);
			}
			myprover(hWnd, raspChess);
		}
	}
						 break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_prog:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
			break;
		case ID_cancel: {
			hFile = CreateFile(FILE_FOR_CANCEL, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				myLoadGame(hWnd, hFile);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if ((i % 2) ^ (j % 2)) {
							rect.left = 65 * (j);
							rect.top = 65 * (i);
							rect.right = 65 * (j + 1);
							rect.bottom = 65 * (i + 1);
							InvalidateRect(hWnd, &rect, FALSE);
						}
					}
				}
			}
			else
				MessageBox(hWnd, L"Невозможно открыть файл", L"Ошибка", MB_ICONWARNING | MB_OK);
		}
						break;
		case ID_lose: {
			if (movChess == BL) {
				MessageBox(hWnd, L"Белые выиграли.", L"Конец игры.", MB_ICONASTERISK | MB_OK);
			}
			else if (movChess == WH) {
				MessageBox(hWnd, L"Чёрные выиграли.", L"Конец игры.", MB_ICONASTERISK | MB_OK);
			}
			for (size_t i = 0; i < 8; i++) {
				for (size_t j = 0; j < 8; j++) {
					if ((i % 2) ^ (j % 2)) {
						raspChess[i][j].chess = FALSE;
						raspChess[i][j].queen = FALSE;
						raspChess[i][j].shine = FALSE;
						raspChess[i][j].color = 2;
						rect.left = 65 * (j);
						rect.top = 65 * (i);
						rect.right = 65 * (j + 1);
						rect.bottom = 65 * (i + 1);
						InvalidateRect(hWnd, &rect, FALSE);
					}
				}
			}
		}
					  break;
		case ID_exit:
			DestroyWindow(hWnd);
			break;
		case ID_new1: {
			for (size_t i = 0; i < 8; i++) {
				for (size_t j = 0; j < 8; j++) {
					if ((i % 2) ^ (j % 2)) {
						if (i < 3) {
							raspChess[i][j].chess = TRUE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = BL;
						}
						else if ((i >= 3) && (i <= 4)) {
							raspChess[i][j].chess = FALSE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = 2;
						}
						else if (i > 4) {
							raspChess[i][j].chess = TRUE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = WH;
						}
						rect.left = 65 * (j);
						rect.top = 65 * (i);
						rect.right = 65 * (j + 1);
						rect.bottom = 65 * (i + 1);
						InvalidateRect(hWnd, &rect, FALSE);
					}
				}
			}
			START = FALSE;
			gameWithComp = TRUE;
			movChess = 0;
		}
					  break;
		case ID_new2: {
			for (size_t i = 0; i < 8; i++) {
				for (size_t j = 0; j < 8; j++) {
					if ((i % 2) ^ (j % 2)) {
						if (i < 3) {
							raspChess[i][j].chess = TRUE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = BL;
						}
						else if ((i >= 3) && (i <= 4)) {
							raspChess[i][j].chess = FALSE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = 2;
						}
						else if (i > 4) {
							raspChess[i][j].chess = TRUE;
							raspChess[i][j].queen = FALSE;
							raspChess[i][j].shine = FALSE;
							raspChess[i][j].color = WH;
						}
						rect.left = 65 * (j);
						rect.top = 65 * (i);
						rect.right = 65 * (j + 1);
						rect.bottom = 65 * (i + 1);
						InvalidateRect(hWnd, &rect, FALSE);
					}
				}
			}
			START = FALSE;
			gameWithComp = FALSE;
			movChess = 0;
		}
					  break;
		case ID_save: {
			hFile = CreateFile(FILE_PATH, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				mySaveGame(hWnd, hFile);
			}
			else
				MessageBox(hWnd, L"Невозможно открыть файл", L"Ошибка", MB_ICONWARNING | MB_OK);
		}
					  break;
		case ID_load: {
			hFile = CreateFile(FILE_PATH, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				myLoadGame(hWnd, hFile);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if ((i % 2) ^ (j % 2)) {
							rect.left = 65 * (j);
							rect.top = 65 * (i);
							rect.right = 65 * (j + 1);
							rect.bottom = 65 * (i + 1);
							InvalidateRect(hWnd, &rect, FALSE);
						}
					}
				}
			}
			else
				MessageBox(hWnd, L"Невозможно открыть файл", L"Ошибка", MB_ICONWARNING | MB_OK);
		}
					  break;
		}
		break;
	case WM_PAINT: // если нужно нарисовать, то:
		hDC = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
		GetWindowRect(hWnd, &rect);
		/* создать совместимый с контекстом окна контекст в памяти */
		hDCmem = CreateCompatibleDC(hDC);
		for (signed int i = 0; i < rect.right / 65; i++) {
			for (signed int j = 0; j < rect.bottom / 65; j++) {
				if ((i % 2) ^ (j % 2)) {
					// Создаем оранжевое перо.
					hPen = CreatePen(PS_SOLID, 0, RGB(129, 88, 47));
					// Создаем оранжевую кисть.
					hBrush = CreateSolidBrush(RGB(129, 88, 47));
					// Выбираем новое перо и кисть, а затем рисуем.
					SelectObject(hDC, hPen);
					SelectObject(hDC, hBrush);
					Rectangle(hDC, 65 * j, 65 * i, 65 * (j + 1), 65 * (i + 1));
					// Не забывайте очищать.
					DeleteObject(hPen);
					DeleteObject(hBrush);
					if (raspChess[i][j].chess) {
						/* получть размерность изображения */
						GetObject(hBitmapNum1, sizeof(BITMAP) / 4, &Bitmap);
						/* создать совместимый с контекстом окна контекст в памяти */
						hDCmem = CreateCompatibleDC(hDC);
						/* делаем загруженный битмап текущим в совместимом контексте */
						/* версия без прокрутки копировать битмап с совместимого на основной контекст устройства с масштабированием*/
						if (raspChess[i][j].shine) {
							hOldBitmap = SelectObject(hDCmem, hBitmapNum2);
						}
						else {
							hOldBitmap = SelectObject(hDCmem, hBitmapNum1);
						}

						if (raspChess[i][j].color == WH) {
							if (raspChess[i][j].queen == TRUE) {
								StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 195, 0, 65, 65, SRCCOPY);
							}
							else {
								StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 130, 0, 65, 65, SRCCOPY);
							}
						}
						else if (raspChess[i][j].color == BL) {
							if (raspChess[i][j].queen == TRUE) {
								StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 65, 0, 65, 65, SRCCOPY);
							}
							else {
								StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 0, 0, 65, 65, SRCCOPY);
							}
						}
						DeleteDC(hDCmem);
					}
				}
			}
		}
		/* удалить совместимый контекст */
		DeleteDC(hDCmem);
		EndPaint(hWnd, &ps); // заканчиваем рисовать
		break;
	case WM_DESTROY: // если окошко закрылось, то:
		PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
	}
	return NULL; // возвращаем значение
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//Функция, проверяющая игру на конец игры
BOOL myprover(HWND hWnd, clChess::myChessStruct raspChess[8][8]) {
	BOOL black = FALSE, white = FALSE;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if (raspChess[i][j].chess) {
				if (raspChess[i][j].color == BL) {
					black = TRUE;
				}
				else if (raspChess[i][j].color == WH) {
					white = TRUE;
				}
			}
		}
	}
	if ((!black) && (white)) {
		MessageBox(hWnd, L"Белые выиграли.", L"Конец игры.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	else if ((black) && (!white)) {
		MessageBox(hWnd, L"Чёрные выиграли.", L"Конец игры.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	return TRUE;
}
//Функция, сохранящая игру в файл
void mySaveGame(HWND hWnd, HANDLE hFile) {
	DWORD NumberOfBytesRead;
	WriteFile(hFile, raspChess, sizeof(raspChess), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.nShashka, sizeof(clChess::myChessStruct), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.xG, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.yG, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &movChess, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &START, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &gameWithComp, sizeof(BOOL), &NumberOfBytesRead, NULL);
	CloseHandle(hFile);
}

void myLoadGame(HWND hWnd, HANDLE hFile) {
	DWORD NumberOfBytesRead;
	ReadFile(hFile, raspChess, sizeof(raspChess), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.nShashka, sizeof(clChess::myChessStruct), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.xG, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.yG, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &movChess, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &START, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &gameWithComp, sizeof(BOOL), &NumberOfBytesRead, NULL);
	CloseHandle(hFile);
}