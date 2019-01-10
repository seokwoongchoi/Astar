#pragma once

class SpriteAnimator
{
public:
	SpriteAnimator(class Context* context);
	virtual ~SpriteAnimator();

	SpriteAnimation* GetCurrentAnimation() { return curAnimation; }
	const SpriteKeyframe& GetCurrentKeyframe();

	const bool GetIsPlaying() { return mode == AnimationMode::Play ? true : false; }
	const bool GetIsPause() { return mode == AnimationMode::Pause ? true : false; }
	const bool GetIsStop() { return mode == AnimationMode::Stop ? true : false; }

	void SetCurrentAnimation(const string& animationName);
	void SetCurrentAnimation(const uint& index);

	void RegistAnimation(const string& filePath);
	void RegistAnimation(SpriteAnimation* animation);

	void Play();
	void Stop();
	void Pause();

	void Update();
	void BindPipeline();

	void SaveToFile(const string& saveFilePath);
	void LoadFromFile(const string& loadFilePath);

private:
	enum class AnimationMode : uint
	{
		Play,//�ִϸ��̼� ����
		Stop,//����
		Pause//�Ͻ�����
	};

private:
	class Context* context;
	class ResourceManager* resourceManager;
	class Timer* timer;
	class ConstantBuffer* cbuffer;

	AnimationMode mode;
	uint curClipNum;
	float frameTimer;

	SpriteAnimation* curAnimation; //���� ���� ������ �ִϸ��̼�
	map<string, SpriteAnimation*> animationTable; //�ִϸ����Ͱ� ��Ʈ�� �� �� �ִ� ��� �ִϸ��̼ǵ�
};