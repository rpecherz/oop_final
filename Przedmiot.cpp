#include "Przedmiot.hpp"
#include "Platformy.hpp"
#include <iostream>
#include <limits>
using namespace std;

int Przedmiot::last_id = 0;
std::vector<Przedmiot> Przedmiot::lista_przedmiotow;

const string red("\033[0;31m");
const string magenta("\033[0;35m");
const string color_reset("\033[0m");

int Przedmiot::get_id() const
{
	return id;
}
void Przedmiot::show_all()
{
	for(const auto& i:lista_przedmiotow)
		i.print_properties();
}

void Przedmiot::print_properties() const
{
    cout << id << " " << kategoria << " " << designer << " " << main_material << " " << rozmiar << " stan: " << stan << "\n";
}

void Przedmiot::set_properties()
{
	int i_k=-1;
	cout << "Najpierw podaj kategorie!\n";                                  
	cin >> kategoria;                    
	cout << "Teraz podaj marke!\n";
	cin >> designer;  
	cout << "Teraz podaj materiał główny\n"; 
	cin >> main_material;
	cout << "Teraz podaj rozmiar przedmiotu na metce\n";
	cin >> rozmiar;
        cout << "Teraz stan od 1 do 10\n";
	cin >> stan;
	while(!cin.good() || stan<1 || stan>10)
	{
           cin.clear();
	   cin.ignore(numeric_limits<streamsize>::max(), '\n');
           cout << red << "Zły input! Podaj ilość jeszcze raz" << color_reset << "\n";
           cin >> stan;
        }
	cout << "Podaj ilość kolorow od 1 do 5!\n";
	cin >> i_k;
        while(!cin.good() || i_k<0 || i_k>5)
        {
           cin.clear();
	   cin.ignore(numeric_limits<streamsize>::max(), '\n');
           cout << red << "Zły input! Podaj ilość jeszcze raz" << color_reset << "\n";
           cin >> i_k;
        }
            for(int i=1;i<=i_k;++i)
            {
                cout << "Podaj " << i << " kolor\n";
                string kolor1;
		cin >> kolor1;
                color.push_back(kolor1);
            }

            sprzedane=false;
            int rok;
            cout << "Podaj rok produkcji\n";
            cin >> rok;
            while(!cin.good() || rok<1800)
            {
                cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << red << "Zły input! Podaj rok produkcji jeszcze raz" << color_reset << "\n";
                cin >> rok;
            }
            time_t now = time(nullptr);
            tm* localtm = localtime(&now);
            int year = localtm->tm_year + 1900;
            if(year-rok>=15)
                vintage=true;
            else
                vintage=false;
	    Grailed grailed;
	    Vinted vinted;
	    Vestiaire vestiaire;
	    string yn;
            cout << "Czy chcesz wystawic na Grailed? t/n\n";
            cin >> yn;
            //do dokonczenia
            if(yn=="t" || yn=="T" || yn=="y" || yn=="Y" || yn=="Tak" || yn=="TAK" || yn=="tak" || yn=="YES" || yn=="Yes" || yn=="yes")
            {
                    czy_grailed=1;
            }
            cout << "Czy chcesz wystawic na Vestiaire? t/n\n";
            cin >> yn;

            if(yn=="t" || yn=="T" || yn=="y" || yn=="Y" || yn=="Tak" || yn=="TAK" || yn=="tak" || yn=="YES" || yn=="Yes" || yn=="yes")
                {
                        czy_vestiaire=1;
                }
            cout << "Czy chcesz wystawic na Vinted? t/n\n";
            cin >> yn;

            if(yn=="t" || yn=="T" || yn=="y" || yn=="Y" || yn=="Tak" || yn=="TAK" || yn=="tak" || yn=="YES" || yn=="Yes" || yn=="yes")
            {
                    czy_vinted=1;
            }
            if(czy_grailed==1)
                grailed.wystaw_przedmiot(*this);
            if(czy_vestiaire==1)
                    vestiaire.wystaw_przedmiot(*this);
            if(czy_vinted==1)
                    vinted.wystaw_przedmiot(*this);
	    lista_przedmiotow.push_back(*this);
}



Przedmiot::Przedmiot(double stan1, std::string kat, std::string des, std::string mat, std::string size, bool vint)
    : id(++last_id), stan(stan1), kategoria(kat), designer(des), main_material(mat), rozmiar(size), vintage(vint), sprzedane(false) 
{
}


void Przedmiot::do_pliku() 
{
    ofstream outfile("przedmioty.txt",ios::out);
    if (outfile.is_open())
    {
        for(const auto& przedmiot : lista_przedmiotow) 
        {
            outfile << przedmiot.id << endl;
            outfile << przedmiot.stan << endl;
            outfile << przedmiot.kategoria << endl;
            outfile << przedmiot.designer << endl;
            outfile << przedmiot.main_material << endl;
            outfile << przedmiot.rozmiar << endl;
            outfile << przedmiot.vintage << endl;
            outfile << przedmiot.sprzedane << endl;
            outfile << przedmiot.color.size() << endl;  
            for (const auto& col : przedmiot.color) {
                outfile << col << endl;  
            }
	    outfile << przedmiot.czy_grailed << endl;
	    outfile << przedmiot.czy_vestiaire << endl;
	    outfile << przedmiot.czy_vinted << endl;
        }
        outfile.close();
    } 
    else
    {
        cout << "Unable to open file przedmioty.txt" << endl;
    }
}

void Przedmiot::z_pliku() 
{
    Vinted vinted;
    Vestiaire vestiaire;
    Grailed grailed;
    ifstream infile("przedmioty.txt");
    if(infile.is_open()) 
    {
        lista_przedmiotow.clear();  
        while(!infile.eof())
        {
            Przedmiot przedmiot;
            int color_count;
            infile >> przedmiot.id;
            infile >> przedmiot.stan;
            infile >> przedmiot.kategoria;
            infile >> przedmiot.designer;
            infile >> przedmiot.main_material;
            infile >> przedmiot.rozmiar;
            infile >> przedmiot.vintage;
            infile >> przedmiot.sprzedane;
            infile >> color_count;  
            przedmiot.color.clear();
            for(int i = 0; i < color_count; ++i) 
            {
                string col;
                infile >> col;
                przedmiot.color.push_back(col);  
            }
            infile >> przedmiot.czy_grailed;
	    infile >> przedmiot.czy_vestiaire;
	    infile >> przedmiot.czy_vinted;
            if(infile.eof())
                break;
	    if(przedmiot.czy_grailed==1)
                        grailed.wystaw2(przedmiot);
            if(przedmiot.czy_vestiaire==1)
                     vestiaire.wystaw2(przedmiot);
            if(przedmiot.czy_vinted==1)
                    vinted.wystaw2(przedmiot);
            
            lista_przedmiotow.push_back(przedmiot);
        }
        infile.close();
    } 
    else 
    {
        cout << "Unable to open file przedmioty.txt" << endl;
    }
}

