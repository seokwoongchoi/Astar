#include "stdafx.h"
#include "Path.h"

//find() - 주어진 문자열이 존재하는 위치 -> 정방향
//rfind() - 주어진 문자열이 존재하는 위치 -> 역방향
//find_first_of() - 주어진 문자중에 하나라도 걸리는 첫번째 위치
//find_last+of() - 주어진 문자중에 하나라도 걸리는 마지막 위치
//find_first_not_of() - 주어진 문자들이 아닌 문자가 걸리는 첫번째 위치
//find_last_not_of() - 주어진 문자들이 아닌 문자가 걸리는 마지막 위치

const string Path::GetFileNameFromFilePath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png ----> Tree.png
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());

	return fileName;
}

const string Path::GetIntactFileNameFromFilePath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png ----> Tree.png ----> Tree
	auto fileName = GetFileNameFromFilePath(path);
	auto lastIndex = fileName.find_last_of('.');
	auto intactFileName = fileName.substr(0, lastIndex);

	return intactFileName;
}

const string Path::GetDirectoryFromFilePath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png ----> C:\\SGA\\2D\\;
	auto lastIndex = path.find_last_of("\\/");
	auto directory = path.substr(0, lastIndex + 1);

	return directory;
}

const string Path::GetExtensionFromFilePath(const string & path)
{
	//C:\\SGA\\2D\\Tree.png ----> png
	auto lastIndex = path.find_last_of('.');
	if (lastIndex != string::npos)
		return path.substr(lastIndex, path.length());

	return "";
}

const string Path::ToUpper(const string & lower)
{
	string upper = "";
	for (const auto& character : lower)
		upper += toupper(character);

	return upper;
}

const string Path::ToLower(const string & upper)
{
	string lower = "";
	for (const auto& character : upper)
		lower += tolower(character);

	return lower;
}

const string Path::ToString(const wstring & value)
{
	string result = "";
	result.assign(value.begin(), value.end());

	return result;
}

const wstring Path::ToWstring(const string & value)
{
	wstring result = L"";
	result.assign(value.begin(), value.end());

	return result;
}
