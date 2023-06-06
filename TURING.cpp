#include <fstream>
#include <iostream>

using namespace std;
int index(1); // integras
class turing  // pazymima klases struktura
{
private: // aprasoma privati klase
  int pozicija, pozicija2;
  int baigimas = 0;
  int luzimas = 0;
  string eilute, eilute2, pavadinimas, esama_busena[100], nauja_busena[100],
      klaus;
  char esamas_simb[100], naujas_simb[100], kryptis[100], esamas_simb2[100],
      naujas_simb2[100], kryptis2[100];

public:
  int juostu;
  void ived() // ivedimo funckija
  {
    cout << "Iveskite skaitomo failo pavadinima, pvz: 2.txt: ";
    cin >> pavadinimas; // nuskaito kuri vartotojas pasirinks faila
    ifstream fd(pavadinimas.c_str()); // ifstream nuo pasirinkto failo

    fd >> juostu; // nuskaito kiek yra juostu
    if (juostu == 1)
      fd >> eilute; // nuskaito eilute kodo kuri reiks modifikuot
    else {
      fd >> eilute;
      fd >> eilute2;
    }
    if (juostu == 1)
      fd >> pozicija; // nuskaito pozicija
    else {
      fd >> pozicija >> pozicija2;
    }
    if (juostu == 1) { // funkcija ivest 1 eilutei
      cout << "Pradine eilute = " << eilute << endl;
      fd >> esama_busena[0] >> esamas_simb[0] >> naujas_simb[0] >> kryptis[0] >>
          nauja_busena[0];
      while (!fd.eof()) {
        fd >> esama_busena[index] >> esamas_simb[index] >> naujas_simb[index] >>
            kryptis[index] >> nauja_busena[index];
        index++; // pliusuojami masyvo kiekiai
      }
      fd.close();
    }
    if (juostu == 2) { // funkcija ivest 2 eilutem
      cout << "Pradines eilutes = " << endl
           << eilute << endl
           << eilute2 << endl;
      fd >> esama_busena[0] >> esamas_simb[0] >> naujas_simb[0] >> kryptis[0] >>
          nauja_busena[0];
      while (!fd.eof()) {
        fd >> esama_busena[index] >> esamas_simb[index] >>
            esamas_simb2[index] >> naujas_simb[index] >> naujas_simb2[index] >>
            kryptis[index] >> kryptis2[index] >> nauja_busena[index];
        index++;
      }
      index--;
      fd.close();
    }
  }
  void masina() {
    int ilgis = eilute.length(); // ilgis lygu eilutes ilgiui
    string laikina = "0";        // laikina busena
    while (pozicija >= 0 &&
           pozicija < ilgis) { // tikrina ar galvute dar ant juostos

      for (int i = 0; i < index; i++) {
        if (esama_busena[i] == laikina &&
            esamas_simb[i] == eilute[pozicija]) { // tikrina ar esama busena atitinka koda +
                                    // tikrina ar simbolis kuri reiks pakeist
                                    // atitinka
          eilute[pozicija] = naujas_simb[i]; // sukeicia simbolius
          laikina = nauja_busena[i];         // pakeicia i busena kuri bus
          if (kryptis[i] == 'R')
            pozicija++; // juda i prieki
          else if (kryptis[i] == 'L')
            pozicija--; // juda atgal
          if (pozicija < 0 ||
              pozicija >= ilgis) // ziuri ar galvute neisejo uz juostos ribu
            break;
          cout << eilute << endl
               << endl; // isprintina eilute jeigu ji pasikeicia
          luzimas++;
          if (luzimas > 10000) {
            string klaus;
            cout << "ar norite testi darba? nes tai gali buti begalinis ciklas "
                    "Irasykite TAIP arba NE"
                 << endl;
            cin >> klaus;
            if (klaus == "NE")
              return;
            else
              luzimas = 0;
          }
        }
      }
      baigimas++;
      if (baigimas > 10000) {
        cout << "jeigu paspaudus TAIP rezultatas nepasikeis irasykit NE, nes "
                "programa atliko darba"
             << endl;
        cin >> klaus;
        if (klaus == "NE")
          return;
        else
          baigimas = 0;
      }
    }
  }
  void masina2() // masinos veikimo funkcija
  {

    int ilgis = eilute.length();
    int ilgis2 = eilute2.length();
    string laikina = "0";
    while ((pozicija >= 0 && pozicija < ilgis) ||
           (pozicija2 >= 0 && pozicija2 < ilgis2)) {
      for (int i = 0; i < index; i++) {
        if (esama_busena[i] == laikina && esamas_simb[i] == eilute[pozicija]) {
          eilute[pozicija] = naujas_simb[i]; // sukeicia simbolius
          laikina = nauja_busena[i];         // pakeicia i busena kuri bus
          if (kryptis[i] == 'R')
            pozicija++; // juda i prieki
          else if (kryptis[i] == 'L')
            pozicija--; // juda atgal
          if (pozicija < 0 ||
              pozicija >= ilgis) // ziuri ar galvute neisejo uz juostos ribu
            return;
          luzimas++;
          if (luzimas > 10000) {
            string klaus;
            cout << "ar norite testi darba? nes tai gali buti begalinis ciklas "
                    "Irasykite TAIP arba NE"
                 << endl;
            cin >> klaus;
            if (klaus == "NE")
              return;
            else
              luzimas = 0;
          }}

          if (esama_busena[i] == laikina &&
              esamas_simb2[i] == eilute2[pozicija2]) {

            eilute2[pozicija2] = naujas_simb2[i]; // sukeicia simbolius
            laikina = nauja_busena[i];            // pakeicia i busena kuri bus
            if (kryptis2[i] == 'R')
              pozicija2++; // juda i prieki
            else if (kryptis2[i] == 'L')
              pozicija2--; // juda atgal
            if (pozicija2 < 0 ||
                pozicija2 >= ilgis2) // ziuri ar galvute neisejo uz juostos ribu
              break;
          }
        }
        // amzinas ciklas
        baigimas++;
        if (baigimas > 1000) {
          cout << "jeigu paspaudus rezultatas nepasikeis irasykit NE, nes "
                  "programa atliko darba"
               << endl;
          cin >> klaus;
          if (klaus == "NE")
            return;
          else
            baigimas = 0;
        }
      }
    }
};

int main() // pagrindine funckija
{
  turing veiksmas; // tiuringo klase
  veiksmas.ived(); // ivedimo kvietimas
  if (veiksmas.juostu == 1)
    veiksmas.masina(); // masinos kvietimas
  if (veiksmas.juostu == 2)
    veiksmas.masina2(); // 2 juostu kvietimas
  return 0;
}