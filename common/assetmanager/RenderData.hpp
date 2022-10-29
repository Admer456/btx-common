// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Assets
{
	class IMaterial;

	namespace RenderData
	{
		// Comments for datatypes here are my personal recommendations for what they
		// could, and potentially should be. If you need extra precision, you can always
		// use larger types.
		enum class VertexAttributeType
		{
			// XYZ
			// float[3]
			Position,
			// XYZ
			// int8[4]; 4 because there's no XYZ uint8 format in NVRHI
			Normal,
			// XYZ -> tangent; W -> sign of the bitangent
			// int8[4]
			TangentAndBitangent,
			// XY
			// float[2]
			Uv1,
			Uv2,
			Uv3,
			Uv4,
			// RGBA
			// uint8[4]
			Colour1,
			Colour2,
			Colour3,
			Colour4,
			// XYZW
			// uint8[4]
			BoneWeights,
			// IJKL
			// uint8[4]
			BoneIndices
		};

		enum class VertexAttributeDataType
		{
			Float,
			Uint32,
			Int32,
			Uint16,
			Int16,
			Uint8,
			Int8
		};

		// Look at ModelUtilities.hpp to see how to actually add data here
		struct VertexDataSegment
		{
			size_t GetNumVertices() const;

			VertexAttributeType type{ VertexAttributeType::Position };
			VertexAttributeDataType dataType{ VertexAttributeDataType::Float };
			Vector<byte> rawData;
		};

		struct VertexData
		{
			Vector<VertexDataSegment> vertexData;
			Vector<uint32_t> vertexIndices;
		};

		struct Face
		{
			VertexData data;
			IMaterial* material{ nullptr };
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
}
