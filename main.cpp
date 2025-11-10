#include "Dataset.h"

int main()
{
    Dataset dataset("../data/haberman.csv", 0.8, 3);

    dataset.Fit();

    dataset.ReportAccuracy();

    return 0;
}
