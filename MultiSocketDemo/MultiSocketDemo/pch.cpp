// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
void DoEvents()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
}

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
