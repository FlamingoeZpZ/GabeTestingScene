// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDLL.generated.h"

UCLASS()
class GABETESTINGSCENE_API ATestDLL : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDLL();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void* DLLHandle;

	/*
	* extern "C" __declspec(dllexport) void MyDemo(float time);
extern "C" __declspec(dllexport) float t();
	 */
	typedef void(*TestOne)(float);
	TestOne TestOneFunction;

	typedef float(*TestTwo)();
	TestTwo TestTwoFunction;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
