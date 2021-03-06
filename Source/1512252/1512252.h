#pragma once

#include "resource.h"
#include <windowsx.h>
#include <Commdlg.h>
#include <CommCtrl.h>
#include <vector>
#include <fstream>
#include <locale>
#include <codecvt>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
struct ChiTieu
{
	WCHAR* Loai;
	WCHAR* Noidung;
	WCHAR* Sotien;
	ChiTieu(WCHAR* s1, WCHAR* s2, WCHAR* s3)
	{
		Loai = _wcsdup(s1);
		Noidung = _wcsdup(s2);
		Sotien = _wcsdup(s3);
	}
};
struct TiLe
{
	int tongtien;
	COLORREF color;
};
vector <ChiTieu*> list;
TiLe listTiLe[6] = { {0,0x3232ff}, {0, 0xff9c32}, {0,0x32ff4a}, {0,0x215ece}, {0,0xce21cc}, {0,0x4de3d3} };
HWND groupbox1, groupbox2, groupbox3;
HWND labelLoai, labelNoidung, labelSotien, labelTongcong, labelTiLe, labelList[6];
HWND comboBox, txtNoidung, txtSotien, txtTongcong, lvDanhSach, txtList[6];
HWND btnThem, btnThoat, btnXoa;
int sum = 0, dem = 0;
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hWnd);
void ListView_Insert(ChiTieu *s);
void AddNew();
void Draw(HDC hdc, int x, int y, DWORD r, float start, float sweep, int brush);
void UpdatePercent();
double Pround(double x, int precision);

