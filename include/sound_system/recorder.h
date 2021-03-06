/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * capturing sound
 */
#include <mutex>
#include "system.h"
#include "definitions.h"

#ifndef RECORDER_H
#define RECORDER_H

class Recorder{
	public:
		Recorder();
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		virtual ~Recorder();
		void virtual start() = 0;
		result_t virtual getStream(void * buff, int size) = 0;
		void virtual stop() = 0;
		inline status_t getStatus() { return status;}


	protected:
	std::thread * thread_capture;
	status_t status;
	std::mutex capture_thread_mutex;

};

#endif
