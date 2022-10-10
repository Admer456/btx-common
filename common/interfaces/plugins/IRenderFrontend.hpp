// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	// These are defined in rendering/IRender*.hpp
	struct BatchDesc;
	struct EntityDesc;
	struct LightDesc;
	struct TextureDesc;
	struct ViewDesc;
	struct VolumeDesc;
	// These are implemented by the render backend
	class IBatch;
	class IEntity;
	class ILight;
	class ITexture;
	class IView;
	class IVolume;
}

class IRenderFrontend : public IPlugin
{
public:
	DeclarePluginInterface( IRenderFrontend );

	// Before PostInit is called, the swapchain is already created by the engine
	virtual bool 						PostInit( Render::IBackend* renderBackend, IWindow* mainWindow ) = 0;
	// Handle window resizing etc.
	virtual void						Update() = 0;
	virtual Render::IBackend*			GetBackend() const = 0;

	virtual void						RenderView( const Render::IView* view ) = 0;

	virtual void						DebugLine( Vec3 start, Vec3 end, Vec3 colour = Vec3( 1.0f ), float life = 0.0f, bool depthTest = true) = 0;
	virtual void						DebugRay( Vec3 start, Vec3 direction, float length = 1.0f, bool withArrowhead = false, Vec3 colour = Vec3( 1.0f ), float life = 0.0f, bool depthTest = true ) = 0;
	virtual void						DebugBox( Vec3 min, Vec3 max, Vec3 colour = Vec3( 1.0f ), float life = 0.0f, bool depthTest = true ) = 0;
	virtual void						DebugCube( Vec3 position, float extents = 1.0f, Vec3 colour = Vec3( 1.0f ), float life = 0.0f, bool depthTest = true ) = 0;
	virtual void						DebugSphere( Vec3 position, float extents = 1.0f, Vec3 colour = Vec3( 1.0f ), float life = 0.0f, bool depthTest = true ) = 0;

	virtual Render::IBatch* 			CreateBatch( const Render::BatchDesc& desc ) = 0;
	virtual bool 						DestroyBatch( Render::IBatch* batch ) = 0;
	virtual const Vector<Render::IBatch*>& GetBatches() const = 0;

	virtual Render::IEntity* 			CreateEntity( const Render::EntityDesc& desc ) = 0;
	virtual bool 						DestroyEntity( Render::IEntity* entity ) = 0;
	virtual const Vector<Render::IEntity*>& GetEntities() const = 0;

	virtual Render::ILight* 			CreateLight( const Render::LightDesc& desc ) = 0;
	virtual bool 						DestroyLight( Render::ILight* light ) = 0;
	virtual const Vector<Render::ILight*>& GetLights() const = 0;

	virtual Render::ITexture*			CreateTexture( const Render::TextureDesc& desc ) = 0;
	virtual bool 						DestroyTexture( Render::ITexture* view ) = 0;
	virtual const Vector<Render::ITexture*>& GetTextures() const = 0;

	virtual Render::IView* 				CreateView( const Render::ViewDesc& desc ) = 0;
	virtual bool 						DestroyView( Render::IView* view ) = 0;
	virtual const Vector<Render::IView*>& GetViews() const = 0;

	virtual Render::IVolume* 			CreateVolume( const Render::VolumeDesc& desc ) = 0;
	virtual bool 						DestroyVolume( Render::IVolume* volume ) = 0;
	virtual const Vector<Render::IVolume*>& GetVolumes() const = 0;
};
