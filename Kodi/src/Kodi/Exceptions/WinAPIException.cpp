#include "pch.h"
#include "WinAPIException.h"

WinAPIException::WinAPIException(int line, const char* file, HRESULT hr)
    : KodiException(line, file), m_hr(hr)
{

}

const char* WinAPIException::what() const
{
    std::ostringstream oss;
    oss << GetType() << '\n'
        << "[Error Code] " << GetErrorCode() << '\n'
        << "[Description] " << GetErrorString() << '\n'
        << GetOriginString();

    m_WhatBuffer = oss.str();
    return m_WhatBuffer.c_str();
}

std::string WinAPIException::TranslateErrorCode(HRESULT hr) const
{
    char* pMsgBuf = nullptr;
    DWORD nMsgLen = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&pMsgBuf, 0, nullptr);

    if (nMsgLen == 0)
        return "Unidentified error code";

    std::string errorString = pMsgBuf;
    LocalFree(pMsgBuf);
    return errorString;
}


