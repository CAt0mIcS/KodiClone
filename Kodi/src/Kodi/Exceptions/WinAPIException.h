#pragma once

#include "KodiException.h"


class WinAPIException : public KodiException
{
public:
	WinAPIException(int line, const char* file, HRESULT hr);

	virtual const char* what() const override;
	virtual const char* GetType() const override { return "WinAPI Exception"; }

	std::string TranslateErrorCode(HRESULT hr) const;

	std::string GetErrorString() const { return TranslateErrorCode(m_hr); }
	HRESULT GetErrorCode() const { return m_hr; }

private:
	HRESULT m_hr;
};


#define KODI_THROW_WINAPI_EXCEPTION(hr)		throw WinAPIException(__LINE__, __FILE__, hr)
#define KODI_THROW_LAST_WINAPI_EXCEPTION()	throw WinAPIException(__LINE__, __FILE__, GetLastError())
