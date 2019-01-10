#pragma once
#include "stdafx.h"

//�߻� Ŭ����
//����ý����� �Ѱ����ƴ϶� ��������
//�������� ����ý��۵��� �ϳ��� �ڷ������� �������ؼ� ���
class ISubsystem
{
public:
	ISubsystem(class Context* context) : context(context) {}
	virtual ~ISubsystem() {}

	virtual void Initialize() = 0;
	virtual void Update() = 0;

protected:
	friend class Context;
	class Context* context;
};