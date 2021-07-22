#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(void)
{
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    int return_code = 0;

    if (s == -1)
    {
        perror("Error while opening socket");
        return_code = -1;
    }

    if (return_code == 0)
    {
        struct ifreq ifr;
        const char *ifname = "vcan0";
        (void)strcpy(ifr.ifr_name, ifname);
        ioctl(s, SIOCGIFINDEX, &ifr);

        struct sockaddr_can addr;
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        (void)printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

        if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        {
            perror("Error in socket bind");
            return_code = -2;
        }

        if (return_code == 0)
        {
            int writeToEdrFlag = 0;

            // CANパケットキャプチャ無限ループ
            // EDRへデータ書き込み完了後、内部でexitされる
            while (writeToEdrFlag == 0)
            {
                struct can_frame frame;
                // CANパケットキャプチャ
                int n_bytes = read(s, &frame, sizeof(struct can_frame));

                (void)printf("Read %d bytes\n", n_bytes);

                struct struct_ret checkFrameData =
                    checkFrame(frame.can_id, frame.can_dlc, frame.data); // F*言語関数

                if ((checkFrameData.value == 1) && (checkFrameData.struct_error.code > 0))
                {
                    struct struct_ret edr = recordInEdr(frame.can_id, frame.can_dlc, frame.data);

                    if (edr.struct_error.code > 0)
                    {
                        (void)printf("record edr error message: %s(%d)", edr.struct_error.message, edr.struct_error.code);
                        continue;
                    }
                    writeToEdrFlag = edr.value
                }
                else
                {
                    (void)printf("parse frame error message: %s(%d)", checkFrameData.struct_error.message, checkFrameData.struct_error.code)
                }
            }
        }
    }

    return return_code;
}