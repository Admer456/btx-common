// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

// The data representation of a 3D model
// Different from Render::IModel which is a renderer representation

namespace Assets
{
	class IMaterial;
	
	struct ModelDesc final
	{
		// Raw model data
		RenderData::Model modelData{};
		// If modelPath is set, the model will be loaded from a file
		// Currently unsupported until we get asset loader plugins
		Path modelPath{};
		// If modelPath is set, should this model be streamed in,
		// instead of the engine waiting for it to load?
		// Currently unsupported until JobSystem is here
		bool shouldStream{ false };
	};

	class IModel
	{
	public:
		virtual StringView GetName() const = 0;
		virtual const RenderData::Model& GetModelData() const = 0;

		virtual ModelDesc& GetDesc() = 0;
		virtual const ModelDesc& GetDesc() const = 0;
	};
}
