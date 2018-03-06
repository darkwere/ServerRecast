// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ServerRecastCommands.h"

#define LOCTEXT_NAMESPACE "FServerRecastModule"

void FServerRecastCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ServerRecast", "Execute ServerRecast action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
