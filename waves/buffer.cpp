#include "buffer.h"

#include <string.h>

char *getBuffer()
{
  return buffer;
}

void clearBuffer()
{
  memset(buffer, 0, BUFFER_LENGTH);
}