#include <fstream>
#include <iostream>

using namespace std;

int main() 
{
 /* 
editas nuo praeitos programos, kuri viska talpina pagal charakteristikas  
 */

  char ram[256];
   ram[252] = 'n'; // jump
  char flagZERO = 'n';
  char flagEND = 'n';
  char flagOverf = 'n';

   ram[253] = 'n'; // end pabaigos "bool"
   ram[249] = 0; // simbolis
  
   // atmintis i kuria dedamas visas decryptor
  ram [255] = 0; // kiek 
  char reg[16];     // 16 registru
  int programcounter = 0;      // naudoti sita randant programcounter
  

  ifstream fdecryptor("decryptor.bin", ios::binary); // duomenys kaip ivest
  ifstream fencoded("q1_encr.txt");                  // q1_encr.txt

  while (ram[249] = fdecryptor.get(), !fdecryptor.eof()) 
  { // ivedimo funkcija
    ram[ram[255]] = ram[249];
    ram[255]++;
  }
  fdecryptor.close();

  while (1) 
  {

    ram[251] = 0x0f & ram[programcounter + 1]; //  x 
    ram[250] = (0xf0 & ram[programcounter + 1]) >> 4; // y

    switch (ram[programcounter])
      {
    case 1:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]]++;
      if (reg[ram[251]]==0)
      flagOverf='t';
      break; // prideti viena Rx
    case 2:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]]--;
      if (reg[ram[251]]==0)
      flagOverf='t';
      break; // atimti viena RX
    case 3:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]] = reg[ram[250]];
      break; // priskirti Rx  Ry konstanta
    case 4:
      reg[0] = ram[programcounter + 1];
      break; // kopijuoja konstanta i r0
    case 5:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]] = reg[ram[251]] << 1;
      break; // Rx << 1
    case 6:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]] = reg[ram[251]] >> 1;
      break; // Rx >> 1
    case 7:
      programcounter = programcounter + ram[programcounter + 1]; // kiek nusokti nusokti
      while (programcounter >= ram[255])  // Kol programcounter didesnis uz visu komandu skaiciu
      {
        programcounter = programcounter - ram[255]; // atimam po 32, nes ram masyvas 32 elementai(butent sitam decryptor) t.y. 16
                     // komandu ir 16 konstantu ar registru
      }
      ram[252] = 't';
      break;
    case 8:
      if (flagZERO == 't') { // rodo kiek nusokti pridedant konstanta prie
                             // skaitiklio taciau tik jeigu zero flag 't'
        programcounter = programcounter + ram[programcounter + 1];
        while (programcounter >= ram[255]) // Kol programcounter didesnis uz visu komandu skaiciu
        {
          programcounter = programcounter - ram[255]; // atimam po 32, nes ram masyvas 32 elementai t.y. 16
                       // komandu ir 16 konstantu ar registru
        }
        ram[252] = 't';
      }
      break;
    case 9:
      if (flagZERO == 'n') { // rodo programcounter nusokti pridedant konstanta prie
                             // skaitiklio taciau tik jeigu zero flag 'n'
        programcounter = programcounter + ram[programcounter + 1];
        while (programcounter >= ram[255]) // Kol programcounter didesnis uz visu komandu skaiciu
        {
          programcounter = programcounter - ram[255]; // atimam po 32, nes ram masyvas 32 elementai t.y. 16
                       // komandu ir 16 konstantu ar registru
        }
        ram[252] = 't';
      }
      break;
    case 0x0A:
      if (flagEND == 't') // jeigu end flag iskeltas tai padaro suoli 
      {
        programcounter = programcounter + ram[programcounter + 1];
        while (programcounter >= ram[255]) // Kol programcounter didesnis uz visu komandu skaiciu
        {
          programcounter = programcounter - ram[255]; // atimam po 32, nes ram masyvas 32 elementai t.y. 16
                       // komandu ir 16 konstantu ar registru
        }
        ram[252] = 't';
      }
      break;
    case 0x0B:
      ram[253] = 't';
      break; // baigia programa darba
    case 0x0C:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      if ((reg[ram[251]]&0x80)==(reg[ram[250]]&0x80))
      flagOverf='t';
      reg[ram[251]] = reg[ram[251]] + reg[ram[250]];
      if ((reg[ram[251]]&0x80)!=(reg[ram[250]]&0x80))
      {
        
      }
      else
      {
        flagOverf='n';
      }
      break; // Rx+Ry
    case 0x0D:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
       if ((reg[ram[251]]&0x80)==(reg[ram[250]]&0x80))
      flagOverf='t';
      reg[ram[251]] = reg[ram[251]] - reg[ram[250]];
      if ((reg[ram[251]]&0x80)!=(reg[ram[250]]&0x80))
      {
        
      }
      else
      {
        flagOverf='n';
      }
      break; // Rx-Ry
    case 0x0E:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]] = reg[ram[251]] ^ reg[ram[250]];
      break; // XOR Rx,Ry  (Rx⨁Ry)
    case 0x0F:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      reg[ram[251]] = reg[ram[251]] | reg[ram[250]];
      break; // OR Rx,Ry (Rx&Ry)
    case 0x10:
      if (!fencoded.eof())
       { // vienas simbolio ivedimas kaip rodo 10 komanda ir
                             // if ar nepasibaige uzkoduotas failas
        fencoded >> ram[249];
        reg[ram[251]] = ram[249];
      } 
      else 
      {
        flagEND = 't'; // nustate kad pasibaige failas encr
      }
      break;
    case 0x11:
      flagZERO = 'n';
      flagEND = 'n';
      flagOverf = 'n';
      cout << reg[ram[251]];
      break;
        case 0x12:
          if ( flagOverf=='t'){
         programcounter = programcounter + ram[programcounter + 1]; // kiek nusokti nusokti
      while (programcounter >= ram[255])  // Kol programcounter didesnis uz visu komandu skaiciu
      {
        programcounter = programcounter - ram[255]; // atimam po 32, nes ram masyvas 32 elementai(butent sitam decryptor) t.y. 16
                     // komandu ir 16 konstantu ar registru
      }
      ram[252] = 't';
      
    }
          flagOverf='n';
        break;
      }

    // Jei ivyko aritmetines ir logines operacijos, programcounter kito registro value 
    if (ram[programcounter] == 0x01 || ram[programcounter] == 0x02 || ram[programcounter] == 0x05 ||
        ram[programcounter] == 0x06 || ram[programcounter] == 0x0c || ram[programcounter] == 0x0d ||
        ram[programcounter] == 0x0e || ram[programcounter] == 0x0f) 
    {
      if (reg[ram[251]] == 0) // jeigu rezultatas nulis po keitimu 
      {
        flagZERO = 't';
      } 
      else 
      {
        flagZERO = 'n';
      }
    }

    if (ram[252] == 'n') // jeigu nebuvo suolio pajudinam i kita registra
    {
      programcounter = programcounter + 2;
    } else 
    { // jeigu ram[252] buvo tai tada nieko nedarom ir padarom suoli i false
      ram[252] = 'n';
    }
    if (ram[253] == 't') // jeigu pasiekiam gala tai uzbaigia darba 
      break;
   
  }
  fencoded.close();
}