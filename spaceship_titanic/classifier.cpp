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

    mlpack::data::Load("train_labels.csv", labels);

    arma::mat trainDataset, validDataset;
    arma::Row<size_t> trainLabels, validLabels;
    mlpack::data::Split(dataset, labels, trainDataset, validDataset, trainLabels, validLabels, 0.2);
    std::cout << ">> Train/Validation split, "
              << trainDataset.n_cols << " training, "
              << validDataset.n_cols << " validation." << std::endl;

    std::cout << ">> Training a RandomForest classifier..." << std::endl;
    std::vector<double> rfNTree{1, 10, 50, 100, 150, 200, 300, 500};
    std::vector<double> rfTrainScores, rfValidScores;
    for(const auto& nTree: rfNTree) {
        mlpack::RandomForest<> rfClf(
            trainDataset,
            info,
            trainLabels,
            2 /*Classes*/,
            nTree /*Trees*/
        );
        arma::Row<size_t> rfTrainPreds, rfValidPreds;
        rfClf.Classify(trainDataset, rfTrainPreds);
        rfClf.Classify(validDataset, rfValidPreds);
        const double rfTrainScore = arma::accu(rfTrainPreds == trainLabels) * 100.0 / trainLabels.n_elem;
        rfTrainScores.push_back(rfTrainScore);
        const double rfValidScore = arma::accu(rfValidPreds == validLabels) * 100.0 / validLabels.n_elem;
        rfTrainScores.push_back(rfValidScore);
        std::cout << ".. Trees: " << nTree
                  << ", Train Score: " << rfTrainScore
                  << "%, Validation Score: " << rfValidScore << "%" << std::endl;
    }

    std::cout << std::endl << "Done!";
    return 0;
}
