#pragma once

#include <vector>
#include"Object2D.h"

class ObjectManager
{
public:
	
	ObjectManager() = default;
	~ObjectManager() = default;

	void Update(float _deltaTime);
	void Draw();

	template <class T, class...Args>
	T* CreateObject(Args&&... args) {
		static_assert(
			std::is_base_of_v<Object2D, T>,
			"T must derive from GameObject"
			);

		auto obj = new T(std::forward<Args>(args)...);

		// obj->Initialize(this);

		mObjects.push_back(obj);

		return obj;
	}

	template<class T>
	T* FindObject() {
		for (auto& object : mObjects) {
			if (auto ptr = dynamic_cast<T*>(object)) {
				return ptr;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> FindObjects() {
		static_assert(
			std::is_base_of_v<Object2D, T>,
			"T must derive from GameObject"
			);

		std::vector<T*> result;

		for (auto& object : mObjects) {
			if (auto ptr = dynamic_cast<T*>(object)) {
				result.push_back(ptr);
			}
		}

		return result;
	}
	
	void Clear();	// 全てのObjectを解放する(シーン終了時など)

private:
	void RemoveDestroyObjects();

private:
	std::vector<Object2D*> mObjects;	// Objのリスト
};


