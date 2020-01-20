//
// Created by shadikanda on 11/17/19.
//

#ifndef DNA_ANALYZER_DNA_DATABASE_H
#define DNA_ANALYZER_DNA_DATABASE_H

typedef std::vector<DnaSequenceAnalyzer*> dna_vector;

//////////////////  Database  /////////////////////

class DataBase{
public:
    ~DataBase();
    dna_vector getDnas();
    DnaSequenceAnalyzer* getDnaA(const char* dna_id);
    void pushBack(DnaSequenceAnalyzer* dna_a);

private:
    dna_vector m_dnas;
};

inline DataBase::~DataBase() {
    dna_vector::iterator it;
    for (it = m_dnas.begin(); it != m_dnas.end(); ++it){
        free(*it);
        it = m_dnas.erase(it);
    }
}

inline dna_vector DataBase::getDnas() {
    return m_dnas;
}

inline DnaSequenceAnalyzer *DataBase::getDnaA(const char* dna_id) {
    char temp[20];
    size_t id = 0;

    memcpy(temp, dna_id + 1, strlen(dna_id) - 1);
    id = size_t(strtol(temp, NULL, 10));

    dna_vector::iterator it;
    for (it = m_dnas.begin(); it != m_dnas.end(); ++it)   {
        if(it.operator*()->getId() == id)
            return *it;
    }
    return NULL;
}

inline void DataBase::pushBack(DnaSequenceAnalyzer *dna_a) {
    m_dnas.push_back(dna_a);
}

#endif //DNA_ANALYZER_DNA_DATABASE_H
