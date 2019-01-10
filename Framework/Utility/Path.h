#pragma once

//Static Class
class Path
{
public:
	//���� ��ο��� ���� �̸�ã��
	static const string GetFileNameFromFilePath(const string& path);
	
	//���� ��ο��� ������ ���� �̸� ã��
	static const string GetIntactFileNameFromFilePath(const string& path);
	
	//���� ��ο��� ���丮 ��� ã��
	static const string GetDirectoryFromFilePath(const string& path);
	
	//���� ��ο��� Ȯ���� ã��
	static const string GetExtensionFromFilePath(const string& path);

	//�ҹ��ڸ� �빮�ڷ�
	static const string ToUpper(const string& lower);

	//�빮�ڸ� �ҹ��ڷ�
	static const string ToLower(const string& upper);
	
	//wstring�� string ����
	static const string ToString(const wstring& value);

	//string�� wstring ����
	static const wstring ToWstring(const string& value);
};