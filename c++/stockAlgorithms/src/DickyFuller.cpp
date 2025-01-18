#include "DickyFuller.hpp"

#include <Eigen/Dense>
#include <vector>

using std::vector;
using Eigen::Dynamic;
using Eigen::Matrix;
using Eigen::Map;
using Eigen::MatrixXf;


float DickyFuller::testWithTrendAndConstant(vector<float>& stockPrices, int maxLag) {
        
        // if (stockPrices.size() <= (maxLag + 1)) {

        // }





        // we need to a check to ensure that the data is of minimum size
        Matrix<float, Dynamic, Dynamic> dataAsMatrix = Map<Matrix<float, Dynamic, Dynamic>>(stockPrices.data(), 1, stockPrices.size());
        return 0.0f;

        // MatrixXf derivative = dataAsMatrix.block(1, 2, 1, stockPrices.size() - 2) - dataAsMatrix.block(1, 1, 1, stockPrices.size() - 2);
        // MatrixXf constant = MatrixXf::Ones(1, stockPrices.size() - 2);
        // MatrixXf x = MatrixXf::LinSpaced(2, 100);

        // MatrixXf yLaggedOriginal = dataAsMatrix.block(1, 1, 1, stockPrices.size() - 1);
        // MatrixXf yLaggedOrder1 = dataAsMatrix.block(1, 1, 1, stockPrices.size() - 2) - dataAsMatrix.block(1, 0, 1, stockPrices.size() - 2);

        // MatrixXf A(stockPrices.size() - 2, 4);
        // A << constant, x, yLaggedOriginal, yLaggedOrder1;

        // MatrixXf ATransposeA = A.transpose() * A;
        // MatrixXf ATransposeAInverse = ATransposeA.inverse();

        // MatrixXf lambdas = (ATransposeAInverse * A.transpose()) * derivative;

        // MatrixXf yPredict = A * lambdas;
        // MatrixXf residuals = derivative - yPredict;
        
        // float sigmaSquare = residuals.dot(residuals) / (stockPrices.size() - 2 - 4);
        // MatrixXf var_beta = sigmaSquare * ATransposeA.inverse();
        // MatrixXf std_errors = var_beta.diagonal().array().sqrt();

        // MatrixXf tstat = lambdas.array() / std_errors.array();

        // return tstat[1, 1];
}