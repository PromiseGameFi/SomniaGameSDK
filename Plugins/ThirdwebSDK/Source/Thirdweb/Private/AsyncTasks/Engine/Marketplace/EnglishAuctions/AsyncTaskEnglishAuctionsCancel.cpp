// Copyright (c) 2025 Thirdweb. All Rights Reserved.

#include "AsyncTasks/Engine/Marketplace/EnglishAuctions/AsyncTaskEnglishAuctionsCancel.h"

#include "Components/SlateWrapperTypes.h"
#include "Engine/ThirdwebEngine.h"
#include "Engine/Marketplace/ThirdwebMarketplace.h"

UAsyncTaskEnglishAuctionsCancel* UAsyncTaskEnglishAuctionsCancel::Cancel(
	UObject* WorldContextObject,
	const int64 ChainId,
	const FString& Contract,
	const FString& BackendWallet,
	const FSmartWalletHandle& Account,
	const FString& ListingId,
	const FString& IdempotencyKey,
	const bool bSimulateTx
)
{
	NEW_TASK
	Task->Chain = ChainId;
	Task->MarketplaceContract = Contract;
	Task->BackendWalletAddress = BackendWallet;
	Task->SmartWallet = Account;
	Task->ListingId = ListingId;
	Task->Idempotency = IdempotencyKey;
	Task->bSimulateTransaction = bSimulateTx;
	RR_TASK
}

UAsyncTaskEnglishAuctionsCancel* UAsyncTaskEnglishAuctionsCancel::MarketplaceCancel(
	UObject* WorldContextObject,
	const UThirdwebMarketplace* Marketplace,
	const FString& BackendWallet,
	const FSmartWalletHandle& Account,
	const FString& ListingId,
	const FString& IdempotencyKey,
	const bool bSimulateTx
)
{
	NEW_MARKETPLACE_TASK
	Task->Chain = Marketplace->GetChainId();
	Task->MarketplaceContract = Marketplace->GetContractAddress();
	Task->BackendWalletAddress = BackendWallet;
	Task->SmartWallet = Account;
	Task->ListingId = ListingId;
	Task->Idempotency = IdempotencyKey;
	Task->bSimulateTransaction = bSimulateTx;
	RR_TASK
}

void UAsyncTaskEnglishAuctionsCancel::Activate()
{
	ThirdwebEngine::Marketplace::EnglishAuctions::Cancel(
		this,
		Chain,
		MarketplaceContract,
		BackendWalletAddress,
		{SmartWallet},
		ListingId,
		Idempotency,
		bSimulateTransaction,
		BIND_UOBJECT_DELEGATE(FStringDelegate, HandleResponse),
		BIND_UOBJECT_DELEGATE(FStringDelegate, HandleFailed)
	);
}
