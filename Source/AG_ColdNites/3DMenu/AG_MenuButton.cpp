#include "AG_MenuButton.h"
#include "Components/StaticMeshComponent.h"

AAG_MenuButton::AAG_MenuButton()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonRootTransformation = CreateDefaultSubobject<USceneComponent>("RootTransform");
	RootComponent = ButtonRootTransformation;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ButtonMesh->SetupAttachment(GetRootComponent());
	ButtonMesh->SetRelativeLocation(FVector(0.f, 200.f, 0.f));

	ButtonMesh->OnClicked.AddDynamic(this, &AAG_MenuButton::OnButtonClicked);
}

void AAG_MenuButton::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_MenuButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_MenuButton::RotateButton()
{
	
}