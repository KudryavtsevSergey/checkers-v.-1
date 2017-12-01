#include <windows.h> // ������������ ����, ���������� WINAPI
#include "Konstn.h"
#include "resource.h"
#include "zapisi.h"
#include "AIcomp.h"

// �������� ������� ��������� ��������� � ���������������� ���������:
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

// ����������� �������:
int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
	HINSTANCE hPrevInst, // �� ����������
	LPSTR lpCmdLine, // �� ����������
	int nCmdShow) // ����� ����������� ������
{
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_MY50, szWindowClass, MAX_LOADSTRING);
	//	HWND hMainWnd; // ������ ���������� �������� ������
	MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������
	MyRegisterClass(hInst);
	if (!InitInstance(hInst, nCmdShow)) {
		return FALSE;
	}


	while (GetMessage(&msg, NULL, NULL, NULL)) { // ��������� ��������� �� �������, ���������� ��-�����, ��
		TranslateMessage(&msg); // �������������� ���������
		DispatchMessage(&msg); // ������� ��������� ������� ��
	}
	return msg.wParam; // ���������� ��� ������ �� ����������
}


ATOM MyRegisterClass(HINSTANCE hInst) {
	WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
	wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
	wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
	wc.lpszClassName = szWindowClass; // ��������� �� ��� ������
	wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
	wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ��������� �����������
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)); // ���������� ��������� ����������� (� ����)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(253, 253, 200)); // ���������� ����� ��� �������� ���� ����
	wc.hInstance = hInst; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	if (!RegisterClassEx(&wc)) {
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}
	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	HWND hMainWnd;
	// �������, ��������� ������:
	hMainWnd = CreateWindow(szWindowClass, // ��� ������
		szTitle,  // ��� ������ (�� ��� ������)
		WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // ������ ����������� ������
		CW_USEDEFAULT, // ������� ������ �� ��� �
		NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
		visOkna - 42,//    (CW_USEDEFAULT ��� ���������) ������ ������
		visOkna,// ������ ������ (��� ������ � ������, �� ������ �� �����) - NULL
		(HWND)NULL, // ���������� ������������� ����
		NULL, // ���������� ����
		HINSTANCE(hInst), // ���������� ���������� ����������
		NULL); // ������ �� ������� �� WndProc
	if (!hMainWnd) {
		// � ������ ������������� �������� ������ (�������� ��������� � ��):
		MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
		return FALSE;
	}
	ShowWindow(hMainWnd, nCmdShow); // ���������� ������
	UpdateWindow(hMainWnd); // ��������� ������
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC, hDCmem; // ������ ���������� ���������� ������ �� ������
	static HANDLE hFile = NULL;
	PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
	RECT rect; // ���-��, ������������ ������ ���������� �������
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

		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hGame, L"����");
		AppendMenu(hMenubar, MF_POPUP, ID_prog, L"� ���������");

		AppendMenu(hGame, MF_POPUP, (UINT_PTR)hFile, L"�����");
		AppendMenu(hGame, MF_POPUP, ID_save, L"���������");
		AppendMenu(hGame, MF_STRING, ID_load, L"���������");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_cancel, L"��������");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_lose, L"�������");
		AppendMenu(hGame, MF_STRING, ID_exit, L"�����");

		AppendMenu(hFile, MF_STRING, ID_new1, L"���� �����");
		AppendMenu(hFile, MF_STRING, ID_new2, L"��� ������");
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
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
		}
						break;
		case ID_lose: {
			if (movChess == BL) {
				MessageBox(hWnd, L"����� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
			}
			else if (movChess == WH) {
				MessageBox(hWnd, L"׸���� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
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
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
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
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
		}
					  break;
		}
		break;
	case WM_PAINT: // ���� ����� ����������, ��:
		hDC = BeginPaint(hWnd, &ps); // �������������� �������� ����������
		GetWindowRect(hWnd, &rect);
		/* ������� ����������� � ���������� ���� �������� � ������ */
		hDCmem = CreateCompatibleDC(hDC);
		for (signed int i = 0; i < rect.right / 65; i++) {
			for (signed int j = 0; j < rect.bottom / 65; j++) {
				if ((i % 2) ^ (j % 2)) {
					// ������� ��������� ����.
					hPen = CreatePen(PS_SOLID, 0, RGB(129, 88, 47));
					// ������� ��������� �����.
					hBrush = CreateSolidBrush(RGB(129, 88, 47));
					// �������� ����� ���� � �����, � ����� ������.
					SelectObject(hDC, hPen);
					SelectObject(hDC, hBrush);
					Rectangle(hDC, 65 * j, 65 * i, 65 * (j + 1), 65 * (i + 1));
					// �� ��������� �������.
					DeleteObject(hPen);
					DeleteObject(hBrush);
					if (raspChess[i][j].chess) {
						/* ������� ����������� ����������� */
						GetObject(hBitmapNum1, sizeof(BITMAP) / 4, &Bitmap);
						/* ������� ����������� � ���������� ���� �������� � ������ */
						hDCmem = CreateCompatibleDC(hDC);
						/* ������ ����������� ������ ������� � ����������� ��������� */
						/* ������ ��� ��������� ���������� ������ � ������������ �� �������� �������� ���������� � ����������������*/
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
		/* ������� ����������� �������� */
		DeleteDC(hDCmem);
		EndPaint(hWnd, &ps); // ����������� ��������
		break;
	case WM_DESTROY: // ���� ������ ���������, ��:
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���� ������� ������
	}
	return NULL; // ���������� ��������
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
//�������, ����������� ���� �� ����� ����
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
		MessageBox(hWnd, L"����� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	else if ((black) && (!white)) {
		MessageBox(hWnd, L"׸���� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	return TRUE;
}
//�������, ���������� ���� � ����
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