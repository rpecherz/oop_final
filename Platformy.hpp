#ifndef PLATFORMY_HPP
#define PLATFORMY_HPP

#include "Przedmiot.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>

class Platformy
{
    public:
        Platformy() = default;
	    virtual ~Platformy() {};
        virtual void change_price(int id, int nowa) = 0;
        virtual void wystaw_przedmiot(Przedmiot& k) = 0;
        virtual void search_by(std::string x) = 0;
        virtual void show_all() = 0;
        virtual void sold(int id) = 0;
        virtual std::string generate_name(const Przedmiot& k) = 0;
        virtual void z_pliku() = 0;
        virtual void do_pliku() = 0;
};



class Vinted : public Platformy
{
    protected:
        struct wlasciwosci
        {
            int id_przedmiotu;
            int cena;
        };
        const std::vector<std::string> baza_slow;
        static std::vector<Przedmiot> przedmioty_vinted;
        static std::map<int,double> cennik;
        
        std::vector<std::pair<time_t,wlasciwosci>> historia;
    public:
        Vinted();
        void change_price(int id, int nowa) override;
        void wystaw_przedmiot(Przedmiot& k) override;
	void wystaw2(Przedmiot& k);
        void search_by(std::string x) override;
        void show_all() override;
        void sold(int id) override;
        std::string generate_name(const Przedmiot& k) override;
        void do_pliku() override;
        void z_pliku() override;
	const std::vector<Przedmiot>& get_przedmioty_vinted() const { return przedmioty_vinted; }
	std::map<int,double> get_cennik(){ return cennik; }
};


class Grailed : public Platformy
{
    protected:
        struct wlasciwosci
        {
            int cena;
            std::vector<std::pair<std::string, int>> shipping_cost;
            std::string tags[10];
        };
        const std::vector<std::string> buzzword;
        static std::vector<Przedmiot> przedmioty_grailed;
        static std::map<int,wlasciwosci> informacje;
        std::vector<std::pair<time_t,wlasciwosci>> historia;
   	static std::map<int,double> cennik; 
    public:
        Grailed();
        void change_price(int id, int nowa) override;
        void wystaw_przedmiot(Przedmiot& k) override;
	void wystaw2(Przedmiot& k);
        void search_by(std::string x) override;
        void show_all() override;
        void sold(int id) override;
        void set_tags(int id);
        void set_shipping(int id);
        std::string generate_name(const Przedmiot& k) override;
        void do_pliku() override;
        void z_pliku() override;
	const std::vector<Przedmiot>& get_przedmioty_grailed() const { return przedmioty_grailed; }
        const std::map<int,wlasciwosci>& get_informacje() const { return informacje; }
	std::map<int,double> get_cennik(){ return cennik; }
};


class Vestiaire : public Platformy
{
    protected:
        struct wlasciwosci
        {
            int cena;
            int id_przedmiotu;
        };
        static std::vector<Przedmiot> przedmioty_vestiaire;
        static std::vector<std::pair<time_t,wlasciwosci>> historia;
        static std::map<int,double> cennik;
        
    public:
        Vestiaire();
        void change_price(int id, int nowa) override;
        void wystaw_przedmiot(Przedmiot& k) override;
	void wystaw2(Przedmiot& k);
        void show_all() override;
        void search_by(std::string x) override;
        void sold(int id) override;
        std::string generate_name(const Przedmiot& k) override; 
        void do_pliku() override;
        void z_pliku() override;
	const std::vector<Przedmiot>& get_przedmioty_vestiaire() const { return przedmioty_vestiaire; }
        std::map<int,double> get_cennik() { return cennik; }
};


#endif
