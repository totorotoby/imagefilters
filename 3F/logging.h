
#ifndef  LOGGING_H
#define  LOGGING_H

#include <exception>
#include <stdio.h>

using std::exception;

class Logger
{
public:
  static void LogEvent(const char *event);
  static void Finalize();
  
private:
  static FILE *logger;
  
};

class DataFlowException : public exception
{
protected:
  char msg[1024];
public:
  DataFlowException(const char *type, const char *error)
  {
    sprintf(msg, "%s: %s", type, error);
    Logger::LogEvent(msg);
  };
  virtual const char  *what() const throw() { return msg; };
  
};




#endif
