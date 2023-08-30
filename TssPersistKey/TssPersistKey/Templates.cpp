#include <string>
#include <memory>
#include <stdexcept>
#include "Templates.h"

static const TpmCpp::TPMT_SYM_DEF_OBJECT Aes128Cfb{ TpmCpp::TPM_ALG_ID::AES, 128, TpmCpp::TPM_ALG_ID::CFB };

TpmCpp::TPMT_PUBLIC Templates::getEkRsaTemplate() {
    return TpmCpp::TPMT_PUBLIC(
        TpmCpp::TPM_ALG_ID::SHA256,
        TpmCpp::TPMA_OBJECT::decrypt
        | TpmCpp::TPMA_OBJECT::restricted
        | TpmCpp::TPMA_OBJECT::fixedParent
        | TpmCpp::TPMA_OBJECT::fixedTPM
        | TpmCpp::TPMA_OBJECT::sensitiveDataOrigin
        | TpmCpp::TPMA_OBJECT::userWithAuth,
        {},           // No policy
        TpmCpp::TPMS_RSA_PARMS(Aes128Cfb, TpmCpp::TPMS_NULL_ASYM_SCHEME(), 2048, 65537),
        TpmCpp::TPM2B_PUBLIC_KEY_RSA());
}

TpmCpp::TPMT_PUBLIC Templates::getLakRsaTemplate() {
    return TpmCpp::TPMT_PUBLIC(
        TpmCpp::TPM_ALG_ID::SHA256,    // nameAlg

        TpmCpp::TPMA_OBJECT::fixedTPM                   //
        | TpmCpp::TPMA_OBJECT::fixedParent              //
        | TpmCpp::TPMA_OBJECT::sensitiveDataOrigin      //
        | TpmCpp::TPMA_OBJECT::userWithAuth             // objectAttributes
        | TpmCpp::TPMA_OBJECT::restricted               //
        | TpmCpp::TPMA_OBJECT::sign,                    //

        {}, // authPolicy (no policy)
        TpmCpp::TPMS_RSA_PARMS({}, TpmCpp::TPMS_SCHEME_RSASSA(TpmCpp::TPM_ALG_ID::SHA256), 2048, 0), // parameters
        TpmCpp::TPM2B_PUBLIC_KEY_RSA());    // unique
}

TpmCpp::TPMT_PUBLIC Templates::getSrkRsaTemplate() {
    return TpmCpp::TPMT_PUBLIC(
        TpmCpp::TPM_ALG_ID::SHA256,	// nameAlg

        TpmCpp::TPMA_OBJECT::fixedTPM               //
        | TpmCpp::TPMA_OBJECT::fixedParent          //
        | TpmCpp::TPMA_OBJECT::sensitiveDataOrigin  //
        | TpmCpp::TPMA_OBJECT::userWithAuth		    // ObjectAttributes
        | TpmCpp::TPMA_OBJECT::restricted           //
        | TpmCpp::TPMA_OBJECT::noDA                 //
        | TpmCpp::TPMA_OBJECT::decrypt,			    //

        {},	// authPolicy (no policy)
        TpmCpp::TPMS_RSA_PARMS(Aes128Cfb, TpmCpp::TPMS_NULL_ASYM_SCHEME(), 2048, 0),	// parameters
        TpmCpp::TPM2B_PUBLIC_KEY_RSA());	// unique
}

TpmCpp::TPMT_PUBLIC Templates::getLDevidRsaTemplate() {
	return TpmCpp::TPMT_PUBLIC(
		TpmCpp::TPM_ALG_ID::SHA256,	// nameAlg

        TpmCpp::TPMA_OBJECT::fixedTPM               //
        | TpmCpp::TPMA_OBJECT::fixedParent          //
        | TpmCpp::TPMA_OBJECT::sensitiveDataOrigin  //
		| TpmCpp::TPMA_OBJECT::userWithAuth		    // ObjectAttributes
		| TpmCpp::TPMA_OBJECT::sign,			    //

		{},	// authPolicy (no policy)
		TpmCpp::TPMS_RSA_PARMS({}, TpmCpp::TPMS_SCHEME_RSASSA(TpmCpp::TPM_ALG_ID::SHA256), 2048, 0),	// parameters
		TpmCpp::TPM2B_PUBLIC_KEY_RSA());	// unique
}