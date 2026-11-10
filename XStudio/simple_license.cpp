#include "simple_license.h"
#include <WinSock2.h>
#include <IPHlpApi.h>
#include <string.h>
#include <ctime>
#include <iomanip>
#include <exception>
#include <sstream>
#include <streambuf>
#include <iterator>
#include "aes256.h"
#include <algorithm>
//#include <QNetworkInterface>

#pragma comment(lib, "IPHLPAPI.lib")

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

const unsigned char PT::LicenseCrypto::gKey[] = "n#If^*:Y8;-xH&<Ozj/Zybq]~@%,JC'o"; // custom

std::ostream & PT::operator<<(std::ostream& os, const License& license)
{
	auto expire_day = std::chrono::system_clock::to_time_t(license.m_expire);
	os << license.m_mac << " " << std::put_time(std::localtime(&expire_day), "%F %T");

	return os;
}

std::vector<std::string> PT::GetLocalMacAddr()
{
	std::vector<std::string> vecMac;

	IP_ADAPTER_INFO pAdapterInfo[32];
	DWORD dwBufLen = sizeof(pAdapterInfo);

	DWORD dwRetVal = GetAdaptersInfo(pAdapterInfo, &dwBufLen);
	if (dwRetVal != ERROR_SUCCESS)
		return vecMac;

	PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
	while (pAdapter)
	{
		BYTE* mac = pAdapter->Address;
		char buf[18];
		snprintf(buf, sizeof(buf), "%02X-%02X-%02X-%02X-%02X-%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		vecMac.emplace_back(buf);
		pAdapter = pAdapter->Next;
	}
	
	return vecMac;
}

std::ostream& PT::operator<<(std::ostream& os, const LicenseCrypto& licCrypto)
{
	aes256_context ctx;
    aes256_init(&ctx, LicenseCrypto::gKey);

	std::ostringstream oss;
	oss << *licCrypto.m_pLic;
	std::string plaintext = oss.str();
	std::vector<unsigned char> ciphertext(16 * (plaintext.size() / 16 + 1), 0);
	std::copy(plaintext.begin(), plaintext.end(), ciphertext.begin());
	for (size_t i = 0; i < ciphertext.size(); i += 16)
		aes256_encrypt_ecb(&ctx, &ciphertext[i]);
	
	for (auto c : ciphertext)
		os << c;

	return os;
}

PT::License::License(const std::string& strMac, int month): m_mac(strMac), m_expire(std::chrono::system_clock::now() + months{ month })
{
}

PT::License::License(const std::string& strMac, std::chrono::system_clock::time_point expire)
    : m_mac(strMac), m_expire(expire)
{
}

PT::License::License(std::istream& is)
{
	std::tm tm = {};
	try {
		is >> m_mac >> std::get_time(&tm, "%Y-%m-%d %T");
		m_expire = std::chrono::system_clock::from_time_t(std::mktime(&tm));
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

std::pair<bool, std::string> PT::License::Check() const
{
	if (m_mac.empty())
		return std::make_pair(false, "The license file cannot be found.");

	std::vector<std::string> vecMac = GetLocalMacAddr();
	if (std::find(vecMac.begin(), vecMac.end(), m_mac) == vecMac.end())
		return std::make_pair(false, "The MAC address does not match.");

	if (std::chrono::system_clock::now() > m_expire)
		return std::make_pair(false, "The license has expired.");

	return std::make_pair(true, "success");
}

std::string PT::License::GetExpDate() const
{
	std::ostringstream oss;
	auto expire_day = std::chrono::system_clock::to_time_t(m_expire);
	oss << std::put_time(std::localtime(&expire_day), "%F %T");
	return oss.str();
}

PT::LicenseCrypto::LicenseCrypto(std::istream& is, int iType)
{
	aes256_context ctx;

    m_iType = iType;
	aes256_init(&ctx, gKey);
    aes256_init(&ctx, LicenseCrypto::gKey);

	try {
		std::vector<unsigned char> ciphertext((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
		for (size_t i = 0; i < ciphertext.size(); i += 16)
			aes256_decrypt_ecb(&ctx, &ciphertext[i]);
		std::string plaintext(ciphertext.begin(), ciphertext.end());
		std::istringstream iss(plaintext);
		m_pLic = std::make_shared<License>(iss);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
