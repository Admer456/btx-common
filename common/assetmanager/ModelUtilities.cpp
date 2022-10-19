// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#include "common/Precompiled.hpp"

using namespace Assets::RenderData;

static const Map<VertexAttributeDataType, size_t> VertexAttributeDataTypeSizes =
{
	{ VertexAttributeDataType::Float, 4U },
	{ VertexAttributeDataType::Uint32, 4U },
	{ VertexAttributeDataType::Int32, 4U },
	{ VertexAttributeDataType::Uint16, 2U },
	{ VertexAttributeDataType::Int16, 2U },
	{ VertexAttributeDataType::Uint8, 1U },
	{ VertexAttributeDataType::Int8, 1U }
};

// It is assumed that 'value' is between -1 and +1, or 0 and +1
// For things like tangents and bitangents, we convert this -1 and +1 range to -128 and +127 and so on
template<typename T>
inline static float Normalised( T value, VertexAttributeDataType dataType )
{
	switch ( dataType )
	{
	case VertexAttributeDataType::Uint32:	return value * float( std::numeric_limits<uint32_t>::max() );
	case VertexAttributeDataType::Int32:	return value * float( std::numeric_limits<int32_t>::max() );
	case VertexAttributeDataType::Uint16:	return value * float( std::numeric_limits<uint16_t>::max() );
	case VertexAttributeDataType::Int16:	return value * float( std::numeric_limits<int16_t>::max() );
	case VertexAttributeDataType::Uint8:	return value * float( std::numeric_limits<uint8_t>::max() );
	case VertexAttributeDataType::Int8:		return value * float( std::numeric_limits<int8_t>::max() );
	}

	return value;
}

inline static void AppendData( Vector<byte>& bytes, float value, VertexAttributeDataType dataType, bool normalised = false )
{
	if ( normalised )
	{
		value = Normalised( value, dataType );
	}

	uint32_t valueUint32 = value;
	int32_t valueInt32 = value;
	uint16_t valueUint16 = value;
	int16_t valueInt16 = value;
	uint8_t valueUint8 = value;
	int8_t valueInt8 = value;

	byte* punner = reinterpret_cast<byte*>(&value);
	size_t offset = 4;
	
	switch ( dataType )
	{
	case VertexAttributeDataType::Uint32: punner = reinterpret_cast<byte*>(valueUint32); break;
	case VertexAttributeDataType::Int32: punner = reinterpret_cast<byte*>(valueInt32); break;
	case VertexAttributeDataType::Uint16: punner = reinterpret_cast<byte*>(valueUint16); offset = 2; break;
	case VertexAttributeDataType::Int16: punner = reinterpret_cast<byte*>(valueInt16); offset = 2; break;
	case VertexAttributeDataType::Uint8: punner = reinterpret_cast<byte*>(valueUint8); offset = 0; break;
	case VertexAttributeDataType::Int8: punner = reinterpret_cast<byte*>(valueInt8); offset = 0; break;
	}

	if ( !offset )
	{
		bytes.push_back( *punner );
	}
	else
	{
		bytes.insert( bytes.end(), punner, punner + offset );
	}
}

void ModelBuilder::AddSegment( VertexAttributeType attribute, VertexAttributeDataType dataType )
{
	segments[attribute] = { attribute, dataType };
}

void ModelBuilder::ClearSegments()
{
	segments.clear();
}

bool ModelBuilder::Validate() const
{
	if ( segments.empty() || vertexIndices.empty() )
	{
		return false;
	}

	if ( vertexIndices.size() % 3 )
	{
		return false;
	}

	const size_t numVertices = segments.begin()->second.GetNumVertices();
	if ( numVertices == 0 )
	{
		return false;
	}

	for ( const auto& segment : segments )
	{
		if ( numVertices != segment.second.GetNumVertices() )
		{
			return false;
		}
	}

	return true;
}

VertexData ModelBuilder::Build() const
{
	if ( !Validate() )
	{
		return {};
	}

	VertexData vd;
	vd.vertexIndices = vertexIndices;
	for ( const auto& segment : segments )
	{
		vd.vertexData.push_back( segment.second );
	}

	return vd;
}

void ModelBuilder::AddPosition( Vec3 position )
{
	return AddData( position, VertexAttributeType::Position, VertexAttributeDataType::Float );
}

void ModelBuilder::AddNormal( Vec3 normal )
{
	return AddData( normal, VertexAttributeType::Normal, VertexAttributeDataType::Float );
}

void ModelBuilder::AddTangentPair( Vec4 tangentAndBitangent )
{
	return AddData( tangentAndBitangent, VertexAttributeType::TangentAndBitangent, VertexAttributeDataType::Int8, true );
}

void ModelBuilder::AddUv( Vec2 uv, int channel )
{
	VertexAttributeType channelType = VertexAttributeType::Uv1;
	switch ( channel )
	{
	case 2: channelType = VertexAttributeType::Uv2; break;
	case 3: channelType = VertexAttributeType::Uv3; break;
	case 4: channelType = VertexAttributeType::Uv4; break;
	}

	return AddData( uv, channelType, VertexAttributeDataType::Float );
}

void ModelBuilder::AddColour( Vec4 colour, int channel )
{
	VertexAttributeType channelType = VertexAttributeType::Colour1;
	switch ( channel )
	{
	case 2: channelType = VertexAttributeType::Colour2; break;
	case 3: channelType = VertexAttributeType::Colour3; break;
	case 4: channelType = VertexAttributeType::Colour4; break;
	}

	return AddData( colour, channelType, VertexAttributeDataType::Uint8, true );
}

void ModelBuilder::AddBones( Vec4 weights, uint8_t boneId1, uint8_t boneId2, uint8_t boneId3, uint8_t boneId4 )
{
	AddData( weights, VertexAttributeType::BoneWeights, VertexAttributeDataType::Uint8, true );

	Vec4 boneIds{ float(boneId1), float(boneId2), float(boneId3), float(boneId4) };
	return AddData( boneIds, VertexAttributeType::BoneIndices, VertexAttributeDataType::Uint8 );
}

void ModelBuilder::AddData( Vec2 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalised )
{
	auto& rawData = segments[attribute].rawData;
	AppendData( rawData, v.x, dataType, normalised );
	AppendData( rawData, v.y, dataType, normalised );
}

void ModelBuilder::AddData( Vec3 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalised )
{
	auto& rawData = segments[attribute].rawData;
	AppendData( rawData, v.x, dataType, normalised );
	AppendData( rawData, v.y, dataType, normalised );
	AppendData( rawData, v.z, dataType, normalised );
}

void ModelBuilder::AddData( Vec4 v, VertexAttributeType attribute, VertexAttributeDataType dataType, bool normalised )
{
	auto& rawData = segments[attribute].rawData;
	AppendData( rawData, v.m.x, dataType, normalised );
	AppendData( rawData, v.m.y, dataType, normalised );
	AppendData( rawData, v.m.z, dataType, normalised );
	AppendData( rawData, v.m.w, dataType, normalised );
}

void ModelBuilder::ClearData()
{
	for ( auto& segment : segments )
	{
		segment.second.rawData.clear();
	}
}

void ModelBuilder::AddTriangle( uint32_t a, uint32_t b, uint32_t c )
{
	vertexIndices.insert( vertexIndices.end(), { a, b, c } );
}
