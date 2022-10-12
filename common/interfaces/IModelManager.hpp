// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	struct ModelDesc;
	class IModel;
}

class IModelManager
{
public:
	virtual bool				Init() = 0;
	virtual void				Shutdown() = 0;

	virtual Render::IModel* 	CreateModel( const Render::ModelDesc& desc ) = 0;
	virtual bool				UpdateModel( Render::IModel* model, const Render::ModelDesc& desc ) = 0;
	virtual void				DestroyModel( Render::IModel* model ) = 0;

	virtual size_t				GetNumModels() const = 0;
	virtual Render::IModel*		GetModel( uint32_t index ) const = 0;
};
