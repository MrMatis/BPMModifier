#include "BMPModifier.h"
void BMPModifier::drawLine(int x1, int x2, int y1, int y2)
{
    vector<Point> points;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 && y1 != y2) {
        points.push_back({ x1, y1 });

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    int bytesPerPixel = infoHead.bitCount / 8;
    int rowSize = ((infoHead.width * bytesPerPixel + 3) / 4) * 4;
    //bool flipped = infoHead.height > 0;

    for (const auto& p : points) {
        if (p.x >= 0 && p.x < infoHead.width && p.y >= 0 && p.y < infoHead.height) {
            int rowIndex = infoHead.height - 1 - p.y;
            char* row = buffer + rowIndex * rowSize;
            char* pixel = row + p.x * bytesPerPixel;


            pixel[0] = 0;
            pixel[1] = 0;
            pixel[2] = 0;
        }
    }
}

bool BMPModifier::readBMP(string filePath)
{
    if (!buffer) clearBuffer();
    fileHead = {};
    infoHead = {};

    ifstream ifile(filePath, ios::binary);

    if (ifile.is_open()) {

        ifile.read(reinterpret_cast<char*>(&fileHead), sizeof(fileHead));

        if (fileHead.fileType != 0x4d42) {
            cout << "\nERROR: readed file isn't BMP image!\n";
            return false;
        }

        ifile.read(reinterpret_cast<char*>(&infoHead), sizeof(infoHead));

        if (infoHead.bitCount != 24 && infoHead.bitCount != 32) {
            cout << "\nERROR: readed image isn't 24 or 32 bits!\n";
            return false;
        }

        ifile.seekg(fileHead.offBits, ios::beg);

        buffer = new char[static_cast<size_t>(infoHead.imgSize)];

        ifile.read(buffer, infoHead.imgSize);

        ifile.close();
        return true;
    }
    else {
        cout << "\nERROR: failed to open file!" << endl;
        return false;
    }
}

void BMPModifier::showBMP() const
{
    if (!buffer) {
        cout << "\nERROR: nothing to show!" << endl;
        return;
    }

    int bytesPerPixel = infoHead.bitCount / 8;
    int rowSize = ((infoHead.width * bytesPerPixel + 3) / 4) * 4;
    bool flipped = infoHead.height > 0;

    for (int y = 0; y < infoHead.height; y++) {
        int rowIndex = flipped ? infoHead.height - 1 - y : y;
        char* row = buffer + rowIndex * rowSize;

        for (int x = 0; x < infoHead.width; x++) {
            uint8_t blue = static_cast<uint8_t>(row[x * bytesPerPixel]);
            uint8_t green = static_cast<uint8_t>(row[x * bytesPerPixel + 1]);
            uint8_t red = static_cast<uint8_t>(row[x * bytesPerPixel + 2]);

            if (red == 255 && green == 255 && blue == 255) {
                std::cout << ". ";
            }
            else {
                std::cout << "@ ";
            }
        }
        std::cout << "\n";
    }
}

void BMPModifier::saveBMP(string filePath) const
{
    if (!buffer) {
        cout << "\nERROR: nothing to save!" << endl;
        return;
    }

    ofstream ofile(filePath, ios::binary);

    if (!ofile) {
        cout << "\nERROR: filed to create file " << filePath << " !" << endl;
        return;
    }

    ofile.write(reinterpret_cast<const char*>(&fileHead), sizeof(BMPFILEHEADER));
    ofile.write(reinterpret_cast<const char*>(&infoHead), sizeof(BMPINFOHEADER));

    int bytesPerPixel = infoHead.bitCount / 8;
    int rowSize = ((infoHead.width * bytesPerPixel + 3) / 4) * 4;

    ofile.write(buffer, rowSize * infoHead.height);
    ofile.close();
}
