
#include "Particle.h"
#include "features.h"               // Feature extraction
#include "feature_scaler.h"         // Scaler parametre
#include "knock_detector.h"         // emlearn model

#include "test_audio_knock101.h"    // Test audio

#define NUM_FEATURES		4
#define THRESHOLD			40
#define TARGET_LENGTH		15800
#define DOWNSAMPLE_FACTOR	2
#define DOWNSAMPLED_LENGTH (TARGET_LENGTH / DOWNSAMPLE_FACTOR)
SYSTEM_MODE(SEMI_AUTOMATIC);

uint8_t audio_buffer[TARGET_LENGTH];

void setup() 
{
	Serial.begin(115200);
	waitFor(Serial.isConnected, 10000);

    static float audio_float[DOWNSAMPLED_LENGTH];
	for (int i = 0; i < DOWNSAMPLED_LENGTH; i++)
		audio_float[i] = (int8_t)(samples[i * DOWNSAMPLE_FACTOR] - 128) / 128.0f;

	delay(1000);

    float features[4];
    extract_features(audio_float, DOWNSAMPLED_LENGTH, features);

    float features_scaled[4];

	for(uint8_t i = 0; i < NUM_FEATURES; i++)
		features_scaled[i] = (features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];

    bool prediction = knock_detector_FLOAT_predict(features_scaled, 4);
    
    Serial.println("Prediction:");
    Serial.printf("  Class: %d (%s)\n", prediction, 
                  prediction == 0 ? "Knock" : "Noise");
			  
}

void loop() 
{

}

