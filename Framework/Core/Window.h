#pragma once

class Window
{
public:
	//함수포인터
	static function<void(const uint&, const uint&)> OnResize;

public:
	Window();
	virtual ~Window();
	void Initialize();
};