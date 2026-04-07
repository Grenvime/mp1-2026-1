#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Data {
    int den, mesyac, god;

    bool operator<(const Data& other) const {
        if (god != other.god) return god < other.god;
        if (mesyac != other.mesyac) return mesyac < other.mesyac;
        return den < other.den;
    }
};

struct Nablyudenie {
    Data data;
    string imya;
    double ves;
};

class VesiyNapolniye {
private:
    vector<Nablyudenie> istoriya;
    Data nachalnayaData;

    double okruglitDo50Gramm(double ves) {
        return (int)(ves * 20 + 0.5) / 20.0;
    }

    int naytiIndexPoDate(const Data& data) {
        for (int i = 0; i < (int)istoriya.size(); i++) {
            if (istoriya[i].data.den == data.den &&
                istoriya[i].data.mesyac == data.mesyac &&
                istoriya[i].data.god == data.god) {
                return i;
            }
        }
        return -1;
    }

public:
    void ustanovitNachalnuyuData(int den, int mesyac, int god) {
        nachalnayaData.den = den;
        nachalnayaData.mesyac = mesyac;
        nachalnayaData.god = god;
    }

    Data uznatNachalnuyuData() {
        return nachalnayaData;
    }

    void zadatNablyudenie(int den, int mesyac, int god, string imya, double ves) {
        Data novayaData;
        novayaData.den = den;
        novayaData.mesyac = mesyac;
        novayaData.god = god;

        double okruglenniyVes = okruglitDo50Gramm(ves);

        int index = naytiIndexPoDate(novayaData);
        if (index != -1) {
            istoriya[index].imya = imya;
            istoriya[index].ves = okruglenniyVes;
        }
        else {
            Nablyudenie novoe;
            novoe.data = novayaData;
            novoe.imya = imya;
            novoe.ves = okruglenniyVes;
            istoriya.push_back(novoe);
        }

        for (int i = 0; i < (int)istoriya.size() - 1; i++) {
            for (int j = i + 1; j < (int)istoriya.size(); j++) {
                if (istoriya[j].data < istoriya[i].data) {
                    Nablyudenie temp = istoriya[i];
                    istoriya[i] = istoriya[j];
                    istoriya[j] = temp;
                }
            }
        }
    }

    double uznatVes(int den, int mesyac, int god) {
        Data iskData;
        iskData.den = den;
        iskData.mesyac = mesyac;
        iskData.god = god;

        int index = naytiIndexPoDate(iskData);
        if (index != -1) {
            return istoriya[index].ves;
        }
        return -1;
    }

    double naytiSredniyVes(string imya, int mesyac = -1, int god = -1) {
        double summa = 0;
        int count = 0;

        for (int i = 0; i < (int)istoriya.size(); i++) {
            if (istoriya[i].imya == imya) {
                if (mesyac == -1 || (istoriya[i].data.mesyac == mesyac && istoriya[i].data.god == god)) {
                    summa = summa + istoriya[i].ves;
                    count = count + 1;
                }
            }
        }

        if (count == 0) return 0;
        return summa / count;
    }

    pair<double, Data> naytiMinimalniyVes(string imya, int mesyac = -1, int god = -1) {
        double minVes = 999999;
        Data minData;
        minData.den = 0;
        minData.mesyac = 0;
        minData.god = 0;
        bool naydeno = false;

        for (int i = 0; i < (int)istoriya.size(); i++) {
            if (istoriya[i].imya == imya) {
                if (mesyac == -1 || (istoriya[i].data.mesyac == mesyac && istoriya[i].data.god == god)) {
                    if (istoriya[i].ves < minVes) {
                        minVes = istoriya[i].ves;
                        minData = istoriya[i].data;
                        naydeno = true;
                    }
                }
            }
        }

        if (!naydeno) {
            pair<double, Data> rez;
            rez.first = -1;
            rez.second.den = 0;
            rez.second.mesyac = 0;
            rez.second.god = 0;
            return rez;
        }

        pair<double, Data> rez;
        rez.first = minVes;
        rez.second = minData;
        return rez;
    }

    pair<double, Data> naytiMaksimalniyVes(string imya, int mesyac = -1, int god = -1) {
        double maxVes = -1;
        Data maxData;
        maxData.den = 0;
        maxData.mesyac = 0;
        maxData.god = 0;
        bool naydeno = false;

        for (int i = 0; i < (int)istoriya.size(); i++) {
            if (istoriya[i].imya == imya) {
                if (mesyac == -1 || (istoriya[i].data.mesyac == mesyac && istoriya[i].data.god == god)) {
                    if (istoriya[i].ves > maxVes) {
                        maxVes = istoriya[i].ves;
                        maxData = istoriya[i].data;
                        naydeno = true;
                    }
                }
            }
        }

        if (!naydeno) {
            pair<double, Data> rez;
            rez.first = -1;
            rez.second.den = 0;
            rez.second.mesyac = 0;
            rez.second.god = 0;
            return rez;
        }

        pair<double, Data> rez;
        rez.first = maxVes;
        rez.second = maxData;
        return rez;
    }

    void sohranitVFile(string imyaFaila) {
        ofstream fail(imyaFaila);
        fail << nachalnayaData.den << " " << nachalnayaData.mesyac << " " << nachalnayaData.god << endl;
        fail << istoriya.size() << endl;

        for (int i = 0; i < (int)istoriya.size(); i++) {
            fail << istoriya[i].data.den << " " << istoriya[i].data.mesyac << " " << istoriya[i].data.god << " "
                << istoriya[i].imya << " " << istoriya[i].ves << endl;
        }
        fail.close();
    }

    void schitatIzFile(string imyaFaila) {
        ifstream fail(imyaFaila);
        istoriya.clear();

        fail >> nachalnayaData.den >> nachalnayaData.mesyac >> nachalnayaData.god;

        int kolvo;
        fail >> kolvo;

        for (int i = 0; i < kolvo; i++) {
            Nablyudenie nab;
            fail >> nab.data.den >> nab.data.mesyac >> nab.data.god >> nab.imya >> nab.ves;
            istoriya.push_back(nab);
        }
        fail.close();
    }
};

int main() {
    VesiyNapolniye vesiy;

    vesiy.ustanovitNachalnuyuData(1, 1, 2024);

    vesiy.zadatNablyudenie(15, 1, 2024, "Mama", 65.3);
    vesiy.zadatNablyudenie(15, 1, 2024, "Papa", 80.25);
    vesiy.zadatNablyudenie(20, 1, 2024, "Syn", 45.8);
    vesiy.zadatNablyudenie(10, 2, 2024, "Mama", 64.9);

    cout << "Ves 15.01.2024: " << vesiy.uznatVes(15, 1, 2024) << " kg" << endl;
    cout << "Sredniy ves Mama: " << vesiy.naytiSredniyVes("Mama") << " kg" << endl;

    pair<double, Data> minRes = vesiy.naytiMinimalniyVes("Mama");
    cout << "Min ves Mama: " << minRes.first << " kg data: " << minRes.second.den << "." << minRes.second.mesyac << "." << minRes.second.god << endl;

    pair<double, Data> maxRes = vesiy.naytiMaksimalniyVes("Syn");
    cout << "Max ves Syn: " << maxRes.first << " kg data: " << maxRes.second.den << "." << maxRes.second.mesyac << "." << maxRes.second.god << endl;

    int chislo_dlya_faila = 42;
    string imyaFaila = "ves_" + to_string(chislo_dlya_faila) + ".txt";
    vesiy.sohranitVFile(imyaFaila);

    VesiyNapolniye vesiy2;
    vesiy2.schitatIzFile(imyaFaila);
    cout << "Zagruzheno iz faila. Ves 15.01.2024: " << vesiy2.uznatVes(15, 1, 2024) << " kg" << endl;

    return 0;
}