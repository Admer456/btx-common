// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#include "common/Precompiled.hpp"

using namespace Assets::RenderData;

size_t VertexDataSegment::GetNumVertices() const
{
	const size_t numBytes = rawData.size();

	size_t numComponents = 4;
	switch ( type )
	{
	case VertexAttributeType::Position: numComponents = 3; break;
	case VertexAttributeType::Uv1:
	case VertexAttributeType::Uv2:
	case VertexAttributeType::Uv3:
	case VertexAttributeType::Uv4: numComponents = 2; break;
	}

	size_t numBytesPerComponent = 4;
	switch ( dataType )
	{
	case VertexAttributeDataType::Uint16:
	case VertexAttributeDataType::Int16: numBytesPerComponent = 2; break;
	case VertexAttributeDataType::Uint8:
	case VertexAttributeDataType::Int8: numBytesPerComponent = 1; break;
	}

	return numBytes / (numComponents * numBytesPerComponent);
}
