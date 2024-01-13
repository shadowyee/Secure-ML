#include "read_MNIST.hpp"
#include "matrix_generate_test.hpp"

using namespace Eigen;
using Eigen::Matrix;
using namespace emp;
using namespace std;

IOFormat CommaInitFmt(StreamPrecision, DontAlignCols, ", ", ", ", "", "", " << ", ";");

int NUM_IMAGES = BATCH_SIZE;
int PARTY;

int main(int argc, char** argv){
    int port;
    int n, d, t, batch_size;
    string address;

    PARTY = atoi(argv[1]);
    port = atoi(argv[2]);
    n = atoi(argv[3]);
    d = atoi(argv[4]);
    t = atoi(argv[5]);
    batch_size = atoi(argv[6]);

    try{
        int x = -1;
        if(argc <= 7)
            throw x;
        address = argv[7];
    } catch(int x) {
        address = "127.0.0.1";
    }

    NetIO* io = new NetIO(PARTY == ALICE ? nullptr : address.c_str(), port);

    TrainingParams params;
    
    cout << "=================" << endl;
    cout << "Matrix Generating" << endl;
    cout << "=================" << endl;

    params.n = n;
    params.d = d;

    LinearRegression linear_regression(params, io, t, batch_size);
    return 0;
}
