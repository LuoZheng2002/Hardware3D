#include "Drawable.h"
#include "../Bindable/IndexBuffer.h"
#include <cassert>

#include<map>


void Drawable::Draw(Graphics& gfx)
{
	// static binds extraction
	std::map<Graphics*, std::vector<std::unique_ptr<Bindable>>>& staticBinds = GetStaticBinds();
	if (!staticBinds.contains(&gfx))
	{
		CreateStaticBinds(gfx);
	}
	assert(staticBinds.contains(&gfx));
	// binds extraction
	if (!binds.contains(&gfx))
	{
		CreateBinds(gfx);
	}
	assert(binds.contains(&gfx));
	std::vector<std::unique_ptr<Bindable>>& gfxStaticBinds = staticBinds.at(&gfx);
	std::vector<std::unique_ptr<Bindable>>& gfxBinds = binds.at(&gfx);
	for (auto& b : gfxBinds)
	{
		b->Bind(gfx);
	}
	for (auto& b : gfxStaticBinds)
	{
		b->Bind(gfx);
	}
	gfx.DrawIndexed(GetIndexCount());
}


