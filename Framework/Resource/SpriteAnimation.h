#pragma once
#include "IResource.h"

enum class AnimationRepeatType : uint
{
	Once, Loop
};

struct SpriteKeyframe
{
	Texture2D* Texture;
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Size;
	float Time;
};

class SpriteAnimation : public IResource
{
public:
	SpriteAnimation(class Context* context);
	virtual ~SpriteAnimation();

	const AnimationRepeatType& GetRepeatType() const { return repeatType; }
	const SpriteKeyframe& GetKeyframeFromIndex(const uint& index);
	const uint GetKeyframesSize() const { return keyframes.size(); }

	void SetName(const string& name) { this->name = name; }
	void SetRepeatType(const AnimationRepeatType& type) { this->repeatType = type; }
	
	void AddKeyframe(const SpriteKeyframe& keyframe);

	void Write(Xml::XMLDocument& doc) override;
	void Read(Xml::XMLElement* element) override;

private:
	class Context* context;
	AnimationRepeatType repeatType;
	vector<SpriteKeyframe> keyframes;
};