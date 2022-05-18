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

    string getNume() const { return nume; }
    void setNume(string nume) { this->nume = nume; }

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
            Animal::citire(in);
            cout << "Danger level-ul este: ";
            in >> dangerLevel;
            cout << "\n\n";
        }
    }

    void afisare(ostream& out){
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

    void combinaHaita(Lup& altLup){
        haita.merge(altLup.haita);
        altLup.haita = this->haita;
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

class SorterAnimale{
public:
    bool operator() (const Animal* a, const Animal* b) const {
        return a->getNume() < b->getNume();
    }
};

class SorterJucarie{
public:
    bool operator() (const Jucarie& a, const Jucarie& b) const {
        return a.getNume() < b.getNume();
    }
};

template<class T = bool>
class Caine: public Pradator{
protected:
    set<Jucarie, SorterJucarie> jucarii;
    T pedigree;
public:
    Caine(){}
    Caine(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici, int dangerLevel, list<Lup*> haita,
        set<Jucarie, SorterJucarie> jucarii, T pedigree):
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

    void adaugaJucarie(const Jucarie& jucarie){
        assert(jucarii.find(jucarie) == jucarii.end());
        jucarii.insert(jucarie);
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
        }
    }

    void afisare(ostream& out){
        out << "Cainele gasit este: \n";
        Animal::afisare(out);
        out << "Danger level-ul este: " << dangerLevel << '\n';
        out << "Pedigree-ul: " << pedigree << '\n';
        if(jucarii.size() == 0)
            out << "Nici-o jucarie pentru aceste caine\n\n\n";
        else{
            out << "Numar jucarii este: " << jucarii.size() << "\n";

            for(auto x : jucarii)
                out << x;

            out << "\n\n";
        }
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
        set<Animal*, SorterAnimale> lupi, caini;

        int stop = 0;

        while(!stop){
            cout << "Buna ziua! Bine ati venit la Laboratorul Animalelor! Va rog alegeti una din optiuniel de mai jos\n";
            cout << "--------------------------------------------------------------------------------------------------\n";
            cout << "0. Exit!";
            cout << "1. Adaugati un lup!\n";
            cout << "2. Afisati informatii despre un lup dupa nume!\n";
            cout << "3. Stergeti un lup dupa nume!\n";
            cout << "4. Afisati informatii despre totii lupii de pana acum!\n";
            cout << "5. Creste un lup dupa nume!\n";
            cout << "6. Uneste haitele a doi lupi dupa nume!\n";
            cout << "7. Adaugati un caine!\n";
            cout << "8. Afisati informatii despre un caine dupa nume!\n";
            cout << "9. Stergeti un caine dupa nume!\n";
            cout << "10. Afisati informatii despre totii cainii de pana acum!\n";
            cout << "11. Creste un caine dupa nume!\n";
            cout << "12. Adauga o jucarie la un caine!\n";
            cout << "13. Sterge o jucarie de la un caine!\n";
            cout << "14. Adauga o avarie la o jucarie a unui caine!\n";
            cout << "15. Afiseaza informatii despre toate jucariile detinute de catre un caine dupa nume!\n";
            cout << "16. Compara doua animale dupa nume!\n";
            cout << "Optiunea aleasa este: ";

            int choice;

            cin >> choice;

            switch(choice){
            case 0:
                stop = 1;
                break;
            case 1:{
                Animal* newLup = static_cast<Animal*>(new Lup);

                cin >> *newLup;

                try{
                    assert(lupi.find(newLup) == lupi.end());

                    lupi.insert(newLup);
                }catch(exception e){
                    cout << "Lupul cu numele acesta exista deja in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 2:{
                cout << "Numele lupului pe care doriti sa-l stergeti: \n";
                string numeLup;
                cin >> numeLup;

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);
                    cout << *lupGasit << '\n';
                }catch(exception e){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 3:{
                cout << "Numele lupului despre care doresti sa aflii informatii: \n";
                string numeLup;
                cin >> numeLup;

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);
                    lupi.erase(lupGasit);
                }catch(exception e){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 4:{
                if(lupi.size() == 0)
                    cout << "Nu exista nici un lup in baza de date!\n";
                else{
                    cout << "Afisam informatiile despre totii lupii din baza de date\n";
                    for(auto lup : lupi)
                        cout << *lup << '\n';

                    break;
                }
            }
            case 5:{
                cout << "Numele lupului pe care doriti sa-l cresteti: \n";
                string numeLup;
                cin >> numeLup;

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);
                    (*lupGasit)->creste();
                }catch(exception e){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 6:{
                string numeLup1, numeLup2;

                cout << "Numele primului lup: \n";
                cin >> numeLup1;

                cout << "Numele celui de-al doilea lup: \n";
                cin >> numeLup2;

                Lup* lupAux1 = new Lup, *lupAux2 = new Lup;
                lupAux1->setNume(numeLup1);
                lupAux2->setNume(numeLup2);
                try{
                    auto lupGasit1 = lupi.find(lupAux1), lupGasit2 = lupi.find(lupAux2);
                    dynamic_cast<Lup*>(*lupGasit1)->combinaHaita(*dynamic_cast<Lup*>(*lupGasit2));
                }catch(exception e){
                    cout << "Unul din cei doi lupi nu exista!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 7:{
                cout << "Intai de toate, spuneti-ne pedigree-ul: ";

                bool eBool, eInt, eString;
                Caine<bool>* boolCaine = new Caine<bool>;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;
                Animal* newCaine;

                eBool = eInt = eString = 1;

                try{
                    bool pedigree;

                    cin >> pedigree;
                }catch(exception e){
                    eBool = 0;
                    int pedigree;

                    cin >> pedigree;
                }catch(exception e){
                    eInt = 0;
                    string pedigree;

                    getline(cin, pedigree);
                }catch(exception e){
                    cout << "Ceva a merst prost!\n";
                    cout << "Incercati o alta optiune!\n";

                    break;
                }

                if(eBool)
                    newCaine = boolCaine;
                else if(eInt)
                    newCaine = intCaine;
                else
                    newCaine = stringCaine;

                cin >> *newCaine;

                try{
                    assert(caini.find(newCaine) == caini.end());

                    caini.insert(newCaine);
                }catch(exception e){
                    cout << "Cainele cu numele acesta exista deja in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 8:{
                cout << "Numele cainelui pe care doriti sa-l stergeti: \n";
                string numeCaine;
                cin >> numeCaine;

                Caine<bool>* boolCaine = new Caine<bool>;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                boolCaine->setNume(numeCaine);
                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineBoolGasit = caini.find(boolCaine);
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);
                    assert(caineBoolGasit != caini.end() || caineIntGasit != caini.end() || caineStringGasit != caini.end());

                    if(caineBoolGasit != caini.end())
                        caini.erase(caineBoolGasit);
                    else if(caineIntGasit != caini.end())
                        caini.erase(caineIntGasit);
                    else
                        caini.erase(caineStringGasit);
                }catch(exception e){
                    cout << "Cainele cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 9:{
                cout << "Numele cainelui despre care doriti sa aflati informatii: \n";
                string numeCaine;
                cin >> numeCaine;

                Caine<bool>* boolCaine = new Caine<bool>;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                boolCaine->setNume(numeCaine);
                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineBoolGasit = caini.find(boolCaine);
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    assert(caineBoolGasit != caini.end() || caineIntGasit != caini.end() || caineStringGasit != caini.end());

                    if(caineBoolGasit != caini.end())
                        cout << **caineBoolGasit << '\n';
                    else if(caineIntGasit != caini.end())
                        cout << **caineIntGasit << '\n';
                    else
                        cout << **caineStringGasit << '\n';
                }catch(exception e){
                    cout << "Cainele cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 10:{
                if(caini.size() == 0)
                    cout << "Nu exista nici un caine in baza de date!\n";
                else{
                    cout << "Afisam informatiile despre totii cainii din baza de date\n";
                    for(auto caine : caini)
                        cout << *caine << '\n';

                    break;
                }
            }
            case 11:{
                cout << "Numele cainelui pe care doriti sa-l cresteti: \n";
                string numeCaine;
                cin >> numeCaine;

                Caine<bool>* boolCaine = new Caine<bool>;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                boolCaine->setNume(numeCaine);
                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineBoolGasit = caini.find(boolCaine);
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    assert(caineBoolGasit != caini.end() || caineIntGasit != caini.end() || caineStringGasit != caini.end());

                    if(caineBoolGasit != caini.end())
                        (*caineBoolGasit)->creste();
                    else if(caineIntGasit != caini.end())
                        (*caineIntGasit)->creste();
                    else
                        (*caineStringGasit)->creste();
                }catch(exception e){
                    cout << "Cainele cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 12:{
                Jucarie jucarie;

                cin >> jucarie;

                cout << "Numele cainelui la care vreti sa adaugati jucaria: ";
                string numeCaine;
                cin >> numeCaine;

                Caine<bool>* boolCaine = new Caine<bool>;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                boolCaine->setNume(numeCaine);
                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    try{
                        auto caineBoolGasit = caini.find(boolCaine);
                        auto caineIntGasit = caini.find(intCaine);
                        auto caineStringGasit = caini.find(stringCaine);

                        assert(caineBoolGasit != caini.end() || caineIntGasit != caini.end() || caineStringGasit != caini.end());
                    }catch(exception e){
                        cout << "Cainele cautat nu exista!\n";
                        cout << "Incercati alta optiune!\n";
                    }

                    auto caineBoolGasit = caini.find(boolCaine);
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineBoolGasit != caini.end())
                        dynamic_cast<Caine<bool>*>(*caineBoolGasit)->adaugaJucarie(jucarie);
                    else if(caineIntGasit != caini.end())
                        dynamic_cast<Caine<int>*>(*caineIntGasit)->adaugaJucarie(jucarie);
                    else
                        dynamic_cast<Caine<string>*>(*caineStringGasit)->adaugaJucarie(jucarie);
                }catch(exception e){
                    cout << "Jucaria pe care vrei s-o adaugi exista deja pentru caine\n";
                    cout << "Incercati alta optiune!\n";
                }

                break;
            }
            case 13:{

            }
        }
    }
};

Menu* Menu::menu = NULL;

int main(){

}
