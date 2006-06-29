#include "stdafx.h"

#include "TextOptions.h"

namespace AppLogic
{
	TextOptions::TextOptions()
	{
		setAlphabet();
	}
	TextOptions::~TextOptions()
	{

	}
	void TextOptions::setAlphabet()
	{
		m_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	std::string TextOptions::getAlphabet()
	{
		return m_alphabet;
	}

	ManTextOptions::ManTextOptions()
	{
		mTextOptions = new TextOptions();
	}
	ManTextOptions::~ManTextOptions()
	{
		delete mTextOptions;
		mTextOptions = NULL;
	}
	String^ ManTextOptions::getAlphabet()
	{
		String^ tempStr = gcnew String(mTextOptions->getAlphabet().c_str());
		return tempStr;
	}
}