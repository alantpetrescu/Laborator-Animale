#include <bits/stdc++.h>

using namespace std;

class Animal{
protected:
    string nume;
    int varsta;
    float masa, inaltime;
    int viteza;
    vector<string> caracteristici;
public:
    Animal(){}
    Animal(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici):
        nume(nume), varsta(varsta), masa(masa), inaltime(inaltime), viteza(viteza), caracteristici(caracteristici){}
    Animal(const Animal& animal):
        nume(animal.nume), varsta(animal.varsta), masa(animal.masa), inaltime(animal.inaltime), viteza(animal.viteza), caracteristici(animal.caracteristici){}
    Animal& operator = (const Animal& animal){
        if(this != &animal){
            nume = animal.nume;
            varsta = animal.varsta;
            masa = animal.masa;
            inaltime = animal.inaltime;
            viteza = animal.viteza;
            caracteristici = animal.caracteristici;
        }

        return *this;
    }

    virtual void cresteMasa() = 0;
    virtual void cresteInaltime() = 0;
    virtual void cresteViteza() = 0;

    void creste(){
        cresteMasa();
        cresteInaltime();
        cresteViteza();
    }

    virtual void citire(istream& in){
        if(typeid(in) == typeid(ifstream)){
            in >> nume >> varsta >> masa >> inaltime >> viteza;
            int nrCaracteristici;

            in >> nrCaracteristici;
            caracteristici.clear();

            for(int i = 0; i < nrCaracteristici; i++){
                string x;

                getline(in, x);
                caracteristici.emplace_back(x);
            }
        }else{
            cout << "Nume: ";
            in >> nume;
            cout << "varsta: ";
            in >> varsta;
            cout << "masa: ";
            in >> masa;
            cout << "inaltime: ";
            in >> inaltime;
            cout << "viteza: ";
            in >> viteza;
            cout << "Nr. caracteristici: ";

            int nrCaracteristici;
            in >> nrCaracteristici;

            caracteristici.clear();

            cout << "Caracteristicile (cate una pe o linie): \n";
            for(int i = 0; i < nrCaracteristici; i++){
                string x;

                getline(in, x);
                caracteristici.emplace_back(x);
            }
        }
    }

    virtual void afisare(ostream& out){
        out << "Nume: " << nume << '\n';
        out << "varsta: " << varsta << '\n';
        out << "masa: " << masa << '\n';
        out << "inaltime: " << inaltime << '\n';
        out << "viteza: " << viteza << '\n';
        out << "Nr. caracteristici: ";

        int nrCaracteristici = caracteristici.size();
        out << nrCaracteristici;

        cout << "Caracteristicile (cate una pe o linie): \n";
        for(int i = 0; i < nrCaracteristici; i++)
            out << "Caracteristica #" << i << ": " << caracteristici[i] << '\n';
    }

    friend istream& operator >>(istream& in, Animal& animal){
        animal.citire(in);

        return in;
    }

    friend ostream& operator <<(ostream& out, Animal& animal){
        animal.afisare(out);

        return out;
    }

    virtual ~Animal() = 0;
};

Animal::~Animal(){
    cout << "Animal distrus";
}

class Pradator: public Animal{
protected:
    int dangerLevel;
public:
    Pradator(){}
    Pradator(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici, int dangerLevel):
        Animal(nume, varsta, masa, inaltime, viteza, caracteristici), dangerLevel(dangerLevel){}
    Pradator(const Pradator& pradator):
        Animal(pradator.nume, pradator.varsta, pradator.masa, pradator.inaltime, pradator.viteza, pradator.caracteristici),
        dangerLevel(pradator.dangerLevel){}
    Pradator& operator = (const Pradator& pradator){
        if(this != &pradator){
            nume = pradator.nume;
            varsta = pradator.varsta;
            masa = pradator.masa;
            inaltime = pradator.inaltime;
            viteza = pradator.viteza;
            caracteristici = pradator.caracteristici;
            dangerLevel = pradator.dangerLevel;
        }

        return *this;
    }

    void cresteMasa(){ masa += 2.5; }
    void cresteInaltime(){ inaltime += 0.2; }
    void cresteViteza(){ viteza += 1; }

    virtual int vaneaza() = 0;
    virtual int eAlintat() = 0;

    float afiseazaNivelulDeFericire(){
        return vaneaza() * 0.7 + eAlintat() * 0.3;
    }

    void citire(istream& in){
        if(typeid(in) == typeid(ifstream)){
            Animal::citire(in);
            in >> dangerLevel;
        }else{
            cout << "Pradatorul citit este: \n";
            Animal::citire(in);
            cout << "Danger level-ul este: ";
            in >> dangerLevel;
            cout << "\n\n";
        }
    }

    void afisare(ostream& out){
        out << "Pradatorul gasit este: \n";
        Animal::afisare(out);
        out << "Danger level-ul este: ";
        out << dangerLevel << "\n\n\n";
    }

    friend istream& operator >>(istream& in, Pradator& pradator){
        pradator.citire(in);

        return in;
    }

    friend ostream& operator <<(ostream& out, Pradator& pradator){
        pradator.afisare(out);

        return out;
    }
};

class Lup: public Pradator{
protected:
    list<Lup*> haita;
public:
    Lup(){}
    Lup(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici, int dangerLevel, list<Lup*> haita):
        Pradator(nume, varsta, masa, inaltime, viteza, caracteristici, dangerLevel), haita(haita){}
    Lup(const Lup& lup):
        Pradator(lup.nume, lup.varsta, lup.masa, lup.inaltime, lup.viteza, lup.caracteristici, lup.dangerLevel),
        haita(lup.haita){}
    Lup& operator = (const Lup& lup){
        if(this != &lup){
            nume = lup.nume;
            varsta = lup.varsta;
            masa = lup.masa;
            inaltime = lup.inaltime;
            viteza = lup.viteza;
            caracteristici = lup.caracteristici;
            dangerLevel = lup.dangerLevel;
            haita = lup.haita;
        }

        return *this;
    }

    int vaneaza(){
        return (haita.size() + 1) * 2;
    }

    int eAlintat(){
        return 100 / (haita.size() + 1);
    }

    void citire(istream& in){
        if(typeid(in) == typeid(ifstream))
            Pradator::citire(in);
        else{
            cout << "Lupul citit este: \n";
            Animal::citire(in);
            cout << "Danger level-ul este: ";
            in >> dangerLevel;
            cout << "\n\n";
        }
    }

    void afisare(ostream& out){
        out << "Lupul gasit este: \n";
        Animal::afisare(out);
        out << "Danger level-ul este: " << dangerLevel << '\n';
        out << "Numarul de lupi din haita este: " << haita.size() << '\n';
        cout << "\n\n";
    }

    friend istream& operator >>(istream& in, Lup& lup){
        lup.citire(in);

        return in;
    }

    friend ostream& operator <<(ostream& out, Lup& lup){
        lup.afisare(out);

        return out;
    }

    ~Lup(){
        cout << "Un lup a fost omorat!\n";
    }
};

class Jucarie{
private:
    string nume;
    float pret;
    map<string, float> stricaciuni;
public:
    Jucarie(){}
    Jucarie(string nume, float pret, map<string, float> stricaciuni):
        nume(nume), pret(pret), stricaciuni(stricaciuni){}
    Jucarie(const Jucarie& jucarie):
        nume(jucarie.nume), pret(jucarie.pret), stricaciuni(jucarie.stricaciuni){}
    Jucarie& operator = (const Jucarie& jucarie){
        if(this != &jucarie){
            nume = jucarie.nume;
            pret = jucarie.pret;
            stricaciuni = jucarie.stricaciuni;
        }

        return *this;
    }

    string getNume() const { return nume; }

    friend istream& operator >> (istream& in, Jucarie& jucarie){
        if(typeid(in) == typeid(ifstream)){
            in >> jucarie.nume >> jucarie.pret;
        }else{
            cout << "Jucaria nou adusa este: \n";
            cout << "Nume: ";
            in >> jucarie.nume;
            cout << "Pret: ";
            in >> jucarie.pret;
        }

        return in;
    }

    friend ostream& operator << (ostream& out, Jucarie& jucarie){
        out << "Jucaria cautata este: \n";
        out << "Nume: " << jucarie.nume << '\n';
        out << "Pret: " << jucarie.pret << '\n';

        if(jucarie.stricaciuni.size()){
            int nrStricaciuni;

            nrStricaciuni = jucarie.stricaciuni.size();

            out << "Nr. stricaciuni: " << nrStricaciuni << 'n';
            out << "Stricaciuni: \n";

            for(auto stricaciune : jucarie.stricaciuni){
                out << "Pretext: " << stricaciune.first << '\n';
                out << "Reparatie: " << stricaciune.second << '\n';
            }
        }

        return out;
    }

    ~Jucarie(){
        cout << "O jucarie a fost distrusa complet de un caine!\n";
    }
};

class Sorter{
public:
    bool operator() (const Jucarie& a, const Jucarie& b) const {
        return a.getNume() < b.getNume();
    }
};

template<class T = bool>
class Caine: public Pradator{
protected:
    set<Jucarie, Sorter> jucarii;
    T pedigree;
public:
    Caine(){}
    Caine(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici, int dangerLevel, list<Lup*> haita,
        set<Jucarie, Sorter> jucarii, T pedigree):
        Pradator(nume, varsta, masa, inaltime, viteza, caracteristici, dangerLevel), jucarii(jucarii), pedigree(pedigree){}
    Caine(const Caine& caine):
        Pradator(caine.nume, caine.varsta, caine.masa, caine.inaltime, caine.viteza, caine.caracteristici, caine.dangerLevel),
        jucarii(caine.jucarii), pedigree(caine.pedigree){}
    Caine& operator = (const Caine& caine){
        if(this != &caine){
            nume = caine.nume;
            varsta = caine.varsta;
            masa = caine.masa;
            inaltime = caine.inaltime;
            viteza = caine.viteza;
            caracteristici = caine.caracteristici;
            dangerLevel = caine.dangerLevel;
            jucarii = caine.jucarii;
            pedigree = caine.pedigree;
        }

        return *this;
    }

    int vaneaza(){
        return 3;
    }

    int eAlintat();

    void citire(istream& in){
        if(typeid(in) == typeid(ifstream))
            Pradator::citire(in);
        else{
            cout << "Cainele citit este: \n";
            Animal::citire(in);
            cout << "Danger level-ul este: ";
            in >> dangerLevel;
            cout << "Pedigree-ul este: ";
            in >> pedigree;
        }
    }

    void afisare(ostream& out){
        out << "Lupul gasit este: \n";
        Animal::afisare(out);
        out << "Danger level-ul este: ";
        out << dangerLevel << "\n";
        cout << "Numar jucarii este: " << jucarii.size() << "\n\n\n";
    }

    friend istream& operator >>(istream& in, Caine& caine){
        caine.citire(in);

        return in;
    }

    friend ostream& operator <<(ostream& out, Caine& caine){
        caine.afisare(out);

        return out;
    }

    ~Caine(){
        cout << "Un caine tocmai a fost mancat de un chinez!\n";
    }
};

template<> int Caine<bool>::eAlintat(){
    return pedigree;
}

template<> int Caine<int>::eAlintat(){
    return pedigree;
}

template<> int Caine<string>::eAlintat(){
    if(pedigree == "Golden Retriever")
        return 100;
    if(pedigree == "Husky")
        return 200;
    if(pedigree == "Shiba Inu")
        return 500;

    return -1;
}

class Menu{
private:
    static Menu* menu;
    Menu(){}
public:
    static Menu* getInstance(){
        if(!menu)
            menu = new Menu;

        return menu;
    }

    void showMenu(){
        set<Animal, Sorter> animals;
        set<Pradator, Sorter> predators;
        set<Lup, Sorter> lupi;
        set<Caine<bool>, Sorter> cainiBool;
        set<Caine<int>, Sorter> cainiInt;
        set<Caine<string>, Sorter> cainiString;

        int stop = 0;

        while(!stop){
            cout << "Buna ziua! Bine ati venit la Laboratorul Animalelor! Va rog alegeti una din optiuniel de mai jos\n";
            cout << "--------------------------------------------------------------------------------------------------\n";
            cout << "0. Exit!";
            cout << "1. Adaugati un animal neidentificat!\n";
            cout << "2. Afisati informatii despre un animal neidentificat dupa nume!\n";
            cout << "3. Stergeti un animal neidentificat dupa nume!\n";
            cout << "4. Afisati informatii despre toate animalele neidentificate de pana acum!\n";
            cout << "5. Adaugati un pradator!\n";
            cout << "6. Afisati informatii despre un pradator dupa nume!\n";
            cout << "7. Stergeti un pradator dupa nume!\n";
            cout << "8. Afisati informatii despre totii pradatorii de pana acum!\n";
            cout << "9. Creste un animal dupa nume!\n";
            cout << "10. Adaugati un lup!\n";
            cout << "11. Afisati informatii despre un lup dupa nume!\n";
            cout << "12. Stergeti un lup dupa nume!\n";
            cout << "13. Afisati informatii despre totii lupii de pana acum!\n";
            cout << "14. Creste un lup dupa nume!\n";
            cout << "15. Uneste haitele a doi lupi dupa nume!\n";
            cout << "16. Adaugati un caine!\n";
            cout << "17. Afisati informatii despre un caine dupa nume!\n";
            cout << "18. Stergeti un caine dupa nume!\n";
            cout << "19. Afisati informatii despre totii cainii de pana acum!\n";
            cout << "20. Creste un caine dupa nume!\n";
            cout << "21. Adauga o jucarie la un caine!\n";
            cout << "22. Sterge o jucarie de la un caine!\n";
            cout << "23. Adauga o avarie la o jucarie a unui caine!\n";
            cout << "24. Afiseaza informatii despre toate jucariile detinute de catre un caine dupa nume!\n";
            cout << "Optiunea aleasa este: ";

            int choice;

            cin >> choice;

            switch(choice){
            case 0:
                stop = 1;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                break;
            case 17:
                break;
            case 18:
                break;
            case 19:
                break;
            case 20:
                break;
            case 21:
                break;
            case 22:
                break;
            case 23:
                break;
            case 24:
                break;
            }
        }
    }
};

Menu* Menu::menu = NULL;

int main(){

}
