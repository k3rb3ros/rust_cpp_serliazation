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

bool serialize(const TinyAircraftState *state, uint8_t *ser_buff, uint32_t max_len);

TinyAircraftState deserialize(const uint8_t *ser_buff);

} // extern "C"
