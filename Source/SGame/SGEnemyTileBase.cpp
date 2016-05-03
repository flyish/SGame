// Fill out your copyright notice in the Description page of Project Settings.

#include "SGame.h"
#include "SGEnemyTileBase.h"


ASGEnemyTileBase::ASGEnemyTileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackingElapsedTime = 0;
	AttackingDuration = 1.0f;
	AttackingShakeDegree = 10.0f;
	AttackingShakeFreq = 6;
	AttackingScaleTimeWindow = 0.1f;
	AttackingScaleRatio = 1.3f;
	bIsAttacking = false;
}

void ASGEnemyTileBase::TickAttacking(float DeltaSeconds)
{
	if (bIsAttacking == false)
	{
		return;
	}

	// Calculate the time ratio
	float Ratio = AttackingElapsedTime / AttackingDuration;
	if (Ratio > 1.0f)
	{
		EndAttack();
		return;
	}

	checkSlow(GetRenderComponent());

	// Scale up the tile
	if (Ratio < AttackingScaleTimeWindow)
	{
		// Calculate the scale up ratio
		float ScaleUpRatio = FMath::Lerp(1.0f, AttackingScaleRatio, Ratio / AttackingScaleTimeWindow);
		GetRenderComponent()->SetWorldScale3D(FVector(ScaleUpRatio, ScaleUpRatio, ScaleUpRatio));
	}
	// Scale down the tile
	else if (Ratio > 1 - AttackingScaleTimeWindow)
	{
		// Calculate the scale down ratio
		float ScaleUpRatio = FMath::Lerp(1.0f, AttackingScaleRatio, (1.0f - Ratio) / AttackingScaleTimeWindow);
		GetRenderComponent()->SetWorldScale3D(FVector(ScaleUpRatio, ScaleUpRatio, ScaleUpRatio));
	}
	// We are in shaking 
	else
	{
		// Calculate the shaking ratio
		float CurrentRatio = (Ratio - AttackingScaleTimeWindow) / (1 - AttackingScaleTimeWindow) * PI * AttackingShakeFreq;

		// Do a sin curve to map to [1, -1]
		float FinalRatio = FMath::Sin(CurrentRatio);
		GetRenderComponent()->SetRelativeRotation(FRotator(FinalRatio * AttackingShakeDegree, 0, 0));
	}

	AttackingElapsedTime += DeltaSeconds;
}

void ASGEnemyTileBase::BeginAttack()
{
	bIsAttacking = true;
	AttackingElapsedTime = 0;

	// Pop up our tile on top of the fading sprite

	// Set the attack sprite
	checkSlow(Sprite_Attacking);
	checkSlow(GetRenderComponent());
	GetRenderComponent()->SetSprite(Sprite_Attacking);
}

void ASGEnemyTileBase::EndAttack()
{
	bIsAttacking = false;

	// Pop down the tile to the original place
	

	// Make sure the rotation and scale back to origin
	checkSlow(Sprite_Normal);
	checkSlow(GetRenderComponent());
	GetRenderComponent()->SetSprite(Sprite_Normal);
	GetRenderComponent()->SetRelativeRotation(FRotator(0, 0, 0));
	GetRenderComponent()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void ASGEnemyTileBase::Tick(float DeltaSeconds)
{
	TickAttacking(DeltaSeconds);
	Super::Tick(DeltaSeconds);
}
