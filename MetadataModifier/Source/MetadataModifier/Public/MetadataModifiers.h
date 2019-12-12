// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MetadataModifiers.generated.h"

USTRUCT(BlueprintType)
struct FMetaModifierProperty
{
	GENERATED_USTRUCT_BODY()
public:

	FMetaModifierProperty() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	This is the actual name of the metamodifier.
		FName MetaModifierName;


	//	These are the possible values for a metamodifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Integer = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Float = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Vector = FVector(0,0,0);
};

DECLARE_LOG_CATEGORY_EXTERN(LogMetaModifiers, Log, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METADATAMODIFIER_API UMetadataModifiers : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMetadataModifiers();

	UPROPERTY(Category = "MetaModifiers", BlueprintReadOnly)
		//	The main container for the metamodifiers owned by this component
		TArray<FMetaModifierProperty> MetaModifiers;


	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		const TArray<FMetaModifierProperty> GetMetaModifiersByName(const FName& MetaModifierName) const;

	
	
	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		float GetMetaModifierValue_Float(const FName& metaModifierName);

	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		int32 GetMetaModifierValue_Integer(const FName& metaModifierName);

	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		FVector GetMetaModifierValue_Vector(const FName& metaModifierName);



	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		TArray<FName> GetMetaModifierNamesInUse() const;

	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		bool IsMetamodifierNameInUse(const FName& metaModifierNameToFind) const;

	UFUNCTION(Category = "MetaModifiers", BlueprintCallable)
		void AddMetaModifier(const FMetaModifierProperty& metaMod);


	template<class T> T GetMetamodifierValue(const FName MetaModifierName) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};