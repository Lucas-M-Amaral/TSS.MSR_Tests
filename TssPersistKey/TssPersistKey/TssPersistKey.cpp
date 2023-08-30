#include <iostream>
#include <Tpm2.h>

#include "Tpm_Handling.h"
#include "Keys.h"
#include "Utils.h"

TpmCpp::Tpm2 tpm;
TpmCpp::TpmTbsDevice deviceTbs;
TpmCpp::TpmTcpDevice deviceTcp;

/*
    If you set useSimulator to false and useOemKeys to true the
    program will try to read Ek Key and Cert from TPM NV

    Currently this is NOT WORKING!
*/

bool useSimulator = false;
bool useOemKeys = false;

void createNewEkKey(TpmCpp::TPMT_PUBLIC& ek, TpmCpp::TPM_HANDLE& ekHandle) {
    std::cout << ">> Generating EK Key instead of reading from NV\n\n";

    auto createPrimaryResponse = MakeEndorsementKey();
    ek = createPrimaryResponse.outPublic;
    ekHandle = createPrimaryResponse.handle;

    std::cout << "\t> EK Key generated with success!\n\n";
}

int main()
{
    if (true)  // Key Creation and Certify
    {
        InitTpm();

        TpmCpp::TPMT_PUBLIC ek;
        TpmCpp::TPM_HANDLE ekHandle;

        createNewEkKey(ek, ekHandle);
        handleError();
        std::cout << "EK: \n\n" << ek.ToString() << std::endl;

        auto srk = MakeSrkKey();
        TpmCpp::TPM_HANDLE srkHandle = srk.handle;
        handleError();
        std::cout << "\nSRK: \n\n" << srk.ToString() << std::endl;

        //auto lak = MakeAttestationKey();
        //handleError();
        //TpmCpp::TPM_HANDLE lakHandle = lak.handle;
        //std::cout << "\nLAK: \n\n" << lak.ToString() << std::endl;

        auto lak = MakeOrdinaryLak(ekHandle);
        handleError();
        TpmCpp::TPM_HANDLE lakHandle = tpm.Load(ekHandle, lak.outPrivate, lak.outPublic);
        std::cout << "\nLAK: \n\n" << lak.ToString() << std::endl;

        auto devid = MakeLDevidKey(srkHandle);
        handleError();
        TpmCpp::TPM_HANDLE devidHandle = tpm.Load(srkHandle, devid.outPrivate, devid.outPublic);
        std::cout << "\nLDEVID: \n\n" << devid.ToString() << std::endl;

        auto certifyLak = tpm.Certify(ekHandle, lakHandle, {}, TpmCpp::TPMS_NULL_SIG_SCHEME());
        auto certifyDevid = tpm.Certify(devidHandle, lakHandle, {}, TpmCpp::TPMS_NULL_SIG_SCHEME());

        std::cout << "\nCertify Data (EK - LAK): \n\n" << certifyLak.ToString() << std::endl;
        std::cout << "\nCertify Data (LAK - LDevID): \n\n" << certifyDevid.ToString() << std::endl;

        ShutdownTpm();
    }
    if (false)  // Key Persistency
    {
        InitTpm();

        TpmCpp::TPMT_PUBLIC ek;
        TpmCpp::TPM_HANDLE ekHandle;

        //tpm.NV_DefineSpace()

        auto nvHandle = TpmCpp::TPM_HANDLE::NV(0x81FFFFFE);

        //TpmCpp::TPM_HANDLE persistentEkHandle = TpmCpp::TPM_HANDLE::Persistent(nvHandle);

        createNewEkKey(ek, ekHandle);
        std::cout << "EK: \n\n" << ek.ToString() << std::endl;
        handleError();


        //auto s = tpm.StartAuthSession({}, {}, TpmCpp::TPM_SE::POLICY, TpmCpp::TPM_ALG_ID::SHA256, TpmCpp::TPMA_SESSION::continueSession, TpmCpp::TPMT_SYM_DEF(), {}, {});

        //tpm.PolicySecret(TpmCpp::TPM_RH::ENDORSEMENT, s, {}, {}, {}, 0);

        //printBin(tpm.PolicyGetDigest(s), "Session digest");

        tpm._AllowErrors().EvictControl(TpmCpp::TPM_RH::PLATFORM, ekHandle, nvHandle);
        handleError();

        ShutdownTpm();
    }
}