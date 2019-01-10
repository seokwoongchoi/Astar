#pragma once
#include "stdafx.h"
#include "./Subsystem/ISubsystem.h"

//서브시스템들을 관리
//-등록
//-출력
class Context
{
public:
	Context() {}
	virtual ~Context()
	{
		//for(uint i =0; i <subsystems.size(); i++)
		for (auto subsystem : subsystems)
			SAFE_DELETE(subsystem);
	}

	void UpdateSubsystems()
	{
		for (auto subsystem : subsystems)
			subsystem->Update();
	}

	//서브시스템 등록
	void RegistSubsystem(class ISubsystem* subsystem)
	{
		if (!subsystem)
			assert(false);

		subsystem->Initialize();
		subsystems.push_back(subsystem);
	}

	//서브시스템 대여
	//함수템플릿
	// - 헤더에서만 정의가 가능
	// - 전역에서 선언되어야함(클래스 템플릿일 경우)
	template<typename T>
	T* GetSubsystem();

private:
	//동적배열
	//uint count = 100;
	//int array[count]; 이거 안됨
	vector<class ISubsystem*> subsystems;
};

//inline 함수 - 함수를 복사해놓고 사용
template<typename T>
inline T * Context::GetSubsystem()
{
	for (auto subsystem : subsystems)
	{
		//typeid : 자료형의 정보가 나옴
		//typeid(T).name() -> class Mouse
		if (typeid(T) == typeid(*subsystem)/*자식의 이름을 꺼내옴*/)
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
