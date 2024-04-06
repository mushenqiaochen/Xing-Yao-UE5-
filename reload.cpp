// Include necessary headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Reload.generated.h"

UCLASS()
class YOURPROJECT_API AReload : public AActor
{
    GENERATED_BODY()

public:
    AReload();

    // Reload key
    UPROPERTY(EditAnywhere)
    FKey ReloadKey = EKeys::R;

    // Ammo class reference
    UPROPERTY(EditAnywhere)
    class AAmmo* Ammo;

    // Cooldown duration after reloading
    UPROPERTY(EditAnywhere)
    float ReloadCooldown = 3.f;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // Flag to track if reloading is on cooldown
    bool bIsReloadingCooldown;

    // Timer for reloading cooldown
    float ReloadingCooldownTimer;

    // Start the reloading cooldown
    void StartReloadingCooldown();
};

// Constructor
AReload::AReload()
{
    // Set default values
    PrimaryActorTick.bCanEverTick = true;
    bIsReloadingCooldown = false;
    ReloadingCooldownTimer = 0.f;
}

// Called when the game starts or when spawned
void AReload::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AReload::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the reloading cooldown timer
    if (bIsReloadingCooldown)
    {
        ReloadingCooldownTimer -= DeltaTime;

        // Check if the reloading cooldown has ended
        if (ReloadingCooldownTimer <= 0.f)
        {
            bIsReloadingCooldown = false;
        }
    }

    // Check if reloading is not on cooldown and input is received to reload
    if (!bIsReloadingCooldown && GetWorld()->GetFirstPlayerController()->IsInputKeyDown(ReloadKey) && !Ammo->IsReloading && Ammo->CurrentAmmo < Ammo->MaxAmmo)
    {
        // Reload the weapon
        Ammo->Reload();

        // Start the reloading cooldown
        StartReloadingCooldown();
    }
}

// Start the reloading cooldown
void AReload::StartReloadingCooldown()
{
    // Start the reloading cooldown
    bIsReloadingCooldown = true;
    ReloadingCooldownTimer = ReloadCooldown;
}
