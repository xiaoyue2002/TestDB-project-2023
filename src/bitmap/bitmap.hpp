#pragma once
#include <vector>
#include <climits>
#include "../defines.h"
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

template <typename T>
class Bitmap{
public:
    T size;
    char * bits;

    size_t bitmap_size;
    size_t bits_size;

    Bitmap(){}
    Bitmap(T n): size(n){
        size_t byteSize = (n + CHAR_BIT - 1) / CHAR_BIT;
        byteSize = std::max(CHAR_STRIDE, byteSize);
        bits = new char[byteSize];
        std::memset(bits, 0, byteSize);
        bitmap_size = sizeof(char) * byteSize + sizeof(size);
        bits_size = sizeof(char) * byteSize;
    };

    Bitmap<T>& operator=(const Bitmap<T>& map) {
    if (this != &map) {
        size = map.size;
        bits_size = map.bits_size;
        bits = new char[bits_size / sizeof(char)];
        std::memcpy(bits, map.bits, bits_size);
        bitmap_size = map.bitmap_size;
    }
    return *this;
}

    Bitmap<T> (const Bitmap<T> & map){
        size = map.size;
        bits_size = map.bits_size;
        bits = new char[bits_size / sizeof(char)];
        memcpy(bits, map.bits, bits_size);
        bitmap_size = map.bitmap_size;
        
    }

    ~Bitmap(){delete bits; bits=nullptr;}

    void set(T index, bool value){
        if (index >= size) return;
        if (value)
            bits[index / CHAR_BIT] |= (1 << (index % CHAR_BIT));
        else
            bits[index / CHAR_BIT] &= ~(1 << (index % CHAR_BIT));
    };

    void show() const{
        for(T i = 0; i < size; i++){
            auto res = (bits[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) != 0;
            std::cout<<int(res)<<" ";
        }
        std::cout<<std::endl;
    }

    void print(std::ofstream& file, size_t& offset){
        file << "= [" << offset << ": " << offset+sizeof(size) << "] size : " << size << std::endl;
        offset += sizeof(size);
        file << "= [" << offset << ": " << offset + bitmap_size - sizeof(size) << "] bits : ";
        // std::cout << size << endl;
        // std::cout << "bits: "<< bits << endl;
        for(T i = 0; i < size; i++){
            // std::cout << "i: "<< i << std::endl;
            auto res = (bits[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) != 0;
            file << int(res) <<" ";
        }
        offset += bitmap_size - sizeof(size);
        file << std::endl;
    }

    std::string show_bits(){
        std::stringstream ss ;
        for(T i = 0; i < size; i++){
            auto res = (bits[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) != 0;
            ss << int(res) <<" ";
        }
        return ss.str();
    }

    void print_bits(std::ofstream& file){
        for(T i = 0; i < size; i++){
            auto res = (bits[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) != 0;
            file << int(res) <<" ";
        }
    }

    bool get(T index) const{
        if (index >= size) return false;
        return (bits[index / CHAR_BIT] & (1 << (index % CHAR_BIT))) != 0;
    };

    std::vector<T> get_all_used() const{
        std::vector<T> ret;
        for (T i = 0 ; i < size ; i++)
            if (get(i)) ret.push_back(i); 
        return ret;
    }

    T findFirstEmptySlot() const {
        for (T i = 0; i < size; ++i)
            if (!get(i)) return i;
        return -1;
    };
};