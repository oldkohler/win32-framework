#include<Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include <CommCtrl.h>//���ÿؼ�
#include "resource.h"

HINSTANCE hIns;
//���ڹ��̺�����˵��
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinChildProc(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
);
LRESULT CALLBACK WinChildProc2(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
);
LRESULT CALLBACK WinTVProc(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
);
HWND hwndTV;
HWND hParentWnd;
HWND hChildWnd;
HWND hChildWnd2;
HWND hTVWnd;
BOOL CreatedChildWindow1 = false;
BOOL CreatedChildWindow2 = false;
BOOL CreatedTVWindow = false;
TVITEM tvi;
#define TreeViewWeight 200
/* *********************************************
*���ܣ�Ϊtreeview���ӽڵ�
*������hwndTV,TreeView�ؼ����
			LpszItem���ڵ������
			hParent�����ڵ�ľ��
*����ֵ�������Ľڵ���
**********************************************/
HTREEITEM AddItemToTree(
	HWND hwndTV,
	LPSTR lpszItem,
	HTREEITEM hParent
)
{
	TVITEM tParent;
	TVINSERTSTRUCT tvins;
	HTREEITEM hme;
	//����ITEM�Ĳ���
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
	tvi.pszText = lpszItem;
	
	//���STRUCT�ṹ
	tvins.item = tvi;
	tvins.hInsertAfter = TVI_ROOT;
	if (hParent == NULL)
	{
		tvins.hParent = TVI_ROOT;
	}
	else
	{
		tvins.hParent = hParent;
	}
	//���ùؼ���TreeView_InsertItem����
	hme = TreeView_InsertItem(hwndTV, &tvins);
	return hme;
}
/* *********************************************
*���ܣ�Ϊtreeview�����������ɸ��ڵ�
*������hwndtv��treeview�ռ䴰�ھ��
**********************************************/
bool InitTreeViewItems(HWND hwndTV)
{
	HTREEITEM hRoot = AddItemToTree(hwndTV, "input", NULL);
	HTREEITEM hp = AddItemToTree(hwndTV, "document1", hRoot);
	hp = AddItemToTree(hwndTV, "document2", hRoot);
	return true;
}

/* *********************************************
*���ܣ�����һ��TreeView�ؼ�
*������hwndParent��Ҫ�����ĸ����ھ��
*����ֵ��������TreeView�ؼ����
**********************************************/
HWND CreateATreeView(HWND hwndParent)
{
	RECT rcClient;
	GetClientRect(hwndParent, &rcClient);
	hwndTV = CreateWindowEx(0,
		WC_TREEVIEW,
		TEXT("Tree View"),
		WS_VISIBLE | WS_CHILD | TVS_HASLINES|TVS_HASBUTTONS | TVS_EDITLABELS | TVS_LINESATROOT | WS_BORDER,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rcClient.right,
		rcClient.bottom,
		hwndParent,
		NULL,
		hIns,
		NULL);
	InitTreeViewItems(hwndTV);
	
	return hwndTV;
}


/* *********************************************
*���ܣ����treeview���ĸ��ڵ㱻ѡ��
*������pNMHDR,WM_NOTIFY  ��Ϣ������LParam����
*����ֵ���Ƿ����˽ڵ�
**********************************************/
//BOOL ClickTree()
//{
//	POINT point;
//	TVHITTESTINFO thti;
//	HTREEITEM htitem;
//
//	GetCursorPos(&point);
//
//	ScreenToClient(hwndTV, &point);
//
//	thti.pt = point;
//	thti.flags = TVHT_TORIGHT;
//
//	htitem = TreeView_HitTest(hwndTV, &thti);
//	if (htitem!= NULL)
//	{
//		ClientToScreen(hwndTV, &point);
//		TreeView_SelectItem(hwndTV, htitem);
//		return true;
//	}
//	return false;
//}
/* *********************************************
*���ܣ������Ӵ���1
*������hwndParent��Ҫ�����ĸ����ھ��
*����ֵ�������Ĵ��ھ��
**********************************************/
HWND CreateChildWindows(HWND hwndParent)
{
	hChildWnd = CreateWindowEx(NULL,
		"window class2",
		"Child Window",
		WS_OVERLAPPEDWINDOW,
		TreeViewWeight,
		150,
		640,
		480,
		NULL,
		NULL,
		hIns,
		NULL);

	if (!hChildWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	SetParent(hChildWnd, hParentWnd);//����

	//��ʾ����
	ShowWindow(hChildWnd, SW_SHOWNORMAL);

	//���´���
	UpdateWindow(hChildWnd);
	return hChildWnd;
}
/* *********************************************
*���ܣ������Ӵ���2
*������hwndParent��Ҫ�����ĸ����ھ��
*����ֵ�������Ĵ��ھ��
**********************************************/
HWND CreateChildWindows2(HWND hwndParent)
{
	hChildWnd2 = CreateWindowEx(NULL,
		"window class3",
		"Child Window2",
		WS_OVERLAPPEDWINDOW,
		200,
		150,
		640,
		480,
		NULL,
		NULL,
		hIns,
		NULL);

	if (!hChildWnd2)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	SetParent(hChildWnd2, hParentWnd);//����

	//��ʾ����
	ShowWindow(hChildWnd2, SW_SHOWNORMAL);

	//���´���
	UpdateWindow(hChildWnd2);
	return hChildWnd2;
}
/* *********************************************
*���ܣ�����TV����
*������hwndParent��Ҫ�����ĸ����ھ��
*����ֵ�������Ĵ��ھ��
**********************************************/
HWND CreateTVWindows(HWND hwndParent)
{
	hTVWnd = CreateWindowA(
		"ChildTVClass",	//����������
		"TVForm",
		WS_OVERLAPPEDWINDOW,	//���ڷ�񣬶���Ϊ��ͨ��
		0,						//����λ�õ�x����
		0,						//����λ�õ�y����
		TreeViewWeight,					//���ڵĿ��
		400,					//���ڵĸ߶�
		hwndParent,					//�����ھ��
		NULL,					//�˵����
		hIns,				//Ӧ�ó���ʵ�����
		NULL);					//���ڴ�������ָ��
	if (hTVWnd == NULL) return NULL;

	SetParent(hTVWnd, hParentWnd);//����

	//��ʾ����
	ShowWindow(hTVWnd, SW_SHOWNORMAL);

	//���´���
	UpdateWindow(hTVWnd);
	return hTVWnd;
}
/* *********************************************
*���ܣ�ע�ᴰ��
*������hInstance��������Ĵ��ڹ��̵�ʵ���ľ����
*����ֵ���Ƿ�ע��ɹ�
**********************************************/
//BOOL RegisterWindows(HINSTANCE hInstance)
//{
//	WNDCLASSEXA wcx;
//	//��ʼ������
//	wcx.cbSize = sizeof(wcx);
//	wcx.style = CS_HREDRAW | CS_VREDRAW;//���ڴ�С�ı䣬�ػ�����
//	wcx.lpfnWndProc = MainWndProc;//�ص㣺ָ��������Ϣ�Ĵ�����
//	wcx.lpszClassName = "MainWndClass";
//	wcx.cbClsExtra = 0;
//	wcx.cbWndExtra = 0;
//	wcx.lpszMenuName = NULL;
//	wcx.hInstance = hInstance;
//	wcx.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wcx.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�Դ��Ļ�ˢ
//	wcx.hIconSm = NULL;
//	//ע�Ტ����Ƿ�ɹ�ע��
//	if (!RegisterClassExA(&wcx)) {
//		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
//		return 0;
//	}
//	//ע���Ӵ���
//	WNDCLASSEXA wc;	//���岢��䴰����
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_HREDRAW | CS_VREDRAW;//���ڴ�С�ı䣬�ػ�����
//	wc.lpfnWndProc = WinChildProc;//�ص㣺ָ��������Ϣ�Ĵ�����
//	wc.lpszClassName = "ChildWndClass1";
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.lpszMenuName = NULL;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�Դ��Ļ�ˢ
//	wc.hIconSm = NULL;
//	//ע���Ӵ���2
//	WNDCLASSEXA wc2;	//���岢��䴰����
//	wc2.cbSize = sizeof(wc2);
//	wc2.style = CS_HREDRAW | CS_VREDRAW;//���ڴ�С�ı䣬�ػ�����
//	wc2.lpfnWndProc = WinChildProc2;//�ص㣺ָ��������Ϣ�Ĵ�����
//	wc2.lpszClassName = "ChildWndClass2";
//	wc2.cbClsExtra = 0;
//	wc2.cbWndExtra = 0;
//	wc2.lpszMenuName = NULL;
//	wc2.hInstance = hInstance;
//	wc2.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc2.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�Դ��Ļ�ˢ
//	wc2.hIconSm = NULL;
//	//ע��TV����
//	WNDCLASSEXA wc3;	//���岢��䴰����
//	wc3.cbSize = sizeof(wc3);
//	wc3.style = CS_HREDRAW | CS_VREDRAW;//���ڴ�С�ı䣬�ػ�����
//	wc3.lpfnWndProc = WinChildProc2;//�ص㣺ָ��������Ϣ�Ĵ�����
//	wc3.lpszClassName = "ChildWndClass2";
//	wc3.cbClsExtra = 0;
//	wc3.cbWndExtra = 0;
//	wc3.lpszMenuName = NULL;
//	wc3.hInstance = hInstance;
//	wc3.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc3.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�Դ��Ļ�ˢ
//	wc3.hIconSm = NULL;

//	if (!RegisterClassExA(&wc)) {
//		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
//		return 0;
//	}
//	if (!RegisterClassExA(&wc2)) {
//		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
//		return 0;
//	}
//	if (!RegisterClassExA(&wc3)) {
//		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
//		return 0;
//	}
//}
/* *********************************************
*���ܣ���������
*������hInstance��������Ĵ��ڹ��̵�ʵ���ľ����
*����ֵ���������ڵľ��
**********************************************/
HWND CreateWindows(HINSTANCE hInstance)
{
	hParentWnd = CreateWindowEx(NULL,
		"MainWndClass",
		"Parent Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), 
		hInstance,
		NULL); 
	//����Ƿ�ɹ��������
	if (!hParentWnd)
		MessageBox(NULL, "����ʧ��", "Infor", MB_OK);
	//���ɴ���
	return hParentWnd;
}
/* *********************************************
*���ܣ���ʾ����
*������nCmdShow ���ڵ���ʾ��ʽ����󻯡���С������
**********************************************/
//void displaywindows(int nCmdShow)
//{
//	nCmdShow = SW_SHOWDEFAULT;
//	UpdateWindow(hParentWnd);
//	ShowWindow(hParentWnd, nCmdShow);
//}
/* *********************************************
*���ܣ���Ϣ���������ϵ�ͨ��GetMessage��׽�Ŵ��ڵ���Ϣ��
��ͨ��TranslateMessage���������Ϣת��Ϊ�ַ���Ϣ,
Ȼ��ͨ��DispatchMessage����Ϣ���ɸ����ǵĴ��ڳ�����д���
����ν������ǵ������Ƕ���Ĵ��ڴ�����WinProc��
**********************************************/
void Message()
{
	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	bool endprogram = false;
	//create window 1

	WNDCLASSEX windowclassforwindow1;
	ZeroMemory(&windowclassforwindow1, sizeof(WNDCLASSEX));
	windowclassforwindow1.cbClsExtra = NULL;
	windowclassforwindow1.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow1.cbWndExtra = NULL;
	windowclassforwindow1.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow1.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow1.hIcon = NULL;
	windowclassforwindow1.hIconSm = NULL;
	windowclassforwindow1.hInstance = hInstance;
	windowclassforwindow1.lpfnWndProc = (WNDPROC)MainWndProc;
	windowclassforwindow1.lpszClassName = "windowclass 1";
	windowclassforwindow1.lpszMenuName = NULL;
	windowclassforwindow1.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow1))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed",
			"Window Class Failed",
			MB_ICONERROR);
	}

		hParentWnd = CreateWindowEx(NULL,
		windowclassforwindow1.lpszClassName,
		"Parent Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),
		hInstance,
		NULL                /* No Window Creation data */
	);

	if (!hParentWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(hParentWnd, nCmdShow);

	// create window 2

	WNDCLASSEX windowclassforwindow2;
	ZeroMemory(&windowclassforwindow2, sizeof(WNDCLASSEX));
	windowclassforwindow2.cbClsExtra = NULL;
	windowclassforwindow2.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow2.cbWndExtra = NULL;
	windowclassforwindow2.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow2.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow2.hIcon = NULL;
	windowclassforwindow2.hIconSm = NULL;
	windowclassforwindow2.hInstance = hInstance;
	windowclassforwindow2.lpfnWndProc = (WNDPROC)WinChildProc;
	windowclassforwindow2.lpszClassName = "window class2";
	windowclassforwindow2.lpszMenuName = NULL;
	windowclassforwindow2.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow2))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed for window 2",
			"Window Class Failed",
			MB_ICONERROR);
	}

		 

	// create window 3

	WNDCLASSEX windowclassforwindow3;
	ZeroMemory(&windowclassforwindow3, sizeof(WNDCLASSEX));
	windowclassforwindow3.cbClsExtra = NULL;
	windowclassforwindow3.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow3.cbWndExtra = NULL;
	windowclassforwindow3.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow3.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow3.hIcon = NULL;
	windowclassforwindow3.hIconSm = NULL;
	windowclassforwindow3.hInstance = hInstance;
	windowclassforwindow3.lpfnWndProc = (WNDPROC)WinChildProc2;
	windowclassforwindow3.lpszClassName = "window class3";
	windowclassforwindow3.lpszMenuName = NULL;
	windowclassforwindow3.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow3))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed for window 3",
			"Window Class Failed",
			MB_ICONERROR);
	}
	
	//create TV window
	WNDCLASSEXA wc3;	//���岢��䴰����
	wc3.cbSize = sizeof(wc3);
	wc3.style = CS_HREDRAW | CS_VREDRAW;//���ڴ�С�ı䣬�ػ�����
	wc3.lpfnWndProc = WinTVProc;//�ص㣺ָ��������Ϣ�Ĵ�����
	wc3.lpszClassName = "ChildTVClass";
	wc3.cbClsExtra = 0;
	wc3.cbWndExtra = 0;
	wc3.lpszMenuName = NULL;
	wc3.hInstance = hInstance;
	wc3.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	wc3.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
	wc3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�Դ��Ļ�ˢ
	wc3.hIconSm = NULL;
	
	if (!RegisterClassEx(&wc3))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed for window 3",
			"Window Class Failed",
			MB_ICONERROR);
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
//���ڹ��̺���
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_COMMAND:
	{
		// ȡ����ԴIdֵ  
		// ���ж��û�ѡ�����ĸ��˵���  
		switch (LOWORD(wParam))
		{
		case IDM_Tree:
			if (CreatedTVWindow == false)
			{
				CreateTVWindows(hParentWnd);
				CreateATreeView(hTVWnd);
				CreatedTVWindow = true;
			}
			break;
		default:
			break;
		}
	}
	
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
}
LRESULT CALLBACK WinChildProc(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		CreatedChildWindow1 = false;
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;	//return 1
}
LRESULT CALLBACK WinChildProc2(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		CreatedChildWindow2 = false;
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;	//return 1
}
LRESULT CALLBACK WinTVProc(
	HWND hWnd,		// ���ھ��
	UINT uMsg,		// ��ϢID
	WPARAM wParam,	// ��1����Ϣ����
	LPARAM lParam	// ��2����Ϣ����
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		CreatedTVWindow = false;
		return 0;
		break;
	case WM_NOTIFY:
	{
		LPNMHDR lpnmh = (LPNMHDR)lParam;
		if (NM_DBLCLK == lpnmh->code)
		{
			DWORD dwPos = GetMessagePos();
			POINT pt;
			pt.x = LOWORD(dwPos);
			pt.y = HIWORD(dwPos);
			ScreenToClient(lpnmh->hwndFrom, &pt);//��Ļ����ת���ͻ����������
			TVHITTESTINFO ht = { 0 };
			ht.pt = pt;
			ht.flags = TVHT_ONITEM;
			HTREEITEM hItem = TreeView_HitTest(lpnmh->hwndFrom, &ht);//ȷ��ָ�������������ͼ�ؼ��Ŀͻ�����λ��
			TCHAR buf[10] = { 0 };
			tvi.cchTextMax = 10;
			tvi.pszText = buf;
			tvi.hItem = hItem;
			TreeView_GetItem(lpnmh->hwndFrom, &tvi);//������οؼ���item��ֵ�����а����˽ڵ����Ƶ�ֵ
			//���ݽڵ����ƵĲ�ͬ���򿪲�ͬ���Ӵ���
			if ((strcmp(tvi.pszText, "document1") || CreatedChildWindow1) == false)
			{
				CreateChildWindows(hParentWnd);
				CreatedChildWindow1 = true;
				BringWindowToTop(hChildWnd);
			}
			else if ((strcmp(tvi.pszText, "document2") || CreatedChildWindow2) == false)
			{
				CreateChildWindows2(hParentWnd);
				CreatedChildWindow2 = true;
				BringWindowToTop(hChildWnd2);
			}
		}
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;	//return 1
}