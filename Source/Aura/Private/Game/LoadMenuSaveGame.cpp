// Copyright Nathan Guerin


#include "Game/LoadMenuSaveGame.h"

bool ULoadMenuSaveGame::HasMap(const FString& InMapName)
{
	for (const FSavedMap& Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName) return true;
	}
	return false;
}

FSavedMap ULoadMenuSaveGame::GetSavedMapWithMapName(const FString& InMapName)
{
	for (const FSavedMap& Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName) return Map;
	}
	return FSavedMap();
}
