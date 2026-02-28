#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#pragma pack(push, 1)			
struct BMPFILEHEADER {
	uint16_t fileType = 0;
	uint32_t size = 0;
	uint16_t reserv1 = 0;
	uint16_t reserv2 = 0;
	uint32_t offBits = 0;
};

struct BMPINFOHEADER {
	uint32_t headSize = 0;
	uint32_t width = 0;
	uint32_t height = 0;
	uint16_t Planes = 0;
	uint16_t bitCount = 0;
	uint32_t compression = 0;
	uint32_t imgSize = 0;
	uint32_t xRes = 0;
	uint32_t yRes = 0;
	uint32_t crlUsed = 0;
	uint32_t crlImportant = 0;
};
#pragma pack(pop)				

struct Point {
	int x = 0;
	int y = 0;
};

class BMPModifier
{
private:
	char* buffer;
	BMPFILEHEADER fileHead;
	BMPINFOHEADER infoHead;
	void drawLine(int x1, int x2, int y1, int y2);
	void clearBuffer() {
		delete[] buffer;
		buffer = nullptr;
	};
public:
	BMPModifier() { 
		buffer = nullptr;
		fileHead = {};
		infoHead = {};
	};
	BMPModifier(string filePath) {
		buffer = nullptr;
		fileHead = {};
		infoHead = {};
		readBMP(filePath);
	};
	~BMPModifier() { clearBuffer(); };
	void drawCross() {
		drawLine(0, infoHead.width, 0, infoHead.height);
		drawLine(infoHead.width, 0, 0, infoHead.height);
	};
	bool readBMP(string filePath);
	void showBMP() const;
	void saveBMP(string filePath) const;
};

