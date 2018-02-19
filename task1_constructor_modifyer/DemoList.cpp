// DemoList.cpp : Defines the entry point for the console application.
//

#if !defined(_WINDOWS)
#include "stdafx.h"

#endif

#include "Image.h"


int main()
{
	Image a(3,4);
	a.init();
	a.show();
	int tmp = getchar();

    return 0;
}

