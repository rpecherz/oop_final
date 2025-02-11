#include "Buyer.hpp"
#include "Platformy.hpp"
#include "Przedmiot.hpp"
#include "Srodki.hpp"
#include <iostream>
#include <cstdlib>
#include <random>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <fstream>

using namespace std;


int Buyer::oferta::last_number = 0;

Buyer::Buyer() {}

const string red("\033[0;31m");
const string color_reset("\033[0m");

vector<Buyer::oferta> Buyer::offers;
vector<Buyer::trojka> Buyer::solds;

void Buyer::print_offers()
{
    if(offers.empty())
    {
        cout << red << "BRAK AKTUALNYCH OFERT OD KUPUJACYCH!" << color_reset << "\n";
        return;
    }
    for(const auto& i : offers)
    {
        cout << "Numer oferty: " << i.numer << " portal " << i.portal << " o " << i.data << " oferuje " << i.cena << " zamiast " << i.cena_org << "za przedmiot" << i.id_przedmiotu << "\n";
    }
}

void Buyer::eras(int id)
{
    auto it = offers.begin();
    while(it != offers.end()) 
    {
        if (it->id_przedmiotu == id) 
	{
            it = offers.erase(it);  
 	} 
	else 
	{
            ++it;
        }
    }
}

void Buyer::print_solds()
{
    if(solds.empty())
    {
        cout << red << "BRAK SPRZEDANYCH RZECZY!" << color_reset << "\n";
        return;
    }
    for(const auto& item : solds)
    {
        cout << "Item nr " << item.id << " sprzedał się " << item.data << " za" << item.cena << "\n";
    }
}

void Buyer::do_pliku()
{
    ofstream outfile("buyer.txt" , ios::out);
    if(outfile.is_open())
    {
        for (const auto& offer : offers)
        {
            outfile << offer.numer << endl;
            outfile << offer.data << endl;
            outfile << offer.cena << endl;
            outfile << offer.cena_org << endl;
            outfile << offer.id_przedmiotu << endl;
            outfile << offer.portal << endl;
        }
        outfile.close();
    } 
    else 
    {
        cout << "Unable to open file buyer.txt" << endl;
    }
}

void Buyer::z_pliku()
{
    ifstream infile("buyer.txt");
    if (infile.is_open())
    {
        while (true)
        {
            oferta offer;
            if (!(infile >> offer.numer >> offer.data >> offer.cena >> offer.cena_org >> offer.id_przedmiotu >> offer.portal))
                break;
            offers.push_back(offer);
        }
        infile.close();
    } 
    else
    {
        cout << "Unable to open file buyer.txt" << endl;
    }
}

void Buyer::kasynko()
{
	Vinted vinted;
                Grailed grailed;
                Vestiaire vestiaire;
                PortfelVinted pv;
                PayPal pp;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 40);            
    while(true)
    {
        for(int i=0;i<10;i++)
        {
            int x = dist(mt);
            
            if(x%3 == 2)
            {
                int portal = dist(mt) % 3;
                int typ_transakcji = dist(mt) % 2;
                double znizka = 1.0;
                oferta of;
                
                if(typ_transakcji == 0)
                {
                    znizka = (100.0 - double(dist(mt))) / 100.0;
                    of.numer = oferta::last_number++;
                    of.data = time(nullptr);
                }
              
                if(portal == 0)
                {
                    const auto& vinted_items = vinted.get_przedmioty_vinted();
                    
                    if(!vinted_items.empty())
                    {
                        if(typ_transakcji == 1)
                        {
			    trojka g;
                            int id = vinted_items.front().get_id();
			    double cena = vinted.get_cennik().find(id)->second;
			    time_t data = time(nullptr);
			    g.id=id;
			    g.cena=cena;
			    g.data=data;
			     solds.push_back(g);
                            vinted.sold(id);
			    pv.historia_push(time(nullptr),id);
			    
                        }
                        else
                        {
                            auto it = vinted.get_cennik().find(vinted_items.back().get_id());
                            if (it != vinted.get_cennik().end()) {
                                of.cena = znizka * it->second;
                                of.cena_org = it->second;
                                of.id_przedmiotu = vinted_items.back().get_id();
                                of.portal = "Vinted";
                                offers.push_back(of);
                            } else {
                                cout << "Error: Item not found in vinted.cennik" << endl;
                            }
                        }
                    }
                }
                else if(portal == 1)
                {
                    const auto& vestiaire_items = vestiaire.get_przedmioty_vestiaire();
                    
                    if(!vestiaire_items.empty())
                    {
                        if(typ_transakcji == 1)
                        {
                            trojka g;
                            int id = vestiaire_items.front().get_id();
                            double cena = vestiaire.get_cennik().find(id)->second;
                            time_t data = time(nullptr);
                            g.id=id;
                            g.cena=cena;
                            g.data=data;
                             solds.push_back(g);
			     vestiaire.sold(id);
			    pp.historia_push(time(nullptr),id);
                        }
                        else
                        {
                            auto it = vestiaire.get_cennik().find(vestiaire_items.back().get_id());
                            if (it != vestiaire.get_cennik().end()) {
                                of.cena = znizka * it->second;
                                of.cena_org = it->second;
                                of.id_przedmiotu = vestiaire_items.back().get_id();
                                of.portal = "Vestiaire";
                                offers.push_back(of);
                            } else {
                                cout << "Error: Item not found in vestiaire.cennik" << endl;
                            }
                        }
                    }
                }
                else 
                {
                    const auto& grailed_items = grailed.get_przedmioty_grailed();
                    
                    if(!grailed_items.empty())
                    {
                        if(typ_transakcji == 1)
                        {
                            trojka g;
                            int id = grailed_items.front().get_id();
                            time_t data = time(nullptr);
                            g.id=id;
                            g.data=data;
			     g.cena=grailed.get_cennik().find(id)->second;
                             solds.push_back(g);
				grailed.sold(id);
			    pp.historia_push(time(nullptr),id);
                        }
                        else
                        {
                            auto it = grailed.get_informacje().find(grailed_items.back().get_id());
                            if (it != grailed.get_informacje().end()) {
                                of.cena = znizka * it->second.cena;
                                of.cena_org = it->second.cena;
                                of.id_przedmiotu = grailed_items.back().get_id();
                                of.portal = "Grailed";
                                offers.push_back(of);
                            } else {
                                cout << "Error: Item not found in grailed.informacje" << endl;
                            }
                        }
                    }
                }
            }
        }
        
        this_thread::sleep_for(chrono::seconds(10));
    }
}


