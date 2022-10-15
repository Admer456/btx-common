// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Assets
{
	struct ModelDesc;
	class IModel;
}

class IModelManager
{
public:
	virtual bool				Init() = 0;
	virtual void				Shutdown() = 0;

	virtual Assets::IModel* 	CreateModel( const Assets::ModelDesc& desc ) = 0;
	virtual bool				UpdateModel( Assets::IModel* model, const Assets::ModelDesc& desc ) = 0;
	virtual void				DestroyModel( Assets::IModel* model ) = 0;

	virtual size_t				GetNumModels() const = 0;
	virtual Assets::IModel*		GetModel( uint32_t index ) const = 0;
};
