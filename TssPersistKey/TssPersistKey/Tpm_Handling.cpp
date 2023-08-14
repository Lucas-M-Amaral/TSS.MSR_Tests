#include <iostream>
//#include <Tpm2.h>
#include "Tpm_Handling.h"

int InitTpm() {
    if (useSimulator) {
        std::cout << ">> You're using a simulator (TCP) <<\n" << std::endl;
        if (!deviceTcp.Connect("127.0.0.1", 2321)) {
            std::cerr << "Could not connect to the TPM TCP device\n";
            return -1;
        }
        std::cout << ">> Connected with the simulator <<\n" << std::endl;
        tpm._SetDevice(deviceTcp);
        deviceTcp.PowerOff();
        deviceTcp.PowerOn();
        tpm.Startup(TpmCpp::TPM_SU::CLEAR);
        return 0;
    }

    std::cout << ">> You're using real TPM (TBS) <<\n" << std::endl;

    if (!deviceTbs.Connect()) {
        std::cerr << "Could not connect to the TPM TBS device\n";
        return -1;
    }

    tpm._SetDevice(deviceTbs);
    return 0;
} // InitTpm()

void ShutdownTpm() {
    if (!useSimulator) return;

    tpm.Shutdown(TpmCpp::TPM_SU::CLEAR);
    deviceTcp.PowerOff();
} // ShutdownTpmSimulator()