#pragma once

class Window
{
public:
	//�Լ�������
	static function<void(const uint&, const uint&)> OnResize;

public:
	Window();
	virtual ~Window();
	void Initialize();
};