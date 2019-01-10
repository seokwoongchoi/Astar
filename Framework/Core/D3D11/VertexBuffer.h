#pragma once

// \�Լ�()     <====
// \			   \
// \->�Լ� ȣ��  ====
class VertexBuffer
{
public:
	VertexBuffer(class Graphics* graphics);
	virtual ~VertexBuffer();

	ID3D11Buffer* GetBuffer()const { return vbuffer; }

	//���ø� �Լ�
	//������ Ÿ�԰� �����ϰ� ������ ������ �ϴ� �Լ�
	//��������� ���ǰ� ����(inline�Լ�)
	//���ø� Ŭ������ ������ �������� ����Ǿ����(namespace ���Եɼ�����)
	template <typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT/*����Ʈ �Ķ����*/); // ����³�
	void Clear();//���³�

	//���۸� ������Ʈ�ϴ� �Լ�
	void* Map();
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* vbuffer; //���ؽ����� : �������� ������ �����������ο� �ֱ����� ��ȯ��Ų ������
	uint stride;//�����ϳ��� ũ��
	uint offset;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	assert(!vertices.empty()); //���������� �ϳ��������� ���� �ʿ䰡�����ϱ� �ߴ�
	Clear();
	//���࿡ Create�� �Τ���ȣ��� ��� �̹� �Ҵ���ִ� ���¿��� �ٽ� �Ҵ��� �õ��ϱ⶧���� ���� �߻�

	stride = sizeof(T);

	//���� Desc �����
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));

	//���۸� �������۷� ����ٸ� CPU���� ������ �����͸� ������Ʈ����� �ϱ⶧����
	//CPU_ACCESS_WRITE �÷��׸� �Ѽ� CPU�� ���۸� ������Ʈ �� �� �ֵ��� ����
	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(T) * vertices.size();

	//������ ��Ƴ��� ������ �����ŭ ���۸� ü�� �������� �����͸� �����صд�
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();

	//���ؽ����� ����
	HRESULT hr = graphics->GetDevice()->CreateBuffer(&bufferDesc, &subData, &vbuffer);
	assert(SUCCEEDED(hr));
}
