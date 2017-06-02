#ifndef PID_H
#define PID_H

// #include <iostream>
// #include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Momentum speed variables for parameters
  */ 
  //double Mp;
  //double Mi;
  //double Md;

  // vector<double> avg_cte (10,0.);
  //std::vector<double> totErr_n;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_, double Ki_, double Kd_);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Compute control gains dynamically
  */
  void GradDesc();
};

#endif /* PID_H */
