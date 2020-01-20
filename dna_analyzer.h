//
// Created by shadikanda on 10/4/19.
//

#ifndef DNA_ANALYZER_DNA_ANALYZER_H
#define DNA_ANALYZER_DNA_ANALYZER_H

#include <vector>
#include "dna_sequence.h"

class DnaSequenceAnalyzer{

public:
    DnaSequenceAnalyzer(String& dna, const String& name = "");
    DnaSequenceAnalyzer(const DnaSequence& dna, const String& name = "");
    DnaSequenceAnalyzer();
    void load(const char* path, const String& name = "");
    void save(const char* file_name = "");
    void dup(const DnaSequenceAnalyzer& dna, const String& name = "");
    ~DnaSequenceAnalyzer();

    DnaSequenceAnalyzer slice(size_t from_ind, size_t to_ind, const String& name = "");
    DnaSequenceAnalyzer replace(char nuc, size_t index, const String& name = "");
    String getName() const;
    size_t getId() const;
    String getStatus() const;
    DnaSequence getDnaSequence() const;
    bool isDna(const String &data) const;
    friend std::ostream& operator << (std::ostream& os,const DnaSequenceAnalyzer& dna);

private:
    size_t m_id;
    String m_name;
    DnaSequence m_dna_seq;
    String m_status;
    static size_t id;
};

inline DnaSequenceAnalyzer::DnaSequenceAnalyzer(String &dna, const String &name) {
    if(isDna(dna)) {
        m_id = ++id;
        m_dna_seq = dna;
        m_status = "new";
        if(name == ""){
            char str[20];
            sprintf(str, "%lu", m_id);
            String temp(str);
            m_name = "seq";
            m_name += temp;
        }
        else{
            m_name = name;
        }
    }
    else{
        m_id = 0;
        m_name = " None ";
        m_dna_seq = dna;
        m_status = "";
    }
}

inline DnaSequenceAnalyzer::DnaSequenceAnalyzer(const DnaSequence &dna, const String &name) {
    m_id = ++id;
    m_dna_seq = dna;
    m_status = "new";
    if(name == ""){
        char str[20];
        sprintf(str, "%lu", m_id);
        String temp(str);
        m_name = "seq_";
        m_name += temp;
    }
    else{
        m_name = name;
    }
}

inline DnaSequenceAnalyzer::DnaSequenceAnalyzer() {
    m_id = 0;
    m_name = "";
    m_dna_seq = "";
    m_status = "";
}

inline DnaSequenceAnalyzer::~DnaSequenceAnalyzer() {
    delete[] m_dna_seq.getData();
}

inline size_t DnaSequenceAnalyzer::getId() const {
    return m_id;
}


inline String DnaSequenceAnalyzer::getStatus() const {
    return m_status;
}

inline void DnaSequenceAnalyzer::load(const char *path, const String &name) {
    DnaSequence dna(path);
    //if(isDna(dna)){
    m_id = ++id;
    m_dna_seq = dna;
    m_status = "new";
    if(name == ""){
        char str[20];
        sprintf(str, "%lu", m_id);
        String temp(str);
        m_name = "seq";
        m_name += temp;
    }
    else{
        m_name = name;
    }
//    }
//    else{
//        m_id = 0;
//        m_name = "";
//        m_dna_seq = "";
//        m_status = "";
//    }
}
//
inline void DnaSequenceAnalyzer::dup(const DnaSequenceAnalyzer& dna, const String& name){
    m_id = ++id;
    m_dna_seq = dna.getDnaSequence();
    m_status = "new";
    if(name == ""){
        char str[20];
        sprintf(str, "%lu", m_id);
        String temp(str);
        m_name = "seq_";
        m_name += temp;
    }
    else{
        m_name = name;
    }
}

inline void DnaSequenceAnalyzer::save(const char* file_name) {
    std::ofstream new_file;
    String dna = "/home/shadikanda/CLionProjects/DNA_Design/";
    String txt = ".rawdna";
    size_t len1, len2, i = 0;
    char *temp = NULL;

    if(!strcmp(file_name,""))
        dna += this->getName();
    else
        dna += file_name;

    len1 = dna.getLen();
    len2 = txt.getLen();
    temp = (char*)malloc(len1 + len2);

    for(; i < len1; ++i)
        temp[i] = dna[i];

    for(i = 0; i < len2; ++i)
        temp[i + len1] = txt[i];

    temp[len1 + len2] = '\0';

    new_file.open(temp);
    new_file << *this;
    new_file.close();

    delete [] temp;
    free(temp);

    m_status = "up to date";
}

// TODO: adapt for nucs.
inline bool DnaSequenceAnalyzer::isDna(const String &data) const {
    size_t  i = 0;
    while(data[i] == 'A' || data[i] == 'T' || data[i] == 'C' || data[i] == 'G'){
        ++i;
    }
    return(!(data[i]));
}

inline DnaSequence DnaSequenceAnalyzer::getDnaSequence() const {
    return m_dna_seq;
}

inline String DnaSequenceAnalyzer::getName() const {
    return m_name;
}

inline DnaSequenceAnalyzer DnaSequenceAnalyzer::replace(char nuc, size_t index, const String& name) {
    if(!my_strcmp(name, "")){
        m_dna_seq.replace(nuc, index);
        m_status = "modified";
        DnaSequenceAnalyzer dna_null;
        return dna_null;
    }
    else if(!my_strcmp(name, "@@")){
        char str[20];
        sprintf(str, "%lu", m_id);
        String new_name(name);
        new_name += "_r";
        new_name += str;

        DnaSequenceAnalyzer dna_a(m_dna_seq, new_name);
        dna_a.getDnaSequence().replace(nuc, index);
        return dna_a;
    }
    else{
        DnaSequenceAnalyzer dna_a(m_dna_seq, name);
        dna_a.getDnaSequence().replace(nuc, index);
        return dna_a;
    }
}



std::ostream &operator<<(std::ostream &os, const DnaSequenceAnalyzer &dna);
//
//typedef std::vector<DnaSequenceAnalyzer*> dna_vector;
//
//class DNADatabase{
//public:
////    DNADatabase();
//    ~DNADatabase();
////    dna_vector getDnas();
////private:
////    dna_vector m_dnas;
//    static dna_vector dnas;
//};
//
//inline DNADatabase::~DNADatabase() {}

//inline dna_vector DNADatabase::getDnas() {
//    return m_dnas;
//}
//
//DNADatabase::DNADatabase() {
//    m_dnas = dnas;
//}


#endif //DNA_ANALYZER_DNA_ANALYZER_H
