#pragma once

#include <stdint.h>
//#include <math.h>

// Feature 1: Energy (sum of squares / 100)
float calculate_energy(const float* samples, int length) 
{
    float sum_squares = 0.0f;
    for (int i = 0; i < length; i++) {
        sum_squares += samples[i] * samples[i];
    }
    return sum_squares / 100.0f;
}

// Feature 2: Positive count
float calculate_pos_count(const float* samples, int length) 
{
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (samples[i] > 0.0f) {
            count++;
        }
    }
    return (float)count;
}

// Feature 3: Above mean count
float calculate_above_mean(const float* samples, int length) 
{
    // Calculate mean
    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        sum += samples[i];
    }
    float mean = sum / length;
    
    // Count above mean
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (samples[i] > mean) {
            count++;
        }
    }
    return (float)count;
}

// Feature 4: Argmax (index of maximum value)
float calculate_argmax(const float* samples, int length) 
{
    int max_idx = 0;
    float max_val = samples[0];
    
    for (int i = 1; i < length; i++) {
        if (samples[i] > max_val) {
            max_val = samples[i];
            max_idx = i;
        }
    }
    return (float)max_idx;
}

// Extract all 4 features in correct order
void extract_features(const float* samples, int length, float* features_out) 
{
    features_out[0] = calculate_energy(samples, length);       // x_energy
    features_out[1] = calculate_pos_count(samples, length);    // x_pos_count
    features_out[2] = calculate_above_mean(samples, length);   // x_above_mean
    features_out[3] = calculate_argmax(samples, length);       // x_argmax
}
