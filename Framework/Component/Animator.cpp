#include "stdafx.h"
#include "Animator.h"

SpriteAnimator::SpriteAnimator(Context * context)
	: context(context)
	, mode(AnimationMode::Stop)
	, curClipNum(0)
	, frameTimer(0.0f)
	, curAnimation(nullptr)
{
	timer = context->GetSubsystem<Timer>();
	resourceManager = context->GetSubsystem<ResourceManager>();

	cbuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	cbuffer->Create<SpriteData>();
}

SpriteAnimator::~SpriteAnimator()
{
	SAFE_DELETE(cbuffer);

	//map을 지우는 첫번째 방법
	//map<string, SpriteAnimation*>::iterator iter = animationTable.begin();
	//for (; iter != animationTable.end(); iter++)
	//	SAFE_DELETE(iter->second);

	//map을 지우는 두번째 방법
	//for (auto animation : animationTable)
	//	SAFE_DELETE(animation.second);
}

const SpriteKeyframe & SpriteAnimator::GetCurrentKeyframe()
{
	return curAnimation->GetKeyframeFromIndex(curClipNum);
}

void SpriteAnimator::SetCurrentAnimation(const string & animationName)
{
	assert(animationTable.count(animationName) > 0);
	curClipNum = 0;
	curAnimation = nullptr;
	curAnimation = animationTable[animationName];
}

void SpriteAnimator::SetCurrentAnimation(const uint & index)
{
	uint count = 0;
	for (auto animation : animationTable)
	{
		if (index == count)
		{
			curClipNum = 0;
			curAnimation = animation.second;
			return;
		}
		count++;
	}

	assert(false);
}

void SpriteAnimator::RegistAnimation(const string & filePath)
{
	auto animation
		= resourceManager->LoadFromFile<SpriteAnimation>(filePath);

	RegistAnimation(animation);
}

void SpriteAnimator::RegistAnimation(SpriteAnimation * animation)
{
	assert(animationTable.count(animation->GetResourceName()) < 1);
	animationTable[animation->GetResourceName()] = animation;
}

void SpriteAnimator::Play()
{
	mode = AnimationMode::Play;
	frameTimer = 0.0f;
}

void SpriteAnimator::Stop()
{
	mode = AnimationMode::Stop;
	curClipNum = 0;
}

void SpriteAnimator::Pause()
{
	mode = AnimationMode::Pause;
}

void SpriteAnimator::Update()
{
	bool bCheck = true;
	bCheck &= curAnimation != nullptr;
	bCheck &= mode == AnimationMode::Play;

	if (bCheck)
	{
		frameTimer += timer->GetDeltaTimeMs();

		if (frameTimer > curAnimation->GetKeyframeFromIndex(curClipNum).Time)
		{
			curClipNum++;

			switch (curAnimation->GetRepeatType())
			{
			case AnimationRepeatType::Once:
				if (curClipNum >= curAnimation->GetKeyframesSize())
				{
					curClipNum = curAnimation->GetKeyframesSize() - 1;
					Pause();
				}
				break;

			case AnimationRepeatType::Loop:
				curClipNum %= curAnimation->GetKeyframesSize();
				break;
			}

			frameTimer = 0.0f;
		}
	}
}

void SpriteAnimator::BindPipeline()
{
	if (curAnimation)
	{
		auto data = static_cast<SpriteData*>(cbuffer->Map());
		data->TextureSize = curAnimation->GetKeyframeFromIndex(curClipNum).Texture->GetSize();
		data->SpriteOffset = curAnimation->GetKeyframeFromIndex(curClipNum).Offset;
		data->SpriteSize = curAnimation->GetKeyframeFromIndex(curClipNum).Size;
		cbuffer->Unmap();
		cbuffer->SetVS(2);
	}
}

void SpriteAnimator::SaveToFile(const string & saveFilePath)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	Xml::XMLElement* root = doc.NewElement("Animator");
	doc.LinkEndChild(root);

	for (auto animation : animationTable)
	{
		Xml::XMLElement* firstElem = doc.NewElement("SpriteAnimation");
		root->LinkEndChild(firstElem);

		animation.second->Write(doc);
	}

	doc.SaveFile(saveFilePath.c_str());
}

void SpriteAnimator::LoadFromFile(const string & loadFilePath)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(loadFilePath.c_str());
	assert(error == Xml::XMLError::XML_SUCCESS);
	Xml::XMLElement* root = doc.FirstChildElement();

	Xml::XMLElement* firstElem = root->FirstChildElement();
	for (; firstElem != nullptr; firstElem = firstElem->NextSiblingElement())
	{
		SpriteAnimation* animation = new SpriteAnimation(context);
		animation->Read(firstElem);

		resourceManager->RegistResource(animation);
		RegistAnimation(animation);
	}
}
