// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Assets
{
	namespace RenderData
	{
		class ModelBuilder final
		{
		public:
			// AddSegment must be called first to define the vertex layout, before you call any of the AddXyz methods
			void AddSegment( VertexAttributeType attribute, VertexAttributeDataType dataType );
			void ClearSegments();
			// Validates the model for any inconsistencies in the vertex
			// layout and the number of vertices per each segment
			bool Validate() const;
			// If validation fails, the returned vertex data will be empty
			VertexData Build() const;

			void AddPosition( Vec3 position );
			void AddNormal( Vec3 normal );
			void AddTangentPair( Vec4 tangentAndBitangent );
			void AddUv( Vec2 uv, int channel = 0 );
			void AddColour( Vec4 colour, int channel = 0 );
			void AddBones( Vec4 weights, uint8_t boneId1, uint8_t boneId2, uint8_t boneId3, uint8_t boneId4 );
			void AddData( Vec2 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalise = false );
			void AddData( Vec3 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalise = false );
			void AddData( Vec4 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalise = false );
			void ClearData();

			void AddTriangle( uint32_t a, uint32_t b, uint32_t c );

		private:
			Map<VertexAttributeType, VertexDataSegment> segments;
			Vector<uint32_t> vertexIndices;
		};
	}
}
