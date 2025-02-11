#include <iostream>
#include <thread>
#include "Buyer.hpp"
#include "Przedmiot.hpp"
#include "Platformy.hpp"
#include "Srodki.hpp"
#include <ctime>
using namespace std;


const string red("\033[0;31m");
const string magenta("\033[0;35m");
const string color_reset("\033[0m");


void interfejs()
{
    Grailed grailed;
    Vinted vinted;
    Vestiaire vestiaire;
    PayPal pp;
    PortfelVinted pv;
    Srodki srodek;
    Buyer Buyer1;
    Przedmiot p;
    
    p.z_pliku();
    srodek.z_pliku();
    
    pp.z_pliku(); 
    pv.z_pliku();
    vinted.z_pliku();
    vestiaire.z_pliku();
    system("clear");
    /*
    */
    while(true)
    {
        cout << magenta << "Co chcesz zrobić?" << color_reset << "\n";
        cout << "1. Przegladac przedmioty\n";
        cout << "2. Wystawić przedmiot\n";
        cout << "3. Przegladać środki\n";
        cout << "4. Przejrzeć oferty za przedmioty\n";
        cout << "5. Zobaczyć ostatnio sprzedane przedmioty\n";
        cout << "By wyjść wpisz q\n";
        
        string wejscie;
        int K;
        cin >> wejscie;
        system("clear");
        if(wejscie=="1")
        {
            while(true)
            {
                cout << "Która platforma?\n";
                cout << "1. Grailed\n";
                cout << "2. Vinted\n";
                cout << "3. Vestiaire\n";
		cout << "4. Pokaż wszystkie przedmioty\n";
                cout << "5. Wróć\n";
                cin >> wejscie;
                system("clear");
                if(wejscie=="1")
                {
                    while(true)
                    {
                        cout << "Co chcesz zobaczyć?\n";
                        cout << "1. Pokaż wszystko\n";    
                        cout << "2. Szukaj po stringu\n";
                        cout << "3. Wróć\n";
                        cin >> wejscie;
                        system("clear");
                        if(wejscie=="1")
                        {
                            cout << "Przedmioty Grailed\n";
                            grailed.show_all();
                        }
                        else if(wejscie=="2")
                        {
                            //moze byc rozmiar typu L, designer obojetnie
                            cout << "Podaj string do wyszukania";
                            cin >> wejscie;
                            cout << "Przedmioty Grailed\n";
                            grailed.search_by(wejscie);
                        }
                        else if(wejscie=="3")
                            break;
                        else
                            cout << red << "ZLY INPUT" << color_reset << "\n";
                    }
                }
                else if(wejscie=="2")
                {
                    while(true)
                    {
                        cout << "Co chcesz zobaczyć?\n";
                        cout << "1. Pokaż wszystko\n";    
                        cout << "2. Szukaj po stringu\n";
                        cout << "3. Wróć\n";
                        cin >> wejscie;
                        system("clear");
                        if(wejscie=="1")
                        {
                            cout << "Przedmioty Vinted\n";
                            vinted.show_all();
                        }
                        else if(wejscie=="2")
                        {
                            //moze byc rozmiar typu L, designer obojetnie
                            cout << "Podaj string do wyszukania";
                            cin >> wejscie;
                            cout << "Przedmioty Vinted\n";
                            vinted.search_by(wejscie);
                        }
                        else if(wejscie=="3")
                            break;
                        else
                            cout << red << "ZLY INPUT" << color_reset << "\n";
                    }
                }
                else if(wejscie=="3")
                {
                    while(true)
                    {
                        cout << "Co chcesz zobaczyć?\n";
                        cout << "1. Pokaż wszystko\n";    
                        cout << "2. Szukaj po stringu\n";
                        cout << "3. Wróć\n";
                        cin >> wejscie;
                        system("clear");
                        if(wejscie=="1")
                        {
                            cout << "Przedmioty Vestiaire\n";
                            vestiaire.show_all();
                        }
                        else if(wejscie=="2")
                        {
                            //moze byc rozmiar typu L, designer obojetnie
                            cout << "Podaj string do wyszukania";
                            cin >> wejscie;
                            cout << "Przedmioty Vestiaire\n";
                            vestiaire.search_by(wejscie);
                        }
                        else if(wejscie=="3")
                            break;
                        else
                            cout << red << "ZLY INPUT" << color_reset << "\n";
                    }
                }
		else if(wejscie=="4")
		{
			p.show_all();
		}
                else if(wejscie=="5")
                    break;
                else
                    cout << red << "ZLY INPUT" << color_reset << "\n";
            }
        }
        else if(wejscie=="2")
        {
            cout << "Jeżeli nie chcesz wystawić przedmiotu wpisz b, a jezeli tak to wpisz cokolwiek\n";
            string powrot;
            cin >> powrot;
            if(powrot=="b")
            {
                continue;
            }
                
                
            system("clear");
            Przedmiot nowy;
	    nowy.set_properties();
            system("clear");
            cout << magenta << "Wystawianie przedmiotu zakonczone!" << color_reset << "\n";
        }
        else if(wejscie=="3")
        {
            while(true)
            {
		system("clear");
                cout << "1. Srodki\n";
                cout << "2. PayPal\n";
                cout << "3. PortfelVinted\n";
                cout << "4. Powrot\n";
        
                string cas;
                cin >> cas;
		system("clear");
                if(cas=="1")
                {
                    while(true)
                    {
                        srodek.stan_konta(); 
                        cout << "Co chcesz zrobić?\n";
                        cout << "1. Wplacam\n";
                        cout << "2. Wyplacam\n";
                        cout << "3. Pozyczam\n";
                        cout << "4. Splacam\n";
                        cout << "5. Powrot\n";
                        cin >> cas;
			system("clear");
                        if(cas=="5")
                            break;
                            
                        cout << "Ile?\n";
                        double kwota;
                        cin >> kwota;
                        while(!cin.good())
                        {
                            cin.clear();
                            cout << red << "ZLY INPUT. Podaj liczbe\n" << color_reset << "\n";
                            cin >> kwota;
                        }
                        if(cas=="1")
                        {
                            srodek.wplata(kwota);
                        }
                        else if(cas=="2")
                        {
                            srodek.wyplata(kwota);
                        }
                        else if(cas=="3")
                        {
                            srodek.pozyczka(kwota);
                        }
                        else if(cas=="4")
                        {
                            srodek.splata(kwota);
                        }
                        else if(cas=="5")
                            break;
                        else
                        {
                            cout << red << "ZLY INPUT\n" << color_reset << "\n";
                        }
                    }
                    
                }
                else if(cas=="2")
                {
                    //do dokonczenia historia
                    while(true)
                    {
                        pp.stan();
                        cout << "Co chcesz zrobić?\n";
                        cout << "1. Wyplacam\n";
			cout << "2. Pokaż historię\n";
                        cout << "3. Powrot\n";
                        cin >> cas;
			system("clear");
                        if(cas=="1")
			{
			    double kwota=-1;
			    cout << "1. Euro\n2. USD\n";
		            cin >> cas;

			    
			    cout << "Podaj kwote\n";
			    cin >> kwota;
			    while(!cin.good() || kwota<0)
			    {
				cin.clear();
				cout << red << "ZLY INPUT" << color_reset << "\n";
				cin >> kwota;
			    }
			    if(cas=="1")
			    {
				pp.wyplacEURO(kwota);
			    }
		            else
				pp.wyplacUSD(kwota);
			}
			if(cas=="2")
			{
				pp.print_history();
			}
                        if(cas=="3")
                            break;
                    }
                }
                else if(cas=="3")
                {
                    //do dokoczenia chodzi mi o historie
                    while(true)
                    {
			pv.stan(); 
                        cout << "Co chcesz zrobić?\n";
                        cout << "1. Wyplacam\n";
			cout << "2. Pokaż historie\n"; 
                        cout << "3. Powrot\n";
                        cin >> cas;
			system("clear");
                        if(cas=="1")
                            pv.wyplac();
			if(cas=="2")
			    pv.print_history();
                        if(cas=="3")
                            break;
                    }
                }
                else if(cas=="4")
                    break;
                else
                {
                    cout << red << "ZLY INPUT\n" << color_reset << "\n";
                }
            }
        }
        else if(wejscie=="4")
        {
	    Buyer1.print_offers();
            while(true)
            {
		    cout << "Jeżeli akceptujesz którąś ofertę, wpisz jej numer. W przeciwnym przypadku wpisz -1\n";
		    cin >> K;
		    if(!cin.good() || K>Buyer1.get_offers().size())
		    {
			    cout << red << "ZLY INPUT" << color_reset << "\n";
                    cin.clear();
                }
                if(K==-1)
                {
                    system("clear");
                    break;
                }
		bool x=0;
                for(const auto& i:Buyer1.get_offers())
                {
		    if(x==1)
		     {
			     Buyer1.eras(i.id_przedmiotu);
			     break;
		     }
                    if(i.numer==K)
                    {
			x==1;
                        if(i.portal=="Grailed")
                        {
                            grailed.sold(i.id_przedmiotu);
                            pp.wplac(i.cena);
                        }
                        else if(i.portal=="Vinted")
                        {
                            vinted.sold(i.id_przedmiotu);
                            pv.wplac(i.cena);
                        }
                        else
                        {
                            vestiaire.sold(i.id_przedmiotu);
                            pp.wplac(i.cena);
                        }
                    }
                }
            }
        }
        else if(wejscie=="5")
        {
            Buyer1.print_solds();
            cout << "By wrocić wpisz b\n";
            while(true)
            {
                cin >> wejscie;
                if(wejscie=="b")
                    break;
            }
        }
        else if(wejscie=="q")
        {
            //tutaj ma być zapisywanie do plikow
	    srodek.do_pliku();
	    pp.do_pliku();
	    pv.do_pliku();    
	    p.do_pliku();
	    vinted.do_pliku();
	    grailed.do_pliku();
	    vestiaire.do_pliku();
            return;
        }
        else
            cout << red << "ZLY INPUT" << color_reset << "\n";
    }
}

void buyers()
{
    Buyer Buyer1;
    Buyer1.kasynko();
}

int main()
{
    thread t1(interfejs);
    thread t2(buyers);
    
    t1.join();
    t2.join();
    return 0;
}
