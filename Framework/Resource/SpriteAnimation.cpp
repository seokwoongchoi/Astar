#include "stdafx.h"
#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Context * context)
	: IResource(context)
	, repeatType(AnimationRepeatType::Once)
{
}

SpriteAnimation::~SpriteAnimation()
{
}

const SpriteKeyframe & SpriteAnimation::GetKeyframeFromIndex(const uint & index)
{
	assert(index < keyframes.size());
	return keyframes[index];
}

void SpriteAnimation::AddKeyframe(const SpriteKeyframe & keyframe)
{
	keyframes.push_back(keyframe);
}

void SpriteAnimation::Write(Xml::XMLDocument & doc)
{
	Xml::XMLElement* root = doc.NewElement("SpriteAnimation");
	doc.LinkEndChild(root);

	root->SetAttribute("AnimationName", name.c_str());
	root->SetAttribute("RepeatType", static_cast<uint>(type));

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* firstElem = doc.NewElement("Keyframe");
		root->LinkEndChild(firstElem);

		firstElem->SetAttribute("TextureFilePath", keyframe.Texture->GetFilePath().c_str());
		firstElem->SetAttribute("OffsetX", keyframe.Offset.x);
		firstElem->SetAttribute("OffsetY", keyframe.Offset.y);
		firstElem->SetAttribute("SizeX", keyframe.Size.x);
		firstElem->SetAttribute("SizeY", keyframe.Size.y);
		firstElem->SetAttribute("Time", keyframe.Time);
	}
}

void SpriteAnimation::Read(Xml::XMLElement* element)
{
	name = element->Attribute("AnimationName");
	repeatType = static_cast<AnimationRepeatType>(element->IntAttribute("RepeatType"));

	Xml::XMLElement* firstElem = element->FirstChildElement();
	for (; firstElem != nullptr; firstElem = firstElem->NextSiblingElement())
	{
		SpriteKeyframe keyframe;
		string textureFilePath = firstElem->Attribute("TextureFilePath");

		keyframe.Texture = resourceManager->LoadFromFile<Texture2D>(textureFilePath);
		keyframe.Offset.x = firstElem->FloatAttribute("OffsetX");
		keyframe.Offset.y = firstElem->FloatAttribute("OffsetY");
		keyframe.Size.x = firstElem->FloatAttribute("SizeX");
		keyframe.Size.y = firstElem->FloatAttribute("SizeY");
		keyframe.Time = firstElem->FloatAttribute("Time");

		keyframes.push_back(keyframe);
	}
}