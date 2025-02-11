#include "Przedmiot.hpp"
#include "Platformy.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <random>
#include <limits>
using namespace std;

const string red("\033[0;31m");                                         const string magenta("\033[0;35m");                                     const string color_reset("\033[0m");


Grailed::Grailed() : buzzword({"BandTee","Vintage","Hype","Streetwear","HighEnd","Designer","y2k","90s","TEE","Rare","Classic","AOP","OG","Oversize","Baggy","Archive","Luxury","AvantGarde"})
{}
Vinted::Vinted() : baza_slow({"vintage","y2k", "aesthetic", "lana", "core", "90s", "elegant", "baggy", "pinterest", "goth", "chamberlain", "oldmoney", "oversize", "itgirl"}) 
{}
Vestiaire::Vestiaire()
{}
vector<Przedmiot> Grailed::przedmioty_grailed;
vector<Przedmiot> Vinted::przedmioty_vinted;
vector<Przedmiot> Vestiaire::przedmioty_vestiaire;
std::vector<std::pair<time_t, Vestiaire::wlasciwosci>> Vestiaire::historia;

map<int, double> Vinted::cennik;
map<int, Grailed::wlasciwosci> Grailed::informacje;
map<int,double> Grailed::cennik;
map<int, double> Vestiaire::cennik;


void Grailed::change_price(int id,int nowa)
{
    if(informacje.find(id)==informacje.end())
    {
        cout << "Nie ma przedmiotu o takim id\n";
        return;
    }
    informacje[id].cena=nowa;
}


void Grailed::wystaw2(Przedmiot& k)
{
	przedmioty_grailed.push_back(k);
}


void Vestiaire::wystaw2(Przedmiot& k)
{
	przedmioty_vestiaire.push_back(k);
}

void Vinted::wystaw2(Przedmiot& k)
{
	przedmioty_vinted.push_back(k);
}


//tutaj ma byc wszystko ladnie opisane 🙂
void Grailed::wystaw_przedmiot(Przedmiot& k)
{
    przedmioty_grailed.push_back(k);
    cout << "Podaj cene w dolarach\n";
    double cand=0;
    while (true) {
        cin >> cand;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << red << "Zly input! Podaj liczbe:\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    int id=k.get_id();
    informacje[id].cena=cand;
    set_shipping(id); 
    set_tags(id);
}

//done
string Grailed::generate_name(const Przedmiot& k)
{
    string name=k.get_kategoria();
    vector<int> indeksy(buzzword.size());
    for (int i=0;i<buzzword.size();++i)
        indeksy[i]=i;

    random_device rd;
    mt19937 g(rd());
    shuffle(indeksy.begin(),indeksy.end(),g);

    for (int i=0;i<8 && i<buzzword.size(); ++i) {
        name+=buzzword[indeksy[i]] + " ";
    }

    if (!name.empty() && name.back() == ' ') 
        name.pop_back();
    return name;
}

void Grailed::sold(int id)
{
    if(informacje.find(id)==informacje.end())
        return;
    for(auto it=przedmioty_grailed.begin();it!=przedmioty_grailed.end();++it)
    {
        if(it->get_id()==id)
        {
            przedmioty_grailed.erase(it);
            break;
        }
    }
            
    
    informacje.erase(id);
    Vestiaire vestiaire;
    Vinted vinted;
    vestiaire.sold(id);
    vinted.sold(id);
}
//done
void Grailed::show_all()
{
    if(przedmioty_grailed.empty())
    {
        cout << "BRAK ELEMENTOW\n";
        return;
    }
    for(const auto& item:przedmioty_grailed)
            item.print_properties();
}

void Grailed::do_pliku()
{
    fstream plik("grailed.txt", ios::out);
    if (plik.is_open())
    {
        for (const auto &entry : historia)
        {
            plik << entry.first << " " << entry.second.cena << endl;
            for (const auto &cost : entry.second.shipping_cost)
            {
                plik << cost.first << " " << cost.second << endl;
            }
            for (int i = 0; i < 10; ++i)
            {
                plik << entry.second.tags[i] << endl;
            }
        }
        plik.close();
    }
    else
    {
        cerr << "Unable to open file grailed.txt" << endl;
    }
}

void Grailed::z_pliku()
{
    fstream plik("grailed.txt", ios::in);
    if (plik.is_open())
    {
        historia.clear();
        time_t czas;
        wlasciwosci wl;
        while (plik >> czas >> wl.cena)
        {
	    pair<string,double> p;
            for(int i=0;i<7;++i)
	    {
              	plik >> p.first >> p.second;
		wl.shipping_cost.push_back(p);
	    }
            for (int i=0;i<10;++i)
            {
                plik >> wl.tags[i];
            }
            historia.emplace_back(czas, wl);
        }
        plik.close();
    }
    else
    {
        cerr << "Unable to open file grailed.txt" << endl;
    }
}

string Vinted::generate_name(const Przedmiot& k) 
{
    string name = k.get_kategoria();

    vector<int> indeksy(baza_slow.size());
    for (int i=0;i<baza_slow.size();++i)
        indeksy[i] = i;

    random_device rd;
    mt19937 g(rd());
    shuffle(indeksy.begin(), indeksy.end(), g);

    for(int i=0;i<8 && i<baza_slow.size();++i)
    {
        name += baza_slow[indeksy[i]]+" ";
    }

    if (!name.empty() && name.back()==' ') 
        name.pop_back();

    return name;
}

void Vinted::change_price(int id,int nowa)
{
    if(cennik.find(id)==cennik.end())
    {
        cout << "Nie ma przedmiotu o takim id\n";
        return;
    }
    cennik[id]=nowa;
}


void Vinted::sold(int id)
{
    if(cennik.find(id)==cennik.end())
        return;
    for(auto it=przedmioty_vinted.begin(); it!=przedmioty_vinted.end();++it)
    {
        if(it->get_id()==id)
        {
            przedmioty_vinted.erase(it);
            break;
        }
    }
    cennik.erase(id);
    
    Grailed g;
    Vestiaire v;
    v.sold(id);
    g.sold(id);
}

void Grailed::set_shipping(int id)
{
	int cena;
	cout << "Podaj koszt przesyłki dla Afryki\n";
	cin >> cena;
	informacje[id].shipping_cost.push_back(make_pair("Afryka",cena));
	cout << "Koszt dla Europy\n";
	cin >> cena;
	informacje[id].shipping_cost.push_back(make_pair("Europa",cena));
	cout << "USA\n";
        cin >> cena;
        informacje[id].shipping_cost.push_back(make_pair("USA",cena));
	cout << "UK\n";
        cin >> cena;
        informacje[id].shipping_cost.push_back(make_pair("UK",cena));
	cout << "Azja\n";
        cin >> cena;
        informacje[id].shipping_cost.push_back(make_pair("Azja",cena));
	cout << "Australia\n";
        cin >> cena;
        informacje[id].shipping_cost.push_back(make_pair("Australia",cena));
	cout << "Kanada\n";
        cin >> cena;
        informacje[id].shipping_cost.push_back(make_pair("Kanada",cena));
}

void Grailed::search_by(string x)
{
    for(const auto& i:przedmioty_grailed)
    {
        if(i.get_rozmiar()==x || i.get_designer()==x || i.get_main_material()==x || i.get_kategoria()==x)
        {
            i.print_properties();
        }
    }
    cout << red << "Brak dopasowania" << color_reset << "\n";
}

void Vinted::search_by(string x)
{
    for(const auto& i:przedmioty_vinted)
    {
        if(i.get_rozmiar()==x || i.get_designer()==x || i.get_main_material()==x || i.get_kategoria()==x)
        {
            i.print_properties();
        }
    }
    cout << red << "Brak dopasowania" << color_reset << "\n";
}
void Vestiaire::search_by(string x)
{
    for(const auto& i:przedmioty_vestiaire)
    {
        if(i.get_rozmiar()==x || i.get_designer()==x || i.get_main_material()==x || i.get_kategoria()==x)
        {
            i.print_properties();
        }
    }
    cout << red << "Brak dopasowania" << color_reset << "\n";
}

void Vinted::show_all()
{
    cout << "Liczba przedmiotów w Vinted: " << przedmioty_vinted.size() << endl;

    if(przedmioty_vinted.empty())
    {
        cout << "BRAK ELEMENTOW\n";
        return;
    }

    for(const auto& i : przedmioty_vinted)
    {
        i.print_properties();
    }
}


void Vestiaire::show_all()
{
    cout << "Liczba przedmiotów w Vestiaire: " << przedmioty_vestiaire.size() << endl;
    if(przedmioty_vestiaire.empty())
    {
        cout << "BRAK ELEMENTOW\n";
        return;
    }
    for(const auto& i:przedmioty_vestiaire)
            i.print_properties();
}


//tutaj wszystko ladnie opisane 🙂
void Vinted::wystaw_przedmiot(Przedmiot& p)
{
    cout << "Jaka ma być cena za przedmiot na Vinted?\n";
    double pom;
    while(true)
    {
        cin >> pom;
        if(cin.good())
        {
	   break;
        }
        else
	{
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << red << "Zly input! Musisz podac liczbe!"  << color_reset;
	}
    }
    cennik[p.get_id()]=pom;
    przedmioty_vinted.push_back(p);
}



void Vinted::do_pliku()
{
    fstream plik("vinted.txt", ios::out);
    if (plik.is_open())
    {
	    plik << historia.size() << endl;
        for(const auto &entry : historia)
        {
            plik << entry.first << endl << entry.second.id_przedmiotu << endl << entry.second.cena << endl;
        }
	for(const auto& xd : cennik)
		plik << xd.first << endl << xd.second << endl;
        plik.close();
    }
    else
    {
        cerr << "Unable to open file vinted.txt" << endl;
    }
}

void Vinted::z_pliku()
{
    fstream plik("vinted.txt", ios::in);
    if (plik.is_open())
    {
        historia.clear();
        time_t czas;
        wlasciwosci wl;
	int rozm,cena,id;
	plik >> rozm;
	for(int i=0;i<rozm;++i)
	{
		plik >> czas >> wl.id_przedmiotu >> wl.cena;
		historia.emplace_back(czas,wl);
	}
        while(plik >> id >> cena)
        {
            cennik[id]=cena;
        }
        
        plik.close();
    }
    else
    {
        cerr << "Unable to open file vinted.txt" << endl;
    }
}

void Vestiaire::change_price(int id,int nowa)
{
    if(cennik.find(id)==cennik.end())
    {
        cout << "Nie ma przedmiotu o takim id\n";
        return;
    }
    cennik[id]=nowa;
}
void Vestiaire::wystaw_przedmiot(Przedmiot& p)
{
    cout << "Jaka ma być cena za przedmiot na Vestiaire?\n";
    int pom;
    while(true)
    {
        cin >> pom;
        if(cin.good())
        {
            break;
        }
        else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << red << "Zly input! Musisz podac liczbe!"  << color_reset;
	}
    }
    cennik[p.get_id()]=pom;
    przedmioty_vestiaire.push_back(p);
}
//done
void Grailed::set_tags(int id)
{
    for(int i=0;i<10;++i)
    {
        cout << "Podaj jeszcze " << i << "tagow\n";
        cin >> informacje[id].tags[i];
    }
}

void Vestiaire::sold(int id)
{
    if(cennik.find(id)==cennik.end())
        return;
    for(auto it=przedmioty_vestiaire.begin();it!=przedmioty_vestiaire.end();++it)
    {
        if(it->get_id()==id)
        {
            przedmioty_vestiaire.erase(it);
            break;
        }
    }
            
    
    cennik.erase(id);
    Grailed grailed;
    Vinted vinted;
    grailed.sold(id);
    vinted.sold(id);
}

void Vestiaire::do_pliku()
{
    fstream plik("vestiaire.txt", ios::out);
    if (plik.is_open())
    { 
	    plik << historia.size() << endl;  
	    for(const auto &entry : historia)    
	    {
		    plik << entry.first << endl << entry.second.id_przedmiotu << endl << entry.second.cena << endl;                                             }          
	    for(const auto& xd : cennik)   
		    plik << xd.first << endl << xd.second << endl;
	    plik.close();  
    }   
    else
    {
        cerr << "Unable to open file vestiaire.txt" << endl;
    }
}

void Vestiaire::z_pliku()
{
    fstream plik("vestiaire.txt", ios::in);
    if (plik.is_open())
    {
        historia.clear();
        time_t czas;
        wlasciwosci wl;
        int rozm,cena,id;
        plik >> rozm;
        for(int i=0;i<rozm;++i)
        {
                plik >> czas >> wl.id_przedmiotu >> wl.cena;
                historia.emplace_back(czas,wl);
        }
        while(plik >> id >> cena)
        {
            cennik[id]=cena;
        }

        plik.close();
    }
    else
    {
        cerr << "Unable to open file vestiaire.txt" << endl;
    }
}

string Vestiaire::generate_name(const Przedmiot& k)
{
	return "";
}
