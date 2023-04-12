#include "AssTest.h"
#include "../Bindable/BindableBase.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>> AssTest::staticBinds;
std::optional<UINT> AssTest::indexCount;

AssTest::AssTest(float scale)
	:
	scale(scale)
{}

DirectX::XMMATRIX AssTest::GetTransformXM() const noexcept
{
	return  DirectX::XMMatrixTranslation(0, -2, 4);
}

void AssTest::Update(float dt) noexcept
{
	angle += dt;
}

void AssTest::CreateStaticBinds(Graphics& gfx)
{
	if (staticBinds.contains(&gfx))
	{
		return;
	}
	staticBinds.emplace(&gfx, std::vector<std::unique_ptr<Bindable>>());
	std::vector<std::unique_ptr<Bindable>>& gfxStaticBinds = staticBinds.at(&gfx);
	// position, normal, texcoord
	struct Vertex
	{
		dx::XMFLOAT3 pos;
		dx::XMFLOAT3 n;
	};

	Assimp::Importer imp;
	const auto pModel = imp.ReadFile("models\\sketchfab_teapot.blend",
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);
	const auto pMesh = pModel->mMeshes[0];

	std::vector<Vertex> vertices;
	vertices.reserve(pMesh->mNumVertices);

	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		vertices.push_back({
			{ pMesh->mVertices[i].x,pMesh->mVertices[i].y,pMesh->mVertices[i].z},
			*reinterpret_cast<dx::XMFLOAT3*>(&pMesh->mNormals[i])
			});
	}
	std::vector<unsigned short> indices;
	indexCount = pMesh->mNumFaces * 3;
	indices.reserve(*indexCount);

	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		const auto& face = pMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	gfxStaticBinds.emplace_back(std::make_unique<VertexBuffer<Vertex>>(gfx, vertices));
	gfxStaticBinds.emplace_back(std::make_unique<IndexBuffer>(gfx, indices));

	ShaderBytecode vertexShaderBytecode(L"Shaders/PhongVS.cso");
	gfxStaticBinds.emplace_back(std::make_unique<VertexShader>(gfx, vertexShaderBytecode));
	ShaderBytecode pixelShaderBytecode(L"Shaders/PhongPS.cso");
	gfxStaticBinds.emplace_back(std::make_unique<PixelShader>(gfx, pixelShaderBytecode));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	gfxStaticBinds.emplace_back(std::make_unique<InputLayout>(gfx, ied, vertexShaderBytecode.Get()));

	gfxStaticBinds.emplace_back(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	struct PSMaterialConstant
	{
		DirectX::XMFLOAT3 color;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[3];
	} pmc;
	pmc.color = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	gfxStaticBinds.emplace_back(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, pmc, 1u));
}

std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>>& AssTest::GetStaticBinds() noexcept
{
	return staticBinds;
}

UINT AssTest::GetIndexCount() const noexcept
{
	assert(indexCount.has_value());
	return *indexCount;
}

void AssTest::CreateBinds(Graphics& gfx)
{
	if (binds.contains(&gfx))
	{
		return;
	}
	binds.emplace(&gfx, std::vector<std::unique_ptr<Bindable>>());
	std::vector<std::unique_ptr<Bindable>>& gfxBinds = binds.at(&gfx);
	gfxBinds.emplace_back(std::make_unique<TransformCbuf>(gfx, *this));
}
