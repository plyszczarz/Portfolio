#ifndef MATRIX_HH
#define MATRIX_HH

#include <iostream>
#include "vector.hh"
#include <cmath>

using namespace std;


/*!
 * \brief  Class Matrix that contains array with 4 variables type of double
 *
 *  Tutaj trzeba opisac szablon. Jakie pojecie on modeluje
 *  i jakie ma glowne cechy.
 */
template <typename rodzaj, int Wymiar>
class matrix
{

  double tab[Wymiar][Wymiar];

public:

/**
 * @brief konstruktor dla macierzy z dwoma parametrami
 * 
 * @param a pierwsza wspolrzedna
 * @param b druga wspolrzedna
 * @return macierz o rozmiarach rownych parametrom 
 */

  rodzaj operator()(const int a, const int b) const
  {
    return tab[a][b];
  }

/**
 * @brief konstruktor dla macierzy z dwoma parametrami
 * ten konstruktor od poprzedniego rozni sie tym iz tak owa macierz moze sie zmieniac
 * @param a pierwsza wspolrzedna
 * @param b druga wspolrzedna
 * @return macierz o rozmiarach rownych parametrom 
 */

  rodzaj &operator()(const int a, const int b)
  {
    return tab[a][b];
  }
/**
 * @brief Delkaracje funkcji
 */
  matrix<rodzaj, Wymiar> przypisanieZZZ(double wspolczynnik);
  matrix<rodzaj, Wymiar> przypisanieXXX(double wspolczynnik);
  matrix<rodzaj, Wymiar> przypisanieYYY(double wspolczynnik);
  Vector<Wymiar> operator*(Vector<Wymiar> cos);
};
/**
 * @brief Funckja przeciazenia operacji mnozenia wektora przez macierz
 * 
 * @tparam rodzaj rodzaj macierzy
 * @tparam Wymiar macierzy
 * @param cos macierz przez ktora mnozymy
 * @return vector<Wymiar> 
 */
template <typename rodzaj, int Wymiar>
Vector<Wymiar> matrix<rodzaj, Wymiar>::operator*(Vector<Wymiar> cos)
{
  Vector<Wymiar> wynik;
  for (int i = 0; i < Wymiar; i++)
  {
    for (int j = 0; j < Wymiar; j++)
    {
      wynik[i] += tab[i][j] * cos[j];
    }
  }
  return wynik;
}

/**
 * @brief przypisanie wartosci dla maciezy obroto w okol osi Z
 * 
 * @tparam rodzaj macierzy
 * @tparam Wymiar macierzy
 * @param wspolczynnik wartosc obortu w katach
 * @return matrix<rodzaj, Wymiar> 
 */

template <typename rodzaj, int Wymiar>

matrix<rodzaj, Wymiar> matrix<rodzaj, Wymiar>::przypisanieZZZ(double wspolczynnik)
{
  double a;
  a = (wspolczynnik * 3.14 / 180.0);
  tab[0][0]= cos(a);
  tab[0][1]= -sin(a);
  tab[0][2]= 0;
  tab[1][0]= sin(a);
  tab[1][1]= cos(a);
  tab[1][2]= 0;
  tab[2][0]= 0;
  tab[2][1]= 0;
  tab[2][2]= 1;
  return *this;
}

/**
 * @brief przypisanie wartosci dla maciezy obroto w okol osi X
 * 
 * @tparam rodzaj macierzy
 * @tparam Wymiar macierzy
 * @param wspolczynnik wartosc obortu w katach
 * @return matrix<rodzaj, Wymiar> 
 */

template <typename rodzaj, int Wymiar>

matrix<rodzaj, Wymiar> matrix<rodzaj, Wymiar>::przypisanieXXX(double wspolczynnik)
{
  double a;
  a = (wspolczynnik * 3.14 / 180.0);
  // tab[0][0]= 1;
  // tab[0][1]= 0;
  // tab[0][2]= 0;
  // tab[1][0]= 0;
  // tab[1][1]= cos(a);
  // tab[1][2]= -sin(a);
  // tab[2][0]= 0;
  // tab[2][1]= sin(a);
  // tab[2][2]= cos(a);
  tab[0][0]= cos(a);
  tab[0][1]= -sin(a);
  tab[0][2]= 0;
  tab[1][0]= sin(a);
  tab[1][1]= cos(a);
  tab[1][2]= 0;
  tab[2][0]= 0;
  tab[2][1]= 0;
  tab[2][2]= 1;
  return *this;
}

/**
 * @brief przypisanie wartosci dla maciezy obroto w okol osi Y
 * 
 * @tparam rodzaj macierzy
 * @tparam Wymiar macierzy
 * @param wspolczynnik wartosc obortu w katach
 * @return matrix<rodzaj, Wymiar> 
 */

template <typename rodzaj, int Wymiar>

matrix<rodzaj, Wymiar> matrix<rodzaj, Wymiar>::przypisanieYYY(double wspolczynnik)
{
  double a;
  a = (wspolczynnik * 3.14 / 180.0);
  tab[0][0]= cos(a);
  tab[0][1]= 0;
  tab[0][2]= sin(a);
  tab[1][0]= 0;
  tab[1][1]= 1;
  tab[1][2]= 0;
  tab[2][0]= -sin(a);
  tab[2][1]= 0;
  tab[2][2]= cos(a);
  return *this;
}

/*!
 * \brief Przeciążenie dla wejścia musi także być szablonem
 * 
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
template <typename rodzaj, int Wymiar>
inline std::ostream &operator<<(std::ostream &Strm, const matrix<rodzaj, Wymiar> &Wek)
{
  for (int i = 0; i < Wymiar; i++)
  {
    for (int j = 0; j < Wymiar; j++)
    {
//      Strm << Mac(i, j);
    }
  }
  cout << endl;
  return Strm;
}



typedef matrix<double, 3>  matrix3x3;

#endif
