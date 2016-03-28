// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PaperSpriteActor.h"

#include "GameFramework/Actor.h"
#include "SGTileBase.generated.h"

/** Types of tile base type. */
UENUM()
namespace ESGTileType
{
	enum Type
	{
		ETT_Sword = 0,					// Sword
		ETT_Shield = 1,					// Shield
		ETT_Potion = 2,					// Potion
		ETT_Coin = 3,					// Coin
		ETT_Mana = 4,					// Mana
		ETT_Arrow = 5,					// Arrow
		ETT_Soldier = 6					// Soldier
	};
}

/** Types of every possible tile state flag that the tile will be in, note it can be in multiple state */
UENUM()
namespace ESGTileStatusFlag
{
	enum Type
	{
		ESF_STATUS_CHANGED,		// Tile status has changed
		ESF_POISONED,			// Tile is posioned
		ESF_BURNING,			// Tile is burning
		ESF_PATH_TYPE,			// Tile is the same type as path
		ESF_DEAD,				// Tile is dead
		ESF_SELECTABLE,			// Tile is linkable
		ESF_MATCHABLE,			// Tile is matchable to the current path
		ESF_BROKEN,				// Tile is broken
		ESF_FROZEN,				// Tile is frozen
		ESF_SELECTED,			// Tile is selected
	};
}

UENUM()
namespace ESGTileLinkType
{
	enum Type
	{
		ETLT_Weapon = 0,					// Sword, Arrow...
		ETLT_Enemy = 1,						// Soldier, Boss... 
		ETLT_Potion = 2,					// HP Potion, Mana Potion, Posion Potion
		ETT_Coin = 3,						// Money
	};
}

USTRUCT()
struct FSGTileAbilities
{
	GENERATED_USTRUCT_BODY();
};

USTRUCT()
struct FSGTileData
{
	GENERATED_USTRUCT_BODY();

public:
	/** The base type of the curernt tile*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESGTileType::Type> TileType;

	/** The current tile status flag, should not be accessed anywhere, for test convenient now*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESGTileStatusFlag::Type> TileStatus;
};

UCLASS()
class SGAME_API ASGTileBase : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGTileBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetGridAddress(int32 NewLocation);
	int32 GetGridAddress() const;

	UPROPERTY(BlueprintReadOnly)
	int32 TileTypeID;

	UPROPERTY(BlueprintReadOnly)
	FSGTileAbilities Abilities;

	UPROPERTY(BlueprintReadOnly)
	FSGTileData TileData;

protected:
	/** Location on the grid as a 1D key/value. To find neighbors, ask the grid. */
	UPROPERTY(BlueprintReadOnly, Category = Tile)
	int32 GridAddress;

	/** Location where we will land on the grid as a 1D key/value. Used while falling. */
	int32 LandingGridAddress;
};
