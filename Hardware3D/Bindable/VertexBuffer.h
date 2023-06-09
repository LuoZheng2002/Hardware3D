#pragma once
#include "Bindable.h"
template<typename V>
class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
	{
		INFOMAN(gfx);
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer);
		CHECK_GFX_ERROR;
	}
	void Bind(Graphics& gfx)
	{
		const UINT stride = sizeof(V);
		const UINT offset = 0u;
		GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};
