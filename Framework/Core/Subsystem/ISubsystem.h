#pragma once
#include "stdafx.h"

//추상 클래스
//서브시스템이 한개가아니라 여러개임
//여러개의 서브시스템들을 하나의 자료형으로 묶기위해서 사용
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