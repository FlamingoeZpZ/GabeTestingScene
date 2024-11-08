// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDLL.h"

// Sets default values
ATestDLL::ATestDLL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestDLL::BeginPlay()
{
	Super::BeginPlay();

	FString DLLPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries/Win64/MyTestingDLL.dll"));
	DLLHandle = FPlatformProcess::GetDllHandle(*DLLPath);

	if (DLLHandle)
	{
		// Bind function pointers
		TestOneFunction = (TestOne)FPlatformProcess::GetDllExport(DLLHandle, TEXT("MyDemo"));
		TestTwoFunction = (TestTwo)FPlatformProcess::GetDllExport(DLLHandle, TEXT("Mutate"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DLL."));
	}

	TestOneFunction(GetActorLocation().X);
}

// Called every frame
void ATestDLL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FVector::ForwardVector * TestTwoFunction());
}

