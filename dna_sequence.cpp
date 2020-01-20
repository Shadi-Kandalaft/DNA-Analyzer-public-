//
// Created by shadikanda on 10/4/19.
//

#include "dna_sequence.h"

std::ostream &operator<<(std::ostream &os,const DnaSequence& dna){
    size_t i = 0, size = dna.getLen();
    for(; i < size; ++i){
        os << dna.getData()[i].getNuc();
    }
    return os;
}


size_t DnaSequence::subSeq(const DnaSequence& dna) {
    size_t i = 0, j = 0, size = this->getLen(), size_sub = dna.getLen(), size_delta;
    size_delta = size - size_sub;

    for(i = 0; i < (size_delta); i++){

        while (dna.getData()[j].getNuc() == this->getData()[i + j].getNuc()/* && (j-i) < size_sub*/){
            ++j;
        }

        if((j - i + 1) == (size_sub)){
            return i;
        }
        j = 0;
    }

    return size;
}

//
//size_t *DnaSequence::findAllConsesusSeq() {
//    const String start_seq = "TGA";
//    const String end_seq_TAG = "TAG",end_seq_TAA = "TAA", end_seq_TGA = "TGA";
//    DnaSequence start_codon(start_seq), end_codon_TAG(end_seq_TAG), end_codon_TAA(end_seq_TAA),
//            end_codon_TGA(end_seq_TGA), temp;
//
//    temp = this->m_data;
//    size_t size_arr_start = this->countSubSeq(start_codon);
//    size_t *arr_start = new size_t[size_arr_start];
//    size_t size_arr_end_TAG = this->countSubSeq(end_codon_TAG);
//    size_t *arr_end_TAG = new size_t[size_arr_end_TAG];
//    size_t size_arr_end_TAA = this->countSubSeq(end_codon_TAA);
//    size_t *arr_end_TAA = new size_t[size_arr_end_TAA];
//    size_t size_arr_end_TGA = this->countSubSeq(end_codon_TGA);
//    size_t *arr_end_TGA = new size_t[size_arr_end_TGA];
//
//    size_t i = 0, index = 0, j = 0, size = this->getLen(), size_delta;
//
//    for(; i < size; ++i){
//        j=i;
//        while(j < size && arr_end_TAA && arr_end_TAG && arr_end_TGA){
//            ++j;
//        }
//    }
//}
