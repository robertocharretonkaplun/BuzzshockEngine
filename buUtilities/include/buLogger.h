/**
* @brief Class in charge of storing important proccess in the engine
* Ref: https://cppcodetips.wordpress.com/2014/01/02/a-simple-logger-class-in-c/
* Note: Check how to store it on week reports with new dates.
*/
#pragma once
#include "buPrerequisitesUtil.h"
#include <buTime.h>


namespace buEngineSDK {
	class BU_UTILITY_EXPORT buLogger
	{
	public:
		/**
			* @brief Default constructor
			*/
		buLogger() = default;

		/** 
			* @brief Copy constructor
			* @param const buLogger& copy object of the class
			*/
		buLogger(const buLogger&) {};

		/**
			* @brief Assignator constructor
			* @param const buLogger& copy object of the class
			*/
		buLogger& operator=(const buLogger& _log) { return *this; };

		~buLogger() = default;

		/**
			* @brief Method to log a message
			*/
		void
		Log(String _message/*, MessageType::E _type*/);
    
		/**
			* @brief overloaded method to Logs a message
			* @param sMessage message to be logged.
			*/
		buLogger& operator<<(const String& sMessage);
    

		Vector<String> 
		GetLogDataFromFile();
		/**
			* @brief Method in charge of create the instance of logger
			* @return singleton object of Clogger class..
			*/
    static buLogger*
		GetLogger();
	private:
		static const String m_fileName;
		static buLogger* m_this;
		static std::ofstream m_logfile;
		buTime m_time;
	};
}