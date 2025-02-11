#ifndef BUYER_HPP
#define BUYER_HPP

#include "Platformy.hpp"
#include <vector>
#include <string>
#include <ctime>

class Buyer
{
    private:
    struct oferta
    {
        static int last_number;
        int numer;
        time_t data;
        double cena;
        double cena_org;
        int id_przedmiotu;
        std::string portal;
    };
    struct trojka
    {
        int id;
        time_t data;
        double cena;
    };
    static std::vector<oferta> offers;
    static std::vector<trojka> solds;

    public:
    Buyer();
    void eras(int id);
    const std::vector<oferta>& get_offers() const { return offers; }
    void kasynko();
    void print_offers();
    void print_solds();
    void do_pliku();
    void z_pliku();
    void set_data();
};


#endif
