#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    AMyActor();

protected:
    // 게임 시작 시 호출되는 함수
    virtual void BeginPlay() override;

public:
    // 매 프레임 호출되는 함수
    virtual void Tick(float DeltaTime) override;

private:
    // 현재 위치를 저장하는 2D 벡터
    FVector2D Start;

    // 이전 위치를 저장하는 2D 벡터 (이동 거리 계산을 위해 필요)
    FVector2D PreviousPosition;

    // 랜덤하게 0 또는 1을 반환
    int32 Step();

    // 이동 함수
    void Move();

    // 이벤트 발생 여부 함수
    void TriggerEventWithProbability(float Probability);

    // 이동 거리 계산 함수
    float CalculateDistance(FVector2D First, FVector2D Second);

    // 이동과 이벤트 발생 관련 변수
    float TotalDistance;    // 총 이동 거리
    int32 TotalEventCount;  // 총 이벤트 발생 횟수

    // Move 함수가 한 번만 실행되도록 상태 관리
    bool bHasMoved;
};
