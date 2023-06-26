#include "TriggerComponent.h"
#include "Components/PrimitiveComponent.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Mover == nullptr)
	{
		return;
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		Mover->SetShouldMove(true);
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

		Component->AttachToComponent
		(
			this,
			FAttachmentTransformRules::KeepWorldTransform
		);

		if(Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{

		if (Actor->ActorHasTag(AcceptableActorTagName) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}