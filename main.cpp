#include <stdio.h>
#include <iostream>
using namespace std;

class PC {
public:int codice;
    char marca[100];
    char modello[100];
    int velocitàprocessori;
    int dimememoriaRam;
    int dimensidisco;
    int dimemonitor;
    int annoacquisto;
    PC (int codice,char marca[100],char modello[100],int velocitàprocessori,int dimememoriaRam,int dimensidisco,int dimemonitor,int annoacquisto) {
        this->codice = codice;
        copiaStringa(this->marca, marca, 100);
        copiaStringa(this->modello, modello, 100);
        this->dimememoriaRam = dimememoriaRam;
        this->dimensidisco = dimensidisco;
        this->dimemonitor = dimemonitor;
        this->annoacquisto = annoacquisto;
    }
    void copiaStringa(char* dest, const char* src, int max) {
        int i = 0;
        while (src[i] != '\0' && i < max - 1) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    PC() {
        codice = 0;
        marca[0] = "";
        modello[0] = "";
        dimememoriaRam = 0;
        dimensidisco = 0;
        dimemonitor = 0;
        annoacquisto = 1900;
        velocitàprocessori=0;
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
    bool aggiungiPc(const PC & nuovo) {
        if (numPc >= 10) {
            return false;
        }
        pc[numPc] = nuovo;
        numPc++;
        return true;
    }
    bool eliminaPc(const PC & nuovo) {
        for (int i = 0; i < numPc; i++) {
            if (pc[i].codice == nuovo.codice) {
                pc[i] = pc[numPc - 1];
                numPc--;
                return true;
            }
        }
        return false;
    }
    PC Seleziona(int& numpc) {
        return pc[numpc];
    }
    PC caratteristiche(int codice,char marca[100],char modello[100]) {
        PC pc;
        pc.codice = codice;
        pc.marca[100] = *marca;
        pc.modello[100] = *modello;
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
int main(void) {
    Dipendente dipente;
    PC pc;
    int pos = dip.cercaPerCodice(1);
    if (pos != -1) {
        dip.caratteristiche(pos);
    }
    dip.cercaPerRam(16);
    dip.stampaLista();
    dip.salva("pc.dat");
    dip.ripristina("pc.dat");
    return 0;
}
