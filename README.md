# PGA 3D classification exercise
Basic setup code to solve a binary classification problem on the Haberman's Survival Data using FlyFish PGA operations.

## Dataset

The Haberman survival dataset is provided as a binary classification problem.
https://www.kaggle.com/datasets/gilsousa/habermans-survival-data-set

Three features are provided:
Age of patient at time of operation (numerical), 
Patient's year of operation (year - 1900, numerical), 
Number of positive axillary nodes detected (numerical), 
Survival status (class attribute)

## Exercise

The datapoints are presented as a pair of Trivector (three features) and boolean describing patients death within 5 years.
Invent a fit function that determines a Vector (plane) which determines the binary classification,
i.e. splitting point cloud in two groups.
Also implement a 'Predict' function that determines to which class a point (Trivector) is assigned based on the decision plane.

## Testing

The dataset gets split up at random in a train and test set. The decision plane gets determined by the training dataset,
the test set is used to validate your classifier on new data on which it wasn't trained.

The results get reported as:
- Accuracy
- Precision
- Recall
- F1

More info about these metrics can be found: https://medium.com/@piyushkashyap045/understanding-precision-recall-and-f1-score-metrics-ea219b908093

Try to optimize for one of these metrics.
