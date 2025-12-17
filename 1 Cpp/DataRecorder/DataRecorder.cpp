

#include "Particle.h"
#include "Microphone_PDM.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

#define LENGTH 2000
#define THRESHOLD 40

enum State
{
	WAITING,
	CONNECT,
	RUNNING,
	FINISH
};
State state = WAITING;

SerialLogHandler logHandler;
IPAddress serverAddr = IPAddress(192, 168, 245, 10);
int serverPort = 7123;
TCPClient client;
unsigned long recordingStart;

bool red = false;

uint8_t max_t = 128 + THRESHOLD;
uint8_t min_t = 128 - THRESHOLD;

void buttonHandler(system_event_t event, int data);
bool getThreshold(void *pSamples, uint16_t numSamples);

void setup()
{
	Particle.connect();
	pinMode(D7, OUTPUT); // Blue led -> recording running
	digitalWrite(D7, LOW);

	int err = Microphone_PDM::instance()
				  .withOutputSize(Microphone_PDM::OutputSize::UNSIGNED_8)
				  .withRange(Microphone_PDM::Range::RANGE_2048)
				  .withSampleRate(8000)
				  .init();

	if (err)
		Log.error("PDM decoder init err=%d", err);

	if (Microphone_PDM::instance().start())
		Log.error("PDM decoder start err=%d", err);
}

void loop()
{
	switch (state)
	{
	case WAITING:
		Microphone_PDM::instance().noCopySamples([](void *pSamples, size_t numSamples)
												 {
			if(getThreshold(pSamples, numSamples))	// If threshold crossed
				state = CONNECT; });
		break;

	case CONNECT:
		if (client.connect(serverAddr, serverPort)) // Connected
		{
			Log.info("starting");
			recordingStart = millis();
			state = RUNNING;
			if (!red)
			{
				red = true;
				digitalWrite(D7, HIGH);
			}
		}
		else
		{
			Log.info("failed to connect to server");
			state = WAITING;
		}
		break;

	case RUNNING:
		Microphone_PDM::instance().noCopySamples([](void *pSamples, size_t numSamples)
												 { client.write((const uint8_t *)pSamples, Microphone_PDM::instance().getBufferSizeInBytes()); });

		if (millis() - recordingStart >= LENGTH)
			state = FINISH;

		break;

	case FINISH:
		client.stop();
		Log.info("stopping");
		state = WAITING;
		if (red)
		{
			red = false;
			digitalWrite(D7, LOW);
		}
		break;
	}
}

// Check if threshold is crossed
bool getThreshold(void *pSamples, uint16_t numSamples)
{
	const uint8_t *samples = (const uint8_t *)pSamples;

	for (size_t i = 0; i < numSamples; i++)
	{
		if (samples[i] == 0 || samples[i] == 255) // Ignore these
			continue;

		if (samples[i] > max_t || samples[i] < min_t) // Recording threshold
			return true;
	}
	return false;
}
