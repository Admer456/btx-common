// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	class IMaterial;

	namespace Data
	{
		// This is absolutely not optimised and probably won't be
		// The render frontend can optimise this in its own vertex layouts
		struct Vertex
		{
			Vec3 position{};
			Vec3 normal{};
			Vec3 tangent{};
			Vec3 bitangent{};
			Vec4 uv{};
			Vec4 colour[2]{};

			int boneIndices[4]{};
			float boneWeights[4]{};
		};

		inline Vertex VertexPos( Vec3 position )
		{
			Vertex v;
			v.position = position;
			return v;
		}

		inline Vertex VertexPosUv( Vec3 position, Vec2 uv )
		{
			Vertex v;
			v.position = position;
			v.uv = Vec4( uv );
			return v;
		}

		constexpr size_t VertexSize = sizeof( Vertex );
		constexpr size_t VertexAlignment = alignof( Vertex );
		
		struct Face
		{
			Vector<Vertex> vertexData{};
			Vector<uint32_t> vertexIndices{};
			IMaterial* material{ nullptr };

			enum FaceFlags
			{
				HasPosition,
				HasNormal,
				HasTangentAndBitangent,
				HasUv1,
				HasUv2,
				HasColour1,
				HasColour2,
				HasBones
			};

			uint32_t faceFlags{ 0 };
		};

		struct Mesh
		{
			String name{};
			Dictionary metadata{};
			Vector<Face> faces{};
		};

		struct Model
		{
			String name{};
			Dictionary metadata{};
			Vector<Mesh> meshes{};
		};
	}

	struct ModelDesc final
	{
		// Raw model data
		Data::Model modelData{};
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
		virtual const Data::Model& GetModelData() const = 0;

		virtual ModelDesc& GetDesc() = 0;
		virtual const ModelDesc& GetDesc() const = 0;
	};
}
