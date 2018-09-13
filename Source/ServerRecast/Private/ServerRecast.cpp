// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ServerRecast.h"
#include "ServerRecastStyle.h"
#include "ServerRecastCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

// Nav Data
#include "Runtime/Engine/Classes/AI/Navigation/NavigationData.h"
#include "ExportNavMesh.h"

//Test
#include "Runtime/Navmesh/Public/Detour/DetourNavMesh.h"
#include "AI/Navigation/PImplRecastNavMesh.h"
#include "Runtime/Engine/Classes/AI/Navigation/RecastNavMesh.h"
#include "Runtime/Navmesh/Public/Detour/DetourNavMeshBuilder.h"

// Editor
#include "Editor/UnrealEd/Public/Editor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "UnrealEd.h"
#include "LevelEditor.h"

#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProcess.h"
#include <windows.h>

static const FName ServerRecastTabName("ServerRecast");

#define LOCTEXT_NAMESPACE "FServerRecastModule"

void FServerRecastModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FServerRecastStyle::Initialize();
	FServerRecastStyle::ReloadTextures();

	FServerRecastCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FServerRecastCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FServerRecastModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FServerRecastModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FServerRecastModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FServerRecastModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FServerRecastStyle::Shutdown();

	FServerRecastCommands::Unregister();
}

class ARecastNavMeshTrick : public ARecastNavMesh { public: const FPImplRecastNavMesh* GetRecastNavMeshImplTrick() const { return GetRecastNavMeshImpl(); } };

void FServerRecastModule::PluginButtonClicked()
{

	if (UWorld* World = GEditor->GetEditorWorldContext().World())
	{
		// Create mesh
		if (UNavigationSystem* NavSys = World->GetNavigationSystem())
		{
			NavSys->GetAbstractNavData();
			if (ANavigationData* NavData = NavSys->GetMainNavData(FNavigationSystem::ECreateIfEmpty::Create))
			{
				const FString Name =  World->GetMapName() ;// "UE_ExportingLevel";//NavData->GetName();
				const FString Path =  FPaths::ProjectPluginsDir() + "/ServerRecast/recastnavigation/RecastDemo/Bin/Meshes";

				FExportNavMesh* NewRecast = static_cast<FExportNavMesh*>(NavData->GetGenerator());
				
				// Export Landscape
				NewRecast->MyExportNavigationData(FString::Printf(TEXT("%s/%s"), *Path, *Name));

				// Create PathToExecutable. Adding "..." 
				FString PathToExecutable = "\"" + FPaths::ProjectPluginsDir() + TEXT("ServerRecast/recastnavigation/RecastDemo/Bin/\" RecastDemo.exe");
				PathToExecutable = PathToExecutable.Replace(TEXT("/"), TEXT("\\"), ESearchCase::IgnoreCase);

				// Create SaveNavmeshPath
				FString SaveNavmeshPath = FPaths::ProjectDir();
				//SaveNavmeshPath.RemoveFromEnd(FApp::GetProjectName() + FString("/"));
				SaveNavmeshPath = SaveNavmeshPath.Replace(TEXT("/"), TEXT("\\"), ESearchCase::IgnoreCase);

				// Create PathToExecutable. SaveNavmeshPath haven't "...". It already adding to Sample_TileMesh 
				FString EndCommand = TEXT("cmd /c start /D ") + PathToExecutable + TEXT(" 1 ") + Name + TEXT(".obj ") + Name + TEXT(".navmesh ") + "\"" + SaveNavmeshPath + TEXT("Navmeshes\\") ;

				UE_LOG(LogTemp, Log, TEXT(" %s "), *EndCommand);
				system(TCHAR_TO_ANSI(*EndCommand));
				///FPlatformProcess::CreateProc(*PathToExecutable, NULL, true, false, false, NULL, 0, NULL, NULL);
			}
		}
	}

}


void FServerRecastModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FServerRecastCommands::Get().PluginAction);
}

void FServerRecastModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FServerRecastCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FServerRecastModule, ServerRecast)