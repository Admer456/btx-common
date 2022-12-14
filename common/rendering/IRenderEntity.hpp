// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	class IModel;

	struct EntityDesc final
	{
		Mat4	transform{};
		IModel*	model{ nullptr };

		// bones must point to valid memory, otherwise null
		// if you won't be using any animations
		uint8_t	numBones{ 0 };
		Mat4*	bones{ nullptr };

		uint32_t renderMask{ RenderMaskDefault };
		Vec4	shaderParameters[2];
	};

	class IEntity
	{
	public:
		virtual EntityDesc& GetDesc() = 0;
		virtual const EntityDesc& GetDesc() const = 0;
	};
}
