// 1512252.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512252.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1512252, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512252));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512252));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1512252);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Quản lý chi tiêu", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 880, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			int i = 0;
			int y = 450;
			DWORD radius = 100;
			int nX = 200, nY = 550;
			for (; i < 6; i++)
			{
				Draw(hdc, 470, y, 30, 0.0, 45.0, listTiLe[i].color);
				y += 40;
			}
			i = 0;
			while (i < 6)
			{
				if (listTiLe[i].tongtien != 0)
					break;
				i++;
			}
			if (i == 6)
				Draw(hdc, nX, nY, radius, 0, 360, 0xb2b2b2);
			else
			{
				float startpos = 0;
				for (int j = 0; j < 6; j++)
				{
					Draw(hdc, nX, nY, radius, startpos, ((float)listTiLe[j].tongtien / sum) * 360.0, listTiLe[j].color);
					startpos += ((float)listTiLe[j].tongtien / sum) * 360.0;
				}
			}

			ReleaseDC(hWnd, hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Microsoft Sans Serif");
	groupbox1 = CreateWindow(L"Button", L"Thêm một loại chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		30, 10, 900, 100, hwnd, 0, hInst, 0);
	groupbox2 = CreateWindow(L"Button", L"Toàn bộ danh sách các chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		30, 120, 900, 230, hwnd, 0, hInst, 0);
	groupbox3 = CreateWindow(L"Button", L"Thông tin thống kê", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		30, 370, 900, 430, hwnd, 0, hInst, 0);
	labelLoai = CreateWindow(L"STATIC", L"Loại chi tiêu:", WS_CHILD | WS_VISIBLE | SS_LEFT, 60, 40, 80, 40, hwnd,
		NULL, hInst, NULL);
	labelNoidung = CreateWindow(L"STATIC", L"Nội dung:", WS_CHILD | WS_VISIBLE | SS_LEFT, 320, 40, 80, 40, hwnd,
		NULL, hInst, NULL);
	labelSotien = CreateWindow(L"STATIC", L"Số tiền:", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 40, 80, 40, hwnd,
		NULL, hInst, NULL);
	labelTongcong = CreateWindow(L"STATIC", L"Tổng cộng:", WS_CHILD | WS_VISIBLE | SS_LEFT, 440, 700, 80, 40, hwnd,
		NULL, hInst, NULL);
	labelTiLe = CreateWindow(L"STATIC", L"Tỉ lệ (%):", WS_CHILD | WS_VISIBLE | SS_LEFT, 700, 400, 80, 40, hwnd,
		NULL, hInst, NULL);
	comboBox = CreateWindow(WC_COMBOBOX, L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | CBS_SORT,
		60, 60, 150, 60, hwnd, NULL, hInst, NULL);
	WCHAR* text[6] = { L"Ăn uống", L"Di chuyển", L"Nhà cửa", L"Xe cộ", L"Nhu yếu phẩm", L"Dịch vụ" };
	int y = 440;
	for (int i = 0; i < 6; i++)
	{
		SendMessage(comboBox, CB_ADDSTRING, 0, (LPARAM)text[i]);
		labelList[i] = CreateWindow(L"STATIC", text[i], WS_CHILD | WS_VISIBLE | SS_LEFT, 520, y, 100, 40, hwnd,
			NULL, hInst, NULL);
		txtList[i] = CreateWindow(L"EDIT", L"0.000", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT | ES_READONLY,
			700, y - 5, 55, 25, hwnd, NULL, hInst, NULL);
		y += 40;
		SendMessage(labelList[i], WM_SETFONT, WPARAM(hFont), TRUE);
		SendMessage(txtList[i], WM_SETFONT, WPARAM(hFont), TRUE);
	}
	SendMessage(comboBox, CB_SETCURSEL, 0, (LPARAM) text[0]);
	txtNoidung = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		320, 60, 130, 25, hwnd, NULL, hInst, NULL);
	txtSotien = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
		580, 60, 150, 25, hwnd, NULL, hInst, NULL);
	txtTongcong = CreateWindow(L"EDIT", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY | ES_RIGHT,
		530, 695, 150, 25, hwnd, NULL, hInst, NULL);
	lvDanhSach = CreateWindow(WC_LISTVIEWW, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
		60, 150, 850, 150, hwnd, NULL, hInst, NULL);
	ListView_SetExtendedListViewStyle(lvDanhSach, LVS_EX_FULLROWSELECT | LVS_EX_COLUMNSNAPPOINTS);
	LVCOLUMN lvCol1, lvCol2, lvCol3, lvCol4;

	lvCol1.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_MINWIDTH;
	lvCol2.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_MINWIDTH;
	lvCol3.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_MINWIDTH;
	lvCol4.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_MINWIDTH;

	lvCol1.fmt = LVCFMT_LEFT;
	lvCol1.cx = 80;
	lvCol1.cxMin = 50;
	lvCol1.pszText = L"STT";
	ListView_InsertColumn(lvDanhSach, 0, &lvCol1);

	lvCol2.fmt = LVCFMT_LEFT;
	lvCol2.cx = 200;
	lvCol2.cxMin = 150;
	lvCol2.pszText = L"Loại chi tiêu";
	ListView_InsertColumn(lvDanhSach, 1, &lvCol2);

	lvCol3.fmt = LVCFMT_LEFT;
	lvCol3.cx = 300;
	lvCol3.cxMin = 200;
	lvCol3.pszText = L"Nội dung";
	ListView_InsertColumn(lvDanhSach, 2, &lvCol3);

	lvCol4.pszText = L"Số tiền";
	lvCol4.fmt = LVCFMT_LEFT;
	lvCol4.cx = 150;
	lvCol4.cxMin = 80;
	ListView_InsertColumn(lvDanhSach, 3, &lvCol4);

	btnThem = CreateWindow(L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 55, 80, 30, hwnd,
		(HMENU)ID_BTNADD, hInst, NULL);
	btnThoat = CreateWindow(L"BUTTON", L"Thoát", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 480, 760, 80, 30, hwnd,
		(HMENU)ID_BTNEXIT, hInst, NULL);
	btnXoa = CreateWindow(L"BUTTON", L"Xóa", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 310, 80, 30, hwnd,
		(HMENU)ID_BTNXOA, hInst, NULL);
	SendMessage(groupbox1, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(groupbox2, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(groupbox3, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(labelLoai, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(labelNoidung, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(labelSotien, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(labelTongcong, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(labelTiLe, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(comboBox, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(txtNoidung, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(txtSotien, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(txtTongcong, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(lvDanhSach, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(btnThem, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(btnThoat, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(btnXoa, WM_SETFONT, WPARAM(hFont), TRUE);
	const int BUFFERSIZE = 10240;
	WCHAR buffer[BUFFERSIZE];
	GetCurrentDirectory(BUFFERSIZE, buffer);
	lstrcatW(buffer, L"\\data.txt");
	wfstream wf;
	wf.open(buffer, ios::in | ios::binary);
	if (wf)
	{
		wf.imbue(locale(wf.getloc(), new codecvt_utf16<WCHAR, 0x10ffff, codecvt_mode(little_endian)>));
		wf.seekg(0, ios::end);
		int size = wf.tellg() / 2;
		wf.seekg(0, ios::beg);
		WCHAR *buff = new WCHAR[size];
		wf.read(buff, size);
		buff[size] = 0;
		WCHAR *temp;
		WCHAR *line = wcstok_s(buff, L"\r\n", &temp);
		WCHAR *loai, *noidung, *sotien;
		while (line)
		{
			loai = wcstok_s(NULL, L"\t", &line);
			noidung = wcstok_s(NULL, L"\t", &line);
			sotien = wcstok_s(NULL, L"\t", &line);
			ChiTieu *s = new ChiTieu(loai, noidung, sotien);
			list.push_back(s);
			ListView_Insert(s);
			line = wcstok_s(NULL, L"\r\n", &temp);
		}
		WCHAR tongtien[20];
		_itow_s(sum, tongtien, 10);
		SetWindowText(txtTongcong, tongtien);
		UpdatePercent();
		InvalidateRect(hwnd, NULL, TRUE);
	}
	wf.close();
	return TRUE;
}
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// Parse the menu selections:
	switch (id)
	{
	case ID_BTNADD:
		AddNew();
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_BTNEXIT:
		DestroyWindow(hWnd);
		break;
	case ID_BTNXOA:
	{
		int iPos = ListView_GetNextItem(lvDanhSach, -1, LVNI_SELECTED);
		if (iPos == -1)
			MessageBox(0, L"Vui lòng chọn 1 loại chi tiêu để xóa", L"Lỗi", 0);
		else
		{
			ListView_DeleteItem(lvDanhSach, iPos);
			ChiTieu *s = list[iPos];
			int num = _wtoi(s->Sotien);
			int pos;
			if (lstrcmpW(s->Loai, L"﻿Ăn uống") == 0)
				pos = 0;
			else
				if (lstrcmpW(s->Loai, L"Di chuyển") == 0)
					pos = 1;
				else
					if (lstrcmpW(s->Loai, L"Nhà cửa") == 0)
						pos = 2;
					else
						if (lstrcmpW(s->Loai, L"Xe cộ") == 0)
							pos = 3;
						else
							if (lstrcmpW(s->Loai, L"Nhu yếu phẩm") == 0)
								pos = 4;
							else
								if (lstrcmpW(s->Loai, L"Dịch vụ") == 0)
									pos = 5;
			listTiLe[pos].tongtien -= num;
			sum -= num;
			dem--;
			WCHAR tongtien[20];
			_itow_s(sum, tongtien, 10);
			SetWindowText(txtTongcong, tongtien);
			WCHAR number[10];
			for (int i = 0; i < dem; i++)
			{
				_itow_s(i + 1, number, 10);
				ListView_SetItemText(lvDanhSach, i, 0, number);
			}
			UpdatePercent();
			delete list[iPos];
			list[iPos] = NULL;
			list.erase(list.begin() + iPos);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	}
}
void OnDestroy(HWND hWnd)
{

	const int BUFFERSIZE = 10240;
	WCHAR buffer[BUFFERSIZE];
	GetCurrentDirectory(BUFFERSIZE, buffer);
	lstrcatW(buffer, L"\\data.txt");
	wfstream wf;
	wf.open(buffer, ios::out | ios::binary);
	locale loc(locale(), new codecvt_utf16<WCHAR, 0x10ffff, codecvt_mode(little_endian)>);
	wf.imbue(loc);
	if (!list.empty())
	{
		wf << list[0]->Loai << L"\t" << list[0]->Noidung << L"\t" << list[0]->Sotien;
		for (int i = 1; i < list.size(); i++)
			wf << L"\r\n" << list[i]->Loai << L"\t" << list[i]->Noidung << L"\t" << list[i]->Sotien;
	}
	wf.close();
	PostQuitMessage(0);
}
void ListView_Insert(ChiTieu *s)
{
	WCHAR number[10];
	_itow_s(dem + 1, number, 10);
	LVITEM lv;
	lv.mask = LVIF_TEXT | LVIF_PARAM;
	lv.iItem = dem;
	lv.iSubItem = 0;
	lv.pszText = number;
	ListView_InsertItem(lvDanhSach, &lv);
	ListView_SetItemText(lvDanhSach, dem, 1, s->Loai);
	ListView_SetItemText(lvDanhSach, dem, 2, s->Noidung);
	ListView_SetItemText(lvDanhSach, dem, 3, s->Sotien);
	int add = _wtoi(s->Sotien);
	int pos;
	if (lstrcmpW(s->Loai, L"﻿Ăn uống") == 0)
		pos = 0;
	else
		if (lstrcmpW(s->Loai, L"Di chuyển") == 0)
			pos = 1;
		else
			if (lstrcmpW(s->Loai, L"Nhà cửa") == 0)
				pos = 2;
			else
				if (lstrcmpW(s->Loai, L"Xe cộ") == 0)
					pos = 3;
				else
					if (lstrcmpW(s->Loai, L"Nhu yếu phẩm") == 0)
						pos = 4;
					else
						if (lstrcmpW(s->Loai, L"Dịch vụ") == 0)
							pos = 5;
	listTiLe[pos].tongtien += add;
	sum += add;

	dem++;
}
void AddNew()
{
	int size1 = GetWindowTextLength(comboBox) + 1, size2 = GetWindowTextLength(txtNoidung) + 1, size3 = GetWindowTextLength(txtSotien) + 1;
	if (size1 <= 1)
	{
		MessageBox(0, L"Vui lòng chọn loại chi tiêu", L"Lỗi", 0);
		return;
	}
	if (size2 <= 1)
	{
		MessageBox(0, L"Vui lòng nhập nội dung", L"Lỗi", 0);
		return;
	}
	if (size3 <= 1)
	{
		MessageBox(0, L"Vui lòng nhập số tiền", L"Lỗi", 0);
		return;
	}
	WCHAR* buffer1 = new WCHAR[size1];
	WCHAR* buffer2 = new WCHAR[size2];
	WCHAR* buffer3 = new WCHAR[size3];
	GetWindowText(comboBox, buffer1, size1);
	GetWindowText(txtNoidung, buffer2, size2);
	GetWindowText(txtSotien, buffer3, size3);
	ChiTieu *s = new ChiTieu(buffer1, buffer2, buffer3);
	list.push_back(s);
	ListView_Insert(s);
	SetWindowText(txtNoidung, L"");
	SetWindowText(txtSotien, L"");
	WCHAR tongtien[20];
	_itow_s(sum, tongtien, 10);
	SetWindowText(txtTongcong, tongtien);
	UpdatePercent();
}
void Draw(HDC hdc, int x, int y, DWORD r, float start, float sweep, int brush)
{
	SetDCBrushColor(hdc, brush);
	BeginPath(hdc);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	MoveToEx(hdc, x, y, (LPPOINT)NULL);
	AngleArc(hdc, x, y, r, start, sweep);
	LineTo(hdc, x, y);
	EndPath(hdc);
	StrokeAndFillPath(hdc);
}
void UpdatePercent()
{
	if (sum == 0)
	{
		for (int i = 0; i < 6; i++)
			SetWindowTextW(txtList[i], L"0.000");
		return;
	}
	double percent;
	wstring rate;
	WCHAR ratechar[7];
	for (int i = 0; i < 6; i++)
	{
		percent = (double)listTiLe[i].tongtien / sum * 100.0;
		percent = Pround(percent, 4);
		if (percent == 100.0)
			lstrcpy(ratechar, L"100.00");
		else
		{
			rate = to_wstring(percent);
			for (int j = 0; j < 5; j++)
				ratechar[j] = rate[j];
			ratechar[5] = 0;
		}
		SetWindowTextW(txtList[i], ratechar);
	}
}
double Pround(double x, int precision)
{
	if (x == 0.0)
		return x;
	int ex = floor(log10(abs(x))) - precision + 1;
	double div = pow(10, ex);
	return floor(x / div + 0.5) * div;
}