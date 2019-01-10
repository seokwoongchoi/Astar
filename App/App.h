#pragma once

class App
{
public:
	App();//������ -> �ʱ�ȭ
	virtual ~App();//�Ҹ��� -> ���ﶧ
	//����� �ɼ��� �ֱ⶧���� �Ҹ��� �տ� virtual ����
	//��ӽÿ� �θ� �Ҹ��ڿ� virtual�� �Ⱥپ� ������ �ڽļҸ��ڰ� ȣ���� �ȵ�

	//�츮 ���α׷��� ���� ����
	virtual WPARAM Run();

	//���������Լ� - ��ü�� ����
	//�ڽ�Ŭ�������� ������ ������ �Ǿ��Ѵ� : �������̵�
	virtual void Initialize() = 0; //�ʱ�ȭ
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0; // ��ó��
	virtual void Destroy() = 0; //����

protected:
	//���� �ý���
	class Window* window; // ������ ����
	class Context* context; // ����ý��� ����
};