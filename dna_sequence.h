//
// Created by shadikanda on 10/4/19.
//

#ifndef DNA_ANALYZER_DNA_SEQUENCE_H
#define DNA_ANALYZER_DNA_SEQUENCE_H

//#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include "nucleotide.h"

typedef std::pair<const char, const char> nuc_pair;
typedef std::map<const char, const char> nuc_map;

class DnaSequence{

public:
    DnaSequence(const char* path );
    DnaSequence(const String& str);
    DnaSequence();
//    DnaSequence(const String& path);
    ~DnaSequence();

    DnaSequence& operator = (const DnaSequence& dna);
    DnaSequence& operator = (const char* data);
    DnaSequence& operator = (const String& str);
    DnaSequence& operator = (Nucleotide* data);

    bool isDna(const char* data) const;
    bool isDna(const String& data) const;
    bool isDna(const std::string& data) const;

    const Nucleotide* getData() const;
//    nuc_map getMap() const ;
    size_t getLen() const;
    size_t getCalc() const;

    bool operator == (const DnaSequence& dna) const;  // out of the class so we won't make an access to the object's parts
    bool operator != (const DnaSequence& dna) const;
    Nucleotide operator [] (size_t n) const;
    DnaSequence& getComplementary(const DnaSequence& dna);
    Nucleotide getPair(const Nucleotide&nuc);
    void replace(const char nuc, size_t index);

    size_t subSeq(const DnaSequence& dna); // Not inline
    size_t countSubSeq(const DnaSequence& dna);
    size_t* findAllSubSeq(const DnaSequence& dna);
//    void replace(const char nuc);
//    size_t* findAllConsesusSeq();
    void slice(const DnaSequence& dna, size_t begin, size_t end);
    void save_to_file(const char* path);
    friend std::ostream& operator << (std::ostream& os,const DnaSequence& dna);
//    friend std::ostream &operator<<(std::ostream &os, const char* str);


private:

    Nucleotide* m_data;
    size_t m_length;
    nuc_map pairs;
};

inline DnaSequence::DnaSequence(const char *path) {
    std::ifstream file(path);
    std::string data;

    if (file.is_open()){
        getline (file,data);
        file.close();
    }
    else{
        std::cout << "Unable to open file";
        m_data = NULL;
        m_length = 0;
        return ;
    }

    if(isDna(data)){
        size_t size = data.length(), i = 0;
        m_data = new Nucleotide[size + 1] ;
        for(; i < size; ++i){
            m_data[i] = data[i];
        }
        m_data[size] = '\0';
        m_length = getCalc();
    }
    else{
        std::cout << "Not a DNA sequence!" << std::endl;
        m_data = NULL;
        return ;
    }
    pairs.insert(std::pair< char,  char>('G', 'C'));
    pairs.insert(std::pair< char,  char>('C', 'G'));
    pairs.insert(std::pair< char,  char>('T', 'A'));
    pairs.insert(std::pair< char,  char>('A', 'T'));
}

inline DnaSequence::DnaSequence(const String &str){
    if(isDna(str)){
        size_t size = str.getLen(), i = 0;
        m_data = new Nucleotide[size + 1] ;
        for(; i < size; ++i){
            m_data[i] = str[i];
        }
        m_data[size] = '\0';
        m_length = getCalc();
    }
    else{
        std::cout << "Not a DNA sequence!" << std::endl;
        m_data = NULL;
        m_length = 0;
        return ;
    }

    pairs.insert(nuc_pair('G', 'C'));
    pairs.insert(nuc_pair('C', 'G'));
    pairs.insert(nuc_pair('T', 'A'));
    pairs.insert(nuc_pair('A', 'T'));
}


inline DnaSequence::DnaSequence() {
    m_data = NULL;
    m_length = 0;
    pairs.insert(nuc_pair('G', 'C'));
    pairs.insert(nuc_pair('C', 'G'));
    pairs.insert(nuc_pair('T', 'A'));
    pairs.insert(nuc_pair('A', 'T'));
}

inline DnaSequence::~DnaSequence() {
//    delete[] m_data;
}

inline const Nucleotide* DnaSequence::getData() const{
    return m_data;
}

inline DnaSequence &DnaSequence::operator=(const DnaSequence &dna) {
    size_t size = dna.getLen(), i = 0;
    delete[] m_data;
    m_data = new Nucleotide[size+1];

    for(; i < size; i++){
        m_data[i] = dna.m_data[i];
    }
    m_data[size] = '\0';
    m_length = size;
    return *this;
}

inline DnaSequence &DnaSequence::operator=(const char *data) {
    size_t size = strlen(data), i = 0;
    delete[] m_data;
    m_data = new Nucleotide[size+1];

    for(; i < size; i++){
        m_data[i] = data[i];
    }
    m_data[size] = '\0';
    m_length = size;
    return *this;
}

inline DnaSequence &DnaSequence::operator=(const String &str) {
    size_t size = str.getLen(), i = 0;
    delete[] m_data;
    m_data = new Nucleotide[size+1];

    for(; i < size; i++){
        m_data[i] = (str[i]);
    }
    m_data[size] = '\0';
    m_length = size;
    return *this;
}


inline DnaSequence &DnaSequence::operator=(Nucleotide *data) {
    size_t size = 0, i = 0;
    delete[] m_data;
    while (data[size++]!='\0'){}
    m_data = new Nucleotide[size--];

    for(; i < size; i++){
        m_data[i] = (data[i]);
    }
    m_data[size] = '\0';
    m_length = size;
    return *this;
}

inline bool DnaSequence::operator == (const DnaSequence& dna)const {
    size_t i = 0, j = 0, l1 = this->getLen();

    if (l1 != dna.getLen()){
        return false;
    }

    while(m_data[i++] == dna.m_data[j++]){}
    return (m_data[i] == '\0');
}

inline bool DnaSequence::operator != (const DnaSequence& dna) const {
    return !(*this==dna);
}


std::ostream &operator<<(std::ostream &os,const DnaSequence& dna);

//std::ostream &operator<<(std::ostream &os, const char* str);

inline Nucleotide DnaSequence::operator[](size_t n) const {
    return this->m_data[n];
}


inline bool DnaSequence::isDna(const char *data) const{
    while(*data == 'A' || *data == 'T' || *data == 'C' || *data == 'G'){
        ++data;
    }
    return(!(*data));
}

/**/
inline bool DnaSequence::isDna(const String &data) const {
    size_t  i = 0;
    while(data[i++] == 'A' || data[i++] == 'T' || data[i++] == 'C' || data[i++] == 'G'){}
    return(!(data[--i]));
}
/**/
inline bool DnaSequence::isDna(const std::string &data) const {
    size_t  i = 0;
    while(data[i] == 'A' || data[i] == 'T' || data[i] == 'C' || data[i] == 'G'){
        ++i;
    }
    return(i == data.length());
}

inline size_t DnaSequence::getCalc() const {
    size_t c = 0;
    while(m_data[c++]!='\0'){}
    return --c;
}

inline size_t DnaSequence::getLen() const {
    return m_length;
}

inline void DnaSequence::save_to_file(const char *path) {
    std::ofstream new_file;
    new_file.open(path);
    new_file << *this;
    new_file.close();
}

inline void DnaSequence::slice(const DnaSequence &dna, size_t begin, size_t end) {
    size_t size = dna.getLen(), i = 0;
    delete[] m_data;

    if(begin >= size){
        m_data = NULL;
    }

    if(end > size){
        size =size - begin - 1;
    }
    else{
        size = end - begin - 1;
    }
    m_data = new Nucleotide[size + 1];

    for(; i < size; i++){
        m_data[i] = dna.m_data[i + begin + 1];
    }
    m_data[size] = '\0';
}

inline DnaSequence &DnaSequence::getComplementary(const DnaSequence &dna) {
    size_t size = dna.getLen(), i = 0;

    m_data = new Nucleotide[size + 1] ;
    for(; i < size; ++i){
        m_data[i] = this->getPair(dna[size - i - 1]);
    }
    m_data[size] = '\0';

    return *this;
}

inline Nucleotide DnaSequence::getPair(const Nucleotide &nuc) {
    nuc_map::iterator itr;

    for (itr = pairs.begin(); itr != pairs.end(); ++itr) {
        if(itr->first == nuc.getNuc()){
            return Nucleotide(itr->second);
        }
    }
    return Nucleotide();
}

inline size_t DnaSequence::countSubSeq(const DnaSequence& dna){
    size_t index = 0, c = 0, size = this->getLen(), size_sub = dna.getLen(), size_delta;
    size_delta = size - size_sub;
    DnaSequence temp;
    temp = this->m_data;

    while (index < size_delta){
        index = temp.subSeq(dna);
        if(index != size){
            temp.slice(*this, index, size);
            ++c;
        }
    }

    delete[] temp.getData();

    return c;
}

inline size_t *DnaSequence::findAllSubSeq(const DnaSequence &dna) {
    size_t size_arr = this->countSubSeq(dna);
    size_t *arr = new size_t[size_arr];
    size_t index = 0, c = 0, size = this->getLen(), size_sub = dna.getLen(), size_delta;
    size_delta = size - size_sub;
    DnaSequence temp;
    temp = this->m_data;

    while (index < size_delta){
        index = temp.subSeq(dna);
        if(index != size){
            temp.slice(*this, index, size);
            arr[c++] = index;
        }
    }

    delete[] temp.getData();
    return arr;
}

inline void DnaSequence::replace(const char nuc, size_t index) {
    Nucleotide new_nuc(nuc);
    if(new_nuc.getNuc() != '\0')
    {
        m_data[index] = new_nuc;
    }
    else{
        std::cout << "failed to create a nucleotide!" << std::endl;
    }
}


//inline nuc_map DnaSequence::getMap() const{
//    return this->pairs;
//}


#endif //DNA_ANALYZER_DNA_SEQUENCE_H
