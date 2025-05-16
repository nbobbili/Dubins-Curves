#include <cstdio>
extern "C" {
#include "../include/dubins.h"
}
#include <fstream>

class GetPath {
private:
    std::ofstream file;

public:
    static int printConfiguration(double q[3], double x, void *user_data);
    GetPath() {
        printf("Clearing dubins path csv\n");
        file.open("../dubins_path.csv", std::ios::trunc);
        if (file.is_open()) file.close();
    };
};

int GetPath::printConfiguration(double q[3], double x, void *user_data) {
    GetPath *self = static_cast<GetPath *>(user_data);
    // printf("%f, %f, %f, %f\n", q[0], q[1], q[2], x);

    std::ofstream file("../dubins_path.csv", std::ios::app);  // use append mode
    file << q[0] << "," << q[1] << "," << q[2] << "," << x << std::endl;
    return 0;
    return 0;
}

int main() {
    double q0[] = {0, 0, 0};
    double q1[] = {300.238, 0.0, 0.0};
    double turning_radius = 60;
    GetPath data;
    DubinsPath path;
    printf("Generating dubins path\n");
    dubins_shortest_path(&path, q0, q1, turning_radius);
    printf("Writing to csv\n");
    dubins_path_sample_many(&path, 0.1, GetPath::printConfiguration, &data);
    return 0;
}
