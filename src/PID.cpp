#include "PID.h"
// #include <iostream>
#include <math.h>
#include <numeric>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
    Kp = Kp_;                   // proportional gain
    Ki = Ki_;                   // integral gain
    Kd = Kd_;                   // differential gain

    p_error = 0.;
    i_error = 0.;
    d_error = 0.;

    // Mp, Mi, Md = 0.;

    // set some values (from 1 to 10)
    // for (int i=1; i<=5; i++) totErr_n.push_back(0);
}

void PID::UpdateError(double cte) {

    d_error = cte - p_error;    // differential gain error
    p_error = cte;              // proportional gain error
    i_error += cte;             // integral gain error

    GradDesc();

    // cout << "p error: " << p_error << "\t" << "i error " << i_error << "\t" << "d error " << d_error << endl;
    // cout << "Kp: " << Kp << "\t" << "Ki: " << Ki << "\t" << "Kd: " << Kd << endl;
}

double PID::TotalError() {
    double tot_err = (Kp*p_error + Ki*i_error + Kd*d_error);

    // Taking average of steering values did not prove effective, hence commented out

    // totErr_n.erase (totErr_n.begin());
    // totErr_n.push_back(tot_err);
    // double sum = std::accumulate(totErr_n.begin(), totErr_n.end(), 0.);
    // double totErr_avg = sum / totErr_n.size();

    // cout << "p error: " << Kp*p_error << "\t" << "i error " << Ki*i_error << "\t" << "d error " << Kd*d_error << endl;
    // cout << "Total error: " << tot_err << endl;
    return tot_err;
}

void PID::GradDesc() {

    float alphaP = 0.0015;          // 0.0011;
    //float alphaI = 0.0001;
    float alphaD = 0.15;            // 0.15;


    // weight = weight - learning_rate * gradient
    // Simulator does not introduce systeematic bias, hence adjusting Ki ignored
    Kp = Kp - alphaP * p_error;
    //Ki = Ki - alphaI * i_error;
    Kd = Kd - alphaD * d_error;


    // Considering momentum involved working with too many hyper-parameters
    // and made things over-complicated. Hence, commented out

    // momentum_speed = momentum_speed * momentum_multiplier - gradient;
    // weight = weight + momentum_speed * learning_rate_a;
    
    // float MMp = 0.;                 // 0.1; 
    // float MMd = 0.;                 // 0.01;

    // Mp = Mp * MMp - p_error;
    // Kp = Kp + alphaP * Mp;
    
    // Md = Md * MMd - d_error;
    // Kd = Kd + alphaD * Md;

}