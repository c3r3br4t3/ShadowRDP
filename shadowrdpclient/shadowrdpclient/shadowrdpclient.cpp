/******
	Shadow RDP Client
	Original Authors: Athenian & wap2k - Rohitab forums
	Made by	c3r3br4t3
******/

/*THE CLIENT (VIEWER)*/
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <iads.h>
#include <initguid.h>
#include <comutil.h>
#include <combaseapi.h>
#include <objbase.h>
#include <activeds.h>
#include <sddl.h>
#include <comdef.h>
#include <wtsprotocol.h>
#include <stdio.h>
#include <iostream>
#include <rdpappcontainerclient.h>
#include <wtsapi32.h>
#include <rdpencomapi.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlhost.h>
#include <commctrl.h>
#include "gdiplus.h"
#include <gdiplusinit.h>
#include "associated.h"

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

/*GLOBALS*/
#define APP MAKEINTRESOURCE(101)
#define APPSMALL MAKEINTRESOURCE(102)
#define MAX_ATTENDEE 1
#define override

HWND hwnd, hwndConnect, hwndDisconnect, infoLog, scrollbarWindow, view, ACTIVEX_WINDOW, levelList, invitationbox;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK scrollProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CtrlASubProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
const wchar_t* className = L"CLIENT";
static HINSTANCE instance = NULL;

IRDPSRAPIViewer* viewer = NULL;
IRDPSRAPIInvitationManager* invitationManager = NULL;
IRDPSRAPIInvitation* invitation = NULL;
IRDPSRAPIAttendeeManager* attendeeManager = NULL;
IRDPSRAPIAttendee* attendee = NULL;

IConnectionPointContainer* picpc = NULL;
IConnectionPoint* picp = NULL;
int remember = NULL;
SCROLLINFO si;
int vs = 0;

const wchar_t* list[3] = { L"CTRL_NONE", L"CTRL_VIEW", L"CTRL_INTERACTIVE" };

int ConnectEvent(IUnknown* Container, REFIID riid, IUnknown* Advisor, IConnectionPointContainer** picpc, IConnectionPoint** picp)
{
	HRESULT hr = 0;
	unsigned long tid = 0;
	IConnectionPointContainer* icpc = 0;
	IConnectionPoint* icp = 0;
	*picpc = 0;
	*picp = 0;

	Container->QueryInterface(IID_IConnectionPointContainer, (void**)&icpc);
	if (icpc)
	{
		*picpc = icpc;
		icpc->FindConnectionPoint(riid, &icp);
		if (icp)
		{
			*picp = icp;
			hr = icp->Advise(Advisor, &tid);
			//icp->Release();
		}
		//icpc->Release();
	}
	return tid;
}

void DisconnectEvent(IConnectionPointContainer* icpc, IConnectionPoint* icp, unsigned int Cookie)
{
	unsigned long hr = 0;
	icp->Unadvise(Cookie);
	icp->Release();
	icpc->Release();
}

void AddText(HWND edit, LPCWSTR Text)
{
	int len = GetWindowTextLength(edit);
	SendMessageW(edit, EM_SETSEL, (WPARAM)len, (LPARAM)len);
	SendMessageW(edit, EM_REPLACESEL, 0, (LPARAM)Text);
}

/*Event function prototypes*/
void OnConnectionFailed();
void OnConnectionEstablished();

class EventSink : public _IRDPSessionEvents {
public:
	EventSink() {
	}
	~EventSink() {
	}

	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE override QueryInterface(
		REFIID iid, void** ppvObject) {
		*ppvObject = 0;
		if (iid == IID_IUnknown || iid == IID_IDispatch || iid == __uuidof(_IRDPSessionEvents))
			*ppvObject = this;
		if (*ppvObject)
		{
			((IUnknown*)(*ppvObject))->AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	virtual ULONG STDMETHODCALLTYPE override AddRef(void) {
		return 0;
	}

	virtual ULONG STDMETHODCALLTYPE override Release(void) {
		return 0;
	}


	// IDispatch
	virtual HRESULT STDMETHODCALLTYPE override GetTypeInfoCount(
		__RPC__out UINT* pctinfo) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE override GetTypeInfo(
		UINT iTInfo,
		LCID lcid,
		__RPC__deref_out_opt ITypeInfo** ppTInfo) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE override GetIDsOfNames(
		__RPC__in REFIID riid,
		__RPC__in_ecount_full(cNames) LPOLESTR* rgszNames,
		UINT cNames,
		LCID lcid,
		__RPC__out_ecount_full(cNames) DISPID* rgDispId) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE override Invoke(
		DISPID dispIdMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS FAR* pDispParams,
		VARIANT FAR* pVarResult,
		EXCEPINFO FAR* pExcepInfo,
		unsigned int FAR* puArgErr) {

		switch (dispIdMember) {
		case DISPID_RDPSRAPI_EVENT_ON_VIEWER_CONNECTFAILED:
			//OnConnectionFailed();
			OnConnectionEstablished();
			break;
		case DISPID_RDPSRAPI_EVENT_ON_VIEWER_CONNECTED:
			OnConnectionEstablished();
			break;
		}
		return S_OK;
	}
};

EventSink ev;

char* dupcat(const char* s1, ...) {
	int len;
	char* p, * q, * sn;
	va_list ap;

	len = strlen(s1);
	va_start(ap, s1);
	while (1) {
		sn = va_arg(ap, char*);
		if (!sn)
			break;
		len += strlen(sn);
	}
	va_end(ap);

	p = new char[len + 1];
	strcpy(p, s1);
	q = p + strlen(p);

	va_start(ap, s1);
	while (1) {
		sn = va_arg(ap, char*);
		if (!sn)
			break;
		strcpy(q, sn);
		q += strlen(q);
	}
	va_end(ap);

	return p;
}

void GDIPLUS(HDC hdc) {
	Graphics graphics(hdc);
	const wchar_t* text = L"Shadow RDP Client";
	const wchar_t* author = L"Original Author: Athenian & wap2k - Rohitab\r\nMade by: c3r3br4t3";
	const wchar_t* selectLevel = L"Request control level:";
	const wchar_t* shadowtext = L"Shadow invite:";

	FontFamily family(L"Verdana");
	Gdiplus::Font font(&family, 15, FontStyleRegular, UnitPixel);
	
	SolidBrush bBrush(Color(136, 64, 156));
	// Fill the rectangle.
	graphics.FillRectangle(&bBrush, 0, 0, 400, 100);
	
	SolidBrush sbrush(Color::Black);
	graphics.DrawString(text, wcslen(text), &font, PointF(20, 200), &sbrush);
	//graphics.DrawString(selectLevel, wcslen(selectLevel), &font, PointF(15, 107), &sbrush);
	graphics.DrawString(author, wcslen(author), &font, PointF(20, 470), &sbrush);

	SolidBrush wbrush(Color::White);
	graphics.DrawString(shadowtext, wcslen(shadowtext), &font, PointF(20, 5), &wbrush);
}

void COM_INIT() {
	CoInitialize(0);
}
void COM_UNIN() {
	CoUninitialize();
}

bool check_path_file(char* path) {
	FILE* check = fopen(path, "r");
	if (check) {
		//check for size 0
		fseek(check, 0, SEEK_END);
		int size = ftell(check);
		rewind(check);
		if (size > 0) {
			fclose(check);
			return true;
		}
		else {
			fclose(check);
			return false;
		}
	}
	return false;
}

char* selectFile() {
	char* ret = new char[100];
	OPENFILENAMEA name = { 0 };
	ZeroMemory(&name, sizeof(name));
	name.lStructSize = sizeof(name);
	name.hwndOwner = hwnd;
	name.lpstrFile = ret;
	name.lpstrFile[0] = 0;
	name.nMaxFile = sizeof(name);
	name.lpstrFilter = "XML\0*.xml\0";
	name.nFilterIndex = 1;
	name.lpstrFileTitle = 0;
	name.nMaxFileTitle = 0;
	name.lpstrInitialDir = 0;
	name.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileNameA(&name))
		return ret;
	return NULL;
}

bool TRY_CONNECT() {
	if (viewer == NULL) {
		int invitationlength = GetWindowTextLengthW(invitationbox);
		if (invitationlength > 0 && invitationlength < 3200)
		{
			if (CoCreateInstance(__uuidof(RDPViewer),
				NULL, CLSCTX_INPROC_SERVER,
				__uuidof(IRDPSRAPIViewer),
				(void**)&viewer) == S_OK) {
				AddText(infoLog, L"\r\nInstance created!\r\n");
	
				remember = ConnectEvent((IUnknown*)viewer, __uuidof(_IRDPSessionEvents), (IUnknown*)&ev, &picpc, &picp);
	
				AddText(infoLog, L"Reading invitation file!\r\n");
				LPWSTR inviteString = (LPWSTR)malloc((invitationlength + 1) * sizeof(wchar_t));
				if (inviteString)
				{
					GetWindowTextW(invitationbox, inviteString, invitationlength+1);
					wchar_t username[] = L"";
					wchar_t password[] = L"";
					if (viewer->Connect(inviteString, username, password) == S_OK) {
						viewer->put_SmartSizing(true);
						AddText(infoLog, L"Connection line active!\r\n");
						return true;
					}
					else {
						AddText(infoLog, L"\r\nConnection line error!");
						return false;
					}
					free(inviteString);
				}
			}
			else {
				AddText(infoLog, L"\r\nError creating instance!");
				return false;
			}
		}
		else
		{
			AddText(infoLog, L"\r\nError please provide a valid invitation!");
		}
	}
	else {
		AddText(infoLog, L"\r\nError starting: Session already exists!");
		return false;
	}
}

void TRY_DISCONNECT() {
	AddText(infoLog, L"\r\nDisconnecting...");
	if (viewer) {
		DisconnectEvent(picpc, picp, remember);
		viewer->Disconnect();
		viewer->Release();
		viewer = NULL;
		AddText(infoLog, L"\r\nDisconnected!");
	}
	else
	{
		AddText(infoLog, L"\r\nError disconnecting: No active connection!");
	}
	EnableWindow(levelList, false);
}

HWND CreateButton(const wchar_t* lpButtonName, HWND hWnd, int x, int y) {
	return CreateWindowW(L"button", lpButtonName, WS_EX_TRANSPARENT | BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, x, y, 100, 30, hWnd, 0, (HINSTANCE)hWnd, 0);
}

void main() {
	WNDCLASSEXW WndClass;
	MSG Msg;
	instance = GetModuleHandle(NULL);
	HMODULE hInstance = instance;
	AXRegister();
	INITCOMMONCONTROLSEX icex = { 0 };
	InitCommonControls();

	WndClass.cbSize = sizeof(WNDCLASSEXW);
	WndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = instance;
	WndClass.hIcon = LoadIcon(hInstance, APP);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = CreateSolidBrush(RGB(245, 247, 248));
	WndClass.lpszMenuName = 0;
	WndClass.lpszClassName = className;
	WndClass.hIconSm = LoadIcon(hInstance, APPSMALL);

	RegisterClassExW(&WndClass);

	hwnd = CreateWindowExW(
		0,
		className,
		L"SHADOW RDP CLIENT",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1200, 600,
		NULL, NULL,
		instance,
		NULL);

	RECT wInfo;
	GetClientRect(hwnd, &wInfo);

	int Width = wInfo.right;
	int Height = wInfo.bottom;

	//CreateWindowW(L"static", L"Invitation string:", WS_VISIBLE | WS_CHILD, 20, 5, 280, 15, hwnd, NULL, (HINSTANCE)hwnd, NULL);
	invitationbox = CreateWindowW(L"edit", 0, ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 30, 280, 20, hwnd, 0, (HINSTANCE)hwnd, 0);

	hwndConnect = CreateButton(L"Connect", hwnd, 20, 60);
	hwndDisconnect = CreateButton(L"Disconnect", hwnd, 200, 60);
	infoLog = CreateWindowW(L"edit", 0, WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, 20, 250, 350, 200, hwnd, 0, instance, 0);

	view = CreateWindowW(L"edit", 0, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE, 405, 0, Width - 410, Height - 10, hwnd, 0, instance, 0);
	levelList = CreateWindowW(L"combobox", 0, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD /*| WS_VISIBLE*/ , 200, 105, 180, 200, hwnd, 0, instance, 0);
	SetWindowSubclass(invitationbox, CtrlASubProc, 0, 0);
	for (int k = 0; k < 3; k++)
	{
		SendMessageW(levelList, CB_ADDSTRING, 0, (LPARAM)list[k]);
	}

	SendMessageW(levelList, CB_SETCURSEL, 1, 0);
	SendMessageW(levelList, EM_SETREADONLY, 1, 0);
	EnableWindow(levelList, false);

	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);

	SendMessageW(infoLog, EM_SETREADONLY, 1, 0);
	SendMessageW(view, EM_SETREADONLY, 1, 0);
	//SetWindowLongW(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return;

	//return Msg.wParam;
}

void PutStreamOnWindow(HWND hh) {
	// While looking at the calls made I have never seen this create window called it is always returns 0 and is recreated 
	ACTIVEX_WINDOW = CreateWindowExA(0, "AX", "{32be5ed2-5c86-480f-a914-0ff8885a1b3f}", WS_CHILD | WS_VISIBLE, 0, 20, 1, 1, hh, 0, instance, 0);
	if (ACTIVEX_WINDOW) {
		IUnknown* a = 0;
		SendMessageW(ACTIVEX_WINDOW, AX_QUERYINTERFACE, (WPARAM) & __uuidof(IUnknown*), (LPARAM)&a);
	}
	else {
		ACTIVEX_WINDOW = CreateWindowA("AX", "}32BE5ED2-5C86-480F-A914-0FF8885A1B3F}", WS_CHILD | WS_VISIBLE, 0, 0, 1, 1, hh, 0, instance, 0);
		SendMessageW(ACTIVEX_WINDOW, AX_RECREATE, 0, (LPARAM)viewer);
	}

	SendMessageW(ACTIVEX_WINDOW, AX_INPLACE, 1, 0);
	ShowWindow(ACTIVEX_WINDOW, SW_MAXIMIZE);
}

int WindowDiscProc(HWND hwnd, LPARAM lparam)
{
	DestroyWindow(hwnd);
	return 0;
}

int WindowResizeProc(HWND hwnd, LPARAM lparam)
{
	RECT* wInfo = (RECT*)lparam;
	int Width = wInfo->right;
	int Height = wInfo->bottom;
	SetWindowPos(hwnd, NULL, 0, 0, Width - 410, Height - 10, NULL);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	RECT wInfo;
	GetClientRect(hwnd, &wInfo);
	int Width = wInfo.right;
	int Height = wInfo.bottom;

	switch (Message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		COM_INIT();
		GDIPLUS(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT pDIS;
		pDIS = (LPDRAWITEMSTRUCT)lParam;
		WCHAR staticText[256];
		int len = SendMessageW(pDIS->hwndItem, WM_GETTEXT, ARRAYSIZE(staticText), (LPARAM)staticText);
		if (pDIS->hwndItem == infoLog)
			DrawTextW(pDIS->hDC, staticText, wcslen(staticText), &pDIS->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		if (pDIS->hwndItem == hwndConnect || pDIS->hwndItem == hwndDisconnect) {
			SetBkMode(pDIS->hDC, TRANSPARENT);
			FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(136, 64, 156)));
			SetTextColor(pDIS->hDC, RGB(255, 255, 255));
			DrawTextW(pDIS->hDC, staticText, wcslen(staticText), &pDIS->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			SetTextColor(pDIS->hDC, RGB(0, 0, 0));
			SelectObject(pDIS->hDC, GetStockObject(NULL_BRUSH));
			SelectObject(pDIS->hDC, CreatePen(PS_DOT, 1, RGB(255, 255, 255)));

			if (pDIS->itemAction & ODA_SELECT)
				SelectObject(pDIS->hDC, CreatePen(PS_DOT, 1, RGB(255, 255, 255)));
			else
				SelectObject(pDIS->hDC, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));

			Rectangle(
				pDIS->hDC,
				pDIS->rcItem.left,
				pDIS->rcItem.top,
				pDIS->rcItem.right,
				pDIS->rcItem.bottom
			);
		}
	}
	break;
	case WM_COMMAND:
		if ((HWND)lParam == hwndConnect) {
			if (TRY_CONNECT()) {
				PutStreamOnWindow(view);
			}
		}
		if ((HWND)lParam == hwndDisconnect) {
			TRY_DISCONNECT();
			EnumChildWindows(view, WindowDiscProc, NULL);
		}
		if ((HWND)lParam == levelList) {
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int index = SendMessageW(levelList, CB_GETCURSEL, 0, 0);
				switch (index) {
				case 0:
					if (viewer->RequestControl(CTRL_LEVEL_NONE) == S_OK) {
						AddText(infoLog, L"Control set to CTRL_LEVEL_NONE!\r\n");
						ShowWindow(ACTIVEX_WINDOW, SW_HIDE);
					}
					else
						AddText(infoLog, L"Error requesting control level!\r\n");
					break;
				case 1:
					if (viewer->RequestControl(CTRL_LEVEL_VIEW) == S_OK) {
						AddText(infoLog, L"Control set to CTRL_LEVEL_VIEW!\r\n");
						ShowWindow(ACTIVEX_WINDOW, SW_MAXIMIZE);
					}
					else
						AddText(infoLog, L"Error requesting control level!\r\n");
					break;
				case 2:
					if (viewer->RequestControl(CTRL_LEVEL_INTERACTIVE) == S_OK) {
						AddText(infoLog, L"Control set to CTRL_LEVEL_INTERACTIVE!\r\n");
						ShowWindow(ACTIVEX_WINDOW, SW_MAXIMIZE);
					}
					else
						AddText(infoLog, L"Error requesting control level!\r\n");
					break;
				}
			}
		}
		break;
	case WM_CLOSE:
		TRY_DISCONNECT();
		COM_UNIN();
		//To destroy the activex inherent window
		DestroyWindow(view);
		DestroyWindow(hwnd);
		break;
	case WM_SIZE:
		SetWindowPos(view, NULL, 405, 0, Width - 410, Height - 10, NULL);
		EnumChildWindows(view, WindowResizeProc, (LPARAM)&wInfo);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void OnConnectionFailed() {
	AddText(infoLog, L"Connection failed!\r\n   Is the server active?\r\n");
	TRY_DISCONNECT();
}

void OnConnectionEstablished() {
	AddText(infoLog, L"Connection successful! We are live!\r\n");
	EnableWindow(levelList, true);
}

LRESULT CALLBACK CtrlASubProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if (uMsg == WM_DESTROY)
		RemoveWindowSubclass(hWnd, CtrlASubProc, uIdSubclass);
	else if (uMsg == WM_GETDLGCODE && wParam == 'A')
	{
		if (GetKeyState(VK_CONTROL) < 0)
			return DLGC_WANTALLKEYS | DLGC_WANTMESSAGE;
	}
	else if (uMsg == WM_CHAR && wParam == 1) // ctrl-A
	{
		SendMessage(hWnd, EM_SETSEL, 0, -1);
		return 0;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}