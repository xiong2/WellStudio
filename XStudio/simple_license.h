#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

namespace PT // pezy tools
{

/**
@class PT::License provided in the file "simple_license.h"
@brief The class provides License generation and identification functions.
@author pezy
@date 2017-08-29
@sa
*/
class License {
	using days = std::chrono::duration<int, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;
	using years = std::chrono::duration<int, std::ratio_multiply<std::ratio<146097, 400>, days::period>>;
	using months = std::chrono::duration<int, std::ratio_divide<years::period, std::ratio<12>>>;

	std::string m_mac;
	std::chrono::system_clock::time_point m_expire;
public:
    License(const std::string& strMac, std::chrono::system_clock::time_point expire);
	License(const std::string& strMac, int month);
	License(std::istream& is);
	std::pair<bool, std::string> Check() const;
	std::string GetExpDate() const;
	//! @brief Output License object("MAC date time")
	friend std::ostream& operator<<(std::ostream& os, const License& license);
};

//! @brief Get local Netcard physical address.
std::vector<std::string> GetLocalMacAddr();

/**
@class LicenseCrypto provided in the file "simple_license.h"
@brief The class provides cryptogram for license.
@author pezy
@date 2017-08-29
@sa License AesProxy
*/
class LicenseCrypto {
	std::shared_ptr<License> m_pLic;
    const static unsigned char gKey[];
public:
    LicenseCrypto(const std::shared_ptr<License>& pLic, int iType = 0) : m_pLic(pLic)
    {m_iType = iType;}
    LicenseCrypto(std::istream& is, int iType = 0);
	std::pair<bool, std::string> Check() const { return m_pLic->Check(); }
	std::string GetExpDate() const { return m_pLic->GetExpDate(); }
	//! @brief Output LicenseCrypto object("Passphrase")
	friend std::ostream& operator<<(std::ostream& os, const LicenseCrypto& licCrypto);

    int m_iType = 0;    //  0: ThinMAN;  1: GSM.
};
}
