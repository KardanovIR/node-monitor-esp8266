#include "buffer.h"

char *getBuffer()
{
  return buffer;
}

void clearBuffer()
{
  memset(buffer, 0, BUFFER_LENGTH);
}