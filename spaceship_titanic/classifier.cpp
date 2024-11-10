#include "mlpack/core/util/forward.hpp"
#define MLPACK_PRINT_INFO
#define MLPACK_PRINT_WARN
#include <mlpack.hpp>

int main()
{
    arma::mat dataset;
    mlpack::data::DatasetInfo info;
    arma::Row<size_t> labels;

    mlpack::data::Load("train_data.csv", dataset, info, true);
    std::cout << ">> Loaded training data, "
              << dataset.n_cols << " observations, "
              << info.Dimensionality() << " features." << std::endl;

    mlpack::data::Load("train_labels.csv", labels);
    std::cout << ">> Loaded training labels, "
              << labels.size() << " labels, " << std::endl;

    arma::mat trainDataset, validDataset;
    arma::Row<size_t> trainLabels, validLabels;
    mlpack::data::Split(dataset, labels, trainDataset, validDataset, trainLabels, validLabels, 0.2);
    std::cout << ">> Train/Validation split, "
              << trainDataset.n_cols << " training, "
              << validDataset.n_cols << " validation." << std::endl;

    std::cout << ">> Training a RandomForest classifier..." << std::endl;
    mlpack::RandomForest<> r(
        trainDataset,
        trainLabels,
        7 /*Classes*/,
        10 /*Trees*/,
        3 /*Minimum leaf size*/
    );


    std::cout << std::endl << "Done!";
    return 0;
}
