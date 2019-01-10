#pragma once

// \함수()     <====
// \			   \
// \->함수 호출  ====
class VertexBuffer
{
public:
	VertexBuffer(class Graphics* graphics);
	virtual ~VertexBuffer();

	ID3D11Buffer* GetBuffer()const { return vbuffer; }

	//템플릿 함수
	//변수의 타입과 무관하게 일정한 동작을 하는 함수
	//헤더에서만 정의가 가능(inline함수)
	//템플릿 클래스는 무조건 전역에서 선언되어야함(namespace 포함될수없음)
	template <typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT/*디폴트 파라미터*/); // 만드는놈
	void Clear();//비우는놈

	//버퍼를 업데이트하는 함수
	void* Map();
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* vbuffer; //버텍스버퍼 : 정점들의 정보를 파이이프라인에 넣기위해 변환시킨 데이터
	uint stride;//정점하나의 크기
	uint offset;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	assert(!vertices.empty()); //정점정보가 하나도없으면 만들 필요가없으니까 중단
	Clear();
	//만약에 Create가 두ㄷ번호출될 경우 이미 할당되있는 상태에서 다시 할당을 시도하기때문에 에러 발생

	stride = sizeof(T);

	//버퍼 Desc 만들기
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	//버퍼를 동적버퍼로 만든다면 CPU에서 버퍼의 데이터를 업데이트해줘야 하기때문에
	//CPU_ACCESS_WRITE 플레그를 켜서 CPU가 버퍼를 업데이트 할 수 있도록 해줌
	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(T) * vertices.size();

	//위에서 잡아놓은 버퍼의 사이즈만큼 버퍼를 체울 데이터의 포인터를 저장해둔다
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();

	//버텍스버퍼 생성
	HRESULT hr = graphics->GetDevice()->CreateBuffer(&bufferDesc, &subData, &vbuffer);
	assert(SUCCEEDED(hr));
}
