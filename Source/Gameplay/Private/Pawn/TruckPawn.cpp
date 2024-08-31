#include "Pawn/TruckPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Logging/StructuredLog.h"
#include "Widgets/TruckNumberWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "NavModifierComponent.h"

ATruckPawn::ATruckPawn() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	IsTruckDestroyed = false;
	MeshBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBody"));
	MeshBody->SetStaticMesh(TruckStaticMesh);
	SetRootComponent(MeshBody);
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(MeshBody);
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Navigation"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void ATruckPawn::SetTruckDestroyed(bool InIsTruckDestroyed)
{
	IsTruckDestroyed = InIsTruckDestroyed;
	
	if (IsTruckDestroyed)
	{
		MeshBody->SetStaticMesh(DestroyedTruckStaticMesh);
		MeshBody->SetMaterial(0, DestroyedTruckMaterial);
		BlockArea();
	}
	else
	{
		MeshBody->SetStaticMesh(TruckStaticMesh);
		MeshBody->SetMaterial(0, TruckMaterial);
	}
}

bool ATruckPawn::GetIsTruckDestroyed() const
{
	return IsTruckDestroyed;
}

void ATruckPawn::SetPawnWidgetNumber(int InNumber)
{
	auto Widget = Cast<UTruckNumberWidget>(WidgetComponent->GetWidget());
	Widget->SetTruckNumberText(FText::FromString(FString::FromInt(InNumber)));
}

void ATruckPawn::InitWidgetComponent()
{
	WidgetComponent->InitWidget();
}

void ATruckPawn::BlockArea()
{
	BlockingObject = NewObject<UNavModifierComponent>(this, "BlockingObject");
	BlockingObject->RegisterComponent();
	FTransform t = GetTransform();
	FVector Location = t.GetLocation();
	Location.Z -= 320;// need to push to the ground. becouse physic os not working
	t.SetLocation(Location);
	CollisionComponent->SetWorldTransform(t);
}

UWidgetComponent* ATruckPawn::GetWidgetComponent()
{
	return WidgetComponent;
}

void ATruckPawn::Tick(float DeltaTime)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	auto WorlRoatation = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->K2_GetComponentLocation(), CameraManager->GetTransformComponent()->GetComponentLocation());
	WidgetComponent->SetWorldRotation(WorlRoatation);
}

TrackPawnArray FindAllPawnTrucks(UObject* InWorldContext)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(InWorldContext->GetWorld(), ATruckPawn::StaticClass(), FoundActors);
	TrackPawnArray TruckArray;

	if (FoundActors.Num() > 0)
	{
		for (int i = 0; i < FoundActors.Num(); i++)
		{
			TruckArray.Add(Cast<ATruckPawn>(FoundActors[i]));

		}
	}
	else
	{
		UE_LOGFMT(LogTemp, Warning, "ATruck actors is  not founded on map!");
	}

	return TruckArray;
}