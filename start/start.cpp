#include<Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include <CommCtrl.h>//引用控件
#include "resource.h"

HINSTANCE hIns;
//窗口过程函数的说明
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinChildProc(
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
);
LRESULT CALLBACK WinChildProc2(
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
);
LRESULT CALLBACK WinTVProc(
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
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
*功能：为treeview增加节点
*参数：hwndTV,TreeView控件句柄
			LpszItem，节点的名字
			hParent，父节点的句柄
*返回值：创建的节点句柄
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
	//设置ITEM的参数
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
	tvi.pszText = lpszItem;
	
	//填充STRUCT结构
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
	//调用关键的TreeView_InsertItem函数
	hme = TreeView_InsertItem(hwndTV, &tvins);
	return hme;
}
/* *********************************************
*功能：为treeview窗口增加若干个节点
*参数：hwndtv，treeview空间窗口句柄
**********************************************/
bool InitTreeViewItems(HWND hwndTV)
{
	HTREEITEM hRoot = AddItemToTree(hwndTV, "input", NULL);
	HTREEITEM hp = AddItemToTree(hwndTV, "document1", hRoot);
	hp = AddItemToTree(hwndTV, "document2", hRoot);
	return true;
}

/* *********************************************
*功能：创建一个TreeView控件
*参数：hwndParent所要创建的父窗口句柄
*返回值：创建的TreeView控件句柄
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
*功能：检测treeview上哪个节点被选中
*参数：pNMHDR,WM_NOTIFY  消息所带的LParam参量
*返回值：是否点击了节点
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
*功能：创建子窗口1
*参数：hwndParent所要创建的父窗口句柄
*返回值：创建的窗口句柄
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

	SetParent(hChildWnd, hParentWnd);//核心

	//显示窗口
	ShowWindow(hChildWnd, SW_SHOWNORMAL);

	//更新窗口
	UpdateWindow(hChildWnd);
	return hChildWnd;
}
/* *********************************************
*功能：创建子窗口2
*参数：hwndParent所要创建的父窗口句柄
*返回值：创建的窗口句柄
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

	SetParent(hChildWnd2, hParentWnd);//核心

	//显示窗口
	ShowWindow(hChildWnd2, SW_SHOWNORMAL);

	//更新窗口
	UpdateWindow(hChildWnd2);
	return hChildWnd2;
}
/* *********************************************
*功能：创建TV窗口
*参数：hwndParent所要创建的父窗口句柄
*返回值：创建的窗口句柄
**********************************************/
HWND CreateTVWindows(HWND hwndParent)
{
	hTVWnd = CreateWindowA(
		"ChildTVClass",	//窗口类名称
		"TVForm",
		WS_OVERLAPPEDWINDOW,	//窗口风格，定义为普通型
		0,						//窗口位置的x坐标
		0,						//窗口位置的y坐标
		TreeViewWeight,					//窗口的宽度
		400,					//窗口的高度
		hwndParent,					//父窗口句柄
		NULL,					//菜单句柄
		hIns,				//应用程序实例句柄
		NULL);					//窗口创建数据指针
	if (hTVWnd == NULL) return NULL;

	SetParent(hTVWnd, hParentWnd);//核心

	//显示窗口
	ShowWindow(hTVWnd, SW_SHOWNORMAL);

	//更新窗口
	UpdateWindow(hTVWnd);
	return hTVWnd;
}
/* *********************************************
*功能：注册窗口
*参数：hInstance包含该类的窗口过程的实例的句柄。
*返回值：是否注册成功
**********************************************/
//BOOL RegisterWindows(HINSTANCE hInstance)
//{
//	WNDCLASSEXA wcx;
//	//初始化参数
//	wcx.cbSize = sizeof(wcx);
//	wcx.style = CS_HREDRAW | CS_VREDRAW;//窗口大小改变，重画窗口
//	wcx.lpfnWndProc = MainWndProc;//重点：指定窗口消息的处理函数
//	wcx.lpszClassName = "MainWndClass";
//	wcx.cbClsExtra = 0;
//	wcx.cbWndExtra = 0;
//	wcx.lpszMenuName = NULL;
//	wcx.hInstance = hInstance;
//	wcx.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wcx.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//自带的画刷
//	wcx.hIconSm = NULL;
//	//注册并检测是否成功注册
//	if (!RegisterClassExA(&wcx)) {
//		MessageBox(NULL, "注册失败", "Infor", MB_OK);
//		return 0;
//	}
//	//注册子窗口
//	WNDCLASSEXA wc;	//定义并填充窗口类
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_HREDRAW | CS_VREDRAW;//窗口大小改变，重画窗口
//	wc.lpfnWndProc = WinChildProc;//重点：指定窗口消息的处理函数
//	wc.lpszClassName = "ChildWndClass1";
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.lpszMenuName = NULL;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//自带的画刷
//	wc.hIconSm = NULL;
//	//注册子窗口2
//	WNDCLASSEXA wc2;	//定义并填充窗口类
//	wc2.cbSize = sizeof(wc2);
//	wc2.style = CS_HREDRAW | CS_VREDRAW;//窗口大小改变，重画窗口
//	wc2.lpfnWndProc = WinChildProc2;//重点：指定窗口消息的处理函数
//	wc2.lpszClassName = "ChildWndClass2";
//	wc2.cbClsExtra = 0;
//	wc2.cbWndExtra = 0;
//	wc2.lpszMenuName = NULL;
//	wc2.hInstance = hInstance;
//	wc2.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc2.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//自带的画刷
//	wc2.hIconSm = NULL;
//	//注册TV窗口
//	WNDCLASSEXA wc3;	//定义并填充窗口类
//	wc3.cbSize = sizeof(wc3);
//	wc3.style = CS_HREDRAW | CS_VREDRAW;//窗口大小改变，重画窗口
//	wc3.lpfnWndProc = WinChildProc2;//重点：指定窗口消息的处理函数
//	wc3.lpszClassName = "ChildWndClass2";
//	wc3.cbClsExtra = 0;
//	wc3.cbWndExtra = 0;
//	wc3.lpszMenuName = NULL;
//	wc3.hInstance = hInstance;
//	wc3.hIcon = LoadIconA(NULL, IDI_APPLICATION);
//	wc3.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
//	wc3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//自带的画刷
//	wc3.hIconSm = NULL;

//	if (!RegisterClassExA(&wc)) {
//		MessageBox(NULL, "注册失败", "Infor", MB_OK);
//		return 0;
//	}
//	if (!RegisterClassExA(&wc2)) {
//		MessageBox(NULL, "注册失败", "Infor", MB_OK);
//		return 0;
//	}
//	if (!RegisterClassExA(&wc3)) {
//		MessageBox(NULL, "注册失败", "Infor", MB_OK);
//		return 0;
//	}
//}
/* *********************************************
*功能：创建窗口
*参数：hInstance包含该类的窗口过程的实例的句柄。
*返回值：创建窗口的句柄
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
	//检测是否成功创建句柄
	if (!hParentWnd)
		MessageBox(NULL, "生成失败", "Infor", MB_OK);
	//生成窗口
	return hParentWnd;
}
/* *********************************************
*功能：显示窗口
*参数：nCmdShow 窗口的显示方式，最大化、最小化那种
**********************************************/
//void displaywindows(int nCmdShow)
//{
//	nCmdShow = SW_SHOWDEFAULT;
//	UpdateWindow(hParentWnd);
//	ShowWindow(hParentWnd, nCmdShow);
//}
/* *********************************************
*功能：消息函数，不断的通过GetMessage捕捉着窗口的消息，
再通过TranslateMessage将虚拟键消息转换为字符消息,
然后通过DispatchMessage将消息分派给我们的窗口程序进行处理
（所谓处理就是调用我们定义的窗口处理函数WinProc）
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
	WNDCLASSEXA wc3;	//定义并填充窗口类
	wc3.cbSize = sizeof(wc3);
	wc3.style = CS_HREDRAW | CS_VREDRAW;//窗口大小改变，重画窗口
	wc3.lpfnWndProc = WinTVProc;//重点：指定窗口消息的处理函数
	wc3.lpszClassName = "ChildTVClass";
	wc3.cbClsExtra = 0;
	wc3.cbWndExtra = 0;
	wc3.lpszMenuName = NULL;
	wc3.hInstance = hInstance;
	wc3.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	wc3.hCursor = LoadCursorA((HINSTANCE)NULL, IDC_ARROW);
	wc3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//自带的画刷
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
//窗口过程函数
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_COMMAND:
	{
		// 取出资源Id值  
		// 并判断用户选择了哪个菜单项  
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
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
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
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
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
	HWND hWnd,		// 窗口句柄
	UINT uMsg,		// 消息ID
	WPARAM wParam,	// 第1个消息参数
	LPARAM lParam	// 第2个消息参数
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
			ScreenToClient(lpnmh->hwndFrom, &pt);//屏幕坐标转换客户区域的坐标
			TVHITTESTINFO ht = { 0 };
			ht.pt = pt;
			ht.flags = TVHT_ONITEM;
			HTREEITEM hItem = TreeView_HitTest(lpnmh->hwndFrom, &ht);//确定指定点相对于树视图控件的客户区的位置
			TCHAR buf[10] = { 0 };
			tvi.cchTextMax = 10;
			tvi.pszText = buf;
			tvi.hItem = hItem;
			TreeView_GetItem(lpnmh->hwndFrom, &tvi);//获得树形控件的item的值，其中包含了节点名称的值
			//根据节点名称的不同，打开不同的子窗口
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