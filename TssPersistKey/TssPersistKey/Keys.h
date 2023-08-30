#pragma once

#include <Tpm2.h>

TpmCpp::CreatePrimaryResponse MakeEndorsementKey();
TpmCpp::CreatePrimaryResponse MakeAttestationKey();
TpmCpp::CreatePrimaryResponse MakeSrkKey();
TpmCpp::CreateResponse MakeOrdinaryLak(TpmCpp::TPM_HANDLE ekHandle);
TpmCpp::CreateResponse MakeLDevidKey(TpmCpp::TPM_HANDLE lakHandle);