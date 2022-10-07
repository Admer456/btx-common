// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

struct ModelDesc;
class IModel;

class IModelManager
{
public:
	virtual bool Init() = 0;
	virtual void Shutdown() = 0;

	virtual IModel* CreateModel( const ModelDesc& desc ) = 0;
	virtual void DestroyModel( IModel* mode ) = 0;

	virtual const Vector<IModel*>& GetModels() const = 0;
};
