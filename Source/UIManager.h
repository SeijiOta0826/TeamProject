#pragma once

#include <vector>

class UI;
/* memo : 
* UIを管理するクラス
*/
class UIManager
{
public:
	UIManager() = default;
	~UIManager() = default;

	// void Update();
	void Draw();

	template<class T, class...Args>
	T* CreateUI(Args&&... args)
	{
		static_assert(
			std::is_base_of_v<UI, T>,
			"T must derive from GameObject"
			);

		auto ui = new T(std::forward<Args>(args)...);
		ui->Initialize(this);

		mUIs.push_back(ui);

		return ui;
	}

	template<class T>
	T* FindUI()
	{
		for (auto& ui : mUIs)
		{
			if (auto ptr = dynamic_cast<T*>(ui)) 
			{
				return ptr;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> FindObjects() {
		static_assert(
			std::is_base_of_v<UI, T>,
			"T must derive from GameObject"
			);

		std::vector<T*> result;

		for (auto& ui : mUIs) {
			if (auto ptr = dynamic_cast<T*>(ui)) {
				result.push_back(ptr);
			}
		}

		return result;
	}

	void Clear();

private:
	std::vector<UI*> mUIs;
};