# Cursor predicting signal processing

This repo contains applications for following cursor position. *(currently only velocity model kalman filter)*

## Kalman filter

[Kalman filterering](https://en.wikipedia.org/wiki/Kalman_filter) is a algorithm to estimate a phenomenom from noisy measurements. A basic block
diagram of kalman filter without control inputs is

![kalman](./images/kalman.png)

1. We predict based on the system model the next state
2. We update the state with the model predictions and the new measurements

The estimation for actual measurements is the state vector coming from the update step.

Depending on how we initialize the F, Q and H we can estimate different phenomenons

### Velocity model

I don't have enough education on systems and control theory I could explain
how the matrixes are formulated but they atleast seem to work :D