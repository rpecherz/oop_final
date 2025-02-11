#ifndef PRZEDMIOT_HPP
#define PRZEDMIOT_HPP

#include <vector>
#include <string>

class Przedmiot 
{
    protected:
        static int last_id;
        int id;
        double stan;
        
        std::string kategoria;
        std::string designer;
        std::string main_material;
        std::string rozmiar;
        
        static std::vector<Przedmiot> lista_przedmiotow;
	std::vector<std::string> color;
       	 
        bool sprzedane;
        bool vintage;
        int czy_grailed=0;
        int czy_vestiaire=0;
	int czy_vinted=0;	
    public:
    void set_czy_grailed(){czy_grailed=1;}
    void set_czy_vestiaire(){czy_vestiaire=1;}
    void set_czy_vinted(){czy_vinted=1;} 
    int get_czy_grailed(){return czy_grailed;}
    int get_czy_vestiaire(){return czy_vestiaire;}
    int get_czy_vinted(){return czy_vinted;}
    Przedmiot(double stan1=0.0,std::string kat="und",std::string des="und",std::string mat="und",std::string size="und",bool vint=false);
    std::string get_kategoria() const { return kategoria; }
    std::string get_rozmiar() const { return rozmiar; }
    std::string get_designer() const { return designer; }
    std::string get_main_material() const { return main_material;};

    void show_all();
    void print_properties() const;
    void set_properties();
    int get_id() const;
    static void do_pliku();
    static void z_pliku();
};

#endif
