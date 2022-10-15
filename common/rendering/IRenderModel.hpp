// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	class IMaterial;

	class IModel
	{
	public:
		virtual StringView GetName() const = 0;

		virtual size_t GetNumFaces() const = 0;

		virtual IBuffer* GetVertexBuffer( uint32_t face, Assets::RenderData::VertexAttributeType attribute ) const = 0;
		virtual IBuffer* GetIndexBuffer( uint32_t face ) const = 0;

		virtual const Assets::ModelDesc& GetDesc() const = 0;
	};
}
