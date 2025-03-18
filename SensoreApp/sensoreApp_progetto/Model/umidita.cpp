#include "umidita.h"

Umidita::Umidita(const std::string& name, const double& min, const double& height): AbstractSensor(name), min(min), height(height) {
    last_simulation = new std::vector<double>();
}

std::vector<double>* Umidita::generate_values(){
    std::vector<double>* s = new std::vector<double>();

    double min_value, max_value;

    if(this->height > 2.0 && this->height < 4.0){
        min_value = 1.0;
        max_value = 2.0;
    }
    if(this->height > 4.0){
        min_value = 2.0;
        max_value = 3.0;
    }
    else if(this->height < 2.0){
        min_value = 0.5;
        max_value = 1.0;
    }

    s->push_back(0);
    s->push_back(100);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(min_value, max_value);

    double start_value = min + min + (max_value - min_value)/2 + dis(gen)/10;
    double max_step = dis(gen);
    double trend_strength = 0.1;
    double cycle_length = 15.0;
    double noise_level = 0.5;

    double current_value = start_value;
    double long_term_trend = 0.0;

    for (int i = 0; i < 100; ++i) {
        double random_fluctuation = (static_cast<double>(std::rand()) / RAND_MAX) * 2 * max_step - max_step;

        long_term_trend += trend_strength * (static_cast<double>(std::rand()) / RAND_MAX - 0.5);

        double cyclic_variation = std::sin(1/2 * M_PI * i / cycle_length) * max_step;

        double noise = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * noise_level;

        current_value += 5*(random_fluctuation + long_term_trend + cyclic_variation + noise);

        if(current_value < 0) current_value = (-1)*current_value;
        if(current_value > 100) current_value = 100 - (current_value-100);

        s->push_back(current_value);
    }

    last_simulation = s;
    return s;
}

void Umidita::resetLastSim(){
    delete last_simulation;
    last_simulation = new std::vector<double>();
}

std::vector<double>* Umidita::getLastSim() const {return last_simulation;}

void Umidita::setLastSim(std::vector<double>* v) {last_simulation = v;}

const double& Umidita::getMin() const {return min;}
const double& Umidita::getHeight() const {return height;}

void Umidita::setMin(const double& new_min) {this->min = new_min;}
void Umidita::setHeight(const double& new_height) {this->height = new_height;}
