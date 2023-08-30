#pragma once

#include <Tpm2.h>

class Templates {
public:
	static TpmCpp::TPMT_PUBLIC getEkRsaTemplate();
	static TpmCpp::TPMT_PUBLIC getLakRsaTemplate();
	static TpmCpp::TPMT_PUBLIC getSrkRsaTemplate();
	static TpmCpp::TPMT_PUBLIC getLDevidRsaTemplate();
};