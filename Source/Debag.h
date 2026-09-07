#pragma once
#include <DxLib.h>
#include <sstream>
#include <vector>

class Debag
{
public:
	Debag() = default;
	~Debag() = default;

	static void Draw();
	static void Toggle();

	static bool IsEnable();

	template<typename... Args>
	static void Print(Args&&... _args)
	{
		if (!mbEnable)
			return;

		std::ostringstream stream;

		((stream << ... << std::forward<Args>(_args)));

		mTexts.push_back(stream.str());
	}

private:
	static void DrawGrid();
	static void DrawColliders();
	static void DrawGameTime();
	static void DrawTexts();

private:
	static bool mbEnable;

	static std::vector<std::string> mTexts;
};