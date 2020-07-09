#ifndef TGVOIP_IMPL_H
#define TGVOIP_IMPL_H

#include <iostream>

#include "Instance.h"

namespace tgcalls {

class Manager;
template <typename T>
class ThreadLocalObject;

class InstanceImpl final : public Instance {
public:
	explicit InstanceImpl(Descriptor &&descriptor);
	~InstanceImpl() override;

	static int GetConnectionMaxLayer();
	static std::string GetVersion();

	void receiveSignalingData(const std::vector<uint8_t> &data) override;
	void setSendVideo(bool sendVideo) override;
	void setNetworkType(NetworkType networkType) override;
	void setMuteMicrophone(bool muteMicrophone) override;
	void setIncomingVideoOutput(std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> sink) override;
	void setAudioOutputGainControlEnabled(bool enabled) override;
	void setEchoCancellationStrength(int strength) override;
	void setAudioInputDevice(std::string id) override;
	void setAudioOutputDevice(std::string id) override;
	void setInputVolume(float level) override;
	void setOutputVolume(float level) override;
	void setAudioOutputDuckingEnabled(bool enabled) override;
	std::string getLastError() override;
	std::string getDebugInfo() override;
	int64_t getPreferredRelayId() override;
	TrafficStats getTrafficStats() override;
	PersistentState getPersistentState() override;
	FinalState stop() override;
	//void controllerStateCallback(Controller::State state);

private:
	class LogSinkImpl;

	std::unique_ptr<ThreadLocalObject<Manager>> _manager;
	std::unique_ptr<LogSinkImpl> _logSink;
	std::function<void(State)> _stateUpdated;
	std::function<void(const std::vector<uint8_t> &)> _signalingDataEmitted;

};

} // namespace tgcalls

#endif