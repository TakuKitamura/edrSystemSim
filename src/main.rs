use socketcan::*;

fn main() {
    // open can device
    let vcan = CANSocket::open("vcan0");

    // match vcan
    match vcan {
        Ok(can) => {
            // infinite loop
            loop {
                // read can frame
                let can_frame = can.read_frame();
                // print can frame
                println!("{:?}", can_frame);

                // match can_frame
                match can_frame {
                    Ok(frame) => {}
                    Err(err) => {
                        // print error
                        println!("{}", err);
                    }
                }
            }
        }
        Err(e) => {
            // print canSocketOpenError message
            println!("{}", e);
            return;
        }
    }
}
