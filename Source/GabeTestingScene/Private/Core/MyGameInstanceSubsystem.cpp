// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameInstanceSubsystem.h"


void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("My subsystem is intialized"))
}

void UMyGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("My subsystem is de-intialized"))
}

void UMyGameInstanceSubsystem::HelloWorld()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World"))
	value += 1;
}

int UMyGameInstanceSubsystem::GetValue()
{
	return value;
}
