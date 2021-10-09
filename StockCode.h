#pragma once

#include <string>


class StockCode
{
public:
	union {
		uint64_t	raw;
		struct {
			uint8_t	byte[7];
			uint8_t	flag;
		};
	};

	StockCode() noexcept : raw(0) {}
	StockCode(const char* lpszCode, uint8_t flag) noexcept;
	StockCode(const wchar_t* lpszCode, uint8_t flag) noexcept;
	StockCode(uint32_t value) noexcept;
	StockCode(const StockCode& rhs) noexcept { this->raw = rhs.raw; }

	inline operator uint64_t() const noexcept { return this->raw; }
	inline uint64_t operator=(uint64_t value) noexcept { this->raw = value; return this->raw; }
	operator uint32_t() const noexcept;
	bool operator ==(const char* lpszCode) const noexcept;
	bool operator ==(const wchar_t* lpszCode) const noexcept;
	char operator [](int index) const noexcept;

	__declspec(property(get = getCodeStr))	std::string code;
	__declspec(property(get = getCodeWStr))	std::wstring wcode;
	__declspec(property(get = getLength))	int length;
	std::string getCodeStr() const noexcept;
	std::wstring getCodeWStr() const noexcept;
	inline int getLength() const noexcept { return ((this->byte[6] >> 6) & 0x03) + 6; }

protected:
	size_t GetCode(char* lpszCode) const noexcept;

private:
	static const char ASCII6[64];
};
