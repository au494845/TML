#include "Particle.h"
#include "Microphone_PDM.h"

//SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

SerialLogHandler logHandler;


const unsigned long MAX_RECORDING_LENGTH_MS = 3000;
const int8_t THRESHOLD = 50;	// 8bit threshold start recording
uint8_t max_t = 128 + THRESHOLD;
uint8_t min_t = 128 - THRESHOLD;

IPAddress serverAddr = IPAddress(192,168,245,10);
int serverPort = 7123;

TCPClient client;
unsigned long recordingStart;

enum State { STATE_WAITING, STATE_CONNECT, STATE_RUNNING, STATE_FINISH };
State state = STATE_WAITING;

bool red = false;

void buttonHandler(system_event_t event, int data);
bool getThreshold(void *pSamples, uint16_t numSamples);		// max 65535 samples

void setup() {
	Particle.connect();

	System.on(button_click, buttonHandler); // Handler for MODE button

	pinMode(D7, OUTPUT);        // Blue led -> recording running (?)
	pinMode(S4, OUTPUT);					// Indicator - recording  
	digitalWrite(D7, LOW);
	digitalWrite(S4, LOW);

  	int err = Microphone_PDM::instance()
		//.withOutputSize(Microphone_PDM::OutputSize::SIGNED_16)
		.withOutputSize(Microphone_PDM::OutputSize::UNSIGNED_8)
		.withRange(Microphone_PDM::Range::RANGE_2048)
		.withSampleRate(8000)
		.init();

	if (err) {
		Log.error("PDM decoder init err=%d", err);
	}

	err = Microphone_PDM::instance().start();
	if (err) {
		Log.error("PDM decoder start err=%d", err);
	}
}

void loop() {

	switch(state) {
	case STATE_WAITING:
		Microphone_PDM::instance().noCopySamples([](void *pSamples, size_t numSamples) {
			if(getThreshold(pSamples, numSamples))	// If threshold crossed
				state = STATE_CONNECT;
		});
		break;

	case STATE_CONNECT:
		if (client.connect(serverAddr, serverPort)) // Connected
		{	
			Log.info("starting");
			digitalWrite(D7, HIGH);
			recordingStart = millis();
			state = STATE_RUNNING;
			if(!red)
			{
				red = true;
				digitalWrite(S4, HIGH);	// Turn on red LED
			}
		}
		else {
			Log.info("failed to connect to server");
			state = STATE_WAITING;
		}
		break;

	case STATE_RUNNING:
		Microphone_PDM::instance().noCopySamples([](void *pSamples, size_t numSamples) {
		    client.write((const uint8_t *)pSamples, Microphone_PDM::instance().getBufferSizeInBytes());
		});

		if (millis() - recordingStart >= MAX_RECORDING_LENGTH_MS) {
			state = STATE_FINISH;
		}
		break;

	case STATE_FINISH:
		digitalWrite(D7, LOW);
		client.stop();
		Log.info("stopping");
		state = STATE_WAITING;
		if (red)
		{
			red = false;
			digitalWrite(S4, LOW);	// Turn off red LED 
		}
		break;
	}
}

// Check if threshold is crossed
bool getThreshold(void *pSamples, uint16_t numSamples) {
	const uint8_t *samples = (const uint8_t *)pSamples;

	for (size_t i = 0; i < numSamples; i++) {
		if (samples[i] == 0 || samples[i] == 255) // These apparently appear every time
			continue;

		if(samples[i] > max_t || samples[i] < min_t)	// Start recording when threshold crossed
			return true;
	}
	return false;
}

// button handler for the SETUP button, used to toggle recording on and off
void buttonHandler(system_event_t event, int data) {
	switch(state) {
	case STATE_WAITING:
		if (WiFi.ready()) {
			state = STATE_CONNECT;
		}
		break;

	case STATE_RUNNING:
		state = STATE_FINISH;
		break;
	}
}