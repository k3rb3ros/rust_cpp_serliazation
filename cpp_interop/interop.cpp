#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "tiny_aircraft_state_data.h"

using std::cout;
using std::cerr;
using std::hex;
using std::endl;

int main (void)
{
    TinyAircraftState as = create_default_struct();
    std::array<uint8_t, 1024> buff{};

    as.pitch = 1.23f;
    as.roll = 2.34f;
    as.yaw = 3.45;
    as.status = 0xAB;
    as.valid = true;

    if (serialize(&as, &buff[0], buff.size()))
    {
        std::string test{reinterpret_cast<const char*>(buff.data())};
        cout << "serialized struct: " << test << endl;
    }
    else
    {
        cerr << "unable to serialize TinyAircraftState" << endl;
    }

    TinyAircraftState ds_as = deserialize(buff.data());
    cout << "Deserialized struct" << endl;
    cout << "Pitch: " << ds_as.pitch << endl;
    cout << "Roll:" << ds_as.roll << endl;
    cout << "Yaw:" << ds_as.yaw << endl;
    cout << "Status: " << hex << "0x" << static_cast<int32_t>(ds_as.status) << endl;
    cout << "Valid: " << ds_as.valid << endl;

    return 0;
}
