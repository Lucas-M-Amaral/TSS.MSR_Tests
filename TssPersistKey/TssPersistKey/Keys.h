#pragma once

#include <Tpm2.h>

TpmCpp::CreatePrimaryResponse MakeEndorsementKey();
TpmCpp::CreatePrimaryResponse MakeAttestationKey();
TpmCpp::CreateResponse MakeLDevidKey(TpmCpp::TPM_HANDLE lakHandle);