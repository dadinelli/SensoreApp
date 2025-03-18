#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include "temperatura.h"

Temperatura::Temperatura(const std::string& name, const double& min, const double& max): AbstractSensor(name), min(min), max(max){
    last_simulation = new std::vector<double>();
    std::srand(std::time(nullptr));
}

std::vector<double>* Temperatura::generate_values(){
    std::vector<double>* s = new std::vector<double>();
    double min_value = min;
    double max_value = max;

    s->push_back(min_value);
    s->push_back(max_value);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(min_value, max_value);

    double start_value = min + (max_value - min_value)/2 + dis(gen)/10;
    double max_step = dis(gen);
    double trend_strength = 0.1;
    double cycle_length = 15.0;
    double noise_level = 0.5;
    double long_term_trend = 0.0;

    double current_value = start_value;

    for (int i = 2; i < 102; ++i) {
        double random_fluctuation = (static_cast<double>(std::rand()) / RAND_MAX) * 2 * max_step - max_step;

        long_term_trend += trend_strength * (static_cast<double>(std::rand()) / RAND_MAX - 0.5);

        double cyclic_variation = std::sin(1/2 * M_PI * i / cycle_length) * max_step;

        double noise = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * noise_level;

        current_value += 2*((random_fluctuation + long_term_trend + cyclic_variation + noise)/(max_value-min_value));

        if(current_value < min_value) current_value = min_value + abs(min_value - current_value);
        if(current_value > max_value) current_value = max_value - (current_value - max_value);

        s->push_back(current_value);
    }

    last_simulation = s;
    return s;
}

void Temperatura::resetLastSim(){
    delete last_simulation;
    last_simulation = new std::vector<double>();
}


void Temperatura::setLastSim(std::vector<double>* v) {last_simulation = v;}

void Temperatura::setMin(double new_min){this->min = new_min;}

void Temperatura::setMax(double new_max){this->max = new_max;}

double Temperatura::getMin() const {return min;}

double Temperatura::getMax() const {return max;}

std::vector<double>* Temperatura::getLastSim() const {return last_simulation;}

Temperatura::~Temperatura(){}
