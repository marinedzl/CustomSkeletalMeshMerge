#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "CustomSkeletalMeshMergeBPLibrary.generated.h"

USTRUCT(BlueprintType)
struct FCustomSkelMeshMergePart_BP
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Params")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Params")
	FName AttachedBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Params")
	FTransform VerticesTransform;
};

USTRUCT(BlueprintType)
struct  FCustomSkelMeshMergeSectionMapping_BP
{
	GENERATED_BODY()

	/** Indices to final section entries of the merged skeletal mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Params")
	TArray<int32> SectionIDs;
};

/**
* Struct containing all parameters used to perform a Skeletal Mesh merge.
*/
USTRUCT(BlueprintType)
struct  FCustomSkeletalMeshMergeParams
{
	GENERATED_BODY()

	FCustomSkeletalMeshMergeParams()
	{
		StripTopLODS = 0;
		bNeedsCpuAccess = false;
		bSkeletonBefore = false;
		Skeleton = nullptr;
	}

	// An optional array to map sections from the source meshes to merged section entries
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCustomSkelMeshMergeSectionMapping_BP> MeshSectionMappings;

	// The list of skeletal meshes to merge.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCustomSkelMeshMergePart_BP> MeshesToMerge;

	// The number of high LODs to remove from input meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StripTopLODS;

	// Whether or not the resulting mesh needs to be accessed by the CPU for any reason (e.g. for spawning particle effects).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bNeedsCpuAccess : 1;

	// Update skeleton before merge. Otherwise, update after.
	// Skeleton must also be provided.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bSkeletonBefore : 1;

	// Skeleton that will be used for the merged mesh.
	// Leave empty if the generated skeleton is OK.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeleton* Skeleton;

	// Material that will be used for the merged mesh.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* BaseMaterial;
};

UCLASS()
class UCustomSkeletalMeshMergeBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* Merges the given meshes into a single mesh.
	* @return The merged mesh (will be invalid if the merge failed).
	*/
	//UFUNCTION(BlueprintCallable, Category = "Mesh Merge", meta = (UnsafeDuringActorConstruction = "true"))
	UFUNCTION(BlueprintCallable, Category = "Mesh Merge")
	static class USkeletalMesh* MergeMeshes(const FCustomSkeletalMeshMergeParams& Params);
};
