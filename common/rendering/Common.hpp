// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

namespace Render
{
	constexpr uint8_t RenderMaskAll = 0xff;
	constexpr uint8_t RenderMaskNone = 0x00;
	constexpr uint8_t RenderMaskDefault = RenderMaskAll;

	using IBackend = nvrhi::IDevice;
}
