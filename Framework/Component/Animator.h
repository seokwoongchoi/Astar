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
		Play,//애니메이션 동작
		Stop,//중지
		Pause//일시정지
	};

private:
	class Context* context;
	class ResourceManager* resourceManager;
	class Timer* timer;
	class ConstantBuffer* cbuffer;

	AnimationMode mode;
	uint curClipNum;
	float frameTimer;

	SpriteAnimation* curAnimation; //현재 내가 선택한 애니메이션
	map<string, SpriteAnimation*> animationTable; //애니메이터가 컨트롤 할 수 있는 모든 애니메이션들
};