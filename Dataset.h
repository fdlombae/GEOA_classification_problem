#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <random>
#include "src/FlyFish.h"

struct AccuracyReport
{
    float accuracy;
    float precision;
    float recall;
    float f1;

    friend std::ostream& operator<< (std::ostream& stream, const AccuracyReport& rhs);
};

struct PredictionReport
{
    int falsePositives;
    int falseNegatives;
    int truePositives;
    int trueNegatives;
};

class Dataset {
public:
    Dataset(const std::string& path, float dataSplit, int seed);
    void Fit();
    [[nodiscard]] static bool Predict(const TriVector& input, const Vector& decisionPlane);

    [[nodiscard]] int GetTrainingSize() const { return trainingData.size(); }
    [[nodiscard]] int GetTestDataSize() const { return testData.size(); }

    void ReportAccuracy() const;
private:
    [[nodiscard]] static PredictionReport Predictions(const std::vector<std::pair<TriVector, bool>>& input, const Vector& decisionPlane);
    [[nodiscard]] static AccuracyReport Accuracy(const std::vector<std::pair<TriVector, bool>>& input, const Vector& decisionPlane);

    Vector decisionPlane{1, 1, 1, 0};
    std::vector<std::pair<TriVector, bool>> trainingData{};
    std::vector<std::pair<TriVector, bool>> testData{};

    std::default_random_engine rng;
};

#endif //DATASET_H
