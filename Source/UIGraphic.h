#pragma once
#include <string>

class UI;
class UIGraphic
{
public:
	UIGraphic(UI* _pUI,std::string _graphicFileName);
	~UIGraphic() = default;

	void Draw();

private:
	int mnGraphHandle = -1;

	UI* mpUI;
};