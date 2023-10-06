#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <cmath>
#include <cassert>
#include "countObjects.hh"


using namespace std;

#define EE 0.000001


/*!
 * \brief Class Vector
 * 
 * Class contains array of 2 variables "double" type
 * 
 */
template <int Wymiar>
class Vector : public Count<Vector<Wymiar>>
{
    double tab[Wymiar];

public:
    /**
    * @brief Konstruktor dla wektora bez parametrow
    */
    Vector()
    {
        for (int i = 0; i < Wymiar; i++)
        {
            tab[i] = 0;
        }
    }
    /**
     * @brief Konstruktor dla wektora z parametrami
     * 
     * @param x pierwsza wsporzedna wektora
     * @param y druga wsporzedna wektora
     * @param z trzecia wsporzedna wektora
     */
    Vector(double x, double y, double z)
    {
        tab[0] = x;
        tab[1] = y;
        tab[2] = z;
    }

    inline Vector(const std::initializer_list<double> &ListaWartosci) {
        assert(ListaWartosci.size() <= Wymiar);
        int Indeks = -1;
        for(double Wartosc : ListaWartosci) (*this)[++Indeks] = Wartosc;
    }

    double operator[](const int i) const
    {
        return tab[i];
    }
    double &operator[](const int i)
    {
        return tab[i];
    }
    /**
     * @brief Definicje funkcji
     */
    Vector<Wymiar> operator+(const Vector<Wymiar> cos1) const;
    Vector<Wymiar> operator-(const Vector<Wymiar> cos1) const;
    bool porownanie(Vector<Wymiar> com);
    double dlugoscW();
    bool operator==(Vector<Wymiar> ktos);
    Vector<Wymiar> przypisanietranslacji(double x, double y, double z);
};

template <int Wymiar>

Vector<Wymiar> Vector<Wymiar>::przypisanietranslacji(double x, double y, double z)
{
    tab[0]=x;
    tab[1]=y;
    tab[2]=z;
    return *this;
}


/**
 * @brief Fukncja przeciazenia operatora wpisywania wektora
 * 
 * @tparam Wymiar wektora
 * @param Strm strumien
 * @param Wek wektor ktory bedzie wczytywany
 * @return std::ostream& 
 */

template <int Wymiar>

std::ostream &operator<<(std::ostream &Strm, const Vector<Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; i++)
    {
        //Strm << std::setw(16) <<std::fixed << std::setprecision(10) << Wek[i];
         Strm << Wek[i] << " ";
    }
    Strm << std::endl;
    return Strm;
}

/**
 * @brief Funkcja przeciaznia operatora dodawania wektorow
 * 
 * @tparam Wymiar wektora
 * @param cos1 wektor dodawany
 * @return Vector<Wymiar> 
 */

template <int Wymiar>

Vector<Wymiar> Vector<Wymiar>::operator+(const Vector<Wymiar> cos1) const
{
    Vector<Wymiar> stonks;
    for (int i = 0; i < Wymiar; i++)
    {
        stonks[i] = this->tab[i] + cos1[i];
    }
    return stonks;
}

/**
 * @brief Funkcja przeciaznia operatora odejmowania wektorow
 * 
 * @tparam Wymiar wektora
 * @param cos1 wektor odejmowany
 * @return Vector<Wymiar> 
 */

template <int Wymiar>

Vector<Wymiar> Vector<Wymiar>::operator-(const Vector<Wymiar> cos1) const
{
    Vector<Wymiar> stonks;
    for (int i = 0; i < Wymiar; i++)
    {
        stonks[i] = this->tab[i] - cos1[i];
    }
    return stonks;
}

/**
 * @brief funkcja przeciarzenia operatora wypisywania wektora 
 * 
 * @tparam Wymiar wektora
 * @param Strm strumien
 * @param Wek wektor wypisywany
 * @return std::istream& 
 */

template <int Wymiar>

std::istream &operator>>(std::istream &Strm, Vector<Wymiar> &Wek)
{
    double x;
    for (int i = 0; i < Wymiar; ++i)
    {
        Strm >> x;
         Wek[i] = x;
    }
    return Strm;
}

/**
 * @brief Funckja porownywania dwoch wektorow
 * 
 * Funkcja porownuje dlugosci wektorow czy sa takie same (a dokladniej, czy roznice ich dlugosci nie sa wieksze od epsilonu)
 * 
 * @tparam Wymiar wektora
 * @param com wektor do porownania
 * @return true prawda gdy rowne
 * @return false falsz gdy nierowne
 */

template <int Wymiar>

bool Vector<Wymiar>::porownanie(Vector<Wymiar> com)
{
    if (this->dlugoscW() - com.dlugoscW() < EE)
    {
        return true;
    }
    return false;
}

/**
 * @brief Funkcja liczaca dlugosc wektora ze wzoru
 * @tparam Wymiar wektora
 * @return double 
 */

template <int Wymiar>

double Vector<Wymiar>::dlugoscW()
{
    double wynik;
    wynik = sqrt(pow(tab[0], 2) + pow(tab[1], 2));
    return wynik;
}

/**
 * @brief Funckja porownywania do siebie wektorow pod wzgledem ich dlugosci (wykorzystywane sa powyzsze funkcje)
 * 
 * @tparam Wymiar wektora
 * @param ktos wektor porownywany
 * @return true prawda gdy rowne
 * @return false falsz gdy nierowne
 */

template <int Wymiar>

bool Vector<Wymiar>::operator==(Vector<Wymiar> ktos)
{
    if (this->porownanie(ktos) == true)
    {
        return true;
    }
    return false;
}

typedef Vector<3> vector3d;

#endif
