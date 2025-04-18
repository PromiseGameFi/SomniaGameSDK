// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#pragma once

#include "AsyncTasks/Engine/Marketplace/AsyncTaskMarketplaceGetBase.h"
#include "AsyncTaskDirectListingsIsCurrencyApproved.generated.h"

class UThirdwebMarketplace;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class THIRDWEB_API UAsyncTaskDirectListingsIsCurrencyApproved : public UAsyncTaskMarketplaceGetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="Is Currency Approved For Direct Listing", meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"),
		Category="Thirdweb|Engine|Marketplace|Direct Listings|Read|Raw")
	static UAsyncTaskDirectListingsIsCurrencyApproved* IsCurrencyApproved(
		UObject* WorldContextObject,
		UPARAM(DisplayName="Chain ID") const int64 ChainId,
		const FString& Contract,
		UPARAM(DisplayName="Listing ID") const FString& ListingId,
		const FString& Currency
	);

	UFUNCTION(BlueprintCallable, DisplayName="Is Currency Approved For Direct Listing", meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"),
		Category="Thirdweb|Engine|Marketplace|Direct Listings|Read")
	static UAsyncTaskDirectListingsIsCurrencyApproved* MarketplaceIsCurrencyApproved(
		UObject* WorldContextObject,
		const UThirdwebMarketplace* Marketplace,
		UPARAM(DisplayName="Listing ID") const FString& ListingId,
		const FString& Currency
	);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIsCurrencyApprovedDelegate, const bool, bApproved, const FString&, Error);

	UPROPERTY(BlueprintAssignable)
	FIsCurrencyApprovedDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FIsCurrencyApprovedDelegate Failed;

protected:
	UPROPERTY(Transient)
	FString ListingId;

	UPROPERTY(Transient)
	FString CurrencyContractAddress;

private:
	virtual void HandleResponse(const bool bApproved);
	void HandleFailed(const FString& Error);

public:
	virtual void Activate() override;
};
