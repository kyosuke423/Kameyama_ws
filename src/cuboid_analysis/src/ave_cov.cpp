#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>

// キューボイドを表す構造体
struct Cuboid {
    double height;
    double width;
    double depth;
};

// CSVファイルからキューボイドデータを読み取る関数
std::vector<Cuboid> readCuboidsFromCSV(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<Cuboid> cuboids;
    std::string line;

    if (inputFile.is_open()) {
        // 最初の行（ヘッダー）を読み飛ばす
        if (getline(inputFile, line)) {
            while (getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string item;
                std::vector<std::string> tokens;
                while (getline(ss, item, ',')) {
                    tokens.push_back(item);
                }

                if (tokens.size() >= 5) {
                    try {
                        double height = std::stod(tokens[2]);
                        double width = std::stod(tokens[3]);
                        double depth = std::stod(tokens[4]);

                        // nanチェックを追加
                        if (!std::isnan(height) && !std::isnan(width) && !std::isnan(depth)) {
                            Cuboid cuboid;
                            cuboid.height = height;
                            cuboid.width = width;
                            cuboid.depth = depth;
                            cuboids.push_back(cuboid);
                        }
                    } catch (const std::invalid_argument& e) {
                        // 無効なデータを無視する
                        std::cerr << "無効なデータがあり、スキップされました: " << line << std::endl;
                    }
                }
            }
        }
    } else {
        std::cerr << "ファイルを開くことができません: " << filename << std::endl;
    }

    // 最新の1000個のデータを取得するために、逆順にソートし、最初の1000個を選択
    if (cuboids.size() > 1000) {
        std::reverse(cuboids.begin(), cuboids.end());
        cuboids.resize(1000);
    }

    return cuboids;
}

// 平均と共分散行列を計算する関数
void calculateMeansAndCovarianceMatrix(const std::vector<Cuboid>& cuboids, 
                                       double& meanHeight, double& meanWidth, double& meanDepth, 
                                       double covarianceMatrix[3][3]) {
    int n = cuboids.size();
    meanHeight = 0.0;
    meanWidth = 0.0;
    meanDepth = 0.0;

    for (const auto& cuboid : cuboids) {
        meanHeight += cuboid.height;
        meanWidth += cuboid.width;
        meanDepth += cuboid.depth;
    }

    meanHeight /= n;
    meanWidth /= n;
    meanDepth /= n;

    double sumXX = 0.0, sumXY = 0.0, sumXZ = 0.0;
    double sumYY = 0.0, sumYZ = 0.0, sumZZ = 0.0;

    for (const auto& cuboid : cuboids) {
        double diffHeight = cuboid.height - meanHeight;
        double diffWidth = cuboid.width - meanWidth;
        double diffDepth = cuboid.depth - meanDepth;

        sumXX += diffHeight * diffHeight;
        sumXY += diffHeight * diffWidth;
        sumXZ += diffHeight * diffDepth;
        sumYY += diffWidth * diffWidth;
        sumYZ += diffWidth * diffDepth;
        sumZZ += diffDepth * diffDepth;
    }

    covarianceMatrix[0][0] = sumXX / (n - 1);
    covarianceMatrix[0][1] = sumXY / (n - 1);
    covarianceMatrix[0][2] = sumXZ / (n - 1);
    covarianceMatrix[1][0] = sumXY / (n - 1);
    covarianceMatrix[1][1] = sumYY / (n - 1);
    covarianceMatrix[1][2] = sumYZ / (n - 1);
    covarianceMatrix[2][0] = sumXZ / (n - 1);
    covarianceMatrix[2][1] = sumYZ / (n - 1);
    covarianceMatrix[2][2] = sumZZ / (n - 1);
}

// 平均と共分散行列をCSVファイルに書き込む関数
void writeMeansAndCovarianceToCSV(const std::string& filename, double meanHeight, double meanWidth, double meanDepth, 
                                  double covarianceMatrix[3][3]) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        outputFile << "Mean Height," << meanHeight << "\n";
        outputFile << "Mean Width," << meanWidth << "\n";
        outputFile << "Mean Depth," << meanDepth << "\n";

        outputFile << "Covariance Matrix\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                outputFile << covarianceMatrix[i][j];
                if (j < 2) {
                    outputFile << ",";
                }
            }
            outputFile << "\n";
        }
    } else {
        std::cerr << "ファイルを開くことができません: " << filename << std::endl;
    }
}

int main() {
    std::string inputFilename = "/home/dars/.ros/3object_cuboids_data.csv";
    std::string outputFilename = "/home/dars/.ros/output.csv";

    std::vector<Cuboid> cuboids = readCuboidsFromCSV(inputFilename);

    if (!cuboids.empty()) {
        double meanHeight, meanWidth, meanDepth;
        double covarianceMatrix[3][3];

        calculateMeansAndCovarianceMatrix(cuboids, meanHeight, meanWidth, meanDepth, covarianceMatrix);
        writeMeansAndCovarianceToCSV(outputFilename, meanHeight, meanWidth, meanDepth, covarianceMatrix);

        std::cout << "平均と共分散行列が " << outputFilename << " に書き込まれました。" << std::endl;
    } else {
        std::cerr << "処理するデータがありません。" << std::endl;
    }

    return 0;
}
