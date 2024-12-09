//      +––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––+
//      |                   HOTELLIN VARAUSJÄRJESTELMA                   |
//      +----------------------------------------------------------------+
//      | Kurssi: 5G00EI63-3012                                          |
//      | Tyyppi: Loppuharjoitustyö                                      |
//      |                                                                |
//      | Tekijä: Jyri Nieminen                                          |
//      | Luokka: 24TIETOB                                               |
//      +––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––+

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
    int yo_LKM;              // Öiden lukumäärä
    int loppusumma;          // Loppusumma alennuksen jälkeen
    string huone_tyyppi;     // Huoneen tyyppi (1/2)
    int alennus_prosentti;   // Alennuksen määrä prosentteina
};



static int VARAUS_nro_GEN() {                       // SATUNNAISLUKUGENERAATTORI VARAUSNUMEROLLE
    random_device rd;                               // Alustetaan satunnaislaite siementä varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenellä
    uniform_int_distribution<> dis(10000, 99999);   // Määritetään jakauma
    return dis(gen);                                // Palautetaan satunnainen luku
}

static int HUONEIDEN_MAARA_GEN() {                  // SATUNNAISLUKUGENERAATTORI HUONEIDEN MÄÄRÄLLE
    random_device rd;                               // Alustetaan satunnaislaite siementä varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenellä
    uniform_int_distribution<> dis(40, 300);        // Määritetään jakauma
    int num = dis(gen);                             // Arvotaan satunnainen luku
    if (num % 2 != 0) {                             // Jos luku on pariton
        num++;                                      // Muutetaan seuraavaksi parilliseksi
    }
    return num;                                     // Palautetaan parillinen luku
}

static int ALENNUS_MAARA_GEN() {                  // SATUNNAISLUKUGENERAATTORI Alennukselle
    random_device rd;                               // Alustetaan satunnaislaite siementä varten
    mt19937 gen(rd());                              // Luodaan Mersenne Twister -generaattori siemenellä
    uniform_int_distribution<> dis(0, 2);           // Määritetään jakauma
    int ale = dis(gen);                             // Arvotaan satunnainen luku
    return ale;                                     // Palautetaan parillinen luku
}





//  ALIOHJELMA 1
//  Varausten tallentaminen tiedostoon

void tallenna_varaukset(const vector<VARAUS>& varaukset, const string& tiedostonimi) {
    ofstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        cerr << "Tiedoston avaaminen epäonnistui!" << endl;
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
        cout << "Tiedostoa '" << tiedostonimi << "' ei löytynyt. Aloitetaan tyhjällä varauslistalla." << endl;
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
//  Tiedoston tyhjentäminen

void tyhjenna_tiedosto(const string& tiedostonimi) {
    ofstream tiedosto(tiedostonimi, ofstream::trunc);
    if (!tiedosto) {
        cerr << "Tiedoston avaaminen epäonnistui!" << endl;
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
            cout << "Öiden määrä: " << varaus.yo_LKM << endl;
            cout << "Loppusumma: " << varaus.loppusumma << " \u20AC" << endl;
            cout << "----------------------------------" << endl;
            loytyi = true;
        }
    }

    if (!loytyi) {
        cout << "Ei löytynyt varauksia nimelle: " << nimi << endl;
    }
}





//  ALIOHJELMA 5
//  Varausten lisäys

void lisaa_varaus(vector<VARAUS>& varaukset) {
    VARAUS uusi_varaus;

    string varaaja_NIMI;

    while (true) {
        getline(cin, varaaja_NIMI);

        // Tarkista, että nimi ei ole tyhjä
        if (!varaaja_NIMI.empty()) {
            break; // Hyväksy syöte, jos se ei ole tyhjä
        }
        else {
            cout << "\nSyötä varaajan nimi (ei voi olla tyhjä): ";
        }
    }

    uusi_varaus.varaaja_NIMI = varaaja_NIMI;

    uusi_varaus.varaus_NRO = VARAUS_nro_GEN(); // Generoi satunnainen varausnumero

    //  Kysytään käyttäjältä huonetyyppi
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


    //  Kysytään käyttäjältä öiden lukumäärä
    cout << "\nSyötä öiden lukumäärä: ";
    int yo_LKM;
    while (true) {
        cin >> yo_LKM;

        if (cin.fail() || yo_LKM <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nVirheellinen syöte. \nSyötä positiivinen kokonaisluku: ";
        }
        else {
            break;
        }
    }

    uusi_varaus.yo_LKM = yo_LKM;

    uusi_varaus.huone_NRO = VARAUS_nro_GEN();
    uusi_varaus.loppusumma = uusi_varaus.yo_LKM * (uusi_varaus.huone_tyyppi == "1" ? 100 : 150);  //    Huoneiden yöpymishinnat 1h = 100€ & 2h = 150€

    // Alennuksen generoiminen
    int alennus_prosentti = ALENNUS_MAARA_GEN() * 10; // Alennus 0%, 10% tai 20%
    int alennus_summa = (uusi_varaus.loppusumma * alennus_prosentti) / 100;
    uusi_varaus.loppusumma -= alennus_summa;

    // Näytä alennus asiakkaalle
    cout << "\nSinulle on myönnetty " << alennus_prosentti << "% alennus!" << endl;
    cout << "Loppusumma alennuksen jälkeen: " << uusi_varaus.loppusumma << " \u20AC" << endl;

    // Lisää varaus listaan
    varaukset.push_back(uusi_varaus);

    cout << "\nVaraus lisätty onnistuneesti!\n" << endl;
}




//  PÄÄOHJELMA

int main() {
    setlocale(LC_ALL, "FI_fi");

    const string TIEDOSTONIMI = "varaukset.txt";
    vector<VARAUS> varaukset;

    cout << "Järjestelmän muistista löytyy vanhoja varauksia. \n"
        << "\nHaluatko palauttaa varaukset tiedostosta? (k/e): ";
    char valinta;
    cin >> valinta;

    // Syötteentarkistus muistin palautukseen/poistoon
    while (valinta != 'k' && valinta != 'K' && valinta != 'e' && valinta != 'E') {
        cout << "Virheellinen syöte. Anna 'k' (kyllä) tai 'e' (ei): ";
        cin >> valinta;
    }

    if (valinta == 'k' || valinta == 'K') {
        lue_varaukset(varaukset, TIEDOSTONIMI);
    }
    else if (valinta == 'e' || valinta == 'E') {
        tyhjenna_tiedosto(TIEDOSTONIMI);
    }


    // Päävalikko
    do {
        cout << "\nValitse toiminto:\n"
            << "1. Lisää uusi varaus\n"
            << "2. Hae varauksia nimen perusteella\n"
            << "3. Tallenna varaukset ja poistu\n"
            << "\nValinta: ";

        string valinta; // Käytetään merkkijonotyyppiä syötteen tarkistamiseen
        cin >> valinta;

        // Tarkista, että syöte on hyväksytty vaihtoehto
        if (valinta == "1" || valinta == "2" || valinta == "3") {
            switch (valinta[0]) { // Käytetään syötettä char-tyyppisenä
            case '1':
                lisaa_varaus(varaukset);
                break;
            case '2': {
                string nimi;
                cout << "\nSyötä varaajan nimi: ";
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
            cout << "\nVirheellinen valinta. Anna numero välillä 1-3." << endl;
        }
    } while (true);

    return 0;
}
