#pragma once

//Static Class
class Path
{
public:
	//파일 경로에서 파일 이름찾기
	static const string GetFileNameFromFilePath(const string& path);
	
	//파일 경로에서 온전한 파일 이름 찾기
	static const string GetIntactFileNameFromFilePath(const string& path);
	
	//파일 경로에서 디렉토리 경로 찾기
	static const string GetDirectoryFromFilePath(const string& path);
	
	//파일 경로에서 확장자 찾기
	static const string GetExtensionFromFilePath(const string& path);

	//소문자를 대문자로
	static const string ToUpper(const string& lower);

	//대문자를 소문자로
	static const string ToLower(const string& upper);
	
	//wstring을 string 으로
	static const string ToString(const wstring& value);

	//string을 wstring 으로
	static const wstring ToWstring(const string& value);
};