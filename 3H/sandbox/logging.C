#include <fstream>
#include <stdio.h>
#include <logging.h>

using namespace std;

FILE *Logger::logger = NULL;

void Logger::LogEvent(const char *event)
{
  if (logger == NULL)
    {
      logger = fopen("logger", "w");
    }
  fprintf(logger, "%s\n", event);

}

void Logger::Finalize()
{
  fclose(logger);
}
