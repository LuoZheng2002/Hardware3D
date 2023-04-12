#pragma once
#include"../Bindable/ConstantBuffers.h"
#include"Drawable.h"
#include<optional>
class AssTest: public Drawable
{
public:
	AssTest(float scale);
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept override;
	std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>>& GetStaticBinds() noexcept override;
	UINT GetIndexCount() const noexcept override;
	void CreateBinds(Graphics& gfx) override;
	void CreateStaticBinds(Graphics& gfx) override;
	void Update(float dt) noexcept override;
private:
	static std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>> staticBinds;
	static std::optional<UINT> indexCount;
private:
	float scale;
	float angle;
};