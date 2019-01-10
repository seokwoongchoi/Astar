#pragma once

//���������� �� Singleton Pattern ���
// - ���������� ����� ���ִ�
// - �ν��Ͻ�(��ü) �ϳ��� �����ϵ��� �����Ѵ�

//C++ -> OOP(Object Oriented Programming) : ��ü�������α׷���
// - ĸ��ȭ : �����͸� ������ִ�(private - ����, protected - ���� �ڽ��̶�, public - �츮���)
// - �߻�ȭ : ���������Լ�
// - ������ : �����ε� -> �ߺ�����, �������̵� -> ������ // �߻�Ŭ������ ��ӹ޾�����
// - ��� : 

// ��ȯ�� �Լ��̸�(�Ű�����)
class Settings
{
public:
	//�Լ� �տ� staitc Ű���尡 ������ �������� ����� �� �ִٴ� ��
	//�׷��� private Ű���� �ȿ������� �������� ��������
	static Settings* Get();
	static void Delete();

public:
	//Gatter Function
	//private ������ �ٷ� ������ ���ϴϱ� 
	const wstring& GetAppName() const { return appName; }
	HINSTANCE GetWindowInstance() const { return hInstance; }
	HWND GetWindowHandle() const { return handle; }
	const float& GetWidth() const { return width; }
	const float& GetHeight() const { return height; }
	const bool& GetIsVsync() const { return bVsync; }
	const bool& GetIsFullScreen() const { return bFullScreen; }
	const D3D11_VIEWPORT& GetViewport() const { return viewport; }

	//Setter Function
	void SetAppName(const wstring& appName) { this->appName = appName; }
	void SetWindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }
	void SetWidth(const float& width) { this->width = width; }
	void SetHeight(const float& height) { this->height = height; }
	void SetIsVsync(const bool& bVsync) { this->bVsync = bVsync; }
	void SetIsFullScreen(const bool& bFullScreen) { this->bFullScreen = bFullScreen; }
	void SetViewport(const D3D11_VIEWPORT& viewport) { this->viewport = viewport; }

private:
	//�̱��������� ����ϱ⶧����
	//�ܺο��� ��ü�� ������ �� ������ ����
	Settings();
	virtual ~Settings() {}

private:
	//static �ٴ� ���� : ��������
	//Ŭ���� ���ο������� ��������
	//�������� �̱⶧���� �����ϴܰ迡�� �޸� �Ҵ�
	static Settings* instance;

	//�������
	wstring appName;
	HINSTANCE hInstance;
	HWND handle;
	float width;
	float height;
	bool bVsync;
	bool bFullScreen;

	D3D11_VIEWPORT viewport;
};