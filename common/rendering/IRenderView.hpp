// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	class IMaterial;
	class ITexture;

	struct HookMoment
	{
		enum Type
		{
			Before,
			After
		};
	};

	using HookFn = void( IBackend* renderBackend );

	struct ViewDesc final
	{
		Mat4 viewMatrix{};
		Mat4 projectionMatrix{};
		Vec2 viewportSize{};
		Vec4 clearColour{};

		// Render hooks allow you to render your own stuff on top, e.g. a GUI
		// hook is called when the current render view is being drawn, when exactly
		// depends on hookMoment
		HookMoment::Type moment{ HookMoment::After };
		std::function<HookFn> hook{ nullptr };
		// Post-process material to apply when rendering this view
		// Todo: maybe a separate subsystem for post-processing stacks?
		IMaterial* postProcessMaterial{ nullptr };
		// The render mask of this view
		// Objects will render if (view->renderMask & renderObject->renderMask)
		uint32_t renderMask{ RenderMaskDefault };
	};

	class IView
	{
	public:
		virtual nvrhi::IFramebuffer* GetFramebuffer() const = 0;
		virtual nvrhi::ITexture* GetColourTexture() const = 0;
		virtual nvrhi::ITexture* GetDepthTexture() const = 0;
		// When presenting the frame, this binding set is used to tell the GPU
		// to use this view's colour & depth textures
		virtual nvrhi::IBindingSet* GetBindingSet() const = 0;

		virtual ViewDesc& GetDesc() = 0;
		virtual const ViewDesc& GetDesc() const = 0;
	};
}
