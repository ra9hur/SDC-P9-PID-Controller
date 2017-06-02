# CarND-PID-Control-Project
The project objective is to implement a PID controller in C++ to maneuver a simulated car around the lake race track. 
This project has already been implemented using Behavioural Cloning in Term 1.

---

![pid_snapshot](https://cloud.githubusercontent.com/assets/17127066/26726815/22121c30-47c2-11e7-8985-484a1c646eaf.png)

![change_with_ki](https://cloud.githubusercontent.com/assets/17127066/26726820/25e5d7fc-47c2-11e7-96b3-d72c3e7f0229.png)

PID Controller is a control loop feedback mechanism as shown in the diagram above. The difference between the measured and the desired value (setpoint) of a process variable of a system is fed into the PID controller as an error signal. Depending on the PID parameters (Kp, Ki, Kd), a control output is generated to steer the system closer to the setpoint. 

In this project, a car simulator produces the error signal (cross-track-error or cte) as the distance between the actual car position on the road and a reference trajectory. Students are expected to implement a PID controller to minimize the distance to this reference trajectory. The primary control output of the PID controller here is the steering angle.

Assumption: The car is expected to move within driveable portion of the track surface. It need not be aware of other vehicles on the road.

## Parameters Optimization

### Options Considered

1. Tune PID parameters manually while referring to Sebastian’s class notes for initial control gain values [Kp=0.2, KI=0.004, Kd=3.0]
2. Twiddle – An attempt was made to implement Twiddle algorithm. It got really hard to tune them with just one measurement coming in, at a time
3. Gradient Descent – SGD to optimize control gain parameters using PID errors as gradients

### Implementation

Options 1 and 3 were considered for the implementation.

PID parameters are manually tuned with starting values [Kp=0.2, KI=0.004, Kd=3.0]. The approach was to first tune proportant gain Kp. Optimizing Kp helped to converge quickly, but the car continued to oscillate around the center-line. Playing around with differential gain Kd helped to reduce oscillations. The integral gain Ki was not much of a priority, because there are no external influences in the simulater that introduce systematic bias. 

Small oscillations continued to remain. Implementing ‘Gradient Descent’ helped  to reduce oscillations and also to increase car’s speed while keep the car stable. There was also an attempt to further optimize SGD through momentum. To many hyper-parameters was causing undue complications and hence, restricted implementation just to SGD.

## Throttle / Brakes

To simulate human behaviour, throttle and brakes are applied depending on the steering angle.

- Steering angle between 5 & 10 deg – throttle is adjusted to 0.2
- Steering angle between 10 & 15 deg – no throttle applied (throttle = 0.)
- Steering angle between 15 & 20 deg – brakes applied (throttle = -0.05)
- Steering angle between 20 & 25 deg – brakes applied (throttle = -0.1)

## Smoothening the steering angle

Varying steering angles could result in car oscillating. Initial guess to reduce oscillations was to take average of last 5 steering value outputs. This, however caused more oscillations. The reason could be that averaging may already have been factored in PID equations and hence applying this again should be pointless.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
