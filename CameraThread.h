#include <winsock2.h>
#include <thread>

class CameraThread {
public:

	CameraThread(SOCKET socket) : cameraSocket_(socket){}
	void startCameraThread() { cameraThread_ = std::jthread(&CameraThread::cameraThreadLoop, this); };
private:
	void cameraThreadLoop();
	SOCKET cameraSocket_;

	std::jthread cameraThread_;
};