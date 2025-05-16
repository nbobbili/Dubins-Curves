#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>

extern "C" {
#include "../include/dubins.h"
}

class GetPath {
private:
    std::ofstream file;
    void sigmoid(double time);

    double init_height_, final_height_;
    double z_, vz_, az_, jz_;

public:
    static int printConfiguration(double q[3], double x, void *user_data);

    std::vector<std::vector<double>> path_;
    void addAltitude(std::vector<std::vector<double>> &path);
    void writeToCsv();

    GetPath(double init[3], double final[3], double init_height, double final_height) {
        z_ = vz_ = az_ = jz_ = 0.0;
        init_height_ = init_height;
        final_height_ = final_height;
        printf("Clearing dubins path csv\n");
        file.open("../dubins_path.csv", std::ios::trunc);
        if (file.is_open()) file.close();
    };
};

void GetPath::sigmoid(double time) {
    double number = -20 * (time - 0.5);
    z_ = 1 / (1 + std::exp(number));
    vz_ = z_ * (1 - z_);
    az_ = vz_ * (1 - 2 * z_);
    jz_ = az_ - 2 * vz_ * vz_ - 2 * z_ * az_;
}

int GetPath::printConfiguration(double q[3], double x, void *user_data) {
    GetPath *self = static_cast<GetPath *>(user_data);

    std::vector<double> configuration;
    configuration.push_back(q[0]);
    configuration.push_back(q[1]);
    configuration.push_back(0);
    configuration.push_back(q[2]);
    self->path_.push_back(configuration);

    return 0;
}

void GetPath::addAltitude(std::vector<std::vector<double>> &path) {
    double size = (double)path.size();
    printf("Number of points: %f \n", size);
    for (int i = 0; i <= size; i++) {
        double time = i / size;
        sigmoid(time);
        if (i == size) continue;
        path_[i][2] = final_height_ * z_ + init_height_ * (1 - z_);
    }
}

void GetPath::writeToCsv() {
    std::ofstream file("../dubins_path.csv", std::ios::app);
    for (const auto &q : path_) {
        file << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << std::endl;
    }
}

int main() {
    double q0[] = {0, 0, 0};
    double q1[] = {320.123, -453.453, 2.124};
    double turning_radius = 60;
    double init_height = 45.0;
    double final_height = 500.0;

    GetPath data(q0, q1, init_height, final_height);
    DubinsPath path;

    printf("Generating dubins path\n");
    dubins_shortest_path(&path, q0, q1, turning_radius);

    printf("Writing to csv\n");
    dubins_path_sample_many(&path, 2.0, GetPath::printConfiguration, &data);
    data.addAltitude(data.path_);
    data.writeToCsv();

    return 0;
}
