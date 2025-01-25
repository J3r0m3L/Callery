#include "DickyFuller.hpp"

#include <Eigen/Dense>
#include <vector>
#include <iostream>

using std::vector;
using Eigen::Dynamic;
using Eigen::Map;
using Eigen::MatrixXf;
using Eigen::VectorXf;

float DickyFuller::testWithTrendAndConstant(vector<float>& stockPrices, int maxLag) {
    // https://faculty.washington.edu/ezivot/econ584/notes/unitrootLecture2.pdf 
    // https://people.ucsc.edu/~cheung/pubs/with_Lai/LagOrderAugDickey_Fuller.pdf?utm_source=chatgpt.com
    // for now just assuming maxLag = 1
    if (stockPrices.size() <= (maxLag + 1)) {
        return 0.0f;
    }
 
    int size = stockPrices.size();
    int sizeSub2 = stockPrices.size() - 2;

    VectorXf stockPricesAsVector = Map<VectorXf>(stockPrices.data(), size);
    VectorXf derivative = stockPricesAsVector.segment(2, sizeSub2).eval() - stockPricesAsVector.segment(1, sizeSub2).eval();
    VectorXf constant(sizeSub2);
    constant.setOnes();
    VectorXf x(sizeSub2);
    for (int i = 2; i < size; i++) {
        x(i - 2) = i;
    }

    VectorXf yLaggedOriginal = stockPricesAsVector.segment(1, sizeSub2).eval();
    VectorXf yLaggedOrder1 = stockPricesAsVector.segment(1, sizeSub2).eval() - stockPricesAsVector.segment(0, sizeSub2).eval();

    MatrixXf A(sizeSub2, 4);
    A << constant, x, yLaggedOriginal, yLaggedOrder1;
    MatrixXf A_transpose_A = A.transpose() * A;
    MatrixXf A_transpose_A_inverse = A_transpose_A.inverse();
    VectorXf lambdas = ((A_transpose_A_inverse * A.transpose()) * derivative).col(0);

    VectorXf y_predict = (A * lambdas).col(0);
    VectorXf residuals  = derivative - y_predict;
    float sigma_square = residuals.dot(residuals) / (sizeSub2 - 4);

    MatrixXf var_beta = sigma_square * A_transpose_A_inverse;
    VectorXf std_errors = var_beta.diagonal().array().sqrt();

    VectorXf result = lambdas.array() / std_errors.array();

    return result(2);
}