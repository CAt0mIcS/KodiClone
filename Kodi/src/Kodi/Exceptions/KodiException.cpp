#include "pch.h"
#include "KodiException.h"


KodiException::KodiException(int line, const char* file)
    : m_Line(line), m_File(file), m_WhatBuffer("")
{
}

const char* KodiException::what() const
{
    std::ostringstream oss;
    oss << GetType() << '\n'
        << GetOriginString();

    m_WhatBuffer = oss.str();
    return m_WhatBuffer.c_str();
}

std::string KodiException::GetOriginString() const
{
    std::ostringstream oss;
    oss << "[File] " << m_File << '\n'
        << "[Line] " << m_Line;

    return oss.str();
}
