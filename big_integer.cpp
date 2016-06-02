#include <bits/stdc++.h>

#include "big_integer.h"

unsigned long long p = 1 << 30;
const unsigned long long mod = p * 4;


void my_resize(big_integer &a) {
    if(a.mass.empty())
        a.mass.push_back(0);
    while(a.mass.size() > 1 && a.mass.back() == 0)
        a.mass.pop_back();
    if(a.mass.size() == 1 && a.mass.back() == 0)
        a.sign = 0;
}

big_integer::big_integer() : mass(1, 0), sign(0)
{
    this->mass.clear();
    this->mass.push_back(0);
    this->sign = 0;
}

big_integer::big_integer(big_integer const& new_big)
{
    this->mass = new_big.mass;
    this->sign = new_big.sign;
}
big_integer::big_integer(unsigned int new_int) {
    mass.resize(1);
    mass[0] = new_int;
    sign = 0;
}
big_integer::big_integer(unsigned long long new_int) {
    mass.push_back(new_int % mod);
    if (new_int> mod) {
        mass.push_back(new_int / mod);
    }
    sign = 0;
}


big_integer::big_integer(int new_int)
{
    new_int < 0 ? (sign = 1, new_int = -new_int) : sign = 0;
    mass.resize(1);
    mass[0] = new_int;
}

/*big_integer::big_integer(std::string const& line)
{
    int start;
    big_integer ten(10);
    line[0] == '-' ? (start = 1, this->sign = 1) : (start = 0, this->sign = 0);
    for (int i = start; i < (int) line.size(); i++)
    {
        *this *= ten;
        *this += line[i] - '0';
    }
}*/
big_integer::big_integer(std::string const& str)
{
    int i;
    //cout << "str " << str << "\n";
    big_integer ten(10);
    str[0] == '-' ? i = 1 : i = 0;
    for (; i < (int) str.size(); i++)
    {
        *this *= ten;
        *this += str[i] - '0';
    }

    str[0] == '-' ? this->sign = 1 : this->sign = 0;
    //big_integer f = *this;
}

big_integer::~big_integer()
{

}

int compare(big_integer const& a, big_integer const& b) {

    if (a.sign != b.sign)
    {
        if(a.mass.size()==1 && b.mass.size()==1 && a.mass.back()==0 && b.mass.back()==0 )
        {
            return 0;
        }
        return b.sign - a.sign;
    }
    else
    {
        if (a.mass.size() != (int) b.mass.size()) {

           return (a.sign == 1) == (a.mass.size() < b.mass.size()) ?  1 : -1;
        }
        else
        {
            int i;
            for (i = (int) a.mass.size() - 1; i >= 0 && a.mass[i] == b.mass[i]; --i);
            {

                if (i < 0) {
                    return 0;
                }
            }
            return (a.mass[i] < b.mass[i] ? -1 : 1) * (a.sign != 1 ?  1 : -1);
        }
    }
}

big_integer& big_integer::operator=(big_integer const& a)
{
    this->mass = a.mass;
    this->sign = a.sign;
    return *this;
}


bool operator==(big_integer const& a, big_integer const& b) {
    return compare(a,b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return compare(a,b) != 0;
}

bool operator>(big_integer const& a, big_integer const& b) {
    return compare(a,b) == 1;
}

bool operator<(big_integer const& a, big_integer const& b) {
    return compare(a,b) == -1;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return compare(a,b) != 1;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return compare(a,b) != -1;
}
void swap(big_integer& a, big_integer& b)
{
    big_integer temp;
    temp = a;
    a = b;
    b = temp;
}

big_integer operator-(big_integer a, big_integer const& b) {
    big_integer first = a, second = b, result;
    result.mass.clear();
    first.sign = second.sign = 0;
    if (a.sign != b.sign) {
        result.sign = a.sign;
        int m = max((int) first.mass.size(), (int) second.mass.size());
        result.mass.resize(m);
        first.mass.resize(m);
        second.mass.resize(m);
        long long carry = 0;
        for (int i = 0; i < m; ++i)
        {
            unsigned long long f = (unsigned long long) first.mass[i] +
            (unsigned long long) second.mass[i] + (unsigned long long) carry;
            result.mass[i] = f % mod;
            carry = f / mod;
        }
        if (carry)
        {
            result.mass.push_back(carry);
        }
    } else {
        if (first < second) {
            swap(first, second);
        }
        int sizeBig = max((int) first.mass.size(), (int) second.mass.size());
        first.mass.resize(sizeBig);
        second.mass.resize(sizeBig);

        long long carry = 0;
        for (int i = 0; i < sizeBig; ++i)
        {
            long long res2 = (long long)first.mass[i] - (long long)second.mass[i] - carry;
            carry = 0;
            if (res2 < 0)
            {
                res2 += mod;
                carry = 1;
            }
            result.mass.push_back(res2);
        }
        while ( result.mass.size()!=1 && !result.mass.back())
        {
            result.mass.pop_back();
        }
        if (result.mass.size() != 1 || result.mass[0] != 0)
        {
            result.sign = (a > b ? 0 : 1);
        }
    }
    my_resize(result);
    return result;
}

big_integer operator+(big_integer a, big_integer const& b) {
    big_integer first = a, second = b;
    first.sign = a.sign;
    b.sign == 0 ? second.sign = 1 : second.sign = 0;
    return (first - second);
}

big_integer operator*(big_integer a, big_integer const& b)
{
    big_integer first = a, second = b, result;
    result.mass.clear();
    if ((int) a.mass.size() < (int) b.mass.size())
    {
        swap(first, second);
    }
    for (int i = 0; i < (int) second.mass.size(); i++)
    {
        big_integer pow;
        pow.mass.clear();
        for (int j = 0; j < i; j++)
        {
            pow.mass.push_back(0);
        }
        long long carry = 0;
        for (int j = 0; j < (int) first.mass.size(); j++)
        {
            unsigned long long f = (unsigned long long) first.mass[j] *
            (unsigned long long) second.mass[i] + (unsigned long long) carry;
            pow.mass.push_back(f % mod);
            carry = f / mod;
        }
        if (carry)
        {
            pow.mass.push_back(carry);
        }
        result = result + pow;
    }
    result.sign = a.sign != b.sign;
    my_resize(result);
    return result;
}

unsigned int binary (big_integer dop, big_integer second) {
    unsigned long long l = 0;
    unsigned long long r = mod;
    while (l < r -1) {
        unsigned long long m = (l+r)/2;
        big_integer multy= second * m;
        if (multy > dop)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    return l;
}

/*big_integer div_long_short (big_integer &first, int second) {
    int carry = 0;
    for (int i=(int)first.mass.size()-1; i>=0; --i)
    {
        long long cur = first.mass[i] + carry * 1ll *  mod;
        first.mass[i] = int (cur / second);
        carry = int (cur % second);
    }
    //while (a.size() > 1 && a.back() == 0)
    //	a.pop_back();
    my_resize(first);
    return first;
}*/


big_integer operator/(big_integer a, big_integer const& b) {
    big_integer aa = a, bb= b;
    aa.sign= bb.sign = 0;
    if (aa < bb)
    {
        return 0;
    }
    big_integer first = a, second = b, dop, result;
    result.mass.clear();
    dop.mass.clear();
    first.sign = second.sign = 0;
    result.sign= ((a.sign != b.sign) ? 1 : 0);
   /* if ( second.mass.size()==1)
    {
        result = div_long_short(first, second.mass[0]);
        reverse(result.mass.begin(), result.mass.end());
        return result;
    }*/
    while (first.mass.size() != 0) {
        dop.mass.insert(dop.mass.begin(), first.mass.back());
        first.mass.pop_back();
        unsigned int l = binary(dop, second);
        if (result.mass.size() != 1 || l != 0)
        {
            result.mass.push_back(l);
        }
        dop -= l * second;
        big_integer P = l * second;
        int ind = 0;
        while(!dop.mass.empty() && dop.mass.back() == 0)
            dop.mass.pop_back();
    }
    reverse(result.mass.begin(), result.mass.end());
    my_resize(result);
    return result;
}

big_integer operator%(big_integer a, big_integer const& b) {
    big_integer result;
    result.mass.clear();
    result.sign = a.sign;
    big_integer res = a/b;
    result = (a - res*b);
    return result;
}

big_integer& big_integer::operator+=(big_integer const& a)
{
    *this = *this + a;
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& a)
{
    *this = *this - a;
    return *this;
}

big_integer& big_integer::operator*=(big_integer const& a)
{
    *this = *this * a;
    return *this;
}

big_integer& big_integer::operator/=(big_integer const& a)
{
    *this = *this / a;
    return *this;
}
big_integer& big_integer::operator%=(big_integer const& a)
{
    *this = *this % a;
    return *this;
}
big_integer& big_integer::operator--()
{
    this->operator-=(1);
    return *this;
}

big_integer big_integer::operator--(int)
{
    big_integer t = *this;
    --(*this);
    return t;
}

big_integer& big_integer::operator++()
{
    this->operator+=(1);
    return *this;
}

big_integer big_integer::operator++(int)
{
    big_integer t = *this;
    ++(*this);
    return t;
}

big_integer double_code(big_integer a)
{
    if (a.sign == 0)
    {
        return a;
    }
    for (int i = 0; i < (int) a.mass.size(); i++)
    {
        a.mass[i] = ~a.mass[i];
    }
    return a;
}

big_integer operator&(big_integer a, big_integer const& b)
{
    big_integer first = double_code(a), second = double_code(b), result;
    result.mass.clear();
    result.sign = a.sign && b.sign;
    first.sign == 1 ? --first : first;
    second.sign == 1 ? --second : second;
    if (first.mass.size() > second.mass.size())
    {
        swap(first, second);
    }
    for (int i = 0; i < (int) second.mass.size(); i++)
    {
        if (i >= first.mass.size())
        {
            a.sign == 1 ? first.mass.push_back(numeric_limits<long long>::max()) : first.mass.push_back(0);
        }
        result.mass.push_back(first.mass[i] & second.mass[i]);
    }
    result.sign == 1 ? result = double_code(result + 1) : result = result;
    my_resize(result);
    return result;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    big_integer first = double_code(a), second = double_code(b), result;
    result.mass.clear();
    result.sign = a.sign || b.sign;
    first.sign == 1 ? --first : first;
    second.sign == 1 ? --second : second;
    if (first.mass.size() > second.mass.size())
    {
        swap(first, second);
    }
    for (int i = 0; i < (int) second.mass.size(); i++)
    {
        if (i >= first.mass.size())
        {
            a.sign == 1 ? first.mass.push_back(numeric_limits<long long>::max()) : first.mass.push_back(0);
        }
        result.mass.push_back(first.mass[i] | second.mass[i]);
    }
    result.sign == 1 ? result = double_code(result + 1) : result = result;
    my_resize(result);
    return result;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    big_integer first = double_code(a), second = double_code(b), result;
    result.mass.clear();
    result.sign = a.sign ^ b.sign;
    first.sign == 1 ? --first : first;
    second.sign == 1 ? --second : second;
    if (first.mass.size() > second.mass.size())
    {
        swap(first, second);
    }
    for (int i = 0; i < (int) second.mass.size(); i++)
    {
        if (i >= first.mass.size())
        {
            a.sign == 1 ? first.mass.push_back(numeric_limits<long long>::max()) : first.mass.push_back(0);
        }
        result.mass.push_back(first.mass[i] ^ second.mass[i]);
    }
    result.sign == 1 ? result = double_code(result + 1) : result = result;
    my_resize(result);
    return result;
}

big_integer operator<< (big_integer a , int b) {
    if (b < 0) {
        return (a >> (-b));
    }
    int count = b/32;
    int ost = b%32;
    unsigned int last  = 0;
    if (ost)
    {
        for (int i = 0; i < (int) a.mass.size(); ++i)
        {
            unsigned long long now = (unsigned long long) a.mass[i] << ost;
            a.mass[i] = (unsigned int) now % mod + last;
             if (now >= mod)
            {
                now >>= 32;
                last = now;
            }
            else
            {
                break;
            }
        }
        if (last)
        {
            a.mass.push_back(last);
        }
    }

    int k = (int)a.mass.size();
    a.mass.resize(k + count);
    for (int i = 0; i < (int) count; i++)
    {
      a.mass[i + k] = a.mass[i];
    }
    for (int i = 0; i < count; i++) {
        a.mass[i]= 0;
    }
    if (a.mass.back() == 0 && a.mass.size() == 1)
    {
        a.sign=0;
    }
        return a;

}


big_integer operator>> (big_integer a , int b) {

    if (b < 0) {
        return (a << (-b));
    }
    if ( a< 0)
    {
        a =double_code(a);
        --a;
    }
    int count = b/32;
    int ost = b%32;
    unsigned long long last  = 0;
    int k = (int)a.mass.size();
    if (k - count  < 0) {
        return big_integer();
    } if ( count > 0)
        {
        for (int i = count; i < (int) a.mass.size(); i++)
        {

            a.mass[i - count] = a.mass[i];
            a.mass[i] = 0;
        }
    }

    if (ost)
    {
        unsigned int M = 1 << ost;
        for (int i = (int) a.mass.size() - count - 1; i >= 0; --i)
        {
            unsigned long long f = (unsigned long long) a.mass[i] + (last << 32);
            last = f % M;
            a.mass[i] = f >> ost;
        }
        if (a.sign == 1 ){
        a.mass[(int) a.mass.size() - count - 1] += (M - 1) * (1 << (32 - ost));
        }
    }

    a = a.sign == 1 ? double_code(a + 1) :  a;
    my_resize(a);
    return a;
}

big_integer& big_integer::operator&=(big_integer const& a)
{
    *this = *this & a;
    return *this;
}

big_integer& big_integer::operator^=(big_integer const& a)
{
    *this = *this ^ a;
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& a)
{
    *this = *this | a;
    return *this;
}

big_integer& big_integer::operator>>=(int shift)
{
    *this = *this >> shift;
    return *this;
}

big_integer& big_integer::operator<<=(int shift)
{
    *this = *this << shift;
    return *this;
}

big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    big_integer a(*this);
    a.sign == 1 ? a.sign = 0 : a.sign = 1;
    return a;
}

big_integer big_integer::operator~() const
{
    big_integer a(*this);
    a += 1;
    a.sign = (a.sign + 1) % 2;
    return a;
}

std::string to_string(big_integer const& a)
{
     big_integer aa = a, nul(0);
     string s = "";
     int module = 1000000;
     while(aa != nul)
     {
        big_integer M = aa % module;
        int m = M.mass[0];
        string ss = "";
        while (m > 0)
        {
            ss += (char) (m % 10 + 48);
            m /= 10;
        }
        aa /= big_integer(module);
        if (aa != nul)
        {
            for (int i = ss.length(); i < 6; i++)
            {
                ss += "0";
            }
        }
        s += ss;
     }
     reverse(s.begin(), s.end());

     if (a.sign == 1)
     {
        if (s.empty())
        {
            return "0";
        }
            s = "-" + s;
     }
     return s.empty() ? "0" : s;
}

std::istream& operator>>(std::istream& s, big_integer& a)
{
    string str;
    s >> str;
    a = big_integer(str);
    return s;
}
std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    s << to_string(a);
    return s;
}




