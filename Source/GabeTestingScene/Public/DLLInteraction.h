// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DLLInteraction.generated.h"

UCLASS()
class GABETESTINGSCENE_API ADLLInteraction : public AActor
{
	GENERATED_BODY()
	
public:
    ADLLInteraction();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void LoadDLL();
    void UnloadDLL();
    void InitializeGDI();
    void ShutdownGDI();
    void CaptureScreenshot();

    // Handle to the DLL
    void* DLLHandle;

    // Function pointers for the DLL functions
    typedef void(*CaptureScreenshotFunc)();
    CaptureScreenshotFunc CaptureScreenshotPtr;

    typedef void(*InitializeGDIPlusFunc)();
    InitializeGDIPlusFunc InitializeGDIPlusPtr;

    typedef void(*ShutdownGDIPlusFunc)();
    ShutdownGDIPlusFunc ShutdownGDIPlusPtr;

    // Timer handle for calling CaptureScreenshot periodically
    FTimerHandle ScreenshotTimer;

};
