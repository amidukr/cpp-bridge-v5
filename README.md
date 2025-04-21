[![Build Status](https://travis-ci.org/amidukr/cpp-bridge-v5.svg?branch=master)](https://travis-ci.org/amidukr/cpp-bridge-v5) [![codecov](https://codecov.io/gh/amidukr/cpp-bridge-v5/branch/master/graph/badge.svg)](https://codecov.io/gh/amidukr/cpp-bridge-v5)


# Project Overview

This project is sample implementation for matrix based soft-body dynamic modeling for mesh with infinite stiffness.

The intention of this project is to prove that use of system of linear equation (Elastic Matrix model) for calcualation of force strength distribution accross soft-body model will give better accuracy than classical elastic model on larger simulation time interval

## Goal

The goal for modeling is to create soft-body dyanmic algorithms with infinitly hard connected mesh which will give steady and accurate result on large simulation intervals.

Matrix-Elastic model is considered as most advanced algorithm used in this study, and it is a target to be proove that it will give better result than just plain Elastic model.


# Modeling

Application can run in 3 different mathematic modeling mode to simulate dyanmic process in mesh model.

- Matrix - assumes that model is stiff and uses system of linear equation to calculate Force distribution considering bridge model as whole system. This modeling is syntesis of two algorithms: Matrix and Kinematics/Dynamics.
- Elastic - assume that model is elastic. This modeling is syntesis of two algorithms: Kinematics/Dynamicsa and Principle of minimum energy, while gravity shifting the positions of the model.
- Matrix-Elastic - combination of Matix and Elastic algorithm to get best results. This modeling is syntesis of three algorithms: Matrix, Principle of minimum energy and Kinematics/Dynamics.

## Bridge Model Mesh

Bridge model is presented by series:

- Floating junctions with mass, example: P1, P2, P3, P5
- Fixed junction: Example P4
- And connection between this junctions

![Bridge Model Example](media/bridge-model.png)

## Bridge Model Dynamic

Expectation that mesh model will be dynamically in motion according to physics law.
- So floating junction can change its velocity and position
- Floating junction have a mass and inertion.
- Fixed junction will have fixed position, zero velocity, infinite mass and inertion staying fixed all the time.
- Gravity force is applied everytime for every Free floating junctions
- Connection are non-ideally elastic, however the target for evaluation is that connection should be as harder as possible.

Expected behaviour for the sample above is that mass junction P1, P2, P3, P5 will be in falling and rotation around fixed point P4.

# Algorithms
## Kinematics and Dynamics

Dynamic for soft-body modeling makes an assumption that body presented as set of junction connected with elastic springs, that behaves according to [Hooke's law](https://en.wikipedia.org/wiki/Hooke%27s_law).

Every floating junction is accelerated based on applied force that is gravity and spring tension forces.

Let's assume that:
- ![m_i](media/elastic-math/m_i.gif) is a mass of Junction Pi
- ![Fi](media/elastic-math/F_i.gif) is superposition of forces applied to Junction Pi,
velocity will be update for each iteration in following way:
- ![P_i](media/elastic-math/P_i.gif) is position of Junction Pi.
- ![v_i](media/elastic-math/v_i.gif) is velocity of Junction Pi at current moment of time.
- ![Vi'](media/elastic-math/v_i_next.gif) is velocity of Junction Pi at next moment after
inteval ![dt](media/elastic-math/dt.gif).
- ![Pi'](media/elastic-math/P_i_next.gif) is position of Junction Pi at next moment after
interval ![dt](media/elastic-math/dt.gif).

Having the ![P_i](media/elastic-math/P_i.gif), ![v_i](media/elastic-math/v_i.gif), ![dt](media/elastic-math/dt.gif),
![Fi](media/elastic-math/F_i.gif) and ![m_i](media/elastic-math/m_i.gif) next state of Junction Pi can be calculated with
following formula:

- ![Pi_next_formula](media/elastic-math/P_i_next_formula.gif)
- ![Vi_next_formula](media/elastic-math/v_i_next_formula.gif)
- ![ai_formula](media/elastic-math/a_i_formula.gif) - according to Newton's second law

Example bellow illustrates force applied to Junction P3

![Elastic Model](media/bridge-model-springs.png)

- ![F3](media/elastic-math/F_3.gif) - superposition of forces applied to Junction P3.
- ![Fg](media/elastic-math/F_g.gif) - Gravity force
- ![F23](media/elastic-math/F_23.gif) - force applied applied to junction P3 by spring 23 tension. Same symetrical force
![F32](media/elastic-math/F_32.gif) with opposit direction applied to junction P2.

![F3 Formula](media/elastic-math/F_3_formula.gif)

## Hook's Law
Spring tension force is calculated according to [Hooke's law](https://en.wikipedia.org/wiki/Hooke%27s_law). Illustration bellow demonstrates Hooke's law. However direct definition of Hoke's law is not used in this application, because Minimum Energy algorithm is enough to simulate elastic model.

- ![P3](media/elastic-math/P_3.gif) is commpressed state of spring.
- ![P3'](media/elastic-math/P_3_next.gif) is relaxed state of spring.

![Single spring](media/bridge-model-signle-spring.png)


Spring tension force can be calculated with following formula
- ![F13 Formua](media/elastic-math/F_13_formula.gif); according to 
[Hooke's law](https://en.wikipedia.org/wiki/Hooke%27s_law)
- ![P3 Next Formula](media/elastic-math/P_3_next_formula.gif)

## Minimum Energy
[Principle of minimum energy](https://en.wikipedia.org/wiki/Principle_of_minimum_energy) it states that the internal energy will decrease and approach a minimum value at equilibrium. 

In soft-body simulation model simulation case internal energy is spring tension, and iterative algorithm searchs for the equilibrium state with minimum tension and minimum internal energy.


Algorithm that implements principle of minimum energy is illustrated on the image bellow.

![Bridge Model - Minimul energy](media/bridge-model-minimum-energy.png)

Let's assume that
- ![P1](media/minimum-energy/P_1.gif) - is current  position of Junction P1. It also represent the current state of the model. In this case tension of the spring will tend to accelerate Junction P1 to the direction close to 
![P1r](media/minimum-energy/P_1r.gif). This state needs store internal energy as spring tension, and needs to be optimized according to 
[Principle of minimum energy](https://en.wikipedia.org/wiki/Principle_of_minimum_energy)
- ![P1r](media/minimum-energy/P_1r.gif) is ideal target position of junction P1, which is practically impossible. It represent relaxed state of the model, that means that all spring tension forces are equal to zero, in this state
![P1r](media/minimum-energy/P_1r.gif) and system is in equilibrium state. We can say that this is the state of minimum energy, where no internal energy stored by the springs.
- ![P'1s1](media/minimum-energy/P_1s1.gif) and ![P1s2](media/minimum-energy/P_1s2.gif) is intermediate Junction P1
position during algorithm run on iteration 1 and iteration 2, while the last step is result of algorithm. For generalc case amount of steps for each junction is variable and depends on amount of spring connected to this junction.
  - ![P'1s1](media/minimum-energy/P_1s1.gif) represent algorithm iteration related to Junction P1 and Spring that connection
  Junction P1 and Junction P2
  - ![P'1s2](media/minimum-energy/P_1s2.gif) represent algorithm iteration related to Junction P1 and Spring that connection
  Junction P1 and Junction P3


Principle of the algorithm is to iterate over every Floating Junctions and every Spring Connected to the Junction. These iteration can be repeated multiple time, to come closer to ideal relaxed state. On every step of the iteration over Spring related to Floating Junction, just needs to move Floating Junction in the direction to relaxate that Spring to achieve the state of minimum energy. Formula exmaples for the illustration above:
- ![P_1s1_formula](media/minimum-energy/P_1s1_formula.gif)
- ![P_1s2_formula](media/minimum-energy/P_1s2_formula.gif)
 
 0.5 factor is applied to the formulas, because algorithm moves Junction symetrically on both ends of the spring. Half move on Junctions on both ends will make a whole change to the spring.

## Matrix

Intention to create this application is to prove that Matrix algorithm will show better resulst than classical elastic. Concept of this algorithm is that forces and tension in real world construction a spread immediately all objects are interact with each other and even the most remote ones.

Matrix are good to describe systems that can be defined as system of linear equation, where root are states of the objects and each of this states is dependent and affected by every other object and object's states.

In the Matrix algorithm, there is assumption that connection between junction are extremely hard spring with Hook's factor about infinity, and forces between junctions are spread immediately. To do the soft body dynamics modeling, matrix is used find force superposition applied to every Junction. Matrix algorithm is explained using Model bellow:

![Bridge Model - Matrix](media/bridge-model-matrix.png)

On this model two type of Junction:

- P3, P4 - fixed junction, has infinity mass and inertion can accept any force or impulse without moving.
- P1, P2 - floating junction have some mass and moving.

Let's assume that:
- ![F1](media/matrix-math/F1.gif), ![F2](media/matrix-math/F2.gif) - force applied to Junction P1 and Junction P2 accordingly. And these forces will make acceleration to Junction P1, P2.
- ![Fg](media/matrix-math/Fg.gif) - gravity force
- ![F12](media/matrix-math/F12.gif), ![F13](media/matrix-math/F13.gif), ![F24](media/matrix-math/F24.gif)
is forces applied to P2 by P1, P3 by P1 and P4 by P2 accordingly.
- ![F21](media/matrix-math/F21.gif), ![F31](media/matrix-math/F31.gif), ![F42](media/matrix-math/F42.gif) is force applied to P1 by P2, P1 by P3, P2 by P4 and equal to -![F12](media/matrix-math/F12.gif), -![F13](media/matrix-math/F13.gif), -![F24](media/matrix-math/F12.gif) accordingly.
- ![P1](media/matrix-math/P1.gif), ![P2](media/matrix-math/P2.gif), ![P3](media/matrix-math/P3.gif), 
![P4](media/matrix-math/P4.gif) is positions of Junction Points P1, P2, P3, P4 accordingly.
- ![R12](media/matrix-math/R12.gif), ![R13](media/matrix-math/R13.gif), ![R24](media/matrix-math/R24.gif)
are normalized vectors connecting Junctions, and can be calculated as 
![normalize(P2_P1)](media/matrix-math/normalize_P2_P1.gif),
![normalize(P3_P1)](media/matrix-math/normalize_P3_P1.gif) and 
![normalize(P4_P2)](media/matrix-math/normalize_P4_P2.gif) accordingly.

Next steps to build the system of linear equation that represent Bridge Model as interacting system, where the roots will be the Forces necessary to calculate Junction accelerations. 

1. Force applied to every Junction can be calculated as sum of forces applied by connection between Junctions and Gravity. For example model above formula will looks like follows:
   - ![F1 = Fg + F21 + F31](media/matrix-math/F1_formula_general.gif)
   - ![F2 = Fg + F12 + F42](media/matrix-math/F2_formula_general.gif)
 
   or   
   
   - ![F1 = Fg + normalize(P1-P3)|F31| + normalize(P1-P3)|F21|](media/matrix-math/F1_formula_P1_P2_P3.gif)
   - ![F2 = Fg + normalize(P1-P2)|F12| + normalize(P4-P2)|F42|](media/matrix-math/F2_formula_P1_P2_P4.gif)
   
   or
   
   - ![F1 = Fg - R12*|F12| - R13*|F13|](media/matrix-math/F1_formula_R12_R13.gif)
   - ![F2 = Fg + R12*|F12| - R24*|F24|](media/matrix-math/F2_formula_R12_R24.gif)
2. Rotation of the sysetm of two Junction and Connection between them is also constrained by following formula. Mahematical Prove of [Girder Rotation](#girder-rotation) is providen bellow.
   - Junction 13 and Junction 24 has one fixed and one floating junction so the formulas are follows:
     - ![-F1*R13 = 0](media/matrix-math/F1_R13.gif)
     - ![-F2*R24 = 0](media/matrix-math/F2_R24.gif)
   - Connection 12 has two floating junction, so formula is follows:
     - ![-F1/m1*R12 + F2/m2*R12 = 0](media/matrix-math/F1_R12_and_F2_R12.gif)

Resulting matrix for the equations above, will look like follows:

![Matrix Equation](media/matrix-math/matrix.gif)

For general case for N Junction and M connection Matrix still will be square. For every Junction it will be two equation plus
one equation for each connection. The same amount of roots: two roots for every Junction superposition force and one root for
every connection tension.

### Girder Rotation

Here are two cases to review rotation of girder over fixed junction, and free rotation with two floating junction.

1. Rotation over fixed girder is simple case, floating point can be accelerated only in the direction perpendicular to the connection.

   ![Rotaing Pendulum](media/bridge-model-rotating-pendulum.png)
   
   Since force othogonal to connection, Dot product of these two should be equal to zero:
   - ![F1*(P2 - P1) = 0](media/matrix-math/F1_P2_P1.gif)
   
   or 
   
   - ![F1*R12 = 0](media/matrix-math/F1_R12.gif)

2. Describing constraint for connection with floating junction, needs to consider that connection length is constant, and velocity of junctions on both ends can't change connection length. 

   ![Rotaing Girder](media/bridge-model-rotating-plunk.png)
   
   It means that decomposed part of vector which collinear with connection for both end should have same value, otherwise 
   connection length will be changed.
   - ![v1*normalize(P1-P2) = v2*normalize(P1-P2) = v12](media/matrix-math/v1_P1_P2_and_v2_P1_P2_normalized.gif)
   
   or
   
   - ![v1*(P1-P2) = v2*(P1-P2)](media/matrix-math/v1_P1_P2_and_v2_P1_P2.gif)
   
   Same true for vector next moment of time
   - ![(v1+dv1)*(P1-P2) = (v2+dv2)*(P1-P2)](media/matrix-math/v1_dv1_P1_P2_and_v2_dv2_P1_P2.gif)
   
   Simplifying equation:
   - ![v1*(P1-P2)+dv1*(P1-P2) = v2*(P1-P2)+dv2*(P1-P2)](media/matrix-math/v1_dv1_P1_P2_and_v2_dv2_P1_P2_expanded.gif)
   - ![dv1*(P1-P2) = dv2*(P1-P2)](media/matrix-math/dv1_P1_P2_and_dv2_P1_P2.gif)
   
   Same true for force and acceleration
   - ![a1*dt*(P1-P2) = a2*dt*(P1-P2)](media/matrix-math/a1_dt_P1_P2_and_a2_dt_P1_P2.gif)
   - ![a1*(P1-P2) = a2*(P1-P2)](media/matrix-math/a1_P1_P2_and_a2_P1_P2.gif)
   - ![F1/m1*(P1 - P2) = F2/m2*(P1 - P2)](media/matrix-math/F1_P1_P2_and_F2_P1_P2.gif)
   
   
   Linear equation format, suitable for matrix:
   - ![-F1/m1*(P2 - P1) + F2/m2*(P2 - P1) = 0](media/matrix-math/F1_P2_P1_and_P2_P1.gif)
  
   or
  
   - ![-F1/m1*R12 + F2/m2*R12 = 0](media/matrix-math/F1_R12_and_F2_R12.gif)

# Simulation Configurations

Simulation configuration provides an option to run modeling with different time factor.

- Optimal - provide most accurate simulation resul
- 10x - time factor set to 10x 
- 100x - time factor set to 100x 

# Video Recordings

## Pandulum - 100x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 1             | 1        | 1        | 2        | 3     |
| Elastic        | 0             | 1        | 0        | 1        | 1     |
| Matrix         | 1             | 1        | 1        | 2        | 3     |

[![Pandulum 100x](https://img.youtube.com/vi/CZ_dfPfVO-M/mqdefault.jpg)](https://youtu.be/CZ_dfPfVO-M "Pandulum 100x")

## Line - 100x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 2             | 2        | 2        | 4        | 6     |
| Elastic        | 1             | 1        | 1        | 2        | 3     |
| Matrix         | 0             | 0        | 0        | 0        | 0     |

[![Line 100x](https://img.youtube.com/vi/uTghom1pDSs/mqdefault.jpg)](https://youtu.be/uTghom1pDSs "Line 100x")

## Line - 10x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 2             | 2        | 3        | 5        | 7     |
| Elastic        | 2             | 1        | 2        | 3        | 5     |
| Matrix         | 1             | 1        | 1        | 2        | 3     |

[![Line 10x](https://img.youtube.com/vi/27WBwdrFHrE/mqdefault.jpg)](https://youtu.be/27WBwdrFHrE "Line 10x")

## Line - Optimal

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 3             | 1        | 1        | 2        | 5     |
| Elastic        | 2             | 1        | 1        | 2        | 4     |
| Matrix         | 1             | 1        | 2        | 3        | 4     |


[![Line Optimal](https://img.youtube.com/vi/B3NJsNYoTu0/mqdefault.jpg)](https://youtu.be/B3NJsNYoTu0 "Line Optimal")

## Triangle Grid - Optimal

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 1             | 1        | 2        | 3        | 4     |
| Elastic        | 1             | 1        | 1        | 2        | 3     |
| Matrix         | 1             | 1        | 3        | 4        | 5     |

[![Triangle Grid Optimal](https://img.youtube.com/vi/r9zhTKDoSyk/mqdefault.jpg)](https://youtu.be/r9zhTKDoSyk "Triangle Grid Optimal")


## Triangle Grid - 10x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 1             | 1        | 1        | 2        | 3     |
| Elastic        | 0             | 0        | 0        | 0        | 0     |
| Matrix         | 1             | 1        | 2        | 3        | 4     |


[![Triangle Grid 10x](https://img.youtube.com/vi/ru1z6gKe6f0/mqdefault.jpg)](https://youtu.be/ru1z6gKe6f0 "Triangle Grid 10x")


## Triangle Grid - 100x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 2             | 2        | 1        | 3        | 5     |
| Elastic        | 0             | 0        | 0        | 0        | 0     |
| Matrix         | 0             | 1        | 1        | 2        | 2     |


[![Triangle Grid 100x](https://img.youtube.com/vi/l2fo0-HfS_I/mqdefault.jpg)](https://youtu.be/l2fo0-HfS_I "Triangle Grid 100x")

## Swing - Optimal

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 1             | 1        | 2        | 3        | 4     |
| Elastic        | 1             | 1        | 1        | 2        | 3     |
| Matrix         | 1             | 1        | 3        | 4        | 5     |


[![Swing Optimal](https://img.youtube.com/vi/_G4N5KpsYAo/mqdefault.jpg)](https://youtu.be/_G4N5KpsYAo "Swing Optimal")

## Rope - 10x

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 2             | 2        | 1        | 3        | 5     |
| Elastic        | 1             | 1        | 2        | 3        | 4     |
| Matrix         | 0             | 0        | 0        | 0        | 0     |

[![Rope 10x](https://img.youtube.com/vi/UrLe8GCPYH8/mqdefault.jpg)](https://youtu.be/UrLe8GCPYH8 "Rope 10x")

## Total

| Modeling       | Aesthetics    | Firnmess | Friction | Accuracy | Total |
|----------------|---------------|----------|----------|----------|-------|
| Matrix Elastic | 15            | 13       | 14        | 27      | 42    |
| Elastic        | 8             | 7        | 8         | 15      | 23    |
| Matrix         | 6             | 7        | 13        | 20      | 26    |

# Analysis

## Scoring

Scoing on presented video samples are provided in 3 categories:
- Aesthetics - general impression if the simulation looks natural and smooth.
- Acuracy - combination of Firmness and Friction, technical evaluation if modeling fits to the goals.
  - Firmness - less deformation is better. Object that will keep original size of connection will get extra score.
  - Friction - less frictions is better. Object that will swing to base position will get extra score.

## Conclusion

Matrix-Elastic prove that it performs better in both scorings Aesthetical and Accuracy, while Elastic looks more natural Matrix has smaller frictions.

For Triangle Grid model which is closer to simulation plane surface elastic model failed the test completely, while Matrix Elastic looks natural.


## Possible improvement

Matrix Elastic looks natural and aesthetically, while matrix modeling prooved that it can be used for accurate force calcualtion, however there are still exist possibilities to improve simulation:
1. More accurately Matrix does a calculation for force momentum rather than just a force, because junction is connected to another junction, and can move only with cirucal curve around other junction it connected to, so to improve simulation, model positions should be constrained to the original connection length, which also can be presetned as system of equations: sqrt((Pi + dPi) - (Pj + dPj)) = relaxed_spring_length(Pi, Pj), while force momentum is already calculated.
2. Matrix general pattern is also looks natural and smooth, while junction point are vibrating around accurate position, for this reason presented junction point can be averaged using position of previouse steps.

# Application Usage Manual
## Command Line Help

To get a help please use -h flag for the application:

```text
  ./cpp_bridge_v5_app_executable [simulations...] {OPTIONS}

    Application that demonstates soft-body dynamics modeling.

  OPTIONS:

      -h, --help                        Display this help menu
      -s, --help-simulation             Display help for simulation commands
      -l, --headless                    Run in headless mode
      -t, --test                        Run self-testing scenarios
      --gtest_filter=[gtest_filter]     Run self-testing scenarios
      -v, --video                       Write simulation to video file
      simulations...                    Simulation models, use help-simulation
                                        for more information
      "--" can be used to terminate flag options and force all following
      arguments to be treated as positional options
```

## Build Instruction

CMake is used to build the project.

1. Consider that all necessary depdenencies are installed in the system
2. Than run following cmake command from projet source folder:
   ```bash
   mkdir build
   cd build
   cmake -S .. -B .
   cmake --build .
   ```
3. Run tests to check that application is build properly
   ```
   ./cpp_bridge_v5_app_executable -t
   ```

# Contacts

For any questions please contact amid.ukr@gmail.com

