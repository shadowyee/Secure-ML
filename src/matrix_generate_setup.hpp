#ifndef SECML_SETUP_HPP
#define SECML_SETUP_HPP
#include "util.hpp"
#include <emp-ot/emp-ot.h>

class SetupPhase{
public:
    int n, d, t;
    int party;
    RowMatrixXi64 Ai;
    ColMatrixXi64 Bi;
    ColMatrixXi64 Ci;
    ColMatrixXi64 Bi_;
    ColMatrixXi64 Ci_;

    emp::NetIO* io;
    emp::SHOTExtension<emp::NetIO>* send_ot;
    emp::SHOTExtension<emp::NetIO>* recv_ot;
    emp::PRG prg;

    SetupPhase(int n, int d, int t, emp::NetIO* io, int batch_size){
        this->n = n;
        this->d = d;
        this->t = t;
        this->io = io;
        this->send_ot = new emp::SHOTExtension<emp::NetIO>(io);
        this->recv_ot = new emp::SHOTExtension<emp::NetIO>(io);
        this->party = PARTY;

        Ai.resize(n, d);
        Bi.resize(d, t);
        Ci.resize(batch_size, t);
        Bi_.resize(batch_size, t);
        Ci_.resize(d, t);

        initialize_matrices(batch_size);
        std::cout << "Matrices Initialized" << std::endl;
    }

    void initialize_matrices(int batch_size);
    void generateMTs(int batch_size);
    void secure_mult(int N, int D, vector<vector<uint64_t>>& a,
                     vector<uint64_t>& b, vector<uint64_t> &c);
    void getMTs(SetupTriples* triples);
    void verify(int batch_size);
};
#endif // SECML_SETUP_HPP
