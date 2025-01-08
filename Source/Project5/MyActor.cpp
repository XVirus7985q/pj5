#include "MyActor.h"
#include "Math/UnrealMathUtility.h" // FMath 사용을 위한 헤더
#include "Engine/Engine.h"          // UE_LOG 사용

// 생성자
AMyActor::AMyActor()
{
    // Tick 함수 활성화
    PrimaryActorTick.bCanEverTick = true;

    // 시작 위치 초기화
    Start = FVector2D(0.0f, 0.0f);
    PreviousPosition = Start;

    // 이동 및 이벤트 관련 변수 초기화
    TotalDistance = 0.0f;
    TotalEventCount = 0;

    // Move가 한 번만 호출되도록 상태 관리 변수 초기화
    bHasMoved = false;
}

// BeginPlay: 게임 시작 시 호출
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // Move 함수 호출 (단, 한 번만 호출되도록 bHasMoved로 상태 확인)
    if (!bHasMoved)
    {
        Move();
        bHasMoved = true;  // 한 번만 호출되도록 상태 변경
    }
}

// Tick: 매 프레임 호출
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick 함수에서 추가적인 작업이 필요하면 여기에 작성
}

// Step 함수: 0 또는 1을 랜덤 반환
int32 AMyActor::Step()
{
    return FMath::RandRange(0, 1);  // 0 또는 1을 랜덤하게 반환
}

// 이벤트 발생 여부를 결정하는 함수
void AMyActor::TriggerEventWithProbability(float Probability)
{
    int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
    if (RandomValue <= Probability)
    {
        TotalEventCount++;
        UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Event Not Triggered"));
    }
}

// 두 좌표 간 거리 계산 함수
float AMyActor::CalculateDistance(FVector2D First, FVector2D Second)
{
    float dx = First.X - Second.X;
    float dy = First.Y - Second.Y;
    return FMath::Sqrt(dx * dx + dy * dy);  // 거리 계산
}

// Move 함수: 캐릭터를 10번 랜덤하게 이동
void AMyActor::Move()
{
    // 10회 반복하여 이동
    for (int32 i = 0; i < 10; ++i)
    {
        // X와 Y 이동 거리 결정
        int32 DeltaX = Step();
        int32 DeltaY = Step();

        // 이전 위치를 기준으로 새로운 위치 계산
        FVector2D NewPosition = Start + FVector2D(DeltaX, DeltaY);

        // 이동 거리 계산 (이전 위치와 새 위치의 거리 차이)
        float Distance = CalculateDistance(PreviousPosition, NewPosition);
        TotalDistance += Distance;  // 총 이동 거리 갱신

        // 좌표 업데이트
        Start = NewPosition;
        PreviousPosition = Start;

        // 현재 위치와 이동 거리를 로그로 출력
        UE_LOG(LogTemp, Warning, TEXT("Step %d: Moved to (%.1f, %.1f) | Distance: %.2f"), i + 1, Start.X, Start.Y, Distance);

        // 이벤트 발생 여부 확인
        TriggerEventWithProbability(50.0f);  // 50% 확률로 이벤트 발생

    }

    // 총 이동 거리와 총 이벤트 발생 횟수 출력
    UE_LOG(LogTemp, Log, TEXT("Total Distance: %.2f"), TotalDistance);
    UE_LOG(LogTemp, Log, TEXT("Total Events Triggered: %d"), TotalEventCount);
}
