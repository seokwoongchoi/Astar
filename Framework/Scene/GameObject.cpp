#include "stdafx.h"
#include "GameObject.h"
#include "../Camera/Camera.h"
#include "../Component/Animator.h"
#include "../Component/Collider.h"

GameObject::GameObject(Context * context, Camera * camera)
	: context(context)
	, camera(camera)
{
	timer = context->GetSubsystem<Timer>();
	input = context->GetSubsystem<Input>();
	auto resourceManager = context->GetSubsystem<ResourceManager>();

	//Create Shader
	shader = resourceManager->LoadFromFile<Shader>("Sprite.hlsl");

	//Create Mesh
	mesh = resourceManager->LoadFromFile<Mesh>("Quad");

	//Create Texture
	texture = resourceManager->LoadFromFile<Texture2D>("Metalslug.png");

	//Create Animator
	animator = new SpriteAnimator(context);
	//animator->RegistAnimation(resourceManager->LoadFromFile<SpriteAnimation>("Metalslug.xml"));
	animator->LoadFromFile("Metalslug.xml");
	
	animator->SetCurrentAnimation("Idle");
	animator->Play();

	//Create World
	transform = new Transform(context);

	//Create Collider
	collider = new Collider(context, transform);
	collider->EventFunc = [this]()
	{
		assert(false);
	};

	// [변수캡쳐](파라미터)->리턴타입 { 함수 구현부 }(넘길 인자)

	// 변수캡쳐 : 현재함수에서 사용할 외부변수
	// = 을 넣으면 해당함수의 모든 변수를 전부 사용한다는 의미
	// & 을 넣으면 모든 변수를 참조형으로 받는다는 의미
	// 비워두면 아무것도 사용하지 않겠다는 의미
	// *전역변수는 캡쳐할 필요없음

	// 파라미터 : 함수에서 받는 인자들
	// 리턴타입 : 리턴타입 지정, void일때는 ->와 함께 생략 가능
	// 함수 구현부 : 함수 몸체
	// 넘길 인자 : 호출하는 함수에 넘겨주는 값들 //Add(10, 20);
}

GameObject::~GameObject()
{
	SAFE_DELETE(collider);
	SAFE_DELETE(transform);
	SAFE_DELETE(animator);
}

void GameObject::Update()
{
	collider->SetCenter(transform->GetWorldPosition());
	collider->SetSize(D3DXVECTOR3(28, 38, 1));

	if (input->KeyDown(VK_1))
		animator->SetCurrentAnimation("Idle");
	else if (input->KeyDown(VK_2))
		animator->SetCurrentAnimation("Walk");

	animator->Update();
}

void GameObject::Render()
{
	shader->BindPipeline();
	mesh->BindPipeline();
	animator->BindPipeline();
	transform->BindPipeline();

	texture->SetPS(0);

	auto graphics = context->GetSubsystem<Graphics>();
	graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
}

bool GameObject::IsContain(const D3DXVECTOR3 & mousePose)
{
	D3DXVECTOR3 mouseWorld = camera->ScreenToWorldPoint(D3DXVECTOR2(mousePose.x, mousePose.y));
	D3DXVECTOR2 size = animator->GetCurrentKeyframe().Size;
	D3DXVECTOR3 position = transform->GetWorldPosition();

	// .........
	// .       .
	// .   .   .
	// .       .
	// .........

	bool bCheck = true;
	bCheck &= position.x - size.x * 0.5f < mouseWorld.x;
	bCheck &= position.x + size.x * 0.5f > mouseWorld.x;
	bCheck &= position.y - size.y * 0.5f < mouseWorld.y;
	bCheck &= position.y + size.y * 0.5f > mouseWorld.y;
	return bCheck;
}
