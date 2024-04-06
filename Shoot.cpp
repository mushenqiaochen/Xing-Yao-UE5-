// Include necessary headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimInstance.h"
#include "Shoot.generated.h"

UCLASS()
class YOURPROJECT_API AShoot : public AActor
{
    GENERATED_BODY()

public:
    AShoot();

    // Gun animator component
    UPROPERTY(EditAnywhere)
    class UAnimInstance* GunAnimator;

    // Ammo class reference
    UPROPERTY(EditAnywhere)
    class AAmmo* Ammo;

    // Cooldown duration after shooting
    UPROPERTY(EditAnywhere)
    float ShootCooldown = 3.f;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // Flag to track if shooting is on cooldown
    bool bIsShootingCooldown;

    // Timer for shooting cooldown
    float ShootingCooldownTimer;

    // Start the shooting cooldown
    void StartShootingCooldown();
};

// Constructor
AShoot::AShoot()
{
    // Set default values
    PrimaryActorTick.bCanEverTick = true;
    bIsShootingCooldown = false;
    ShootingCooldownTimer = 0.f;
}

// Called when the game starts or when spawned
void AShoot::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AShoot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the shooting cooldown timer
    if (bIsShootingCooldown)
    {
        ShootingCooldownTimer -= DeltaTime;

        // Check if the shooting cooldown has ended
        if (ShootingCooldownTimer <= 0.f)
        {
            bIsShootingCooldown = false;
        }
    }

    // Check if shooting is not on cooldown and input is received to shoot
    if (!bIsShootingCooldown && GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && Ammo->CurrentAmmo > 0 && !Ammo->IsReloading)
    {
        // Decrement the ammo count using the ModifyAmmo method from the Ammo class
        Ammo->ModifyAmmo(-1);

        // Trigger shooting animation
        if (GunAnimator)
        {
            GunAnimator->Montage_Play(FireMontage, 1.f);
        }

        // Start the shooting cooldown
        StartShootingCooldown();
    }
}

// Start the shooting cooldown
void AShoot::StartShootingCooldown()
{
    // Start the shooting cooldown
    bIsShootingCooldown = true;
    ShootingCooldownTimer = ShootCooldown;
}
