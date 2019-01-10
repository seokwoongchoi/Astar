#pragma once
#include "stdafx.h"
#include "./Subsystem/ISubsystem.h"

//����ý��۵��� ����
//-���
//-���
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

	//����ý��� ���
	void RegistSubsystem(class ISubsystem* subsystem)
	{
		if (!subsystem)
			assert(false);

		subsystem->Initialize();
		subsystems.push_back(subsystem);
	}

	//����ý��� �뿩
	//�Լ����ø�
	// - ��������� ���ǰ� ����
	// - �������� ����Ǿ����(Ŭ���� ���ø��� ���)
	template<typename T>
	T* GetSubsystem();

private:
	//�����迭
	//uint count = 100;
	//int array[count]; �̰� �ȵ�
	vector<class ISubsystem*> subsystems;
};

//inline �Լ� - �Լ��� �����س��� ���
template<typename T>
inline T * Context::GetSubsystem()
{
	for (auto subsystem : subsystems)
	{
		//typeid : �ڷ����� ������ ����
		//typeid(T).name() -> class Mouse
		if (typeid(T) == typeid(*subsystem)/*�ڽ��� �̸��� ������*/)
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
