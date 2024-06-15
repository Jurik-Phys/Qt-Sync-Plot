#include "lsl_cpp.h"
#include <array>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <random>

// Modified example from liblsl

/**
* This example program offers an 20-channel stream, float-formatted, that resembles EEG data.
* The example demonstrates also how per-channel meta-data can be specified using the .desc() field
* of the stream information object.
*
* Note that the timer used in the send loop of this program is not particularly accurate.
*/

const char *channels[] = {"FP1", "FP2", "F3", "F4", "C3", "C4", "P3", "P4", "O1" ,"O2", "F7", "F8", "T3", "T4", "T5", "T6", "FZ", "CZ", "PZ", "E1"};

int main(int argc, char *argv[]) {
	std::string name, type;
	if (argc < 3) {
		std::cout
			<< "This opens a stream under some user-defined name and with a user-defined content "
			   "type."
			<< std::endl;
		std::cout << "SendData Name Type [n_channels=20] [srate=500] [max_buffered=360]"
				  << std::endl;
		std::cout
			<< "Please enter the stream name and the stream type (e.g. \"BioSemi EEG\" (without "
			   "the quotes)):"
			<< std::endl;
		std::cin >> name >> type;
	} else {
		name = argv[1];
		type = argv[2];
	}
	int n_channels = argc > 3 ? std::stol(argv[3]) : 20;
	n_channels = n_channels < 20 ? 20 : n_channels;
	int samplingrate = argc > 4 ? std::stol(argv[4]) : 500;
	int max_buffered = argc > 5 ? std::stol(argv[5]) : 360;

    // Randrom data generation values
    int m_channelsCount = n_channels;
    double m_noiseAmpl = 2.5;
    double m_dataAmpl = 1.0;
    double m_dataFreq = 0.4;
    double m_srcRate = samplingrate;
    double m_pointIndex = 0;
    double m_pltTime = 15;
    std::vector<double> *m_initPhase;

    // Generate random initial phase for all channels
    std::random_device rd; // Источник случайного числа
    std::mt19937 gen(rd()); // Генератор Mersenne Twister
    std::uniform_int_distribution<> distrib(0, 99); // Диапазон от 0 до 99
                                                    //
    m_initPhase     = new std::vector<double>(m_channelsCount, 0);
    for (int chIdx = 0; chIdx < m_channelsCount; ++chIdx){
        double phase  = 2*M_PI*distrib(gen)*0.01;
        (*m_initPhase)[chIdx] = phase;
    }

	try {

		// make a new stream_info (500 Hz)
		lsl::stream_info info(
			name, type, n_channels, samplingrate, lsl::cf_float32, std::string(name) += type);

		// add some description fields
		info.desc().append_child_value("manufacturer", "LSL");
		lsl::xml_element chns = info.desc().append_child("channels");
		for (int k = 0; k < n_channels; k++)
			chns.append_child("channel")
				.append_child_value("label", k < 20 ? channels[k] : "Chan-" + std::to_string(k + 1))
				.append_child_value("unit", "microvolts")
				.append_child_value("type", type);

		// make a new outlet
		lsl::stream_outlet outlet(info, 0, max_buffered);
		std::vector<float> sample(n_channels, 0.0);

		// Your device might have its own timer. Or you can decide how often to poll
		//  your device, as we do here.
		int32_t sample_dur_us = 1000000 / (samplingrate > 0 ? samplingrate : 500);
		auto t_start = std::chrono::high_resolution_clock::now();
		auto next_sample_time = t_start;

		// send data forever
		std::cout << "Now sending data... " << std::endl;
		double starttime = ((double)clock()) / CLOCKS_PER_SEC;

        // For testing channel over it's index
           //       SendData   |   Qt-Sync-Plot
           //       channel   <=>       channel
           // "T4"        13  <=>  0
           // "F8"        11  <=>  1
           // "FP2"        1  <=>  2
           // "FP1"        0  <=>  3
           // "F7"        10  <=>  4
           // "T3"        12  <=>  5
           // "T5"        14  <=>  6
           // "O1"         8  <=>  7
           // "O2"         9  <=>  8
           // "T6"        15  <=>  9

        bool tstChannel = false;
        int testChIdx = 8;
		for (unsigned t = 0;; t++) {
			// Create random data for the first 20 channels.
			for (int chIdx = 0; chIdx < 20; chIdx++) {
                // Testing channel condition
                if (!tstChannel){
                    double noise  = m_noiseAmpl*(distrib(gen)*0.01 - 0.5);
                    double signal = m_dataAmpl*std::sin(2*M_PI*m_dataFreq * (1.0/m_srcRate)*m_pointIndex + (*m_initPhase)[chIdx]);

                    sample[chIdx] = signal + noise;

                    if (chIdx == m_channelsCount - 1){
                        m_pointIndex++;
                        if (m_pointIndex > m_srcRate*m_pltTime - 1){
                            m_pointIndex = 0;
                        }
                    }
                }
                else {
                    if (chIdx == testChIdx){
                        double noise = 5.0*(distrib(gen)*0.01 - 0.5);
                        sample[chIdx] = noise;
                    }
                    else {
                        sample[chIdx] = 0.0;
                    }
                }
            }

			// For the remaining channels, fill them with a sample counter (wraps at 1M).
			std::fill(sample.begin() + 20, sample.end(), (float)(t % 1000000));

			// Wait until the next expected sample time.
			next_sample_time += std::chrono::microseconds(sample_dur_us);
			std::this_thread::sleep_until(next_sample_time);

			// send the sample
			std::cout << sample[0] << "\t" << sample[n_channels-1] << std::endl;
			outlet.push_sample(sample);
		}

	} catch (std::exception &e) { std::cerr << "Got an exception: " << e.what() << std::endl; }
	std::cout << "Press any key to exit. " << std::endl;
	std::cin.get();
	return 0;
}
