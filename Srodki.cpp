#include "Srodki.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

// Konstruktor Srodki
Srodki::Srodki() : pln(0.0), dlug(0.0) {}

void Srodki::stan_konta() const
{
    cout << "Stan konta: " << pln << " PLN\nDług: " << dlug << " PLN" << endl;
}

void Srodki::pozyczka(double kwota)
{
    pln+=kwota;
    dlug+=kwota;
}

void Srodki::wplata(double kwota)
{
    pln+=kwota;
}

void Srodki::wyplata(double kwota)
{
    if(kwota>pln)
        cout << "NIEWYSTARCZAJĄCE FUNDUSZE\n";
    else
        pln-=kwota;
}

void Srodki::splata(double kwota)
{
    if(kwota>pln)
        cout << "NIEWYSTARCZAJĄCE FUNDUSZE\n";
    else if(kwota>dlug)
    {
	pln-=dlug;
	dlug=0;
    }
    else
    {
        pln -= kwota;
        dlug -= kwota;
    }
}

void Srodki::do_pliku() const
{
    ofstream outfile("srodki.txt");
    if (outfile.is_open()) 
    {
        outfile << pln << endl;
        outfile << dlug << endl;
        outfile.close();
    } 
    else 
    {
        cout << "Unable to open file srodki.txt" << endl;
    }
}

void Srodki::z_pliku()
{
    ifstream infile("srodki.txt");
    if (infile.is_open())
    {
        infile >> pln;
        infile >> dlug;
        infile.close();
    } 
    else 
    {
        cout << "Unable to open file srodki.txt" << endl;
    }
}

// Konstruktor PayPal
PayPal::PayPal() : euro(0.0), usd(0.0) {}

double PayPal::fromUSDtoPLN(double kwota)
{
    return kwota*3.90;
}

double PayPal::fromEUROtoPLN(double kwota)
{
    return kwota*4.3;
}

void PayPal::wyplacUSD(double kwota)
{
    if(kwota>usd)
        cout << "INSUFFICIENT FUNDS\n";
    else
    {
        pln+=fromUSDtoPLN(kwota);
        usd-=kwota;
    }
}

void PayPal::wyplacEURO(double kwota)
{
    if(kwota>euro)
        cout << "INSUFFICIENT FUNDS\n";
    else
    {
        pln+=fromEUROtoPLN(kwota);
        euro-=kwota;
    }
}

void PayPal::wplac(double kwota)
{
    time_t now=time(0);
    historia.push_back(make_pair(now, kwota));
    pln+=kwota;
}

void PayPal::do_pliku() const
{
    ofstream outfile("paypal.txt");
    if (outfile.is_open())
    {
        outfile << euro << endl;
        outfile << usd << endl;
        for(const auto& record : historia)
        {
            outfile << record.first << " " << record.second << endl;
        }
        outfile.close();
    } 
    else 
    {
        cout << "Unable to open file paypal.txt" << endl;
    }
}

void PayPal::z_pliku()
{
    ifstream infile("paypal.txt");
    if(infile.is_open())
    {
        infile >> euro;
        infile >> usd;
        historia.clear();
        time_t czas;
        double kwota;
        while (infile >> czas >> kwota)
        {
            historia.emplace_back(czas, kwota);
        }
        infile.close();
    } 
    else 
    {
        cout << "Unable to open file paypal.txt" << endl;
    }
}

void PayPal::stan()
{
	cout << "Dostepne srodki: \n";
        cout << "Euro: " << euro;
        cout << "\nDolary: " << usd << "\n";
}

void PayPal::print_history()
{
	for (const auto& entry : historia) 
	{
        	struct tm *timeinfo;
        	char buffer[80];
        	timeinfo = localtime(&entry.first);
	        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	
        	// Wypisanie daty i wartości
        	cout << "Date: " << buffer << ", Value: " << entry.second << std::endl;
    	}
}


void PayPal::historia_push(time_t t,int id)
{
	historia.push_back(make_pair(t,id));
}
void PortfelVinted::historia_push(time_t t,int id)
{
        historia.push_back(make_pair(t,id));
}


// Konstruktor PortfelVinted
PortfelVinted::PortfelVinted() : gotowe_srodki(0.0), srodki_oczekujace(0.0) {}

void PortfelVinted::wyplac()
{
    pln+=gotowe_srodki;
    gotowe_srodki=0.0;
}

void PortfelVinted::wplac(double kwota)
{
    check_if_ready();
    srodki_oczekujace-=kwota;
}

void PortfelVinted::do_pliku() const
{
    ofstream outfile("portfel_vinted.txt");
    if(outfile.is_open())
    {
        outfile << gotowe_srodki << endl;
        outfile << srodki_oczekujace << endl;
        for (const auto& entry : historia)
        {
            outfile << entry.first << " " << entry.second << endl;
        }
        outfile.close();
    } 
    else 
    {
        cout << "Unable to open file portfel_vinted.txt" << endl;
    }
}

void PortfelVinted::z_pliku()
{
    ifstream infile("portfel_vinted.txt");
    if(infile.is_open())
    {
        infile >> gotowe_srodki;
        infile >> srodki_oczekujace;
        historia.clear();
        time_t czas;
        double kwota;
        while (infile >> czas >> kwota)
        {
            historia.emplace_back(czas, kwota);
        }
        infile.close();
    } 
    else 
    {
        cout << "Unable to open file portfel_vinted.txt" << endl;
    }
}

void PortfelVinted::check_if_ready()
{
    time_t now = time(0);
    const int SECONDS_IN_DAY=86400;

    for(auto it = zablokowane.begin();it!=zablokowane.end();++it)
    {
        time_t czas=it->first;
        double kwota=it->second;

        double roznica_czasu = difftime(now, czas);
        if (roznica_czasu>=2*SECONDS_IN_DAY)
            it=zablokowane.erase(it);
    }
}
void PortfelVinted::print_history()
{
	for (const auto& entry : historia)
        {
                struct tm *timeinfo;
                char buffer[80];
                timeinfo = localtime(&entry.first);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                // Wypisanie daty i wartości
                cout << "Date: " << buffer << ", Value: " << entry.second << std::endl;
        }
}
void PortfelVinted::stan()
{
	cout << "Dostepne srodki " << gotowe_srodki << "\n";
        cout << "Zablokowane srodki " << srodki_oczekujace << "\n";
}
