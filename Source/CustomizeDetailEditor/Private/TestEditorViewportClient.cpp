#include "TestEditorViewportClient.h"

#include "AdvancedPreviewScene.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/WorldSettings.h"

FTestEditorViewportClient::FTestEditorViewportClient()
	: FEditorViewportClient(nullptr, new FPreviewScene(FPreviewScene::ConstructionValues()))
{
	SetRealtime(true);
	
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();


	const UBlueprintCore* BlueprintCore = Cast<UBlueprintCore>(StreamableManager.LoadSynchronous(FSoftObjectPath{TEXT("Blueprint'/Game/NewBlueprint.NewBlueprint'")}));
	PreviewScene->GetWorld()->GetWorldSettings()->NotifyBeginPlay();
	PreviewScene->GetWorld()->GetWorldSettings()->NotifyMatchStarted();
	PreviewScene->GetWorld()->GetWorldSettings()->SetActorHiddenInGame(false);
	PreviewScene->GetWorld()->bBegunPlay = true;
	int32 mn = 53;

	UStaticMeshComponent* SkyComp = NewObject<UStaticMeshComponent>();
	UStaticMesh * StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/MapTemplates/Sky/SM_SkySphere.SM_SkySphere"), NULL, LOAD_None, NULL);
	SkyComp->SetStaticMesh(StaticMesh);
	UMaterial* SkyMaterial = LoadObject<UMaterial>(NULL, TEXT("/Engine/EditorMaterials/PersonaSky.PersonaSky"), NULL, LOAD_None, NULL);
	SkyComp->SetMaterial(0, SkyMaterial);
	const float SkySphereScale = 1000.f;
	const FTransform SkyTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(SkySphereScale));
	PreviewScene->AddComponent(SkyComp, SkyTransform);

	// now add floor
	UStaticMesh* FloorMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh"), NULL, LOAD_None, NULL);
	UStaticMeshComponent* FloorComp = NewObject<UStaticMeshComponent>();
	FloorComp->SetStaticMesh(FloorMesh);
	PreviewScene->AddComponent(FloorComp, FTransform::Identity);
	FloorComp->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	if (BlueprintCore)
	{
		A = PreviewScene->GetWorld()->SpawnActor(BlueprintCore->GeneratedClass);
		if (ACharacter* Character = Cast<ACharacter>(A))
		{
			USkeletalMeshComponent* SkeletalMesh = Character->GetMesh();
			static FRotator CustomOrbitRotation(-33.75, -135, 0);
			FSphere BoundSphere = SkeletalMesh->CalcBounds(SkeletalMesh->GetComponentTransform()).GetSphere();
			FVector CustomOrbitZoom(0, BoundSphere.W / (75.0f * (float)PI / 360.0f), 0);
			FVector CustomOrbitLookAt = BoundSphere.Center;
			SetViewLocation(EditorViewportDefs::DefaultPerspectiveViewLocation);
			SetViewRotation(EditorViewportDefs::DefaultPerspectiveViewRotation);

			UDebugSkelMeshComponent* SkeletalMeshComponent = NewObject<UDebugSkelMeshComponent>(Character);
			if (GEditor->PreviewPlatform.GetEffectivePreviewFeatureLevel() <= ERHIFeatureLevel::ES3_1)
			{
				SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
			}
			PreviewScene->AddComponent(SkeletalMeshComponent, FTransform::Identity);
			PreviewScene->SetPreviewMeshComponent(SkeletalMeshComponent);

			// set root component, so we can attach to it. 
			Actor->SetRootComponent(SkeletalMeshComponent);
			// SetCameraSetup(CustomOrbitLookAt, CustomOrbitRotation, CustomOrbitZoom, CustomOrbitLookAt, GetViewLocation(), GetViewRotation() );
		}
	}
	
}

void FTestEditorViewportClient::Tick(float DeltaTime)
{
	FEditorViewportClient::Tick(DeltaTime);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaTime);
}
