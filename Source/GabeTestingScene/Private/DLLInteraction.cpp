#include "DLLInteraction.h"
#include "HAL/PlatformProcess.h"
#include "Engine/World.h"

ADLLInteraction::ADLLInteraction()
{
    DLLHandle = nullptr;
    CaptureScreenshotPtr = nullptr;
    InitializeGDIPlusPtr = nullptr;
    ShutdownGDIPlusPtr = nullptr;
}

void ADLLInteraction::BeginPlay()
{
    Super::BeginPlay();

    LoadDLL();
    InitializeGDI();

    // Set a timer to call CaptureScreenshot every 3 seconds
    GetWorld()->GetTimerManager().SetTimer(ScreenshotTimer, this, &ADLLInteraction::CaptureScreenshot, 3.0f, true);
}

void ADLLInteraction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Clear the timer
    GetWorld()->GetTimerManager().ClearTimer(ScreenshotTimer);

    // Clean up DLL resources
    ShutdownGDI();
    UnloadDLL();
}

void ADLLInteraction::LoadDLL()
{
    FString DLLPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries/Win64/GameStatsDLL.dll"));
    DLLHandle = FPlatformProcess::GetDllHandle(*DLLPath);

    if (DLLHandle)
    {
        // Bind function pointers
        CaptureScreenshotPtr = (CaptureScreenshotFunc)FPlatformProcess::GetDllExport(DLLHandle, TEXT("CaptureScreenshot"));
        InitializeGDIPlusPtr = (InitializeGDIPlusFunc)FPlatformProcess::GetDllExport(DLLHandle, TEXT("InitializeGDIPlus"));
        ShutdownGDIPlusPtr = (ShutdownGDIPlusFunc)FPlatformProcess::GetDllExport(DLLHandle, TEXT("ShutdownGDIPlus"));

        if (!CaptureScreenshotPtr || !InitializeGDIPlusPtr || !ShutdownGDIPlusPtr)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to bind one or more DLL functions."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load DLL."));
    }
}

void ADLLInteraction::UnloadDLL()
{
    if (DLLHandle)
    {
        FPlatformProcess::FreeDllHandle(DLLHandle);
        DLLHandle = nullptr;
    }
}

void ADLLInteraction::InitializeGDI()
{
    if (InitializeGDIPlusPtr)
    {
        InitializeGDIPlusPtr();
        UE_LOG(LogTemp, Log, TEXT("GDI+ initialized."));
    }
}

void ADLLInteraction::ShutdownGDI()
{
    if (ShutdownGDIPlusPtr)
    {
        ShutdownGDIPlusPtr();
        UE_LOG(LogTemp, Log, TEXT("GDI+ shutdown."));
    }
}

void ADLLInteraction::CaptureScreenshot()
{
    if (CaptureScreenshotPtr)
    {
        CaptureScreenshotPtr();
        UE_LOG(LogTemp, Log, TEXT("Screenshot captured."));
    }
}
