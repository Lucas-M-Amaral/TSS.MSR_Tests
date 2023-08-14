#pragma once

#include <Tpm2.h>

extern TpmCpp::Tpm2 tpm;
extern TpmCpp::TpmTbsDevice deviceTbs;
extern TpmCpp::TpmTcpDevice deviceTcp;

extern bool useSimulator;

int InitTpm();
void ShutdownTpm();