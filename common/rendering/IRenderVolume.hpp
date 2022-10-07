// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	struct VolumeDesc final
	{

	};

	class IVolume
	{
	public:
		virtual VolumeDesc& GetDesc() = 0;
		virtual const VolumeDesc& GetDesc() const = 0;
	};
}
