#pragma once

#include <iostream>
#include <Tpm2.h>

#include "Tpm_Handling.h"

void handleError();
void printBin(TpmCpp::ByteVec buffer, std::string label);