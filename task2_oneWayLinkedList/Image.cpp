#include <iostream>
#include "Image.h"
#include <fstream>

Image::Image(int tmy, int tmx):mx(tmx),my(tmy)
{
	img = new int[tmx*tmy];
}

Image::Image(const Image & image)
{
	img = image.img;
	mx = image.mx;
	my = image.my;
}

Image::~Image()
{
	delete []img;
}

void Image::load(char* fname)
{
	std::ifstream file;
	file.open(fname, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "failed" << std::endl;
	}

	char* buffer = new char[256];
	file.getline(buffer, 256);
	if (strcmp(buffer, "P2"))
	{
		std::cout << "Unknown format" << std::endl;
		return;
	}

	int width = 0;
	int heigth = 0;
	file.getline(buffer, 256);
	char * pch = strchr(buffer, '#');
	if (pch != NULL)
	{
		while (pch != NULL)
		{
			file.getline(buffer, 256);
			pch = strchr(buffer, '#');
		}
	}

	char *next = 0;
	pch = strtok_s(buffer, " ", &next);
	mx = atoi(pch);
	my = atoi(next);
	delete[]img;
	img = new int[mx*my];
	this->init();
		file.getline(buffer, 256);
	int maxColors;
	file >> maxColors;

	for (int y = 0; y < my; y++)
	{
		file.getline(buffer, 256);
		next = 0;
		pch = strtok_s(buffer, " ", &next);
		for (int x = 0; x < mx; x++)
		{
			if (pch != NULL)
			{
				set(y, x, atoi(pch));
				pch = strtok_s(0, " ", &next);
			}
		}
	}
}

void Image::show()
{
	for (int i = 0; i < my; i++) 
	{
		for (int j = 0; j < mx; j++)
		{
			std::cout << get(i, j) << " ";
		}

		std::cout << std::endl;
	}
}

void Image::init()
{
	for (int i = 0; i<my; i++)
		for (int j = 0; j < mx; j++)
		{
			set(i,j,0);
		}
}

void Image::set(int y, int x, int c)
{
	img[mx*y + x] = c;
}
int Image::get(int y, int x)
{
	return img[mx*y + x];
}

Image & Image::operator=(const Image & image)
{
	this->img = image.img;
	this->mx = image.mx;
	this->my = image.my;
	return *this;
}
