// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ServerRecastStyle.h"

class FServerRecastCommands : public TCommands<FServerRecastCommands>
{
public:

	FServerRecastCommands()
		: TCommands<FServerRecastCommands>(TEXT("ServerRecast"), NSLOCTEXT("Contexts", "ServerRecast", "ServerRecast Plugin"), NAME_None, FServerRecastStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
