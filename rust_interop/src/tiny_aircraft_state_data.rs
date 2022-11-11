use serde::{Serialize, Deserialize};
use std::ffi::{CStr};
use std::os::raw::{c_char, c_int};

#[derive(Debug, Deserialize, Serialize)]
#[repr(C)]
pub struct TinyAircraftState {
    pub pitch: f32,
    pub roll: f32,
    pub yaw: f32,
    pub status: u8,
    pub valid: bool,
}

impl Default for TinyAircraftState {
    fn default() -> TinyAircraftState {
        TinyAircraftState {
            pitch: 0.0,
            roll: 0.0,
            yaw: 0.0,
            status: 0x0,
            valid: false,
        }
    }
}

#[no_mangle]
pub extern fn create_default_struct() -> TinyAircraftState {
    return TinyAircraftState{ ..Default::default() };
}

#[no_mangle]
pub extern fn serialize(state: &TinyAircraftState, ser_buff:*mut c_char, max_len:c_int) -> bool {
    let binding = serde_json::to_string(&state).unwrap();
    let json_str = binding.as_bytes();
    let c_str_len= json_str.len();
    let buffer_big_enough = c_str_len + 1 <= max_len as usize;

    if buffer_big_enough {
        unsafe {
            let mut i: isize = 0; 
            for byte in json_str {
                let src_byte = *byte as c_char;
                let dest_byte = ser_buff.offset(i);
                *dest_byte = src_byte;
                i += 1;
            }
            // null terminate C-String
            i += 1;
            let null_term_byte = ser_buff.offset(i);
            *null_term_byte = 0;

            return true;
        }
    }

    return false;
}

#[no_mangle]
pub extern fn deserialize(ser_buff:*mut c_char) -> TinyAircraftState {  
    let serialized_c_str = unsafe { CStr::from_ptr(ser_buff) };
    let serialized_rust_str = String::from_utf8_lossy(serialized_c_str.to_bytes()).to_string();
    let deserialized_struct: TinyAircraftState = serde_json::from_str(&serialized_rust_str).unwrap();

    return deserialized_struct;
}
