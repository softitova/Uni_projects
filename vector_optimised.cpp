#include "vector_optimized.h"
#include <iostream>
#include<cassert>

opt_vector::opt_vector(){
    opt_size = 0;
    is_big = false;
}

opt_vector::opt_vector(const opt_vector& other) {
    if(is_big) {
        safe_delete();
    }
    if(!other.is_big) {
        small_number = other.small_number;
    } else {
        other.big_number->link_counter+=1;
        this->big_number = other.big_number;
    }
    is_big = other.is_big;
    opt_size = other.opt_size;
}

opt_vector::opt_vector(size_t sz, unsigned val) {
    if(sz>1) {
        is_big = true;
        big_number->data.resize(sz);
        big_number->data.push_back(val);
    } else {
        small_number = val;
    }
    opt_size = sz;
}
void opt_vector::safe_delete() {
    if(big_number->link_counter > 1) {
        big_number->link_counter--;
    } else {
        delete big_number;
    }
}

void opt_vector::make_alone(){
    if(is_big && big_number->link_counter>1) {
        my_vector* new_vector = new my_vector;
        big_number-> link_counter--;
        new_vector->data = big_number->data;
        new_vector->link_counter=1;
        std::swap(new_vector, big_number);
    }
}
opt_vector::~opt_vector() {
    if(is_big && big_number -> link_counter > 0) {
        safe_delete();
    }
}

void swap(opt_vector& a, opt_vector& b) {
    swap(a.is_big, b.is_big);
    swap(a.opt_size, b.opt_size);
    swap(a.small_number, b.small_number);
}

opt_vector &opt_vector::operator=(opt_vector const &other) {
    opt_vector r(other);
    swap(*this, r);
    return *this;
}

unsigned& opt_vector::operator[](size_t index) {
    assert(index<opt_size);
    return (is_big) ? big_number->data[index] : small_number;
}

unsigned const& opt_vector::operator[](size_t index) const {
    assert(index<opt_size);
    return (is_big) ? big_number->data[index] : small_number;
}

size_t opt_vector::size() const {
    return opt_size;
}

unsigned &opt_vector::back() {
    return (is_big) ? big_number->data.back() : small_number;
}

unsigned const &opt_vector::back() const  {
    return (is_big) ? big_number->data.back() : small_number;
}

void opt_vector::resize(size_t new_size) {
    if (is_big) {
        make_alone();
    }
    if (new_size == 1) {
        if(is_big) {
            unsigned temp = big_number->data[0];
            small_number = temp;
            opt_size = 1;
            is_big = false;
        }
    } else {
        if (is_big) {
            big_number -> data.resize(new_size);
            opt_size = new_size;
        } else {
            unsigned temp = small_number;
            big_number -> data.resize(new_size);
            big_number -> data[0] = temp;
            is_big = true;
        }

    }
}


void opt_vector::push_back(unsigned a) {
    if (opt_size > 1) {
        make_alone();
        opt_size++;
        big_number -> data.push_back(a);
    } else if (opt_size == 1){
        unsigned temp = small_number;
        big_number = new my_vector;
        big_number -> data.resize(2);
        big_number -> data[0] = temp;
        big_number -> data[1] = a;
        big_number->link_counter = 1;
        is_big = true;
        opt_size = 2;
    } else {
        opt_size = 1;
        small_number = a;
    }
}

void opt_vector::pop_back() {
    if (opt_size > 2) {
        big_number -> data.pop_back();
    } else if (opt_size == 2) {
        is_big = false;
        unsigned temp = big_number -> data[0];
        small_number = temp;
    } else if (opt_size == 0) {
        return;
    }
    opt_size--;
}


void opt_vector::clear() {
    if (is_big) {
        make_alone();
        big_number -> data.clear();
    }
    is_big = false;
    opt_size = 0;
}


int main () {
    opt_vector a;
//    a.push_back(1);
//    a.push_back(2);
//    a.pop_back();
//    std::cout << a[0] << std::endl;
//    std::cout << a.is_big << std::endl;
//    a.push_back(3);
//    a.pop_back();
//    a.pop_back();
//    a.push_back(4);
//    a.push_back(5);
//    std::cout << a[0] <<  ' ' << a[1] << std::endl;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    opt_vector b(a);
    b = a;
    b = a;
//    b = a;
//    cout << a.is_big << "\n";
    //b.push_back(4);
    std::cout<<a.big_number->link_counter << " here ";
    std::cout << b.big_number->link_counter;
    //for (int i = 0; i < a.opt_size; ++i) std::cout << a[i] << ' '; std::cout << std::endl;
    //for (int i = 0; i < b.opt_size; ++i) std::cout << b[i] << ' '; std::cout << std::endl;

}
