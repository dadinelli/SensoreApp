#include "rumore.h"

Rumore::Rumore(const std::string& name, const std::string& stanza, const double& min):AbstractSensor(name), stanza(stanza), min(min){
    last_simulation = new std::vector<double>();
    std::srand(std::time(nullptr));
}

std::vector<double>* Rumore::generate_values(){
    std::vector<double>* res = new std::vector<double>();

    res->push_back(0);
    res->push_back(140);

    std::random_device rd;
    std::mt19937 gen(rd());

    double min_value, max_value, cycle_length;

    if(this->stanza == "Auditorium"){
        min_value = -0.3;
        max_value = 0.3;
        cycle_length = 27;
    }
    else if(this->stanza == "Camera da letto"){
        min_value = -0.5;
        max_value = 0.5;
        cycle_length = 20;
    }
    else if(this->stanza == "Arena"){
        min_value = -0.1;
        max_value = 0.1;
        cycle_length = 23;
    }
    else min_value = max_value = cycle_length = 1;

    std::uniform_real_distribution<> dis(min_value, max_value);

    double start_value = min;
    double max_step = 3 * dis(gen);
    double trend_strength = 0.1;
    double noise_level = 0.5;

    double current_value = start_value;
    double long_term_trend = 0.0;

    for (int i = 0; i < 100; ++i) {
        double random_fluctuation = (static_cast<double>(std::rand()) / RAND_MAX) * 2 * max_step - max_step;

        long_term_trend += trend_strength * (static_cast<double>(std::rand()) / RAND_MAX - 0.5);

        double cyclic_variation = std::sin(1/2 * M_PI * i / cycle_length) * max_step;

        double noise = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * noise_level;

        current_value += random_fluctuation + long_term_trend + cyclic_variation + noise;

        if(current_value < 0) current_value = (-1)*current_value;
        if(current_value > 140) current_value = current_value - (current_value-140);

        res->push_back(current_value);
    }

    last_simulation = res;
    return res;
}

void Rumore::resetLastSim(){
    delete last_simulation;
    last_simulation = new std::vector<double>();
}

void Rumore::setStanza(const std::string& new_stanza){stanza = new_stanza;}
void Rumore::setMin(const double& m){min = m;}

std::string Rumore::getStanza() const {return stanza;}
double Rumore::getMin() const {return min;}
std::vector<double>* Rumore::getLastSim() const {return last_simulation;}

void Rumore::setLastSim(std::vector<double>* v) {last_simulation = v;}

Rumore::~Rumore(){}
