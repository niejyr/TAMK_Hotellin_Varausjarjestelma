# TAMK_Hotellin_Varausjarjestelma
 C++ Perusteet kurssin Harjoitustyö

Tämä ohjelma on yksinkertainen hotellin varausjärjestelmä, joka mahdollistaa huonevarausten hallinnan. Ohjelman avulla voi lisätä uusia varauksia, hakea varauksia asiakkaan nimen perusteella sekä tallentaa ja palauttaa varauksia tiedostosta.

---

## Ominaisuudet

- **Uusien varausten lisääminen:** 
  - Ohjelma tallentaa varaajan nimen, huonetyypin, huoneen numeron, öiden määrän, mahdollisen alennuksen ja loppusumman.
  - Satunnainen varausnumero luodaan automaattisesti.
- **Varausten haku:**
  - Varauksia voi hakea asiakkaan nimen perusteella.
- **Tietojen tallennus ja palautus:**
  - Varaustiedot tallennetaan tiedostoon `varaukset.txt` ja ne voi palauttaa ohjelman muistiin.
- **Satunnaisgeneraattorit:**
  - Käytetään varausten numeroiden, huoneiden määrien ja alennusten luomiseen.

---

## Käyttöohjeet

1. **Ohjelman käynnistys:**
   - Käynnistä ohjelma. 
   - Ohjelma kysyy, haluatko palauttaa tiedostosta aiemmat varaukset (k/e). 

2. **Päävalikko:**
   - Valitse toiminto kirjoittamalla vastaava numero:
     - **1:** Lisää uusi varaus
     - **2:** Hae varauksia nimen perusteella
     - **3:** Tallenna varaukset ja poistu

3. **Uuden varauksen lisääminen:**
   - Valitse valikosta **1**.
   - Syötä varaajan nimi.
   - Valitse huonetyyppi:
     - `1` = yhden hengen huone (100 €/yö).
     - `2` = kahden hengen huone (150 €/yö).
   - Syötä öiden määrä.
   - Ohjelma laskee loppusumman ja mahdollisen alennuksen (0%, 10% tai 20%).
   - Varaus tallennetaan ohjelman muistiin.

4. **Varausten haku:**
   - Valitse valikosta **2**.
   - Syötä asiakkaan nimi.
   - Ohjelma näyttää kaikki asiakkaan tekemät varaukset.

5. **Tietojen tallennus ja ohjelman sulkeminen:**
   - Valitse valikosta **3**, jotta ohjelman muistissa olevat varaukset tallennetaan tiedostoon `varaukset.txt`.

---

## Tekniset tiedot

- **Ohjelmointikieli:** C++
- **Tietorakenne:** Käytössä on `VARAUS`-rakenne, joka sisältää seuraavat kentät:
  - Varaajan nimi
  - Varausnumero
  - Huoneen numero
  - Öiden lukumäärä
  - Loppusumma
  - Huoneen tyyppi
  - Alennusprosentti
- **Tiedoston käsittely:**
  - Varausten tallennus ja palautus tapahtuu CSV-muotoisessa tiedostossa.
- **Satunnaisgeneraattorit:**
  - Varausnumeron, huonemäärän ja alennusprosentin generointi perustuu C++:n `random_device` ja `mt19937` -kirjastoihin.

---

## Lisätiedot

- Ohjelma on tehty osana loppuharjoitustyötä.
- Tekijä: **Jyri Nieminen**, kurssi **5G00EI63-3012**, luokka **24TIETOB**.
