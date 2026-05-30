#include <CameraThread.h>
#include <vector>
#include <cstdint>
#include <opencv2/opencv.hpp>

void CameraThread::cameraThreadLoop() {

	//start the OpenCV window thread to display the camera feed
	cv::startWindowThread();

	int frameSize = 0;

	//infinite loop to receive frames from the client and display them using OpenCV
	while (true) {

		//receive the size of the incoming frame
		if (recv(cameraSocket_, (char*)&frameSize, sizeof(int), 0) <= 0) {
			break; // Connection closed or error
		}

		//initialize a vector to hold the incoming frame data
		std::vector<char> frameVec(frameSize);

		//receive the frame data from the client
		if (recv(cameraSocket_, (char*)frameVec.data(), frameSize, MSG_WAITALL) <= 0) {
			break;
		}

		//decode the received frame data into an OpenCV Mat object
		cv::Mat frame = cv::imdecode(frameVec, cv::IMREAD_COLOR);

		//if the frame is empty, skip it and continue to the next iteration of the loop
		if (frame.empty()) {
			std::cout << "Failed to decode frame. Skipping." << std::endl;
			continue;
		}

		uint8_t* pixelData = reinterpret_cast<uint8_t*>(frameVec.data());

		//show the decoded frame in an OpenCV window
		cv::imshow("Camera Feed", frame);
		cv::waitKey(1);
	}
}