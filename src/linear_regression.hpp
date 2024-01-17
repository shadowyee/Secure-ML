#ifndef SECML_LR_HPP
#define SECML_LR_HPP
#include "setup_phase.hpp"
#include "online_phase.hpp"

class LinearRegression{
public:
    emp::NetIO* io;
    int party;
    int n, d, t;
    RowMatrixXi64 X;
    ColVectorXi64 Y;
    ColVectorXi64 w;
    ColVectorXd w_d;
    SetupPhase* setup;
    OnlinePhase* online;
    LinearRegression(RowMatrixXi64& training_data, ColVectorXi64& training_labels,
                     TrainingParams params, emp::NetIO* io){
        this->n = params.n;
        this->d = params.d;
        this->t = (params.n)/BATCH_SIZE;
        this->X = training_data;
        this->Y = training_labels;
        this->io = io;
        this->party = PARTY;
        this->w.resize(d);
        this->w_d.resize(d);

        auto startOffline = std::chrono::high_resolution_clock::now();

        this->setup = new SetupPhase(n, d, t, io);

        setup->generateMTs();
        
        std::cout << "Setup done" << std::endl;
        SetupTriples triples;
        setup->getMTs(&triples); 

        RowMatrixXi64 Xi(X.rows(), X.cols());
        ColVectorXi64 Yi(Y.rows(), Y.cols());
        if (party == emp::ALICE) {
            emp::PRG prg;
            RowMatrixXi64 rX(X.rows(), X.cols());
            ColVectorXi64 rY(Y.rows(), Y.cols());
            prg.random_data(rX.data(), X.rows() * X.cols() * sizeof(uint64_t));
            prg.random_data(rY.data(), Y.rows() * Y.cols() * sizeof(uint64_t));
            Xi = X + rX;
            Yi = Y + rY;
            rX *= -1;
            rY *= -1;
            send<RowMatrixXi64>(io, rX);
            send<ColVectorXi64>(io, rY);
        } else {
            recv<RowMatrixXi64>(io, Xi);
            recv<ColVectorXi64>(io, Yi);
        }
        
        std::cout << "Offline Phase Communication Cost: " << io->counter << "B" << endl;
        uint64_t scount = io->counter;

        auto endOffline = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> offlineTime = endOffline - startOffline;
        std::cout << "Offline Phase Runtime Cost: " << offlineTime.count() << endl;
      
        auto startOnline = std::chrono::high_resolution_clock::now();

        this->online = new OnlinePhase(params, io, &triples);
        online->initialize(Xi, Yi);

        train_model();
              
        std::cout << "Online Phase Communication Cost: " << io->counter - scount << "B" << endl;

        auto endOnline = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> onlineTime = endOnline - startOnline;
        std::cout << "Online Phase Runtime Cost: " << onlineTime.count() << endl;
    }

    void train_model();
    void test_model(RowMatrixXd& testing_data, ColVectorXd& testing_labels);
};
#endif //SECML_LR_HPP
