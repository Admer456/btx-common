// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#include "Precompiled.hpp"
#include "EngineConfig.hpp"

EngineConfig::EngineConfig( Path pathToEngineConfig )
{
	json jsonData = adm::ParseJSON( pathToEngineConfig.string() );
	if ( jsonData.empty() )
	{
		return;
	}

	engineFolder = jsonData.value( "engineFolder", "unknown" );
	gameFolder = jsonData.value( "gameFolder", "unknown" );

	parsedCorrectly = true;
}
