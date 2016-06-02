#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

//#include <gmp.h>
//#include <iosfwd>
using namespace std;
struct big_integer
{
    big_integer();
    big_integer(big_integer const& other);
    big_integer(int new_int);
    big_integer(unsigned int a);
    big_integer(unsigned long long new_int);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);

    std::vector <unsigned int> mass;
    int sign;
private:
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif
