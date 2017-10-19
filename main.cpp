#include <iostream>

#include "Mat2d.hpp"
#include "Layers.hpp"

void print(Mat2d t) {
    uint32_t dim0 = t.get_row();
    uint32_t dim1 = t.get_col();
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            std::cout << t(i, j) << " ";	
        }
        std::cout << std::endl;
    }
    return;
}

int main() {

    // [Test] operator 
    uint32_t row = 2, col = 2;
    float a_data[row * col] = {1, 1, 1, 1};
    float b_data[row * col] = {1, 2, 3, 4};
    Mat2d A(row, col, a_data);
    Mat2d B(row, col, b_data);

    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d B: " << std::endl;
    print(B);
    std::cout << "Mat2d A + B: " << std::endl;
    print(A + B);
    std::cout << "Mat2d A * B: " << std::endl;
    print(A * B);
    std::cout << "Mat2d A / B: " << std::endl;
    print(A / B);
    std::cout << "Mat2d A > B: " << std::endl;
    print(A > B);	
    std::cout << "Mat2d A >= B: " << std::endl;
    print(A >= B);	
    std::cout << "Mat2d A < B: " << std::endl;
    print(A < B);	
    std::cout << "Mat2d A <= B: " << std::endl;
    print(A <= B);	
    std::cout << "Mat2d C <- B: " << std::endl;
    std::cout << "Mat2d C: " << std::endl;
    Mat2d C = B;
    print(C);	

    // [Test] vector broadcast
    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d A + onevec: " << std::endl;
    print(A + onevec);
    std::cout << "Mat2d A + onevec.T(): " << std::endl;
    print(A + onevec.T());

    // [Test] indexing reference
    float onevec_data[2] = {1, 2};
    Mat2d onevec(1, 2, onevec_data);

    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d A(0,0) <- 0: " << std::endl;
    A(0,0) = 0;
    print(A);

    // [Test] sum 
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d t1(dim0_t, dim1_t, t_data_1);

    std::cout << "Mat2d t1: " << std::endl;
    print(t1);
    std::cout << "Mat2d t1.sum(0): " << std::endl;
    print(t1.sum(0));
    std::cout << "Mat2d t1.sum(1): " << std::endl;
    print(t1.sum(1));

    // [Test] transpose 
    std::cout << "Mat2d t1: " << std::endl;
    print(t1);
    std::cout << "Mat2d t1.T(): " << std::endl;
    print(t1.T());
    std::cout << "Mat2d t1.dot(t1.T()): " << std::endl;
    print(t1.dot(t1.T()));

    //float out_data[10] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
    float out_data[10] = {0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0};
    float inp_data[2 * 2] = {0, 0, -5, 5};
    float dout_data[2 * 3] = {1, 1, 1, 1, 1, 1};

    Mat2d inp(2, 2, inp_data);
    Mat2d output(10, 1, out_data);
    Mat2d dout(2, 3, dout_data);

    LeakyReLU l_relu = LeakyReLU();
    std::cout << "Mat2d inp" << std::endl;
    print(inp);
    std::cout << "Mat2d forward of LeakyReLU(inp) : " << std::endl;
    print(l_relu.forward(inp));
    std::cout << "Mat2d backward of LeakyReLU(inp) when dout = 1 : " << std::endl;
    print(l_relu.backward(dout));

    std::cout << "Mat2d inp: " << std::endl;
    print(inp);
    Sigmoid sigmoid = Sigmoid();
    std::cout << "Mat2d forward of sigmoid(inp) : " << std::endl;
    print(sigmoid.forward(inp));
    std::cout << "Mat2d backward of sigmoid(inp) when d = 1 : " << std::endl;
    print(sigmoid.backward(A));

    std::cout << "Mat2d inp: " << std::endl;
    print(inp);
    Linear linear = Linear(2, 3);
    std::cout << "Mat2d forward of linear(inp) : " << std::endl;
    print(linear.forward(inp));
    std::cout << "Mat2d backward of linear(inp) when d = 1 : " << std::endl;
    print(linear.backward(dout));

    SoftmaxWithLoss criterion = SoftmaxWithLoss();
    int target = 2;
    std::cout << "Mat2d output: " << std::endl;
    print(output);
    std::cout << "Mat2d target: " << std::endl;
    std::cout << target << std::endl;
    std::cout << "Mat2d criterion.compute(output, target): " << std::endl;
    std::cout << criterion.compute(output, target) << std::endl;
    std::cout << "Mat2d criterion.backward(): " << std::endl;
    print(criterion.backward(A));

    return 0;
}
