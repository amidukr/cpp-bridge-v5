[![Build Status](https://travis-ci.org/amidukr/cpp-bridge-v5.svg?branch=master)](https://travis-ci.org/amidukr/cpp-bridge-v5) [![codecov](https://codecov.io/gh/amidukr/cpp-bridge-v5/branch/master/graph/badge.svg)](https://codecov.io/gh/amidukr/cpp-bridge-v5)


# Project Overview

This project is sample implementation for matrix based soft-body modeling.

The intention of this project is to prove that use of system of linear equation (Elastic Matrix model) for calcualation of force strength distribution accross soft-body model will give better accuracy than classical elastic model on larger simulation time interval.

# Simulation Configurations

Optimal - 
10x - 
100x - 

# Video Recordings

## Pandulum - 100x

### Elastic

### Matrix

### Matrix Elastic

## Line - 100x

### Elastic

### Matrix

### Matrix Elastic

## Line - 10x

### Elastic

### Matrix

### Matrix Elastic

## Line - optimal

### Elastic

### Matrix

### Matrix Elastic

## Triangle Grid - optimal

### Elastic

### Matrix

### Matrix Elastic

## Triangle Grid - 10x

### Elastic

### Matrix

### Matrix Elastic

## Triangle Grid - 100x

### Elastic

### Matrix

### Matrix Elastic

## Swing - optimal

Matrix is winner in this test, the reason for that  Matrix keeps energy in best ways - what means that iterative calculation is most accurate, second place takes  Matrix Elastic. Elastic losses energy pretty fast, because of frictionsc cuased by  inefficiency of classical  elastic algorithm.

### Elastic

### Matrix

### Matrix Elastic




# TODO:
- Project Overview
  - Matrix
  - Presented Models
- Models
  - Elastic Model
  - Matrix Model
  - Elastic Matrix Model
- Video Recordings
- Conclusion and Analysis
- Application Usage Manual
  - Command Line Help
  - Build Instruction
- Contacts

 
  
