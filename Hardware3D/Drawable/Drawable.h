#pragma once
#include "../Graphics.h"
#include <DirectXMath.h>
#include<optional>
#include<map>
class Bindable;
class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	// pure virtual functions
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	virtual std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>>& GetStaticBinds() noexcept = 0;
	virtual UINT GetIndexCount() const noexcept = 0;
	virtual void CreateBinds(Graphics& gfx)= 0;
	virtual void CreateStaticBinds(Graphics& gfx)= 0;
	virtual void Update(float dt) noexcept = 0;
	void Draw(Graphics& gfx);
	virtual ~Drawable() = default;
protected:
	std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>> binds;
	DirectX::XMMATRIX modelTransform;
	DirectX::XMMATRIX positionTransform;
	DirectX::XMMATRIX cameraTransform;
	// 一个graphics可能有多个camera，graphics只代表绘图表面
	// 
};

