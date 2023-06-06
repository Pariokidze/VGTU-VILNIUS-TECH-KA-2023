#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

string hexconverter(int desimtainis) {
  stringstream stream;
  stream << hex << desimtainis;
  string sesioliktainis = stream.str();
  return sesioliktainis;
}
string didziojiraid(string sesioliktainis) {
  string upperStr;
  for (int i = 0; i < sesioliktainis.length(); i++) {
    upperStr += toupper(sesioliktainis[i]);
  }
  return upperStr;
}
void UTF8(string utf[], int baitas[], int desimtainis) {
  if (desimtainis < 0x80) {
    baitas[0] = desimtainis;
    utf[0] = hexconverter(baitas[0]);
  } else if (desimtainis < 0x800) {
    baitas[0] = ((desimtainis >> 6) | 0xC0);
    baitas[1] = ((desimtainis & 0x3F) | 0x80);
    for (int i = 0; i < 2; i++) {
      utf[i] = hexconverter(baitas[i]);
    }
  } else if (desimtainis < 0x10000) {
    baitas[0] = ((desimtainis >> 12) | 0xE0);
    baitas[1] = (((desimtainis >> 6) & 0x3F) | 0x80);
    baitas[2] = ((desimtainis & 0x3F) | 0x80);
    for (int i = 0; i < 3; i++) {
      utf[i] = hexconverter(baitas[i]);
    }
  } else if (desimtainis <= 0x10FFFF) {
    baitas[0] = ((desimtainis >> 18) | 0xF0);
    baitas[1] = (((desimtainis >> 12) & 0x3F) | 0x80);
    baitas[2] = (((desimtainis >> 6) & 0x3F) | 0x80);
    baitas[3] = ((desimtainis & 0x3F) | 0x80);
    for (int i = 0; i < 4; i++) {
      utf[i] = hexconverter(baitas[i]);
    }
  }
}
int main() {
  int desimtainis;
  int baitas[4] = {0, 0, 0, 0};
  string utf[4];
  string sesioliktainis;
  cin >> desimtainis;
  sesioliktainis = hexconverter(desimtainis);
  sesioliktainis = didziojiraid(sesioliktainis);
  UTF8(utf, baitas, desimtainis);

  cout << "Unikodas: U+" << setfill('0') << setw(4) << sesioliktainis << endl;
  if (desimtainis < 0x80) {
    cout << "UTF-8: ";
    cout << didziojiraid(utf[0]) << endl;
    cout << "CHAR: " << char(baitas[0]);
  } else if (desimtainis < 0x800) {
    cout << "UTF-8:";
    for (int i = 0; i < 2; i++)
      cout << " " << didziojiraid(utf[i]);
    cout << endl;
    cout << "CHAR: " << char(baitas[0]) << char(baitas[1]);
  } else if (desimtainis < 0x10000) {
    cout << "UTF-8:";
    for (int i = 0; i < 3; i++)
      cout << " " << didziojiraid(utf[i]);
    cout << endl;
    cout << "CHAR: " << char(baitas[0]) << char(baitas[1]) << char(baitas[2]);
  } else if (desimtainis <= 0x10FFFF) {
    cout << "UTF-8:";
    for (int i = 0; i < 4; i++)
      cout << " " << didziojiraid(utf[i]);
    cout << endl;
    cout << "CHAR: " << char(baitas[0]) << char(baitas[1]) << char(baitas[2])
         << char(baitas[3]);
  }

  return 0;
}