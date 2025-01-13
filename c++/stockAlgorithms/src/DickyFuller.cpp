// #include "DickyFuller.hpp" vscode failing to detect the hpp file

#include <Eigen/Dense>
#include <vector>

using std::vector;
using Eigen::Dynamic;
using Eigen::Matrix;
using Eigen::Map;
using Eigen::MatrixXf;

namespace DickyFullerTest {
    
    float WithTrendAndConstant(vector<float>& data) {
        // we need to a check to ensure that the data is of minimum size
        Matrix<float, Dynamic, Dynamic> dataAsMatrix = Map<Matrix<float, Dynamic, Dynamic>>(data.data(), 1, data.size());

        MatrixXf derivative = dataAsMatrix.block(1, 2, 1, data.size() - 2) - dataAsMatrix.block(1, 1, 1, data.size() - 2);
        MatrixXf constant = MatrixXf::Ones(1, data.size() - 2);
        MatrixXf x = MatrixXf::LinSpaced(2, 100);

        MatrixXf yLaggedOriginal = dataAsMatrix.block(1, 1, 1, data.size() - 1);
        MatrixXf yLaggedOrder1 = dataAsMatrix.block(1, 1, 1, data.size() - 2) - dataAsMatrix.block(1, 0, 1, data.size() - 2);

        MatrixXf A(data.size() - 2, 4);
        A << constant, x, yLaggedOriginal, yLaggedOrder1;

        MatrixXf ATransposeA = A.transpose() * A;
        MatrixXf ATransposeAInverse = ATransposeA.inverse();

        MatrixXf lambdas = (ATransposeAInverse * A.transpose()) * derivative;

        MatrixXf yPredict = A * lambdas;
        MatrixXf residuals = derivative - yPredict;
        
        float sigmaSquare = residuals.dot(residuals) / (data.size() - 2 - 4);
        MatrixXf var_beta = sigmaSquare * ATransposeA.inverse();
        MatrixXf std_errors = var_beta.diagonal().array().sqrt();

        MatrixXf tstat = lambdas.array() / std_errors.array();

        return tstat[1, 1];
    }

}