//
// Created by shadikanda on 10/4/19.
//

#include "nucleotide.h"

std::ostream &operator<<(std::ostream &os, const Nucleotide &nuc){
    return (os << nuc.getNuc());
}

bool Nucleotide::operator<(const Nucleotide &nuc) const {
    return false;
}

