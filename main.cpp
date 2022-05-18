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
            getline(in, nume);
            in >> varsta >> masa >> inaltime >> viteza;
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
            getline(in, nume);
            getline(in, nume);
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

            string x;

            getline(in, x);
            for(int i = 0; i < nrCaracteristici; i++){
                cout << "Caracteristica #" << i << ": ";
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
        out << nrCaracteristici << '\n';

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
    list<string> haita;
public:
    Lup(){}
    Lup(string nume, int varsta, float masa, float inaltime, int viteza, vector<string> caracteristici, int dangerLevel, list<string> haita):
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

    void adaugaLaHaita(Lup* lup){
        try{
            bool semafor = 1;

            for(auto x = haita.begin(); semafor && x != haita.end(); ++x)
                if((*x) == lup->nume)
                    semafor = 0;

            if(!semafor)
                throw(lup->nume);
            else
                haita.push_back(lup->nume);
        }catch(string nume){
            cout << "Lupul " << nume << " este deja in haita!\n";
        }
    }

    int vaneaza(){
        return haita.size() * 2;
    }

    int eAlintat(){
        return 100 / haita.size();
    }

    void combinaHaita(Lup& altLup){
        cout << *haita.begin() << '\n';
        cout << *altLup.haita.begin() << '\n';
        haita.merge(altLup.haita);
        for (auto it = haita.begin(); it != haita.end(); ++it)
            cout << *it << "\n";
        altLup.haita = this->haita;
        for (auto it = altLup.haita.begin(); it != altLup.haita.end(); ++it)
            cout << *it << "\n";
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
        out << "Numarul de lupi din haita lupului " << nume << " este: " << haita.size() << '\n';
        out << "Lupii din haita fiind: ";

        if(haita.size() == 1)
            out << (*haita.begin());
        else if(haita.size() == 2)
            out << *haita.begin() << " , " << *(++haita.begin());
        else{
            out << *haita.begin() << " , ";

            list<string>::iterator i = haita.begin(), j = haita.end();
            i++;
            j--;
            j--;

            while(i != j){
                out << (*i) << ", ";
                i++;
            }

            if(haita.size() > 1)
                out << (*i);
        }

        cout << "\n\n\n";
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

    void adaugaAvarie(string textAvarie, float pretAvarie){
        assert(stricaciuni.find(textAvarie) == stricaciuni.end());
        stricaciuni[textAvarie] = pretAvarie;
    }

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

template<class T = int>
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

    void setPedigree(T pedigree) { this->pedigree = pedigree; }

    void adaugaJucarie(const Jucarie& jucarie){
        assert(jucarii.find(jucarie) == jucarii.end());
        jucarii.insert(jucarie);
    }

    void stergeJucarie(const Jucarie& jucarie){
        assert(jucarii.find(jucarie) != jucarii.end());
        jucarii.erase(jucarie);
    }

    void adaugaAvarieLaJucarie(Jucarie& jucarie, string textAvarie, float pretAvarie){
        assert(jucarii.find(jucarie) != jucarii.end());
        try{
            jucarie.adaugaAvarie(textAvarie, pretAvarie);
        }catch(exception e){
            cout << "Avaria exista deja pe jucarie!\n";
        }
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
    static Menu* object;
    Menu(){}
public:
    static Menu* getInstance(){
        if(!object)
            object = new Menu();

        return object;
    }

    void showMenu(){
        set<Animal*, SorterAnimale> lupi, caini;

        int stop = 0;

        cin.exceptions(istream::failbit);
        while(!stop){
            cout << "Buna ziua! Bine ati venit la Laboratorul Animalelor! Va rog alegeti una din optiuniel de mai jos\n";
            cout << "--------------------------------------------------------------------------------------------------\n";
            cout << "0. Exit!\n";
            cout << "1. Adaugati un lup!\n";
            cout << "2. Stergeti un lup dupa nume!\n";
            cout << "3. Afisati informatii despre un lup dupa nume!\n";
            cout << "4. Afisati informatii despre totii lupii de pana acum!\n";
            cout << "5. Creste un lup dupa nume!\n";
            cout << "6. Uneste haitele a doi lupi dupa nume!\n";
            cout << "7. Adaugati un caine!\n";
            cout << "8. Stergeti un caine dupa nume!\n";
            cout << "9. Afisati informatii despre un caine dupa nume!\n";
            cout << "10. Afisati informatii despre totii cainii de pana acum!\n";
            cout << "11. Creste un caine dupa nume!\n";
            cout << "12. Adauga o jucarie la un caine!\n";
            cout << "13. Sterge o jucarie de la un caine!\n";
            cout << "14. Adauga o avarie la o jucarie a unui caine!\n";
            cout << "--------------------------------------------------------------------------------------------------\n";
           // cout << "15. Afiseaza informatii despre toate jucariile detinute de catre un caine dupa nume!\n";
           // cout << "16. Compara doua animale dupa nume!\n";
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
                    if(lupi.find(newLup) != lupi.end())
                        throw(newLup->getNume());

                    dynamic_cast<Lup*>(newLup)->adaugaLaHaita(dynamic_cast<Lup*>(newLup));
                    lupi.insert(newLup);
                }catch(string nume){
                    cout << "Lupul " << nume << " exista deja in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n";
                }

                break;
            }
            case 2:{
                cout << "Numele lupului pe care doriti sa-l stergeti: ";
                string numeLup;
                getline(cin, numeLup);
                getline(cin, numeLup);

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);

                    if(lupGasit == lupi.end())
                        throw(numeLup);

                    cout << **lupGasit << '\n';
                    lupi.erase(lupGasit);

                    cout << "Lupul " << numeLup << " a fost sters din baza de date!\n";
                }catch(string x){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 3:{
                cout << "Numele lupului despre care doresti sa aflii informatii: ";
                string numeLup;
                getline(cin, numeLup);
                getline(cin, numeLup);

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);

                    if(lupGasit == lupi.end())
                        throw(numeLup);

                    cout << **lupGasit;
                }catch(string x){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
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
                cout << "Numele lupului pe care doriti sa-l cresteti: ";
                string numeLup;
                getline(cin, numeLup);
                getline(cin, numeLup);

                Lup* lupAux = new Lup;
                lupAux->setNume(numeLup);
                try{
                    auto lupGasit = lupi.find(lupAux);

                    if(lupGasit == lupi.end())
                        throw(numeLup);

                    (*lupGasit)->creste();
                    cout << "Lupul " << numeLup << " tocmai a crescut!\n\n\n";
                }catch(exception e){
                    cout << "Lupul cu numele acesta nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 6:{
                string numeLup1, numeLup2;

                cout << "Numele primului lup: ";
                getline(cin, numeLup1);
                getline(cin, numeLup1);

                cout << "Numele celui de-al doilea lup: ";
                getline(cin, numeLup2);

                Lup* lupAux1 = new Lup, *lupAux2 = new Lup;
                lupAux1->setNume(numeLup1);
                lupAux2->setNume(numeLup2);
                try{
                    auto lupGasit1 = lupi.find(lupAux1), lupGasit2 = lupi.find(lupAux2);

                    if(lupGasit1 == lupi.end())
                        throw(0);
                    else if(lupGasit2 == lupi.end())
                        throw(1);

                    dynamic_cast<Lup*>(*lupGasit1)->combinaHaita(*dynamic_cast<Lup*>(*lupGasit2));
                    cout << "Haitele celor doi lupi au s-au contopit!\n\n\n";
                }catch(int care){
                    if(care == 0)
                        cout << "Primul lup n-a fost gasit!\n";
                    else
                        cout << "Al doilea lup n-a fost gasit!\n";

                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 7:{
                cout << "Intai de toate, spuneti-ne pedigree-ul: ";

                bool eInt, eString;
                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;
                Animal* newCaine;

                eInt = eString = 1;

                try{
                    string pedigree;

                    getline(cin, pedigree);
                    getline(cin, pedigree);

                    int nr = 0;

                    for(auto x : pedigree)
                        if(x < '0' || x > '9')
                            throw(0);
                        else
                            nr = nr * 10 + x - '0';

                    intCaine->setPedigree(nr);
                }catch(int x){
                    eInt = 0;
                    string pedigree;


                    stringCaine->setPedigree(pedigree);
                }

                if(eInt)
                    newCaine = intCaine;
                else
                    newCaine = stringCaine;

                cin >> *newCaine;

                try{
                    if(caini.find(newCaine) != caini.end())
                        throw(newCaine->getNume());

                    caini.insert(newCaine);
                }catch(string nume){
                    cout << "Cainele " << nume << "exista deja in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 8:{
                cout << "Numele cainelui pe care doriti sa-l stergeti: \n";
                string numeCaine;
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);
                    if(caineIntGasit == caini.end() && caineStringGasit == caini.end())
                        throw(numeCaine);

                    if(caineIntGasit != caini.end())
                        caini.erase(caineIntGasit);
                    else
                        caini.erase(caineStringGasit);

                    cout << "Cainele a fost sters cu succes!\n\n\n";
                }catch(string nume){
                    cout << "Cainele " << nume <<  "nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 9:{
                cout << "Numele cainelui despre care doriti sa aflati informatii: \n";
                string numeCaine;
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineIntGasit == caini.end() && caineStringGasit == caini.end())
                        throw(numeCaine);

                    if(caineIntGasit != caini.end())
                        cout << **caineIntGasit << '\n';
                    else
                        cout << **caineStringGasit << '\n';
                }catch(string nume){
                    cout << "Cainele " << nume << "nu exista in baza  de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
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
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineIntGasit == caini.end() && caineStringGasit == caini.end())
                        throw(numeCaine);

                    if(caineIntGasit != caini.end())
                        (*caineIntGasit)->creste();
                    else
                        (*caineStringGasit)->creste();
                }catch(string nume){
                    cout << "Cainele " << nume << "nu exista in baza de date!\n";
                    cout << "Va rugam sa alegeti altceva!\n\n\n";
                }

                break;
            }
            case 12:{
                Jucarie jucarie;

                cin >> jucarie;

                cout << "Numele cainelui la care vreti sa adaugati jucaria: ";
                string numeCaine;
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    try{
                        auto caineIntGasit = caini.find(intCaine);
                        auto caineStringGasit = caini.find(stringCaine);

                        assert(caineIntGasit != caini.end() || caineStringGasit != caini.end());
                    }catch(exception e){
                        cout << "Cainele cautat nu exista!\n";
                        cout << "Incercati alta optiune!\n";
                    }

                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineIntGasit != caini.end())
                        dynamic_cast<Caine<int>*>(*caineIntGasit)->adaugaJucarie(jucarie);
                    else
                        dynamic_cast<Caine<string>*>(*caineStringGasit)->adaugaJucarie(jucarie);
                }catch(exception e){
                    cout << "Jucaria pe care vrei s-o adaugi exista deja pentru caine\n";
                    cout << "Incercati alta optiune!\n\n\n";
                }

                break;
            }
            case 13:{
                Jucarie jucarie;

                cin >> jucarie;

                cout << "Numele cainelui de la care vrei sa stergi jucaria: ";
                string numeCaine;
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    try{
                        auto caineIntGasit = caini.find(intCaine);
                        auto caineStringGasit = caini.find(stringCaine);

                        if(caineIntGasit == caini.end() && caineStringGasit == caini.end())
                            throw(numeCaine);
                    }catch(string nume){
                        cout << "Cainele " << nume << "nu exista!\n";
                        cout << "Incercati alta optiune!\n";
                    }

                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineIntGasit != caini.end())
                        dynamic_cast<Caine<int>*>(*caineIntGasit)->stergeJucarie(jucarie);
                    else
                        dynamic_cast<Caine<string>*>(*caineStringGasit)->stergeJucarie(jucarie);
                }catch(exception e){
                    cout << "Jucaria pe care vrei s-o adaugi nu exista pentru caine\n";
                    cout << "Incercati alta optiune!\n\n\n";
                }

                break;
            }
            case 14:{
                Jucarie jucarie;

                cin >> jucarie;

                cout << "Numele cainelui de la care vrei sa stergi jucaria: ";
                string numeCaine;
                getline(cin, numeCaine);
                getline(cin, numeCaine);

                Caine<int>* intCaine = new Caine<int>;
                Caine<string>* stringCaine = new Caine<string>;

                intCaine->setNume(numeCaine);
                stringCaine->setNume(numeCaine);

                try{
                    auto caineIntGasit = caini.find(intCaine);
                    auto caineStringGasit = caini.find(stringCaine);

                    if(caineIntGasit == caini.end() && caineStringGasit != caini.end())
                        throw(numeCaine);
                }catch(string nume){
                    cout << "Cainele " << nume << "nu exista!\n";
                    cout << "Incercati alta optiune!\n\n\n";
                }

                auto caineIntGasit = caini.find(intCaine);
                auto caineStringGasit = caini.find(stringCaine);

                if(caineIntGasit != caini.end()){
                    cout << "Avaria pe care vrei s-o adaugi(text): ";
                    string textAvarie;
                    cin >> textAvarie;

                    cout << "Pretul repararii avariei(float): ";
                    float pretAvarie;
                    cin >> pretAvarie;

                    dynamic_cast<Caine<int>*>(*caineIntGasit)->adaugaAvarieLaJucarie(jucarie, textAvarie, pretAvarie);
                }
                else if(caineStringGasit != caini.end()){
                    cout << "Avaria pe care vrei s-o adaugi(text): ";
                    string textAvarie;
                    cin >> textAvarie;

                    cout << "Pretul repararii avariei(float): ";
                    float pretAvarie;
                    cin >> pretAvarie;

                    dynamic_cast<Caine<string>*>(*caineStringGasit)->adaugaAvarieLaJucarie(jucarie, textAvarie, pretAvarie);
                }

                break;
            }
            default:
                cout << "Aceasta optiune nu exista!\n\n\n";
            }
        }
    }
};

Menu* Menu::object = 0;

int main(){
    Menu* menu = Menu::getInstance();

    menu->showMenu();

    return 0;
}
