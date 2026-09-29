#pragma once

#include <string>
#include <DxLib.h>

enum class TextAlign
{
	LEFT,
	CENTER,
	RIGHT
};

class UItext
{
public:
	UItext() = default;
	~UItext() = default;

	void SetText(std::string _text) { mText = _text; }
	std::string GetText() { return mText; }

	void SetFontSize(int _size) { mnFontSize = _size; }
	void SetColor(unsigned int _color) { mColor = _color; }

	void SetAlign(TextAlign _align) { mAlign = _align; }
	TextAlign GetAlign() { return mAlign; }

	void Draw();

private:
	std::string mText;

	int mnFontSize = 24;
	unsigned int mColor = GetColor(255, 255, 255);

	TextAlign mAlign = TextAlign::CENTER;
};