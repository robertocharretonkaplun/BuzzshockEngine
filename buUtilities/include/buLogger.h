#pragma once
#include "buPrerequisitesUtil.h"
#include <buTime.h>
namespace MessageType {
	enum E {
		DEFAULT,
		INFO, 
		WARNING,
		ERROR
	};
}
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

		~buLogger();

		/**
			* @brief Method to log a message
			*/
		void
		Log(String _message, MessageType::E _type);
    
		/**
			* @brief overloaded method to Logs a message
			* @param sMessage message to be logged.
			*/
		buLogger& operator<<(const String& sMessage);
    
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