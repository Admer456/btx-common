
#pragma once

namespace Render
{
	using NvrhiTextureDesc = nvrhi::TextureDesc;
	using TextureFormat = nvrhi::Format;
	using TextureType = nvrhi::TextureDimension;

	// Wrapper of nvrhi::TextureDesc
	struct TextureDesc final
	{
		uint32_t width{ 1 };
		uint32_t height{ 1 };
		uint32_t depth{ 1 };
		uint32_t mipLevels{ 1 };

		TextureFormat format{ TextureFormat::RGBA8_UNORM };
		TextureType type{ TextureType::Texture2D };

		bool isRenderTarget{ false };

		byte* textureData{ nullptr };
	};

	class ITexture
	{
	public:
		virtual TextureDesc& GetDesc() = 0;
		virtual const TextureDesc& GetDesc() const = 0;
	};
}
