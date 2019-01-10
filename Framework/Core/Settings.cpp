#include "stdafx.h"
#include "Settings.h"

//�Լ� ���ο������� �޸��Ҵ��� ��ü�� �����ɶ�(��Ÿ�Ӵܰ迡��) �Ҵ�Ǳ⶧����
//������������ �̸� �Ҵ�������Ѵ�
Settings* Settings::instance = nullptr;

Settings * Settings::Get()
{
	if (!instance)
		instance = new Settings();

	return instance;
}

void Settings::Delete()
{
	SAFE_DELETE(instance);
}

//�̴ϼȶ����� -> ��ü�� ������ ���ÿ� �ʱ�ȭ�� �Ͼ
//�����ڴ� ������ �̴ϼȶ������ �ʱ�ȭ �ؾ��Ѵ�

//* -> �����ʹ� ������ �س��� �������
//& -> ������ �����ϴ� ���̱⶧���� ������ ���ÿ� �Ҵ��� �Ͼ����
Settings::Settings()
	: appName(L"")
	, hInstance(nullptr)
	, handle(nullptr)
	, width(0)
	, height(0)
	, bVsync(true)
	, bFullScreen(false)
{
}
