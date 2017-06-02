## About Project
The project objective is to implement a PID controller in C++ to maneuver a simulated car around the lake race track. 
This project has already been implemented using Behavioural Cloning in Term 1.

---

![pid_snapshot](https://cloud.githubusercontent.com/assets/17127066/26726815/22121c30-47c2-11e7-8985-484a1c646eaf.png)

![change_with_ki](https://cloud.githubusercontent.com/assets/17127066/26726820/25e5d7fc-47c2-11e7-96b3-d72c3e7f0229.png)

source: https://en.wikipedia.org/wiki/PID_controller

PID Controller is a control loop feedback mechanism as shown in the diagram above. The difference between the measured and the desired value (setpoint) of a process variable of a system is fed into the PID controller as an error signal. Depending on the PID parameters (Kp, Ki, Kd), a control output is generated to steer the system closer to the setpoint. 

In this project, a car simulator produces the error signal (cross-track-error or cte) as the distance between the actual car position on the road and a reference trajectory. Students are expected to implement a PID controller to minimize the distance to this reference trajectory. The primary control output of the PID controller here is the steering angle.

Assumption: The car is expected to move within driveable portion of the track surface. It need not be aware of other vehicles on the road.

---

## Parameters Optimization

### Options Considered

1. Tune PID parameters manually while referring to Sebastian’s class notes for initial control gain values [Kp=0.2, KI=0.004, Kd=3.0]
2. Twiddle – An attempt was made to implement Twiddle algorithm. It got really hard to tune them with just one measurement coming in, at a time
3. Gradient Descent – SGD to optimize control gain parameters using PID errors as gradients

### Implementation

Options 1 and 3 were considered for the implementation.

PID parameters are manually tuned with starting values [Kp=0.2, KI=0.004, Kd=3.0]. The approach was to first tune proportant gain Kp. Optimizing Kp helped to converge quickly, but the car continued to oscillate around the center-line. Playing around with differential gain Kd helped to reduce oscillations. The integral gain Ki was not much of a priority, because there are no external influences in the simulater that introduce systematic bias. Manual tuning ended up with [Kp=0.18, KI=0.001, Kd=1.0]

Small oscillations continued to remain. Implementing ‘Gradient Descent’ helped  to reduce oscillations and also to increase car’s speed while keep the car stable. There was also an attempt to further optimize SGD through momentum. To many hyper-parameters was causing undue complications and hence, restricted implementation just to SGD without momentum.

---

## Throttle / Brakes

To simulate human behaviour, throttle and brakes are applied depending on the steering angle.

- Steering angle between 5 & 10 deg – throttle is adjusted to 0.2
- Steering angle between 10 & 15 deg – no throttle applied (throttle = 0.)
- Steering angle between 15 & 20 deg – brakes applied (throttle = -0.05)
- Steering angle between 20 & 25 deg – brakes applied (throttle = -0.1)

---

## Smoothening the steering angle

Successive steering angles could result in car to oscillate. Intuitive guess to reduce oscillations would be, to take average of last 5 steering value outputs. This, however caused more oscillations. The reason could be that averaging may already have been factored in PID equations and hence applying this again should be pointless.

---
