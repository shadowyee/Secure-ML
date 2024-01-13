#ifndef SECML_LR_HPP
#define SECML_LR_HPP
#include "matrix_generate_setup.hpp"
#include "online_phase.hpp"

class LinearRegression{
public:
    emp::NetIO* io;
    int party;
    int n, d, t;
    ColVectorXi64 w;
    ColVectorXd w_d;
    SetupPhase* setup;
    OnlinePhase* online;
    LinearRegression(TrainingParams params, emp::NetIO* io, int t, int batch_size){
        this->n = params.n;
        this->d = params.d;
        // this->t = (params.n)/BATCH_SIZE;
        this->t = t;
        this->io = io;
        this->party = PARTY;
        this->w.resize(d);
        this->w_d.resize(d);

        this->setup = new SetupPhase(n, d, t, io, batch_size);

        setup->generateMTs(batch_size);
        
        std::cout << "Matrix Generate done" << std::endl;
    }
};
#endif //SECML_LR_HPP
