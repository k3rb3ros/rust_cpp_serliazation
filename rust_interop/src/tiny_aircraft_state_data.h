#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

struct TinyAircraftState {
  float pitch;
  float roll;
  float yaw;
  uint8_t status;
  bool valid;
};

extern "C" {

TinyAircraftState create_default_struct();

bool serialize(const TinyAircraftState *state, char *ser_buff, int max_len);

TinyAircraftState deserialize(char *ser_buff);

} // extern "C"
