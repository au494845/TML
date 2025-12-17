
#include "Particle.h"
#include "features.h"          // Feature extraction
#include "feature_scaler.h"    // Scaler parametre
#include "knock_detector_FLOAT.h"    // emlearn model
#include "Microphone_PDM.h"


#define NUM_FEATURES		4
#define THRESHOLD			40
#define TARGET_LENGTH		15800
#define DOWNSAMPLE_FACTOR	2
#define DOWNSAMPLED_LENGTH	(TARGET_LENGTH / DOWNSAMPLE_FACTOR)
#define MAX					(128 + THRESHOLD)
#define MIN					(128 - THRESHOLD)

SYSTEM_MODE(SEMI_AUTOMATIC);

bool recording = false;
uint8_t audio_buffer[TARGET_LENGTH];
size_t buffer_index = 0;


/**
 * Process audio buffer & predict
 */
void processAudio()
{
	// Convert & downsample
	static float audio_float[DOWNSAMPLED_LENGTH];
	for (uint16_t i = 0; i < DOWNSAMPLED_LENGTH; i++)
		audio_float[i] = (int8_t)(audio_buffer[i * DOWNSAMPLE_FACTOR] - 128) / 128.0f;

	// Extract features
	float features[NUM_FEATURES];	
	extract_features(audio_float, DOWNSAMPLED_LENGTH, features);

	// Scale features
	float features_scaled[NUM_FEATURES];
	for(uint8_t i = 0; i < NUM_FEATURES; i++)
		features_scaled[i] = (features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];

	// Predict (I see counting in my future)
	bool prediction = knock_detector_FLOAT_predict(features_scaled, NUM_FEATURES);
	Serial.printf("Prediction: %d\n", prediction);

	// Present prediction
	switch (prediction)
	{
		case 0:
			RGB.color(0, 100, 0);
			break;
		case 1:
			RGB.color(0, 0, 100);
			break;
	}

	delay(2000);
	RGB.color(0, 0, 0);
}

/**
 * Audio callback
 */
void audioCallback(void *pSamples, size_t numSamples)
{
	if (numSamples == 0) 
		return;

	uint8_t* samples = (uint8_t*)pSamples;

	if(!recording)
	{
		// Check if threshold is crossed
		for (size_t i = 0; i < numSamples; i++) 
		{
			if (samples[i] == 0 || samples[i] == 255)		// Ignore these
				continue;

			if(samples[i] > MAX || samples[i] < MIN)		// Recording threshold
			{
				recording = true;
				buffer_index = 0;
				RGB.color(100, 0, 0);

				// Collect the rest of buffer
                for (size_t j = i; j < numSamples && buffer_index < TARGET_LENGTH; j++)
                    audio_buffer[buffer_index++] = samples[j];

				break;
			}
		}			
	}
	else
	{
		// collect samples
		for (size_t i = 0; i < numSamples && buffer_index < TARGET_LENGTH; i++)
			audio_buffer[buffer_index++] = samples[i];

		// Process samples if TERGET_LENGTH reached
		if (buffer_index >= TARGET_LENGTH) 
		{
			recording = false;
			RGB.color(0, 0, 0);
			processAudio();
		}
	}
}

/**
 * Setup RGB led, microphone and serial port
 */
void setup() 
{
	Serial.begin(115200);
    RGB.control(true);
    RGB.color(0, 0, 0);

  	int err = Microphone_PDM::instance()
		.withOutputSize(Microphone_PDM::OutputSize::UNSIGNED_8)
		.withRange(Microphone_PDM::Range::RANGE_2048)
		.withSampleRate(8000)
		.init();

	if (Microphone_PDM::instance().start())
		Serial.printf("PDM decoder start err=%d", err);
}

/**
 * Main loop, check for new samples
 */
void loop() 
{
	Microphone_PDM::instance().noCopySamples(audioCallback);
}

