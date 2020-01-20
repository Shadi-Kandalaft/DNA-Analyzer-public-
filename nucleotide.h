//
// Created by shadikanda on 10/4/19.
//

#ifndef DNA_ANALYZER_NUCLEOTIDE_H
#define DNA_ANALYZER_NUCLEOTIDE_H

#include "string_class.h"

class Nucleotide{

public:

    Nucleotide();
    Nucleotide(char nuc);
    ~Nucleotide();

    Nucleotide& operator = (const Nucleotide& nuc);
    Nucleotide& operator = (char nuc);

    char getNuc() const;

    bool operator == (const Nucleotide& nuc) const;  // out of the class so we won't make an access to the object's parts
    bool operator != (const Nucleotide& nuc);
    bool operator < (const Nucleotide& nuc) const;

    friend std::ostream& operator << (std::ostream& os,const Nucleotide& nuc);
    bool isDnaNuc(char nuc) const;

private:

    char m_nuc;
};

inline Nucleotide::Nucleotide() {
    m_nuc = '\0';
}

inline Nucleotide::Nucleotide(char nuc) {
    if(isDnaNuc(nuc)){
        m_nuc = nuc;
    }
    else{
        std::cout << nuc << " is not a nucleotide!" << std::endl;
        m_nuc = '\0';
    }
}

inline Nucleotide::~Nucleotide() {}


inline bool Nucleotide::isDnaNuc(char nuc) const{
    return (nuc == 'A' || nuc == 'T' || nuc == 'C' || nuc == 'G' || nuc == '\0');
}

inline Nucleotide &Nucleotide::operator=(const Nucleotide &nuc) {
    m_nuc = nuc.m_nuc;
    return *this;
}

inline Nucleotide &Nucleotide::operator=(const char nuc) {
    m_nuc = nuc;
    return *this;
}

inline char Nucleotide::getNuc() const {
    return this->m_nuc;
}

inline bool Nucleotide::operator==(const Nucleotide &nuc) const{
    return (this->getNuc() == nuc.getNuc());
}

inline bool Nucleotide::operator!=(const Nucleotide &nuc) {
    return !(*this == nuc);
}

std::ostream &operator<<(std::ostream &os, const Nucleotide &nuc);


#endif //DNA_ANALYZER_NUCLEOTIDE_H
