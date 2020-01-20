//
// Created by shadikanda on 10/6/19.
//

#include "tests.h"

using std::cout;
using std::endl;

void test_1(){
    String str1("AAATCGCGA");
    DnaSequenceAnalyzer dna1(str1, "second_test2");
    cout << "DNA 1: " << dna1 << " ; Name: " << dna1.getName() << endl;
    dna1.save("/home/shadikanda/CLionProjects/DNA_Design/dna1.txt");
    dna1.save();
    DnaSequenceAnalyzer dna2;
    DnaSequenceAnalyzer dna3;
    dna2.load("/home/shadikanda/CLionProjects/DNA_Design/dna1.txt", "second dna test");
    cout << "DNA 2: " << dna2 << " ; Name: " << dna2.getName() << endl;
    dna3.load("/home/shadikanda/CLionProjects/DNA_Design/dna1.txt");
    cout << "DNA 3: " << dna3 << " ; Name: " << dna3.getName() << endl;

}

void test_2(){
    DataBase *db = new DataBase();
    Run *r = new Run();
    r->setup(static_cast<VectorS>(0), *db);
    r->execute();
    free(r);
}
