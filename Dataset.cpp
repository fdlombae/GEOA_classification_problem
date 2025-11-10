#include "Dataset.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>

namespace fs = std::filesystem;

float randomFloat(std::default_random_engine& rng)
{
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return dist(rng);
}

Dataset::Dataset(const std::string& path, float dataSplit, int seed)
{
    fs::path filepath{path};

    // Check if the file exists
    if (!fs::exists(filepath)) {
        std::cerr << "Error: File not found -> " << filepath << std::endl;
    }

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file -> " << filepath << std::endl;
    }

    std::string line;
    std::vector<std::pair<TriVector, bool>> data;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string cell;
        TriVector record{0, 0, 0, 1};
        int category{};

        if (std::getline(ss, cell, ',')) record.e032() = std::stoi(cell);
        if (std::getline(ss, cell, ',')) record.e013() = std::stoi(cell);
        if (std::getline(ss, cell, ',')) record.e021() = std::stoi(cell);
        if (std::getline(ss, cell, ',')) category = std::stoi(cell);

        data.push_back({record, category == 2});
    }

    file.close();

    std::cout << "Loaded " << data.size() << " datapoints from " << filepath << ":\n";

    // Shuffle dataset
    std::cout << "Shuffling dataset with seed " << seed << std::endl;
    rng = std::default_random_engine(seed);
    std::ranges::shuffle(data.begin(), data.end(), rng);

    int splitIndex{static_cast<int>(data.size() * dataSplit)};
    for (const auto& sample : std::ranges::subrange(data.begin(), data.begin() + splitIndex))
    {
        trainingData.push_back(sample);
    }
    for (const auto& sample : std::ranges::subrange(data.begin() + splitIndex, data.end()))
    {
        testData.push_back(sample);
    }
}

// TODO: create an algorithm to determine your decision plane
void Dataset::Fit()
{
    std::cout << "Fitting dataset on " << GetTrainingSize() << " samples." << std::endl;

    std::cout << "Decision plane: " << decisionPlane << std::endl;
}

// TODO: Use decision plane and input sample to determine classification
bool Dataset::Predict(const TriVector& input, const Vector& decisionPlane)
{
    return true;
}

std::ostream& operator<<(std::ostream& stream, const AccuracyReport& report)
{
    stream << "Accuracy: " << report.accuracy << std::endl;
    stream << "Precision: " << report.precision << std::endl;
    stream << "Recall: " << report.recall << std::endl;
    stream << "F1: " << report.f1 << std::endl;

    return stream;
}

void Dataset::ReportAccuracy() const
{
    std::cout << "Dataset contains " << GetTrainingSize() << " training samples and " << GetTestDataSize() << " test samples." << std::endl;
    std::cout << "Training report: " << std::endl << std::endl << Accuracy(trainingData, decisionPlane) << std::endl;
    std::cout << "Test report: " << std::endl << std::endl << Accuracy(testData, decisionPlane) << std::endl;
}

AccuracyReport Dataset::Accuracy(const std::vector<std::pair<TriVector, bool>>& input, const Vector& decisionPlane)
{
    PredictionReport predictions = Predictions(input, decisionPlane);

    AccuracyReport report{};
    report.accuracy = (predictions.truePositives + predictions.trueNegatives) /
        static_cast<float>(predictions.truePositives + predictions.trueNegatives + predictions.falsePositives + predictions.falseNegatives);
    report.precision = predictions.truePositives / static_cast<float>(predictions.truePositives + predictions.falsePositives);
    report.recall = predictions.truePositives / static_cast<float>(predictions.truePositives + predictions.falseNegatives);
    report.f1 = 2 * report.precision * report.recall / (report.precision + report.recall);
    return report;
}

PredictionReport Dataset::Predictions(const std::vector<std::pair<TriVector, bool>>& input, const Vector& decisionPlane)
{
    PredictionReport report{};
    for (const auto& sample : input)
    {
        bool result{Dataset::Predict(sample.first, decisionPlane)};
        if (sample.second)
        {
            if (result)
            {
                report.truePositives++;
            } else {
                report.falseNegatives++;
            }
        }
        else
        {
            if (result)
            {
                report.falsePositives++;
            } else {
                report.trueNegatives++;
            }
        }
    }
    return report;
}

