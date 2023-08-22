#include "Utils.h"

void handleError() {
    if (!tpm._LastCommandSucceeded()) {
        std::cout << "Command failed! " << TpmCpp::EnumToStr(tpm._GetLastResponseCode()) << std::endl;
        ShutdownTpm();
        exit(-1);
    }
}

void printBin(TpmCpp::ByteVec buffer, std::string label = "") {
    std::cout << label << " (" << buffer.size() << "):" << std::endl;
    for (int i = 0; i < buffer.size(); i++)
        printf("%02x ", buffer[i]);
    std::cout << std::endl << std::endl;
}