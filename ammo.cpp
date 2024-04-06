// Include necessary headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Image.h"
#include "Ammo.generated.h"

UCLASS()
class YOURPROJECT_API AAmmo : public AActor
{
    GENERATED_BODY()

public:
    AAmmo();

    // Maximum ammo capacity
    UPROPERTY(EditAnywhere)
    int MaxAmmo = 8;

    // Ammo UI images
    UPROPERTY(EditAnywhere)
    TArray<class UImage*> AmmoUI;

    // Full ammo sprite
    UPROPERTY(EditAnywhere)
    class UTexture2D* FullAmmoSprite;

    // Empty ammo sprite
    UPROPERTY(EditAnywhere)
    class UTexture2D* EmptyAmmoSprite;

    // Reload time
    UPROPERTY(EditAnywhere)
    float ReloadTime = 1.f;

    // Flag to track if reloading is in progress
    bool IsReloading = false;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Method to reload ammo
    void Reload();

    // Method to modify ammo count
    void ModifyAmmo(int Amount);

private:
    // Current ammo count
    int CurrentAmmo;

    // Method to update ammo UI
    void UpdateAmmoUI();

    // Method to finish reloading
    void FinishReload();
};

// Constructor
AAmmo::AAmmo()
{
    // Set default values
    PrimaryActorTick.bCanEverTick = true;
    CurrentAmmo = MaxAmmo;
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
    Super::BeginPlay();

    // Correct initial ammo count if it's greater than the maximum capacity
    CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, MaxAmmo);
    UpdateAmmoUI();
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Method to reload ammo
void AAmmo::Reload()
{
    IsReloading = true;
    // Increment current ammo by one if it's less than the maximum capacity
    if (CurrentAmmo < MaxAmmo)
    {
        CurrentAmmo++;
    }
    UpdateAmmoUI();
    GetWorldTimerManager().SetTimer(TimerHandle_FinishReload, this, &AAmmo::FinishReload, ReloadTime, false);
}

// Method to modify ammo count
void AAmmo::ModifyAmmo(int Amount)
{
    CurrentAmmo += Amount;
    CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, MaxAmmo); // Ensure current ammo stays within limits
    UpdateAmmoUI();
}

// Method to update ammo UI
void AAmmo::UpdateAmmoUI()
{
    for (int32 i = 0; i < AmmoUI.Num(); i++)
    {
        if (i < MaxAmmo)
        {
            if (i < CurrentAmmo)
            {
                AmmoUI[i]->SetBrushFromTexture(FullAmmoSprite);
            }
            else
            {
                AmmoUI[i]->SetBrushFromTexture(EmptyAmmoSprite);
            }
            AmmoUI[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            AmmoUI[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

// Method to finish reloading
void AAmmo::FinishReload()
{
    IsReloading = false;
}
