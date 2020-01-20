//
// Created by shadikanda on 9/3/19.
//

#ifndef CLASS_STRING_STRING_CLASS_H
#define CLASS_STRING_STRING_CLASS_H

#endif //CLASS_STRING_STRING_CLASS_H


#include <cstddef>
#include <iostream>
#include <cstring>

class String{

private:
    char* data;
    //size_t str_len;

public:
    /*If we add explicit we can't just enter in the main() : String str = "Shadi"; */
    String(): data(NULL){}
    String(const char* str );
    String(const String& str);
    String(const std::string& str);
    ~String();

    size_t getLen() const;
    String& operator = (const String& str);
    String& operator += (const String& str);

    bool operator == (const String& str2) const;
    bool operator != (const String& str2);
    bool operator < (const String& str2) const;
    bool operator <= (const String& str2);
    bool operator > (const String& str2);
    bool operator >= (const String& str2);
    friend int my_strcmp(const String& str1, const String& str2);
    friend std::ostream& operator << (std::ostream& os, const String& str);
    const char &operator[](size_t n)const;

};

inline size_t String::getLen() const {
    return strlen(data);
}


inline bool String::operator == (const String& str2) const{
    return !(my_strcmp(*this, str2));
}

inline bool String::operator != (const String& str2){
    return (my_strcmp(*this, str2));
}

inline bool String::operator < (const String& str2) const{
    return (my_strcmp(*this, str2) < 0);
}

inline bool String::operator <= (const String& str2){
    return (my_strcmp(*this, str2) <= 0);
}

inline bool String::operator > (const String& str2){
    return (my_strcmp(*this, str2) > 0);
}

inline bool String::operator >= (const String& str2){
    return (my_strcmp(*this, str2) >= 0);
}

inline const char &String::operator[](size_t n) const {
    return this->data[n];
}



inline int my_strcmp(const String& str1, const String& str2){
    size_t i =0, j = 0, l = str1.getLen();
    int n = 0;
    while(i < l && 0 == n){
        n =  str1.data[i++] - str2.data[j++];
    }
    return n;
}

std::ostream& operator << (std::ostream& os, const String& t);

