#include "StockCode.h"


const char StockCode::ASCII6[64] = {
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
};

StockCode::StockCode(const char* lpszCode, uint8_t flag) noexcept
{
	int codeSize = (int)strlen(lpszCode);
	this->raw = 0;
	this->byte[6] = (uint8_t)((codeSize - 6) & 0x03) << 6;
	int i, j = 8;
	for (i = 0; i < codeSize; i++)
		this->raw |= (uint64_t)ASCII6[lpszCode[i] & 0x3F] << (j-- * 6);
	this->flag = flag;
}

StockCode::StockCode(const wchar_t* lpszCode, uint8_t flag) noexcept
{
	int codeSize = (int)wcslen(lpszCode);
	this->raw = 0;
	this->byte[6] = (uint8_t)((codeSize - 6) & 0x03) << 6;
	int i, j = 8;
	for (i = 0; i < codeSize; i++)
		this->raw |= (uint64_t)ASCII6[lpszCode[i] & 0x3F] << (j-- * 6);
	this->flag = flag;
}

StockCode::StockCode(uint32_t value) noexcept
{
	this->raw = 0;
	uint8_t ch;
	size_t i, j = 8, k = 5;
	for (i = 0; i < 6; i++) {
		ch = (value >> (k-- * 4)) & 0x0F;
		this->raw |= (uint64_t)(ch + 0x30) << (j-- * 6);
	}
	this->flag = (value >> 24) & 0xFF;
}

size_t StockCode::GetCode(char* lpszCode) const noexcept
{
	size_t codeSize = ((this->byte[6] >> 6) & 0x03) + 6;
	size_t i, j = 8;
	for (i = 0; i < codeSize; i++)
		lpszCode[i] = ASCII6[(this->raw >> (j-- * 6)) & 0x3F];
	return codeSize;
}

StockCode::operator uint32_t() const noexcept
{
	if (this->byte[6] & 0xC0)
		return 0;
	uint32_t ch, result = 0;
	size_t i, j = 8, k = 5;
	for (i = 0; i < 6; i++) {
		ch = (this->raw >> (j-- * 6)) & 0x3F;
		result |= ((ch - 0x30) & 0x0F) << (k-- * 4);
	}
	result |= this->flag << 24;
	return result;
}

bool StockCode::operator==(const char* lpszCode) const noexcept
{
	char szTemp[10] = { 0 };
	size_t len = this->GetCode(szTemp);
	return !strcmp(szTemp, lpszCode);
}

bool StockCode::operator==(const wchar_t* lpszCode) const noexcept
{
	char szTemp[10] = { 0 };
	size_t len = this->GetCode(szTemp);
	if (len != wcslen(lpszCode))
		return false;
	for (size_t i = 0; i < len; i++)
		if (szTemp[i] != (char)lpszCode[i])
			return false;
	return true;
}

char StockCode::operator [](int index) const noexcept
{
	size_t codeSize = ((this->byte[6] >> 6) & 0x03) + 6;
	if (index < 0 || index >= (int)codeSize)
		return (char)-1;
	return ASCII6[(this->raw >> ((8 - index) * 6)) & 0x3F];
}

std::string StockCode::getCodeStr() const noexcept
{
	char szTemp[10];
	size_t codeSize = ((this->byte[6] >> 6) & 0x03) + 6;
	size_t i, j = 8;
	for (i = 0; i < codeSize; i++)
		szTemp[i] = ASCII6[(this->raw >> (j-- * 6)) & 0x3F];
	szTemp[i] = '\0';
	return szTemp;
}

std::wstring StockCode::getCodeWStr() const noexcept
{
	wchar_t szTemp[10];
	size_t codeSize = ((this->byte[6] >> 6) & 0x03) + 6;
	size_t i, j = 8;
	for (i = 0; i < codeSize; i++)
		szTemp[i] = ASCII6[(this->raw >> (j-- * 6)) & 0x3F];
	szTemp[i] = '\0';
	return szTemp;
}
