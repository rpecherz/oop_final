#ifndef SRODKI_HPP
#define SRODKI_HPP

#include <vector>
#include <string>
#include <fstream>
#include <ctime>

class Srodki 
{
    protected:
        double pln;
        double dlug;

    public:
        Srodki();
        void stan_konta() const;
        void pozyczka(double kwota);
        void wplata(double kwota);
        void wyplata(double kwota);
        void splata(double kwota);
        void do_pliku() const;
        void z_pliku();
};

class PayPal : public Srodki 
{
    protected:
        double euro;
        double usd;
        std::vector<std::pair<time_t, double>> historia;

    public:
        PayPal();
        double fromUSDtoPLN(double kwota);
        double fromEUROtoPLN(double kwota);
        void wyplacUSD(double kwota);
        void wyplacEURO(double kwota);
        void wplac(double kwota);
	void print_history();
        void do_pliku() const;
        void z_pliku();
	void stan();
	void historia_push(time_t t,int id);
};

class PortfelVinted : public Srodki 
{
    protected:
        double gotowe_srodki;
        double srodki_oczekujace;
        std::vector<std::pair<time_t, double>> historia;
        std::vector<std::pair<time_t,double>> zablokowane;
    public:
        PortfelVinted();
	void print_history();
        void wyplac();
        void wplac(double kwota);
        void do_pliku() const;
        void z_pliku();
        void check_if_ready();
	void stan();
	void historia_push(time_t t,int id);
};

#endif

