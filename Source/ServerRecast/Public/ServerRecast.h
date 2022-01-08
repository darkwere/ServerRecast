// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Modules/ModuleManager.h"

#include "Windows/AllowWindowsPlatformTypes.h"

//The external headers and defines goes here


class FToolBarBuilder;
class FMenuBuilder;


class FServerRecastModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();

	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};