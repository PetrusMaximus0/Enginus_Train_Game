#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID() {
	static ComponentID LastID = 0;
	return LastID++;
}

template <typename T> 
inline ComponentID GetComponentTypeID() noexcept {
	static ComponentID TypeId = GetComponentTypeID();
	return TypeId;

}

constexpr std::size_t MaxComponents = 32;

using ComponentBitSet = std::bitset<MaxComponents>;

using ComponentArray = std::array<Component*, MaxComponents>;

class Component {
public:
	Entity* OwnerEntity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}

};

class Entity {

private:
	bool IsActive{ true };
	std::vector<std::unique_ptr<Component>> Components;
	
	ComponentArray ComponentsArray;
	ComponentBitSet ComponentsBitSet;

public:
	void Update() {
		for (auto& Component : Components) Component->Update();
		for (auto& Component : Components) Component->Draw();
	}
	void Draw() {}
	bool GetIsActive() { return IsActive; }
	void Destroy() { IsActive = false; }

	template <typename T> 
	bool HasComponent() const {
		return ComponentBitSet[ GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs &&... MArgs) {
		T* Create = new T(std::forward<TArgs>(MArgs)...);
		Create->Entity = this;
		std::unique_ptr<Component> uPtr( Create );
		Components.emplace_back(std::move(uPtr));
		ComponentArray[GetComponentTypeID<T>()] = Create;
		ComponentBitSet[GetComponentTypeID<T>()] = true;

		Create->Init();
		return *Create;
	}
	

	template <typename T>
	T& GetComponent() const {
		auto ptr(ComponentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);


	}


};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> Entities;

public:
	void Update() {
		for (auto& Ent : Entities) Ent->Update();
	}
	void Draw() {
		for (auto& Ent : Entities) Ent->Draw();
	}
	void Refresh() {
		Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities),
			[](const std::unique_ptr<Entity> &mEntity) 
			{
				return !mEntity->GetIsActive();

			}),
				std::end(Entities));
	}

	Entity& AddEntity() {
		Entity* Ent = new Entity();
		std::unique_ptr<Entity> uPtr{ Ent };
		Entities.emplace_back(std::move(uPtr));
		return *Ent;

	}

};