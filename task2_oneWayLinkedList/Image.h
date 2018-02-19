#pragma once


class Image
{
	int* img;
	int mx;
	int my;
public:
	Image(int tmx, int tmy);
	Image(const Image& image);
	virtual ~Image();
	int getMx() { return mx; }
	int gerMy() { return my; }
	void load(char* fname);
	void show();
	void init();
	void set(int y, int x, int c);
	int get(int y, int x);
	Image& operator=(const Image& image);
};

