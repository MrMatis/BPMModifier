#include "BMPModifier.h"
#include <string>

int main()
{
    setlocale(LC_ALL, "Russian");
    string str;

    cout << "\nSet input file path: ";
    getline(cin, str);

    BMPModifier test(str);

    test.showBMP();

    cout << "\nSet input file path: ";
    getline(cin, str);

    test.readBMP(str);

    cout << "\nEdited file:\n" << endl;
    test.showBMP();

    test.drawCross();

    cout << "\nSet output file path:\n" << endl;
    test.showBMP();

    getline(cin, str);
    test.saveBMP(str);

    
    return 0;
}
