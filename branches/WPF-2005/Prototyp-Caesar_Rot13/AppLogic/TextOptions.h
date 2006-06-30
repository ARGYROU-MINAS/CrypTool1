//TextOptions.h

#pragma once

#include "stdafx.h"

#using <mscorlib.dll>

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;


namespace AppLogic
{
	class _declspec(dllexport)TextOptions
	{
	private:
		std::string m_alphabet;
	public:
		TextOptions();
		~TextOptions();
		void setAlphabet();
		std::string getAlphabet();
	};

	public ref class ManTextOptions : public IDisposable
	{
	private:
		TextOptions* mTextOptions;
	public:
		ManTextOptions();
		~ManTextOptions();
		String^ getAlphabet();
	};
}