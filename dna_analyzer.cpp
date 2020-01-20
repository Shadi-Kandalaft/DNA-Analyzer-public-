//
// Created by shadikanda on 10/5/19.
//

#include "dna_analyzer.h"

size_t DnaSequenceAnalyzer::id = 0;
//dna_vector DNADatabase::dnas = NULL;
std::ostream &operator<<(std::ostream &os,const DnaSequenceAnalyzer& dna){
    size_t i = 0, size = dna.getDnaSequence().getLen();
    for(; i < size; ++i){
        os << dna.getDnaSequence().getData()[i].getNuc();
    }
    return os;
}


DnaSequenceAnalyzer DnaSequenceAnalyzer::slice(size_t from_ind, size_t to_ind, const String &name) {
    if(!my_strcmp(name, "")){
        this->getDnaSequence().slice(this->getDnaSequence(), from_ind, to_ind);
        DnaSequenceAnalyzer dna_null;
        return dna_null;
    }
    else if(!my_strcmp(name, "@@")){
        char str[20];
        sprintf(str, "%lu", m_id);
        String new_name(name);
        new_name += "_s";
        new_name += str;

        DnaSequenceAnalyzer dna_a("", new_name);
        dna_a.getDnaSequence().slice(this->getDnaSequence(), from_ind, to_ind);
        return dna_a;
    }
    else{
        DnaSequenceAnalyzer dna_a("", name);
        dna_a.getDnaSequence().slice(this->getDnaSequence(), from_ind, to_ind);
        return dna_a;
    }
}
