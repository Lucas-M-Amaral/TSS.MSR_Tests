#include <iostream>
#include <Tpm2.h>

#include "Tpm_Handling.h"
#include "Keys.h"


TpmCpp::Tpm2 tpm;
TpmCpp::TpmTbsDevice deviceTbs;
TpmCpp::TpmTcpDevice deviceTcp;

/*
    If you set useSimulator to false and useOemKeys to true the
    program will try to read Ek Key and Cert from TPM NV

    Currently this is NOT WORKING!
*/

bool useSimulator = true;
bool useOemKeys = false;

void createNewEkKey(TpmCpp::TPMT_PUBLIC& ek, TpmCpp::TPM_HANDLE& ekHandle) {
    std::cout << ">> Generating EK Key instead of reading from NV\n\n";

    auto createPrimaryResponse = MakeEndorsementKey();
    ek = createPrimaryResponse.outPublic;
    ekHandle = createPrimaryResponse.handle;

    std::cout << "\t> EK Key generated with success!\n\n";
}

void handleError() {
    if (!tpm._LastCommandSucceeded()) {
        std::cout << "Command failed! " << TpmCpp::EnumToStr(tpm._GetLastResponseCode()) << std::endl;
        ShutdownTpm();
        exit(-1);
    }
}

int main()
{
    if (false)
    {
        InitTpm();

        TpmCpp::TPMT_PUBLIC ek;
        TpmCpp::TPM_HANDLE ekHandle;

        createNewEkKey(ek, ekHandle);
        std::cout << "EK: \n\n" << ek.ToString() << std::endl;
        handleError();

        auto lak = MakeAttestationKey();
        TpmCpp::TPM_HANDLE lakHandle = lak.handle;
        std::cout << "\nLAK: \n\n" << lak.ToString() << std::endl;
        handleError();

        auto devid = MakeLDevidKey(ekHandle);
        TpmCpp::TPM_HANDLE devidHandle = tpm.Load(ekHandle, devid.outPrivate, devid.outPublic);
        std::cout << "\nLDEVID: \n\n" << devid.ToString() << std::endl;
        handleError();


        ShutdownTpm();
    }
    if (true)
    {
        InitTpm();

        TpmCpp::GetCapabilityResponse gt = tpm.GetCapability(TpmCpp::TPM_CAP::AUTH_POLICIES, NULL, 50);

        std::cout << gt.ToString() << std::endl;

        ShutdownTpm();
    }
}