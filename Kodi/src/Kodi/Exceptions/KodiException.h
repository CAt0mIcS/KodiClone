#pragma once

#include <exception>


class KodiException : public std::exception
{
public:
	KodiException(int line, const char* file);

	virtual const char* what() const override;
	virtual const char* GetType() const { return "Kodi Exception"; }

	const std::string& GetFile() const { return m_File; }
	int GetLine() const { return m_Line; }

	std::string GetOriginString() const;

protected:
	mutable std::string m_WhatBuffer;
	int m_Line;
	std::string m_File;
};

