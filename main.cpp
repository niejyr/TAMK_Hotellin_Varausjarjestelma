//      +����������������������������������������������������������������+
//      |                   HOTELLIN VARAUSJ�RJESTELMA                   |
//      +----------------------------------------------------------------+
//      | Kurssi: 5G00EI63-3012                                          |
//      | Tyyppi: Loppuharjoitusty�                                      |
//      |                                                                |
//      | Tekij�: Jyri Nieminen                                          |
//      | Luokka: 24TIETOB                                               |
//      +����������������������������������������������������������������+

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <locale>

using namespace std;

struct VARAUS {
    string varaaja_NIMI;     // Varaajan nimi
    int varaus_NRO;          // Varausnumero
    int huone_NRO;           // Huoneen numero
    int yo_LKM;              // �iden lukum��r�
    int loppusumma;          // Loppusumma alennuksen j�lkeen
    string huone_tyyppi;     // Huoneen tyyppi (1/2)
    int alennus_prosentti;   // Alennuksen m��r� prosentteina
};



static int VARAUS_nro_GEN() {                       // SATUNNAISLUKUGENERAATTORI VARAUSNUMEROLLE
    random_device rd;                               // Alustetaan satunnaislaite siement� varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenell�
    uniform_int_distribution<> dis(10000, 99999);   // M��ritet��n jakauma
    return dis(gen);                                // Palautetaan satunnainen luku
}

static int HUONEIDEN_MAARA_GEN() {                  // SATUNNAISLUKUGENERAATTORI HUONEIDEN M��R�LLE
    random_device rd;                               // Alustetaan satunnaislaite siement� varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenell�
    uniform_int_distribution<> dis(40, 300);        // M��ritet��n jakauma
    int num = dis(gen);                             // Arvotaan satunnainen luku
    if (num % 2 != 0) {                             // Jos luku on pariton
        num++;                                      // Muutetaan seuraavaksi parilliseksi
    }
    return num;                                     // Palautetaan parillinen luku
}

static int ALENNUS_MAARA_GEN() {                  // SATUNNAISLUKUGENERAATTORI Alennukselle
    random_device rd;                               // Alustetaan satunnaislaite siement� varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenell�
    uniform_int_distribution<> dis(0, 2);           // M��ritet��n jakauma
    int ale = dis(gen);                             // Arvotaan satunnainen luku
    return ale;                                     // Palautetaan parillinen luku
}





//  ALIOHJELMA 1
//  Varausten tallentaminen tiedostoon

void tallenna_varaukset(const vector<VARAUS>& varaukset, const string& tiedostonimi) {
    ofstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        cerr << "Tiedoston avaaminen ep�onnistui!" << endl;
        return;
    }

    for (const auto& varaus : varaukset) {
        tiedosto << varaus.varaaja_NIMI << "," << varaus.varaus_NRO << ","
            << varaus.huone_NRO << "," << varaus.yo_LKM << ","
            << varaus.loppusumma << "," << varaus.huone_tyyppi << ","
            << varaus.alennus_prosentti << endl;

    }
    tiedosto.close();
    cout << "\nVaraukset tallennettu onnistuneesti '" << tiedostonimi << "'." << endl;
}





//  ALIOHJELMA 2
//  Varausten palauttaminen tiedostosta

void lue_varaukset(vector<VARAUS>& varaukset, const string& tiedostonimi) {
    ifstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        cout << "Tiedostoa '" << tiedostonimi << "' ei l�ytynyt. Aloitetaan tyhj�ll� varauslistalla." << endl;
        return;
    }

    string rivi;
    while (getline(tiedosto, rivi)) {
        stringstream ss(rivi);
        VARAUS varaus;
        string yo_LKM, loppusumma;

        getline(ss, varaus.varaaja_NIMI, ',');
        ss >> varaus.varaus_NRO;
        ss.ignore(1); // ohitetaan pilkku
        ss >> varaus.huone_NRO;
        ss.ignore(1);
        getline(ss, yo_LKM, ',');
        getline(ss, loppusumma, ',');
        getline(ss, varaus.huone_tyyppi);
        ss >> varaus.alennus_prosentti;

        varaus.yo_LKM = stoi(yo_LKM);
        varaus.loppusumma = stoi(loppusumma);

        varaukset.push_back(varaus);
    }
    tiedosto.close();
    cout << "Varaukset palautettu tiedostosta '" << tiedostonimi << "'." << endl;
}





//  ALIOHJELMA 3
//  Tiedoston tyhjent�minen

void tyhjenna_tiedosto(const string& tiedostonimi) {
    ofstream tiedosto(tiedostonimi, ofstream::trunc);
    if (!tiedosto) {
        cerr << "Tiedoston avaaminen ep�onnistui!" << endl;
        return;
    }
    tiedosto.close();
    cout << "Tiedosto '" << tiedostonimi << "' on tyhjennetty." << endl;
}





//  ALIOHJELMA 4
//  Varausten hakutoiminto

void VARAUS_haku(const vector<VARAUS>& varaukset, const string& nimi) {
    bool loytyi = false;
    cout << "\nVaraukset varaajalle: " << nimi << endl;

    for (const auto& varaus : varaukset) {
        if (varaus.varaaja_NIMI == nimi) {
            cout << "\n----------------------------------" << endl;
            cout << "Varausnumero: " << varaus.varaus_NRO << endl;
            cout << "Huoneen numero: " << varaus.huone_NRO << endl;
            cout << "Huoneen tyyppi: "
                << (varaus.huone_tyyppi == "1" ? "yhden hengen" : "kahden hengen") << endl;
            cout << "�iden m��r�: " << varaus.yo_LKM << endl;
            cout << "Loppusumma: " << varaus.loppusumma << " \u20AC" << endl;
            cout << "----------------------------------" << endl;
            loytyi = true;
        }
    }

    if (!loytyi) {
        cout << "Ei l�ytynyt varauksia nimelle: " << nimi << endl;
    }
}





//  ALIOHJELMA 5
//  Varausten lis�ys

void lisaa_varaus(vector<VARAUS>& varaukset) {
    VARAUS uusi_varaus;

    string varaaja_NIMI;

    while (true) {
        getline(cin, varaaja_NIMI);

        // Tarkista, ett� nimi ei ole tyhj�
        if (!varaaja_NIMI.empty()) {
            break; // Hyv�ksy sy�te, jos se ei ole tyhj�
        }
        else {
            cout << "\nSy�t� varaajan nimi (ei voi olla tyhj�): ";
        }
    }

    uusi_varaus.varaaja_NIMI = varaaja_NIMI;

    uusi_varaus.varaus_NRO = VARAUS_nro_GEN(); // Generoi satunnainen varausnumero

    //  Kysyt��n k�ytt�j�lt� huonetyyppi
    cout << "\nValitse yhden tai kahden hengen huone (1/2): ";
    string huone_tyyppi;

    while (true) {
        cin >> huone_tyyppi;

        if (huone_tyyppi == "1" || huone_tyyppi == "2") {
            break;
        }
        else {
            cout << "\nVirheellinen huonetyyppi.\n Valitse 1 (yhden hengen huone) tai 2 (kahden hengen huone): ";
        }
    }

    uusi_varaus.huone_tyyppi = huone_tyyppi;


    //  Kysyt��n k�ytt�j�lt� �iden lukum��r�
    cout << "\nSy�t� �iden lukum��r�: ";
    int yo_LKM;
    while (true) {
        cin >> yo_LKM;

        if (cin.fail() || yo_LKM <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nVirheellinen sy�te. \nSy�t� positiivinen kokonaisluku: ";
        }
        else {
            break;
        }
    }

    uusi_varaus.yo_LKM = yo_LKM;

    uusi_varaus.huone_NRO = VARAUS_nro_GEN();
    uusi_varaus.loppusumma = uusi_varaus.yo_LKM * (uusi_varaus.huone_tyyppi == "1" ? 100 : 150);  //    Huoneiden y�pymishinnat 1h = 100� & 2h = 150�

    // Alennuksen generoiminen
    int alennus_prosentti = ALENNUS_MAARA_GEN() * 10; // Alennus 0%, 10% tai 20%
    int alennus_summa = (uusi_varaus.loppusumma * alennus_prosentti) / 100;
    uusi_varaus.loppusumma -= alennus_summa;

    // N�yt� alennus asiakkaalle
    cout << "\nSinulle on my�nnetty " << alennus_prosentti << "% alennus!" << endl;
    cout << "Loppusumma alennuksen j�lkeen: " << uusi_varaus.loppusumma << " \u20AC" << endl;

    // Lis�� varaus listaan
    varaukset.push_back(uusi_varaus);

    cout << "\nVaraus lis�tty onnistuneesti!\n" << endl;
}




//  P��OHJELMA

int main() {
    setlocale(LC_ALL, "FI_fi");

    const string TIEDOSTONIMI = "varaukset.txt";
    vector<VARAUS> varaukset;

    cout << "J�rjestelm�n muistista l�ytyy vanhoja varauksia. \n"
        << "\nHaluatko palauttaa varaukset tiedostosta? (k/e): ";
    char valinta;
    cin >> valinta;

    // Sy�tteentarkistus muistin palautukseen/poistoon
    while (valinta != 'k' && valinta != 'K' && valinta != 'e' && valinta != 'E') {
        cout << "Virheellinen sy�te. Anna 'k' (kyll�) tai 'e' (ei): ";
        cin >> valinta;
    }

    if (valinta == 'k' || valinta == 'K') {
        lue_varaukset(varaukset, TIEDOSTONIMI);
    }
    else if (valinta == 'e' || valinta == 'E') {
        tyhjenna_tiedosto(TIEDOSTONIMI);
    }


    // P��valikko
    do {
        cout << "\nValitse toiminto:\n"
            << "1. Lis�� uusi varaus\n"
            << "2. Hae varauksia nimen perusteella\n"
            << "3. Tallenna varaukset ja poistu\n"
            << "\nValinta: ";

        string valinta; // K�ytet��n merkkijonotyyppi� sy�tteen tarkistamiseen
        cin >> valinta;

        // Tarkista, ett� sy�te on hyv�ksytty vaihtoehto
        if (valinta == "1" || valinta == "2" || valinta == "3") {
            switch (valinta[0]) { // K�ytet��n sy�tett� char-tyyppisen�
            case '1':
                lisaa_varaus(varaukset);
                break;
            case '2': {
                string nimi;
                cout << "\nSy�t� varaajan nimi: ";
                cin.ignore();
                getline(cin, nimi);
                VARAUS_haku(varaukset, nimi);
                break;
            }
            case '3':
                tallenna_varaukset(varaukset, TIEDOSTONIMI);
                cout << "\nOhjelma suljetaan." << endl;
                return 0;
            }
        }
        else {
            cout << "\nVirheellinen valinta. Anna numero v�lill� 1-3." << endl;
        }
    } while (true);

    return 0;
}
