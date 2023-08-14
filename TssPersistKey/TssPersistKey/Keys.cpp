#include <string>
#include <memory>
#include <stdexcept>
#include "keys.h"
#include "templates.h"

extern TpmCpp::Tpm2 tpm;

TpmCpp::CreatePrimaryResponse MakeEndorsementKey() {
    return tpm._AllowErrors().CreatePrimary(TpmCpp::TPM_RH::ENDORSEMENT, {}, Templates::getEkRsaTemplate(),
        {}, {});

} // MakeEndorsementKey()

TpmCpp::CreatePrimaryResponse MakeAttestationKey() {
    return tpm._AllowErrors().CreatePrimary(TpmCpp::TPM_RH::ENDORSEMENT, {}, Templates::getLakRsaTemplate(),
        {}, {});
} // MakeAttestationKey()

TpmCpp::CreateResponse MakeLDevidKey(TpmCpp::TPM_HANDLE ekHandle) {
    return tpm._AllowErrors().Create(ekHandle, {}, Templates::getLDevidRsaTemplate(),
        {}, {});
} // MakeLDevidKey()