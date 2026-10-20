#include <iostream>
#include <fstream>
using namespace std;

void copiaStringa(char* dest, const char* src, int max) {
    int i = 0;
    while (src[i] != '\0' && i < max - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class PC {
public:
    int codice;
    char marca[100];
    char modello[100];
    int velocitaprocessori;
    int dimememoriaRam;
    int dimensidisco;
    int dimemonitor;
    int annoacquisto;

    PC(int codice, const char* marca, const char* modello, int velocitaprocessori,
       int dimememoriaRam, int dimensidisco, int dimemonitor, int annoacquisto) {
        this->codice = codice;
        copiaStringa(this->marca, marca, 100);
        copiaStringa(this->modello, modello, 100);
        this->velocitaprocessori = velocitaprocessori;
        this->dimememoriaRam = dimememoriaRam;
        this->dimensidisco = dimensidisco;
        this->dimemonitor = dimemonitor;
        this->annoacquisto = annoacquisto;
    }

    PC() {
        codice = 0;
        marca[0] = '\0';
        modello[0] = '\0';
        velocitaprocessori = 0;
        dimememoriaRam = 0;
        dimensidisco = 0;
        dimemonitor = 0;
        annoacquisto = 1900;
    }

    void stampa() const {
        cout << "Codice: " << codice << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modello: " << modello << endl;
        cout << "Velocita processore: " << velocitaprocessori << " MHz" << endl;
        cout << "RAM: " << dimememoriaRam << " GB" << endl;
        cout << "Disco: " << dimensidisco << " GB" << endl;
        cout << "Monitor: " << dimemonitor << " pollici" << endl;
        cout << "Anno acquisto: " << annoacquisto << endl;
    }
};

class Dipendente {
public:
    PC pc[10];
    char nome[100];
    int numPc;

    Dipendente() {
        numPc = 0;
        nome[0] = '\0';
    }

    bool aggiungiPc(const PC& nuovo) {
        if (numPc >= 10) {
            return false;
        }
        pc[numPc] = nuovo;
        numPc++;
        return true;
    }

    bool eliminaPc(const PC& daEliminare) {
        for (int i = 0; i < numPc; i++) {
            if (pc[i].codice == daEliminare.codice) {
                pc[i] = pc[numPc - 1];
                numPc--;
                return true;
            }
        }
        return false;
    }

    PC Seleziona(int indice) const {
        if (indice < 0 || indice >= numPc) {
            return PC();
        }
        return pc[indice];
    }

    void caratteristiche(int indice) const {
        if (indice < 0 || indice >= numPc) {
            cout << "Indice non valido" << endl;
            return;
        }
        pc[indice].stampa();
    }

    int cercaPerCodice(int codice) const {
        for (int i = 0; i < numPc; i++) {
            if (pc[i].codice == codice) {
                return i;
            }
        }
        return -1;
    }

    int cercaPerRam(int ram) const {
        int trovati = 0;
        for (int i = 0; i < numPc; i++) {
            if (pc[i].dimememoriaRam == ram) {
                pc[i].stampa();
                cout << "---" << endl;
                trovati++;
            }
        }
        return trovati;
    }

    void stampaLista() const {
        if (numPc == 0) {
            cout << "Nessun PC in lista" << endl;
            return;
        }
        for (int i = 0; i < numPc; i++) {
            pc[i].stampa();
            cout << "---" << endl;
        }
    }

    bool salva(const char* nomeFile) const {
        ofstream out(nomeFile, ios::binary);
        if (!out) {
            return false;
        }
        out.write(reinterpret_cast<const char*>(&numPc), sizeof(numPc));
        out.write(reinterpret_cast<const char*>(pc), sizeof(PC) * numPc);
        return true;
    }

    bool ripristina(const char* nomeFile) {
        ifstream in(nomeFile, ios::binary);
        if (!in) {
            return false;
        }
        int n;
        in.read(reinterpret_cast<char*>(&n), sizeof(n));
        if (!in || n < 0 || n > 10) {
            return false;
        }
        in.read(reinterpret_cast<char*>(pc), sizeof(PC) * n);
        if (!in) {
            return false;
        }
        numPc = n;
        return true;
    }
};

int main() {
    Dipendente dip;
    copiaStringa(dip.nome, "Mario Rossi", 100);

    PC pc1(1, "Dell", "XPS 13", 3200, 16, 512, 13, 2024);
    PC pc2(2, "HP", "Pavilion", 2800, 8, 256, 15, 2023);
    dip.aggiungiPc(pc1);
    dip.aggiungiPc(pc2);

    int pos = dip.cercaPerCodice(1);
    if (pos != -1) {
        dip.caratteristiche(pos);
    }

    dip.cercaPerRam(16);
    dip.stampaLista();

    dip.salva("pc.dat");
    dip.eliminaPc(pc1);
    dip.ripristina("pc.dat");
    return 0;
}